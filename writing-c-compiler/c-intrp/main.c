#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token;              // current token
char* src, *old_src;  // pointer to source code string
int poolsize;           // default size of text/data/stack
int line;               // line number

int *text,  // text segment
   *old_text,  // for dump text segment
   *stack;    // stack
char* data;  // data segment

int *pc, *bp, *sp, ax, cycle;  // virtual machine registers

enum {
    LEA = 0,
    IMM,
    JMP,
    CALL,
    JZ,
    JNZ,
    ENT,
    ADJ,
    LEV,
    LI,
    LC,
    SI,
    SC,
    PUSH,
    OR,
    XOR,
    AND,
    EQ,
    NE,
    LT,
    GT,
    LE,
    GE,
    SHL,
    SHR,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    OPEN,
    READ,
    CLOS,
    PRTF,
    MALC,
    MSET,
    MCMP,
    EXIT
};

// tokens and classes (operators last and in precedence order)
enum {
    Num = 128, Fun, Sys, Glo, Loc, Id,
    Char, Else, Enum, If, Int, Return, Sizeof, While,
    Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod,
    Inc, Dec, Brak
};
char TokenStr[100];

struct identifer {
    int token;
    int hash;
    char* name;
    int class;
    int type;
    int value;
    int Bclass;
    int Btype;
    int Bvalue;
};

int token_val;  // value of current token (mainly for number)
int *current_id,  // current parsed ID
    *symbols;  // symbol table

enum { Token, Hash, Name, Type, Class, Value, BType, BValue, IdSize };

