#include "Splitter.h"

#include <QPainter>
#include <QPaintEvent>


Splitter::Splitter(const Qt::Orientation orientation, QWidget* parent /* = nullptr */)
	: QSplitter(orientation, parent)
{

}

QSplitterHandle* Splitter::createHandle()
{
	return new SplitterHandle(orientation(), this);
}


SplitterHandle::SplitterHandle(const Qt::Orientation orientation, QSplitter* parent /* = nullptr */)
	: QSplitterHandle(orientation, parent)
	, m_triangle_color(QColor("darkgrey"))
	, m_handle_delimiter_color(palette().color(QWidget::backgroundRole()))
{
	installEventFilter(this);
}

bool SplitterHandle::eventFilter(QObject* object, QEvent* event)
{
	if (object == this)
	{
		if (event->type() == QEvent::Enter)
		{
			m_triangle_color = QColor("black");
			m_handle_delimiter_color = QColor("black");
			update();
			return true;
		}
		else if (event->type() == QEvent::Leave)
		{
			m_triangle_color = QColor("darkgrey");
			m_handle_delimiter_color = palette().color(QWidget::backgroundRole());
			update();
			return true;
		}
	}
	return false;
}


void SplitterHandle::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QPainterPath triangle_1;
	QPainterPath triangle_2;

	const QRect& rect = event->rect();
	const QPoint& center = rect.center();

	if (orientation() == Qt::Horizontal)
	{
		const int width = rect.width();
		const int triangle_height = (width-10) / 2;

		triangle_1.moveTo(center.x() - 2, center.y() - 20);
		triangle_1.lineTo(center.x() - triangle_height, center.y());
		triangle_1.lineTo(center.x() - 2, center.y() + 20);
		triangle_1.lineTo(center.x() - 2, center.y() - 20);

		triangle_2.moveTo(center.x() + 2, center.y() - 20);
		triangle_2.lineTo(center.x() + triangle_height, center.y());
		triangle_2.lineTo(center.x() + 2, center.y() + 20);
		triangle_2.lineTo(center.x() + 2, center.y() - 20);
	}
	else
	{
		const int height = rect.height();
		const int triangle_height = (height-12) / 2;
		const int start_y_t1 = center.y() - 3;

		triangle_1.moveTo(center.x() - 20, start_y_t1);
		triangle_1.lineTo(center.x(), start_y_t1 - triangle_height);
		triangle_1.lineTo(center.x() + 20, start_y_t1);
		triangle_1.lineTo(center.x() - 20, start_y_t1);

		const int start_y_t2 = center.y() + 3;
		triangle_2.moveTo(center.x() - 20, start_y_t2);
		triangle_2.lineTo(center.x(), start_y_t2 + triangle_height);
		triangle_2.lineTo(center.x() + 20, start_y_t2);
		triangle_2.lineTo(center.x() - 20, start_y_t2);
	}

	QRect rect2 = rect;
	rect2.setWidth(rect.width());
	rect2.moveTop(center.y() - 2);
	rect2.setHeight(4);
	painter.fillRect(rect2, QBrush(m_handle_delimiter_color));

	painter.fillPath(triangle_1, QBrush(m_triangle_color));
	painter.fillPath(triangle_2, QBrush(m_triangle_color));

}