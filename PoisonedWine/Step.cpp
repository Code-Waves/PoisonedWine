#include "pch.h"
#include "Step.h"


Step::Step(HWND hWnd)
{
    GetClientRect(hWnd, &m_rcClient);
    backhomerect = { 10,m_rcClient.Height() - 80,(int)(backhomeimg->GetWidth()),(int)(backhomeimg->GetHeight()) };
    backhomecen = rectCenter(backhomerect);

    tiaoguorect = { m_rcClient.Width() - 230,m_rcClient.Height() - 80,(int)(backhomeimg->GetWidth()),(int)(backhomeimg->GetHeight()) };
    tiaoguocen = rectCenter(tiaoguorect);

    CString img0, img1;
    for (int i = 0; i < 10; i++)
    {
        CString s;
        s.Format(_T(".\\pic\\num%d.gif"), i);

        //30天
        timeimg.push_back(Image::FromFile(s));

        numarr.push_back(new Numberarr(225+67*i, 30));

            img0.Format(_T(".\\pic\\bandman%d0.gif"), i);
            img1.Format(_T(".\\pic\\bandman%d1.gif"), i);
            s.Format(_T(".\\pic\\num%d.gif"), i + 1);
            bandmans.push_back(new BandMan(img0, img1, s, 35 + i * (35 + 70), 430, 70, 70));
    }

}

void Step::toZero()
{
    for (int i = 0; i < 10; i++)
        bi[i] = 0;
}

void Step::toBinary(int num)
{
    int index = 9;
    while (num)
    {
        bi[index] = num % 2;
        num = num / 2;
        index--;
    }
}

void Step::init()
{
    index1 = 0;
    index2 = 0;
    bofang = true;
    shi = 0;
    ge = 0;
    toZero();
    characterinit();
}

//跳过     主菜单
void Step::Choose(bool& inico1, bool& inico2, Gdiplus::Graphics& gh)
{
    if (step < 4)
    {
        if (inRect(tiaoguorect, mousepoint))//跳过
        {
            inico1 = true;
            gh.DrawImage(tiaoguoimg, (tiaoguocen.x - tiaoguoimg->GetWidth() / 2 - 10), (tiaoguocen.y - tiaoguoimg->GetHeight() / 2 - 4), 220, 88);
        }
        else//鼠标未进入
        {
            inico1 = false;
            gh.DrawImage(tiaoguoimg, tiaoguocen.x - tiaoguoimg->GetWidth() / 2, tiaoguocen.y - tiaoguoimg->GetHeight() / 2, tiaoguorect.right, tiaoguorect.bottom);
        }
    }
    ///

    if (inRect(backhomerect, mousepoint))//主菜单
    {
        inico2 = true;
        gh.DrawImage(backhomeimg, (backhomecen.x - backhomeimg->GetWidth() / 2 - 10), (backhomecen.y - backhomeimg->GetHeight() / 2 - 4), 220, 88);
    }
    else//鼠标未进入
    {
        inico2 = false;
        gh.DrawImage(backhomeimg, backhomecen.x - backhomeimg->GetWidth() / 2, backhomecen.y - backhomeimg->GetHeight() / 2, backhomerect.right, backhomerect.bottom);
    }

}

void Step::characterinit()
{
    for (int i = 0; i < 10; i++)
    {
        //38 + i * (38 + 70), 430, 70, 70)
        bandmans[i]->place.left = 38 + i * (38 + 70);
        bandmans[i]->place.top = 430;
    }
    hei = 0;
}

void Step::Draw(bool& inico1, bool& inico2, int& gamestate, Gdiplus::Graphics& gh)
{
    if (step == 1)
    {
        Firststep(inico1, inico2, gh);
    }
    else if (step == 2)
    {
        Secondstep(inico1, inico2, gh);
    }
    else if (step == 3)
    {
        Endstep(inico1, inico2, gh);
    }
    else if (step == 4)
    {
        Progra(inico1, inico2, gh);
    }
 
}

