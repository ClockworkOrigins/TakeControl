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

#include "core/CoreParameters.h"

class QJsonObject;

namespace tc {
namespace core {

	class IProperty;
	typedef std::shared_ptr<IProperty> IPropertyPtr;

	class TC_CORE_API INode {
	public:
		virtual ~INode() {}

		/**
		 * \brief restores INode from json
		 * default implementation restores all properties
		 */
		virtual void read(const QJsonObject &json) = 0;

		/**
		 * \brief saves INode to json
		 * default implementation saves the type of the node retrieved via getType() and all properties
		 */
		virtual void write(QJsonObject & json) const = 0;

		/**
		 * \brief specifies how many inputs this node accepts
		 * default is -1 which means there is no limit on inputs
		 */
		virtual qint32 getInputCount() const;

		/**
		 * \brief specifies how many outputs this node accepts
		 * default is 1 which means this node can be connected to just on other node
		 */
		virtual qint32 getOutputCount() const;

		/**
		 * \brief specifies the labels shown for the output branches
		 * default implementation always returns an empty string as for just one output no label is necessary
		 */
		virtual QString getOutputLabel(qint32 branch) const;

		/**
		 * \brief returns type of this node
		 * used to uniquely identify the node
		 */
		virtual QString getType() const = 0;

		/**
		 * \brief returns the list of properties this node owns
		 */
		QList<IPropertyPtr> getProperties() const;

	protected:
		QList<IPropertyPtr> _properties;
	};
	typedef std::shared_ptr<INode> INodePtr;

} /* namespace core */
} /* namespace tc */
