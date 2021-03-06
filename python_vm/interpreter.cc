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
#include "method_object.h"

#define PUSH(x) _frame->stack()->add(x)
#define POP() _frame->stack()->pop()
#define STACK_LEVEL() _frame->stack()->size()
#define DBG(...) fprintf(stderr, __VA_ARGS__)

Interpreter::Interpreter()
	: _builtins(new Map<HiObject*, HiObject*>())
	, _frame(nullptr), _ret_value(nullptr)
{
	_builtins->put(new HiString("True"), Universe::HiTrue);
	_builtins->put(new HiString("False"), Universe::HiFalse);
	_builtins->put(new HiString("None"), Universe::HiNone);
	_builtins->put(new HiString("len"), new FunctionObject(len));

	ByteCode::initialize();
}

Interpreter::~Interpreter()
{
	delete _builtins;
}

void Interpreter::run(CodeObject* codes)
{
	_frame = new FrameObject(codes);

	eval_frame();
	destroy_frame();
}

void Interpreter::eval_frame()
{
	while (_frame->has_more_codes()) {
		unsigned char op_code = _frame->get_op_code();
		bool has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

		int op_arg = -1;
		if (has_argument) {
			op_arg = _frame->get_op_arg();
		}

		DBG("run %s (%d)\n", ByteCode::lookup(op_code), op_code);
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
			_frame->locals()->put(_frame->names()->get(op_arg), POP());
			break;
		case ByteCode::LOAD_NAME:
			// LEGB scope
			v = _frame->names()->get(op_arg);
			w = _frame->locals()->get(v);
			if (w != Universe::HiNone) {
				PUSH(w);
				break;
			}
			w = _frame->globals()->get(v);
			if (w != Universe::HiNone) {
				PUSH(w);
				break;
			}
			w = _builtins->get(v);
			if (w != Universe::HiNone) {
				PUSH(w);
				break;
			}				
			PUSH(Universe::HiNone);
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
			DBG("run BINARY_ADD (%d)\n", op_code);
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
			case COMPARE::IS:
				if (v == w)
					PUSH(Universe::HiTrue);
				else
					PUSH(Universe::HiFalse);
				break;
			case COMPARE::IS_NOT:
				if (v != w)
					PUSH(Universe::HiTrue);
				else
					PUSH(Universe::HiFalse);
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
			fo->set_globals(_frame->globals());

			ArrayList<HiObject*>* args = nullptr;
			if (op_arg > 0) {
				args = new ArrayList<HiObject*>(op_arg);
				while (op_arg--) {
					args->set(op_arg, POP());
				}
			}
			fo->set_defaults(args);
			delete args;
			PUSH(fo);
			break;
		}
		case ByteCode::CALL_FUNCTION:
		{
			ArrayList<HiObject*>* args = nullptr;
			if (op_arg > 0) {
				args = new ArrayList<HiObject*>(op_arg);
				while (op_arg--) {
					args->set(op_arg, POP());
				}
			}

			build_frame(POP(), args);
			delete args;
			break;
		}
		case ByteCode::LOAD_FAST:
			PUSH(_frame->fast_locals()->get(op_arg));
			break;
		case ByteCode::STORE_FAST:
			_frame->fast_locals()->set(op_arg, POP());
			break;
		case ByteCode::LOAD_GLOBAL:
			v = _frame->names()->get(op_arg);
			w = _frame->globals()->get(v);
			if (w != Universe::HiNone) {
				PUSH(w);
				break;
			}
			w = _builtins->get(v);
			if (w != Universe::HiNone) {
				PUSH(w);
				break;
			}
			PUSH(Universe::HiNone);
			break;
		case ByteCode::LOAD_ATTR:
			v = POP();
			w = _frame->_names->get(op_arg);
			PUSH(v->getattr(w));
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

void Interpreter::build_frame(HiObject* callable, ObjList args)
{
	if (callable->klass() == NativeFunctionKlass::get_instance()) {
		PUSH(((FunctionObject*)callable)->call(args));
	}
	else if (callable->klass() == MethodKlass::get_instance()) {
		MethodObject* method = (MethodObject*)callable;
		if (!args) {
			args = new ArrayList<HiObject*>(1);
		}
		args->insert(0, method->owner());
		build_frame(method->func(), args);
	}
	else if (callable->klass() == FunctionKlass::get_instance()) {
		FrameObject* frame = new FrameObject((FunctionObject*)callable, args);
		frame->set_parent(_frame);
		_frame = frame;
	}
}