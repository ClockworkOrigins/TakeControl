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

#include "nodesParameters.h"
#include "interfaces/IProperty.h"

#include "utils/Singleton.h"

class QJsonObject;

namespace tc {
namespace plugins {
	class IGamePlugin;
} /* namespace plugins */
namespace nodes {

	class TC_NODES_API PropertyFactory : public utils::Singleton<PropertyFactory> {
		friend class utils::Singleton<PropertyFactory>;
		
	public:
		IPropertyPtr create(const QString & type) const;

		void setActivePlugin(const plugins::IGamePlugin * plugin);

	private:
		const plugins::IGamePlugin * _activePlugin = nullptr;
	};

} /* namespace nodes */
} /* namespace tc */
