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

#include "core/Character.h"
#include "core/CharacterPool.h"

#include <QApplication>
#include <QStandardItemModel>

using namespace tc::client;
using namespace tc::client::commands;
using namespace tc::core;

AddCharacterCommand::AddCharacterCommand(const IGamePlugin * plugin) : QUndoCommand(QApplication::tr("AddCharacter")) {
	int number = 1;

	const auto characters = CharacterPool::instance()->getCharacters();
	
	while (std::find_if(characters.begin(), characters.end(), [number](const std::shared_ptr<Character> & c) { return c->getIdentifier() == QString("New Character %1").arg(number); }) != characters.end()) {
		number++;
	}
	
	_character = std::make_shared<Character>(QString("New Character %1").arg(number), plugin);
}

void AddCharacterCommand::redo() {
	CharacterPool::instance()->addCharacter(_character);
}

void AddCharacterCommand::undo() {
	CharacterPool::instance()->removeCharacter(_character);
}
