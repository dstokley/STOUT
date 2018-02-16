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

#include "qv4l2.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QLineEdit>
#include <QValidator>
#include <QLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
<<<<<<< HEAD
<<<<<<< HEAD
#include <QToolButton>
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
#include <QToolTip>

=======
#include <QToolButton>
#include <QToolTip>

<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
#include <math.h>
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

static bool is_valid_type(__u32 type)
{
	switch (type) {
	case V4L2_CTRL_TYPE_INTEGER:
	case V4L2_CTRL_TYPE_BOOLEAN:
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
	case V4L2_CTRL_TYPE_BUTTON:
	case V4L2_CTRL_TYPE_INTEGER64:
	case V4L2_CTRL_TYPE_BITMASK:
	case V4L2_CTRL_TYPE_CTRL_CLASS:
	case V4L2_CTRL_TYPE_STRING:
		return true;
	default:
		return false;
	}
}

void ApplicationWindow::addWidget(QGridLayout *grid, QWidget *w, Qt::Alignment align)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	if (m_col % 2 && !qobject_cast<QToolButton*>(w))
		w->setMinimumWidth(m_minWidth);
	if (w->sizeHint().width() > m_maxw[m_col])
		m_maxw[m_col] = w->sizeHint().width();
<<<<<<< HEAD
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	grid->addWidget(w, m_row, m_col, align | Qt::AlignVCenter);
	m_col++;
	if (m_col == m_cols) {
		m_col = 0;
		m_row++;
	}
}

<<<<<<< HEAD
<<<<<<< HEAD
void ApplicationWindow::addTabs(int m_winWidth)
{
	v4l2_query_ext_ctrl qec = { 0 };
	unsigned which;
	unsigned i;
	int id;

	while (query_ext_ctrl(qec, true) == 0) {
		if (is_valid_type(qec.type) &&
		    (qec.flags & V4L2_CTRL_FLAG_DISABLED) == 0) {
			m_ctrlMap[qec.id] = qec;
			if (qec.type != V4L2_CTRL_TYPE_CTRL_CLASS)
				m_classMap[V4L2_CTRL_ID2WHICH(qec.id)].push_back(qec.id);
		}
	}
	if (m_classMap.find(V4L2_CTRL_CLASS_USER) != m_classMap.end() &&
	    m_ctrlMap.find(V4L2_CID_USER_CLASS) == m_ctrlMap.end()) {
		memset(&qec, 0, sizeof(qec));
		qec.id = V4L2_CID_USER_CLASS;
		strcpy(qec.name, "User Controls");
		qec.type = V4L2_CTRL_TYPE_CTRL_CLASS;
		m_ctrlMap[qec.id] = qec;
	}
	if (m_classMap.find(V4L2_CTRL_CLASS_CAMERA) != m_classMap.end() &&
	    m_ctrlMap.find(V4L2_CID_CAMERA_CLASS) == m_ctrlMap.end()) {
		// UVC still doesn't provide this :-(
		memset(&qec, 0, sizeof(qec));
		qec.id = V4L2_CID_CAMERA_CLASS;
		strcpy(qec.name, "Camera Controls");
		qec.type = V4L2_CTRL_TYPE_CTRL_CLASS;
		m_ctrlMap[qec.id] = qec;
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
void ApplicationWindow::addTabs()
{
	v4l2_queryctrl qctrl;
	unsigned ctrl_class;
	unsigned i;
	int id;

	memset(&qctrl, 0, sizeof(qctrl));
	qctrl.id = V4L2_CTRL_FLAG_NEXT_CTRL;
	while (queryctrl(qctrl)) {
		if (is_valid_type(qctrl.type) &&
		    (qctrl.flags & V4L2_CTRL_FLAG_DISABLED) == 0) {
			m_ctrlMap[qctrl.id] = qctrl;
			if (qctrl.type != V4L2_CTRL_TYPE_CTRL_CLASS)
				m_classMap[V4L2_CTRL_ID2CLASS(qctrl.id)].push_back(qctrl.id);
		}
		qctrl.id |= V4L2_CTRL_FLAG_NEXT_CTRL;
	}
	if (qctrl.id == V4L2_CTRL_FLAG_NEXT_CTRL) {
		strcpy((char *)qctrl.name, "User Controls");
		qctrl.id = V4L2_CTRL_CLASS_USER | 1;
		qctrl.type = V4L2_CTRL_TYPE_CTRL_CLASS;
		m_ctrlMap[qctrl.id] = qctrl;
		for (id = V4L2_CID_USER_BASE; id < V4L2_CID_LASTP1; id++) {
			qctrl.id = id;
			if (!queryctrl(qctrl))
				continue;
			if (!is_valid_type(qctrl.type))
				continue;
			if (qctrl.flags & V4L2_CTRL_FLAG_DISABLED)
				continue;
			m_ctrlMap[qctrl.id] = qctrl;
			m_classMap[V4L2_CTRL_CLASS_USER].push_back(qctrl.id);
		}
		for (qctrl.id = V4L2_CID_PRIVATE_BASE;
				queryctrl(qctrl); qctrl.id++) {
			if (!is_valid_type(qctrl.type))
				continue;
			if (qctrl.flags & V4L2_CTRL_FLAG_DISABLED)
				continue;
			m_ctrlMap[qctrl.id] = qctrl;
			m_classMap[V4L2_CTRL_CLASS_USER].push_back(qctrl.id);
		}
	}
	
	m_haveExtendedUserCtrls = false;
	for (unsigned i = 0; i < m_classMap[V4L2_CTRL_CLASS_USER].size(); i++) {
		unsigned id = m_classMap[V4L2_CTRL_CLASS_USER][i];

		if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_INTEGER64 ||
		    m_ctrlMap[id].type == V4L2_CTRL_TYPE_STRING ||
		    V4L2_CTRL_DRIVER_PRIV(id)) {
			m_haveExtendedUserCtrls = true;
			break;
		}
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
void ApplicationWindow::addTabs(int m_winWidth)
{
	v4l2_query_ext_ctrl qec = { 0 };
	unsigned which;
	unsigned i;
	int id;

	while (query_ext_ctrl(qec, true) == 0) {
		if (is_valid_type(qec.type) &&
		    (qec.flags & V4L2_CTRL_FLAG_DISABLED) == 0) {
			m_ctrlMap[qec.id] = qec;
			if (qec.type != V4L2_CTRL_TYPE_CTRL_CLASS)
				m_classMap[V4L2_CTRL_ID2WHICH(qec.id)].push_back(qec.id);
		}
	}
	if (m_classMap.find(V4L2_CTRL_CLASS_USER) != m_classMap.end() &&
	    m_ctrlMap.find(V4L2_CID_USER_CLASS) == m_ctrlMap.end()) {
		memset(&qec, 0, sizeof(qec));
		qec.id = V4L2_CID_USER_CLASS;
		strcpy(qec.name, "User Controls");
		qec.type = V4L2_CTRL_TYPE_CTRL_CLASS;
		m_ctrlMap[qec.id] = qec;
	}
	if (m_classMap.find(V4L2_CTRL_CLASS_CAMERA) != m_classMap.end() &&
	    m_ctrlMap.find(V4L2_CID_CAMERA_CLASS) == m_ctrlMap.end()) {
		// UVC still doesn't provide this :-(
		memset(&qec, 0, sizeof(qec));
		qec.id = V4L2_CID_CAMERA_CLASS;
		strcpy(qec.name, "Camera Controls");
		qec.type = V4L2_CTRL_TYPE_CTRL_CLASS;
		m_ctrlMap[qec.id] = qec;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	}

	for (ClassMap::iterator iter = m_classMap.begin(); iter != m_classMap.end(); ++iter) {
		if (iter->second.size() == 0)
			continue;
<<<<<<< HEAD
<<<<<<< HEAD
=======
		ctrl_class = V4L2_CTRL_ID2CLASS(iter->second[0]);
		id = ctrl_class | 1;
		m_col = m_row = 0;
		m_cols = 4;

		const v4l2_queryctrl &qctrl = m_ctrlMap[id];
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		which = V4L2_CTRL_ID2WHICH(iter->second[0]);
		id = which | 1;
		m_col = m_row = 0;
		m_cols = 4;
		for (int j = 0; j < m_cols; j++) {
			m_maxw[j] = 0;
		}

		const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
<<<<<<< HEAD
=======
		ctrl_class = V4L2_CTRL_ID2CLASS(iter->second[0]);
		id = ctrl_class | 1;
		m_col = m_row = 0;
		m_cols = 4;

		const v4l2_queryctrl &qctrl = m_ctrlMap[id];
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		QWidget *t = new QWidget(m_tabs);
		QVBoxLayout *vbox = new QVBoxLayout(t);
		QWidget *w = new QWidget(t);

		vbox->addWidget(w);

		QGridLayout *grid = new QGridLayout(w);
<<<<<<< HEAD
<<<<<<< HEAD
=======

		grid->setSpacing(3);
		m_tabs->addTab(t, (char *)qctrl.name);
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		QString tabName(qec.name);

		if (tabName.length()) {
			QLabel *title_tab = new QLabel(tabName, parentWidget());
			QFont f = title_tab->font();
			f.setBold(true);
			title_tab->setFont(f);
			grid->addWidget(title_tab, m_row, m_col, 1, m_cols, Qt::AlignLeft);
			grid->setRowMinimumHeight(m_row, 25);
			m_row++;

			QFrame *m_line = new QFrame(grid->parentWidget());
			m_line->setFrameShape(QFrame::HLine);
			m_line->setFrameShadow(QFrame::Sunken);
			grid->addWidget(m_line, m_row, m_col, 1, m_cols, Qt::AlignVCenter);
			m_row++;
		}
		m_tabs->addTab(t, tabName);
<<<<<<< HEAD
=======

		grid->setSpacing(3);
		m_tabs->addTab(t, (char *)qctrl.name);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		for (i = 0; i < iter->second.size(); i++) {
			if (i & 1)
				id = iter->second[(1+iter->second.size()) / 2 + i / 2];
			else
				id = iter->second[i / 2];
			addCtrl(grid, m_ctrlMap[id]);
		}
		grid->addWidget(new QWidget(w), grid->rowCount(), 0, 1, m_cols);
		grid->setRowStretch(grid->rowCount() - 1, 1);
		w = new QWidget(t);
		vbox->addWidget(w);
<<<<<<< HEAD
<<<<<<< HEAD
=======
		grid = new QGridLayout(w);
		finishGrid(grid, ctrl_class);
	}
}

void ApplicationWindow::finishGrid(QGridLayout *grid, unsigned ctrl_class)
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		fixWidth(grid);

		int totalw = 0;
		int diff = 0;
		for (int i = 0; i < m_cols; i++) {
			totalw += m_maxw[i] + m_pxw;
		}
		if (totalw > m_winWidth)
			m_winWidth = totalw;
		else {
		  diff = m_winWidth - totalw;
		  grid->setHorizontalSpacing(diff/5);
		}
		grid = new QGridLayout(w);
		finishGrid(grid, which);
	}
}

void ApplicationWindow::fixWidth(QGridLayout *grid)
{
	grid->setContentsMargins(m_vMargin, m_hMargin, m_vMargin, m_hMargin);
	grid->setColumnStretch(3, 1);
	QList<QWidget *> list = grid->parentWidget()->parentWidget()->findChildren<QWidget *>();
	QList<QWidget *>::iterator it;

	for (it = list.begin(); it != list.end(); ++it)	{
		if (((*it)->sizeHint().width()) > m_minWidth) {
			m_increment = (int) ceil(((*it)->sizeHint().width() - m_minWidth) / m_pxw);
			(*it)->setMinimumWidth(m_minWidth + m_increment * m_pxw); // for stepsize expantion of widgets
		}
	}

	for (int j = 0; j < m_cols; j++) {
		if (j % 2) // only add possible expansion for odd columns
			grid->setColumnMinimumWidth(j, m_maxw[j] + m_pxw);
		else
			grid->setColumnMinimumWidth(j, m_maxw[j]);
	}
}

void ApplicationWindow::finishGrid(QGridLayout *grid, unsigned which)
<<<<<<< HEAD
=======
		grid = new QGridLayout(w);
		finishGrid(grid, ctrl_class);
	}
}

