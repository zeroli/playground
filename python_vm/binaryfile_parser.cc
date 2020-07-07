#include "binaryfile_parser.h"

#include <iostream>
#include <cassert>
#include <string>

#include "code_object.h"
#include "hi_integer.h"
#include "hi_string.h"
#include "buffered_input_stream.h"

using namespace std;

CodeObject* BinaryFileParser::get_code_object() const
{
	std::cout << "parse code object...\n";
	int argcount = file_stream->read_int();
	std::cout << "argcount: " << argcount << std::endl;
	int nlocals = file_stream->read_int();
	std::cout << "nlocals: " << nlocals << std::endl;
	int stacksize = file_stream->read_int();
	std::cout << "stacksize: " << stacksize << std::endl;
	int flags = file_stream->read_int();
	std::cout << "flags: " << flags << std::endl;

	HiString* bytecodes = get_byte_codes();
	ArrayList<HiObject*>* consts = get_consts();
	ArrayList<HiObject*>* names = get_names();
	ArrayList<HiObject*>* var_names = get_var_names();
	ArrayList<HiObject*>* free_vars = get_free_vars();
	ArrayList<HiObject*>* cell_vars = get_cell_vars();
	HiString* file_name = get_file_name();
	HiString* module_name = get_name();
	int begin_line_no = file_stream->read_int();
	HiString* lnotab = get_no_table();

	std::cout << "filename: " << std::string(file_name->value(), file_name->length()) << std::endl;
	std::cout << "module name: " << std::string(module_name->value(), module_name->length()) << std::endl;
	std::cout << "begin_lin_no: " << begin_line_no << std::endl;

	return new CodeObject(argcount, nlocals, stacksize, flags, bytecodes,
		consts, names, var_names, free_vars, cell_vars, file_name, module_name,
		begin_line_no, lnotab);
}

HiString* BinaryFileParser::get_byte_codes() const
{
	assert(file_stream->read() == 's');
	return get_string();
}

ArrayList<HiObject*>* BinaryFileParser::get_consts() const
{
	if (file_stream->read() == '(') {
		return get_tuple();
	}
	file_stream->unread();
	return NULL;
}

// variable names of arguments for function/method
ArrayList<HiObject*>* BinaryFileParser::get_var_names() const
{
	if (file_stream->read() == '(') {
		return get_tuple();
	}
	file_stream->unread();
	return NULL;
}

ArrayList<HiObject*>* BinaryFileParser::get_free_vars() const
{
	if (file_stream->read() == '(') {
		return get_tuple();
	}
	file_stream->unread();
	return NULL;
}

ArrayList<HiObject*>* BinaryFileParser::get_cell_vars() const
{
	if (file_stream->read() == '(') {
		return get_tuple();
	}
	file_stream->unread();
	return NULL;
}

HiString* BinaryFileParser::get_file_name() const
{
	assert(file_stream->read() == 's');
	return get_string();
}

// module name this code belongs to
HiString* BinaryFileParser::get_name() const
{
	assert(file_stream->read() == 't');
	return get_string();
}

// line number table, string
HiString* BinaryFileParser::get_no_table() const
{
	assert(file_stream->read() == 't');
	return get_string();
}

HiString* BinaryFileParser::get_string() const
{
	int length = file_stream->read_int();
	char* str_value = new char[length];
	for (int i = 0; i < length; i++) {
		str_value[i] = file_stream->read();
	}

	HiString* s = new HiString(str_value, length);
	delete[] str_value;

	return s;
}

ArrayList<HiObject*>* BinaryFileParser::get_tuple() const
{
	int length = file_stream->read_int();
	HiString* str;
	
	ArrayList<HiObject*>* list = new ArrayList<HiObject*>(length);
	for (int i = 0; i < length; i++) {
		char obj_type = file_stream->read();

		switch (obj_type) {
		case 'c':
			std::cout << "got a code object" << std::endl;
			list->add(get_code_object());
			break;
		case 'i':
			list->add(new HiInteger(file_stream->read_int()));
			break;
		case 'N':
			list->add(NULL);
			break;
		case 't':
			str = get_string();
			list->add(str);
			_string_table.add(str);
			break;
		case 's':
			list->add(get_string());
			break;
		case 'R':
			list->add(_string_table.get(file_stream->read_int()));
			break;
		default:
			assert(0);
		}
	}
	return list;
}

ArrayList<HiObject*>* BinaryFileParser::get_names() const
{
	// similar to get_consts list
	if (file_stream->read() == '(') {
		return get_tuple();
	}
	file_stream->unread();
	return NULL;
}


CodeObject* BinaryFileParser::parse()
{
	int magic_number = file_stream->read_int();
	printf("magic number is 0x%x\n", magic_number);

	int moddate = file_stream->read_int();
	printf("moddate is 0x%x\n", moddate);

	char object_type = file_stream->read();
	if (object_type == 'c') {
		CodeObject* result = get_code_object();
		printf("parser ok!\n");
		return result;
	}
	return NULL;
}