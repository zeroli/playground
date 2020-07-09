#include "interpreter.h"

#include <cassert>

#include "code_object.h"
#include "bytecode.h"
#include "hi_object.h"
#include "hi_string.h"
#include "hi_integer.h"
#include "universe.h"

#define PUSH(x) _stack->add(x)
#define POP() _stack->pop()

void Interpreter::run(CodeObject* codes)
{
	int pc = 0;
	int code_length = codes->_bytecodes->length();

	_stack = new ArrayList<HiObject*>(codes->_stack_size);
	_consts = codes->_consts;

	while (pc < code_length) {
		unsigned char op_code = codes->_bytecodes->value()[pc++];
		bool has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

		int op_arg = -1;
		if (has_argument) {
			int byte1 = (codes->_bytecodes->value()[pc++] & 0xFF);
			op_arg = ((codes->_bytecodes->value()[pc++] & 0xFF) << 8) | byte1;
		}

		//HiInteger* lhs, *rhs;
		HiObject* v, *w, *u, *attr;
		switch (op_code) {
		case ByteCode::LOAD_CONST:
			PUSH(_consts->get(op_arg));
			break;
		case ByteCode::PRINT_ITEM:
			v = POP();
			v->print();
			break;
		case ByteCode::PRINT_NEWLINE:
			printf("\n");
			break;
		case ByteCode::BINARY_ADD:
			v = POP();
			w = POP();
			PUSH(w->add(v));
			break;
		case ByteCode::RETURN_VALUE:
			POP();
			break;
		case ByteCode::COMPARE_OP:
			w = POP();
			v = POP();
			switch (op_arg) {
			case COMPARE::GREATER:
				PUSH(v->greater(w));
				break;
			case COMPARE::LESS:
				PUSH(v->less(w));
				break;
			case COMPARE::EQUAL:
				PUSH(v->equal(w));
				break;
			case COMPARE::NOT_EQUAL:
				PUSH(v->not_equal(w));
				break;
			case COMPARE::GREATER_EQUAL:
				PUSH(v->ge(w));
				break;
			case COMPARE::LESS_EQUAL:
				PUSH(v->le(w));
				break;
			default:
				printf("ERROR: Unrecognized compare op %d\n", op_arg);
				assert(0);
			}
			break;
		case ByteCode::POP_JUMP_IF_FALSE:
			v = POP();
			if (v == Universe::HiFalse)
				pc = op_arg;
			break;
		case ByteCode::JUMP_FORWARD:
			pc += op_arg;
			break;
		default:
			printf("ERROR: unrecognized byte code %d\n", op_code);
			assert(0);
		}
	}
}
