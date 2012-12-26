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
#include "view.h"

#include <QGLWidget>

using namespace Speqtacle;

View::View():
    QDeclarativeView()
{
    setResizeMode(SizeRootObjectToView);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
#ifdef Q_WS_MAEMO_5
    setAttribute(Qt::WA_Maemo5AutoOrientation, true);
    setAttribute(Qt::WA_Maemo5NonComposited, true);
#endif
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
#if !defined(Q_OS_WIN32) && !defined (Q_OS_MAC)
    setViewport(new QGLWidget);
#endif
#ifdef Q_WS_MAEMO_5
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    viewport()->setAttribute(Qt::WA_NoSystemBackground);
#endif
}

View::~View()
{
}

void View::switchFullscreen()
{
    bool isFullScreen = windowState() & Qt::WindowFullScreen;
    if (isFullScreen)
        showNormal();
    else
        showFullScreen();
}

void View::closeEvent(QCloseEvent *event)
{
    Q_EMIT closing();
    QDeclarativeView::closeEvent(event);
}
