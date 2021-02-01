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

#include <QtPlugin>

namespace tc {
namespace gui {
	class NodeItem;
	class PropertyItem;
} /* namespace gui */
namespace core {
	
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
		virtual IConditionPtr createCondition(const QString & conditionType, const QJsonObject & json) const = 0;

		/**
		 * \ brief tries to create a node from the given node type
		 */
		virtual INodePtr createNode(const QString & nodeType) const = 0;

		/**
		 * \brief tries to create a NodeItem specialization for the given node type
		 * will automatically fall back to the generic solution provided by TakeControl itself
		 */
		virtual gui::NodeItem * createNodeItem(const QString & nodeType) const = 0;

		/**
		 * \ brief tries to create a property from the given property type
		 */
		virtual IPropertyPtr createProperty(const QString & propertyType) const = 0;

		/**
		 * \brief tries to create a PropertyItem specialization for the given property type
		 */
		virtual gui::PropertyItem * createPropertyItem(const QString & propertyType) const = 0;

		/**
		 * \brief return the supported languages as QString.
		 * used e.g. for translateable texts
		 */
		virtual QStringList getSupportedLanguages() const = 0;

		/**
		 * \brief try to export the given project
		 * return true on success, false on failure
		 */
		virtual bool exportProject(const ProjectPtr & project) const = 0;

		/**
		 * \brief returns the identifier for all properties used for characters
		 */
		virtual QStringList getCharacterProperties() const = 0;
	};

} /* namespace core */
} /* namespace tc */

Q_DECLARE_INTERFACE(tc::core::IGamePlugin, "tc.game.IGamePlugin")
