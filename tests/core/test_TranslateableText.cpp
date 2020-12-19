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

#include "TakeControlConfig.h"

#include "gtest/gtest.h"

#include <QFile>
#include <QJsonDocument>

using namespace tc::core;

TEST(TranslateableText, ctor) {
	const TranslateableText text("Key");
	ASSERT_EQ("Key", text.getKey());
	ASSERT_TRUE(text.getTranslations().isEmpty());
}

TEST(TranslateableText, updateTranslation) {
	TranslateableText text("Key");

	text.updateTranslation("German", "Foo");

	ASSERT_EQ(1, text.getTranslations().size());
	ASSERT_EQ("Foo", text.getTranslation("German"));

	text.updateTranslation("English", "Bar");
	ASSERT_EQ("Foo", text.getTranslation("German"));
	ASSERT_EQ("Bar", text.getTranslation("English"));

	ASSERT_EQ(2, text.getTranslations().size());

	text.updateTranslation("German", "Bar");
	ASSERT_EQ("Bar", text.getTranslation("German"));
	ASSERT_EQ("Bar", text.getTranslation("English"));

	ASSERT_EQ(2, text.getTranslations().size());

	text.updateTranslation("German", "");

	ASSERT_EQ(1, text.getTranslations().size());
	ASSERT_EQ("", text.getTranslation("German"));
	ASSERT_EQ("Bar", text.getTranslation("English"));

	text.updateTranslation("", "");

	ASSERT_EQ(1, text.getTranslations().size());
}

TEST(TranslateableText, save) {
	TranslateableText text("Key1");

	text.updateTranslation("German", "Foo");
	text.updateTranslation("English", "Bar");
	
	const QJsonObject json = text.save();
	const QJsonDocument jsonDoc(json);
	const auto jsonData = jsonDoc.toJson();

	QFile referenceFile(TESTFOLDER + "/core/resources/TranslateableText/save.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	ASSERT_EQ(referenceData, jsonData);
}

TEST(TranslateableText, load) {
	QFile referenceFile(TESTFOLDER + "/core/resources/TranslateableText/load.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	const auto jsonDoc = QJsonDocument::fromJson(referenceData);
	const auto json = jsonDoc.object();

	const auto text = TranslateableText::load(json);
	ASSERT_TRUE(text);

	ASSERT_EQ("Key2", text->getKey());
	ASSERT_EQ(2, text->getTranslations().size());
	ASSERT_EQ("Foo", text->getTranslation("German"));
	ASSERT_EQ("Bar", text->getTranslation("English"));
}
