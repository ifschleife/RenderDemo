#pragma once

#include <QWidget>


class QPushButton;


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