#include "pch.h"
#include "Numberarr.h"

Numberarr::Numberarr(int x, int y)
{
	place = { x,y };
	img.push_back(Image::FromFile(_T(".\\pic\\num0.gif")));
	img.push_back(Image::FromFile(_T(".\\pic\\num1.gif")));
}
