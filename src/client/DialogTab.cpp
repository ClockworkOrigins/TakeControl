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
#include "commands/AddNodeCommand.h"

#include "core/Dialog.h"
#include "core/DialogPool.h"
#include "core/IGamePlugin.h"

#include "gui/NodeItem.h"
#include "gui/NodeItemFactory.h"

#include "utils/UndoStack.h"

#include <QApplication>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QListView>
#include <QMenu>
#include <QPushButton>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QToolBar>
#include <QToolButton>

using namespace tc::client;
using namespace tc::client::commands;
using namespace tc::core;
using namespace tc::gui;
using namespace tc::utils;

DialogTab::DialogTab(QWidget * par) : QWidget(par) {
	initGui();
	initConnections();
}

void DialogTab::setActivePlugin(const IGamePlugin* plugin) {
	_activePlugin = plugin;

	_addNodesMenu->clear();

	_addNodesButton->setEnabled(false);

	if (!_activePlugin) return;

	auto supportedNodes = _activePlugin->getSupportedNodes();

	std::sort(supportedNodes.begin(), supportedNodes.end());

	for (const auto & nodeType : supportedNodes) {
		QAction * action = _addNodesMenu->addAction(nodeType);
		connect(action, &QAction::triggered, [this, nodeType]() {
			auto * cmd = new AddNodeCommand(_currentDialog, nodeType);

			connect(cmd, &AddNodeCommand::addedNode, this, &DialogTab::addNode);
			connect(cmd, &AddNodeCommand::removedNode, this, &DialogTab::removeNode);

			UndoStack::instance()->push(cmd);
		});
	}

	_addNodesButton->setEnabled(!supportedNodes.isEmpty() && _currentDialog);
}

void DialogTab::addDialog() {
	auto * cmd = new AddDialogCommand();
	UndoStack::instance()->push(cmd);
}

void DialogTab::addNode(const INodePtr & node) {
	auto * nodeItem = NodeItemFactory::instance()->create(node);
	_graphicScene->addItem(nodeItem);

	_nodeItems.insert(node, nodeItem);
}

void DialogTab::removeNode(const INodePtr & node) {
	const auto it = _nodeItems.find(node);

	if (it == _nodeItems.end()) return;

	delete it.value();

	_nodeItems.erase(it);
}

void DialogTab::updateDialogs() {
	_dialogModel->clear();

	for (const auto & d : DialogPool::instance()->getDialogs()) {
		_dialogModel->appendRow(new QStandardItem(d->getName()));
	}
}

void DialogTab::addedDialog(const DialogPtr & dialog) {
	_dialogModel->appendRow(new QStandardItem(dialog->getName()));
}

void DialogTab::removedDialog(const DialogPtr & dialog) {
	const auto itemList = _dialogModel->findItems(dialog->getName());

	for (const auto & item : itemList) {
		const auto idx = _dialogModel->indexFromItem(item);
		_dialogModel->removeRows(idx.row(), 1);
	}
}

void DialogTab::initGui() {
	auto * hl = new QHBoxLayout();

	{
		auto * vl = new QVBoxLayout();

		_dialogList = new QListView(this);
		_dialogList->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

	{
		auto * vl = new QVBoxLayout();

		auto * tb = new QToolBar(this);
		vl->addWidget(tb);

		{
			_addNodesButton = new QToolButton(tb);
			const QIcon icon(":/svg/add.svg");
			Q_ASSERT(!icon.isNull());
			_addNodesButton->setIcon(icon);

			_addNodesMenu = new QMenu(_addNodesButton);
			
			_addNodesButton->setMenu(_addNodesMenu);
			_addNodesButton->setPopupMode(QToolButton::InstantPopup);

			_addNodesButton->setEnabled(false);

			tb->addWidget(_addNodesButton);
		}
		
		_graphicScene = new QGraphicsScene(this);
		_graphicScene->setBackgroundBrush(QBrush(QColor(32, 32, 32)));

		_graphicView = new QGraphicsView(_graphicScene);
		_graphicView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

		vl->addWidget(_graphicView, 1);

		hl->addLayout(vl);
	}

	setLayout(hl);
}

void DialogTab::initConnections() {
	connect(_dialogList, &QListView::doubleClicked, this, QOverload<const QModelIndex &>::of(&DialogTab::openDialog));

	connect(DialogPool::instance(), &DialogPool::dialogsChanged, this, &DialogTab::updateDialogs);
	connect(DialogPool::instance(), &DialogPool::dialogAdded, this, &DialogTab::addedDialog);
	connect(DialogPool::instance(), &DialogPool::dialogRemoved, this, &DialogTab::removedDialog);
}

void DialogTab::openDialog(const QModelIndex & idx) {
	Q_ASSERT(idx.model() == _sortModel);

	const auto sourceIdx = _sortModel->mapToSource(idx);

	const int row = sourceIdx.row();

	const auto dialogs = DialogPool::instance()->getDialogs();
	
	Q_ASSERT(row < dialogs.count());

	if (row >= dialogs.count()) return;

	openDialog(dialogs[row]);
}

void DialogTab::openDialog(const QString & name) {
	const auto dialogs = DialogPool::instance()->getDialogs();
	
	const auto it = std::find_if(dialogs.begin(), dialogs.end(), [name](const DialogPtr& d) {
		return name == d->getName();
	});

	Q_ASSERT(it != dialogs.end());

	if (it == dialogs.end()) return;

	openDialog(*it);
}

void DialogTab::openDialog(const DialogPtr & dialog) {
	if (_currentDialog == dialog) return;
	
	_currentDialog = dialog;

	_addNodesButton->setEnabled(_activePlugin && !_activePlugin->getSupportedNodes().isEmpty() && _currentDialog);

	while (!_nodeItems.isEmpty()) {
		removeNode(_nodeItems.firstKey());
	}

	for (const auto & node : _currentDialog->getNodes()) {
		addNode(node);
	}

	// TODO: add connections

	// TODO: restore layout
}
