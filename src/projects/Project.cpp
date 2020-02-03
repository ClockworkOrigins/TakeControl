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

#include "projects/Project.h"

using namespace tc::projects;

Project::Project(const QString & path, const QString & name, const QString & type) : _path(path), _name(name), _type(type) {
}

bool Project::supports(const QString & path) {
	// TODO: open file and check if it can be parsed and is a project file
	return false;
}

void Project::save() {
	// TODO
}

void Project::load() {
	// TODO
}

QString Project::getName() const {
	return _name;
}
