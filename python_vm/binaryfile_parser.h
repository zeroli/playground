#pragma once
#ifndef BINARYFILE_PARSER_H_
#define BINARYFILE_PARSER_H_

#include "array_list.h"

class BufferedInputStream;
class CodeObject;
class HiString;
class HiObject;

class BinaryFileParser {
private:
	BufferedInputStream* file_stream;
	mutable ArrayList<HiString*> _string_table;

	CodeObject* get_code_object() const;

	HiString* get_byte_codes() const;
	ArrayList<HiObject*>* get_consts() const;
	ArrayList<HiObject*>* get_names() const;
	ArrayList<HiObject*>* get_var_names() const;
	ArrayList<HiObject*>* get_free_vars() const;
	ArrayList<HiObject*>* get_cell_vars() const;
	HiString* get_file_name() const;
	HiString* get_name() const;
	HiString* get_no_table() const;

	HiString* get_string() const;
	ArrayList<HiObject*>* get_tuple() const;
public:
	BinaryFileParser(BufferedInputStream* stream) : file_stream(stream) { }

	CodeObject* parse();
};

#endif  // BINARYFILE_PARSER_H_
