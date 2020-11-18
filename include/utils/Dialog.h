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

#include "utils/utilsParameters.h"

#include <QJsonObject>
#include <QList>
#include <QString>

namespace tc {
namespace nodes {
	class INode;
	typedef std::shared_ptr<INode> INodePtr;
} /* namespace nodes */
namespace utils {

	class Dialog;
	typedef std::shared_ptr<Dialog> DialogPtr;

	class TC_UTILS_API Dialog {
	public:
		explicit Dialog(const QString & name);

		QString getName() const;

		QJsonObject save() const;

		static DialogPtr load(const QJsonObject & json);

		void addNode(const nodes::INodePtr & node);
		void removeNode(const nodes::INodePtr & node);

		QList<nodes::INodePtr> getNodes() const;

	private:
		QString _name;
		QList<nodes::INodePtr> _nodes;
	};

} /* namespace utils */
} /* namespace tc */
