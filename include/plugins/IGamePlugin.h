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

#include <QtPlugin>

namespace tc {
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
	};

} /* namespace plugins */
} /* namespace tc */

Q_DECLARE_INTERFACE(tc::plugins::IGamePlugin, "tc.game.IGamePlugin")
