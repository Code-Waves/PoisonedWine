#pragma once
#include "pch.h"
#include "FrontNextMusic.h"
FrontNextMusic::FrontNextMusic(HWND hWnd)
    : m_hWnd(hWnd)
{
    GetClientRect(m_hWnd, &m_rcClient);
    CString s;

    nodeimg.push_back(Image::FromFile(_T(".\\pic\\yf1.gif")));
    nodeimg.push_back(Image::FromFile(_T(".\\pic\\yf2.gif")));

    for (int i = 0; i < 4; i++)
    {
        s.Format(_T(".\\pic\\LongPlayingimg%d.gif"), i);
        LongPlayingimg.push_back(Image::FromFile(s));
        s.Format(_T(".\\music\\backgroundmusic%d.wav"), i);
        MusicPath.push_back(s); 
    } 
    PlaySound(MusicPath[LongPlayingimgindex], NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);///////////////////////////////////////////////////////////
}   
FrontNextMusic::~FrontNextMusic()
{
}
//上一曲下一曲图标变化
void FrontNextMusic::Draw(bool& infrontico, bool& innextico, int& gamestate, Gdiplus::Graphics& gh)
{

    CRect shangyiqurect{ m_rcClient.Width() - 280,m_rcClient.Height() - 70,(int)(frontimg->GetWidth()),(int)(frontimg->GetHeight()) };//about位置
    CPoint shangyiqucen = rectCenter(shangyiqurect);

    CRect xiayiqurect{ m_rcClient.Width() - 210,m_rcClient.Height() - 70,(int)(nextimg->GetWidth()),(int)(nextimg->GetHeight()) };//about位置
    CPoint xiayiqucen = rectCenter(xiayiqurect);

    if (inRect(shangyiqurect, mousepoint))//鼠标进入上一曲
    {
        infrontico = true;
        gh.DrawImage(frontimg, (shangyiqucen.x - frontimg->GetWidth() / 2 - 6), (shangyiqucen.y - frontimg->GetHeight() / 2 - 6), 70, 70);
    }
    else//鼠标未进入
    {
        infrontico = false;
        gh.DrawImage(frontimg, shangyiqucen.x - frontimg->GetWidth() / 2, shangyiqucen.y - frontimg->GetHeight() / 2, shangyiqurect.right, shangyiqurect.bottom);
    }

    if (inRect(xiayiqurect, mousepoint))//鼠标进入
    {
        innextico = true;
        gh.DrawImage(nextimg, (xiayiqucen.x - nextimg->GetWidth() / 2 - 6), (xiayiqucen.y - nextimg->GetHeight() / 2 - 6), 70, 70);
    }
    else//鼠标未进入
    {
        innextico = false;
        gh.DrawImage(nextimg, xiayiqucen.x - nextimg->GetWidth() / 2, xiayiqucen.y - nextimg->GetHeight() / 2, xiayiqurect.right, xiayiqurect.bottom);
    }
}

