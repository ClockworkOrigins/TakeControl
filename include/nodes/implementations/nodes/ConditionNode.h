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

#include <cstdint>

#include "nodesParameters.h"
#include "interfaces/INode.h"

class QJsonObject;

namespace tc {
namespace nodes {

	class ICondition;
	typedef std::shared_ptr<ICondition> IConditionPtr;

	class TC_NODES_API ConditionNode : public INode {
	public:
		ConditionNode();
		
		void read(const QJsonObject &json) override;
		void write(QJsonObject & json) const override;

		void addCondition(const IConditionPtr & condition);
		void removeCondition(int index);
		
		QList<IConditionPtr> getConditions() const;

	private:
		qint32 getOutputCount() const override;
		QString getOutputLabel(qint32 branch) const override;

		QList<IConditionPtr> _conditions;
	};

} /* namespace nodes */
} /* namespace tc */
