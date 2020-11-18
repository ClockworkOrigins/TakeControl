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
#include "core/ICondition.h"

#include "utils/Singleton.h"

namespace tc {
namespace core {
	
	class IGamePlugin;

	class TC_CORE_API ConditionFactory : public utils::Singleton<ConditionFactory> {
		friend class utils::Singleton<ConditionFactory>;
		
	public:
		IConditionPtr create(const QJsonObject & json) const;

		void setActivePlugin(const IGamePlugin * plugin);

	private:
		const IGamePlugin * _activePlugin = nullptr;
	};

} /* namespace core */
} /* namespace tc */
