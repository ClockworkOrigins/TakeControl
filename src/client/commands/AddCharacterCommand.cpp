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

#include "commands/AddCharacterCommand.h"

#include <cassert>

#include "CharacterTab.h"

#include "utils/Character.h"

#include <QApplication>
#include <QStandardItemModel>

using namespace tc::client;
using namespace tc::client::commands;
using namespace tc::utils;

AddCharacterCommand::AddCharacterCommand(CharacterTab * characterTab) : QUndoCommand(QApplication::tr("AddCharacter")), _characterTab(characterTab) {
	int number = 1;

	while (std::find_if(_characterTab->_characters.begin(), _characterTab->_characters.end(), [number](const std::shared_ptr<Character> & c) { return c->getName() == QString("New Character %1").arg(number); }) != _characterTab->_characters.end()) {
		number++;
	}
	
	_character = std::make_shared<Character>(QString("New Character %1").arg(number));
}

void AddCharacterCommand::redo() {
	_characterTab->_characters.append(_character);

	_characterTab->_characterModel->appendRow(new QStandardItem(_character->getName()));
}

void AddCharacterCommand::undo() {
	const int idx = _characterTab->_characters.indexOf(_character);

	assert(idx == _characterTab->_characters.size() - 1);

	_characterTab->_characterModel->removeRows(idx, 1);

	_characterTab->_characters.pop_back();
}
