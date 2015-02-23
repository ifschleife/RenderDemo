#pragma once

#include <QWidget>
#include <memory>

namespace Ui {
class Viewport;
}

class Viewport : public QWidget
{
    Q_OBJECT

public:
    explicit Viewport(QWidget* parent);
    ~Viewport();

private:
    std::unique_ptr<Ui::Viewport> _ui;
};
