/* vi: set et sw=4 ts=4 cino=t0,(0: */
/*
 * Copyright (C) 2012 Alberto Mardegan <info@mardy.it>
 *
 * This file is part of minusphoto.
 *
 * minusphoto is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * minusphoto is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with minusphoto.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MINUSPHOTO_SIZE_CONTROLLER_H
#define MINUSPHOTO_SIZE_CONTROLLER_H

#include <QObject>
#include <QSize>
#include <QUrl>

namespace Minusphoto {

class SizeControllerPrivate;
class SizeController: public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal zoom READ zoom WRITE setZoom NOTIFY zoomChanged);
    Q_PROPERTY(QObject *image READ image WRITE setImage);
    Q_PROPERTY(QUrl source READ source WRITE setSource);
    Q_PROPERTY(QSize viewSize READ viewSize WRITE setViewSize);
    Q_PROPERTY(QString mode READ mode WRITE setMode);

public:
    explicit SizeController(QObject *parent = 0);
    virtual ~SizeController();

    void setZoom(qreal zoom);
    qreal zoom() const;

    void setImage(QObject *image);
    QObject *image() const;

    void setSource(const QUrl &source);
    QUrl source() const;

    void setViewSize(const QSize &size);
    QSize viewSize() const;

    void setMode(const QString &mode);
    QString mode() const;

Q_SIGNALS:
    void zoomChanged();

private:
    SizeControllerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(SizeController)
};

}; // namespace

#endif // MINUSPHOTO_SIZE_CONTROLLER_H
