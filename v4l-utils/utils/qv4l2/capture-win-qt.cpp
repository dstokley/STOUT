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

#include "capture-win-qt.h"

<<<<<<< HEAD
CaptureWinQt::CaptureWinQt(ApplicationWindow *aw) :
	CaptureWin(aw),
	m_image(new QImage(0, 0, QImage::Format_Invalid)),
	m_data(NULL),
	m_supportedFormat(false),
	m_filled(false),
	m_cropBytes(0),
	m_cropOffset(0)
{
	m_videoSurface = new QLabel(this);
	CaptureWin::buildWindow(m_videoSurface);
=======
CaptureWinQt::CaptureWinQt() :
	m_frame(new QImage(0, 0, QImage::Format_Invalid)),
	m_data(NULL),
	m_supportedFormat(false),
	m_filled(false)
{

	CaptureWin::buildWindow(&m_videoSurface);
	m_scaledSize.setWidth(0);
	m_scaledSize.setHeight(0);
	m_crop.cropH  = 0;
	m_crop.cropW  = 0;
	m_crop.height = 0;
	m_crop.width  = 0;
	m_crop.offset = 0;
	m_crop.bytes  = 0;
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
}

CaptureWinQt::~CaptureWinQt()
{
<<<<<<< HEAD
	delete m_image;
=======
	delete m_frame;
}

void CaptureWinQt::resizeScaleCrop()
{
	m_scaledSize = scaleFrameSize(QSize(m_videoSurface.width(), m_videoSurface.height()),
				      QSize(m_frame->width(), m_frame->height()));

	if (!m_crop.bytes || m_crop.cropH != cropHeight(m_frame->width(), m_frame->height())
	    || m_crop.cropW != cropWidth(m_frame->width(), m_frame->height())) {

		m_crop.cropH  = cropHeight(m_frame->width(), m_frame->height());
		m_crop.cropW  = cropWidth(m_frame->width(), m_frame->height());
		m_crop.height = m_frame->height() - (m_crop.cropH * 2);
		m_crop.width  = m_frame->width() - (m_crop.cropW * 2);
		m_crop.offset = m_crop.cropH * (m_frame->depth() / 8) * m_frame->width()
			+ m_crop.cropW * (m_frame->depth() / 8);

		// Even though the values above can be valid, it might be that there is no
		// data at all. This makes sure that it is.
		m_crop.bytes = m_crop.height * m_crop.width * (m_frame->depth() / 8);
	}
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
}

void CaptureWinQt::resizeEvent(QResizeEvent *event)
{
<<<<<<< HEAD
	// Get size of frame viewport.
	QSize margins = getMargins();
	m_windowSize = size() - margins;
	// Re-calculate sizes
	m_frame.updated = true;
	CaptureWin::updateSize();
	// Draw
	paintFrame();
	event->accept();
}

void CaptureWinQt::setRenderFrame()
{
	// Get/copy (TODO: use direct?)
	m_data = m_frame.planeData[0];

	QImage::Format dstFmt;
	m_supportedFormat = findNativeFormat(m_frame.format, dstFmt);
	if (!m_supportedFormat)
		dstFmt = QImage::Format_RGB888;

	if (m_frame.updated || m_image->format() != dstFmt ||
	    m_image->width() != m_frame.size.width() ||
	    m_image->height() != m_frame.size.height()) {
		delete m_image;
		m_image = new QImage(m_frame.size.width(),
				     m_frame.size.height(),
				     dstFmt);
	}

	m_frame.updated = false;

=======
	resizeScaleCrop();
	paintFrame();
}

void CaptureWinQt::setFrame(int width, int height, __u32 format,
		unsigned char *data, unsigned char *data2, const QString &info)
{
	m_data = data;

	QImage::Format dstFmt;
	m_supportedFormat = findNativeFormat(format, dstFmt);
	if (!m_supportedFormat)
		dstFmt = QImage::Format_RGB888;

	if (m_frame->width() != width
	    || m_frame->height() != height
	    || m_frame->format() != dstFmt) {
		delete m_frame;
		m_frame = new QImage(width, height, dstFmt);
		// Force a recalculation by setting this to 0.
		m_crop.bytes = 0;

		resizeScaleCrop();
	}

	m_information.setText(info);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
	paintFrame();
}

void CaptureWinQt::paintFrame()
{
<<<<<<< HEAD
	if (m_crop.updated) {
		m_cropOffset = m_crop.delta.height() * (m_image->depth() / 8)
			* m_frame.size.width()
			+ m_crop.delta.width() * (m_image->depth() / 8);

		// Even though the values above can be valid, it might be that
		// there is no data at all. This makes sure that it is.
		m_cropBytes =  m_crop.size.width() * m_crop.size.height()
			* (m_image->depth() / 8);
		m_crop.updated = false;
	}

	if (!m_supportedFormat || !m_cropBytes) {
		if (!m_filled) {
			m_filled = true;
			m_image->fill(0);
			QPixmap img = QPixmap::fromImage(*m_image);
			m_videoSurface->setPixmap(img);
=======
	if (!m_supportedFormat || !m_crop.bytes) {
		if (!m_filled) {
			m_filled = true;
			m_frame->fill(0);
			QPixmap img = QPixmap::fromImage(*m_frame);
			m_videoSurface.setPixmap(img);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
		}
		return;
	}
	m_filled = false;

<<<<<<< HEAD
	unsigned char *data = (m_data == NULL) ? m_image->bits() : m_data;

	QImage displayFrame(&data[m_cropOffset],
			    m_crop.size.width(), m_crop.size.height(),
			    m_image->width() * (m_image->depth() / 8),
			    m_image->format());
=======
	unsigned char *data = (m_data == NULL) ? m_frame->bits() : m_data;

	QImage displayFrame(&data[m_crop.offset], m_crop.width, m_crop.height,
			    m_frame->width() * (m_frame->depth() / 8), m_frame->format());
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2

	QPixmap img = QPixmap::fromImage(displayFrame);

	// No scaling is performed by scaled() if the scaled size is equal to original size
	img = img.scaled(m_scaledSize.width(), m_scaledSize.height(), Qt::IgnoreAspectRatio);

<<<<<<< HEAD
	m_videoSurface->setPixmap(img);
=======
	m_videoSurface.setPixmap(img);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
}

void CaptureWinQt::stop()
{
	if (m_data != NULL)
<<<<<<< HEAD
#if QT_VERSION >= 0x050000
		memcpy(m_image->bits(), m_data, m_image->byteCount());
#else
		memcpy(m_image->bits(), m_data, m_image->numBytes());
#endif
=======
		memcpy(m_frame->bits(), m_data, m_frame->numBytes());
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
	m_data = NULL;
}

bool CaptureWinQt::hasNativeFormat(__u32 format)
{
	QImage::Format fmt;
	return findNativeFormat(format, fmt);
}

bool CaptureWinQt::findNativeFormat(__u32 format, QImage::Format &dstFmt)
{
	static const struct {
		__u32 v4l2_pixfmt;
		QImage::Format qt_pixfmt;
	} supported_fmts[] = {
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
		{ V4L2_PIX_FMT_RGB32, QImage::Format_RGB32 },
<<<<<<< HEAD
		{ V4L2_PIX_FMT_XRGB32, QImage::Format_RGB32 },
		{ V4L2_PIX_FMT_ARGB32, QImage::Format_ARGB32 },
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
		{ V4L2_PIX_FMT_RGB24, QImage::Format_RGB888 },
		{ V4L2_PIX_FMT_RGB565X, QImage::Format_RGB16 },
		{ V4L2_PIX_FMT_RGB555X, QImage::Format_RGB555 },
#else
		{ V4L2_PIX_FMT_BGR32, QImage::Format_RGB32 },
<<<<<<< HEAD
		{ V4L2_PIX_FMT_XBGR32, QImage::Format_RGB32 },
		{ V4L2_PIX_FMT_ABGR32, QImage::Format_ARGB32 },
		{ V4L2_PIX_FMT_RGB24, QImage::Format_RGB888 },
		{ V4L2_PIX_FMT_RGB565, QImage::Format_RGB16 },
		{ V4L2_PIX_FMT_RGB555, QImage::Format_RGB555 },
		{ V4L2_PIX_FMT_XRGB555, QImage::Format_RGB555 },
		{ V4L2_PIX_FMT_RGB444, QImage::Format_RGB444 },
		{ V4L2_PIX_FMT_XRGB444, QImage::Format_RGB444 },
=======
		{ V4L2_PIX_FMT_RGB24, QImage::Format_RGB888 },
		{ V4L2_PIX_FMT_RGB565, QImage::Format_RGB16 },
		{ V4L2_PIX_FMT_RGB555, QImage::Format_RGB555 },
		{ V4L2_PIX_FMT_RGB444, QImage::Format_RGB444 },
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
#endif
		{ 0, QImage::Format_Invalid }
	};

	for (int i = 0; supported_fmts[i].v4l2_pixfmt; i++) {
		if (supported_fmts[i].v4l2_pixfmt == format) {
			dstFmt = supported_fmts[i].qt_pixfmt;
			return true;
		}
	}
	return false;
}
