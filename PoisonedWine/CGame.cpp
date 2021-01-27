#pragma once
#include "pch.h"
#include "CGame.h"
#include"PoisonedWineDlg.h"
#include "resource.h"
#define KEYDOWN(vk) (GetAsyncKeyState(vk)& 0x8000)
CGame::CGame(HWND hWnd, float x, float y, float w, float h)
    : m_hWnd(hWnd)
    , m_x(x)
    , m_y(y)
    , m_width(w)
    , m_height(h)
{
    about = std::make_shared<AboutFunction>(hWnd);
    mediavoice = std::make_shared<MediaVoice>(hWnd);
    changemusic = std::make_shared<FrontNextMusic>(hWnd);
    otherfunction= std::make_shared<OtherFuction>(hWnd);
    storyorpro = std::make_shared<StoryorPro>(hWnd);
    story =std::make_shared<Story>(hWnd);
    binary = std::make_shared<Binary>(hWnd);
    step = std::make_shared<Step>(hWnd);
    start = std::make_shared<Start>(hWnd);

    AfxBeginThread(cpu, NULL);//////线程

   inico = new bool[15];
    CString img0,img1;
    for (int i = 0; i < 16; i++)
    {
        img0.Format(_T(".\\pic\\bom%d(已去底).gif"), i);//鼠标爆炸各阶段图
        //bom[i] = Image::FromFile(s);
        bom.push_back(Image::FromFile(img0));
        if (i < 15)
        {
            inico[i] = false;//初始图标进入
            img0.Format(_T(".\\pic\\background%d.gif"), i);//背景图片
            backgroundimg.push_back(Image::FromFile(img0));
        }
        if (i < 10)//初始化10个奴隶
        {
            img0.Format(_T(".\\pic\\bandman%d0.gif"), i);
            img1.Format(_T(".\\pic\\bandman%d1.gif"), i);
            CString s;
            s.Format(_T(".\\pic\\num%d.gif"), i + 1);
            bandmans.push_back(new BandMan(img0,img1, s, 35 + i * (35 + 70), 430, 70, 70));
        }
    }
    GetClientRect(m_hWnd, &m_rcClient);   
    CString s;
    s.Format(L"%d", m_rcClient.Width());
    //AfxMessageBox(s);
}

CGame::~CGame()
{
    
}

// 游戏的一帧
bool CGame::EnterFrame(DWORD dwTime)
{
    static int m_fps = 0;
    m_fps++;
    static ULONGLONG stime = ::GetTickCount64();
    if (::GetTickCount64() - stime > 1000)
    {
        fps = m_fps;
        m_fps = 0;
        stime = ::GetTickCount64();
    }
    Draw();
    return false;
}

void CGame::Draw()
{
    HDC hdc = ::GetDC(m_hWnd); 				// 这个是窗口DC
    CDC* dc = CClientDC::FromHandle(hdc); 		// 此指针是一个临时指针，不用释放
    // 双缓冲绘图用
    CDC m_dcMemory; 							// 内存DC
    CBitmap bmp; 								// 创建兼容位图对象，并选入 内存DC
    bmp.CreateCompatibleBitmap(dc, m_rcClient.Width(), m_rcClient.Height());
    m_dcMemory.CreateCompatibleDC(dc);
    CBitmap* pOldBitmap = m_dcMemory.SelectObject(&bmp);		// 选入DC
    Graphics gh(m_dcMemory.GetSafeHdc());						// 构造对象
 
    gh.SetPageUnit(Gdiplus::UnitPixel); 						// 设置单位
    gh.Clear(BACK_GROUND_LAYER);
    gh.ResetClip();

    //不同阶段不同操作
    switch (GameState)
    {
        case menu:
            DrawBackground(gh);
            if (otherfunction->functionon)
            {
                DrawCPU(gh);
                DrawFps(gh);
                DrawTime(gh);
            }
            break;

        case aboutstep:
            DrawBackground(gh);
            about->Drawbackground(gh);
            break;

        case instory:
            story->Draw(inico[homeico], bandmans,gh);
            break;
        case inprogram://进入  显示三个
            InPro(gh);
            break;
        case inbinary://二进制讲解开始
            binary->Draw(inico[binaryaddstepico],inico[homeico],GameState,bandmans,gh);
            break;
        case instep://演示步骤
            step->Draw(inico[stepaddstepico], inico[homeico], GameState, gh);
            break;
        case instart://开始
            start->Draw(inico[startaddstepico], inico[homeico], inico[cleanico],GameState,gh);
            break;
        default:
            DrawBackground(gh);
            break;
    }

    MouseBomb(gh);//鼠标点击爆炸
    ScreenShot(gh);//截图
    ::BitBlt(hdc, 0, 0, m_rcClient.Width(), m_rcClient.Height(),// 拷贝到屏幕
        m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);

    ::ReleaseDC(m_hWnd, hdc);
    return;
}

