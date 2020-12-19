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

#include <QJsonObject>
#include <QMap>
#include <QString>

namespace tc {
namespace core {

	class TC_CORE_API TranslateableText : public QObject {
		Q_OBJECT
		
	public:
		explicit TranslateableText(const QString & key);

		QString getKey() const;
		QMap<QString, QString> getTranslations() const;
		QString getTranslation(const QString & language) const;
		void updateTranslation(const QString & language, const QString & text);

		QJsonObject save() const;

		static TranslateableTextPtr load(const QJsonObject & json);

	signals:
		void translationChanged(const QString & language, const QString & text);

	private:
		QString _key;
		QMap<QString, QString> _texts;
	};

} /* namespace core */
} /* namespace tc */
