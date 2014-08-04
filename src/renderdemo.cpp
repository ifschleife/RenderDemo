#include "renderdemo.h"
#include "Splitter.h"

#include <QAction>
#include <QColor>
#include <QFileInfo>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QSizePolicy>


MainWindow::MainWindow()
	: m_viewports()
	, m_viewport_layout(new QHBoxLayout)
	, m_status_splitter(new Splitter(Qt::Vertical))
{
	setGeometry(100, 100, 1200, 800);

	init_menubar();

	QWidget* main_widget = new QWidget(this);
	QLayout* layout = init_layout();
	main_widget->setLayout(layout);
	setCentralWidget(main_widget);

	add_viewport();
}

void MainWindow::init_menubar()
{
	QMenuBar* menubar = new QMenuBar;
	QMenu* viewport_menu = menubar->addMenu("Viewports");

	QAction* add_viewport_action = new QAction("Add Viewport", this);

	viewport_menu->addAction(add_viewport_action);

	connect(add_viewport_action, SIGNAL(triggered()), this, SLOT(add_viewport()));

	setMenuBar(menubar);
}

QLayout* MainWindow::init_layout()
{
	QVBoxLayout* layout = new QVBoxLayout;
	QWidget* viewport_widget = new QWidget;

	viewport_widget->setLayout(m_viewport_layout);

	m_status_splitter->setHandleWidth(30);
	m_status_splitter->setChildrenCollapsible(false);
	m_status_splitter->setOrientation(Qt::Vertical);
	m_status_splitter->addWidget(viewport_widget);
	m_status_splitter->addWidget(new QLabel("Statistics"));

	layout->addWidget(m_status_splitter);
	return layout;
}

void MainWindow::add_viewport()
{
	Viewport* viewport = new Viewport(m_viewports.size()+1);
	m_viewports.insert(viewport);
	m_viewport_layout->addWidget(viewport);

	connect(viewport, SIGNAL(viewport_closed()), this, SLOT(remove_viewport()));
}


void MainWindow::remove_viewport()
{
	QHBoxLayout* layout = static_cast<QHBoxLayout*>(centralWidget()->layout());
	QObject* object = sender();
	if (object != nullptr)
	{
		Viewport* viewport = static_cast<Viewport*>(object);
		m_viewports.erase(viewport);
		delete viewport;
	}
}


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