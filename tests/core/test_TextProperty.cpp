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

#include "properties/TextProperty.h"

#include "TakeControlConfig.h"

#include "CoreTypes.h"
#include "IProperty.h"

#include "utils/UndoStack.h"

#include "gtest/gtest.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace tc::core;
using namespace tc::utils;

class TextPropertyTest : public ::testing::Test {
protected:
	void SetUp() override {
		UndoStack::instance()->clear();

		textProperty = std::make_shared<TextProperty>();
		prop = textProperty;
	}
	
	TextPropertyPtr textProperty;
	IPropertyPtr prop;
};

TEST_F(TextPropertyTest, ctor) {
	ASSERT_EQ("Text", prop->getType());
	ASSERT_EQ("", textProperty->getValue());
}

TEST_F(TextPropertyTest, valueChange) {
	const QString testText = QStringLiteral("Awesome test text");

	int count = 0;
	QObject::connect(textProperty.get(), &IProperty::valueChanged, [&count]() { count++; });
	
	ASSERT_EQ("", textProperty->getValue());

	textProperty->setValue(testText);

	ASSERT_EQ(testText, textProperty->getValue());
	ASSERT_EQ(1, count);

	UndoStack::instance()->undo();

	ASSERT_EQ("", textProperty->getValue());
	ASSERT_EQ(2, count);

	UndoStack::instance()->redo();

	ASSERT_EQ(testText, textProperty->getValue());
	ASSERT_EQ(3, count);
}

TEST_F(TextPropertyTest, save) {
	QJsonObject json;
	prop->write(json);
	
	const QJsonDocument jsonDoc(json);
	const auto jsonData = jsonDoc.toJson();

	QFile referenceFile(TESTFOLDER + "/core/resources/TextProperty/save.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	ASSERT_EQ(referenceData, jsonData);
}

TEST_F(TextPropertyTest, load) {
	QFile referenceFile(TESTFOLDER + "/core/resources/TextProperty/load.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	const auto jsonDoc = QJsonDocument::fromJson(referenceData);
	const auto json = jsonDoc.object();

	prop->read(json);

	ASSERT_EQ("Awesome test text", textProperty->getValue());
}
