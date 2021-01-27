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
static DWORDLONG physical_memory;//物理内存:
static  float percent_memory;//内存使用率: 
static double cpu_memory;//cpu使用率
class CGame
{
public:
    /* 构造函数:
     * hWnd : 游戏窗口窗口
     * x,y: 位置
     * w,h: 窗口宽高
     */
    CGame(HWND hWnd, float x, float y, float w, float h);
    ~CGame();



public:
    bool EnterFrame(DWORD dwTime);  // 游戏的一帧
    //HCURSOR mouseStyle = LoadCursor(NULL, IDC_ARROW);
    HCURSOR mouseStyle = mouseStyle = (HCURSOR)LoadImage(NULL, L".\\pic\\mouse0.cur", IMAGE_CURSOR, 68, 76, LR_LOADFROMFILE);
    AFX_GLOBAL_DATA hand;
    /// ////////////////////////////////////////////////////////////////////////
    /// 处理鼠标消息
    // 鼠标左键按下
    void OnLButtonDown(UINT nFlags, CPoint point);
    // 鼠标左键抬起
    void OnLButtonUp(UINT nFlags, CPoint point);
    void OnLButtonDblClk(UINT nFlags, CPoint point);
    // 鼠标移动
    void OnMouseMove(UINT nFlags, CPoint point);

    void DrawCPU(Gdiplus::Graphics& gh);

    void DrawRGB(Gdiplus::Graphics& gh);

    void DrawTime(Gdiplus::Graphics& gh);

    CPoint rectCenter(CRect rc);//获得矩形中心点
    bool inRect(CRect rc, CPoint mouse);//判断进入某个矩形区域

private:
    HWND m_hWnd;
    // 窗口的起始位置
    float m_x;
    float m_y;
    // 游戏窗口的宽高
    float m_width;
    float m_height;
    int fps = 0;
    bool backhome = false;
    COLORREF pointcolor;
    // 程序的各个阶段
    enum GameStatus 
    {
        aboutico=0,//功能图标，用于bool数组，存储鼠标是否在其区域
        voiceico,
        nextmusicico,
        frontmusicico,
        otherico,
        storyico,//故事
        programico,//suanfa
        homeico,//背景介绍的z
        binaryaddstepico,//二进制跳过
        binaryico,//二进制
        stepico,//步骤演示
        stepaddstepico,//步骤演示跳过
        startico,//开始
        startaddstepico,
        cleanico,

        menu,//主界面阶段
        aboutstep,
        invoice,
        infrontmusic,
        innextmusic,
        inother, 
        instory, 
        inprogram,
        inbinary,//二进制
        instep,
        instart,
        inclean
    };

    int GameState = menu;//初始化游戏阶段
    std::shared_ptr< AboutFunction> about;//关于类
    std::shared_ptr< MediaVoice> mediavoice;//媒体音量
    std::shared_ptr<FrontNextMusic> changemusic;//改变音乐
    std::shared_ptr<OtherFuction> otherfunction;//改变音乐
    std::shared_ptr<StoryorPro>storyorpro;//故事、演示
    std::shared_ptr<Story>story;
    std::shared_ptr<Binary>binary;
    std::shared_ptr<Step>step;
    std::shared_ptr<Start>start;

    std::vector<BandMan*>bandmans;//奴隶们
    bool *inico;//bool数组记录各个图标是否有鼠标进入
    CRect m_rcClient;// 客户区的大小
    bool clickLeftButton=false;//判断鼠标左键点击用于烟花爆炸
    CPoint mousepoint;//鼠标位置
    CPoint startscreenshotpoint,endscreenpoint;//截图矩形左上角点
    bool screening =false;//没有触发按键组合
    CRect screenshotrect;//截屏区域

    int bomimgindex = 0;//鼠标点击爆炸数组的索引
    bool home = false;//点击主菜单
   

    CPoint bompoin;//烟花爆炸中心点
    int m_fps{ 0 };    // 记录 游戏每秒多少帧
    SolidBrush m_brush{ Color::Red};// 输出FPS文字用的画刷
    Gdiplus::Font m_font{ L"楷体", 15.0,CFE_BOLD };    // 输出文字字体
    PointF origin{ 200.0f,0.0f };    // 文字显示位置使用
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

    Gdiplus::Image* erjinzhiimg = Image::FromFile(_T(".\\pic\\进制转换.gif"));
    Gdiplus::Image* yanshiimg = Image::FromFile(_T(".\\pic\\步骤演示.gif"));
    Gdiplus::Image* startimg = Image::FromFile(_T(".\\pic\\寻找毒酒.gif"));
    Gdiplus::Image* backhomeimg = Image::FromFile(_T(".\\pic\\backhome0.gif"));

    Gdiplus::Image* img = Image::FromFile(_T(".\\pic\\background0.bmp"));

    void Draw();// 画出所有对象
    static UINT cpu(LPVOID p);
    void DrawBackground(Gdiplus::Graphics& gh);
    void ScreenShot(Gdiplus::Graphics& gh);//截图功能
    //背景图片  
    void InPro(Gdiplus::Graphics& gh);//演示  出现三个选项  二进制  演示  寻找
    void DrawFps(Gdiplus::Graphics& gh);// 输出fps
    void DrawMouse(Gdiplus::Graphics& gh);//绘制鼠标位置
    void MouseBomb(Gdiplus::Graphics& gh);//鼠标烟花爆炸
};


