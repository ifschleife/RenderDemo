#pragma once

#include <QWidget>


class QFileInfo;
class QLabel;
class QScrollArea;
class QGroupBox;
class ViewportTitleBar;


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