__int64 CompareFileTime(FILETIME time1, FILETIME time2)		//filetime到const filetime的转换函数
{
    __int64 a = time1.dwHighDateTime << 32 | time1.dwLowDateTime; 
    __int64 b = time2.dwHighDateTime << 32 | time2.dwLowDateTime;

    return   (b - a); 
}
UINT CGame::cpu(LPVOID p)
{
    while (true)
    {
        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx(&statex);

        physical_memory = statex.ullTotalPhys / (1024 * 1024);
        DWORDLONG usePhys = physical_memory - (statex.ullAvailPhys / (1024 * 1024));

        percent_memory = (float)usePhys / (float)physical_memory;
        if (percent_memory * 100 > MAXpercent_memory)MAXpercent_memory = percent_memory * 100;
        if (percent_memory * 100 < Minpercent_memory)Minpercent_memory = percent_memory * 100;
        double idle, kernel, user;
        FILETIME idleTime1, idleTime2;
        FILETIME kernelTime1, kernelTime2;
        FILETIME userTime1, userTime2;
        GetSystemTimes(&idleTime1, &kernelTime1, &userTime1);
        Sleep(100);
        GetSystemTimes(&idleTime2, &kernelTime2, &userTime2);
        idle = (double)CompareFileTime(idleTime1, idleTime2);
        kernel = (double)CompareFileTime(kernelTime1, kernelTime2);
        user = (double)CompareFileTime(userTime1, userTime2);
        if (kernel + user == 0)
        {
            cpu_memory = 0.0;
        }
        else
        {
            cpu_memory = (double)((kernel + user - idle) * 100 / (kernel + user));	//（总的时间-空闲时间）/总的时间=占用cpu的时间就是使用率		
        }
       
        if (cpu_memory<=100)
        {
            if (cpu_memory > MAXcpu_memory)MAXcpu_memory = cpu_memory;
            if (cpu_memory < Mincpu_memory)Mincpu_memory = cpu_memory;
        }
    }
}


