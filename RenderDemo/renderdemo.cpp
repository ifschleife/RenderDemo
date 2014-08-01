#include "renderdemo.h"
#include "Splitter.h"

#include <QAction>
#include <QColor>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QSizePolicy>


MainWindow::MainWindow()
	: m_view_ports()
	, m_viewport_splitter(new Splitter(Qt::Horizontal))
	, m_status_splitter(new Splitter(Qt::Vertical))
{
	setGeometry(100, 100, 1200, 800);

	init_menubar();

	RenderWindow* viewport = new RenderWindow;
	m_view_ports.insert(viewport);

	connect(viewport, SIGNAL(viewport_closed()), this, SLOT(close_viewport()));

	QWidget* main_widget = new QWidget(this);

	QLayout* layout = init_splitters();

	main_widget->setLayout(layout);

	setCentralWidget(main_widget);
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

QLayout* MainWindow::init_splitters()
{
	QVBoxLayout* layout = new QVBoxLayout;
	QVBoxLayout* splitter_layout = new QVBoxLayout;
	QWidget* splitter_widget = new QSplitter;

	m_viewport_splitter->setHandleWidth(30);
	m_viewport_splitter->setChildrenCollapsible(false);
	m_viewport_splitter->addWidget(*m_view_ports.begin());

	splitter_layout->addWidget(m_viewport_splitter);
	splitter_widget->setLayout(splitter_layout);

	m_status_splitter->setHandleWidth(30);
	m_status_splitter->setChildrenCollapsible(false);
	m_status_splitter->setOrientation(Qt::Vertical);
	m_status_splitter->addWidget(splitter_widget);
	m_status_splitter->addWidget(new QLabel("Statistics"));

	layout->addWidget(m_status_splitter);
	return layout;
}

void MainWindow::add_viewport()
{
	RenderWindow* viewport = new RenderWindow;
	m_view_ports.insert(viewport);
	m_viewport_splitter->addWidget(viewport);

	connect(viewport, SIGNAL(viewport_closed()), this, SLOT(close_viewport()));
}


void MainWindow::close_viewport()
{
	QHBoxLayout* layout = static_cast<QHBoxLayout*>(centralWidget()->layout());
	QObject* object = sender();
	if (object != nullptr)
	{
		RenderWindow* viewport = static_cast<RenderWindow*>(object);
		m_view_ports.erase(viewport);
		delete viewport;
	}
}


RenderWindow::RenderWindow(QWidget *parent)
	: QWidget(parent)
	, m_draw_area(new QLabel("foo", this))
	, m_title_bar(new ViewportTitleBar)
{
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setSpacing(0);

	main_layout->addWidget(m_title_bar);
	
	connect(m_title_bar, SIGNAL(close_button_clicked()), this, SIGNAL(viewport_closed()));

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