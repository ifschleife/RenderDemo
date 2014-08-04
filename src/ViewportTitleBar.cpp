#include "ViewportTitleBar.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>


ViewportTitleBar::ViewportTitleBar(const int viewport_number, QWidget* parent /* = nullptr */)
	: QWidget(parent)
	, m_scene_label(new QLabel(tr("Empty")))
{
	m_scene_label->setContentsMargins(5, 0, 5, 0);

	QString viewport_name = QString(tr("Viewport %1: ")).arg(viewport_number);
	QPushButton* scene_button = new QPushButton("...");
	scene_button->setFixedWidth(25);
	scene_button->setToolTip(tr("Click to select a scene from the file system"));
	QPushButton* maximize_button = new QPushButton;
	QPushButton* close_button = new QPushButton;

	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(new QLabel(viewport_name));
	layout->addWidget(m_scene_label);
	layout->addWidget(scene_button);
	layout->addStretch();
	layout->addWidget(maximize_button);
	layout->addWidget(close_button);
	layout->setMargin(0);
	layout->setSpacing(0);
	setLayout(layout);

	connect(scene_button, SIGNAL(clicked()), this, SLOT(select_scene_dialog()));
	connect(close_button, SIGNAL(clicked()), this, SIGNAL(close_button_clicked()));
	connect(maximize_button, SIGNAL(clicked()), this, SIGNAL(maximize_button_clicked()));

	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}


void ViewportTitleBar::select_scene_dialog()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setViewMode(QFileDialog::List);
	
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
	}

	if (0 < filenames.size())
	{
		QFileInfo file_info = filenames[0];
		m_scene_label->setText(file_info.baseName());
		m_scene_label->setToolTip(filenames[0]);
		emit scene_changed(file_info);
	}
}