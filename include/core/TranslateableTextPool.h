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

#include "utils/Singleton.h"

#include <QList>
#include <QObject>

namespace tc {
namespace core {

	class TC_CORE_API TranslateableTextPool : public QObject, public utils::Singleton<TranslateableTextPool> {
		Q_OBJECT
		
		friend class utils::Singleton<TranslateableTextPool>;
		
	public:
		void setTranslateableTexts(const QList<TranslateableTextPtr> & translateableTexts);
		QList<TranslateableTextPtr> getTranslateableTexts() const;

		void addTranslateableText(const TranslateableTextPtr & translateableText);
		void removeTranslateableText(const TranslateableTextPtr & translateableText);

		void setDefaultLanguage(const QString & language);
		QString getDefaultLanguage() const;

	signals:
		void translateableTextsChanged();
		void translateableTextAdded(const TranslateableTextPtr & translateableText);
		void translateableTextRemoved(const TranslateableTextPtr & translateableText);

	private:
		QString _language;
		QList<TranslateableTextPtr> _translateableTexts;
	};

} /* namespace core */
} /* namespace tc */
