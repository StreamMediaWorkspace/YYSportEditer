/**
 * @file
 * @brief Header file for demo application for QtPlayer class
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

#ifndef OPENSHOT_PLAYER_DEMO_H
#define OPENSHOT_PLAYER_DEMO_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <thread>
#include <QtGui/qevent.h>
#include <QApplication>
#include <PlayerBase.h>

#include "VideoWidget.h"

// Define the QtPlayer without including it (due to build issues with Qt moc / Qt macros)
namespace openshot
{
    class QtPlayer;
    class FFmpegReader;
    class Timeline;
    class ReaderInfo;
}

class PlayerDemo : public QWidget
{
    Q_OBJECT

public:
    PlayerDemo(QWidget *parent = 0);
    ~PlayerDemo();

    void setPosition(int pos);
    void open(const std::string &source);

    void openInCache(const std::string &source,
                     openshot::Timeline **pTimeline,
                     openshot::ReaderInfo &info);

signals:
	void PositionChanged(uint64);
    void ModeChanged(openshot::PlaybackMode);

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void open(bool checked);

private:
	struct LockDeleter {
	   void operator()(void *p) {
		   std::thread *pThread = (std::thread*)p;
		  if (pThread) {
			  pThread->join();
			  delete pThread;
			  pThread = nullptr;
			  std::cout<<"thread end"<<std::endl;
		  }
	   }
	};

	static void loopPositionThread(PlayerDemo *p);

private:
    QVBoxLayout *vbox = nullptr;
    QMenuBar *menu = nullptr;
    VideoWidget *video = nullptr;
    openshot::QtPlayer *player = nullptr;

    openshot::Timeline *m_timeline = nullptr;

    uint64 m_frameNumber = 0;

	std::unique_ptr<std::thread, LockDeleter> m_positionThread = nullptr;
	bool m_stop_positionThread = true;
};

#endif // OPENSHOT_PLAYER_H
