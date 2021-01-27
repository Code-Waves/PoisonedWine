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
//��һ����һ��ͼ��仯
void FrontNextMusic::Draw(bool& infrontico, bool& innextico, int& gamestate, Gdiplus::Graphics& gh)
{

    CRect shangyiqurect{ m_rcClient.Width() - 280,m_rcClient.Height() - 70,(int)(frontimg->GetWidth()),(int)(frontimg->GetHeight()) };//aboutλ��
    CPoint shangyiqucen = rectCenter(shangyiqurect);

    CRect xiayiqurect{ m_rcClient.Width() - 210,m_rcClient.Height() - 70,(int)(nextimg->GetWidth()),(int)(nextimg->GetHeight()) };//aboutλ��
    CPoint xiayiqucen = rectCenter(xiayiqurect);

    if (inRect(shangyiqurect, mousepoint))//��������һ��
    {
        infrontico = true;
        gh.DrawImage(frontimg, (shangyiqucen.x - frontimg->GetWidth() / 2 - 6), (shangyiqucen.y - frontimg->GetHeight() / 2 - 6), 70, 70);
    }
    else//���δ����
    {
        infrontico = false;
        gh.DrawImage(frontimg, shangyiqucen.x - frontimg->GetWidth() / 2, shangyiqucen.y - frontimg->GetHeight() / 2, shangyiqurect.right, shangyiqurect.bottom);
    }

    if (inRect(xiayiqurect, mousepoint))//������
    {
        innextico = true;
        gh.DrawImage(nextimg, (xiayiqucen.x - nextimg->GetWidth() / 2 - 6), (xiayiqucen.y - nextimg->GetHeight() / 2 - 6), 70, 70);
    }
    else//���δ����
    {
        innextico = false;
        gh.DrawImage(nextimg, xiayiqucen.x - nextimg->GetWidth() / 2, xiayiqucen.y - nextimg->GetHeight() / 2, xiayiqurect.right, xiayiqurect.bottom);
    }
}

