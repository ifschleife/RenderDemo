#pragma once

#include "ViewportTitleBar.h"

#include <QMainWindow>
#include <QWidget>

#include <set>

class QFileInfo;
class QHBoxLayout;
class QLabel;
class QScrollArea;
class QGroupBox;
class QPushButton;
class QSplitter;


class Viewport : public QWidget
{
	Q_OBJECT
public:
	explicit Viewport(const int viewport_number, QWidget* parent = nullptr);

	//virtual QSize sizeHint() const { return QSize(100, 100); }

signals:
	void viewport_closed();

private slots:
	void load_scene(const QFileInfo& file_info);

private:
	QLabel* m_draw_area;
	ViewportTitleBar* m_title_bar;
};


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