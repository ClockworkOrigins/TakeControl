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

#include "nodes/ExitConversationNode.h"

#include "TakeControlConfig.h"

#include "gtest/gtest.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace tc::core;

TEST(ExitConversationNode, ctor) {
	const INodePtr exitConversationNode = std::make_shared<ExitConversationNode>();

	const auto properties = exitConversationNode->getProperties();
	
	ASSERT_EQ(0, properties.count());

	const auto type = exitConversationNode->getType();

	ASSERT_EQ("Exit Conversation", type);
	ASSERT_EQ(0, exitConversationNode->getID());
}

TEST(ExitConversationNode, save) {
	ExitConversationNode exitConversationNode;
	exitConversationNode.setID(2);
	
	QJsonObject json;
	exitConversationNode.write(json);
	const QJsonDocument jsonDoc(json);
	const auto jsonData = jsonDoc.toJson();

	QFile referenceFile(TESTFOLDER + "/core/resources/ExitConversationNode/save.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	QString text = QString::fromLatin1(jsonData);

	ASSERT_EQ(referenceData, jsonData);
}

TEST(ExitConversationNode, load) {
	QFile referenceFile(TESTFOLDER + "/core/resources/ExitConversationNode/load.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	const auto jsonDoc = QJsonDocument::fromJson(referenceData);
	const auto json = jsonDoc.object();

	ExitConversationNode exitConversationNode;
	exitConversationNode.read(json);

	const auto properties = exitConversationNode.getProperties();

	ASSERT_EQ(0, properties.count());
	ASSERT_EQ(1, exitConversationNode.getID());
}