//截图
void CGame::ScreenShot(Gdiplus::Graphics& gh)
{
    if (KEYDOWN(' '))
    {
        if (KEYDOWN(VK_LBUTTON))
        {
            if (!screening)
            {
                startscreenshotpoint = mousepoint;
                screening = true;
            }
            endscreenpoint = mousepoint;
            Rect rect;
            if (startscreenshotpoint.y < endscreenpoint.y && startscreenshotpoint.x < endscreenpoint.x)//左上
            {
                rect = { startscreenshotpoint.x, startscreenshotpoint.y, endscreenpoint.x - startscreenshotpoint.x, endscreenpoint.y - startscreenshotpoint.y };
            }
            else if(startscreenshotpoint.y>endscreenpoint.y&&startscreenshotpoint.x < endscreenpoint.x)//左下
            {
                rect = { startscreenshotpoint.x, startscreenshotpoint.y-(startscreenshotpoint.y-endscreenpoint.y), endscreenpoint.x - startscreenshotpoint.x,  startscreenshotpoint.y - endscreenpoint.y };
            }
            else if (startscreenshotpoint.y < endscreenpoint.y && startscreenshotpoint.x > endscreenpoint.x)//右上
            {
                rect = { startscreenshotpoint.x- (startscreenshotpoint.x-endscreenpoint.x), startscreenshotpoint.y, startscreenshotpoint.x-endscreenpoint.x,   endscreenpoint.y-startscreenshotpoint.y };
            }
            else //右下
            {
                rect = { startscreenshotpoint.x - (startscreenshotpoint.x - endscreenpoint.x), endscreenpoint.y, startscreenshotpoint.x - endscreenpoint.x,  startscreenshotpoint.y- endscreenpoint.y };
            }
            Pen Pen(Color::Red, 3);
            gh.DrawRectangle(&Pen, rect);
            static ULONGLONG last = GetTickCount();
            if (KEYDOWN(VK_LMENU))//左alt
            {
                if (GetTickCount64() - last > 500)
                {
                    last = GetTickCount64();
                    HDC hDC = ::GetDC(m_hWnd);
                    HDC hdcMem = ::CreateCompatibleDC(hDC);
                    HBITMAP hBitmap = ::CreateCompatibleBitmap(hDC, rect.Width-4, rect.Height-4);
                    HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hdcMem, hBitmap);
                    ::BitBlt(hdcMem, rect.X+2, rect.Y+2, rect.Width-2, rect.Height-2, hDC, 2, 2, SRCCOPY);
                    CImage img;

                    CDC* dc = CClientDC::FromHandle(hDC);
                    CDC memDC;
                    memDC.CreateCompatibleDC(dc);
                    CBitmap bm;//创建位图对象
                    CSize sz(rect.Width, rect.Height);
                    bm.CreateCompatibleBitmap(dc, sz.cx, sz.cy);//创建选择区域大小位图位图。
                    CBitmap* oldbm = memDC.SelectObject(&bm);
                    memDC.BitBlt(0, 0, sz.cx, sz.cy, dc, rect.X, rect.Y, SRCCOPY);//像素进行位块（bit_block）转换，以传送到目标设备环境。
                    OpenClipboard(m_hWnd);
                    ::EmptyClipboard();
                    ::SetClipboardData(CF_BITMAP, bm.m_hObject);
                    CloseClipboard();

                    {
                        HDC hDC = ::GetDC(m_hWnd);
                        RECT saverect;
                        ::GetClientRect(m_hWnd, &saverect);
                        HDC hdcMem = ::CreateCompatibleDC(hDC);
                        HBITMAP hBitmap = ::CreateCompatibleBitmap(hDC, rect.Width-4, rect.Height-4);
                        HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hdcMem, hBitmap);
                        ::BitBlt(hdcMem, saverect.left, saverect.top, saverect.right, saverect.bottom, hDC, rect.X+2, rect.Y+2, SRCCOPY);
                        CImage img;
                        CTime nowtime = CTime::GetCurrentTime();
                        int year = nowtime.GetYear(), month = nowtime.GetMonth(), day = nowtime.GetDay(),
                            hour = nowtime.GetHour(), minute = nowtime.GetMinute(), second = nowtime.GetSecond();
                        CString imgpath;// "L".\\screenimg\\"+ time;
                        imgpath.Format(L".\\screenimg\\%d-%d-%d %d：%d：%d.png", year, month, day, hour, minute, second);
                        img.Attach(hBitmap);//关联windows的资源句柄和c++对象
                        img.Save(imgpath);
                        img.Detach();
                        ::SelectObject(hdcMem, hOldBitmap);
                        ::DeleteObject(hBitmap);
                        ::DeleteDC(hdcMem);
                        ::DeleteDC(hDC);
                    }
                }
            }
        }

    }
}

