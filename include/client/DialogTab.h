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

#include "core/CoreTypes.h"

#include <QMap>
#include <QWidget>

class QListView;
class QMenu;
class QSortFilterProxyModel;
class QToolButton;

namespace tc {
namespace gui {
	class ConnectionItem;
	class GraphicsScene;
	class GraphicsView;
	class NodeItem;
} /* namespace gui */
namespace utils {
	class EditableListViewModel;
} /* namespace utils */
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

		void addConnection(const core::INodePtr & startNode, int startNodeOutput, const core::INodePtr & endNode);

		void addedConnection(const core::ConnectionPtr & connection);
		void removedConnection(const core::ConnectionPtr & connection);

	private:
		QListView * _dialogList = nullptr;
		utils::EditableListViewModel * _dialogModel = nullptr;
		QSortFilterProxyModel * _sortModel = nullptr;

		core::DialogPtr _currentDialog;

		gui::GraphicsScene * _graphicScene = nullptr;
		gui::GraphicsView * _graphicView = nullptr;

		QToolButton * _addNodesButton = nullptr;
		QMenu * _addNodesMenu = nullptr;
		
		const core::IGamePlugin* _activePlugin = nullptr;

		QMap<core::INodePtr, gui::NodeItem *> _nodeItems;
		QMap<core::ConnectionPtr, gui::ConnectionItem *> _connectionItems;

		void initGui();
		void initConnections();

		void openDialog(const QModelIndex & idx);
		void openDialog(const QString & name);
		void openDialog(const core::DialogPtr & dialog);

		void removeConnections(const core::INodePtr & node);
		void removeConnectionIfNecessary(const core::INodePtr & startNode, int startNodeOutput);
	};

} /* namespace client */
} /* namespace tc */
