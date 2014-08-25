#pragma once

#include <QWidget>


class QFileInfo;
class QLabel;
class QPushButton;
class ViewportTitleBar;
class Viewport;


class ViewportPane : public QWidget
{
	Q_OBJECT

public:
	explicit ViewportPane(const int viewport_number, QWidget* parent = nullptr);

	//virtual QSize sizeHint() const { return QSize(100, 100); }

signals:
	void viewport_closed();

private slots:
	void draw_area_resized();
	void load_scene(const QFileInfo& file_info);

private:
	void init_layout();

private:
	Viewport* m_draw_area;
	ViewportTitleBar* m_title_bar;
	QLabel* m_resolution;
	QPushButton* m_fullscreen_button;
};