#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class Viewport;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

protected:
    bool eventFilter(QObject* object, QEvent* event) override;

private slots:
    void on_actionSingleViewport_triggered();
    void on_actionDualViewports_triggered();
    void on_actionQuadViewports_triggered();

private:
    void hide_viewport(const u_int32_t viewport_index);
    void show_viewport(const u_int32_t viewport_index);

private:
    std::unique_ptr<Ui::MainWindow> _ui;
    std::vector<Viewport*> _all_viewports;
};

#endif // MAINWINDOW_H
