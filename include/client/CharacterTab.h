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

#include <QWidget>

class QListView;
class QStandardItemModel;

namespace tc {
namespace utils {
	class Character;
	typedef std::shared_ptr<Character> CharacterPtr;
} /* namespace utils */
namespace client {
namespace commands {
	class AddCharacterCommand;
} /* namespace commands */

	class CharacterTab : public QWidget {
		Q_OBJECT

		friend class commands::AddCharacterCommand;
		
	public:
		explicit CharacterTab(QWidget * par);

	private slots:
		void updateCharacters();
	
		void addCharacter();

		void addedCharacter(const utils::CharacterPtr & character);
		void removedCharacter(const utils::CharacterPtr & character);

	private:
		QListView * _characterList;
		QStandardItemModel * _characterModel;
	};

} /* namespace client */
} /* namespace tc */
