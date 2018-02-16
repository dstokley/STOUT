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

#ifndef CAPTURE_WIN_H
#define CAPTURE_WIN_H

#include "qv4l2.h"

#include <QWidget>
#include <QShortcut>
#include <QLabel>
<<<<<<< HEAD
<<<<<<< HEAD
#include <QPushButton>
#include <QMenu>
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
#include <QPushButton>
#include <QMenu>
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

enum CropMethod {
	// Crop Height
	QV4L2_CROP_NONE,
	QV4L2_CROP_W149,
	QV4L2_CROP_W169,
	QV4L2_CROP_C185,
	QV4L2_CROP_C239,
	QV4L2_CROP_TB,

	// Crop Width
	QV4L2_CROP_P43,
};

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
struct frame {
	__u32 format;
	QSize size;        // int   frameHeight; int   frameWidth;
	unsigned char *planeData[3];
	bool updated;
};

struct crop {              // cropInfo
	QSize delta;       // int cropH; int cropW;
	QSize size;        // int height; int width;
	bool updated;
};

class ApplicationWindow;

<<<<<<< HEAD
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
class CaptureWin : public QWidget
{
	Q_OBJECT

public:
<<<<<<< HEAD
<<<<<<< HEAD
=======
	CaptureWin();
	~CaptureWin();

	void resize(int minw, int minh);
	void enableScaling(bool enable);
	void setPixelAspectRatio(double ratio);
	void setCropMethod(CropMethod crop);
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	CaptureWin(ApplicationWindow *aw);
	~CaptureWin();

	void setWindowSize(QSize size);
	void enableScaling(bool enable);
	void setPixelAspectRatio(double ratio);
	float getHorScaleFactor();
	float getVertScaleFactor();
	virtual void setColorspace(unsigned colorspace, unsigned xfer_func,
			unsigned ycbcr_enc, unsigned quantization, bool is_sdtv) = 0;
	virtual void setField(unsigned field) = 0;
	virtual void setBlending(bool enable) = 0;
	virtual void setLinearFilter(bool enable) = 0;
	void setCropMethod(CropMethod crop);
	void makeFullScreen(bool);
	QAction *m_exitFullScreen;
	QAction *m_enterFullScreen;
<<<<<<< HEAD
=======
	CaptureWin();
	~CaptureWin();

	void resize(int minw, int minh);
	void enableScaling(bool enable);
	void setPixelAspectRatio(double ratio);
	void setCropMethod(CropMethod crop);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	/**
	 * @brief Set a frame into the capture window.
	 *
	 * When called the capture stream is
	 * either already running or starting for the first time.
	 *
	 * @param width Frame width in pixels
	 * @param height Frame height in pixels
	 * @param format The frame's format, given as a V4L2_PIX_FMT.
	 * @param data The frame data.
	 * @param info A string containing capture information.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	void setFrame(int width, int height, __u32 format,
		      unsigned char *data, unsigned char *data2, unsigned char *data3);
=======
	virtual void setFrame(int width, int height, __u32 format,
			      unsigned char *data, unsigned char *data2, const QString &info) = 0;
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	virtual void setFrame(int width, int height, __u32 format,
			      unsigned char *data, unsigned char *data2, const QString &info) = 0;
=======
	void setFrame(int width, int height, __u32 format,
		      unsigned char *data, unsigned char *data2, unsigned char *data3);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	/**
	 * @brief Called when the capture stream is stopped.
	 */
	virtual void stop() = 0;

	/**
	 * @brief Queries the current capture window for its supported formats.
	 *
	 * Unsupported formats are converted by v4lconvert_convert().
	 *
	 * @param format The frame format question, given as a V4L2_PIX_FMT.
	 * @return true if the format is supported, false if not.
	 */
	virtual bool hasNativeFormat(__u32 format) = 0;

	/**
	 * @brief Defines wether a capture window is supported.
	 *
	 * By default nothing is supported, but derived classes can override this.
	 *
	 * @return true if the capture window is supported on the system, false if not.
	 */
	static bool isSupported() { return false; }

	/**
	 * @brief Return the scaled size.
	 *
	 * Scales a frame to fit inside a given window. Preserves aspect ratio.
	 *
	 * @param window The window the frame shall scale into
	 * @param frame The frame to scale
	 * @return The scaledsizes to use for the frame
	 */
	static QSize scaleFrameSize(QSize window, QSize frame);

	/**
<<<<<<< HEAD
<<<<<<< HEAD
	 * @brief Crop size
	 *
	 * Reduces size width or height according to m_cropMethod
	 *
	 * @param size Input size
	 * @return Cropped size
	 *
	 */
	static QSize cropSize(QSize size);