//演示  出现三个选项  二进制  演示  寻找
void CGame::InPro(Gdiplus::Graphics& gh)
{
    //返回会主菜单
    CRect erjinzhirect{ 200,(int)(m_rcClient.Height() / 2 - erjinzhiimg->GetHeight() / 2), (int)(erjinzhiimg->GetWidth()), (int)(erjinzhiimg->GetHeight()) };
    CRect yanshirect{ 495,(int)(m_rcClient.Height() / 2 - erjinzhiimg->GetHeight() / 2), (int)(erjinzhiimg->GetWidth()), (int)(erjinzhiimg->GetHeight()) };
    CRect startrect{ (int)(m_rcClient.right - 200 - startimg->GetWidth()),  (int)(m_rcClient.Height() / 2 - startimg->GetHeight() / 2) , (int)(startimg->GetWidth()), (int)startimg->GetHeight() };
    CPoint  erjinzhicen = rectCenter(erjinzhirect);
    CPoint yanshicen = rectCenter(yanshirect);
    CPoint startcen = rectCenter(startrect);

    Gdiplus::Image* backgroundimg = Image::FromFile(_T(".\\pic\\background2.gif"));
    gh.DrawImage(backgroundimg, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());//背景

    if (inRect(erjinzhirect, mousepoint))///将进入二进制
    {
        inico[stepico] = false;
        inico[startico] = false;
        inico [binaryico]= true;
        gh.DrawImage(erjinzhiimg, (erjinzhicen.x - erjinzhiimg->GetWidth() / 2 - 20), (erjinzhicen.y - erjinzhiimg->GetHeight() / 2 - 105), 170, 390);
        gh.DrawImage(yanshiimg,495, m_rcClient.Height() / 2 - yanshiimg->GetHeight() / 2 - 60);
        gh.DrawImage(startimg, (int)(m_rcClient.right - 200 - startimg->GetWidth()), (int)(m_rcClient.Height() / 2 - startimg->GetHeight() / 2) - 60);
    }
    else if (inRect(yanshirect, mousepoint))//演示
    {
        inico[stepico] = true;
        inico[startico] = false;
        inico[binaryico] = false;
        gh.DrawImage(erjinzhiimg, 200, m_rcClient.Height() / 2 - erjinzhiimg->GetHeight() / 2 - 60);
        gh.DrawImage(yanshiimg, (yanshicen.x - yanshiimg->GetWidth() / 2 - 20), (yanshicen.y - yanshiimg->GetHeight() / 2 - 105), 170, 390);
        gh.DrawImage(startimg, (int)(m_rcClient.right - 200 - startimg->GetWidth()), (int)(m_rcClient.Height() / 2 - startimg->GetHeight() / 2) - 60);
    }
    else if (inRect(startrect, mousepoint))//进入 找毒
    {
        inico[startico] = true;
        inico[stepico] = false;
        inico[binaryico] = false;
        gh.DrawImage(erjinzhiimg, 200, m_rcClient.Height() / 2 - erjinzhiimg->GetHeight() / 2 - 60);
        gh.DrawImage(yanshiimg, 495, m_rcClient.Height() / 2 - yanshiimg->GetHeight() / 2 - 60);
        gh.DrawImage(startimg, (startcen.x - startimg->GetWidth() / 2 - 20), (startcen.y - startimg->GetHeight() / 2 - 105), 170, 390);
    }
    else
    {
        inico[stepico] = false;
        inico[startico] = false;
        inico[binaryico] = false;
        gh.DrawImage(erjinzhiimg, 200, m_rcClient.Height() / 2 - erjinzhiimg->GetHeight() / 2 - 60);
        gh.DrawImage(yanshiimg, 495, m_rcClient.Height() / 2 - yanshiimg->GetHeight() / 2 - 60);
        gh.DrawImage(startimg, (int)(m_rcClient.right - 200 - startimg->GetWidth()), (int)(m_rcClient.Height() / 2 - startimg->GetHeight() / 2) - 60);
    }

    //返回界面
    CRect backhomerect{ m_rcClient.Width() - 270,m_rcClient.Height() - 90,(int)(backhomeimg->GetWidth()),(int)(backhomeimg->GetHeight()) };
    CPoint backhomecen = rectCenter(backhomerect);
    if (inRect(backhomerect, mousepoint))//鼠标进入
    {
       inico[homeico] = true;
       backhome = true;
        gh.DrawImage(backhomeimg, (backhomecen.x - backhomeimg->GetWidth() / 2 - 10), (backhomecen.y - backhomeimg->GetHeight() / 2 - 4), 220, 88);
    }
    else//鼠标未进入
    {
        inico[homeico] = false;
        gh.DrawImage(backhomeimg, backhomecen.x - backhomeimg->GetWidth() / 2, backhomecen.y - backhomeimg->GetHeight() / 2, backhomerect.right, backhomerect.bottom);
    }
}


void CGame::DrawBackground(Gdiplus::Graphics& gh)
{
   gh.DrawImage(backgroundimg[0],0,0, m_rcClient.Width(),m_rcClient.Height());//主背景图

   if(GameState== aboutstep)
   gh.DrawImage(Image::FromFile(_T(".\\pic\\background00.png")), 0, 0, m_rcClient.Width(), m_rcClient.Height());//主背景图
   else
   {
       changemusic->MusicimgDance(gh, mediavoice->mediavoice, mediavoice->playmusic);//黑胶、五线谱跳动
       about->Draw(inico[aboutico], GameState, gh);//about图标
       mediavoice->Draw(inico[voiceico], GameState, gh);//媒体声音
       changemusic->Draw(inico[frontmusicico], inico[nextmusicico], GameState, gh);//上下一曲
       otherfunction->Start(inico[otherico], GameState, gh);//开启其他功能 火箭起飞
       storyorpro->Draw(inico[storyico], inico[programico], GameState, gh);
   }
}