//第一步
void Step::Firststep(bool& inico1, bool& inico2, Gdiplus::Graphics& gh)
{
    CString words = L"有了二进制表示数字这个方法以后,我们就能够找出毒酒桶。\r\n找出下毒毒酒桶的第一步,\r\n我们先将这一千个酒桶通过十进制从1到1000进行编号,\r\n再将十进制的编号转化成二进制。\r\n因为我们有十个奴隶,所以我们用十位二进制数来表示,\r\n比如1的二进制,我们用0000000001来表示,\r\n1000的二进制我们用1111101000来表示。";
    if (bofang)
    {
        PlaySound(L".\\music\\第一步编号.wav", NULL, SND_ASYNC | SND_FILENAME);
        time1 = GetTickCount64();
    }
    bofang= false;

    gh.DrawImage(backgroundimg, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());


    if (::GetTickCount64() - time1 > 13000)
    {
        static int i = 0;
        if (i < 1100)
            i += 9;
        Rect rect{ 0,300,i,145 };
        gh.DrawImage(jiuimg, rect, 0, 0, i, 145, UnitPixel);
        if (::GetTickCount64() - time1> 20000)//二进制
        {
            static int k = 0;
            if (k < 1110)
                k += 9;
            Rect rect{ 0,450,k,80 };
            gh.DrawImage(img0999, rect, 0, 0, k, 145, UnitPixel);
        }
    }

    Choose(inico1, inico2, gh);

    if (::GetTickCount64() - time1 > 35000)
    {
        step++;
        init();
   }
   PointF origin{250,0 };
    SolidBrush m_brush{ Color::Black };// 输出FPS文字用的画刷
    Gdiplus::Font m_font{ L"楷体",15.0,CFE_BOLD };    // 输出文字字体
    //// 输出的文字

    index1++;
    CString s = words.Left((int)(index1 /su));

    gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);
    static int k = 0, bb = 0;
    k++;
    if (k % 5== 1)
    {
        bb = bb == 1 ? 0 : 1;
    }
}

double Step::Theta(CPoint T, CPoint V)//弧度制
{
    return abs(atan2(-(T.y-V.y),T.x-V.x));
}

