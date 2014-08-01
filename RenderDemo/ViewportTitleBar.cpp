#include "ViewportTitleBar.h"

#include <QHBoxLayout>
#include <QPushButton>


ViewportTitleBar::ViewportTitleBar(QWidget* parent /* = nullptr */)
	: QWidget(parent)
	, m_maximize_button(new QPushButton)
	, m_close_button(new QPushButton)
{
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

	QHBoxLayout* layout = new QHBoxLayout;
	layout->addStretch();
	layout->addWidget(m_maximize_button);
	layout->addWidget(m_close_button);
	layout->setMargin(0);
	layout->setSpacing(0);
	setLayout(layout);

	connect(m_close_button, SIGNAL(clicked()), this, SIGNAL(close_button_clicked()));
}