// 画 fps
void CGame::DrawFps(Gdiplus::Graphics& gh)
{
    gh.DrawImage(fpso, m_rcClient.right-100,0,100,100);
    int edg = 0;
    edg = fps*9+50;
    CRect Client{ m_rcClient.right - 56,15,12,37};
    CPoint musiccen = rectCenter(Client);
    gh.TranslateTransform((REAL)musiccen.x - 2, (REAL)musiccen.y + 19);
    gh.RotateTransform(edg);
    gh.DrawImage(fpsi, -Client.right / 2, -Client.right / 2,12, 37);
    gh.ResetTransform();//还原

}

// 鼠标移动
void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
    mousepoint = point;
    about->OnMouseMove(point);
    mediavoice->OnMouseMove(point);
    changemusic->OnMouseMove(point);
    otherfunction->OnMouseMove(point);
    storyorpro->OnMouseMove(point);
    story->OnMouseMove(point);
    binary->OnMouseMove(point);
    step->OnMouseMove(point);
    start->OnMouseMove(point);
}
void CGame::DrawCPU(Gdiplus::Graphics& gh)
{
    gh.DrawImage(count,m_rcClient.right/2-count->GetWidth()/2-50,0);
   
    int edg = 90+ cpu_memory;
    
    CRect Client{(int)(m_rcClient.right / 2 - point->GetWidth() / 2 ),50,(int)point->GetWidth(),(int)point->GetHeight() };
    CPoint musiccen = rectCenter(Client);
    gh.TranslateTransform((REAL)musiccen.x-7,(REAL)musiccen.y+30);
    gh.RotateTransform(edg); 
    gh.DrawImage(point, -Client.right / 2, -Client.right / 2);
    gh.ResetTransform();//还原

}
void CGame::DrawRGB(Gdiplus::Graphics& gh)
{
    HDC hdc = ::GetDC(m_hWnd);
    pointcolor = ::GetPixel(hdc, mousepoint.x, mousepoint.x);
    CString s;
    s.Format(_T("RGB：%03d：%03d：%03d"), GetRValue(pointcolor), GetGValue(pointcolor), GetBValue(pointcolor));
    PointF p = PointF((REAL)mousepoint.x, (REAL)mousepoint.y);
    Gdiplus::Font m_font{ L"楷体", 10.0,CFE_BOLD };
    gh.DrawString(s.GetString(), -1, &m_font, p, &m_brush);
}
void CGame::DrawTime(Gdiplus::Graphics& gh)
{
    CTime nowtime = CTime::GetCurrentTime();
    int   hour = nowtime.GetHour(), minute = nowtime.GetMinute(), second = nowtime.GetSecond();

    gh.DrawImage(clock, 912,320,190,190); 

    gh.TranslateTransform(1007,414);
    gh.RotateTransform(hour*30+180);
    gh.DrawImage(shi,-4,-4);
    gh.ResetTransform();//还原

    gh.TranslateTransform(1007, 414);
    gh.RotateTransform(second * 6 + 180);  
    gh.DrawImage(miao, -4, -18); 
    gh.ResetTransform();//还原

    gh.TranslateTransform(1007, 414);
    gh.RotateTransform(minute * 6 + 180);
    gh.DrawImage(fen, -2,-18);
    gh.ResetTransform();//还原
   
}

//绘制鼠标位置
void CGame::DrawMouse(Gdiplus::Graphics& gh)
{
    CString s;
    s.Format(_T("%04d:%04d"), mousepoint.x, mousepoint.y);
    PointF origin;
    origin.X = (REAL)m_rcClient.Width() - 130;
    origin.Y = 10;
    gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);
}

