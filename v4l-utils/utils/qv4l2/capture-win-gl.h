/*
 * Copyright 2013 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 *
 * This program is free software; you may redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CAPTURE_WIN_GL_H
#define CAPTURE_WIN_GL_H

#include <config.h>

<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "qv4l2.h"
#include "capture-win.h"

#include <QResizeEvent>

#ifdef HAVE_QTGL
#define GL_GLEXT_PROTOTYPES
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
#ifdef HAVE_QTGL
#define GL_GLEXT_PROTOTYPES
#define QT_NO_OPENGL_ES_2

>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
#include <QGLWidget>
#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLFunctions>
<<<<<<< HEAD
=======
#endif

<<<<<<< HEAD
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
#include "qv4l2.h"
#include "capture-win.h"

#include <QResizeEvent>

#ifdef HAVE_QTGL
<<<<<<< HEAD
<<<<<<< HEAD
=======
#define GL_GLEXT_PROTOTYPES
#include <QGLWidget>
#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLFunctions>
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

// This must be equal to the max number of textures that any shader uses
#define MAX_TEXTURES_NEEDED 3

class CaptureWinGLEngine : public QGLWidget
{
public:
	CaptureWinGLEngine();
	~CaptureWinGLEngine();

	void stop();
<<<<<<< HEAD
<<<<<<< HEAD
=======
	void setFrame(int width, int height, __u32 format,
			unsigned char *data, unsigned char *data2);
	bool hasNativeFormat(__u32 format);
	void setSize(int width, int height);
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	void setFrame(int width, int height, int cropWidth, int cropHeight,
		      __u32 format, unsigned char *data, unsigned char *data2,
		      unsigned char *data3);
	bool hasNativeFormat(__u32 format);
	void lockSize(QSize size);
	void setColorspace(unsigned colorspace, unsigned xfer_func,
			unsigned ycbcr_enc, unsigned quantization, bool is_sdtv);
	void setField(unsigned field);
	void setBlending(bool enable) { m_blending = enable; }
	void setLinearFilter(bool enable);
<<<<<<< HEAD
=======
	void setFrame(int width, int height, __u32 format,
			unsigned char *data, unsigned char *data2);
	bool hasNativeFormat(__u32 format);
	void setSize(int width, int height);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

protected:
	void paintGL();
	void initializeGL();
	void resizeGL(int width, int height);

private:
	// Colorspace conversion shaders
<<<<<<< HEAD
<<<<<<< HEAD
=======
	void shader_YUV();
	void shader_NV16M(__u32 format);
	QString shader_NV16M_invariant(__u32 format);
	void shader_BGR();
	void shader_YUY2(__u32 format);
	QString shader_YUY2_invariant(__u32 format);

	// Colorspace conversion render
	void render_BGR();
	void render_YUY2();
	void render_YUV(__u32 format);
	void render_NV16M(__u32 format);
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	void shader_YUV(__u32 format);
	QString shader_NV12_invariant(__u32 format);
	void shader_NV12(__u32 format);
	void shader_NV16(__u32 format);
	QString shader_NV16_invariant(__u32 format);
	void shader_NV24(__u32 format);
	QString shader_NV24_invariant(__u32 format);
	void shader_RGB(__u32 format);
	void shader_Bayer(__u32 format);
	void shader_YUV_packed(__u32 format);
	void shader_YUY2(__u32 format);
	QString shader_YUY2_invariant(__u32 format);
	QString codeYUVNormalize();
	QString codeRGBNormalize();
	QString codeYUV2RGB();
	QString codeTransformToLinear();
	QString codeColorspaceConversion();
	QString codeTransformToNonLinear();

	// Colorspace conversion render
	void render_RGB(__u32 format);
	void render_Bayer(__u32 format);
	void render_YUY2(__u32 format);
	void render_YUV(__u32 format);
	void render_YUV_packed(__u32 format);
	void render_NV12(__u32 format);
	void render_NV16(__u32 format);
	void render_NV24(__u32 format);
<<<<<<< HEAD
=======
	void shader_YUV();
	void shader_NV16M(__u32 format);
	QString shader_NV16M_invariant(__u32 format);
	void shader_BGR();
	void shader_YUY2(__u32 format);
	QString shader_YUY2_invariant(__u32 format);

	// Colorspace conversion render
	void render_BGR();
	void render_YUY2();
	void render_YUV(__u32 format);
	void render_NV16M(__u32 format);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	void clearShader();
	void changeShader();
	void paintFrame();
<<<<<<< HEAD
<<<<<<< HEAD
=======
	void configureTexture(size_t idx);
	void checkError(const char *msg);

	int m_frameHeight;
	int m_frameWidth;
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	void paintSquare();
	void configureTexture(size_t idx);
	void checkError(const char *msg);

	int m_frameWidth;
	int m_frameHeight;
	int m_WCrop;
	int m_HCrop;
	unsigned m_colorspace;
	unsigned m_xfer_func;
	unsigned m_ycbcr_enc;
	unsigned m_quantization;
	bool m_is_sdtv;
	bool m_is_rgb;
	unsigned m_field;
<<<<<<< HEAD
=======
	void configureTexture(size_t idx);
	void checkError(const char *msg);

	int m_frameHeight;
	int m_frameWidth;
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	int m_screenTextureCount;
	bool m_formatChange;
	__u32 m_frameFormat;
	GLuint m_screenTexture[MAX_TEXTURES_NEEDED];
	QGLFunctions m_glfunction;
	unsigned char *m_frameData;
	unsigned char *m_frameData2;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	QGLShaderProgram m_shaderProgram;
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	unsigned char *m_frameData3;
	QGLShaderProgram m_shaderProgram;
	bool m_haveFramebufferSRGB;
	bool m_hasGLRed;
	unsigned m_glRed;
	unsigned m_glRed16;
	unsigned m_glRedGreen;
	bool m_blending;
	GLint m_mag_filter;
	GLint m_min_filter;
<<<<<<< HEAD
=======
	QGLShaderProgram m_shaderProgram;
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
};

#endif

class CaptureWinGL : public CaptureWin
{
public:
<<<<<<< HEAD
<<<<<<< HEAD
	CaptureWinGL(ApplicationWindow *aw);
=======
	CaptureWinGL();
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	~CaptureWinGL();

	void setFrame(int width, int height, __u32 format,
		      unsigned char *data, unsigned char *data2, const QString &info);
	void stop();
	bool hasNativeFormat(__u32 format);
	static bool isSupported();

protected:
	void resizeEvent(QResizeEvent *event);
=======
	CaptureWinGL(ApplicationWindow *aw);
	~CaptureWinGL();

	void stop();
	bool hasNativeFormat(__u32 format);
	static bool isSupported();
	void setColorspace(unsigned colorspace, unsigned xfer_func,
			unsigned ycbcr_enc, unsigned quantization, bool is_sdtv);
	void setField(unsigned field);
	void setBlending(bool enable);
	void setLinearFilter(bool enable);

protected:
	void resizeEvent(QResizeEvent *event);
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	void setRenderFrame();
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

private:
#ifdef HAVE_QTGL
	CaptureWinGLEngine m_videoSurface;
#endif
};

#endif
