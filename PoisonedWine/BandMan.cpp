#include "pch.h"
#include "BandMan.h"
BandMan::BandMan(CString character0, CString character1, CString num, int x, int y, int w, int h)
{
	character.push_back(Image::FromFile(character0));
	character.push_back(Image::FromFile(character1));
	centerpoint = { x + 35,y};
	numimg= Image::FromFile(num);
	place = { x,y,w,h };
}
BandMan::~BandMan()
{
}