	/**
	 * @brief Get the frame size when aspect ratio is applied and increases size.
	 *
	 * @param size The original frame size.
	 * @return The new size with aspect ratio correction (scaling must be enabled).
	 */
	static QSize pixelAspectFrameSize(QSize size);

public slots:
	void resetSize();
	void customMenuRequested(QPoint pos);

private slots:
	void escape();
	void fullScreen();

protected:
	void closeEvent(QCloseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *e);

	/**
	 * @brief Get the amount of space outside the video frame.
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	 * @brief Get the number of pixels to crop.
	 *
	 * When cropping is applied this gives the number of pixels to
	 * remove from top and bottom. To get total multiply the return
	 * value by 2.
	 *
	 * @param width Frame width
	 * @param height Frame height
	 * @return The pixels to remove when cropping height
	 *
	 * @note The width and height must be original frame size
	 *       to ensure that the cropping is done correctly.
	 */
	static int cropHeight(int width, int height);
	static int cropWidth(int width, int height);

	/**
	 * @brief Get the frame width when aspect ratio is applied if ratio > 1.
	 *
	 * @param width The original frame width.
	 * @return The width with aspect ratio correction (scaling must be enabled).
	 */
	static int actualFrameWidth(int width);

	/**
	 * @brief Get the frame height when aspect ratio is applied if ratio < 1.
	 *
	 * @param width The original frame width.
	 * @return The width with aspect ratio correction (scaling must be enabled).
	 */
	static int actualFrameHeight(int height);

public slots:
	void resetSize();

protected:
	void closeEvent(QCloseEvent *event);

	/**
	 * @brief Get the amout of space outside the video frame.
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	 * @brief Crop size
	 *
	 * Reduces size width or height according to m_cropMethod
	 *
	 * @param size Input size
	 * @return Cropped size
	 *
	 */
	static QSize cropSize(QSize size);

	/**
	 * @brief Get the frame size when aspect ratio is applied and increases size.
	 *
	 * @param size The original frame size.
	 * @return The new size with aspect ratio correction (scaling must be enabled).
	 */
	static QSize pixelAspectFrameSize(QSize size);

public slots:
	void resetSize();
	void customMenuRequested(QPoint pos);

private slots:
	void escape();
	void fullScreen();

protected:
	void closeEvent(QCloseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *e);

	/**
	 * @brief Get the amount of space outside the video frame.
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	 *
	 * The margins are that of the window that encloses the displaying
	 * video frame. The sizes are total in both width and height.
	 *
	 * @return The margins around the video frame.
	 */
	QSize getMargins();

	/**
	 * @brief Creates the content of the window.
	 *
	 * Construct the new window layout and adds the video display surface.
	 * @param videoSurface The widget that contains the renderer.
	 */
	void buildWindow(QWidget *videoSurface);

	/**
<<<<<<< HEAD
<<<<<<< HEAD
=======
	 * @brief A label that can is used to display capture information.
	 *
	 * @note This must be set in the derived class' setFrame() function.
	 */
	QLabel m_information;
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	 * @brief Calculate source size after pixel aspect scaling and cropping
	 *
	 */
	void updateSize();

	/**
	 * @brief Frame information.
	 *
	 * @note Set and accessed from derived render dependent classes.
	 */
	struct frame m_frame;
	struct crop  m_crop;
	QSize m_origFrameSize;  // int m_sourceWinWidth; int m_sourceWinHeight;
	QSize m_windowSize;     // int m_curWinWidth; int m_curWinHeight;
	QSize m_scaledSize;

	/**
	 * @brief Update frame information to renderer.
	 *
	 * @note Must be implemented by derived render dependent classes.
	 */
	virtual void setRenderFrame() = 0;
<<<<<<< HEAD
=======
	 * @brief A label that can is used to display capture information.
	 *
	 * @note This must be set in the derived class' setFrame() function.
	 */
	QLabel m_information;
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	/**
	 * @brief Determines if scaling is to be applied to video frame.
	 */
	static bool m_enableScaling;

signals:
	void close();

private:
<<<<<<< HEAD
<<<<<<< HEAD
	ApplicationWindow *m_appWin;
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	ApplicationWindow *m_appWin;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	static double m_pixelAspectRatio;
	static CropMethod m_cropMethod;
	QShortcut *m_hotkeyClose;
	QShortcut *m_hotkeyScaleReset;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	int m_curWidth;
	int m_curHeight;
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	QShortcut *m_hotkeyExitFullscreen;
	QShortcut *m_hotkeyToggleFullscreen;
	QVBoxLayout *m_vboxLayout;
	unsigned m_vboxSpacing;
<<<<<<< HEAD
=======
	int m_curWidth;
	int m_curHeight;
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
};
#endif
