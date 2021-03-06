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

#include "ConditionFactory.h"

#include "IGamePlugin.h"

#include <QJsonObject>

using namespace tc::core;

IConditionPtr ConditionFactory::create(const QJsonObject & json) const {
	if (!json.contains("type")) return nullptr;
	
	const auto conditionType = json["type"].toString();

    IConditionPtr condition;
	
	// TODO: add built-in conditions

	// if no built-in condition matches, try plugin conditions

	if (!condition && _activePlugin) {
		condition = _activePlugin->createCondition(conditionType, json);
	}

	return condition;
}

void ConditionFactory::setActivePlugin(const IGamePlugin * plugin) {
	_activePlugin = plugin;
}
