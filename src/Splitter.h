#pragma once

#include <QSplitter>


class Splitter : public QSplitter
{
public:
	Splitter(const Qt::Orientation orientation, QWidget* parent = nullptr);

protected:
	virtual QSplitterHandle* createHandle();
};


class SplitterHandle : public QSplitterHandle
{
public:
	SplitterHandle(const Qt::Orientation orientation, QSplitter* parent = nullptr);

protected:
	virtual bool eventFilter(QObject* object, QEvent* event) override;
	virtual void paintEvent(QPaintEvent* event) override;

private:
	QColor m_triangle_color;
	QColor m_handle_delimiter_color;
};