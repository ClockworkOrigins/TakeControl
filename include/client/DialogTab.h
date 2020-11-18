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

#include <QMap>
#include <QWidget>

class QGraphicsScene;
class QGraphicsView;
class QListView;
class QMenu;
class QSortFilterProxyModel;
class QStandardItemModel;
class QToolButton;

namespace tc {
namespace core {
	class Dialog;
	typedef std::shared_ptr<Dialog> DialogPtr;
	
	class IGamePlugin;
	
	class INode;
	typedef std::shared_ptr<INode> INodePtr;
} /* namespace core */
namespace gui {
	class NodeItem;
} /* namespace gui */
namespace client {

	class DialogTab final : public QWidget {
		Q_OBJECT

	public:
		explicit DialogTab(QWidget * par);

		void setActivePlugin(const core::IGamePlugin* plugin);

	private slots:
		void addDialog();
		void addNode(const core::INodePtr & node);
		void removeNode(const core::INodePtr & node);
		
		void updateDialogs();

		void addedDialog(const core::DialogPtr & dialog);
		void removedDialog(const core::DialogPtr & dialog);

	private:
		QListView * _dialogList = nullptr;
		QStandardItemModel * _dialogModel = nullptr;
		QSortFilterProxyModel * _sortModel = nullptr;

		core::DialogPtr _currentDialog;

		QGraphicsScene * _graphicScene = nullptr;
		QGraphicsView * _graphicView = nullptr;

		QToolButton * _addNodesButton = nullptr;
		QMenu * _addNodesMenu = nullptr;
		
		const core::IGamePlugin* _activePlugin = nullptr;

		QMap<core::INodePtr, gui::NodeItem *> _nodeItems;

		void initGui();
		void initConnections();

		void openDialog(const QModelIndex & idx);
		void openDialog(const QString & name);
		void openDialog(const core::DialogPtr & dialog);
	};

} /* namespace client */
} /* namespace tc */
