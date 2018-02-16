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

#ifndef QV4L2_H
#define QV4L2_H

#include <config.h>

#include <QMainWindow>
#include <QTabWidget>
#include <QSignalMapper>
#include <QLabel>
#include <QGridLayout>
#include <QSocketNotifier>
#include <QImage>
#include <QFileDialog>
#include <map>
#include <vector>

<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "v4l2-api.h"
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
// Must come before cv4l-helpers.h
#include <libv4l2.h>

extern "C" {
#include <v4l2-tpg.h>
}
#include "cv4l-helpers.h"
<<<<<<< HEAD
=======
#include "v4l2-api.h"
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
#include "raw2sliced.h"
#include "capture-win.h"

class QComboBox;
class QSpinBox;
<<<<<<< HEAD
<<<<<<< HEAD
class QCheckBox;
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
class QCheckBox;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
class GeneralTab;
class VbiTab;
class QCloseEvent;
class CaptureWin;

typedef std::vector<unsigned> ClassIDVec;
typedef std::map<unsigned, ClassIDVec> ClassMap;
<<<<<<< HEAD
<<<<<<< HEAD
typedef std::map<unsigned, struct v4l2_query_ext_ctrl> CtrlMap;
=======
typedef std::map<unsigned, struct v4l2_queryctrl> CtrlMap;
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
typedef std::map<unsigned, struct v4l2_queryctrl> CtrlMap;
=======
typedef std::map<unsigned, struct v4l2_query_ext_ctrl> CtrlMap;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
typedef std::map<unsigned, QWidget *> WidgetMap;

enum {
	CTRL_UPDATE_ON_CHANGE = 0x10,
	CTRL_DEFAULTS,
	CTRL_REFRESH,
	CTRL_UPDATE
};

enum CapMethod {
	methodRead,
	methodMmap,
	methodUser
};

enum RenderMethod {
	QV4L2_RENDER_GL,
	QV4L2_RENDER_QT
};

struct buffer {
	unsigned planes;
	void   *start[VIDEO_MAX_PLANES];
	size_t  length[VIDEO_MAX_PLANES];
<<<<<<< HEAD
<<<<<<< HEAD
	bool clear;
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	bool clear;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
};

#define CTRL_FLAG_DISABLED	(V4L2_CTRL_FLAG_READ_ONLY | \
				 V4L2_CTRL_FLAG_INACTIVE | \
				 V4L2_CTRL_FLAG_GRABBED)

<<<<<<< HEAD
<<<<<<< HEAD
class CaptureWin;

