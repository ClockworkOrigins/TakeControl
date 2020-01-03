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

class QJsonObject;

namespace tc {
namespace nodes {

	class INode {
	public:
		INode();
		INode(uint32_t id);
		
		virtual ~INode() {}

		virtual void read(const QJsonObject &json) = 0;
		virtual void write(QJsonObject & json) const = 0;

		static uint32_t getNextID();

	protected:
		uint32_t _id;

	private:
		static uint32_t _ids;
	};

} /* namespace nodes */
} /* namespace tc */
