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
} /* namespace utils */
namespace client {
namespace commands {
	class AddCharacterCommand;
} /* namespace commands */

	class CharacterTab : public QWidget {
		Q_OBJECT

		friend class commands::AddCharacterCommand;
		
	public:
		CharacterTab(QWidget * par);

		QList<std::shared_ptr<utils::Character>> getCharacters() const;

	private slots:
		void addCharacter();

	private:
		QListView * _characterList;
		QStandardItemModel * _characterModel;
		QList<std::shared_ptr<utils::Character>> _characters;
	};

} /* namespace client */
} /* namespace tc */
