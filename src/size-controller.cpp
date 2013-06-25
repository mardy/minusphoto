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

#include "debug.h"
#include "size-controller.h"

#include <QImageReader>
#include <QMetaEnum>
#include <QUrl>

using namespace Minusphoto;

namespace Minusphoto {

class SizeControllerPrivate: public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(SizeController)

public:
    SizeControllerPrivate(SizeController *tracker);
    SizeControllerPrivate() {}

    void queueRefresh();
    void setupFillModeEnum(QObject *image);

private Q_SLOTS:
    void refresh();

private:
    QObject *image;
    QUrl source;
    qreal requestedZoom;
    qreal zoom;
    QSize fileSize;
    QSize viewSize;
    QString mode;
    int fillModePreserveAspectFit;
    bool refreshQueued;
    mutable SizeController *q_ptr;
};

} // namespace

SizeControllerPrivate::SizeControllerPrivate(SizeController *q):
    QObject(q),
    image(0),
    requestedZoom(-1),
    zoom(-1),
    mode(QLatin1String("fit")),
    fillModePreserveAspectFit(-1),
    refreshQueued(false),
    q_ptr(q)
{
}

void SizeControllerPrivate::queueRefresh()
{
    if (!refreshQueued) {
        QMetaObject::invokeMethod(this, "refresh", Qt::QueuedConnection);
        refreshQueued = true;
    }
}

void SizeControllerPrivate::setupFillModeEnum(QObject *image)
{
    const QMetaObject *metaObject = image->metaObject();

    for (int i = 0; i < metaObject->enumeratorCount(); i++) {
        QMetaEnum metaEnum = metaObject->enumerator(i);
        if (qstrcmp(metaEnum.name(), "FillMode") == 0) {
            fillModePreserveAspectFit =
                metaEnum.keyToValue("PreserveAspectFit");
            break;
        }
    }
}

void SizeControllerPrivate::refresh()
{
    Q_Q(SizeController);

    refreshQueued = false;

    qreal oldZoom = zoom;
    if (mode == "fit") {
        QSize sourceSize = fileSize;
        if (fileSize.width() > viewSize.width() ||
            fileSize.height() > viewSize.height()) {
            sourceSize.scale(viewSize, Qt::KeepAspectRatio);
        }
        image->setProperty("sourceSize", sourceSize);
        image->setProperty("width", sourceSize.width());
        image->setProperty("height", sourceSize.height());
        image->setProperty("fillMode", fillModePreserveAspectFit);
        if (fileSize.width() > 0) {
            zoom = qreal(sourceSize.width()) / fileSize.width();
        } else {
            zoom = 1;
        }
    } else if (mode == "zoom") {
    }
    image->setProperty("source", source);

    if (zoom != oldZoom) Q_EMIT q->zoomChanged();
}

SizeController::SizeController(QObject *parent):
    QObject(parent),
    d_ptr(new SizeControllerPrivate(this))
{
}

SizeController::~SizeController()
{
    delete d_ptr;
    d_ptr = 0;
}

void SizeController::setZoom(qreal zoom)
{
    Q_D(SizeController);
    d->zoom = zoom;
    d->queueRefresh();
}

qreal SizeController::zoom() const
{
    Q_D(const SizeController);
    return d->zoom;
}

void SizeController::setImage(QObject *image)
{
    Q_D(SizeController);
    if (image == d->image) return;

    if (image != 0) {
        if (d->fillModePreserveAspectFit < 0) {
            d->setupFillModeEnum(image);
        }
    }
    d->image = image;
    d->queueRefresh();
}

QObject *SizeController::image() const
{
    Q_D(const SizeController);
    return d->image;
}

void SizeController::setSource(const QUrl &source)
{
    Q_D(SizeController);
    if (source == d->source) return;

    d->source = source;
    QImageReader reader(source.toLocalFile());
    d->fileSize = reader.size();

    d->queueRefresh();
}

QUrl SizeController::source() const
{
    Q_D(const SizeController);
    return d->source;
}

void SizeController::setViewSize(const QSize &size)
{
    Q_D(SizeController);
    d->viewSize = size;
    d->queueRefresh();
}

QSize SizeController::viewSize() const
{
    Q_D(const SizeController);
    return d->viewSize;
}

void SizeController::setMode(const QString &mode)
{
    Q_D(SizeController);
    d->mode = mode;
    d->queueRefresh();
}

QString SizeController::mode() const
{
    Q_D(const SizeController);
    return d->mode;
}

#include "size-controller.moc"
