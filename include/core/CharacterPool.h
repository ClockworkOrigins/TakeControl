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

#pragma once

#include <memory>

#include "core/CoreParameters.h"

#include "utils/Singleton.h"

#include <QList>
#include <QObject>

namespace tc {
namespace core {

	class Character;
	typedef std::shared_ptr<Character> CharacterPtr;

	class TC_CORE_API CharacterPool : public QObject, public utils::Singleton<CharacterPool> {
		Q_OBJECT
		
		friend class utils::Singleton<CharacterPool>;
		
	public:
		void setCharacters(const QList<CharacterPtr> & characters);
		QList<CharacterPtr> getCharacters() const;

		void addCharacter(const CharacterPtr & character);
		void removeCharacter(const CharacterPtr & character);

	signals:
		void charactersChanged();
		void characterAdded(const CharacterPtr & character);
		void characterRemoved(const CharacterPtr & character);

	private:
		QList<CharacterPtr> _characters;
	};

} /* namespace core */
} /* namespace tc */
