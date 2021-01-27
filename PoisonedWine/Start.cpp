#include "pch.h"
#include "Start.h"
#include "pch.h"

Start::Start(HWND hWnd)
{
    GetClientRect(hWnd, &m_rcClient);
    backhomerect = { 10,m_rcClient.Height() - 80,(int)(backhomeimg->GetWidth()),(int)(backhomeimg->GetHeight()) };
    backhomecen = rectCenter(backhomerect);

    tiaoguorect = { m_rcClient.Width() - 230,m_rcClient.Height() - 80,(int)(backhomeimg->GetWidth()),(int)(backhomeimg->GetHeight()) };
    tiaoguocen = rectCenter(tiaoguorect);

    shuaxinrect = {170,m_rcClient.top +10,(int)(shuaxinimg->GetWidth()),(int)(shuaxinimg->GetHeight()) };
    shuaxincen = rectCenter(shuaxinrect);

    CString img0, img1; 
    for (int i = 0; i < 3; i++)  
    {
        for (int k = 0; k < 2; k++)
        {
            s.Format(_T(".\\pic\\g%d.png"),k);
            king.push_back(Image::FromFile(s));
        }
    }
    s.Format(_T(".\\pic\\g%d.png"),2);
    king.push_back(Image::FromFile(s));

    for(int i = 0; i < 8; i++)//初始化8个奴隶
    {
        img0.Format(_T(".\\pic\\bandman%d0.gif"), i);
        img1.Format(_T(".\\pic\\bandman%d1.gif"), i);
        CString s;
        s.Format(_T(".\\pic\\num%d.gif"), i + 1);
        bandman8.push_back(new BandMan(img0, img1, s, 45 + i * (45 + 90), 400, 70, 70));

        if (i < 6)
        {
            s.Format(_T(".\\pic\\%d.png"), i);
            lnkr.push_back(Image::FromFile(s));
            s.Format(_T(".\\pic\\1%d.png"), i);
            lnkl.push_back(Image::FromFile(s));
       }
    }
    for (int i = 0; i < 10;i++)//初始化10个奴隶
    {
        img0.Format(_T(".\\pic\\bandman%d0.gif"), i);
        img1.Format(_T(".\\pic\\bandman%d1.gif"), i);
        CString s;
        s.Format(_T(".\\pic\\num%d.gif"), i + 1);
        bandmans.push_back(new BandMan(img0, img1, s, 35 + i * (35 + 70), 400, 70, 70));

        s.Format(_T(".\\pic\\num%d.gif"), i);

        //30天
        timeimg.push_back(Image::FromFile(s));

        numimgarr.push_back(new Numberarr(225 + 67 * i, 30));
        binaryarr10.push_back(0);

        if (i < 8)
        {
            binaryarr8.push_back(0);
            numarr8.push_back(new Numberarr(310 + 67 * i, 30));
        }
    }
}

int addnum = 0;
int kingindex = 0;
void Start::toZero()
{
    for (int i = 0; i <binaryarr10.size(); i++)
        binaryarr10[i] = 0;
    for (int i = 0; i < binaryarr8.size(); i++)
        binaryarr8[i] = 0;
}

void Start::toBinary(int num)
{
    int index = 9;
    int index8 = 7;
    int num8 = num;
    while (num)
    {
        binaryarr10[index] = num % 2;
        num = num / 2;
        index--;
    }
    if (num8 < 251)
    {
        while (num8)
        {
            binaryarr8[index8] = num8 % 2;
            num8 = num8 / 2;
            index8--;
        }
   }
}

void Start::init()
{
    bofang = true;

    to1000num = false;
    to250num = false;
    to31day = false;

    createrandom = true;
    kingp = 0;
    day = 1;
    
    hei = 0;

    prebo = true;

    find = false;

    x = 0; y = 0; z = 0; p = 0;

    bandaddindex = 0;
    addbandman = true;

    nqian = 0;
    nbai = 0;
    nshi = 0;
    nge = 0;

    shi = 0;
    ge = 0;
    toZero();

    characterinit();
    first31 = true; first32 = true; first33 = true; first34 = true;
    biuend = true;
   bofang = true;
}

