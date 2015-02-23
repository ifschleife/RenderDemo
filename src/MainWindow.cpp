#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Viewport.h"

#include <assert.h>
#include <QtDebug>
#include <QKeyEvent>
#include <QKeySequence>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
    , _ui{new Ui::MainWindow}
{
    _ui->setupUi(this);

    _all_viewports = {_ui->Viewport0, _ui->Viewport1, _ui->Viewport2, _ui->Viewport3};
    _ui->Viewport1->hide();
    _ui->Viewport2->hide();
    _ui->Viewport3->hide();

    QActionGroup* group{new QActionGroup(_ui->mainToolBar)};
    group->addAction(_ui->actionSingleViewport);
    group->addAction(_ui->actionDualViewports);
    group->addAction(_ui->actionQuadViewports);

    installEventFilter(this);
}

MainWindow::~MainWindow() { }


bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (object == this)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
            if (QKeySequence::Close == key_event)
            {
                qDebug() << "Exiting...";
                QApplication::quit();
            }
        }

        return false;
    }
    else
    {
        return QMainWindow::eventFilter(object, event);
    }
}

void MainWindow::on_actionSingleViewport_triggered()
{
    hide_viewport(1);
    hide_viewport(2);
    hide_viewport(3);
}

void MainWindow::on_actionDualViewports_triggered()
{
    hide_viewport(2);
    hide_viewport(3);

    show_viewport(1);
}

void MainWindow::on_actionQuadViewports_triggered()
{
    show_viewport(1);
    show_viewport(2);
    show_viewport(3);
}

void MainWindow::hide_viewport(const u_int32_t viewport_index)
{
    assert(nullptr != _all_viewports[viewport_index]);

    _all_viewports[viewport_index]->setEnabled(false);
    _all_viewports[viewport_index]->hide();
}

void MainWindow::show_viewport(const u_int32_t viewport_index)
{
    assert(nullptr != _all_viewports[viewport_index]);

    Viewport* viewport = _all_viewports[viewport_index];
    viewport->setEnabled(true);
    viewport->show();
}
