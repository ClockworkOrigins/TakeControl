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

#include "Project.h"

#include "Character.h"
#include "Dialog.h"

#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using namespace tc::core;

Project::Project(const QString & path, const QString & name, const QString & type) : _path(path), _name(name), _type(type) {}

bool Project::supports(const QString & path) {
	if (!QFileInfo::exists(path)) return false;

	if (QFileInfo(path).suffix() != "json") return false;
	
	QFile f(path);

	if (!f.open(QIODevice::ReadOnly)) return false;

	const auto data = f.readAll();
	
	const QJsonDocument doc = QJsonDocument::fromJson(data);

	const auto json = doc.object();
	
	return json.contains("Type") && json.contains("Name");
}

void Project::save(const QList<CharacterPtr> & characters, const QList<DialogPtr> & dialogs) const {
	QFile f(QString("%1/%2.json").arg(_path).arg(_name));

	if (!f.open(QIODevice::WriteOnly)) return;

	QJsonObject json;
	json["Type"] = _type;
	json["Name"] = _name;

	QJsonArray characterArray;

	for (const auto & c : characters) {
		const auto characterJson = c->save();
		characterArray.append(characterJson);
	}

	json["Characters"] = characterArray;
	
	QJsonArray dialogArray;

	for (const auto & d : dialogs) {
		const auto dialogJson = d->save();
		dialogArray.append(dialogJson);
	}

	json["Dialogs"] = dialogArray;

	const QJsonDocument doc(json);
	const auto data = doc.toJson();
	
	f.write(data);
}

void Project::load(const QString & path, QList<CharacterPtr> & characters, QList<DialogPtr> & dialogs) {
	const QFileInfo fi(path);

	_path = fi.absolutePath();

	QFile f(path);

	if (!f.open(QIODevice::ReadOnly)) return;

	const auto data = f.readAll();
	
	const QJsonDocument doc = QJsonDocument::fromJson(data);

	const auto json = doc.object();

	_name = json["Name"].toString();
	_type = json["Type"].toString();

	QJsonArray characterArray = json["Characters"].toArray();

	for (const auto characterJson : characterArray) {
		auto c = Character::load(characterJson.toObject());

		if (!c) continue;

		characters.append(c);
	}

	QJsonArray dialogArray = json["Dialogs"].toArray();

	for (const auto dialogJson : dialogArray) {
		auto d = Dialog::load(dialogJson.toObject());

		if (!d) continue;

		dialogs.append(d);
	}
}

QString Project::getName() const {
	return _name;
}

QString Project::getType() const {
	return _type;
}
