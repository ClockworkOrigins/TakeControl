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

#include "DialogTab.h"

#include "commands/AddDialogCommand.h"

#include "utils/Dialog.h"
#include "utils/UndoStack.h"

#include <QApplication>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

using namespace tc::client;
using namespace tc::client::commands;
using namespace tc::utils;

DialogTab::DialogTab(QWidget * par) : QWidget(par), _dialogList(nullptr), _dialogModel(nullptr) {
	QHBoxLayout * hl = new QHBoxLayout();

	{
		QVBoxLayout * vl = new QVBoxLayout();

		_dialogList = new QListView(this);

		_dialogModel = new QStandardItemModel(this);

		auto * sortModel = new QSortFilterProxyModel(this);
		sortModel->setSourceModel(_dialogModel);
		
		_dialogList->setModel(sortModel);

		vl->addWidget(_dialogList);

		QPushButton * pb = new QPushButton(QApplication::tr("AddDialog"), this);
		vl->addWidget(pb);

		connect(pb, &QPushButton::released, this, &DialogTab::addDialog);

		hl->addLayout(vl);
	}

	_graphicScene = new QGraphicsScene(this);
	
	_graphicView = new QGraphicsView(_graphicScene);

	hl->addWidget(_graphicView, 1);

	setLayout(hl);
}

QList<std::shared_ptr<Dialog>> DialogTab::getDialogs() const {
	return _dialogs;
}

void DialogTab::setDialog(const QList<std::shared_ptr<Dialog>> & dialogs) {
	_dialogs = dialogs;
	_dialogModel->clear();
	
	for (const auto & d : dialogs) {
		_dialogModel->appendRow(new QStandardItem(d->getName()));
	}
}

void DialogTab::addDialog() {
	auto * cmd = new AddDialogCommand(this);	
	UndoStack::instance()->push(cmd);
}