void ApplicationWindow::finishGrid(QGridLayout *grid, unsigned ctrl_class)
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
{
	QWidget *w = grid->parentWidget();

	QFrame *frame = new QFrame(w);
	frame->setFrameShape(QFrame::HLine);
	frame->setFrameShadow(QFrame::Sunken);
	grid->addWidget(frame, 0, 0, 1, m_cols);
	m_col = 0;
	m_row = grid->rowCount();

<<<<<<< HEAD
<<<<<<< HEAD
=======
	QCheckBox *cbox = new QCheckBox("Update on change", w);
	m_widgetMap[ctrl_class | CTRL_UPDATE_ON_CHANGE] = cbox;
	addWidget(grid, cbox);
	connect(cbox, SIGNAL(clicked()), m_sigMapper, SLOT(map()));
	m_sigMapper->setMapping(cbox, ctrl_class | CTRL_UPDATE_ON_CHANGE);
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	QWidget *m_w = new QWidget();
	QHBoxLayout *m_boxLayoutBottom = new QHBoxLayout(m_w);

	QCheckBox *cbox = new QCheckBox("Update on change", w);
	m_widgetMap[which | CTRL_UPDATE_ON_CHANGE] = cbox;
	addWidget(grid, cbox);
	connect(cbox, SIGNAL(clicked()), m_sigMapper, SLOT(map()));
	m_sigMapper->setMapping(cbox, which | CTRL_UPDATE_ON_CHANGE);
<<<<<<< HEAD
=======
	QCheckBox *cbox = new QCheckBox("Update on change", w);
	m_widgetMap[ctrl_class | CTRL_UPDATE_ON_CHANGE] = cbox;
	addWidget(grid, cbox);
	connect(cbox, SIGNAL(clicked()), m_sigMapper, SLOT(map()));
	m_sigMapper->setMapping(cbox, ctrl_class | CTRL_UPDATE_ON_CHANGE);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	grid->setColumnStretch(0, 1);

	QPushButton *defBut = new QPushButton("Set Defaults", w);
<<<<<<< HEAD
<<<<<<< HEAD
	m_widgetMap[which | CTRL_DEFAULTS] = defBut;
	m_boxLayoutBottom->addWidget(defBut);
=======
	m_widgetMap[ctrl_class | CTRL_DEFAULTS] = defBut;
	addWidget(grid, defBut);
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	connect(defBut, SIGNAL(clicked()), m_sigMapper, SLOT(map()));
	m_sigMapper->setMapping(defBut, ctrl_class | CTRL_DEFAULTS);

	QPushButton *refreshBut = new QPushButton("Refresh", w);
	m_widgetMap[ctrl_class | CTRL_REFRESH] = refreshBut;
	addWidget(grid, refreshBut);
	connect(refreshBut, SIGNAL(clicked()), m_sigMapper, SLOT(map()));
	m_sigMapper->setMapping(refreshBut, ctrl_class | CTRL_REFRESH);

	QPushButton *button = new QPushButton("Update", w);
	m_widgetMap[ctrl_class | CTRL_UPDATE] = button;
	addWidget(grid, button);
	connect(button, SIGNAL(clicked()), m_sigMapper, SLOT(map()));
	m_sigMapper->setMapping(button, ctrl_class | CTRL_UPDATE);
	connect(cbox, SIGNAL(toggled(bool)), button, SLOT(setDisabled(bool)));

	cbox->setChecked(true);

	refresh(ctrl_class);
}

