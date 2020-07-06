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

#include "CharacterTab.h"

#include "commands/AddCharacterCommand.h"

#include "utils/Character.h"
#include "utils/UndoStack.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

using namespace tc::client;
using namespace tc::client::commands;
using namespace tc::utils;

CharacterTab::CharacterTab(QWidget * par) : QWidget(par), _characterList(nullptr), _characterModel(nullptr) {
	QHBoxLayout * hl = new QHBoxLayout();

	{
		QVBoxLayout * vl = new QVBoxLayout();
		
		_characterList = new QListView(this);

		_characterModel = new QStandardItemModel(this);

		auto * sortModel = new QSortFilterProxyModel(this);
		sortModel->setSourceModel(_characterModel);
		
		_characterList->setModel(sortModel);

		vl->addWidget(_characterList);

		QPushButton * pb = new QPushButton(QApplication::tr("AddCharacter"), this);
		vl->addWidget(pb);

		connect(pb, &QPushButton::released, this, &CharacterTab::addCharacter);

		hl->addLayout(vl);
	}

	setLayout(hl);
}

void CharacterTab::addCharacter() {
	auto * cmd = new AddCharacterCommand(this);	
	UndoStack::instance()->push(cmd);
}
