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

DialogTab::DialogTab(QWidget * par) : QWidget(par) {
	initGui();
	initConnections();
}

QList<DialogPtr> DialogTab::getDialogs() const {
	return _dialogs;
}

void DialogTab::setDialog(const QList<DialogPtr> & dialogs) {
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

void DialogTab::initGui() {
	auto * hl = new QHBoxLayout();

	{
		auto * vl = new QVBoxLayout();

		_dialogList = new QListView(this);

		_dialogModel = new QStandardItemModel(this);

		_sortModel = new QSortFilterProxyModel(this);
		_sortModel->setSourceModel(_dialogModel);

		_dialogList->setModel(_sortModel);

		vl->addWidget(_dialogList);

		auto * pb = new QPushButton(QApplication::tr("AddDialog"), this);
		vl->addWidget(pb);

		connect(pb, &QPushButton::released, this, &DialogTab::addDialog);

		hl->addLayout(vl);
	}

	_graphicScene = new QGraphicsScene(this);

	_graphicView = new QGraphicsView(_graphicScene);

	hl->addWidget(_graphicView, 1);

	setLayout(hl);
}

void DialogTab::initConnections() {
	connect(_dialogList, &QListView::doubleClicked, this, QOverload<const QModelIndex &>::of(&DialogTab::openDialog));
}

void DialogTab::openDialog(const QModelIndex & idx) {
	Q_ASSERT(idx.model() == _sortModel);

	const auto sourceIdx = _sortModel->mapToSource(idx);

	const int row = sourceIdx.row();
	
	Q_ASSERT(row < _dialogs.count());

	if (row >= _dialogs.count()) return;

	openDialog(_dialogs[row]);
}

void DialogTab::openDialog(const QString & name) {
	const auto it = std::find_if(_dialogs.begin(), _dialogs.end(), [name](const DialogPtr& d) {
		return name == d->getName();
	});

	Q_ASSERT(it != _dialogs.end());

	if (it == _dialogs.end()) return;

	openDialog(*it);
}

void DialogTab::openDialog(const DialogPtr & dialog) {
	if (_currentDialog == dialog) return;
	
	_currentDialog = dialog;

	// TODO: add nodes

	// TODO: add connections

	// TODO: restore layout
}
