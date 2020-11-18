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

#include "gui/GuiParameters.h"

#include <QGraphicsItem>

namespace tc {
namespace core {
    class IProperty;
    typedef std::shared_ptr<IProperty> IPropertyPtr;
} /* namespace core */
namespace gui {

	class TC_GUI_API PropertyItem : public QGraphicsItem {
	public:
        virtual ~PropertyItem() = default;
		
        virtual void configure(const core::IPropertyPtr & prop) = 0;
	};

} /* namespace gui */
} /* namespace tc */
