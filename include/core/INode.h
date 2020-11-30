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

#include "core/CoreParameters.h"
#include "core/CoreTypes.h"

class QJsonObject;

namespace tc {
namespace core {

	class TC_CORE_API INode {
	public:
		virtual ~INode() {}

		/**
		 * \brief restores INode from json
		 * default implementation restores all properties and the ID
		 */
		virtual void read(const QJsonObject &json);

		/**
		 * \brief saves INode to json
		 * default implementation saves the type of the node retrieved via getType(), all properties and the ID
		 */
		virtual void write(QJsonObject & json) const;

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

		/**
		 * \brief sets the ID to uniquely define this node
		 * The setter is called when saving the project, so the IDs can change for each change but are persistent across save and load operations
		 */
		void setID(int id);

		/**
		 * \brief returns the ID uniquely defining this node
		 */
		int getID() const;

	protected:
		QList<IPropertyPtr> _properties;

	private:
		int _id = 0;
	};

} /* namespace core */
} /* namespace tc */