void next() {
    char* last_pos;
    int hash;
    while (token = *src) {
        ++src;
        if (token == '\n') {
            ++line;
            strcpy(TokenStr, "NewLine");
        } else if (token == '#') {
            // skip macro, because we will not support it
            while (*src != 0 && *src != '\n') {
                src++;
            }
            strcpy(TokenStr, "#");
        } else if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token == '_')) {
            strcpy(TokenStr, "Identifier");
            // parse identifier
            last_pos = src - 1;
            hash = token;
            while ((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z') || (*src >= 'a' && *src <= 'z')) {
                hash = hash * 147 + *src;
                src++;
            }
            // look for existing identifier, linear search
            current_id = symbols;
            while (current_id[Token]) {
                if (current_id[Hash] == hash && !memcmp((char*)current_id[Name], last_pos, src - last_pos)) {
                    // found one, return
                    token = current_id[Token];
                    return;
                }
                current_id = current_id + IdSize;
            }
            // store new ID
            current_id[Name] = (int)last_pos;
            current_id[Hash] = hash;
            token = current_id[Token] = Id;

            return;
        } else if (token >= '0' && token <= '9') {
            // parse number, three kinds: dec(123) hex(0x123) oct(017)
            token_val = token - '0';
            if (token_val > 0) {
                // dec, starts with [1-9]
                while (*src >= '0' && *src <= '9') {
                    token_val = token_val * 10 + *src++ - '0';
                }
            } else {
                // starts with number 0
                if (*src == 'x' || *src == 'X') {
                    // hex
                    token = *++src;
                    while ((token >= '0' && token <= '9') || (token >= 'a' && token <= 'f') || (token >= 'A' && token <= 'F')) {
                        token_val = token_val * 16 + (token & 0xF) + (token >= 'A' ? 9 : 0);
                        token = *++src;
                    }
                } else {
                    // oct
                    while (*src >= '0' && *src <= '7') {
                        token_val = token_val * 8 + *src++ - '0';
                    }
                }
            }
            token = Num;
            strcpy(TokenStr, "Number");
            return;
        } else if (token == '"' || token == '\'') {
            // parse string literal, currently, the only supported escape
            // character is '\n', store the string literal into data
            last_pos = data;
            while (*src != 0 && *src != token) {
                token_val = *src++;
                if (token_val == '\\') {
                    // escape character
                    token_val = *src++;
                    if (token_val == 'n') {
                        token_val = '\n';
                    }
                }
                if (token == '"') {
                    *data++ = token_val;
                }
            }
            src++;
            // if it is a single character, return Num token
            if (token == '"') {
                token_val = (int)last_pos;
                strcpy(TokenStr, "String Literal");
            } else {
                token = Num;
                strcpy(TokenStr, "Number");
            }
            return;
        } else if (token == '/') {
            if (*src == '/') {
                // skip comments
                while (*src != 0 && *src != '\n') {
                    ++src;
                }
            } else {
                // divide operator
                token = Div;
                strcpy(TokenStr, "Division");
                return;
            }
        } else if (token == '=') {
            // parse '==' and '='
            if (*src == '=') {
                src++;
                token = Eq;
                strcpy(TokenStr, "==");
            } else {
                token = Assign;
                strcpy(TokenStr, "=");
            }
            return;
        } else if (token == '+') {
            // parse '+' and '++'
            if (*src == '+') {
                src++;
                token = Inc;
                strcpy(TokenStr,  "++");
            } else {
                token = Add;
                strcpy(TokenStr, "+");
            }
            return;
        } else if (token == '-') {
            // parse '-' and '--'
            if (*src == '-') {
                src++;
                token = Dec;
                strcpy(TokenStr, "--");
            } else {
                token = Sub;
                strcpy(TokenStr, "-");
            }
            return;
        } else if (token == '!') {
            // parse '!='
            if (*src == '=') {
                src++;
                token = Ne;
                strcpy(TokenStr, "!=");
            }
            return;
        } else if (token == '<') {
            // parse '<=', '<<' or '<'
            if (*src == '=') {
                src++;
                token = Le;
                strcpy(TokenStr, "<=");
            } else if (*src == '<') {
                src++;
                token = Shl;
                strcpy(TokenStr, "<<");
            } else {
                token = Lt;
                strcpy(TokenStr, "<");
            }
            return;
        } else if (token == '>') {
            // parse '>=', '>>', or '>'
            if (*src == '=') {
                src++;
                token = Ge;
                strcpy(TokenStr, ">=");
            } else if (*src == '>') {
                src++;
                token = Shr;
                strcpy(TokenStr, ">>");
            } else {
                token = Gt;
                strcpy(TokenStr, ">");
            }
            return;
        } else if (token == '|') {
            // parse '||', and '|'
            if (*src == '|') {
                src++;
                token = Lor;
                strcpy(TokenStr, "||");
            } else {
                token = Or;
                strcpy(TokenStr, "|");
            }
            return;
        } else if (token == '&') {
            // parse '&&', or '&'
            if (*src == '&') {
                src++;
                token = Lan;
                strcpy(TokenStr, "&&");
            } else {
                token = And;
                strcpy(TokenStr, "&");
            }
            return;
        } else if (token == '^') {
            token = Xor;
            strcpy(TokenStr, "^");
            return;
        } else if (token == '%') {
            token = Mod;
            strcpy(TokenStr, "%");
            return;
        } else if (token == '*') {
            token = Mul;
            strcpy(TokenStr, "*");
            return;
        } else if (token == '[') {
            token = Brak;
            strcpy(TokenStr, "[");
            return;
        } else if (token == '?') {
            token = Cond;
            strcpy(TokenStr, "?");
            return;
        } else if (token == '~' || token == ';' || token == '{' || token == '}' ||
            token == '(' || token == ')' || token == ']' || token == ',' || token == ':') {
            // directly return character as token
            TokenStr[0] = (char)token;
            TokenStr[1] = '\0';
            return;
        }
    }
}

void expression(int level) {
    // do nothing
}

void program() {
    next();  // get next token
    while (token > 0) {
        printf("token is : %d ('%s')\n", token, TokenStr);
        next();
    }
}

