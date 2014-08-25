#include "ViewportPane.h"

#include "Viewport.h"
#include "ViewportTitleBar.h"

#include <QFileInfo>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>


ViewportPane::ViewportPane(const int viewport_number, QWidget *parent)
	: QWidget(parent)
	, m_draw_area(new Viewport("foo", this))
	, m_title_bar(new ViewportTitleBar(viewport_number))
	, m_resolution(new QLabel)
	, m_fullscreen_button(new QPushButton("Enable"))
{
	init_layout();

	m_draw_area->setFrameStyle(QFrame::Box);
	m_draw_area->setLineWidth(1);
	m_draw_area->setMinimumSize(100, 100);
	m_draw_area->setGeometry(0, 0, 1024, 768);

	draw_area_resized();

	connect(m_draw_area, SIGNAL(resized()), this, SLOT(draw_area_resized()));
	connect(m_title_bar, SIGNAL(close_button_clicked()), this, SIGNAL(viewport_closed()));
	connect(m_title_bar, SIGNAL(scene_changed(const QFileInfo&)), this, SLOT(load_scene(const QFileInfo&)));
	connect(m_fullscreen_button, SIGNAL(clicked()), m_draw_area, SLOT(showFullScreen()));
}

void ViewportPane::draw_area_resized()
{
	const QRect& res = m_draw_area->geometry();
	QString res_text = QString("%1x%2");
	res_text = res_text.arg(res.width());
	res_text = res_text.arg(res.height());
	m_resolution->setText(res_text);
}

void ViewportPane::init_layout()
{
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setSpacing(0);
	main_layout->addWidget(m_title_bar);

	QSplitter* splitter = new QSplitter;
	splitter->setChildrenCollapsible(false);
	splitter->addWidget(m_draw_area);

	QWidget* options_widget = new QWidget;
	QFormLayout* options_layout = new QFormLayout;

	options_layout->addRow(tr("Fullscreen"), m_fullscreen_button);
	options_layout->addRow(tr("Resolution:"), m_resolution);

	options_widget->setLayout(options_layout);

	splitter->addWidget(options_widget);

	main_layout->addWidget(splitter);

	setLayout(main_layout);
}

void ViewportPane::load_scene(const QFileInfo& file_info)
{
	m_draw_area->setText(file_info.baseName());
}