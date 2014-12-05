#pragma once
struct MyPoint
{
	int x,
		y;
	MyPoint(){}
	MyPoint(int x,int y)
	{
		this->x=x;
		this->y=y;
	}
	bool operator==(MyPoint point)
	{
		return (this->x==point.x)&&(this->y==point.y);
	}
	MyPoint&operator=(const MyPoint&point)
	{
		this->x=point.x;
		this->y=point.y;
		return *this;
	}
};
class Wall
{
public:
	Wall(void);
	Wall(int xlength,int ylength);
	~Wall(void);
	void Paint(MyPoint point);//ǽ�Ļ���,pointΪǽ�����ϽǶ�����dos�����µ�λ��
	void SetColor(unsigned short color);// ���ô�����ɫ
	void SetXlength(int xlength);
	void SetYlength(int ylength);
	int GetXlength();
	int GetYlength();
private:
	int xlength,//ǽ��ˮƽ�ʹ�ֱ����ĳ���
		ylength;
};

