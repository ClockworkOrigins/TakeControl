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

#include "CharacterPool.h"

#include "Character.h"

using namespace tc::core;

void CharacterPool::setCharacters(const QList<CharacterPtr> & characters) {
    _characters = characters;

    emit charactersChanged();
}

QList<CharacterPtr> CharacterPool::getCharacters() const {
    return _characters;
}

void CharacterPool::addCharacter(const CharacterPtr & character) {
    _characters << character;

    emit characterAdded(character);
}

void CharacterPool::removeCharacter(const CharacterPtr & character) {
    _characters.removeAll(character);

    emit characterRemoved(character);
}

void CharacterPool::changeIdentifier(const QString & before, const QString & after) {
    const auto it = std::find_if(_characters.begin(), _characters.end(), [before](const CharacterPtr & c) {
        return c->getName() == before;
      });

    Q_ASSERT(it != _characters.end());

    if (it == _characters.end()) return;

    (*it)->setName(after);
}