void ApplicationWindow::addCtrl(QGridLayout *grid, const v4l2_queryctrl &qctrl)
=======
	m_widgetMap[which | CTRL_DEFAULTS] = defBut;
	m_boxLayoutBottom->addWidget(defBut);
	connect(defBut, SIGNAL(clicked()), m_sigMapper, SLOT(map()));
	m_sigMapper->setMapping(defBut, which | CTRL_DEFAULTS);

	QPushButton *refreshBut = new QPushButton("Refresh", w);
	m_widgetMap[which | CTRL_REFRESH] = refreshBut;
	m_boxLayoutBottom->addWidget(refreshBut);
	connect(refreshBut, SIGNAL(clicked()), m_sigMapper, SLOT(map()));
	m_sigMapper->setMapping(refreshBut, which | CTRL_REFRESH);

	QPushButton *button = new QPushButton("Update", w);
	m_widgetMap[which | CTRL_UPDATE] = button;
	m_boxLayoutBottom->addWidget(button);
	connect(button, SIGNAL(clicked()), m_sigMapper, SLOT(map()));
	m_sigMapper->setMapping(button, which | CTRL_UPDATE);
	connect(cbox, SIGNAL(toggled(bool)), button, SLOT(setDisabled(bool)));

	grid->addWidget(m_w, m_row, 3, Qt::AlignRight);
	cbox->setChecked(true);

	refresh(which);
}

