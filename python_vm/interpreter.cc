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
#define STACK_LEVEL() _stack->size()

Interpreter::~Interpreter()
{
	delete _stack;
	delete _vars;
	delete _loop_stack;
}

void Interpreter::run(CodeObject* codes)
{
	int pc = 0;
	int code_length = codes->_bytecodes->length();

	_stack = new ArrayList<HiObject*>(codes->_stack_size);
	_consts = codes->_consts;
	auto&& names = codes->_names;

	_vars = new Map<HiObject*, HiObject *>();
	_loop_stack = new ArrayList<Block*>();

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
		case ByteCode::SETUP_LOOP:
			_loop_stack->add(new Block(op_code, pc + op_arg, STACK_LEVEL()));
			break;
		case ByteCode::POP_BLOCK: {
			auto&& b = _loop_stack->pop();
			while (STACK_LEVEL() > b->_level) {
				POP();
			}
			break;
		}
		case ByteCode::BREAK_LOOP: {
			auto&& b = _loop_stack->pop();
			while (STACK_LEVEL() > b->_level) {
				POP();
			}
			pc = b->_target;
			break;
		}
		case ByteCode::STORE_NAME:
			_vars->put(names->get(op_arg), POP());
			break;
		case ByteCode::LOAD_NAME:
			PUSH(_vars->get(names->get(op_arg)));
			break;
		case ByteCode::LOAD_CONST:
			PUSH(_consts->get(op_arg));
			break;
		case ByteCode::PRINT_ITEM:
			v = POP();
			v->print();
			break;
		case ByteCode::PRINT_NEWLINE:
			printf("\n");
			fflush(stdout);
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
				fprintf(stderr, "ERROR: Unrecognized compare op %d\n", op_arg);
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
		case ByteCode::JUMP_ABSOLUTE:
			pc = op_arg;
			break;
		default:
			fprintf(stderr, "ERROR: unrecognized byte code %d\n", op_code);
			assert(0);
		}
	}
}