void Step::Secondstep(bool& inico1, bool& inico2, Gdiplus::Graphics& gh)
{
    //CString words = L"找出下毒毒酒桶的第二步是对国王选择的这十个决定牺牲的奴隶从一到十对十个奴隶进行编号。\r\n关键的第三步是以身来试毒酒。我们让一号奴隶喝所有的酒桶的二进制数字中,\r\n第一位是一数字的酒,比如说第599、第688、第751等,\r\n这些酒桶的二进制编码第一位数字都是一。\r\n紧接着我们让二号奴隶去喝所有的酒桶二进制编号中，从第二位是一的酒桶编号的酒,\r\n三号奴隶去喝所有的酒桶二进制编号中,从第三位是一的酒桶编号的酒,\r\n以此类推。\r\n对于第十号奴隶来说,他所喝的酒的酒桶的编号为第十位是一。";
    if (bofang)
    {
        PlaySound(L".\\music\\第二三步.wav", NULL, SND_ASYNC | SND_FILENAME);
        time1 = GetTickCount64();
        characterinit();
    }
    bofang= false;

    gh.DrawImage(backgroundimg, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());

    static int i = 0;
    bool tt = true;
    if (::GetTickCount64() - time1 > 5000&& ::GetTickCount64() - time1 <11000)///编号动画
    {
        tt = true;
        if (i < 1100)
            i += 12;
        Rect rect{ 0,350,i,68 };
        gh.DrawImage(img110, rect, 0, 0, i, 68, UnitPixel);
    }
    else if(::GetTickCount64() - time1 >11000)
    {
        tt = false;
        i = 0;
    }

    if (::GetTickCount64() - time1 > 18000)///编二进制
    {
        static int i = 0;
        i++;
        if (i < 1067)
            i += 3;
        Rect rect{ 0,180,i,139};
        gh.DrawImage(Image::FromFile(_T(".\\pic\\step1.gif")), rect, 0, 0, i, 139, UnitPixel);
    }
  
    static int k = 0, bb = 0;
    k++;
    if (k % 5 == 1)
    {
        bb = bb == 1 ? 0 : 1;
    }

    static CPoint p1{ 245,100 }, p2{ 525,100 }, p3{ 805 ,100 };//新位置
    static CPoint t1{ 38,430 }, t2{ 146,430}, t3{ 184,430};


    /*CString s;
    s.Format(L"%f", Theta(p2, t1));
    AfxMessageBox(s);*/
    if (::GetTickCount64() - time1 >12000)/////一号二号三号奴隶
    {
            if (bandmans[0]->place.left <= 245&& bandmans[0]->place.top>100)
            {
                bandmans[0]->place.left+= (LONG)4*cos((Theta(p1, t1)));
                bandmans[0]->place.top -= (LONG)4 * sin(Theta(p1, t1));
            }
            if ( bandmans[1]->place.left <=525 && bandmans[1]->place.top > 100)
            {
                bandmans[1]->place.left += (LONG)4 * cos(Theta(p2, t2));
                bandmans[1]->place.top -= (LONG)4 * sin(Theta(p2, t2));
            }
            if ( bandmans[2]->place.left<=805 && bandmans[2]->place.top > 100)
            {
                bandmans[2]->place.left +=(LONG) 4 * cos(Theta(p3, t3));
                bandmans[2]->place.top -= (LONG)4 * sin(Theta(p3, t3));
            }
 }



    if (::GetTickCount64() - time1 > 50000)//播放完毕
    {
            step++;
            init();
    }

    Choose(inico1, inico2, gh);

    //PointF origin{ 0.0f,0.0f };
    //SolidBrush m_brush{ Color::Black };// 输出FPS文字用的画刷
    //Gdiplus::Font m_font{ L"楷体",12.0,CFE_BOLD };    // 输出文字字体
    //// 输出的文字

    //index2++;
    //CString s = words.Left(index2/ 3.5);

   // gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);
   

    for (int i = 0; i < bandmans.size(); i++)
    {
        gh.DrawImage(bandmans[i]->character[bb], bandmans[i]->place.left, bandmans[i]->place.top, 70, 70);
        if(!tt)
        gh.DrawImage(bandmans[i]->numimg, bandmans[i]->place.left+10, bandmans[i]->place.top-80);
    }
    if (k > 7000000)k = 1;
}

