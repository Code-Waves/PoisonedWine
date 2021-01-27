#include "pch.h"
#include "Button.h"

Button::Button()
{}

Button::~Button()
{
}

CPoint Button::rectCenter(CRect rc)
{
    CPoint p{ rc.left + rc.right / 2,rc.top + rc.bottom / 2 };
    return p;
}

bool Button::inRect(CRect rc, CPoint mouse)
{
    if (mouse.x >= rc.left && mouse.x <= rc.left + rc.right)
    {
        if (mouse.y >= rc.top && mouse.y <= rc.top + rc.bottom)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}

void Button::OnMouseMove(CPoint point)
{
        mousepoint = point;
}
