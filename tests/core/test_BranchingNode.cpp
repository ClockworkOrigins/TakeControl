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

#include "nodes/BranchingNode.h"

#include "TakeControlConfig.h"

#include "gtest/gtest.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace tc::core;

TEST(BranchingNode, ctor) {
	const INodePtr branchingNode = std::make_shared<BranchingNode>();

	const auto properties = branchingNode->getProperties();
	
	ASSERT_TRUE(properties.isEmpty());

	const auto type = branchingNode->getType();

	ASSERT_EQ("Branching", type);
	ASSERT_EQ(0, branchingNode->getID());
}

TEST(BranchingNode, save) {
	BranchingNode branchingNode;
	branchingNode.setID(2);
	
	QJsonObject json;
	branchingNode.write(json);
	const QJsonDocument jsonDoc(json);
	const auto jsonData = jsonDoc.toJson();

	QFile referenceFile(TESTFOLDER + "/core/resources/BranchingNode/save.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	QString text = QString::fromLatin1(jsonData);

	ASSERT_EQ(referenceData, jsonData);
}

TEST(BranchingNode, load) {
	QFile referenceFile(TESTFOLDER + "/core/resources/BranchingNode/load.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	const auto jsonDoc = QJsonDocument::fromJson(referenceData);
	const auto json = jsonDoc.object();

	BranchingNode branchingNode;
	branchingNode.read(json);

	const auto properties = branchingNode.getProperties();

	ASSERT_TRUE(properties.isEmpty());
	ASSERT_EQ(1, branchingNode.getID());
}