void Step::Endstep(bool& inico1, bool& inico2, Gdiplus::Graphics& gh)
{

    if (bofang)
    {
        toZero();
        time3 = GetTickCount64();
        characterinit();
        PlaySound(L".\\music\\最后一步.wav", NULL, SND_ASYNC | SND_FILENAME);
    }
    bofang = false;

    gh.DrawImage(backgroundimg, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());

    if (::GetTickCount64() - time3 > 11000)bi[0] = 1;//一号死亡  一号数字变为1
    if (::GetTickCount64() - time3 > 24000)bi[0] = 0;//没有死

    for (int i = 0; i < 10; i++)
        gh.DrawImage(numarr[i]->img[bi[i]], numarr[i]->place.x, numarr[i]->place.y);

    Choose(inico1, inico2, gh);

    if (::GetTickCount64() - time3 > 44000)
    {
            step++;
            init();
   }

    SolidBrush m_brush{ Color::Black };// 输出FPS文字用的画刷
    Gdiplus::Font m_font{ L"楷体",14.0,CFE_BOLD };    // 输出文字字体


    static int k = 0, bb = 0;
    k++;
    if (k % 5 == 1)
    {
        bb = bb == 1 ? 0 : 1;
    }

    if (hei < 100)
        hei++;

    for (int i = 0; i < bandmans.size(); i++)
    {
        if (::GetTickCount64() - time3 > 8000&& ::GetTickCount64() - time3 <22000 &&i==0)
        {
            gh.DrawImage(bandmans[i]->dieimg, bandmans[i]->place.left, bandmans[i]->place.top - hei, 70, 70);
            gh.DrawImage(bandmans[i]->numimg, bandmans[i]->place.left, bandmans[i]->place.top - 60 - hei);
        }
        else
        {
            gh.DrawImage(bandmans[i]->character[bb], bandmans[i]->place.left, bandmans[i]->place.top - hei, 70, 70);
            gh.DrawImage(bandmans[i]->numimg, bandmans[i]->place.left, bandmans[i]->place.top - 60 - hei);
        }
      
    }
    if (k > 7000000)k = 1;
}
void Step::Progra(bool& inico1, bool& inico2, Gdiplus::Graphics& gh)
{
      if (bofang)
    {
        time4 = GetTickCount64();
        PlaySound(L".\\music\\完整演示.wav", NULL, SND_ASYNC | SND_FILENAME);
    }
    bofang = false;

    gh.DrawImage(backgroundimg, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());

    Choose(inico1, inico2, gh);





    //绘制30天
    static bool to30day = false;//到30天了

    static ULONGLONG time = ::GetTickCount64();
    static ULONGLONG timettt = ::GetTickCount64();

    {
            gh.DrawImage(timeimg[shi],895,0,63,93);
            gh.DrawImage(timeimg[ge],950, 0, 63, 93);
            gh.DrawImage(Image::FromFile(_T(".\\pic\\天.gif")),1000, 0,103,93);//天字

            if (::GetTickCount64()-time>300&&!(shi==3&&ge==1))
            {
                ge++;
                if (ge > 9)
                {
                    shi++;
                    ge = 0;
                }
                time = ::GetTickCount64();
            }
            else if(shi == 3 && ge == 1)
            {
                to30day = true;
            }

    }


    //绘制二进制数组
    if (to30day&& ::GetTickCount64() - timettt > 16000)
    {
        toBinary(632);
        for (int i = 0; i < 10; i++)
            gh.DrawImage(numarr[i]->img[bi[i]], numarr[i]->place.x, numarr[i]->place.y);
    }
    else
    {
        for (int i = 0; i < 10; i++)
            gh.DrawImage(numarr[i]->img[bi[i]], numarr[i]->place.x, numarr[i]->place.y);
    }



    if (::GetTickCount64() - timettt > 34000)//绘制数字
    {
        static int i = 0;
        if (i < 138)
            i += 2;
        Rect rect{ 500,150,i,60 };
        gh.DrawImage(Image::FromFile(_T(".\\pic\\632.gif")), rect, 0, 0, i, 60, UnitPixel);
    }


    static int k = 0, bb = 0;
    k++;
    if (k % 5 == 1)
    {
        bb = bb == 1 ? 0 : 1;
    }

    if (hei < 100)
        hei++;

    for (int i = 0; i < bandmans.size(); i++)
    {
        if (to30day)
        {
            if (i == 0 || i == 3 || i == 4 || i == 5 || i == 6)
            {
                gh.DrawImage(bandmans[i]->dieimg, bandmans[i]->place.left, bandmans[i]->place.top - hei, 70, 70);
                gh.DrawImage(bandmans[i]->numimg, bandmans[i]->place.left, bandmans[i]->place.top - 60 - hei);
            }
            else
            {
                gh.DrawImage(bandmans[i]->character[bb], bandmans[i]->place.left, bandmans[i]->place.top - hei, 70, 70);
                gh.DrawImage(bandmans[i]->numimg, bandmans[i]->place.left, bandmans[i]->place.top - 60 - hei);
            }
        }
        else
        {
            gh.DrawImage(bandmans[i]->character[bb], bandmans[i]->place.left, bandmans[i]->place.top - hei, 70, 70);
            gh.DrawImage(bandmans[i]->numimg, bandmans[i]->place.left, bandmans[i]->place.top - 60 - hei);
        }

    }
    if (k > 7000000)k = 1;
}
