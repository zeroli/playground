#include "interpreter.h"

#include <cassert>

#include "code_object.h"
#include "bytecode.h"
#include "hi_object.h"
#include "hi_string.h"
#include "hi_integer.h"
#include "universe.h"
#include "frame_object.h"
#include "function_object.h"

#define PUSH(x) _frame->stack()->add(x)
#define POP() _frame->stack()->pop()
#define STACK_LEVEL() _frame->stack()->size()

Interpreter::~Interpreter()
{
	delete _vars;
}

void Interpreter::run(CodeObject* codes)
{
	_frame = new FrameObject(codes);

	eval_frame();
	destroy_frame();
}

void Interpreter::eval_frame()
{
	_vars = new Map<HiObject*, HiObject *>();

	while (_frame->has_more_codes()) {
		unsigned char op_code = _frame->get_op_code();
		bool has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

		int op_arg = -1;
		if (has_argument) {
			op_arg = _frame->get_op_arg();
		}

		//HiInteger* lhs, *rhs;
		HiObject* v, *w, *u, *attr;
		switch (op_code) {
		case ByteCode::POP_TOP:
			POP();
			break;
		case ByteCode::SETUP_LOOP:
			_frame->loop_stack()->add(new Block(op_code, _frame->get_pc() + op_arg, STACK_LEVEL()));
			break;
		case ByteCode::POP_BLOCK: {
			auto&& b = _frame->loop_stack()->pop();
			while (STACK_LEVEL() > b->_level) {
				POP();
			}
			break;
		}
		case ByteCode::BREAK_LOOP: {
			auto&& b = _frame->loop_stack()->pop();
			while (STACK_LEVEL() > b->_level) {
				POP();
			}
			_frame->set_pc(b->_target);
			break;
		}
		case ByteCode::STORE_NAME:
			_vars->put(_frame->names()->get(op_arg), POP());
			break;
		case ByteCode::LOAD_NAME:
			PUSH(_vars->get(_frame->names()->get(op_arg)));
			break;
		case ByteCode::LOAD_CONST:
			PUSH(_frame->consts()->get(op_arg));
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
			_ret_value = POP();
			if (_frame->is_first_frame())
				return;
			leave_frame();
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
				_frame->set_pc(op_arg);
			break;
		case ByteCode::JUMP_FORWARD:
			_frame->set_pc(_frame->get_pc() + op_arg);
			break;
		case ByteCode::JUMP_ABSOLUTE:
			_frame->set_pc(op_arg);
			break;
		case ByteCode::MAKE_FUNCTION:
		{
			v = POP();  // code object
			auto fo = new FunctionObject(v);
			PUSH(fo);
			break;
		}
		case ByteCode::CALL_FUNCTION:
			build_frame(POP());
			break;
		default:
			fprintf(stderr, "ERROR: unrecognized byte code %d\n", op_code);
			assert(0);
		}
	}
}

void Interpreter::leave_frame()
{
	destroy_frame();
	PUSH(_ret_value);
}

void Interpreter::destroy_frame()
{
	FrameObject* tmp = _frame;
	_frame = _frame->get_parent();
	delete tmp;
}

void Interpreter::build_frame(HiObject* callable)
{
	FrameObject* frame = new FrameObject(((FunctionObject*)callable)->func_code());
	frame->set_parent(_frame);
	_frame = frame;
}