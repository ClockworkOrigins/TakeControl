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

#include "nodes/TextNode.h"

#include "TakeControlConfig.h"

#include "IProperty.h"

#include "gtest/gtest.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace tc::core;

TEST(TextNode, ctor) {
	const INodePtr textNode = std::make_shared<TextNode>();

	const auto properties = textNode->getProperties();
	
	ASSERT_EQ(1, properties.count());
	ASSERT_EQ("Text", properties[0]->getType());

	const auto type = textNode->getType();

	ASSERT_EQ("Text", type);
	ASSERT_EQ(0, textNode->getID());
}

TEST(TextNode, save) {
	TextNode textNode;
	textNode.setID(2);
	
	QJsonObject json;
	textNode.write(json);
	const QJsonDocument jsonDoc(json);
	const auto jsonData = jsonDoc.toJson();

	QFile referenceFile(TESTFOLDER + "/core/resources/TextNode/save.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	QString text = QString::fromLatin1(jsonData);

	ASSERT_EQ(referenceData, jsonData);
}

TEST(TextNode, load) {
	QFile referenceFile(TESTFOLDER + "/core/resources/TextNode/load.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	const auto jsonDoc = QJsonDocument::fromJson(referenceData);
	const auto json = jsonDoc.object();

	TextNode textNode;
	textNode.read(json);

	const auto properties = textNode.getProperties();

	ASSERT_EQ(1, properties.count());
	ASSERT_EQ("Text", properties[0]->getType());
	ASSERT_EQ(1, textNode.getID());
}
