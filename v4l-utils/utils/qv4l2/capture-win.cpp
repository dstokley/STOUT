/* qv4l2: a control panel controlling v4l2 devices.
 *
 * Copyright (C) 2006 Hans Verkuil <hverkuil@xs4all.nl>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "capture-win.h"

<<<<<<< HEAD
=======
#undef min
#undef max

>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
#include <QCloseEvent>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>

<<<<<<< HEAD
#define MIN_WIN_SIZE_WIDTH 160
#define MIN_WIN_SIZE_HEIGHT 120
=======
#include <math.h>

#define MIN_WIN_SIZE_WIDTH 16
#define MIN_WIN_SIZE_HEIGHT 12
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d

bool CaptureWin::m_enableScaling = true;
double CaptureWin::m_pixelAspectRatio = 1.0;
CropMethod CaptureWin::m_cropMethod = QV4L2_CROP_NONE;

<<<<<<< HEAD
CaptureWin::CaptureWin() :
	m_curWidth(-1),
	m_curHeight(-1)
=======
CaptureWin::CaptureWin(ApplicationWindow *aw) :
	m_appWin(aw)
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
{
	setWindowTitle("V4L2 Capture");
	m_hotkeyClose = new QShortcut(Qt::CTRL+Qt::Key_W, this);
	connect(m_hotkeyClose, SIGNAL(activated()), this, SLOT(close()));
<<<<<<< HEAD
	m_hotkeyScaleReset = new QShortcut(Qt::CTRL+Qt::Key_F, this);
	connect(m_hotkeyScaleReset, SIGNAL(activated()), this, SLOT(resetSize()));
=======
	connect(new QShortcut(Qt::Key_Q, this), SIGNAL(activated()), this, SLOT(close()));
	m_hotkeyScaleReset = new QShortcut(Qt::CTRL+Qt::Key_F, this);
	connect(m_hotkeyScaleReset, SIGNAL(activated()), this, SLOT(resetSize()));
	connect(aw->m_resetScalingAct, SIGNAL(triggered()), this, SLOT(resetSize()));
	m_hotkeyExitFullscreen = new QShortcut(Qt::Key_Escape, this);
	connect(m_hotkeyExitFullscreen, SIGNAL(activated()), this, SLOT(escape()));
	m_hotkeyToggleFullscreen = new QShortcut(Qt::Key_F, this);
	connect(m_hotkeyToggleFullscreen, SIGNAL(activated()), aw->m_makeFullScreenAct, SLOT(toggle()));
	m_exitFullScreen = new QAction(QIcon(":/fullscreenexit.png"), "Exit Fullscreen", this);
	connect(m_exitFullScreen, SIGNAL(triggered()), this, SLOT(escape()));
	m_enterFullScreen = new QAction(QIcon(":/fullscreen.png"), "Show Fullscreen", this);
	connect(m_enterFullScreen, SIGNAL(triggered()), this, SLOT(fullScreen()));
	m_frame.format = 0;
	m_frame.size.setWidth(0);
	m_frame.size.setHeight(0);
	m_frame.planeData[0] = NULL;
	m_frame.planeData[1] = NULL;
	m_frame.planeData[2] = NULL;
	m_crop.delta.setWidth(0);
	m_crop.delta.setHeight(0);
	m_crop.size.setWidth(0);
	m_crop.size.setHeight(0);
	m_crop.updated = 0;
	m_scaledSize.setWidth(0);
	m_scaledSize.setHeight(0);
	m_origFrameSize.setWidth(0);
	m_origFrameSize.setHeight(0);
	m_windowSize.setWidth(0);
	m_windowSize.setHeight(0);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
}

CaptureWin::~CaptureWin()
{
	if (layout() == NULL)
		return;

	layout()->removeWidget(this);
	delete layout();
	delete m_hotkeyClose;
	delete m_hotkeyScaleReset;
}

<<<<<<< HEAD
void CaptureWin::buildWindow(QWidget *videoSurface)
{
	int l, t, r, b;
	QVBoxLayout *vbox = new QVBoxLayout(this);
	m_information.setText("No Frame");
	vbox->addWidget(videoSurface, 2000);
	vbox->addWidget(&m_information, 1, Qt::AlignBottom);
	vbox->getContentsMargins(&l, &t, &r, &b);
	vbox->setSpacing(b);
=======
void CaptureWin::setFrame(int width, int height, __u32 format,
	  unsigned char *data, unsigned char *data2, unsigned char *data3)
{
	m_frame.planeData[0] = data;
	m_frame.planeData[1] = data2;
	m_frame.planeData[2] = data3;

	m_frame.updated = false;
	if (width != m_frame.size.width() || height != m_frame.size.height()
	    || format != m_frame.format) {
		m_frame.size.setHeight(height);
		m_frame.size.setWidth(width);
		m_frame.format       = format;
		m_frame.updated      = true;
		updateSize();
	}

	setRenderFrame();
}

void CaptureWin::buildWindow(QWidget *videoSurface)
{
	int l, t, r, b;
	m_vboxLayout = new QVBoxLayout(this);
	m_vboxLayout->getContentsMargins(&l, &t, &r, &b);
	m_vboxLayout->setMargin(0);
	m_vboxLayout->addWidget(videoSurface, 1000, Qt::AlignCenter);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customMenuRequested(QPoint)));
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
}

void CaptureWin::resetSize()
{
<<<<<<< HEAD
	if (isMaximized())
		showNormal();

	int w = m_curWidth;
	int h = m_curHeight;
	m_curWidth = -1;
	m_curHeight = -1;
	resize(w, h);
}

int CaptureWin::cropHeight(int width, int height)
{
	double realWidth = width * m_pixelAspectRatio;
	int validHeight;

	switch (m_cropMethod) {
	case QV4L2_CROP_W149:
		validHeight = realWidth / (14.0 / 9.0);
		break;
	case QV4L2_CROP_W169:
		validHeight = realWidth / (16.0 / 9.0);
		break;
	case QV4L2_CROP_C185:
		validHeight = realWidth / 1.85;
		break;
	case QV4L2_CROP_C239:
		validHeight = realWidth / 2.39;
		break;
	case QV4L2_CROP_TB:
		validHeight = height - 2;
		break;
	default:
		return 0;
	}

	if (validHeight < MIN_WIN_SIZE_HEIGHT || validHeight >= height)
		return 0;

	return (height - validHeight) / 2;
}

int CaptureWin::cropWidth(int width, int height)
{
	if (m_cropMethod != QV4L2_CROP_P43)
		return 0;

	int validWidth = (height * 4.0 / 3.0) / m_pixelAspectRatio;

	if (validWidth < MIN_WIN_SIZE_WIDTH || validWidth >= width)
		return 0;

	return (width - validWidth) / 2;
=======
        // Force resize even if no size change
	QSize resetFrameSize = m_origFrameSize;
	m_origFrameSize.setWidth(0);
	m_origFrameSize.setHeight(0);

	setWindowSize(resetFrameSize);
}

QSize CaptureWin::cropSize(QSize size)
{
	QSize croppedSize = size;
	double realWidth = size.width() * m_pixelAspectRatio;
	double realHeight = size.height() / m_pixelAspectRatio;
	double aspectRatio = 1;

	switch (m_cropMethod) {
	case QV4L2_CROP_P43:
		aspectRatio = 4.0 / 3.0;
		break;
	case QV4L2_CROP_W149:
		aspectRatio = 14.0 / 9.0;
		break;
	case QV4L2_CROP_W169:
		aspectRatio = 16.0 / 9.0;
		break;
	case QV4L2_CROP_C185:
		aspectRatio = 1.85;
		break;
	case QV4L2_CROP_C239:
		aspectRatio = 2.39;
		break;
	case QV4L2_CROP_TB:
		croppedSize.setHeight(size.height() - 2);
		break;
	default:
		break;  // No cropping
	}

	if ((m_cropMethod != QV4L2_CROP_TB) && (m_cropMethod != QV4L2_CROP_NONE)) {
		if (realWidth / size.height() < aspectRatio)
			croppedSize.setHeight(realWidth / aspectRatio);
		else
			croppedSize.setWidth(realHeight * aspectRatio);
	}

	if (croppedSize.width() >= size.width())
		croppedSize.setWidth(size.width());
	if (croppedSize.width() < MIN_WIN_SIZE_WIDTH)
		croppedSize.setWidth(MIN_WIN_SIZE_WIDTH);
	if (croppedSize.height() >= size.height())
		croppedSize.setHeight(size.height());
	if (croppedSize.height() < MIN_WIN_SIZE_HEIGHT)
		croppedSize.setHeight(MIN_WIN_SIZE_HEIGHT);

	return croppedSize;
}

void CaptureWin::updateSize()
{
	m_crop.updated = false;
	if (m_frame.updated) {
		m_scaledSize = scaleFrameSize(m_windowSize, m_frame.size);
		m_crop.size = cropSize(m_frame.size);
		m_crop.delta = (m_frame.size - m_crop.size) / 2;
		m_crop.updated = true;
	}
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
}

void CaptureWin::setCropMethod(CropMethod crop)
{
	m_cropMethod = crop;
<<<<<<< HEAD
	QResizeEvent event (QSize(width(), height()), QSize(width(), height()));
	QCoreApplication::sendEvent(this, &event);
}

int CaptureWin::actualFrameWidth(int width)
{
	if (m_enableScaling && m_pixelAspectRatio > 1)
		return width * m_pixelAspectRatio;

	return width;
}

int CaptureWin::actualFrameHeight(int height)
{
	if (m_enableScaling && m_pixelAspectRatio < 1)
		return height / m_pixelAspectRatio;

	return height;
=======
	resetSize();
}

QSize CaptureWin::pixelAspectFrameSize(QSize size)
{
	if (!m_enableScaling)
		return size;

	if (m_pixelAspectRatio > 1)
		size.rwidth() *= m_pixelAspectRatio;

	if (m_pixelAspectRatio < 1)
		size.rheight() /= m_pixelAspectRatio;

	return size;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
}

QSize CaptureWin::getMargins()
{
	int l, t, r, b;
	layout()->getContentsMargins(&l, &t, &r, &b);
<<<<<<< HEAD
	return QSize(l + r, t + b + m_information.minimumSizeHint().height() + layout()->spacing());
=======
	return QSize(l + r, t + b);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
}

void CaptureWin::enableScaling(bool enable)
{
	if (!enable) {
		QSize margins = getMargins();
<<<<<<< HEAD
		QWidget::setMinimumSize(m_curWidth + margins.width(), m_curHeight + margins.height());
=======
		QWidget::setMinimumSize(m_origFrameSize.width() + margins.width(),
					m_origFrameSize.height() + margins.height());
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
	} else {
		QWidget::setMinimumSize(MIN_WIN_SIZE_WIDTH, MIN_WIN_SIZE_HEIGHT);
	}
	m_enableScaling = enable;
<<<<<<< HEAD
	QResizeEvent event (QSize(width(), height()), QSize(width(), height()));
	QCoreApplication::sendEvent(this, &event);
}

void CaptureWin::resize(int width, int height)
{
	int h, w;

	// Dont resize window if the frame size is the same in
	// the event the window has been paused when beeing resized.
	if (width == m_curWidth && height == m_curHeight)
		return;

	m_curWidth = width;
	m_curHeight = height;

	QSize margins = getMargins();
	h = margins.height() - cropHeight(width, height) * 2 + actualFrameHeight(height);
	w = margins.width() - cropWidth(width, height) * 2 + actualFrameWidth(width);
	height = h;
	width = w;

	QDesktopWidget *screen = QApplication::desktop();
	QRect resolution = screen->screenGeometry();

	if (width > resolution.width())
		width = resolution.width();
	if (width < MIN_WIN_SIZE_WIDTH)
		width = MIN_WIN_SIZE_WIDTH;

	if (height > resolution.height())
		height = resolution.height();
	if (height < MIN_WIN_SIZE_HEIGHT)
		height = MIN_WIN_SIZE_HEIGHT;

	QWidget::setMinimumSize(MIN_WIN_SIZE_WIDTH, MIN_WIN_SIZE_HEIGHT);
	QWidget::resize(width, height);
=======
	resetSize();
}

void CaptureWin::setWindowSize(QSize frameSize)
{
	// Dont resize window if the frame size is the same in
	// the event the window has been paused when beeing resized.
	if (frameSize == m_origFrameSize)
		return;

	m_origFrameSize = frameSize;

	QSize margins = getMargins();
	QDesktopWidget *screen = QApplication::desktop();
	QRect resolution = screen->screenGeometry();

	QSize windowSize =  pixelAspectFrameSize(cropSize(frameSize)) + margins;

	if (windowSize.width() > resolution.width())
		windowSize.setWidth(resolution.width());
	if (windowSize.width() < MIN_WIN_SIZE_WIDTH)
		windowSize.setWidth(MIN_WIN_SIZE_WIDTH);

	if (windowSize.height() > resolution.height())
		windowSize.setHeight(resolution.height());
	if (windowSize.height() < MIN_WIN_SIZE_HEIGHT)
		windowSize.setHeight(MIN_WIN_SIZE_HEIGHT);

	QWidget::setMinimumSize(MIN_WIN_SIZE_WIDTH, MIN_WIN_SIZE_HEIGHT);

	m_frame.size = frameSize;

	QWidget::resize(windowSize);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
}

QSize CaptureWin::scaleFrameSize(QSize window, QSize frame)
{
<<<<<<< HEAD
	int actualWidth = actualFrameWidth(frame.width() - cropWidth(frame.width(), frame.height()) * 2);
	int actualHeight = actualFrameHeight(frame.height() - cropHeight(frame.width(), frame.height()) * 2);

	if (!m_enableScaling) {
		window.setWidth(actualWidth);
		window.setHeight(actualHeight);
	}

	double newW, newH;
	if (window.width() >= window.height()) {
		newW = (double)window.width() / actualWidth;
		newH = (double)window.height() / actualHeight;
	} else {
		newH = (double)window.width() / actualWidth;
		newW = (double)window.height() / actualHeight;
	}
	double resized = std::min(newW, newH);

	return QSize((int)(actualWidth * resized), (int)(actualHeight * resized));
=======
	QSize actualSize = pixelAspectFrameSize(cropSize(frame));

	if (!m_enableScaling) {
		window.setWidth(actualSize.width());
		window.setHeight(actualSize.height());
	}

	qreal newW, newH;
	if (window.width() >= window.height()) {
		newW = (qreal)window.width() / actualSize.width();
		newH = (qreal)window.height() / actualSize.height();
	} else {
		newH = (qreal)window.width() / actualSize.width();
		newW = (qreal)window.height() / actualSize.height();
	}
	qreal resized = (qreal)std::min(newW, newH);

	return (actualSize * resized);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
}

void CaptureWin::setPixelAspectRatio(double ratio)
{
	m_pixelAspectRatio = ratio;
<<<<<<< HEAD
	QResizeEvent event(QSize(width(), height()), QSize(width(), height()));
	QCoreApplication::sendEvent(this, &event);
=======
	resetSize();
}

float CaptureWin::getHorScaleFactor()
{
	float ow, sw, wscale;

	sw = m_scaledSize.width();
	ow = m_origFrameSize.width();
	wscale = floor(100 * (sw / ow)) / 100.0;

	return wscale;
}

float CaptureWin::getVertScaleFactor()
{
	float oh, sh, hscale;

	sh = m_scaledSize.height();
	oh = m_origFrameSize.height();
	hscale = floor(100 * (sh / oh)) / 100.0;

	return hscale;
}

void CaptureWin::mouseDoubleClickEvent(QMouseEvent *e)
{
	m_appWin->m_makeFullScreenAct->toggle();
}

void CaptureWin::escape()
{
	m_appWin->m_makeFullScreenAct->setChecked(false);
}

void CaptureWin::fullScreen()
{
	m_appWin->m_makeFullScreenAct->setChecked(true);
}

void CaptureWin::makeFullScreen(bool enable)
{
	if (enable) {
		showFullScreen();
		setStyleSheet("background-color:#000000;");
	} else {
		showNormal();
		setStyleSheet("background-color:none;");
	}
	QSize resetFrameSize = m_origFrameSize;
	m_origFrameSize.setWidth(0);
	m_origFrameSize.setHeight(0);

	setWindowSize(resetFrameSize);
}

void CaptureWin::customMenuRequested(QPoint pos)
{
	QMenu *menu = new QMenu(this);
	
	if (isFullScreen()) {
		menu->addAction(m_exitFullScreen);
		menu->setStyleSheet("background-color:none;");
	} else {
		menu->addAction(m_enterFullScreen);
	}
	
	menu->addAction(m_appWin->m_resetScalingAct);
	if (m_appWin->m_useBlendingAct)
		menu->addAction(m_appWin->m_useBlendingAct);
	if (m_appWin->m_useLinearAct)
		menu->addAction(m_appWin->m_useLinearAct);
	menu->addAction(m_appWin->m_snapshotAct);
	menu->addAction(m_appWin->m_showFramesAct);
	menu->addMenu(m_appWin->m_overrideColorspaceMenu);
	menu->addMenu(m_appWin->m_overrideXferFuncMenu);
	menu->addMenu(m_appWin->m_overrideYCbCrEncMenu);
	menu->addMenu(m_appWin->m_overrideQuantizationMenu);
	
	menu->popup(mapToGlobal(pos));
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
}

void CaptureWin::closeEvent(QCloseEvent *event)
{
	QWidget::closeEvent(event);
	emit close();
}
