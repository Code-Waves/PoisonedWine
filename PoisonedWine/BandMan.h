#pragma once
	class BandMan
	{
	public:
		BandMan(CString character0, CString character1, CString num,int x,int y,int w,int h);
		~BandMan();
		bool die = false;
		CRect place;
		Point  centerpoint;
		Image* dieimg = Image::FromFile(_T(".\\pic\\die.gif"));//死人
		Image* numimg;
		std::vector<Image*>character;//两个步伐
		
	private:
	};


