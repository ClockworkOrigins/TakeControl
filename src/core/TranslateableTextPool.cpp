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

#include "TranslateableTextPool.h"

#include "TranslateableText.h"

using namespace tc::core;

void TranslateableTextPool::setTranslateableTexts(const QList<TranslateableTextPtr> & translateableTexts) {
    _translateableTexts = translateableTexts;

    emit translateableTextsChanged();
}

QList<TranslateableTextPtr> TranslateableTextPool::getTranslateableTexts() const {
    return _translateableTexts;
}

void TranslateableTextPool::setDefaultLanguage(const QString & language) {
    _language = language;
}

QString TranslateableTextPool::getDefaultLanguage() const {
    return _language;
}

void TranslateableTextPool::changeIdentifier(const QString & before, const QString & after) {
	const auto it = std::find_if(_translateableTexts.begin(), _translateableTexts.end(), [before](const TranslateableTextPtr & tt) {
        return tt->getKey() == before;
	});

    Q_ASSERT(it != _translateableTexts.end());

    if (it == _translateableTexts.end()) return;

    (*it)->setKey(after);
}

void TranslateableTextPool::addTranslateableText(const TranslateableTextPtr & character) {
    _translateableTexts << character;

    emit translateableTextAdded(character);
}

void TranslateableTextPool::removeTranslateableText(const TranslateableTextPtr & character) {
    _translateableTexts.removeAll(character);

    emit translateableTextRemoved(character);
}
