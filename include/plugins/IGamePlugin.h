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

#include <QtPlugin>

namespace tc {
namespace nodes {
	class ICondition;
	class INode;
	typedef std::shared_ptr<ICondition> IConditionPtr;
	typedef std::shared_ptr<INode> INodePtr;
} /* namespace nodes */
namespace nodesGui {
	class NodeItem;
} /* namespace nodesGui */
namespace plugins {

	class IGamePlugin {
	public:
		virtual ~IGamePlugin() = default;

		/**
		 * \brief returns the name of the game this plugin supports
		 * the name will be displayed in the project selection dropdown
		 */
		virtual QString getName() const = 0;

		/**
		 * \brief returns the list of node types this game supports
		 */
		virtual QStringList getSupportedNodes() const = 0;

		/**
		 * \ brief tries to create a condition from the given condition type and json string
		 */
		virtual nodes::IConditionPtr createCondition(const QString & conditionType, const QJsonObject & json) const = 0;

		/**
		 * \ brief tries to create a node from the given node type
		 */
		virtual nodes::INodePtr createNode(const QString & nodeType) const = 0;

		/**
		 * \brief tries to create a NodeItem specialization for the given node type
		 * will automatically fall back to the generic solution provided by TakeControl itself
		 */
		virtual nodesGui::NodeItem * createNodeItem(const QString & nodeType) const = 0;
	};

} /* namespace plugins */
} /* namespace tc */

Q_DECLARE_INTERFACE(tc::plugins::IGamePlugin, "tc.game.IGamePlugin")
