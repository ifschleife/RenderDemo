#pragma once

#include <QLabel>


class Viewport : public QLabel
{
	Q_OBJECT

public:
	explicit Viewport(const QString text, QWidget* parent)
		: QLabel(text, parent)
	{
	}

signals:
	void resized();

protected:
	virtual void resizeEvent(QResizeEvent* event)
	{
		emit resized();
	}
};
