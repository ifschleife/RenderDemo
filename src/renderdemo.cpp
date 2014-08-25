#include "renderdemo.h"
#include "Splitter.h"
#include "ViewportPane.h"

#include <QAction>
#include <QFileInfo>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QSizePolicy>
#include <QSplitter>


MainWindow::MainWindow()
	: m_viewports()
	, m_viewport_layout(new QHBoxLayout)
	, m_status_splitter(new QSplitter(Qt::Vertical))
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

	//m_status_splitter->setHandleWidth(30);
	m_status_splitter->setChildrenCollapsible(false);
	m_status_splitter->setOrientation(Qt::Vertical);
	m_status_splitter->addWidget(viewport_widget);
	m_status_splitter->addWidget(new QLabel("Statistics"));

	layout->addWidget(m_status_splitter);
	return layout;
}

void MainWindow::add_viewport()
{
	ViewportPane* viewport = new ViewportPane(m_viewports.size()+1);
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
		ViewportPane* viewport = static_cast<ViewportPane*>(object);
		m_viewports.erase(viewport);
		delete viewport;
	}
}

