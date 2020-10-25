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

#include "nodes/implementations/ConditionNode.h"

#include "nodes/ConditionFactory.h"
#include "nodes/interfaces/ICondition.h"

#include <QJsonArray>
#include <QJsonObject>

using namespace tc;
using namespace tc::nodes;

ConditionNode::ConditionNode() : INode() {}

void ConditionNode::read(const QJsonObject & json) {
	auto it = json.find("conditions");
	if (it != json.end()) {
		const auto c = it->toArray();
		for (auto conditionEntry : c) {
			const auto conditionObject = conditionEntry.toObject();

			if (conditionObject.isEmpty()) continue;

			if (!conditionObject.contains("type")) continue;

			const auto conditionType = conditionObject["type"].toString();

			IConditionPtr condition = ConditionFactory::instance()->create(conditionObject);

			if (!condition) continue;
			
			_conditions << condition;
		}
	}
}

void ConditionNode::write(QJsonObject & json) const {
	INode::write(json);

	QJsonArray conditionsArray;
	for (const auto & condition : _conditions) {
		QJsonObject c;
		condition->write(c);
		conditionsArray.append(c);
	}
	json["conditions"] = conditionsArray;
}

void ConditionNode::addCondition(const IConditionPtr & condition) {
	_conditions << condition;
}

void ConditionNode::removeCondition(int index) {
	if (index < 0 || index >= _conditions.length()) return;
	
	_conditions.removeAt(index);
}

QList<IConditionPtr> ConditionNode::getConditions() const {
	return _conditions;
}

qint32 ConditionNode::getOutputCount() const {
	return 2;
}

QString ConditionNode::getOutputLabel(qint32 branch) const {
	return branch == 0 ? "True" : "False";
}
