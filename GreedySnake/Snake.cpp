#include "Snake.h"
#include"GotoXY.h"
#include<iostream>
using namespace std;
Snake::Snake(void)
{

}
Snake::~Snake(void)
{
}
void Snake::Move(char direction,bool isGroup)
{
	//����û�гɳ���ɾ����β
	if(!isGroup)
	{
		//������β
		int length=this->snakePos.Length();
		GotoXY()(this->snakePos.Get(length));
		cout<<" ";
		this->snakePos.Delete(length);
	}
	//��ͷ
	MyPoint tempPoint=this->snakePos.Get(1);
	switch(direction)
	{
	case 'w':
		tempPoint.y-=1;
		break;
	case 's':
		tempPoint.y+=1;
		break;
	case 'a':
		tempPoint.x-=1;
		break;
	case 'd':
		tempPoint.x+=1;
		break;
	}
	this->snakePos.Insert(1,tempPoint);
	//�����ƶ��������
	this->Paint();
}
void Snake::Paint(MyPoint point)
{
	int const length=5;//Ĭ�ϴ��ߵĳ���Ϊ5
	//������ͷ
	GotoXY()(point);
	cout<<char('O');
	this->snakePos.Insert(1,point);
	//����
	for(int i=1;i<length;++i)
	{
		++point.y;
		GotoXY()(point);
		cout<<char('*');
		this->snakePos.Insert(i+1,point);
	}
}
void Snake::SetColor(unsigned short color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
bool Snake::isHitBody()
{
	//�����ܺ������ǰ��������ײ��
	for(int i=5;i<=this->snakePos.Length();++i)
	{
		if(this->snakePos.Get(1)==this->snakePos.Get(i))
		{
			return true;
		}
	}
	return false;
}
bool Snake::isHitPoint(MyPoint point) 
{
	if(this->snakePos.Get(1)==point)
		return true;
	return false;
}
void Snake::Paint()
{
	GotoXY()(this->snakePos.Get(1));
	cout<<char('O');
	for(int i=2;i<=this->snakePos.Length();++i)
	{
		GotoXY()(this->snakePos.Get(i));
		cout<<char('*');
	}
}
