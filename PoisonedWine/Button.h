#pragma once
class Button
{
public:
	Button();
	~Button();
	CPoint mousepoint;
	CPoint rectCenter(CRect rc);//获得矩形中心点
	bool inRect(CRect rc, CPoint mouse);//判断进入某个矩形区域
	void OnMouseMove(CPoint point);

    enum GameStatus
    {
        aboutico = 0,//功能图标，用于bool数组，存储鼠标是否在其区域
        voiceico,
        nextmusicico,
        frontmusicico,
        otherico,
        storyico,//故事
        programico,//suanfa
        homeico,//背景介绍的
        binaryaddstepico,//二进制跳过
        binaryico,//二进制
        stepico,//步骤演示
        stepaddstepico,//步骤演示跳过
        startico,//开始
        startaddstepico,
        cleanico,

        menu,//主界面阶段
        invoice,
        infrontmusic,
        innextmusic,
        inother,
        instory,
        inprogram,
        inbinary,//二进制
        instep,
        instart
    };
};

