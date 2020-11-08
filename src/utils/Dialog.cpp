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

#include "Dialog.h"

using namespace tc::utils;

Dialog::Dialog(const QString & name) : _name(name) {}

QString Dialog::getName() const {
	return _name;
}

QJsonObject Dialog::save() const {
	QJsonObject json;
	json["Name"] = _name;

	return json;
}

DialogPtr Dialog::load(const QJsonObject & json) {
	if (!json.contains("Name")) return nullptr;
	
	QString name = json["Name"].toString();
	
	auto c = std::make_shared<Dialog>(name);

	return c;
}
