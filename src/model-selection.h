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

#ifndef MAP_MODEL_SELECTION_H
#define MAP_MODEL_SELECTION_H

#include <QModelIndex>
#include <QObject>
#include <QSet>
#include <QVariant>

class QAbstractListModel;
class QByteArray;

namespace Speqtacle {

typedef QSet<int> ModelIndexes;

class ModelSelection: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel *model READ model WRITE setModel \
               NOTIFY modelChanged);
    Q_PROPERTY(bool empty READ isEmpty NOTIFY isEmptyChanged);
    Q_PROPERTY(QList<int> indexes READ indexes NOTIFY indexesChanged);

public:
    ModelSelection(QObject *parent = 0);
    ~ModelSelection() {};

    void setModel(QAbstractListModel *model);
    QAbstractListModel *model() const { return _model; }
    bool isEmpty() const { return _isEmpty; }

    QList<int> indexes() const;

public Q_SLOTS:
    void clear();
    void selectAll();
    void setSelection(int index);
    void setShiftSelection(int index);
    void setCtrlSelection(int index);
    bool isSelected(int index) { return _indexes.contains(index); }

    QList<QVariant> items(const QByteArray &roleName) const;
    QVariantMap get(int index) const;
    void removeItems();

Q_SIGNALS:
    void modelChanged();
    void isEmptyChanged();
    void indexesChanged();
    void itemsChanged();

private:
    void update();

private Q_SLOTS:
    void onRowsRemoved(const QModelIndex &parent, int start, int end);
    void onDataChanged(const QModelIndex &topLeft,
                       const QModelIndex &bottomRight);

private:
    QAbstractListModel *_model;
    ModelIndexes _indexes;
    bool _isEmpty;
    int _lastIndex;
};

}; // namespace

#endif /* MAP_MODEL_SELECTION_H */
