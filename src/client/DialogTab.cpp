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

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QListView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

using namespace tc::client;

DialogTab::DialogTab(QWidget * par) : QWidget(par), _dialogList(nullptr), _dialogModel(nullptr) {
	QHBoxLayout * hl = new QHBoxLayout();

	_dialogList = new QListView(this);

	_dialogModel = new QStandardItemModel(this);

	auto * sortModel = new QSortFilterProxyModel(this);
	sortModel->setSourceModel(_dialogModel);
	
	_dialogList->setModel(sortModel);

	hl->addWidget(_dialogList);

	_graphicScene = new QGraphicsScene(this);
	
	_graphicView = new QGraphicsView(_graphicScene);

	hl->addWidget(_graphicView, 1);

	setLayout(hl);
}