//跳过     主菜单
void Start::Choose(bool& inico1, bool& inico2, bool& inico3,Gdiplus::Graphics& gh)
{
    if (step < 2)//左键点击修改开始音乐
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

    if (inRect(shuaxinrect, mousepoint))//刷新
    {
        inico3 = true;
        gh.DrawImage(shuaxinimg, (shuaxincen.x - shuaxinimg->GetWidth() / 2 - 6), (shuaxincen.y - shuaxinimg->GetHeight() / 2 - 6), 70, 70);
    }
    else//鼠标未进入
    {
        inico3 = false;
        gh.DrawImage(shuaxinimg, shuaxincen.x - shuaxinimg->GetWidth() / 2, shuaxincen.y - shuaxinimg->GetHeight() / 2, shuaxinrect.right, shuaxinrect.bottom);
    }

}

int Start::RandomNumber()
{
    static std::default_random_engine e((unsigned int)time(0));
    static std::uniform_int_distribution<unsigned> u(1,1000);
    return  u(e);
}

void Start::drawpeop(Gdiplus::Graphics& gh)////画人物运动 头上标签  包括是否死亡等 
{
    for (int i = 0; i < bandman8.size(); i++)
    {
        gh.DrawImage(bandman8[i]->numimg, bandman8[i]->place.left+10, bandman8[i]->place.top - 70);
        if (binaryarr8[i] == 1)
            gh.DrawImage(bandman8[i]->dieimg, bandman8[i]->place.left, bandman8[i]->place.top, 70, 70);
        else
            gh.DrawImage(bandman8[i]->character[bb], bandman8[i]->place.left, bandman8[i]->place.top, 70, 70);

        gh.DrawImage(numarr8[i]->img[binaryarr8[i]], numarr8[i]->place.x, numarr8[i]->place.y + 100);
    }
}

double Start::Theta(CPoint T, CPoint V)//弧度制
{
    return abs(atan2(-(T.y - V.y), T.x - V.x));
}
void Start::characterinit()
{
    for (int i = 0; i < 10; i++)
    {
        bandmans[i]->place.left = 35 + i * (35 + 70);
        bandmans[i]->place.top = 400;
        if (i < 8)
        {
            bandman8[i]->place.left = 45 + i * (45 + 90);
            bandman8[i]->place.top = 400;
        }
    }
}

void Start::Draw(bool& inico1, bool& inico2, bool& inico3, int& gamestate,Gdiplus::Graphics& gh)
{
    if (step == 1)
    {
        TenBandMan(inico1, inico2, inico3, gh);
    }
    else if (step == 2)
    {
        EightBandMan(inico1, inico2, inico3,gh);
    }

}

