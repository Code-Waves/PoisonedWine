#pragma once
#include "AboutFunction.h"
#include "MediaVoice.h"
#include "FrontNextMusic.h"
#include "OtherFuction.h"
#include "BandMan.h"
#include "StoryorPro.h"
#include "Story.h"
#include "Binary.h"
#include "Step.h"
#include "Start.h"
#include "resource.h"
static DWORDLONG physical_memory;//�����ڴ�:
static  float percent_memory;//�ڴ�ʹ����: 
static double cpu_memory;//cpuʹ����
class CGame
{
public:
    /* ���캯��:
     * hWnd : ��Ϸ���ڴ���
     * x,y: λ��
     * w,h: ���ڿ��
     */
    CGame(HWND hWnd, float x, float y, float w, float h);
    ~CGame();



public:
    bool EnterFrame(DWORD dwTime);  // ��Ϸ��һ֡
    //HCURSOR mouseStyle = LoadCursor(NULL, IDC_ARROW);
    HCURSOR mouseStyle = mouseStyle = (HCURSOR)LoadImage(NULL, L".\\pic\\mouse0.cur", IMAGE_CURSOR, 68, 76, LR_LOADFROMFILE);
    AFX_GLOBAL_DATA hand;
    /// ////////////////////////////////////////////////////////////////////////
    /// ���������Ϣ
    // ����������
    void OnLButtonDown(UINT nFlags, CPoint point);
    // ������̧��
    void OnLButtonUp(UINT nFlags, CPoint point);
    void OnLButtonDblClk(UINT nFlags, CPoint point);
    // ����ƶ�
    void OnMouseMove(UINT nFlags, CPoint point);

    void DrawCPU(Gdiplus::Graphics& gh);

    void DrawRGB(Gdiplus::Graphics& gh);

    void DrawTime(Gdiplus::Graphics& gh);

    CPoint rectCenter(CRect rc);//��þ������ĵ�
    bool inRect(CRect rc, CPoint mouse);//�жϽ���ĳ����������

private:
    HWND m_hWnd;
    // ���ڵ���ʼλ��
    float m_x;
    float m_y;
    // ��Ϸ���ڵĿ��
    float m_width;
    float m_height;
    int fps = 0;
    bool backhome = false;
    COLORREF pointcolor;
    // ����ĸ����׶�
    enum GameStatus 
    {
        aboutico=0,//����ͼ�꣬����bool���飬�洢����Ƿ���������
        voiceico,
        nextmusicico,
        frontmusicico,
        otherico,
        storyico,//����
        programico,//suanfa
        homeico,//�������ܵ�z
        binaryaddstepico,//����������
        binaryico,//������
        stepico,//������ʾ
        stepaddstepico,//������ʾ����
        startico,//��ʼ
        startaddstepico,
        cleanico,

        menu,//������׶�
        aboutstep,
        invoice,
        infrontmusic,
        innextmusic,
        inother, 
        instory, 
        inprogram,
        inbinary,//������
        instep,
        instart,
        inclean
    };

    int GameState = menu;//��ʼ����Ϸ�׶�
    std::shared_ptr< AboutFunction> about;//������
    std::shared_ptr< MediaVoice> mediavoice;//ý������
    std::shared_ptr<FrontNextMusic> changemusic;//�ı�����
    std::shared_ptr<OtherFuction> otherfunction;//�ı�����
    std::shared_ptr<StoryorPro>storyorpro;//���¡���ʾ
    std::shared_ptr<Story>story;
    std::shared_ptr<Binary>binary;
    std::shared_ptr<Step>step;
    std::shared_ptr<Start>start;

    std::vector<BandMan*>bandmans;//ū����
    bool *inico;//bool�����¼����ͼ���Ƿ���������
    CRect m_rcClient;// �ͻ����Ĵ�С
    bool clickLeftButton=false;//�ж���������������̻���ը
    CPoint mousepoint;//���λ��
    CPoint startscreenshotpoint,endscreenpoint;//��ͼ�������Ͻǵ�
    bool screening =false;//û�д����������
    CRect screenshotrect;//��������

    int bomimgindex = 0;//�������ը���������
    bool home = false;//������˵�
   

    CPoint bompoin;//�̻���ը���ĵ�
    int m_fps{ 0 };    // ��¼ ��Ϸÿ�����֡
    SolidBrush m_brush{ Color::Red};// ���FPS�����õĻ�ˢ
    Gdiplus::Font m_font{ L"����", 15.0,CFE_BOLD };    // �����������
    PointF origin{ 200.0f,0.0f };    // ������ʾλ��ʹ��
    std::vector<Image*> bom;
    std::vector<Image*> backgroundimg;

    Gdiplus::Image* miao = Image::FromFile(_T(".\\pic\\miao.png"));
    Gdiplus::Image* fen = Image::FromFile(_T(".\\pic\\fen.png"));
    Gdiplus::Image* shi = Image::FromFile(_T(".\\pic\\shi.png"));
    Gdiplus::Image* clock = Image::FromFile(_T(".\\pic\\clock.png"));

    Gdiplus::Image* count = Image::FromFile(_T(".\\pic\\count.png"));
    Gdiplus::Image* point = Image::FromFile(_T(".\\pic\\point.png"));

    Gdiplus::Image* fpso = Image::FromFile(_T(".\\pic\\fpso.png"));
    Gdiplus::Image* fpsi = Image::FromFile(_T(".\\pic\\fpsi.png"));

    Gdiplus::Image* erjinzhiimg = Image::FromFile(_T(".\\pic\\����ת��.gif"));
    Gdiplus::Image* yanshiimg = Image::FromFile(_T(".\\pic\\������ʾ.gif"));
    Gdiplus::Image* startimg = Image::FromFile(_T(".\\pic\\Ѱ�Ҷ���.gif"));
    Gdiplus::Image* backhomeimg = Image::FromFile(_T(".\\pic\\backhome0.gif"));

    Gdiplus::Image* img = Image::FromFile(_T(".\\pic\\background0.bmp"));

    void Draw();// �������ж���
    static UINT cpu(LPVOID p);
    void DrawBackground(Gdiplus::Graphics& gh);
    void ScreenShot(Gdiplus::Graphics& gh);//��ͼ����
    //����ͼƬ  
    void InPro(Gdiplus::Graphics& gh);//��ʾ  ��������ѡ��  ������  ��ʾ  Ѱ��
    void DrawFps(Gdiplus::Graphics& gh);// ���fps
    void DrawMouse(Gdiplus::Graphics& gh);//�������λ��
    void MouseBomb(Gdiplus::Graphics& gh);//����̻���ը
};