// 鼠标左键按下
void CGame::OnLButtonDown(UINT nFlags, CPoint point)
{
    mouseStyle = (HCURSOR)LoadImage(NULL, L".\\pic\\mouse.cur", IMAGE_CURSOR, 68, 76, LR_LOADFROMFILE);

    bomimgindex = 0;
    bompoin = mousepoint;
    clickLeftButton = true; 
     if (inico[aboutico])
    {
        GameState = aboutstep;
    }
     else if (inico[voiceico])//点击媒体按钮
     {
         mediavoice->mediavoice = !mediavoice->mediavoice;
     }
     else if (inico[nextmusicico]&& mediavoice->mediavoice)
     {
         if (changemusic->LongPlayingimgindex < 3)
             changemusic->LongPlayingimgindex++;
         else
             changemusic->LongPlayingimgindex = 0;

         changemusic->clickchangemusic = true;
         PlaySound(changemusic->MusicPath[changemusic->LongPlayingimgindex], NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
         changemusic->frontimgindex = changemusic->LongPlayingimgindex-1;
         if (changemusic->frontimgindex < 0)  changemusic->frontimgindex = 3;
     }
     else if (inico[frontmusicico] && mediavoice->mediavoice)
     {
         if (changemusic->LongPlayingimgindex>0)
             changemusic->LongPlayingimgindex--;
         else
             changemusic->LongPlayingimgindex =3;
         changemusic->clickchangemusic = true;
         PlaySound(changemusic->MusicPath[changemusic->LongPlayingimgindex], NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
            
         changemusic->frontimgindex = changemusic->LongPlayingimgindex+1;
         if (changemusic->frontimgindex>3)  changemusic->frontimgindex = 0;
     }
     else if (inico[otherico])
     {
             PlaySound(otherfunction->rackmusicpath, NULL, SND_ASYNC | SND_FILENAME);
             otherfunction->fire = true;
             otherfunction->functionon = !otherfunction->functionon;

             mediavoice->mediavoice = false;
             mediavoice->playmusic =false;   
     }
     else if (inico[storyico])
     {
         GameState = instory;
         inico[storyico] = false;
     }
     else if (inico[programico])
     {
         GameState = inprogram;
         inico[programico] = false;
     }
     else if (inico[binaryico])//二进制
     {
         GameState = inbinary;
         PlaySound(L".\\music\\二进制起源.wav", NULL, SND_ASYNC | SND_FILENAME);
     }
     else if (inico[stepico])//步骤
     {
         GameState =instep;
         PlaySound(L".\\music\\第一步编号.wav", NULL, SND_ASYNC | SND_FILENAME);

     }
     else if (inico[startico])//开始
     {
         GameState = instart;
         PlaySound(L".\\music\\backgroundmusic1.wav", NULL, SND_ASYNC | SND_FILENAME);

     }
     if (inico[homeico])
     {
         if (backhome||story->backhome)
         {
             GameState = menu;
             backhome = false;
             story->backhome = false;
         }
         else
         {
             GameState = inprogram;
         }
         story->wordindex = 0;
         story->music = true;
         binary->step = 1;
         binary->init();
         step->step = 1;
         step->init();
         start->step = 1;
         start->init();
         PlaySound(NULL, NULL, SND_FILENAME); // 关闭音乐
         if (mediavoice->mediavoice)
             PlaySound(changemusic->MusicPath[changemusic->LongPlayingimgindex], NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
     }
     if (inico[binaryaddstepico])
     {
         binary->step++;
         binary->init();
     }

     if (inico[stepaddstepico])
     {
         step->step++;
         step->init();
     }
     if (inico[startaddstepico])
     {
         start->step++;
         start->init();
         start->characterinit();
     }
     if (inico[cleanico])
     {
         start->init();
     }
     ///////////////////////////////////////////////状态重置
     for (int i = 0; i < 15; i++)
     {
         inico[i] = false;
     }
     
}
//左键抬起
void CGame::OnLButtonUp(UINT nFlags, CPoint point)
{
    mouseStyle = (HCURSOR)LoadImage(NULL, L".\\pic\\mouse0.cur", IMAGE_CURSOR, 68, 76, LR_LOADFROMFILE);
    screening = false;
}
void CGame::OnLButtonDblClk(UINT nFlags, CPoint point)//左键双击
{
    if (GameState == aboutstep)
        GameState = menu;
}
//判断是否进入矩形
bool CGame::inRect(CRect rc, CPoint mouse)
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
//鼠标点击爆炸
void CGame::MouseBomb(Gdiplus::Graphics& gh)
{
    if (clickLeftButton == true)
    {
        gh.DrawImage(bom[bomimgindex], bompoin.x - 100, bompoin.y - 100, 200, 200);
        bomimgindex++;
        if (bomimgindex == bom.size())
        {
            bomimgindex = 0;
            clickLeftButton = false;
        }
    }
}
////返回矩形中心点
CPoint CGame::rectCenter(CRect rc)
{
    CPoint p{ rc.left + rc.right / 2,rc.top + rc.bottom / 2 };
    return p;
}


