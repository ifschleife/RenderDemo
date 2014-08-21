#include "Viewport.h"

#include "ViewportTitleBar.h"



#include <vector>


void Viewport::resizeEvent(QResizeEvent* event)
{
	emit resized();
}