//10个奴隶
void Start::TenBandMan(bool& inico1, bool& inico2, bool& inico3, Gdiplus::Graphics& gh)
{
    static int k = 0;
    k++;
    if (k % 3 == 1)
    {
        bb = bb == 1 ? 0 : 1;
    }

    if (addbandman)
    {
        if (prebo)
        {
            poisonedwinenum = RandomNumber();
            PlaySound(L".\\music\\dododo.wav", NULL, SND_ASYNC | SND_FILENAME| SND_LOOP);
            prebo = false;
        }
        gh.DrawImage(backgroundimg, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());
        Choose(inico1, inico2, inico3, gh);
        s.Format(L"  %d", poisonedwinenum);
        gh.DrawImage(Image::FromFile(_T(".\\pic\\dujiu.png")),0,0,75,75);
        gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);

        for (int i = 0; i <= bandaddindex; i++)
        {
            gh.DrawImage(bandmans[i]->character[bb], bandmans[i]->place.left, bandmans[i]->place.top, 70, 70);
            gh.DrawImage(bandmans[i]->numimg, bandmans[i]->place.left + 10, bandmans[i]->place.top - 70);
        }
        static int k=2;
        k++;
        if (bandaddindex < 10 && k% 19== 1)
        {
            bandaddindex++;
        }
        if (bandaddindex == 10)addbandman = false;
    }
    else
    {
        static ULONGLONG newtime = ::GetTickCount64();
        if (bofang)
        {
            toZero();
            //poisonedwinenum = RandomNumber();
            characterinit();
            newtime = ::GetTickCount64();
            PlaySound(L".\\music\\biu.wav", NULL, SND_ASYNC | SND_FILENAME);
            CTime startime = CTime::GetCurrentTime();//程序开始时间
            ofstream file0("tempstep.txt", ios::out | ios::app);
            file0 << startime.GetHour() << "时" << startime.GetMinute() << "分" << startime.GetSecond() << "秒" << "\t十个奴隶寻找毒酒\t毒酒编号：" << poisonedwinenum << endl;
            file0.close();
        }
        bofang = false;

        gh.DrawImage(backgroundimg, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());


        s.Format(L"  %d", poisonedwinenum);
        gh.DrawImage(Image::FromFile(_T(".\\pic\\dujiu.png")), 0, 0, 75, 75);
        gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);

        //毒酒号数  一直增加

        if (::GetTickCount64() - newtime > 300)
        {
            if (nqian != 1)
            {
                nge++;
                if (nge > 9)
                {
                    nge = 0;
                    nshi += 2;
                    if (nshi > 9)
                    {
                        nshi = 0;
                        nbai += 2;
                        if (nbai > 9)
                        {
                            nbai = 0;
                            nqian++;
                        }
                    }
                }
                gh.DrawImage(Image::FromFile(_T(".\\pic\\酒.png")), 390, 10,62, 79);//酒桶
                gh.DrawImage(timeimg[nqian], 450, 0, 63, 93);
                gh.DrawImage(timeimg[nbai], 515, 0, 63, 93);
                gh.DrawImage(timeimg[nshi], 575, 0, 63, 93);
                gh.DrawImage(timeimg[nge], 635, 0, 63, 93);
            }
            else
            {
                to1000num = true;
                toZero();
            }
        }


        ///二进制数组  自动增长+画线
        {
            if (!to1000num)
            {
                toBinary(nqian * 1000 + nbai * 100 + nshi * 10 + nge);
                gh.DrawImage(timeimg[0], 885, 0, 63, 93);
                gh.DrawImage(timeimg[1], 950, 0, 63, 93);
                gh.DrawImage(Image::FromFile(_T(".\\pic\\天.gif")), 1000, 0, 103, 93);//天字
            }
            else
            {
                if (!to31day)
                {
                    toZero();
                }
                else
                {
                    toBinary(poisonedwinenum);
                }
            }
            for (int i = 0; i < binaryarr10.size(); i++)
            {
                gh.DrawImage(numimgarr[i]->img[binaryarr10[i]], numimgarr[i]->place.x, numimgarr[i]->place.y + 100);
                if (binaryarr10[i] == 1 && !to1000num)
                {
                    Point p{ 551,295 };
                    LinearGradientBrush myBrush(bandmans[i]->centerpoint, p, Color(255, 0, 0), Color(255, 165, 0));
                    Pen pen(&myBrush,10);
                    gh.DrawLine(&pen, bandmans[i]->centerpoint, p);
                }
            }
        }

        static ULONGLONG endtime = ::GetTickCount64();
        //绘制31天
        if (to1000num)
        {
            if (biuend)
            {
                ge = 1;
                PlaySound(L".\\music\\biuend.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
                endtime = ::GetTickCount64();
            }
            biuend = false;

            if (!to31day && ::GetTickCount64() - endtime > jian)
            {
                ge++;
                if (ge > 9)
                {
                    shi++;
                    ge = 0;
                    if (shi == 3)
                    {
                        PlaySound(L".\\music\\backgroundmusic1.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
                        to31day = true;
                    }
                }
            }
            else if (to31day)
            {
                toZero();
                shi = 3;
                ge = 1;
                find = true;
            }
            gh.DrawImage(timeimg[shi], 885, 0, 63, 93);
            gh.DrawImage(timeimg[ge], 950, 0, 63, 93);
            gh.DrawImage(Image::FromFile(_T(".\\pic\\天.gif")), 1000, 0, 103, 93);//天字
        }

        Choose(inico1, inico2, inico3, gh);


        if (find)
        {
            int a = 225;
            gh.DrawImage(Image::FromFile(_T(".\\pic\\毒酒.gif")), 410, 10 + a);//酒桶
            gh.DrawImage(timeimg[(poisonedwinenum / 1000) % 10], 470, 0 + a, 63, 93);
            gh.DrawImage(timeimg[(poisonedwinenum / 100) % 10], 535, 0 + a, 63, 93);
            gh.DrawImage(timeimg[(poisonedwinenum / 10) % 10], 590, 0 + a, 63, 93);
            gh.DrawImage(timeimg[poisonedwinenum % 10], 655, 0 + a, 63, 93);
        }

        if (to31day)
        {
            toBinary(poisonedwinenum);

            for (int i = 0; i < bandmans.size(); i++)
            {
                gh.DrawImage(bandmans[i]->numimg, bandmans[i]->place.left + 10, bandmans[i]->place.top - 70);
                if (binaryarr10[i] == 1)
                    gh.DrawImage(bandmans[i]->dieimg, bandmans[i]->place.left, bandmans[i]->place.top, 70, 70);
                else
                    gh.DrawImage(bandmans[i]->character[bb], bandmans[i]->place.left, bandmans[i]->place.top, 70, 70);

                gh.DrawImage(numimgarr[i]->img[binaryarr10[i]], numimgarr[i]->place.x, numimgarr[i]->place.y + 100);
            }
        }
        else
        {
            for (int i = 0; i < bandmans.size(); i++)
            {
                gh.DrawImage(bandmans[i]->character[bb], bandmans[i]->place.left, bandmans[i]->place.top, 70, 70);
                gh.DrawImage(bandmans[i]->numimg, bandmans[i]->place.left + 10, bandmans[i]->place.top - 70);
            }
        }

        if (to31day)
        {
            addnum++;
            if (addnum % 3 == 1)
            {
                kingindex++;
                if (kingindex == 7)kingindex = 0;
            }

            if (kingp < 191)
                kingp += 3;
            gh.DrawImage(king[kingindex], 551 - 75, 220 - 30 - kingp, 150, 150);
        }
        else
        {
            addnum++;
            if (addnum % 3 == 1)
            {
                kingindex++;
                if (kingindex == 7)kingindex = 0;
            }
            gh.DrawImage(king[kingindex], 551 - 75, 220 - 30, 150, 150);
        }


        if (k == 6000)k = 0;

        static CPoint p1{ 0, 100 }, p2{ 980,100 };
        static CPoint t1{ 305,190 }, t2{ 705,190 };//新位置
        static int yy = 0;
        yy++;
        int t = yy;

        if (!find)
        {
            gh.DrawImage(lnkr[t], 970, 100);
            gh.DrawImage(lnkl[t], 0, 100);
        }
        else
        {
            if (0 - x < 280)
            {
                x += 4 * cos(Theta(p1, t1));
                y += 4 * sin(Theta(p1, t1));
            }
            if (980 + x > 705)
            {
                z += 4 * cos(Theta(p2, t2));
                p += 4 * sin(Theta(p2, t2));
            }
            gh.DrawImage(lnkl[t], 0 - x, 100 + y);
            gh.DrawImage(lnkr[t], 980 - z, 100 + p);

        }
        if (yy >= 5)
            yy = 0;
    }

 }

  

 //////////////////////////////////////////////////////////////////////////////////////////////

