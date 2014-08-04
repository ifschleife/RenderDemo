#pragma once

#include <QMainWindow>

#include <set>


class QHBoxLayout;
class QSplitter;
class Viewport;


class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow();

private:
	void init_menubar();
	QLayout* init_layout();
	
private slots:
	void add_viewport();
	void remove_viewport();

private:
	std::set<Viewport*> m_viewports;
	QHBoxLayout* m_viewport_layout;
	QSplitter* m_status_splitter;
};