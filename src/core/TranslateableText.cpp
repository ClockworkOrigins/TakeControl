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

#include "TranslateableText.h"

#include <QJsonArray>

using namespace tc::core;

TranslateableText::TranslateableText(const QString & key) : _key(key) {}

QString TranslateableText::getKey() const {
	return _key;
}

QMap<QString, QString> TranslateableText::getTranslations() const {
	return _texts;
}

QString TranslateableText::getTranslation(const QString & language) const {
	return _texts.value(language);
}

void TranslateableText::updateTranslation(const QString & language, const QString & text) {
	if (language.isEmpty()) return;

	const auto oldText = _texts.value(language);

	if (text == oldText) return;

	if (text.isEmpty()) {
		_texts.remove(language);
		emit translationChanged(language, text);
		return;
	}

	_texts[language] = text;
	emit translationChanged(language, text);
}

QJsonObject TranslateableText::save() const {
	QJsonObject json;
	json["Key"] = _key;

	QJsonArray arr;

	for (auto it = _texts.begin(); it != _texts.end(); ++it) {
		QJsonObject jsonText;

		auto text = it.value();
		text = text.replace("'", "&apos;");
		text = text.replace("\n", "<br>");

		jsonText["Language"] = it.key();
		jsonText["Text"] = text;

		arr << jsonText;
	}

	if (!_texts.isEmpty()) {
		json["Texts"] = arr;
	}

	return json;
}

TranslateableTextPtr TranslateableText::load(const QJsonObject & json) {
	if (!json.contains("Key")) return nullptr;
	
	QString key = json["Key"].toString();
	
	auto t = std::make_shared<TranslateableText>(key);

	if (json.contains("Texts")) {
		auto arr = json["Texts"].toArray();

		for (auto jsonRef : arr) {
			auto jsonText = jsonRef.toObject();

			auto text = jsonText["Text"].toString();
			const auto language = jsonText["Language"].toString();

			text = text.replace("<br>", "\n");
			text = text.replace("&apos;", "'");

			t->updateTranslation(language, text);
		}
	}

	return t;
}
