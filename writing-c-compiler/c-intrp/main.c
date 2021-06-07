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

void next() {
    token = *src++;
}

void expression(int level) {
    // do nothing
}

void program() {
    next();  // get next token
    while (token > 0) {
        printf("token is : %c\n", token);
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

int main(int argc, char** argv)
{
    int i, fd;
    poolsize = 256 * 1024;  // arbitrary size
    line = 1;
#if 1
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
#endif
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

#if 0 // test code
    i = 0;
    text[i++] = IMM;
    text[i++] = 10;
    text[i++] = PUSH;
    text[i++] = IMM;
    text[i++] = 20;
    text[i++] = ADD;
    text[i++] = PUSH;
    text[i++] = EXIT;
    pc = text;
#else
    program();
#endif

    return eval();
}
