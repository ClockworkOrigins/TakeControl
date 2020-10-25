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

#include "nodes/ConditionFactory.h"

#include "plugins/IGamePlugin.h"

#include <QJsonObject>

using namespace tc;
using namespace tc::nodes;

IConditionPtr ConditionFactory::create(const QJsonObject & json) const {
	if (!json.contains("type")) return nullptr;
	
	const auto conditionType = json["type"].toString();

	// TODO: add built-in conditions

	// if no built-in condition matches, try plugin conditions

	return _activePlugin->createCondition(conditionType, json);
}

void ConditionFactory::setActivePlugin(const plugins::IGamePlugin * plugin) {
	_activePlugin = plugin;
}