<<<<<<< HEAD
void ApplicationWindow::addCtrl(QGridLayout *grid, const v4l2_queryctrl &qctrl)
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
void ApplicationWindow::addCtrl(QGridLayout *grid, const v4l2_query_ext_ctrl &qec)
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
{
	QWidget *p = grid->parentWidget();
	QIntValidator *val;
	QLineEdit *edit;
<<<<<<< HEAD
<<<<<<< HEAD
	QString name(qec.name);
=======
	QString name((char *)qctrl.name);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	QString name((char *)qctrl.name);
=======
	QString name(qec.name);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	QComboBox *combo;
	QSpinBox *spin;
	QSlider *slider;
	struct v4l2_querymenu qmenu;
<<<<<<< HEAD
<<<<<<< HEAD
=======

	switch (qctrl.type) {
	case V4L2_CTRL_TYPE_INTEGER:
		addLabel(grid, name);
		if (qctrl.flags & V4L2_CTRL_FLAG_SLIDER) {
			m_widgetMap[qctrl.id] = slider = new QSlider(Qt::Horizontal, p);
			slider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
			slider->setMinimum(qctrl.minimum);
			slider->setMaximum(qctrl.maximum);
			slider->setSingleStep(qctrl.step);
			slider->setSliderPosition(qctrl.default_value);
			addWidget(grid, m_widgetMap[qctrl.id]);
			connect(m_widgetMap[qctrl.id], SIGNAL(valueChanged(int)),
				m_sigMapper, SLOT(map()));
			break;
		}

		if (qctrl.maximum - qctrl.minimum <= 255) {
			m_widgetMap[qctrl.id] = spin = new QSpinBox(p);
			spin->setMinimum(qctrl.minimum);
			spin->setMaximum(qctrl.maximum);
			spin->setSingleStep(qctrl.step);
			addWidget(grid, m_widgetMap[qctrl.id]);
			connect(m_widgetMap[qctrl.id], SIGNAL(valueChanged(int)),
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	QWidget *wContainer = new QWidget();
	QHBoxLayout *m_boxLayout = new QHBoxLayout(wContainer);
	m_boxLayout->setMargin(0);
	__u64 dif;

	switch (qec.type) {
	case V4L2_CTRL_TYPE_INTEGER:
		addLabel(grid, name);
		dif = qec.maximum - qec.minimum;
		if (dif <= 0xffffU || (qec.flags & V4L2_CTRL_FLAG_SLIDER)) {
			m_sliderMap[qec.id] = slider = new QSlider(Qt::Horizontal, p);
			slider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
			slider->setMinimum(qec.minimum);
			slider->setMaximum(qec.maximum);
			slider->setSingleStep(qec.step);
			slider->setSliderPosition(qec.default_value);

			m_widgetMap[qec.id] = spin = new QSpinBox(p);
			spin->setRange(qec.minimum, qec.maximum);
			spin->setSingleStep(qec.step);

			m_boxLayout->addWidget(slider);
			m_boxLayout->addWidget(spin);
			wContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
			addWidget(grid, wContainer);

			connect(spin, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
			connect(slider, SIGNAL(valueChanged(int)), spin, SLOT(setValue(int)));
			connect(m_widgetMap[qec.id], SIGNAL(valueChanged(int)),
<<<<<<< HEAD
=======

	switch (qctrl.type) {
	case V4L2_CTRL_TYPE_INTEGER:
		addLabel(grid, name);
		if (qctrl.flags & V4L2_CTRL_FLAG_SLIDER) {
			m_widgetMap[qctrl.id] = slider = new QSlider(Qt::Horizontal, p);
			slider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
			slider->setMinimum(qctrl.minimum);
			slider->setMaximum(qctrl.maximum);
			slider->setSingleStep(qctrl.step);
			slider->setSliderPosition(qctrl.default_value);
			addWidget(grid, m_widgetMap[qctrl.id]);
			connect(m_widgetMap[qctrl.id], SIGNAL(valueChanged(int)),
				m_sigMapper, SLOT(map()));
			break;
		}

		if (qctrl.maximum - qctrl.minimum <= 255) {
			m_widgetMap[qctrl.id] = spin = new QSpinBox(p);
			spin->setMinimum(qctrl.minimum);
			spin->setMaximum(qctrl.maximum);
			spin->setSingleStep(qctrl.step);
			addWidget(grid, m_widgetMap[qctrl.id]);
			connect(m_widgetMap[qctrl.id], SIGNAL(valueChanged(int)),
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
				m_sigMapper, SLOT(map()));
			break;
		}

<<<<<<< HEAD
<<<<<<< HEAD
		val = new QIntValidator(qec.minimum, qec.maximum, p);
=======
		val = new QIntValidator(qctrl.minimum, qctrl.maximum, p);
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		edit = new QLineEdit(p);
		edit->setValidator(val);
		addWidget(grid, edit);
		m_widgetMap[qctrl.id] = edit;
		connect(m_widgetMap[qctrl.id], SIGNAL(lostFocus()),
				m_sigMapper, SLOT(map()));
		connect(m_widgetMap[qctrl.id], SIGNAL(returnPressed()),
=======
		val = new QIntValidator(qec.minimum, qec.maximum, p);
		edit = new QLineEdit(p);
		edit->setValidator(val);
		addWidget(grid, edit);
		m_widgetMap[qec.id] = edit;
		connect(m_widgetMap[qec.id], SIGNAL(editingFinished()),
				m_sigMapper, SLOT(map()));
<<<<<<< HEAD
		connect(m_widgetMap[qctrl.id], SIGNAL(returnPressed()),
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
		connect(m_widgetMap[qec.id], SIGNAL(returnPressed()),
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
				m_sigMapper, SLOT(map()));
		break;

	case V4L2_CTRL_TYPE_INTEGER64:
		addLabel(grid, name);
		edit = new QLineEdit(p);
<<<<<<< HEAD
<<<<<<< HEAD
		m_widgetMap[qec.id] = edit;
		addWidget(grid, edit);
		connect(m_widgetMap[qec.id], SIGNAL(editingFinished()),
				m_sigMapper, SLOT(map()));
		connect(m_widgetMap[qec.id], SIGNAL(returnPressed()),
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		m_widgetMap[qctrl.id] = edit;
		addWidget(grid, edit);
		connect(m_widgetMap[qctrl.id], SIGNAL(lostFocus()),
				m_sigMapper, SLOT(map()));
		connect(m_widgetMap[qctrl.id], SIGNAL(returnPressed()),
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
		m_widgetMap[qec.id] = edit;
		addWidget(grid, edit);
		connect(m_widgetMap[qec.id], SIGNAL(editingFinished()),
				m_sigMapper, SLOT(map()));
		connect(m_widgetMap[qec.id], SIGNAL(returnPressed()),
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
				m_sigMapper, SLOT(map()));
		break;

	case V4L2_CTRL_TYPE_BITMASK:
		addLabel(grid, name);
		edit = new QLineEdit(p);
		edit->setInputMask("HHHHHHHH");
		addWidget(grid, edit);
<<<<<<< HEAD
<<<<<<< HEAD
		m_widgetMap[qec.id] = edit;
		connect(m_widgetMap[qec.id], SIGNAL(editingFinished()),
				m_sigMapper, SLOT(map()));
		connect(m_widgetMap[qec.id], SIGNAL(returnPressed()),
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		m_widgetMap[qctrl.id] = edit;
		connect(m_widgetMap[qctrl.id], SIGNAL(lostFocus()),
				m_sigMapper, SLOT(map()));
		connect(m_widgetMap[qctrl.id], SIGNAL(returnPressed()),
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
		m_widgetMap[qec.id] = edit;
		connect(m_widgetMap[qec.id], SIGNAL(editingFinished()),
				m_sigMapper, SLOT(map()));
		connect(m_widgetMap[qec.id], SIGNAL(returnPressed()),
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
				m_sigMapper, SLOT(map()));
		break;

	case V4L2_CTRL_TYPE_STRING:
		addLabel(grid, name);
		edit = new QLineEdit(p);
<<<<<<< HEAD
<<<<<<< HEAD
		m_widgetMap[qec.id] = edit;
		edit->setMaxLength(qec.maximum);
		addWidget(grid, edit);
		connect(m_widgetMap[qec.id], SIGNAL(editingFinished()),
				m_sigMapper, SLOT(map()));
		connect(m_widgetMap[qec.id], SIGNAL(returnPressed()),
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		m_widgetMap[qctrl.id] = edit;
		edit->setMaxLength(qctrl.maximum);
		addWidget(grid, edit);
		connect(m_widgetMap[qctrl.id], SIGNAL(lostFocus()),
				m_sigMapper, SLOT(map()));
		connect(m_widgetMap[qctrl.id], SIGNAL(returnPressed()),
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
		m_widgetMap[qec.id] = edit;
		edit->setMaxLength(qec.maximum);
		addWidget(grid, edit);
		connect(m_widgetMap[qec.id], SIGNAL(editingFinished()),
				m_sigMapper, SLOT(map()));
		connect(m_widgetMap[qec.id], SIGNAL(returnPressed()),
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
				m_sigMapper, SLOT(map()));
		break;

	case V4L2_CTRL_TYPE_BOOLEAN:
		addLabel(grid, name);
<<<<<<< HEAD
<<<<<<< HEAD
		m_widgetMap[qec.id] = new QCheckBox(p);
		addWidget(grid, m_widgetMap[qec.id]);
		connect(m_widgetMap[qec.id], SIGNAL(clicked()),
=======
		m_widgetMap[qctrl.id] = new QCheckBox(p);
		addWidget(grid, m_widgetMap[qctrl.id]);
		connect(m_widgetMap[qctrl.id], SIGNAL(clicked()),
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
		m_widgetMap[qctrl.id] = new QCheckBox(p);
		addWidget(grid, m_widgetMap[qctrl.id]);
		connect(m_widgetMap[qctrl.id], SIGNAL(clicked()),
=======
		m_widgetMap[qec.id] = new QCheckBox(p);
		addWidget(grid, m_widgetMap[qec.id]);
		connect(m_widgetMap[qec.id], SIGNAL(clicked()),
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
				m_sigMapper, SLOT(map()));
		break;

	case V4L2_CTRL_TYPE_BUTTON:
<<<<<<< HEAD
<<<<<<< HEAD
=======
		addLabel(grid, "");
		m_widgetMap[qctrl.id] = new QPushButton((char *)qctrl.name, p);
		addWidget(grid, m_widgetMap[qctrl.id]);
		connect(m_widgetMap[qctrl.id], SIGNAL(clicked()),
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		addLabel(grid, (char *)qec.name);
		QToolButton *button;
		m_widgetMap[qec.id] = button = new QToolButton(p);
		button->setIcon(QIcon(":/enterbutt.png"));
		addWidget(grid, m_widgetMap[qec.id]);
		connect(m_widgetMap[qec.id], SIGNAL(clicked()),
<<<<<<< HEAD
=======
		addLabel(grid, "");
		m_widgetMap[qctrl.id] = new QPushButton((char *)qctrl.name, p);
		addWidget(grid, m_widgetMap[qctrl.id]);
		connect(m_widgetMap[qctrl.id], SIGNAL(clicked()),
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
				m_sigMapper, SLOT(map()));
		break;

	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
		addLabel(grid, name);
		combo = new QComboBox(p);
<<<<<<< HEAD
<<<<<<< HEAD
		m_widgetMap[qec.id] = combo;
		for (int i = (int)qec.minimum; i <= (int)qec.maximum; i++) {
			qmenu.id = qec.id;
			qmenu.index = i;
			if (querymenu(qmenu))
				continue;
			if (qec.type == V4L2_CTRL_TYPE_MENU)
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		m_widgetMap[qctrl.id] = combo;
		for (int i = qctrl.minimum; i <= qctrl.maximum; i++) {
			qmenu.id = qctrl.id;
			qmenu.index = i;
			if (!querymenu(qmenu))
				continue;
			if (qctrl.type == V4L2_CTRL_TYPE_MENU)
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
		m_widgetMap[qec.id] = combo;
		for (int i = (int)qec.minimum; i <= (int)qec.maximum; i++) {
			qmenu.id = qec.id;
			qmenu.index = i;
			if (querymenu(qmenu))
				continue;
			if (qec.type == V4L2_CTRL_TYPE_MENU)
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
				combo->addItem((char *)qmenu.name);
			else
				combo->addItem(QString("%1").arg(qmenu.value));
		}
<<<<<<< HEAD
<<<<<<< HEAD
		addWidget(grid, m_widgetMap[qec.id]);
		connect(m_widgetMap[qec.id], SIGNAL(activated(int)),
=======
		addWidget(grid, m_widgetMap[qctrl.id]);
		connect(m_widgetMap[qctrl.id], SIGNAL(activated(int)),
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
		addWidget(grid, m_widgetMap[qctrl.id]);
		connect(m_widgetMap[qctrl.id], SIGNAL(activated(int)),
=======
		addWidget(grid, m_widgetMap[qec.id]);
		connect(m_widgetMap[qec.id], SIGNAL(activated(int)),
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
				m_sigMapper, SLOT(map()));
		break;

	default:
		return;
	}
<<<<<<< HEAD
<<<<<<< HEAD
=======
	struct v4l2_event_subscription sub;
	memset(&sub, 0, sizeof(sub));
	sub.type = V4L2_EVENT_CTRL;
	sub.id = qctrl.id;
	subscribe_event(sub);

	m_sigMapper->setMapping(m_widgetMap[qctrl.id], qctrl.id);
	if (qctrl.flags & CTRL_FLAG_DISABLED)
		m_widgetMap[qctrl.id]->setDisabled(true);
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	m_sigMapper->setMapping(m_widgetMap[qec.id], qec.id);
	if (qec.flags & CTRL_FLAG_DISABLED) {
		if (qobject_cast<QLineEdit *>(m_widgetMap[qec.id]))
			static_cast<QLineEdit *>(m_widgetMap[qec.id])->setReadOnly(true);
		else
			m_widgetMap[qec.id]->setDisabled(true);
		if (m_sliderMap.find(qec.id) != m_sliderMap.end())
			m_sliderMap[qec.id]->setDisabled(true);
	}
<<<<<<< HEAD
=======
	struct v4l2_event_subscription sub;
	memset(&sub, 0, sizeof(sub));
	sub.type = V4L2_EVENT_CTRL;
	sub.id = qctrl.id;
	subscribe_event(sub);

	m_sigMapper->setMapping(m_widgetMap[qctrl.id], qctrl.id);
	if (qctrl.flags & CTRL_FLAG_DISABLED)
		m_widgetMap[qctrl.id]->setDisabled(true);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
}

void ApplicationWindow::ctrlAction(int id)
{
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned which = V4L2_CTRL_ID2WHICH(id);
	if (which == V4L2_CID_PRIVATE_BASE)
		which = V4L2_CTRL_CLASS_USER;
	unsigned ctrl = id & 0xffff;
	QCheckBox *cbox = static_cast<QCheckBox *>(m_widgetMap[which | CTRL_UPDATE_ON_CHANGE]);
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	unsigned ctrl_class = V4L2_CTRL_ID2CLASS(id);
	if (ctrl_class == V4L2_CID_PRIVATE_BASE)
		ctrl_class = V4L2_CTRL_CLASS_USER;
	unsigned ctrl = id & 0xffff;
	QCheckBox *cbox = static_cast<QCheckBox *>(m_widgetMap[ctrl_class | CTRL_UPDATE_ON_CHANGE]);
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	unsigned which = V4L2_CTRL_ID2WHICH(id);
	if (which == V4L2_CID_PRIVATE_BASE)
		which = V4L2_CTRL_CLASS_USER;
	unsigned ctrl = id & 0xffff;
	QCheckBox *cbox = static_cast<QCheckBox *>(m_widgetMap[which | CTRL_UPDATE_ON_CHANGE]);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	bool update = cbox->isChecked();
	bool all = (ctrl == CTRL_UPDATE || (update && ctrl == CTRL_UPDATE_ON_CHANGE));

	if (ctrl == CTRL_DEFAULTS) {
<<<<<<< HEAD
<<<<<<< HEAD
		setDefaults(which);
		return;
	}
	if (ctrl == CTRL_REFRESH) {
		refresh(which);
		return;
	}
	if (!update && !all && m_ctrlMap[id].type != V4L2_CTRL_TYPE_BUTTON)
		return;
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		setDefaults(ctrl_class);
		return;
	}
	if (ctrl == CTRL_REFRESH) {
		refresh(ctrl_class);
		return;
	}
	if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_INTEGER &&
	    (m_ctrlMap[id].flags & V4L2_CTRL_FLAG_SLIDER)) {
		QWidget *w = m_widgetMap[id];
		int v = static_cast<QSlider *>(w)->value();
		info(QString("Value: %1").arg(v));
	}
	if (!update && !all && m_ctrlMap[id].type != V4L2_CTRL_TYPE_BUTTON)
		return;
	if (!m_haveExtendedUserCtrls && ctrl_class == V4L2_CTRL_CLASS_USER) {
		if (!all) {
			updateCtrl(id);
			return;
		}
		for (unsigned i = 0; i < m_classMap[ctrl_class].size(); i++) {
			updateCtrl(m_classMap[ctrl_class][i]);
		}
		return;
	}
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
		setDefaults(which);
		return;
	}
	if (ctrl == CTRL_REFRESH) {
		refresh(which);
		return;
	}
	if (!update && !all && m_ctrlMap[id].type != V4L2_CTRL_TYPE_BUTTON)
		return;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	if (!all) {
		updateCtrl(id);
		return;
	}
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned count = m_classMap[which].size();
=======
	unsigned count = m_classMap[ctrl_class].size();
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	unsigned count = m_classMap[ctrl_class].size();
=======
	unsigned count = m_classMap[which].size();
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	struct v4l2_ext_control *c = new v4l2_ext_control[count];
	struct v4l2_ext_controls ctrls;
	int idx = 0;

	for (unsigned i = 0; i < count; i++) {
<<<<<<< HEAD
<<<<<<< HEAD
		unsigned id = m_classMap[which][i];
=======
		unsigned id = m_classMap[ctrl_class][i];
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
		unsigned id = m_classMap[ctrl_class][i];
=======
		unsigned id = m_classMap[which][i];
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

		if (m_ctrlMap[id].flags & CTRL_FLAG_DISABLED)
			continue;
		c[idx].id = id;
		c[idx].size = 0;
		if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_INTEGER64)
			c[idx].value64 = getVal64(id);
		else if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_STRING) {
			c[idx].size = m_ctrlMap[id].maximum + 1;
			c[idx].string = (char *)malloc(c[idx].size);
			strcpy(c[idx].string, getString(id).toLatin1());
		}
		else
			c[idx].value = getVal(id);
		idx++;
	}
	memset(&ctrls, 0, sizeof(ctrls));
	ctrls.count = idx;
<<<<<<< HEAD
<<<<<<< HEAD
	ctrls.which = which;
	ctrls.controls = c;
	if (s_ext_ctrls(ctrls)) {
=======
	ctrls.ctrl_class = ctrl_class;
	ctrls.controls = c;
	if (ioctl(VIDIOC_S_EXT_CTRLS, &ctrls)) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	ctrls.ctrl_class = ctrl_class;
	ctrls.controls = c;
	if (ioctl(VIDIOC_S_EXT_CTRLS, &ctrls)) {
=======
	ctrls.which = which;
	ctrls.controls = c;
	if (s_ext_ctrls(ctrls)) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		if (ctrls.error_idx >= ctrls.count) {
			error(errno);
		}
		else {
			errorCtrl(c[ctrls.error_idx].id, errno);
		}
	}
	for (unsigned i = 0; i < ctrls.count; i++) {
		if (c[i].size)
			free(c[i].string);
	}
	delete [] c;
<<<<<<< HEAD
<<<<<<< HEAD
	refresh(which);
=======
	refresh(ctrl_class);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	refresh(ctrl_class);
=======
	refresh(which);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
}

QString ApplicationWindow::getString(unsigned id)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
	const v4l2_queryctrl &qctrl = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qctrl.id];
	QString v;

	switch (qctrl.type) {
	case V4L2_CTRL_TYPE_STRING:
		v = static_cast<QLineEdit *>(w)->text();
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qec.id];
	QString v;
	int mod;

	switch (qec.type) {
	case V4L2_CTRL_TYPE_STRING:
		v = static_cast<QLineEdit *>(w)->text();
		mod = v.length() % qec.step;
		if (mod)
			v += QString(qec.step - mod, ' ');
<<<<<<< HEAD
=======
	const v4l2_queryctrl &qctrl = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qctrl.id];
	QString v;

	switch (qctrl.type) {
	case V4L2_CTRL_TYPE_STRING:
		v = static_cast<QLineEdit *>(w)->text();
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		break;
	default:
		break;
	}
<<<<<<< HEAD
<<<<<<< HEAD
	setWhat(w, id, QString("'") + v + "'");
=======
	setWhat(w, id, v);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	setWhat(w, id, v);
=======
	setWhat(w, id, QString("'") + v + "'");
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	return v;
}

long long ApplicationWindow::getVal64(unsigned id)
{
<<<<<<< HEAD
<<<<<<< HEAD
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qec.id];
	long long v = 0;

	switch (qec.type) {
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	const v4l2_queryctrl &qctrl = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qctrl.id];
	long long v = 0;

	switch (qctrl.type) {
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qec.id];
	long long v = 0;

	switch (qec.type) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	case V4L2_CTRL_TYPE_INTEGER64:
		v = static_cast<QLineEdit *>(w)->text().toLongLong();
		break;
	default:
		break;
	}
	setWhat(w, id, v);
	return v;
}

int ApplicationWindow::getVal(unsigned id)
{
<<<<<<< HEAD
<<<<<<< HEAD
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qec.id];
	v4l2_querymenu qmenu;
	int i, idx;
	int v = 0;
	unsigned dif;

	switch (qec.type) {
	case V4L2_CTRL_TYPE_INTEGER:
		dif = qec.maximum - qec.minimum;
		if (dif <= 0xffffU || (qec.flags & V4L2_CTRL_FLAG_SLIDER)) {
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	const v4l2_queryctrl &qctrl = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qctrl.id];
	v4l2_querymenu qmenu;
	int i, idx;
	int v = 0;

	switch (qctrl.type) {
	case V4L2_CTRL_TYPE_INTEGER:
		if (qctrl.flags & V4L2_CTRL_FLAG_SLIDER) {
			v = static_cast<QSlider *>(w)->value();
			break;
		}

		if (qctrl.maximum - qctrl.minimum <= 255) {
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qec.id];
	v4l2_querymenu qmenu;
	int i, idx;
	int v = 0;
	unsigned dif;

	switch (qec.type) {
	case V4L2_CTRL_TYPE_INTEGER:
		dif = qec.maximum - qec.minimum;
		if (dif <= 0xffffU || (qec.flags & V4L2_CTRL_FLAG_SLIDER)) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
			v = static_cast<QSpinBox *>(w)->value();
			break;
		}
		v = static_cast<QLineEdit *>(w)->text().toInt();
		break;

	case V4L2_CTRL_TYPE_BOOLEAN:
		v = static_cast<QCheckBox *>(w)->isChecked();
		break;

	case V4L2_CTRL_TYPE_BITMASK:
		v = (int)static_cast<QLineEdit *>(w)->text().toUInt(0, 16);
		break;
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
		idx = static_cast<QComboBox *>(w)->currentIndex();
<<<<<<< HEAD
<<<<<<< HEAD
		for (i = qec.minimum; i <= qec.maximum; i++) {
			qmenu.id = qec.id;
			qmenu.index = i;
			if (querymenu(qmenu))
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		for (i = qctrl.minimum; i <= qctrl.maximum; i++) {
			qmenu.id = qctrl.id;
			qmenu.index = i;
			if (!querymenu(qmenu))
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
		for (i = qec.minimum; i <= qec.maximum; i++) {
			qmenu.id = qec.id;
			qmenu.index = i;
			if (querymenu(qmenu))
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
				continue;
			if (idx-- == 0)
				break;
		}
		v = i;
		break;

	default:
		break;
	}
	setWhat(w, id, v);
	return v;
}

void ApplicationWindow::updateCtrl(unsigned id)
{
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned which = V4L2_CTRL_ID2WHICH(id);
	if (which == V4L2_CID_PRIVATE_BASE)
		which = V4L2_CTRL_CLASS_USER;
=======
	unsigned ctrl_class = V4L2_CTRL_ID2CLASS(id);
	if (ctrl_class == V4L2_CID_PRIVATE_BASE)
		ctrl_class = V4L2_CTRL_CLASS_USER;
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	unsigned ctrl_class = V4L2_CTRL_ID2CLASS(id);
	if (ctrl_class == V4L2_CID_PRIVATE_BASE)
		ctrl_class = V4L2_CTRL_CLASS_USER;
=======
	unsigned which = V4L2_CTRL_ID2WHICH(id);
	if (which == V4L2_CID_PRIVATE_BASE)
		which = V4L2_CTRL_CLASS_USER;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	if (m_ctrlMap[id].flags & CTRL_FLAG_DISABLED)
		return;

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	if (!m_haveExtendedUserCtrls && ctrl_class == V4L2_CTRL_CLASS_USER) {
		struct v4l2_control c;

		c.id = id;
		c.value = getVal(id);
		if (ioctl(VIDIOC_S_CTRL, &c)) {
			errorCtrl(id, errno, c.value);
		}
		else if (m_ctrlMap[id].flags & V4L2_CTRL_FLAG_UPDATE)
			refresh(ctrl_class);
		return;
	}
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	struct v4l2_ext_control c;
	struct v4l2_ext_controls ctrls;

	memset(&c, 0, sizeof(c));
	memset(&ctrls, 0, sizeof(ctrls));
	c.id = id;
	if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_INTEGER64)
		c.value64 = getVal64(id);
	else if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_STRING) {
		c.size = m_ctrlMap[id].maximum + 1;
		c.string = (char *)malloc(c.size);
		strcpy(c.string, getString(id).toLatin1());
	}
	else
		c.value = getVal(id);
	ctrls.count = 1;
<<<<<<< HEAD
<<<<<<< HEAD
	ctrls.which = which;
=======
	ctrls.ctrl_class = ctrl_class;
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	ctrls.controls = &c;
	if (ioctl(VIDIOC_S_EXT_CTRLS, &ctrls)) {
		errorCtrl(id, errno, c.value);
	}
	else if (m_ctrlMap[id].flags & V4L2_CTRL_FLAG_UPDATE)
		refresh(ctrl_class);
=======
	ctrls.which = which;
	ctrls.controls = &c;
	if (s_ext_ctrls(ctrls)) {
		errorCtrl(id, errno, c.value);
	}
	else if (m_ctrlMap[id].flags & V4L2_CTRL_FLAG_UPDATE)
<<<<<<< HEAD
		refresh(ctrl_class);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
		refresh(which);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	else {
		if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_INTEGER64)
			setVal64(id, c.value64);
		else if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_STRING) {
			setString(id, c.string);
			free(c.string);
		}
		else
			setVal(id, c.value);
	}
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
void ApplicationWindow::refresh(unsigned ctrl_class)
{
	if (!m_haveExtendedUserCtrls && ctrl_class == V4L2_CTRL_CLASS_USER) {
		for (unsigned i = 0; i < m_classMap[ctrl_class].size(); i++) {
			unsigned id = m_classMap[ctrl_class][i];
			v4l2_control c;

			queryctrl(m_ctrlMap[id]);
			if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_BUTTON)
				continue;
			if (m_ctrlMap[id].flags & V4L2_CTRL_FLAG_WRITE_ONLY)
				continue;
			c.id = id;
			if (ioctl(VIDIOC_G_CTRL, &c)) {
				errorCtrl(id, errno);
			}
			setVal(id, c.value);
			m_widgetMap[id]->setDisabled(m_ctrlMap[id].flags & CTRL_FLAG_DISABLED);
		}
		return;
	}
	unsigned count = m_classMap[ctrl_class].size();
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
void ApplicationWindow::updateCtrlRange(unsigned id, __s32 new_val)
{
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QLineEdit *edit;
	QIntValidator *val;
	unsigned dif;

	switch (qec.type) {
	case V4L2_CTRL_TYPE_INTEGER:
		dif = qec.maximum - qec.minimum;
		if (dif <= 0xffffU || (qec.flags & V4L2_CTRL_FLAG_SLIDER)) {
			QSlider *slider = static_cast<QSlider *>(m_sliderMap[id]);
			slider->setMinimum(qec.minimum);
			slider->setMaximum(qec.maximum);
			slider->setSingleStep(qec.step);
			slider->setSliderPosition(new_val);

			QSpinBox *spin = static_cast<QSpinBox *>(m_widgetMap[id]);
			spin->setRange(qec.minimum, qec.maximum);
			spin->setSingleStep(qec.step);
			spin->setValue(new_val);
			break;
		}

		edit = static_cast<QLineEdit *>(m_widgetMap[id]);
		val = new QIntValidator(qec.minimum, qec.maximum, edit->parent());
		// FIXME: will this delete the old validator?
		edit->setValidator(val);
		break;

	case V4L2_CTRL_TYPE_STRING:
		QLineEdit *edit = static_cast<QLineEdit *>(m_widgetMap[id]);
		edit->setMaxLength(qec.maximum);
		break;
	}
}

void ApplicationWindow::subscribeCtrlEvents()
{
	for (ClassMap::iterator iter = m_classMap.begin(); iter != m_classMap.end(); ++iter) {
		for (unsigned i = 0; i < m_classMap[iter->first].size(); i++) {
			unsigned id = m_classMap[iter->first][i];
			struct v4l2_event_subscription sub;

			memset(&sub, 0, sizeof(sub));
			sub.type = V4L2_EVENT_CTRL;
			sub.id = id;
			subscribe_event(sub);
		}
	}
}

void ApplicationWindow::refresh(unsigned which)
{
	unsigned count = m_classMap[which].size();
<<<<<<< HEAD
=======
void ApplicationWindow::refresh(unsigned ctrl_class)
{
	if (!m_haveExtendedUserCtrls && ctrl_class == V4L2_CTRL_CLASS_USER) {
		for (unsigned i = 0; i < m_classMap[ctrl_class].size(); i++) {
			unsigned id = m_classMap[ctrl_class][i];
			v4l2_control c;

			queryctrl(m_ctrlMap[id]);
			if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_BUTTON)
				continue;
			if (m_ctrlMap[id].flags & V4L2_CTRL_FLAG_WRITE_ONLY)
				continue;
			c.id = id;
			if (ioctl(VIDIOC_G_CTRL, &c)) {
				errorCtrl(id, errno);
			}
			setVal(id, c.value);
			m_widgetMap[id]->setDisabled(m_ctrlMap[id].flags & CTRL_FLAG_DISABLED);
		}
		return;
	}
	unsigned count = m_classMap[ctrl_class].size();
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	unsigned cnt = 0;
	struct v4l2_ext_control *c = new v4l2_ext_control[count];
	struct v4l2_ext_controls ctrls;

	for (unsigned i = 0; i < count; i++) {
<<<<<<< HEAD
<<<<<<< HEAD
=======
		unsigned id = c[cnt].id = m_classMap[ctrl_class][i];
		
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		unsigned id = c[cnt].id = m_classMap[which][i];
		
		c[cnt].size = 0;
		c[cnt].reserved2[0] = 0;
<<<<<<< HEAD
=======
		unsigned id = c[cnt].id = m_classMap[ctrl_class][i];
		
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_BUTTON)
			continue;
		if (m_ctrlMap[id].flags & V4L2_CTRL_FLAG_WRITE_ONLY)
			continue;
		if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_STRING) {
			c[cnt].size = m_ctrlMap[id].maximum + 1;
			c[cnt].string = (char *)malloc(c[cnt].size);
		}
		cnt++;
	}
	memset(&ctrls, 0, sizeof(ctrls));
	ctrls.count = cnt;
<<<<<<< HEAD
<<<<<<< HEAD
	ctrls.which = which;
	ctrls.controls = c;
	if (g_ext_ctrls(ctrls)) {
=======
	ctrls.ctrl_class = ctrl_class;
	ctrls.controls = c;
	if (ioctl(VIDIOC_G_EXT_CTRLS, &ctrls)) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	ctrls.ctrl_class = ctrl_class;
	ctrls.controls = c;
	if (ioctl(VIDIOC_G_EXT_CTRLS, &ctrls)) {
=======
	ctrls.which = which;
	ctrls.controls = c;
	if (g_ext_ctrls(ctrls)) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		if (ctrls.error_idx >= ctrls.count) {
			error(errno);
		}
		else {
			errorCtrl(c[ctrls.error_idx].id, errno);
		}
	}
	else {
		for (unsigned i = 0; i < ctrls.count; i++) {
			unsigned id = c[i].id;
			
<<<<<<< HEAD
<<<<<<< HEAD
			query_ext_ctrl(m_ctrlMap[id]);
=======
			queryctrl(m_ctrlMap[id]);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
			queryctrl(m_ctrlMap[id]);
=======
			query_ext_ctrl(m_ctrlMap[id]);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
			if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_INTEGER64)
				setVal64(id, c[i].value64);
			else if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_STRING) {
				setString(id, c[i].string);
				free(c[i].string);
			}
			else
				setVal(id, c[i].value);
<<<<<<< HEAD
<<<<<<< HEAD
=======
			m_widgetMap[id]->setDisabled(m_ctrlMap[id].flags & CTRL_FLAG_DISABLED);
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

			bool disabled = m_ctrlMap[id].flags & CTRL_FLAG_DISABLED;

			if (qobject_cast<QLineEdit *>(m_widgetMap[id]))
				static_cast<QLineEdit *>(m_widgetMap[id])->setReadOnly(disabled);
			else
				m_widgetMap[id]->setDisabled(disabled);
			if (m_sliderMap.find(id) != m_sliderMap.end())
				m_sliderMap[id]->setDisabled(disabled);
<<<<<<< HEAD
=======
			m_widgetMap[id]->setDisabled(m_ctrlMap[id].flags & CTRL_FLAG_DISABLED);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		}
	}
	delete [] c;
}

void ApplicationWindow::refresh()
{
	for (ClassMap::iterator iter = m_classMap.begin(); iter != m_classMap.end(); ++iter)
		refresh(iter->first);
}

void ApplicationWindow::setWhat(QWidget *w, unsigned id, const QString &v)
{
<<<<<<< HEAD
<<<<<<< HEAD
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QString what;
	QString flags = getCtrlFlags(qec.flags);

	switch (qec.type) {
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	const v4l2_queryctrl &qctrl = m_ctrlMap[id];
	QString what;
	QString flags = getCtrlFlags(qctrl.flags);

	switch (qctrl.type) {
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QString what;
	QString flags = getCtrlFlags(qec.flags);

	switch (qec.type) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	case V4L2_CTRL_TYPE_STRING:
		w->setWhatsThis(QString("Type: String\n"
					"Minimum: %1\n"
					"Maximum: %2\n"
					"Step: %3\n"
					"Current: %4")
<<<<<<< HEAD
<<<<<<< HEAD
			.arg(qec.minimum).arg(qec.maximum).arg(qec.step).arg(v) + flags);
=======
			.arg(qctrl.minimum).arg(qctrl.maximum).arg(qctrl.step).arg(v) + flags);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
			.arg(qctrl.minimum).arg(qctrl.maximum).arg(qctrl.step).arg(v) + flags);
=======
			.arg(qec.minimum).arg(qec.maximum).arg(qec.step).arg(v) + flags);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		w->setStatusTip(w->whatsThis());
		break;
	default:
		break;
	}
}

void ApplicationWindow::setWhat(QWidget *w, unsigned id, long long v)
{
<<<<<<< HEAD
<<<<<<< HEAD
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QString what;
	QString flags = getCtrlFlags(qec.flags);

	switch (qec.type) {
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	const v4l2_queryctrl &qctrl = m_ctrlMap[id];
	QString what;
	QString flags = getCtrlFlags(qctrl.flags);

	switch (qctrl.type) {
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QString what;
	QString flags = getCtrlFlags(qec.flags);

	switch (qec.type) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	case V4L2_CTRL_TYPE_INTEGER:
		w->setWhatsThis(QString("Type: Integer\n"
					"Minimum: %1\n"
					"Maximum: %2\n"
					"Step: %3\n"
					"Current: %4\n"
					"Default: %5")
<<<<<<< HEAD
<<<<<<< HEAD
			.arg(qec.minimum).arg(qec.maximum).arg(qec.step).arg(v).arg(qec.default_value) + flags);
=======
			.arg(qctrl.minimum).arg(qctrl.maximum).arg(qctrl.step).arg(v).arg(qctrl.default_value) + flags);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
			.arg(qctrl.minimum).arg(qctrl.maximum).arg(qctrl.step).arg(v).arg(qctrl.default_value) + flags);
=======
			.arg(qec.minimum).arg(qec.maximum).arg(qec.step).arg(v).arg(qec.default_value) + flags);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		w->setStatusTip(w->whatsThis());
		break;

	case V4L2_CTRL_TYPE_INTEGER64:
		w->setWhatsThis(QString("Type: Integer64\n"
<<<<<<< HEAD
<<<<<<< HEAD
=======
					"Current: %1").arg(v) + flags);
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
					"Minimum: %1\n"
					"Maximum: %2\n"
					"Step: %3\n"
					"Current: %4\n"
					"Default: %5")
			.arg(qec.minimum).arg(qec.maximum).arg(qec.step).arg(v).arg(qec.default_value) + flags);
<<<<<<< HEAD
=======
					"Current: %1").arg(v) + flags);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		w->setStatusTip(w->whatsThis());
		break;

	case V4L2_CTRL_TYPE_BITMASK:
		w->setWhatsThis(QString("Type: Bitmask\n"
					"Maximum: %1\n"
					"Current: %2\n"
					"Default: %3")
<<<<<<< HEAD
<<<<<<< HEAD
			.arg((unsigned)qec.maximum, 0, 16).arg((unsigned)v, 0, 16)
			.arg((unsigned)qec.default_value, 0, 16) + flags);
=======
			.arg((unsigned)qctrl.maximum, 0, 16).arg((unsigned)v, 0, 16)
			.arg((unsigned)qctrl.default_value, 0, 16) + flags);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
			.arg((unsigned)qctrl.maximum, 0, 16).arg((unsigned)v, 0, 16)
			.arg((unsigned)qctrl.default_value, 0, 16) + flags);
=======
			.arg((unsigned)qec.maximum, 0, 16).arg((unsigned)v, 0, 16)
			.arg((unsigned)qec.default_value, 0, 16) + flags);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		w->setStatusTip(w->whatsThis());
		break;

	case V4L2_CTRL_TYPE_BUTTON:
		w->setWhatsThis(QString("Type: Button") + flags);
		w->setStatusTip(w->whatsThis());
		break;

	case V4L2_CTRL_TYPE_BOOLEAN:
		w->setWhatsThis(QString("Type: Boolean\n"
					"Current: %1\n"
					"Default: %2")
<<<<<<< HEAD
<<<<<<< HEAD
			.arg(v).arg(qec.default_value) + flags);
=======
			.arg(v).arg(qctrl.default_value) + flags);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
			.arg(v).arg(qctrl.default_value) + flags);
=======
			.arg(v).arg(qec.default_value) + flags);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		w->setStatusTip(w->whatsThis());
		break;

	case V4L2_CTRL_TYPE_MENU:
		w->setWhatsThis(QString("Type: Menu\n"
					"Minimum: %1\n"
					"Maximum: %2\n"
					"Current: %3\n"
					"Default: %4")
<<<<<<< HEAD
<<<<<<< HEAD
			.arg(qec.minimum).arg(qec.maximum).arg(v).arg(qec.default_value) + flags);
=======
			.arg(qctrl.minimum).arg(qctrl.maximum).arg(v).arg(qctrl.default_value) + flags);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
			.arg(qctrl.minimum).arg(qctrl.maximum).arg(v).arg(qctrl.default_value) + flags);
