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

#include <memory>

namespace tc {
namespace core {

	class Character;
	typedef std::shared_ptr<Character> CharacterPtr;
	
    class CharacterProperty;
    typedef std::shared_ptr<CharacterProperty> CharacterPropertyPtr;

    class Connection;
    typedef std::shared_ptr<Connection> ConnectionPtr;

    class Dialog;
    typedef std::shared_ptr<Dialog> DialogPtr;

    class ICondition;
    typedef std::shared_ptr<ICondition> IConditionPtr;

    class IGamePlugin;

    class INode;
    typedef std::shared_ptr<INode> INodePtr;

    class IProperty;
    typedef std::shared_ptr<IProperty> IPropertyPtr;

    class Project;
    typedef std::shared_ptr<Project> ProjectPtr;

    class TextProperty;
    typedef std::shared_ptr<TextProperty> TextPropertyPtr;

    class TranslateableText;
    typedef std::shared_ptr<TranslateableText> TranslateableTextPtr;

    class TranslateableTextProperty;
    typedef std::shared_ptr<TranslateableTextProperty> TranslateableTextPropertyPtr;

} /* namespace core */
} /* namespace tc */
