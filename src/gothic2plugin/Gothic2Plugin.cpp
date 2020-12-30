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

#include "gothic2plugin/Gothic2Plugin.h"

#include "core/Character.h"
#include "core/Connection.h"
#include "core/Dialog.h"
#include "core/INode.h"
#include "core/Project.h"
#include "core/TranslateableText.h"

#include "core/properties/CharacterProperty.h"
#include "core/properties/TextProperty.h"
#include "core/properties/TranslateableTextProperty.h"

using namespace tc::core;
using namespace tc::gui;
using namespace tc::plugins::gothic2plugin;

QString Gothic2Plugin::getName() const {
	return "Gothic 2";
}

QStringList Gothic2Plugin::getSupportedNodes() const {
	return {
		"And",
		"Branching",
		"Exit Conversation",
		"Or",
		"Output",
		"Translateable Text"
	};
}

IConditionPtr Gothic2Plugin::createCondition(const QString &, const QJsonObject &) const {
	return nullptr;
}

INodePtr Gothic2Plugin::createNode(const QString &) const {
	return nullptr;
}

NodeItem * Gothic2Plugin::createNodeItem(const QString &) const {
    return nullptr;
}

IPropertyPtr Gothic2Plugin::createProperty(const QString &) const {
    return nullptr;
}

PropertyItem * Gothic2Plugin::createPropertyItem(const QString &) const {
    return nullptr;
}

QStringList Gothic2Plugin::getSupportedLanguages() const {
	return {
		"English",
		"German"
	};
}

bool Gothic2Plugin::exportProject(const ProjectPtr & project) const {
	// TODO: get output path
	const auto dialogs = project->getDialogs();
	const auto characters = project->getCharacters();
	const auto texts = project->getTexts();

	QString converted;

	for (const auto & dialog : dialogs) {
		converted += convert(dialog, characters, texts);
	}

	// TODO: write to file
	
	return false; // TODO: implement somewhen in the future
}

QString Gothic2Plugin::convert(const DialogPtr & dialog, const QList<CharacterPtr> & characters, const QList<TranslateableTextPtr> & texts) const {
	const auto connections = dialog->getConnections();
	const auto nodes = dialog->getNodes();

	QString dialogName;
	QString dialogOwnerName;
	
	QString converted = convertDialogHeader(dialog, characters, texts, nodes, connections, dialogName, dialogOwnerName);
	converted += "\n";
	converted += convertDialogConditions(dialog, characters, texts, dialogName, dialogOwnerName);
	converted += "\n";
	converted += convertDialogBody(dialog, characters, texts, nodes, connections, dialogName, dialogOwnerName);

	return converted;
}

QString Gothic2Plugin::convertDialogHeader(const DialogPtr & dialog, const QList<CharacterPtr> & characters, const QList<TranslateableTextPtr> & texts, const QList<INodePtr> & nodes, const QList<ConnectionPtr> & connections, QString & dialogName, QString & dialogOwnerName) const {
	bool permanent = false;
	bool important = false;

	QString dialogOwner;
	QString descriptionText;

	getDialogConfiguration(dialog, characters, texts, nodes, connections, dialogOwner, dialogOwnerName, dialogName, permanent, important, descriptionText);

	if (!descriptionText.isEmpty()) {
		descriptionText = QString("\tdescription\t= \"%1\";\n").arg(descriptionText);
	}
	
	// instance:
	// %1: dialogOwnerName
	// %2: dialogName
	// %3: dialogOwner
	// %4: permanent
	// %5: important
	// %6: descriptionText
	QString converted = QString("INSTANCE DIA_%1_%2 (C_INFO) {\n"
								"\tnpc\t\t\t= %3;\n"
								"\tnr\t\t\t= 1;\n"
								"\tcondition\t= DIA_%1_%2_Condition;\n"
								"\tinformation\t= DIA_%1_%2_Info;\n"
								"\tpermanent\t= %4;\n"
								"\timportant\t= %5;\n"
								"%6"
								"};\n").arg(dialogOwnerName).arg(dialogName).arg(dialogOwner).arg(permanent ? "TRUE" : "FALSE").arg(important ? "TRUE" : "FALSE").arg(descriptionText);

	return converted;
}

QString Gothic2Plugin::convertDialogConditions(const DialogPtr & dialog, const QList<CharacterPtr> & characters, const QList<TranslateableTextPtr> & texts, const QString & dialogName, const QString & dialogOwnerName) const {
	// instance:
	// %1: dialogOwnerName
	QString converted = QString("FUNC INT DIA_%1_%2_Condition() {\n"
								"\treturn TRUE;\n"
								"};\n").arg(dialogOwnerName).arg(dialogName);

	return converted;
}

