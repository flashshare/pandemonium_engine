#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

/*************************************************************************/
/*  query_result.h                                                       */
/*************************************************************************/
/*                         This file is part of:                         */
/*                          PANDEMONIUM ENGINE                           */
/*             https://github.com/Relintai/pandemonium_engine            */
/*************************************************************************/
/* Copyright (c) 2022-present Péter Magyar.                              */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "core/string/ustring.h"

#include "core/object/reference.h"

class QueryResult : public Reference {
	GDCLASS(QueryResult, Reference);

public:
	virtual bool next_row();
	virtual int get_stored_row_count();

	virtual String get_cell(const int index);
	virtual bool get_cell_bool(const int index);
	virtual int get_cell_int(const int index);
	virtual float get_cell_float(const int index);
	virtual double get_cell_double(const int index);

	virtual bool is_cell_null(const int index);
	virtual int get_cell_count();

	int get_current_cell_index() const;
	void set_current_cell_index(const int p_index);

	String get_next_cell();
	bool get_next_cell_bool();
	int get_next_cell_int();
	float get_next_cell_float();
	double get_next_cell_double();
	bool is_next_cell_null();

	virtual int get_last_insert_rowid();

	virtual String get_error_message();

	QueryResult();
	virtual ~QueryResult();

protected:
	static void _bind_methods();

	int _current_cell_index;
};

#endif
