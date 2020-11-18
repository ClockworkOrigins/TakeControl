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
#include "utils/CharacterPool.h"
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
	auto * hl = new QHBoxLayout();

	{
		auto * vl = new QVBoxLayout();
		
		_characterList = new QListView(this);
		_characterList->setEditTriggers(QAbstractItemView::NoEditTriggers);

		_characterModel = new QStandardItemModel(this);

		auto * sortModel = new QSortFilterProxyModel(this);
		sortModel->setSourceModel(_characterModel);
		
		_characterList->setModel(sortModel);

		vl->addWidget(_characterList);

		auto * pb = new QPushButton(QApplication::tr("AddCharacter"), this);
		vl->addWidget(pb);

		connect(pb, &QPushButton::released, this, &CharacterTab::addCharacter);

		hl->addLayout(vl);
	}

	setLayout(hl);

	connect(CharacterPool::instance(), &CharacterPool::charactersChanged, this, &CharacterTab::updateCharacters);
	connect(CharacterPool::instance(), &CharacterPool::characterAdded, this, &CharacterTab::addedCharacter);
	connect(CharacterPool::instance(), &CharacterPool::characterRemoved, this, &CharacterTab::removedCharacter);
}

void CharacterTab::updateCharacters() {
	_characterModel->clear();
	
	for (const auto & c : CharacterPool::instance()->getCharacters()) {
		_characterModel->appendRow(new QStandardItem(c->getName()));
	}
}

void CharacterTab::addCharacter() {
	auto * cmd = new AddCharacterCommand();	
	UndoStack::instance()->push(cmd);
}

void CharacterTab::addedCharacter(const CharacterPtr & character) {
	_characterModel->appendRow(new QStandardItem(character->getName()));
}

void CharacterTab::removedCharacter(const CharacterPtr & character) {
	const auto itemList = _characterModel->findItems(character->getName());

	for (const auto & item : itemList) {
		const auto idx = _characterModel->indexFromItem(item);
		_characterModel->removeRows(idx.row(), 1);
	}
}
