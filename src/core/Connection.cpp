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

#include "Connection.h"

#include "INode.h"

#include <QJsonObject>
#include <QVariant>

using namespace tc::core;

Connection::Connection(const INodePtr & startNode, int startNodeOutput, const INodePtr & endNode) : _startNode(startNode), _startNodeOutput(startNodeOutput), _endNode(endNode) {}

void Connection::read(const QJsonObject & json, const QList<INodePtr> & nodes) {
    const int startNodeId = json["startNode"].toInt();
    const int endNodeId = json["endNode"].toInt();

    auto it = std::find_if(nodes.begin(), nodes.end(), [startNodeId](const INodePtr & n) {
        return n->getID() == startNodeId;
	});

    if (it == nodes.end()) return;

    _startNode = *it;

    it = std::find_if(nodes.begin(), nodes.end(), [endNodeId](const INodePtr & n) {
        return n->getID() == endNodeId;
	});

	if (json.contains("startNodeOutput")) {
        _startNodeOutput = json["startNodeOutput"].toInt();
	}

    if (it == nodes.end()) return;

    _endNode = *it;
}

void Connection::write(QJsonObject & json) const {
    if (!_startNode) return;
	
    if (!_endNode) return;
	
	json["startNode"] = _startNode->getID();
	json["endNode"] = _endNode->getID();

	if (_startNodeOutput != 0) {
        json["startNodeOutput"] = _startNodeOutput;
	}
}

INodePtr Connection::getStartNode() const {
    return _startNode;
}

int Connection::getStartNodeOutput() const {
    return _startNodeOutput;
}

INodePtr Connection::getEndNode() const {
    return _endNode;
}
