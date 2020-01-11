/**
 * @file
 * @brief Source file for Video RendererWidget class
 * @author Jonathan Thomas <jonathan@openshot.org>
 *
 * @ref License
 */

/* LICENSE
 *
 * Copyright (c) 2008-2019 OpenShot Studios, LLC
 * <http://www.openshotstudios.com/>. This file is part of
 * OpenShot Library (libopenshot), an open-source project dedicated to
 * delivering high quality video editing and animation solutions to the
 * world. For more information visit <http://www.openshot.org/>.
 *
 * OpenShot Library (libopenshot) is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * OpenShot Library (libopenshot) is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with OpenShot Library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "VideoWidget.h"
#include <QtGui/QPaintEvent>

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)//, renderer(new VideoRenderer(this))
{
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // init aspect ratio settings (default values)
    aspect_ratio.num = 16;
    aspect_ratio.den = 9;
    pixel_ratio.num = 1;
    pixel_ratio.den = 1;

    //connect(renderer, SIGNAL(present(const QImage &)), this, SLOT(present(const QImage &)));
}

VideoWidget::~VideoWidget()
{
}

/*VideoRenderer *VideoWidget::GetRenderer() const
{
    return renderer;
}*/

void VideoWidget::SetAspectRatio(openshot::Fraction new_aspect_ratio, openshot::Fraction new_pixel_ratio)
{
	aspect_ratio = new_aspect_ratio;
	pixel_ratio = new_pixel_ratio;
}

QRect VideoWidget::centeredViewport(int width, int height)
{
	// calculate aspect ratio
	float aspectRatio = aspect_ratio.ToFloat() * pixel_ratio.ToFloat();
	int heightFromWidth = (int) (width / aspectRatio);
	int widthFromHeight = (int) (height * aspectRatio);

	if (heightFromWidth <= height) {
		return QRect(0,(height - heightFromWidth) / 2, width, heightFromWidth);
	} else {
		return QRect((width - widthFromHeight) / 2.0, 0, widthFromHeight, height);
  }
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // maintain aspect ratio
    painter.fillRect(event->rect(), palette().window());
    painter.setViewport(centeredViewport(width(), height()));
    painter.drawImage(QRect(0, 0, width(), height()), image);
    QWidget::paintEvent(event);
}

void VideoWidget::present(const QImage &m)
{
    image = m;
    repaint();
}
