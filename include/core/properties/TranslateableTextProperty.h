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

#include "core/IProperty.h"

namespace tc {
namespace gui {
    class TranslateableTextPropertyItem;
}
namespace core {

	class TC_CORE_API TranslateableTextProperty : public IProperty {
        friend class SetTranslateableTextPropertyValueCommand;
        friend class gui::TranslateableTextPropertyItem;
		
	public:
        TranslateableTextProperty();

        void setValue(const QString & value);
        QString getValue() const;

	private:
        QString _value;
		
		void read(const QJsonObject &json) override;
		void write(QJsonObject & json) const override;

		QString getType() const override;

        static QString getDefaultValue();
	};

} /* namespace core */
} /* namespace tc */
