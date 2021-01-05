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

#include "DialogPool.h"

#include "Dialog.h"

using namespace tc::core;

void DialogPool::setDialogs(const QList<DialogPtr> & dialogs) {
    _dialogs = dialogs;

    emit dialogsChanged();
}

QList<DialogPtr> DialogPool::getDialogs() const {
    return _dialogs;
}

void DialogPool::addDialog(const DialogPtr & dialog) {
    _dialogs << dialog;

    emit dialogAdded(dialog);
}

void DialogPool::removeDialog(const DialogPtr & dialog) {
    _dialogs.removeAll(dialog);

    emit dialogRemoved(dialog);
}

void DialogPool::changeIdentifier(const QString & before, const QString & after) {
    const auto it = std::find_if(_dialogs.begin(), _dialogs.end(), [before](const DialogPtr & d) {
        return d->getName() == before;
    });

    Q_ASSERT(it != _dialogs.end());

    if (it == _dialogs.end()) return;

    (*it)->setName(after);
}