QString Gothic2Plugin::convertDialogBody(const DialogPtr & dialog, const QList<CharacterPtr> & characters, const QList<TranslateableTextPtr> & texts, const QList<INodePtr> & nodes, const QList<ConnectionPtr> & connections, const QString & dialogName, const QString & dialogOwnerName) const {
	// instance:
	// %1: dialogOwnerName
	QString converted = QString("FUNC VOID DIA_%1_%2_Info() {\n").arg(dialogOwnerName).arg(dialogName);

	auto currentNode = getStartNode(nodes, connections);

	int checkedNodes = 0;

	while (checkedNodes < nodes.count() && currentNode) {
		if (currentNode->getType() == "Output") {
			const auto props = currentNode->getProperties();
			Q_ASSERT(props.size() == 2);

			const auto charProp = std::dynamic_pointer_cast<CharacterProperty>(props[0]);
			const auto textProp = std::dynamic_pointer_cast<TranslateableTextProperty>(props[1]);

			Q_ASSERT(charProp);
			Q_ASSERT(textProp);

			const auto it = std::find_if(texts.begin(), texts.end(), [textProp](const TranslateableTextPtr & tt) {
				return tt->getKey() == textProp->getValue();
			});

			const auto text = it != texts.end() ? (*it)->getTranslation("German") : "";

			// %1: speaker, either self or other
			// %2: listener, either self or other
			// %3: text key
			// %4: text
			converted += QString("\tAI_Output (%1, %2, \"%3\"); //%4\n").arg(charProp->getValue() == "Hero" ? "other" : "self").arg(charProp->getValue() == "Hero" ? "self" : "other").arg(textProp->getValue()).arg(text);
		}

		checkedNodes++;

		currentNode = getNextNode(connections, currentNode);
	}
	
	converted += "};\n";

	return converted;
}

void Gothic2Plugin::getDialogConfiguration(const DialogPtr & dialog, const QList<CharacterPtr> & characters, const QList<TranslateableTextPtr> & texts, const QList<INodePtr> & nodes, const QList<ConnectionPtr> & connections, QString & dialogOwner, QString & dialogOwnerName, QString & dialogName, bool & permanent, bool & important, QString & description) const {
	auto currentNode = getStartNode(nodes, connections);
	
	dialogName = dialog->getName();

	int checkedNodes = 0;

	const auto participants = getParticipants(nodes);

	if (participants.size() == 1) {
		dialogOwner = participants[0];
	}
	
	for (const auto & p : participants) {
		if (p == "Hero") continue; // TODO: make configurable

		dialogOwner = p;
		
		break;
	}

	const auto itOwner = std::find_if(characters.begin(), characters.end(), [dialogOwner](const CharacterPtr & c) {
		return c->getName() == dialogOwner; // TODO: change when character has identifier AND name
	});

	if (itOwner != characters.end()) {
		dialogOwnerName = (*itOwner)->getName();
	}

	while (checkedNodes < nodes.count() && currentNode) {
		if (currentNode->getType() == "Text") {
			description = std::dynamic_pointer_cast<TextProperty>(currentNode->getProperties()[0])->getValue();
		}
		
		if (currentNode->getType() == "Translateable Text") {
			const auto key = std::dynamic_pointer_cast<TranslateableTextProperty>(currentNode->getProperties()[0])->getValue();

			const auto it = std::find_if(texts.begin(), texts.end(), [key](const TranslateableTextPtr & tt) {
				return key == tt->getKey();
			});

			if (it != texts.end()) {
				description = (*it)->getTranslation("German"); // TODO: allow to set export language
			}
		}
		
		if (currentNode->getType() == "Output") {
			const auto props = currentNode->getProperties();
			Q_ASSERT(props.size() == 2);

			const auto charProp = std::dynamic_pointer_cast<CharacterProperty>(props[0]);
			const auto textProp = std::dynamic_pointer_cast<TranslateableTextProperty>(props[1]);

			Q_ASSERT(charProp);
			Q_ASSERT(textProp);
			
			break;
		}

		checkedNodes++;

		currentNode = getNextNode(connections, currentNode);
	}

	important = description.isEmpty();
}

INodePtr Gothic2Plugin::getStartNode(const QList<INodePtr> & nodes, const QList<ConnectionPtr> & connections) const {
	for (const auto & node : nodes) {
		const auto it = std::find_if(connections.begin(), connections.end(), [node](const ConnectionPtr & connection) {
			return connection->getEndNode() == node;
		});

		if (it == connections.end()) return node;
	}

	return nullptr;
}

INodePtr Gothic2Plugin::getNextNode(const QList<ConnectionPtr> & connections, INodePtr & currentNode) const {
	const auto it = std::find_if(connections.begin(), connections.end(), [currentNode](const ConnectionPtr & c) {
		return c->getStartNode() == currentNode;
	});

	return it != connections.end() ? (*it)->getEndNode() : nullptr;
}

QStringList Gothic2Plugin::getParticipants(const QList<INodePtr> & nodes) const {
	QStringList participants;
	
	for (const auto & n : nodes) {
		if (n->getType() != "Output") continue;

		const auto props = n->getProperties();
		Q_ASSERT(props.size() == 2);

		const auto charProp = std::dynamic_pointer_cast<CharacterProperty>(props[0]);

		Q_ASSERT(charProp);

		const auto c = charProp->getValue();
		
		if (participants.contains(c)) continue;

		participants << c;
	}

	return participants;
}

Q_PLUGIN_METADATA(IID "tc.game.IGamePlugin")
