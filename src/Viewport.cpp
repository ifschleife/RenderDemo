#include "Viewport.h"
#include "ui_Viewport.h"

Viewport::Viewport(QWidget* parent)
    : QWidget{parent}
    , _ui{new Ui::Viewport}
{
    _ui->setupUi(this);
}

Viewport::~Viewport() { }