=======
			.arg(qec.minimum).arg(qec.maximum).arg(v).arg(qec.default_value) + flags);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		w->setStatusTip(w->whatsThis());
		break;

	case V4L2_CTRL_TYPE_INTEGER_MENU:
		w->setWhatsThis(QString("Type: Integer Menu\n"
					"Minimum: %1\n"
					"Maximum: %2\n"
					"Current: %3\n"
					"Default: %4")
<<<<<<< HEAD
<<<<<<< HEAD
			.arg(qec.minimum).arg(qec.maximum).arg(v).arg(qec.default_value) + flags);
=======
			.arg(qctrl.minimum).arg(qctrl.maximum).arg(v).arg(qctrl.default_value) + flags);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
			.arg(qctrl.minimum).arg(qctrl.maximum).arg(v).arg(qctrl.default_value) + flags);
=======
			.arg(qec.minimum).arg(qec.maximum).arg(v).arg(qec.default_value) + flags);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
		w->setStatusTip(w->whatsThis());
		break;
	default:
		break;
	}
}

void ApplicationWindow::setVal(unsigned id, int v)
{
<<<<<<< HEAD
<<<<<<< HEAD
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	v4l2_querymenu qmenu;
	QWidget *w = m_widgetMap[qec.id];
	int i, idx;
	unsigned dif;

	switch (qec.type) {
	case V4L2_CTRL_TYPE_INTEGER:
		dif = qec.maximum - qec.minimum;
		if (dif <= 0xffffU || (qec.flags & V4L2_CTRL_FLAG_SLIDER))
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	const v4l2_queryctrl &qctrl = m_ctrlMap[id];
	v4l2_querymenu qmenu;
	QWidget *w = m_widgetMap[qctrl.id];
	int i, idx;

	switch (qctrl.type) {
	case V4L2_CTRL_TYPE_INTEGER:
		if (qctrl.flags & V4L2_CTRL_FLAG_SLIDER)
			static_cast<QSlider *>(w)->setValue(v);
		else if (qctrl.maximum - qctrl.minimum <= 255)
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	v4l2_querymenu qmenu;
	QWidget *w = m_widgetMap[qec.id];
	int i, idx;
	unsigned dif;

	switch (qec.type) {
	case V4L2_CTRL_TYPE_INTEGER:
		dif = qec.maximum - qec.minimum;
		if (dif <= 0xffffU || (qec.flags & V4L2_CTRL_FLAG_SLIDER))
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
			static_cast<QSpinBox *>(w)->setValue(v);
		else
			static_cast<QLineEdit *>(w)->setText(QString::number(v));
		break;

	case V4L2_CTRL_TYPE_BITMASK:
		static_cast<QLineEdit *>(w)->setText(QString("%1").arg((unsigned)v, 8, 16, QChar('0')));
		break;

	case V4L2_CTRL_TYPE_BOOLEAN:
		static_cast<QCheckBox *>(w)->setChecked(v);
		break;

	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
		idx = 0;
<<<<<<< HEAD
<<<<<<< HEAD
		for (i = qec.minimum; i <= v; i++) {
=======
		for (i = qctrl.minimum; i <= v; i++) {
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
			qmenu.id = id;
			qmenu.index = i;
			if (!querymenu(qmenu))
=======
		for (i = qec.minimum; i <= v; i++) {
			qmenu.id = id;
			qmenu.index = i;
<<<<<<< HEAD
			if (!querymenu(qmenu))
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
			if (querymenu(qmenu))
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
				continue;
			idx++;
		}
		static_cast<QComboBox *>(w)->setCurrentIndex(idx - 1);
		break;
	default:
		break;
	}
	setWhat(w, id, v);
}

void ApplicationWindow::setVal64(unsigned id, long long v)
{
<<<<<<< HEAD
<<<<<<< HEAD
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qec.id];

	switch (qec.type) {
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	const v4l2_queryctrl &qctrl = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qctrl.id];

	switch (qctrl.type) {
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qec.id];

	switch (qec.type) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	case V4L2_CTRL_TYPE_INTEGER64:
		static_cast<QLineEdit *>(w)->setText(QString::number(v));
		break;
	default:
		break;
	}
	setWhat(w, id, v);
}

void ApplicationWindow::setString(unsigned id, const QString &v)
{
<<<<<<< HEAD
<<<<<<< HEAD
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qec.id];

	switch (qec.type) {
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	const v4l2_queryctrl &qctrl = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qctrl.id];

	switch (qctrl.type) {
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	const v4l2_query_ext_ctrl &qec = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qec.id];

	switch (qec.type) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	case V4L2_CTRL_TYPE_STRING:
		static_cast<QLineEdit *>(w)->setText(v);
		break;
	default:
		break;
	}
<<<<<<< HEAD
<<<<<<< HEAD
	setWhat(w, id, QString("'") + v + "'");
}

