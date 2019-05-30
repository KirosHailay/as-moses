/** condlink_interpreter.h ---
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

#ifndef ASMOSES_CONDLINK_INTERPRETER_H
#define ASMOSES_CONDLINK_INTERPRETER_H

#include <opencog/atoms/base/Handle.h>
#include <opencog/atoms/value/LinkValue.h>
#include <opencog/utils/valueUtils.h>
#include <boost/iterator/zip_iterator.hpp>

namespace opencog { namespace atomese {
/**
 *  Performs condLink interpreter
 * has constructor that accepts sequences of values
 * a void initilizer method that initilizes the values of conditions, experssions, and default values
 * and the condlink_exec method that returns the ValuePtr of the condlink experssion
 */
struct condLink_interpreter
{
public:
    /*this constructor accepts a value of sequence from
     * */
	condLink_interpreter(const ValueSeq& valueSeq);
	void init();
	ValuePtr condlink_exec();
private:
	ValueSeq conds;
	ValueSeq exps;
	ValueSeq default_exp;
	ValueSeq seqValues;
};
/**
 * this sturct is expected to be used in boost::zip_iterator to perform
 * condlink on ValuePtr
 * and it has method operator overloading that takes three ValuePtr which are the conditions, experssions, and defaults
 *
 */
struct zip_cond :
			public std::unary_function<const boost::tuple
					<const ValuePtr &, const ValuePtr &, const ValuePtr &> &, void> {
		ValueSeq _result;

		void operator()(
				const boost::tuple<const ValuePtr &, const ValuePtr &, const ValuePtr &> &t);
};
/**
 * Compare content of two link_values
 * @param p1 LinkValuePtr&  p1
 * @param p2 LinkValuePtr&  p2
 * @return                  boolean of the comparision
 */
bool condlink_compare(const LinkValuePtr &p1, const LinkValuePtr &p2);
}}
#endif //ASMOSES_CONDLINK_INTERPRETER_H