class ApplicationWindow: public QMainWindow, cv4l_fd
=======
class ApplicationWindow: public QMainWindow, public v4l2
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
{
	Q_OBJECT

=======
class CaptureWin;

class ApplicationWindow: public QMainWindow, cv4l_fd
{
	Q_OBJECT

<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	friend class CaptureWin;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
public:
	ApplicationWindow();
	virtual ~ApplicationWindow();

private slots:
	void closeDevice();
	void closeCaptureWin();

public:
	void setDevice(const QString &device, bool rawOpen);

	// capturing
private:
	CaptureWin *m_capture;

<<<<<<< HEAD
<<<<<<< HEAD
	bool startStreaming();
	void stopStreaming();
	void newCaptureWin();
	void startAudio();
	void stopAudio();
	bool startOutput();
	void stopOutput();

	bool m_clear[64];
	cv4l_fmt m_capSrcFormat;
	cv4l_fmt m_capDestFormat;
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	bool startCapture(unsigned buffer_size);
	void stopCapture();
	void startOutput(unsigned buffer_size);
	void stopOutput();
	void newCaptureWin();
	void startAudio();
	void stopAudio();

	struct buffer *m_buffers;
	struct v4l2_format m_capSrcFormat;
	struct v4l2_format m_capDestFormat;
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	bool startStreaming();
	void stopStreaming();
	void newCaptureWin();
	void startAudio();
	void stopAudio();
	bool startOutput();
	void stopOutput();

	bool m_clear[64];
	cv4l_fmt m_capSrcFormat;
	cv4l_fmt m_capDestFormat;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	unsigned char *m_frameData;
	unsigned m_nbuffers;
	struct v4lconvert_data *m_convertData;
	bool m_mustConvert;
	CapMethod m_capMethod;
	bool m_makeSnapshot;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	RenderMethod m_renderMethod;

private slots:
	void capStart(bool);
	void capFrame();
	void ctrlEvent();
	void snapshot();
	void capVbiFrame();
	void saveRaw(bool);
	void setRenderMethod();
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	bool m_singleStep;
	RenderMethod m_renderMethod;
	int m_overrideColorspace;
	int m_overrideXferFunc;
	int m_overrideYCbCrEnc;
	int m_overrideQuantization;

private slots:
	void capStart(bool);
	void capStep(bool);
	void outStart(bool);
	void makeFullScreen(bool);
	void capFrame();
	void outFrame();
	void ctrlEvent();
	void snapshot();
	void capVbiFrame();
	void capSdrFrame();
	void saveRaw(bool);
	void setRenderMethod(bool);
	void setBlending(bool);
	void setLinearFilter(bool);
	void traceIoctls(bool);
<<<<<<< HEAD
=======
	RenderMethod m_renderMethod;

private slots:
	void capStart(bool);
	void capFrame();
	void ctrlEvent();
	void snapshot();
	void capVbiFrame();
	void saveRaw(bool);
	void setRenderMethod();
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	void changeAudioDevice();

	// gui
private slots:
	void opendev();
	void openrawdev();
	void ctrlAction(int);
	void openRawFile(const QString &s);
	void rejectedRawFile();
	void setAudioBufferSize();
	void enableScaling(bool enable);
	void updatePixelAspectRatio();
	void updateCropping();
<<<<<<< HEAD
<<<<<<< HEAD
=======

	void about();
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	void clearBuffers();
	void about();
	void overrideColorspaceChanged(QAction *a);
	void overrideXferFuncChanged(QAction *a);
	void overrideYCbCrEncChanged(QAction *a);
	void overrideQuantChanged(QAction *a);

	// tpg
private slots:
	void testPatternChanged(int val);
	void horMovementChanged(int val);
	void vertMovementChanged(int val);
	void showBorderChanged(int val);
	void showSquareChanged(int val);
	void insSAVChanged(int val);
	void insEAVChanged(int val);
	void videoAspectRatioChanged(int val);
	void limRGBRangeChanged(int val);
	void fillPercentageChanged(int val);
	void alphaComponentChanged(int val);
	void applyToRedChanged(int val);
	__u32 tpgDefaultColorspace();
	void tpgColorspaceChanged();
<<<<<<< HEAD
=======

	void about();
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

public:
	virtual void error(const QString &text);
	void error(int err);
	void errorCtrl(unsigned id, int err);
	void errorCtrl(unsigned id, int err, long long v);
	void errorCtrl(unsigned id, int err, const QString &v);
	void info(const QString &info);
	virtual void closeEvent(QCloseEvent *event);
<<<<<<< HEAD
<<<<<<< HEAD
=======

private:
	void addWidget(QGridLayout *grid, QWidget *w, Qt::Alignment align = Qt::AlignLeft);
	void addLabel(QGridLayout *grid, const QString &text, Qt::Alignment align = Qt::AlignRight)
	{
		addWidget(grid, new QLabel(text, parentWidget()), align);
	}
	void addTabs();
	void finishGrid(QGridLayout *grid, unsigned ctrl_class);
	void addCtrl(QGridLayout *grid, const struct v4l2_queryctrl &qctrl);
	void updateCtrl(unsigned id);
	void refresh(unsigned ctrl_class);
	void refresh();
	void makeSnapshot(unsigned char *buf, unsigned size);
	void setDefaults(unsigned ctrl_class);
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	void updateLimRGBRange();
	void updateColorspace();
	QAction *m_resetScalingAct;
	QAction *m_useBlendingAct;
	QAction *m_useLinearAct;
	QAction *m_snapshotAct;
	QAction *m_showFramesAct;
	QMenu *m_overrideColorspaceMenu;
	QMenu *m_overrideXferFuncMenu;
	QMenu *m_overrideYCbCrEncMenu;
	QMenu *m_overrideQuantizationMenu;

private:
	void addWidget(QGridLayout *grid, QWidget *w, Qt::Alignment align = Qt::AlignLeft);
	void addLabel(QGridLayout *grid, const QString &text, Qt::Alignment align = Qt::AlignLeft)
	{
		addWidget(grid, new QLabel(text, parentWidget()), align);
	}
	void fixWidth(QGridLayout *grid);
	void addTabs(int m_winWidth);
	void addTpgTab(int m_winWidth);
	void finishGrid(QGridLayout *grid, unsigned which);
	void addCtrl(QGridLayout *grid, const struct v4l2_query_ext_ctrl &qec);
	void updateCtrl(unsigned id);
	void updateCtrlRange(unsigned id, __s32 val);
	void subscribeCtrlEvents();
	void refresh(unsigned which);
	void refresh();
	void calculateFps();
	void makeSnapshot(unsigned char *buf, unsigned size);
	void setDefaults(unsigned which);
<<<<<<< HEAD
=======

private:
	void addWidget(QGridLayout *grid, QWidget *w, Qt::Alignment align = Qt::AlignLeft);
	void addLabel(QGridLayout *grid, const QString &text, Qt::Alignment align = Qt::AlignRight)
	{
		addWidget(grid, new QLabel(text, parentWidget()), align);
	}
	void addTabs();
	void finishGrid(QGridLayout *grid, unsigned ctrl_class);
	void addCtrl(QGridLayout *grid, const struct v4l2_queryctrl &qctrl);
	void updateCtrl(unsigned id);
	void refresh(unsigned ctrl_class);
	void refresh();
	void makeSnapshot(unsigned char *buf, unsigned size);
	void setDefaults(unsigned ctrl_class);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	int getVal(unsigned id);
	long long getVal64(unsigned id);
	QString getString(unsigned id);
	void setVal(unsigned id, int v);
	void setVal64(unsigned id, long long v);
	void setString(unsigned id, const QString &v);
	QString getCtrlFlags(unsigned flags);
	void setWhat(QWidget *w, unsigned id, const QString &v);
	void setWhat(QWidget *w, unsigned id, long long v);
	void updateVideoInput();
	void updateVideoOutput();
	void updateAudioInput();
	void updateAudioOutput();
	void updateStandard();
	void updateFreq();
	void updateFreqChannel();
	bool showFrames();

<<<<<<< HEAD
<<<<<<< HEAD
=======
	GeneralTab *m_genTab;
	VbiTab *m_vbiTab;
	QAction *m_capStartAct;
	QAction *m_snapshotAct;
	QAction *m_saveRawAct;
	QAction *m_showFramesAct;
	QAction *m_useGLAct;
	QAction *m_showAllAudioAct;
	QAction *m_audioBufferAct;
	QAction *m_scalingAct;
	QAction *m_resetScalingAct;
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	// tpg
	struct tpg_data m_tpg;
	v4l2_std_id m_tpgStd;
	unsigned m_tpgField;
	bool m_tpgFieldAlt;
	unsigned m_tpgSizeImage;
	QComboBox *m_tpgColorspace;
	QComboBox *m_tpgXferFunc;
	QComboBox *m_tpgYCbCrEnc;
	QComboBox *m_tpgQuantRange;
	bool m_useTpg;
	QCheckBox *m_tpgLimRGBRange;

	cv4l_queue m_queue;

	const double m_pxw;
	const int m_minWidth;
	const int m_vMargin;
	const int m_hMargin;
	int m_maxw[4];
	int m_increment;
	GeneralTab *m_genTab;
	VbiTab *m_vbiTab;
	QMenu *m_capMenu;
	QAction *m_capStartAct;
	QAction *m_capStepAct;
	QAction *m_saveRawAct;
	QAction *m_useGLAct;
	QAction *m_audioBufferAct;
	QAction *m_scalingAct;
	QAction *m_makeFullScreenAct;
<<<<<<< HEAD
=======
	GeneralTab *m_genTab;
	VbiTab *m_vbiTab;
	QAction *m_capStartAct;
	QAction *m_snapshotAct;
	QAction *m_saveRawAct;
	QAction *m_showFramesAct;
	QAction *m_useGLAct;
	QAction *m_showAllAudioAct;
	QAction *m_audioBufferAct;
	QAction *m_scalingAct;
	QAction *m_resetScalingAct;
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	QString m_filename;
	QSignalMapper *m_sigMapper;
	QTabWidget *m_tabs;
	QSocketNotifier *m_capNotifier;
<<<<<<< HEAD
<<<<<<< HEAD
	QSocketNotifier *m_outNotifier;
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	QSocketNotifier *m_outNotifier;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	QSocketNotifier *m_ctrlNotifier;
	QImage *m_capImage;
	int m_row, m_col, m_cols;
	CtrlMap m_ctrlMap;
	WidgetMap m_widgetMap;
<<<<<<< HEAD
<<<<<<< HEAD
	WidgetMap m_sliderMap;
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	ClassMap m_classMap;
	bool m_haveExtendedUserCtrls;
=======
	WidgetMap m_sliderMap;
	ClassMap m_classMap;
<<<<<<< HEAD
	bool m_haveExtendedUserCtrls;
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	int m_vbiSize;
	unsigned m_vbiWidth;
	unsigned m_vbiHeight;
	struct vbi_handle m_vbiHandle;
<<<<<<< HEAD
<<<<<<< HEAD
	int m_sdrSize;
	unsigned m_frame;
	double m_fps;
	struct timespec m_startTimestamp;
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	unsigned m_frame;
	unsigned m_lastFrame;
	unsigned m_fps;
	struct timeval m_tv;
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	int m_sdrSize;
	unsigned m_frame;
	double m_fps;
	struct timespec m_startTimestamp;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	struct timeval m_totalAudioLatency;
	QFile m_saveRaw;
};

extern ApplicationWindow *g_mw;

class SaveDialog : public QFileDialog
{
	Q_OBJECT

public:
	SaveDialog(QWidget *parent, const QString &caption) :
		QFileDialog(parent, caption), m_buf(NULL) {}
	virtual ~SaveDialog() {}
	bool setBuffer(unsigned char *buf, unsigned size);

public slots:
	void selected(const QString &s);

private:
	unsigned char *m_buf;
	unsigned m_size;
};

#endif
