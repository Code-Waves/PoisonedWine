#pragma once
class Button
{
public:
	Button();
	~Button();
	CPoint mousepoint;
	CPoint rectCenter(CRect rc);//��þ������ĵ�
	bool inRect(CRect rc, CPoint mouse);//�жϽ���ĳ����������
	void OnMouseMove(CPoint point);

    enum GameStatus
    {
        aboutico = 0,//����ͼ�꣬����bool���飬�洢����Ƿ���������
        voiceico,
        nextmusicico,
        frontmusicico,
        otherico,
        storyico,//����
        programico,//suanfa
        homeico,//�������ܵ�
        binaryaddstepico,//����������
        binaryico,//������
        stepico,//������ʾ
        stepaddstepico,//������ʾ����
        startico,//��ʼ
        startaddstepico,
        cleanico,

        menu,//������׶�
        invoice,
        infrontmusic,
        innextmusic,
        inother,
        instory,
        inprogram,
        inbinary,//������
        instep,
        instart
    };
};