int eval() {
    int op, *tmp;
    while (1) {
        op = (int)*pc++;
        switch (op) {
        case IMM:
            ax = *pc++;
            break;
        case LC:
            ax = *(char*)ax;
            break;
        case LI:
            ax = *(int*)ax;
            break;
        case SC:
            *(char*)*sp++ = ax;
            break;
        case SI:
            *(int*)*sp++ = ax;
            break;
        case PUSH:
            *--sp = ax;
            break;
        case JMP:
            pc = (int*)*pc;
            break;
        case JZ:
            pc = ax ? pc + 1 : (int*)*pc;
            break;
        case JNZ:
            pc = ax ? (int*)*pc : pc + 1;
            break;
        case CALL:
            *--sp = (int)(pc+1);
            pc = (int*)*pc;
            break;
        case ENT:
            *--sp = (int)bp;
            bp = sp;
            sp = sp - *pc++;
            break;
        case ADJ:
            sp = sp + *pc++;
            break;
        case LEV:
            sp = bp;
            bp = (int*)*sp++;
            pc = (int*)*sp++;
            break;
        case LEA:
            ax = (int)(bp + *pc++);
            break;
        case OR:
            ax = *sp++ | ax;
            break;
        case XOR:
            ax = *sp++ ^ ax;
            break;
        case AND:
            ax = *sp++ & ax;
            break;
        case EQ:
            ax = *sp++ == ax;
            break;
        case NE:
            ax = *sp++ != ax;
            break;
        case LT:
            ax = *sp++ < ax;
            break;
        case LE:
            ax = *sp++ <= ax;
            break;
        case GT:
            ax = *sp++ > ax;
            break;
        case GE:
            ax = *sp++ >= ax;
            break;
        case SHL:
            ax = *sp++ << ax;
            break;
        case SHR:
            ax = *sp++ >> ax;
            break;
        case ADD:
            ax = *sp++ + ax;
            break;
        case SUB:
            ax = *sp++ - ax;
            break;
        case MUL:
            ax = *sp++ * ax;
            break;
        case DIV:
            ax = *sp++ / ax;
            break;
        case MOD:
            ax = *sp++ % ax;
            break;
        case EXIT:
            printf("exit(%d)", *sp);
            return *sp;
        case OPEN:
            ax = open((char*)sp[1], sp[0]);
            break;
        case CLOS:
            ax = close(*sp);
            break;
        case READ:
            ax = read(sp[2], (char*)sp[1], *sp);
            break;
        case PRTF:
            tmp = sp + pc[1];
            ax = printf((char*)tmp[-1], tmp[-2], tmp[-3], tmp[-4], tmp[-5], tmp[-6]);
            break;
        case MALC:
            ax = (int)malloc(*sp);
            break;
        case MSET:
            ax = (int)memset((char*)sp[2], sp[1], *sp);
            break;
        case MCMP:
            ax = memcmp((char*)sp[2], (char*)sp[1], *sp);
            break;
        default:
            printf("unknown instruction:%d\n", op);
            return -1;
        }
    }
    return 0;
}

// types of variable/function
enum { CHAR, INT, PTR };
int *idmain;  // the 'main' function

int main(int argc, char** argv)
{
    int i, fd;
    poolsize = 256 * 1024;  // arbitrary size
    line = 1;

    argc--;
    argv++;
    if ((fd = open(*argv, 0)) < 0) {
        printf("could not open (%s)\n", *argv);
        return -1;
    }

    if (!(src = old_src = malloc(poolsize))) {
        printf("could not malloc(%d) for source area\n", poolsize);
        return -1;
    }

    // read the source file
    if ((i = read(fd, src, poolsize - 1)) <= 0) {
        printf("read() returned %d\n", i);
        return -1;
    }
    src[i] = 0;  // add EOF charater
    close(fd);

    // allocate memory for virtual machine
    if (!(text = old_text = malloc(poolsize))) {
        printf("could not malloc(%d) for text area\n", poolsize);
        return -1;
    }
    if (!(data = malloc(poolsize))) {
        printf("could not malloc(%d) for data area\n", poolsize);
        return -1;
    }
    if (!(stack = malloc(poolsize))) {
        printf("could not malloc(%d) for stack area\n", poolsize);
        return -1;
    }
    memset(text, 0, poolsize);
    memset(data, 0, poolsize);
    memset(stack, 0, poolsize);

    bp = sp = (int*)((int)stack + poolsize);
    ax = 0;

    if (!(symbols = malloc(poolsize))) {
        printf("could not malloc(%d) for symbols area\n", poolsize);
        return -1;
    }
    memset(symbols, 0, poolsize);

    program();

    src = "char else enum if int return sizeof while "
        "open read close printf malloc memset memcmp exit void main";
    // add keywords to symbol table
    i = Char;
    while (i <= While) {
        next();
        current_id[Token] = i++;
    }

    // add library to symbol table
    i = OPEN;
    while (i <= EXIT) {
        next();
        current_id[Class] = Sys;
        current_id[Type] = INT;
        current_id[Value] = i++;
    }
    next(); current_id[Token] = Char;  // handle void type
    next(); idmain = current_id;  // keep track of main

    return eval();
}
