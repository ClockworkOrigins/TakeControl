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

#include "Config.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

using namespace tc::utils;

void Config::init() {
	const QLocale locale = QLocale::system();
	QString language;
	if (locale.language() == QLocale::Language::German) {
		language = "Deutsch";
	} else {
		language = "English";
	}

	updateLanguage(language);
}

void Config::updateLanguage(const QString & language) {
	QTranslator * translator = new QTranslator(qApp);
	if (language == "Deutsch") {
		QLocale::setDefault(QLocale("de_DE"));
		translator->load(qApp->applicationDirPath() + "/de_DE");
	} else {
		QLocale::setDefault(QLocale("en_US"));
		translator->load(qApp->applicationDirPath() + "/en_US");
	}
	qApp->installTranslator(translator);
}
