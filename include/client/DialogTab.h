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
namespace nodes {
	class INode;
	typedef std::shared_ptr<INode> INodePtr;
} /* namespace nodes */
namespace nodesGui {
	class NodeItem;
} /* namespace nodesGui */
namespace plugins {
	class IGamePlugin;
} /* namespace plugins */
namespace utils {
	class Dialog;
	typedef std::shared_ptr<Dialog> DialogPtr;
} /* namespace utils */
namespace client {
namespace commands {
	class AddDialogCommand;
} /* namespace commands */

	class DialogTab final : public QWidget {
		Q_OBJECT

		friend class commands::AddDialogCommand;
		
	public:
		explicit DialogTab(QWidget * par);

		QList<utils::DialogPtr> getDialogs() const;
		void setDialogs(const QList<utils::DialogPtr> & dialogs);

		void setActivePlugin(const plugins::IGamePlugin* plugin);

	private slots:
		void addDialog();
		void addNode(const nodes::INodePtr & node);
		void removeNode(const nodes::INodePtr & node);

	private:
		QListView * _dialogList = nullptr;
		QStandardItemModel * _dialogModel = nullptr;
		QSortFilterProxyModel * _sortModel = nullptr;
		QList<utils::DialogPtr> _dialogs;

		utils::DialogPtr _currentDialog;

		QGraphicsScene * _graphicScene = nullptr;
		QGraphicsView * _graphicView = nullptr;

		QToolButton * _addNodesButton = nullptr;
		QMenu * _addNodesMenu = nullptr;
		
		const plugins::IGamePlugin* _activePlugin = nullptr;

		QMap<nodes::INodePtr, nodesGui::NodeItem *> _nodeItems;

		void initGui();
		void initConnections();

		void openDialog(const QModelIndex & idx);
		void openDialog(const QString & name);
		void openDialog(const utils::DialogPtr & dialog);
	};

} /* namespace client */
} /* namespace tc */
