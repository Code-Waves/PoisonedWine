#pragma once
class Numberarr
{
public:
    Numberarr(int x, int y);
    //Gdiplus::Image* num0 = Image::FromFile(_T(".\\pic\\num0.gif"));
    //Gdiplus::Image* num1 = Image::FromFile(_T(".\\pic\\num1.gif"));
    std::vector<Image*>img;
    int num=0;
    CPoint place;

};