//黑胶、五线谱、唱针
void FrontNextMusic::MusicimgDance(Gdiplus::Graphics& gh,bool &mediavoice,bool &playmusic)
{
    //黑胶唱片位置   
    CRect musicrect{0,m_rcClient.Height() - (int)(LongPlayingimg[LongPlayingimgindex]->GetHeight()),(int)(LongPlayingimg[LongPlayingimgindex]->GetWidth()),(int)(LongPlayingimg[LongPlayingimgindex]->GetHeight())};
    CPoint musiccen = rectCenter(musicrect);
    if (mediavoice)
    {
        //音乐
        if (!playmusic)//音乐没播放  
        {
            PlaySound(MusicPath[LongPlayingimgindex], NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
            playmusic = true;
        }

        RotateLongPlaying(gh, musicrect,mediavoice);////黑胶唱片 转动
        RotateStylus(gh, musicrect,mediavoice,playmusic);//唱针转动
    }
    else//媒体声音关闭 
    {
        //PlaySound(NULL, NULL, SND_FILENAME);
        RotateLongPlaying(gh, musicrect, mediavoice);//黑胶唱片转动  函数内有判断 是不会转的
        //唱针减
        RotateStylus(gh, musicrect,mediavoice,playmusic);
    }
}

//黑胶唱片转动
void FrontNextMusic::RotateLongPlaying(Gdiplus::Graphics& gh, CRect musicrect,bool& mediavoice)
{
    //黑胶唱片 转动  
    CPoint musiccen = rectCenter(musicrect);
    gh.TranslateTransform((REAL)musiccen.x, (REAL)musiccen.y);
    gh.RotateTransform(float(longplayingAngel));
    gh.DrawImage(LongPlayingimg[LongPlayingimgindex], -musicrect.right / 2, -musicrect.right / 2, musicrect.right, musicrect.bottom);
    gh.ResetTransform();//还原

    if (mediavoice)//媒体音量打开时才执行角度++  媒体关闭时保持角度不变 不转动
    {
        if (!clickchangemusic)longplayingAngel += 3;//如果没有切换音乐 角度++ 
        if (longplayingAngel == 360)longplayingAngel = 0;
    }
}


//唱针转动
void FrontNextMusic::RotateStylus(Gdiplus::Graphics& gh, CRect musicrect, bool& mediavoice, bool& playmusic, REAL x, REAL y)
{
    CPoint musiccen = rectCenter(musicrect);
    Bitmap hjimg(L".\\pic\\stylus.gif");//唱针
    bool mediaVoice =mediavoice;
    if (mediaVoice)
    {
        //唱针  没有切换音乐时的  顺时针转动
        if (!clickchangemusic)
        {
            if (stylusAngel < setangel)
                stylusAngel += 2;
            gh.TranslateTransform(x, y);
            gh.RotateTransform(float(stylusAngel));
            gh.DrawImage(&hjimg, -30, -40, hjimg.GetWidth(),hjimg.GetHeight());//前两个点是新坐标 图形左上角  //2号胶片棒
            gh.ResetTransform();//还原
        }
         

        //切换音乐，唱针恢复->启动
        if (clickchangemusic)
        {
            if (runonce == false)
            {
                //没有运行到原点  还是显示原图
                gh.TranslateTransform((REAL)musiccen.x, (REAL)musiccen.y);
                gh.RotateTransform(float(longplayingAngel));
                gh.DrawImage(LongPlayingimg[frontimgindex], -musicrect.right / 2, -musicrect.right / 2, musicrect.right, musicrect.bottom);
                gh.ResetTransform();//还原

                clickChangeMusicAngel -= 3;
                gh.TranslateTransform(x, y);
                gh.RotateTransform(float(clickChangeMusicAngel));
                gh.DrawImage(&hjimg, -30, -40, hjimg.GetWidth(), hjimg.GetHeight());//前两个点是新坐标 图形左上角  //2号胶片棒
                gh.ResetTransform();//还原
                if (clickChangeMusicAngel < 0)runonce = true;
            }
            else
            {
                //运行到了原点  换碟
                clickChangeMusicAngel += 4;
                gh.TranslateTransform(x, y);
                gh.RotateTransform(float(clickChangeMusicAngel));
                gh.DrawImage(&hjimg, -30, -40, hjimg.GetWidth(), hjimg.GetHeight());//前两个点是新坐标 图形左上角  //2号胶片棒
                gh.ResetTransform();//还原
                if (clickChangeMusicAngel > setangel)
                {
                    clickchangemusic = false;
                    runonce = false;
                }
            }
        }
        //音符
        if (playmusic && !clickchangemusic)
        {
            NodeDance(gh);//音符跳动
        }
    }
    else//没有音乐唱针减
    {
        if (!clickchangemusic)
        {
            if (stylusAngel > 0)
                stylusAngel--;
            gh.TranslateTransform(x, y);
            gh.RotateTransform(float(stylusAngel));
           // gh.DrawImage(&hjimg, -50, -33, 100, 200);//前两个点是新坐标 图形左上角  //1号胶片棒
            gh.DrawImage(&hjimg ,- 30, -40,hjimg.GetWidth(),hjimg.GetHeight());//前两个点是新坐标 图形左上角   //2号胶片棒
            gh.ResetTransform();//还原
            if (playmusic)
            {
                PlaySound(NULL, NULL, SND_FILENAME); // 关闭音乐
                playmusic = false;
            }
        }

    }
}
//音符跳动
void FrontNextMusic::NodeDance(Gdiplus::Graphics& gh)
{
    CRect yfrect{ 300,m_rcClient.Height() - 70,(int)(nodeimg[1]->GetWidth()),(int)(nodeimg[1]->GetHeight()) };
    if ((longplayingAngel < 60) || (longplayingAngel > 120 && longplayingAngel < 180) || (longplayingAngel > 240 && longplayingAngel < 300))
        gh.DrawImage(nodeimg[0], 140, 480, yfrect.right, yfrect.bottom);
    else
        gh.DrawImage(nodeimg[1], 140, 480, yfrect.right, yfrect.bottom);
}

  
  