//�ڽ��������ס�����
void FrontNextMusic::MusicimgDance(Gdiplus::Graphics& gh,bool &mediavoice,bool &playmusic)
{
    //�ڽ���Ƭλ��   
    CRect musicrect{0,m_rcClient.Height() - (int)(LongPlayingimg[LongPlayingimgindex]->GetHeight()),(int)(LongPlayingimg[LongPlayingimgindex]->GetWidth()),(int)(LongPlayingimg[LongPlayingimgindex]->GetHeight())};
    CPoint musiccen = rectCenter(musicrect);
    if (mediavoice)
    {
        //����
        if (!playmusic)//����û����  
        {
            PlaySound(MusicPath[LongPlayingimgindex], NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
            playmusic = true;
        }

        RotateLongPlaying(gh, musicrect,mediavoice);////�ڽ���Ƭ ת��
        RotateStylus(gh, musicrect,mediavoice,playmusic);//����ת��
    }
    else//ý�������ر� 
    {
        //PlaySound(NULL, NULL, SND_FILENAME);
        RotateLongPlaying(gh, musicrect, mediavoice);//�ڽ���Ƭת��  ���������ж� �ǲ���ת��
        //�����
        RotateStylus(gh, musicrect,mediavoice,playmusic);
    }
}

//�ڽ���Ƭת��
void FrontNextMusic::RotateLongPlaying(Gdiplus::Graphics& gh, CRect musicrect,bool& mediavoice)
{
    //�ڽ���Ƭ ת��  
    CPoint musiccen = rectCenter(musicrect);
    gh.TranslateTransform((REAL)musiccen.x, (REAL)musiccen.y);
    gh.RotateTransform(float(longplayingAngel));
    gh.DrawImage(LongPlayingimg[LongPlayingimgindex], -musicrect.right / 2, -musicrect.right / 2, musicrect.right, musicrect.bottom);
    gh.ResetTransform();//��ԭ

    if (mediavoice)//ý��������ʱ��ִ�нǶ�++  ý��ر�ʱ���ֽǶȲ��� ��ת��
    {
        if (!clickchangemusic)longplayingAngel += 3;//���û���л����� �Ƕ�++ 
        if (longplayingAngel == 360)longplayingAngel = 0;
    }
}


//����ת��
void FrontNextMusic::RotateStylus(Gdiplus::Graphics& gh, CRect musicrect, bool& mediavoice, bool& playmusic, REAL x, REAL y)
{
    CPoint musiccen = rectCenter(musicrect);
    Bitmap hjimg(L".\\pic\\stylus.gif");//����
    bool mediaVoice =mediavoice;
    if (mediaVoice)
    {
        //����  û���л�����ʱ��  ˳ʱ��ת��
        if (!clickchangemusic)
        {
            if (stylusAngel < setangel)
                stylusAngel += 2;
            gh.TranslateTransform(x, y);
            gh.RotateTransform(float(stylusAngel));
            gh.DrawImage(&hjimg, -30, -40, hjimg.GetWidth(),hjimg.GetHeight());//ǰ�������������� ͼ�����Ͻ�  //2�Ž�Ƭ��
            gh.ResetTransform();//��ԭ
        }
         

        //�л����֣�����ָ�->����
        if (clickchangemusic)
        {
            if (runonce == false)
            {
                //û�����е�ԭ��  ������ʾԭͼ
                gh.TranslateTransform((REAL)musiccen.x, (REAL)musiccen.y);
                gh.RotateTransform(float(longplayingAngel));
                gh.DrawImage(LongPlayingimg[frontimgindex], -musicrect.right / 2, -musicrect.right / 2, musicrect.right, musicrect.bottom);
                gh.ResetTransform();//��ԭ

                clickChangeMusicAngel -= 3;
                gh.TranslateTransform(x, y);
                gh.RotateTransform(float(clickChangeMusicAngel));
                gh.DrawImage(&hjimg, -30, -40, hjimg.GetWidth(), hjimg.GetHeight());//ǰ�������������� ͼ�����Ͻ�  //2�Ž�Ƭ��
                gh.ResetTransform();//��ԭ
                if (clickChangeMusicAngel < 0)runonce = true;
            }
            else
            {
                //���е���ԭ��  ����
                clickChangeMusicAngel += 4;
                gh.TranslateTransform(x, y);
                gh.RotateTransform(float(clickChangeMusicAngel));
                gh.DrawImage(&hjimg, -30, -40, hjimg.GetWidth(), hjimg.GetHeight());//ǰ�������������� ͼ�����Ͻ�  //2�Ž�Ƭ��
                gh.ResetTransform();//��ԭ
                if (clickChangeMusicAngel > setangel)
                {
                    clickchangemusic = false;
                    runonce = false;
                }
            }
        }
        //����
        if (playmusic && !clickchangemusic)
        {
            NodeDance(gh);//��������
        }
    }
    else//û�����ֳ����
    {
        if (!clickchangemusic)
        {
            if (stylusAngel > 0)
                stylusAngel--;
            gh.TranslateTransform(x, y);
            gh.RotateTransform(float(stylusAngel));
           // gh.DrawImage(&hjimg, -50, -33, 100, 200);//ǰ�������������� ͼ�����Ͻ�  //1�Ž�Ƭ��
            gh.DrawImage(&hjimg ,- 30, -40,hjimg.GetWidth(),hjimg.GetHeight());//ǰ�������������� ͼ�����Ͻ�   //2�Ž�Ƭ��
            gh.ResetTransform();//��ԭ
            if (playmusic)
            {
                PlaySound(NULL, NULL, SND_FILENAME); // �ر�����
                playmusic = false;
            }
        }

    }
}
//��������
void FrontNextMusic::NodeDance(Gdiplus::Graphics& gh)
{
    CRect yfrect{ 300,m_rcClient.Height() - 70,(int)(nodeimg[1]->GetWidth()),(int)(nodeimg[1]->GetHeight()) };
    if ((longplayingAngel < 60) || (longplayingAngel > 120 && longplayingAngel < 180) || (longplayingAngel > 240 && longplayingAngel < 300))
        gh.DrawImage(nodeimg[0], 140, 480, yfrect.right, yfrect.bottom);
    else
        gh.DrawImage(nodeimg[1], 140, 480, yfrect.right, yfrect.bottom);
}

  
  