void ApplicationWindow::setDefaults(unsigned which)
{
	for (unsigned i = 0; i < m_classMap[which].size(); i++) {
		unsigned id = m_classMap[which][i];
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	setWhat(w, id, v);
}

void ApplicationWindow::setDefaults(unsigned ctrl_class)
{
	for (unsigned i = 0; i < m_classMap[ctrl_class].size(); i++) {
		unsigned id = m_classMap[ctrl_class][i];
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	setWhat(w, id, QString("'") + v + "'");
}

void ApplicationWindow::setDefaults(unsigned which)
{
	for (unsigned i = 0; i < m_classMap[which].size(); i++) {
		unsigned id = m_classMap[which][i];
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

		if (m_ctrlMap[id].flags & V4L2_CTRL_FLAG_READ_ONLY)
			continue;
		if (m_ctrlMap[id].flags & V4L2_CTRL_FLAG_GRABBED)
			continue;
		if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_INTEGER64)
			setVal64(id, 0);
		else if (m_ctrlMap[id].type == V4L2_CTRL_TYPE_STRING)
			setString(id, QString(m_ctrlMap[id].minimum, ' '));
		else if (m_ctrlMap[id].type != V4L2_CTRL_TYPE_BUTTON)
			setVal(id, m_ctrlMap[id].default_value);
	}
<<<<<<< HEAD
<<<<<<< HEAD
	ctrlAction(which | CTRL_UPDATE);
=======
	ctrlAction(ctrl_class | CTRL_UPDATE);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	ctrlAction(ctrl_class | CTRL_UPDATE);
=======
	ctrlAction(which | CTRL_UPDATE);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
}

QString ApplicationWindow::getCtrlFlags(unsigned flags)
{
	QString s;

	if (flags & V4L2_CTRL_FLAG_GRABBED)
		s += "grabbed ";
	if (flags & V4L2_CTRL_FLAG_READ_ONLY)
		s += "readonly ";
	if (flags & V4L2_CTRL_FLAG_UPDATE)
		s += "update ";
	if (flags & V4L2_CTRL_FLAG_INACTIVE)
		s += "inactive ";
	if (flags & V4L2_CTRL_FLAG_VOLATILE)
		s += "volatile ";
	if (flags & V4L2_CTRL_FLAG_SLIDER)
		s += "slider ";
	if (s.length()) s = QString("\nFlags: ") + s;
	return s;
}

