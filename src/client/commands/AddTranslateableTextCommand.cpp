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

#include "commands/AddTranslateableTextCommand.h"

#include "core/TranslateableText.h"
#include "core/TranslateableTextPool.h"

#include <QApplication>
#include <QStandardItemModel>

using namespace tc::client;
using namespace tc::client::commands;
using namespace tc::core;

AddTranslateableTextCommand::AddTranslateableTextCommand() : QUndoCommand(QApplication::tr("AddText")) {
	int number = 1;

	const auto translateableTexts = TranslateableTextPool::instance()->getTranslateableTexts();
	
	while (std::find_if(translateableTexts.begin(), translateableTexts.end(), [number](const std::shared_ptr<TranslateableText> & c) { return c->getKey() == QString("New TranslateableText %1").arg(number); }) != translateableTexts.end()) {
		number++;
	}
	
	_translateableText = std::make_shared<TranslateableText>(QString("New TranslateableText %1").arg(number));
}

void AddTranslateableTextCommand::redo() {
	TranslateableTextPool::instance()->addTranslateableText(_translateableText);
}

void AddTranslateableTextCommand::undo() {
	TranslateableTextPool::instance()->removeTranslateableText(_translateableText);
}
