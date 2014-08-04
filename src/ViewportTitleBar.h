#pragma once

#include <QWidget>


class QFileInfo;
class QLabel;


class ViewportTitleBar : public QWidget
{
	Q_OBJECT
public:
	explicit ViewportTitleBar(const int viewport_number, QWidget* parent = nullptr);
	//virtual QSize minimumSizeHint() const { return QSize(100, 100); }

signals:
	void close_button_clicked();
	void maximize_button_clicked();
	void scene_changed(const QFileInfo& file_info);

private slots:
	void select_scene_dialog();

private:
	QLabel* m_scene_label;
};