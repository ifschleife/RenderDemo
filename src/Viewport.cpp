#include "Viewport.h"

#include "ViewportTitleBar.h"

#include <QFileInfo>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>


Viewport::Viewport(const int viewport_number, QWidget *parent)
	: QWidget(parent)
	, m_draw_area(new QLabel("foo", this))
	, m_title_bar(new ViewportTitleBar(viewport_number))
{
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setSpacing(0);

	main_layout->addWidget(m_title_bar);
	
	connect(m_title_bar, SIGNAL(close_button_clicked()), this, SIGNAL(viewport_closed()));
	connect(m_title_bar, SIGNAL(scene_changed(const QFileInfo&)), this, SLOT(load_scene(const QFileInfo&)));

	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(m_draw_area);
	layout->setMargin(0);
	layout->setSpacing(0);

	main_layout->addLayout(layout);
	setLayout(main_layout);

	m_draw_area->setFrameStyle(QFrame::Box);
	m_draw_area->setLineWidth(3);
	m_draw_area->setMinimumSize(100, 100);
}

void Viewport::load_scene(const QFileInfo& file_info)
{
	m_draw_area->setText(file_info.baseName());
}