void Start::EightBandMan(bool& inico1, bool& inico2, bool& inico3, Gdiplus::Graphics& gh)
{
    static int k = 0;
    k++;
    if (k % 3 == 1)
    {
        bb = bb == 1 ? 0 : 1;
    }
    
    if (addbandman)
    {
        if (prebo)
        {
            poisonedwinenum = RandomNumber();
            PlaySound(L".\\music\\dododo.wav", NULL, SND_ASYNC | SND_FILENAME| SND_LOOP);
            prebo = false;
        }

        gh.DrawImage(Image::FromFile(L".\\pic\\8bandman.gif"), m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());
        Choose(inico1, inico2, inico3, gh);
        s.Format(L"  %d", poisonedwinenum);
        gh.DrawImage(Image::FromFile(_T(".\\pic\\dujiu.png")), 0, 0, 75, 75);
        gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);

        for (int i = 0; i <= bandaddindex; i++)
        {
            gh.DrawImage(bandman8[i]->character[bb], bandman8[i]->place.left, bandman8[i]->place.top, 70, 70);
            gh.DrawImage(bandman8[i]->numimg, bandman8[i]->place.left + 10, bandman8[i]->place.top - 70);
        }
        static int k = 2;
        k++;
        if (bandaddindex < 8 && k % 17 == 1)
        {
            bandaddindex++;
        }
        if (bandaddindex == 8)addbandman = false;
    }
    else
    {
        if (createrandom)
        {
            //poisonedwinenum = RandomNumber();
            posionedgroup = (poisonedwinenum - 1) / 250 + 1;
        }
        createrandom = false;
        static ULONGLONG newtime = ::GetTickCount64();
        if (bofang)
        {
            toZero();
            characterinit();
            newtime = ::GetTickCount64();
            PlaySound(L".\\music\\biu.wav", NULL, SND_ASYNC | SND_FILENAME);
            CTime startime = CTime::GetCurrentTime();//程序开始时间
            ofstream file0("tempstep.txt", ios::out | ios::app);
            file0 << startime.GetHour() << "时" << startime.GetMinute() << "分" << startime.GetSecond() << "秒" << "\t八个奴隶寻找毒酒\t毒酒编号：" << poisonedwinenum << endl;
            file0.close();
        }
        bofang = false;

        gh.DrawImage(Image::FromFile(L".\\pic\\8bandman.gif"), m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());

  
        s.Format(L"  %d", poisonedwinenum);
        gh.DrawImage(Image::FromFile(_T(".\\pic\\dujiu.png")), 0, 0, 75, 75);
        gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);

        //毒酒号数  一直增加

        if (day<5 && ::GetTickCount64() - newtime>jian)
        {
            if (nbai * 100 + nshi * 10 + nge == 200)
                PlaySound(L".\\music\\biuend.wav", NULL, SND_ASYNC | SND_FILENAME);
            if (nbai * 100 + nshi * 10 + nge < 250)
            {
                nge++;
                if (nge > 9)
                {
                    nge = 0;
                    if (nbai * 100 + nshi * 10 + nge >= 180)
                        nshi += 1;
                    else
                        nshi += 2;

                    if (nshi > 9)
                    {
                        nshi = 0;
                        nbai += 2;
                    }
                }
                gh.DrawImage(Image::FromFile(_T(".\\pic\\酒.png")), 450, 10,62,79);//酒桶
                gh.DrawImage(timeimg[nbai], 515, 0, 63, 93);
                gh.DrawImage(timeimg[nshi], 575, 0, 63, 93);
                gh.DrawImage(timeimg[nge], 635, 0, 63, 93);
            }
            else
            {
                to250num = true;
                PlaySound(L".\\music\\biu.wav", NULL, SND_ASYNC | SND_FILENAME);
                toZero();
            }
        }

        if (day < 5)
        {
            gh.DrawImage(timeimg[0], 885, 0, 63, 93);
            gh.DrawImage(timeimg[day], 950, 0, 63, 93);
            gh.DrawImage(Image::FromFile(_T(".\\pic\\天.gif")), 1000, 0, 103, 93);//天字

            if (!to250num)
            {
                toBinary(nbai * 100 + nshi * 10 + nge);
            }
            else
            {
                day++;
                to250num = false;
                nbai = 0;
                nshi = 0;
                nge = 0;
            }

            //绘制二进制  +  画线
            for (int i = 0; i < binaryarr8.size(); i++)
            {
                toBinary(nbai * 100 + nshi * 10 + nge);
                gh.DrawImage(numarr8[i]->img[binaryarr8[i]], numarr8[i]->place.x, numarr8[i]->place.y + 100);
                if (binaryarr8[i] == 1 && !to250num)
                {
                    Point p{ 551,295 };
                    LinearGradientBrush myBrush(bandman8[i]->centerpoint, p, Color(255, 0, 0), Color(255, 165, 0));
                    Pen pen(&myBrush, 10);
                    gh.DrawLine(&pen, bandman8[i]->centerpoint, p);
                    addnum++;
                    if (addnum % 5 == 1)
                    {
                        kingindex++;
                        if (kingindex == 7)kingindex = 0;
                    }
                    gh.DrawImage(king[kingindex], 551 - 75, 220 - 30, 150, 150);
                }
            }

        }

        static int k1 = 0, bb = 0;
        k1++;
        if (k1 % 6 == 1)
        {
            bb = bb == 1 ? 0 : 1;
        }

        if (day >= 5 && day < 31)
        {
            if (biuend)
            {
                PlaySound(L".\\music\\backgroundmusic1.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
            }
            biuend = false;
            ge++;
            if (ge > 9)
            {
                shi++;
                ge = 0;
            }
            if (shi * 10 + ge == 31)
                day = 31;
            gh.DrawImage(timeimg[shi], 885, 0, 63, 93);
            gh.DrawImage(timeimg[ge], 950, 0, 63, 93);
            gh.DrawImage(Image::FromFile(_T(".\\pic\\天.gif")), 1000, 0, 103, 93);//天字
            for (int i = 0; i < bandman8.size(); i++)
            {
                gh.DrawImage(bandman8[i]->character[bb], bandman8[i]->place.left, bandman8[i]->place.top, 70, 70);
                gh.DrawImage(bandman8[i]->numimg, bandman8[i]->place.left + 10, bandman8[i]->place.top - 70);
            }
        }

        if (day == 31)
        {
            if (first31)
            {
                temptime31 = ::GetTickCount64();
                first31 = false;
            }
            gh.DrawImage(timeimg[3], 885, 0, 63, 93);
            gh.DrawImage(timeimg[1], 950, 0, 63, 93);
            gh.DrawImage(Image::FromFile(_T(".\\pic\\天.gif")), 1000, 0, 103, 93);//天字

            if (!find)
                for (int i = 0; i < bandman8.size(); i++)
                {
                    gh.DrawImage(bandman8[i]->character[bb], bandman8[i]->place.left, bandman8[i]->place.top, 70, 70);
                    gh.DrawImage(bandman8[i]->numimg, bandman8[i]->place.left + 10, bandman8[i]->place.top - 70);
                }

            if (posionedgroup == 1 && ::GetTickCount64() - temptime31 > 3000)
            {
                find = true;
                toZero();
                toBinary(poisonedwinenum);
                drawpeop(gh);
            }
            else if (::GetTickCount64() - temptime31 > 3000)
            {
                day++;
            }
        }
        if (day == 32)
        {
            if (first32)
            {
                temptime32 = ::GetTickCount64();
                first32 = false;
            }
            gh.DrawImage(timeimg[3], 885, 0, 63, 93);
            gh.DrawImage(timeimg[2], 950, 0, 63, 93);
            gh.DrawImage(Image::FromFile(_T(".\\pic\\天.gif")), 1000, 0, 103, 93);//天字

            if (!find)
                for (int i = 0; i < bandman8.size(); i++)
                {
                    gh.DrawImage(bandman8[i]->character[bb], bandman8[i]->place.left, bandman8[i]->place.top, 70, 70);
                    gh.DrawImage(bandman8[i]->numimg, bandman8[i]->place.left + 10, bandman8[i]->place.top - 70);
                }
            if (posionedgroup == 2 && ::GetTickCount64() - temptime32 > 3000)
            {
                find = true;
                toZero();
                toBinary(poisonedwinenum - 250);
                drawpeop(gh);
            }

            else if (::GetTickCount64() - temptime32 > 3000)
            {
                day++;
            }
        }

        if (day == 33)
        {
            if (first33)
            {
                temptime33 = ::GetTickCount64();
                first33 = false;
            }
            gh.DrawImage(timeimg[3], 885, 0, 63, 93);
            gh.DrawImage(timeimg[3], 950, 0, 63, 93);
            gh.DrawImage(Image::FromFile(_T(".\\pic\\天.gif")), 1000, 0, 103, 93);//天字

            if (!find)
                for (int i = 0; i < bandman8.size(); i++)
                {
                    gh.DrawImage(bandman8[i]->character[bb], bandman8[i]->place.left, bandman8[i]->place.top, 70, 70);
                    gh.DrawImage(bandman8[i]->numimg, bandman8[i]->place.left + 10, bandman8[i]->place.top - 70);
                }
            if (posionedgroup == 3 && ::GetTickCount64() - temptime33 > 3000)
            {
                find = true;
                toZero();
                toBinary(poisonedwinenum - 500);
                drawpeop(gh);
            }

            else if (::GetTickCount64() - temptime33 > 3000)
            {
                day++;
            }
        }

        if (day == 34)
        {
            if (first34)
            {
                temptime34 = ::GetTickCount64();
                first34 = false;
            }
            gh.DrawImage(timeimg[3], 885, 0, 63, 93);
            gh.DrawImage(timeimg[4], 950, 0, 63, 93);
            gh.DrawImage(Image::FromFile(_T(".\\pic\\天.gif")), 1000, 0, 103, 93);//天字

            if (!find)
                for (int i = 0; i < bandman8.size(); i++)
                {
                    gh.DrawImage(bandman8[i]->character[bb], bandman8[i]->place.left, bandman8[i]->place.top, 70, 70);
                    gh.DrawImage(bandman8[i]->numimg, bandman8[i]->place.left + 10, bandman8[i]->place.top - 70);
                }
            if (posionedgroup == 4 && ::GetTickCount64() - temptime34 > 3000)
            {
                find = true;
                toZero();
                toBinary(poisonedwinenum - 750);
                drawpeop(gh);
            }
        }

        Choose(inico1, inico2, inico3, gh);


        if (find)
        {
            int a = 95;
            gh.DrawImage(Image::FromFile(_T(".\\pic\\毒酒.gif")), 450 + a, 215);//酒桶
            int num = poisonedwinenum - (posionedgroup - 1) * 250;
            gh.DrawImage(timeimg[(num / 100) % 10], 515 + a, 210, 63, 93);
            gh.DrawImage(timeimg[(num / 10) % 10], 575 + a, 210, 63, 93);
            gh.DrawImage(timeimg[(num) % 10], 635 + a, 210, 63, 93);
            gh.DrawImage(groupimg, 350, 225);
            gh.DrawImage(timeimg[posionedgroup], 410, 225);
        }

        if (day < 31)
        {
            for (int i = 0; i < bandman8.size(); i++)
            {
                gh.DrawImage(bandman8[i]->character[bb], bandman8[i]->place.left, bandman8[i]->place.top, 70, 70);
                gh.DrawImage(bandman8[i]->numimg, bandman8[i]->place.left + 10, bandman8[i]->place.top - 70);
            }

            addnum++;
            if (addnum % 5 == 1)
            {
                kingindex++;
                if (kingindex == 7)kingindex = 0;
            }
            gh.DrawImage(king[kingindex], 551 - 75, 220 - 30, 150, 150);
        }
        else
        {
            addnum++;
            if (addnum % 5 == 1)
            {
                kingindex++;
                if (kingindex == 7)kingindex = 0;
            }
            if (kingp < 191)
                kingp += 4 / posionedgroup;
            gh.DrawImage(king[kingindex], 551 - 75, 220 - 30 - kingp, 150, 150);
        }
        if (k1 > 7000000)k1 = 1;
        static CPoint p1{ 0, 100 }, p2{ 980,100 };
        static CPoint t1{ 255,190 }, t2{ 705,215 };//新位置
        static int yy = 0;
        yy++;
        int t = yy;
        if (!find)
        {
            gh.DrawImage(lnkr[t], 970, 100);
            gh.DrawImage(lnkl[t], 0, 100);
        }
        else
        {
            if (0 - x < 205)
            {
                x += 4 * cos(Theta(p1, t1));
                y += 4 * sin(Theta(p1, t1));
            }
            if (980 - z > 795)
            {
                z += 4 * cos(Theta(p2, t2));
                p += 4 * sin(Theta(p2, t2));
            }
            gh.DrawImage(lnkl[t], 0 - x, 100 + y);
            gh.DrawImage(lnkr[t], 980 - z, 100 + p);

        }
        if (yy == 5)
            yy = 0;
    }
} 
