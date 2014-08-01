#pragma once

#include <QMainWindow>
#include <QWidget>

#include <set>

class QLabel;
class QScrollArea;
class QGroupBox;
class QPushButton;
class QSplitter;


class ViewportTitleBar : public QWidget
{
	Q_OBJECT
public:
	explicit ViewportTitleBar(QWidget* parent = nullptr);
	//virtual QSize minimumSizeHint() const { return QSize(100, 100); }

private:
	QPushButton* m_maximize_button;
	QPushButton* m_close_button;

signals:
	void close_button_clicked();
};


class RenderWindow : public QWidget
{
	Q_OBJECT
public:
	explicit RenderWindow(QWidget* parent = nullptr);

	//virtual QSize sizeHint() const { return QSize(100, 100); }

signals:
	void viewport_closed();

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
	QLayout* init_splitters();
	
private slots:
	void add_viewport();
	void close_viewport();

private:
	std::set<RenderWindow*> m_view_ports;
	QSplitter* m_viewport_splitter;
	QSplitter* m_status_splitter;
};