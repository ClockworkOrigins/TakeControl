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

	class TC_CORE_API IProperty : public QObject {
		Q_OBJECT

	public:
		virtual ~IProperty() {}

		/**
		 * \brief restores INode from json
		 * default implementation restores nothing
		 */
		virtual void read(const QJsonObject &json) = 0;

		/**
		 * \brief saves INode to json
		 * default implementation saves the type of the node retrieved via getType()
		 */
		virtual void write(QJsonObject & json) const = 0;

		/**
		 * \brief returns type of this property
		 * used to uniquely identify the property
		 */
		virtual QString getType() const = 0;

	signals:
		void valueChanged();
	};
	typedef std::shared_ptr<IProperty> IPropertyPtr;

} /* namespace core */
} /* namespace tc */
