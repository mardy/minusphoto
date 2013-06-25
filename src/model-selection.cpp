/* vi: set et sw=4 ts=4 cino=t0,(0: */
/*
 * Copyright (C) 2012 Alberto Mardegan <info@mardy.it>
 *
 * This file is part of speqtacle.
 *
 * speqtacle is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * speqtacle is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with speqtacle.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "debug.h"
#include "model-selection.h"

#include <QAbstractListModel>

using namespace Speqtacle;

ModelSelection::ModelSelection(QObject *parent):
    QObject(parent),
    _model(0),
    _isEmpty(true),
    _lastIndex(-1)
{
}

void ModelSelection::setModel(QAbstractListModel *model)
{
    if (model == _model) return;

    if (_model != 0) {
        _model->disconnect(this);
    }

    _model = model;

    if (model) {
        connect(model,
                SIGNAL(dataChanged(const QModelIndex&,const QModelIndex&)),
                SLOT(onDataChanged(const QModelIndex&,const QModelIndex&)));
        connect(model, SIGNAL(rowsRemoved(const QModelIndex&,int,int)),
                this, SLOT(onRowsRemoved(const QModelIndex&,int,int)));
    }

    clear();
}

QList<int> ModelSelection::indexes() const
{
    QList<int> sortedIndexes = _indexes.toList();
    qSort(sortedIndexes);
    return sortedIndexes;
}

void ModelSelection::clear()
{
    _indexes.clear();
    _lastIndex = -1;

    update();
}

void ModelSelection::selectAll()
{
    int len = _model->rowCount();
    for (int i = 0; i < len; i++) {
        _indexes.insert(i);
    }
    _lastIndex = -1;

    update();
}

void ModelSelection::setSelection(int index)
{
    _indexes.clear();
    _indexes.insert(index);
    _lastIndex = index;

    update();
}

void ModelSelection::setShiftSelection(int index)
{
    if (_lastIndex < 0) return setSelection(index);

    int first, last;
    if (_lastIndex > index) {
        first = index;
        last = _lastIndex;
    } else {
        first = _lastIndex;
        last = index;
    }

    for (int i = first; i <= last; i++)
        _indexes.insert(i);
    _lastIndex = index;

    update();
}

void ModelSelection::setCtrlSelection(int index)
{
    if (_indexes.contains(index)) {
        _indexes.remove(index);
    } else {
        _indexes.insert(index);
    }
    _lastIndex = index;

    update();
}

QList<QVariant> ModelSelection::items(const QByteArray &roleName) const
{
    QList<QVariant> list;

    QList<int> sortedIndexes = _indexes.toList();
    qSort(sortedIndexes);

    const QHash<int, QByteArray> &roleMap = _model->roleNames();
    int role = roleMap.key(roleName);
    foreach (int index, sortedIndexes) {
        QVariant item = _model->data(_model->index(index), role);
        list.append(item);
    }
    return list;
}

QVariantMap ModelSelection::get(int index) const
{
    QVariantMap map;
    const QHash<int, QByteArray> &roles = _model->roleNames();
    QHash<int, QByteArray>::const_iterator i = roles.constBegin();
    QModelIndex modelIndex = _model->index(index);
    while (i != roles.constEnd()) {
        map[QString::fromLatin1(i.value())] =
            _model->data(modelIndex, i.key());
        ++i;
    }
    return map;
}

void ModelSelection::removeItems()
{
    if (_isEmpty) return;

    QList<int> sortedIndexes = _indexes.toList();
    qSort(sortedIndexes);

    /* Start removing rows from the end, so we don't have to update the indexes
     */
    int last = -1;
    int count = 0;
    int len = sortedIndexes.count();
    for (int i = len - 1; i >= 0; i--) {
        int index = sortedIndexes[i];
        if (index == last - count) {
            count++;
        } else {
            if (last >= 0) {
                _model->removeRows(last - count + 1, count);
            }
            last = index;
            count = 1;
        }
    }
    _model->removeRows(last - count + 1, count);
}

void ModelSelection::update()
{
    if (_indexes.isEmpty() != _isEmpty) {
        _isEmpty = _indexes.isEmpty();
        Q_EMIT isEmptyChanged();
    }

    Q_EMIT indexesChanged();
    Q_EMIT itemsChanged();
}

void ModelSelection::onRowsRemoved(const QModelIndex &, int first, int last)
{
    int count = last - first + 1;

    ModelIndexes newIndexes;

    foreach (int index, _indexes) {
        if (index < first) {
            newIndexes.insert(index);
        } else if (index > last) {
            newIndexes.insert(index - count);
        }
    }

    _indexes = newIndexes;
    update();
}

void ModelSelection::onDataChanged(const QModelIndex &, const QModelIndex &)
{
    update();
}
