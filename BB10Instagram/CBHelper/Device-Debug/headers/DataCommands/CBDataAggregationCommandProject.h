/* Copyright (C) 2012 cloudbase.io

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
*/
#include <vector>
#include "CBDataAggregationCommand.h"

namespace Cloudbase {

#ifndef CBHELPERDATACOMMANDPROJECT_H
#define CBHELPERDATACOMMANDPROJECT_H

/**
 * The project aggregation command filters the number of fields selected
 * from a document.
 * You can either populate the <strong>includeFields</strong> property
 * to exclude all fields and only include the ones selected or use
 * the <strong>excludeFields</strong> to set up an exclusion list.
 */
class CBDataAggregationCommandProject : public CBDataAggregationCommand {
public:
	std::vector<std::string> includeFields;
	std::vector<std::string> excludeFields;

	CBDataAggregationCommandProject();
	virtual ~CBDataAggregationCommandProject();

	std::string serializeAggregateConditions();
};

#endif

}
