/** condlink_interpreter.cc ---
 *
 * Copyright (C) 2019 OpenCog Foundation
 *
 * Authors: Kiros Hailay <kiros.hailay12@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "condlink_interpreter.h"
#include <opencog/atomese/interpreter/Interpreter.h>
#include <opencog/utils/valueUtils.h>
#include <opencog/utils/value_key.h>

namespace opencog { namespace atomese {
condLink_interpreter::condLink_interpreter(const ValueSeq &seqValues_) : seqValues(seqValues_) {
    init();
}
void condLink_interpreter::init()
{

	if ( 0 == seqValues.size()) {
		throw SyntaxException(TRACE_INFO, "CondLink is expected to be arity greater-than 0!");
	}

	if(1 == seqValues.size()) {
		default_exp.push_back(seqValues[0]);
		return;
	}

	// If the conditions and expressions are flattened in even and odd
	// positions respectively.
	for(unsigned i = 0; i < seqValues.size(); ++i) {
		if(i % 2 == 0) {
			if(i == seqValues.size() - 1){
				default_exp.push_back(seqValues[i]);
				return;
			}
			conds.push_back(seqValues[i]);
		}
		else {
			exps.push_back(seqValues[i]);
		}
	}
	condlink_exec();
}
ValuePtr condLink_interpreter::condlink_exec()
{
	zip_cond _cond = std::for_each(
			boost::make_zip_iterator(
					boost::make_tuple(conds.begin(), exps.begin(), default_exp.begin())
					),
			boost::make_zip_iterator(
					boost::make_tuple(conds.end(), exps.end(), default_exp.end())
					),
			zip_cond()

			);
	ValueSeq _result = _cond._result;
	return ValuePtr(new LinkValue(_result));
}
void zip_cond::operator()(
		const boost::tuple<const ValuePtr &, const ValuePtr &, const ValuePtr &> &t) {
	if(is_contin_expr(t.get<0>()-> get_type())) {
	    Handle handle;
	    handle->setValue(moses::value_key, t.get<0>());
        atomese::Interpreter interpreter(moses::value_key);
	    ValuePtr valuePtr = interpreter(handle);
	}

	bool  v = bool_value_to_bool(t.get<0>());
	if (v) {
		_result.push_back(t.get<1>());
	} else {
		_result.push_back(t.get<2>());
	}
}
bool condlink_compare(const LinkValuePtr & p1, const LinkValuePtr& p2)
{
		ValueSeq p1_value = p1 -> value();
		ValueSeq p2_value = p2 -> value();

		std::function<bool(const ValuePtr &, const ValuePtr &)> comparator = []
				(const ValuePtr &left, const ValuePtr &right) {
			return HandleCast(left)->get_type() == HandleCast(right)->get_type();
		};

		return std::equal(p1_value.begin(), p1_value.end(), p2_value.begin(), comparator);
}
	}}
