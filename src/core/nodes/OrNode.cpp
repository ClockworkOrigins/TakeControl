/*
	This file is part of TakeControl.

    TakeControl is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TakeControl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TakeControl.  If not, see <http://www.gnu.org/licenses/>.
 */
// Copyright 2020 Clockwork Origins

#include "nodes/OrNode.h"

#include "PropertyFactory.h"

using namespace tc::core;

OrNode::OrNode() : ConditionNode() {}

void OrNode::read(const QJsonObject & json) {	
	ConditionNode::read(json);
}

void OrNode::write(QJsonObject & json) const {
	ConditionNode::write(json);
}

QString OrNode::getType() const {
	return "Or";
}
