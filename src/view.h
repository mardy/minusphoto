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

#ifndef MINUSPHOTO_VIEW_H
#define MINUSPHOTO_VIEW_H

#include <QQuickView>

namespace Minusphoto {

class View: public QQuickView
{
    Q_OBJECT

public:
    explicit View();
    virtual ~View();

public Q_SLOTS:
    void switchFullscreen();
};

}; // namespace

#endif // MINUSPHOTO_VIEW_H
