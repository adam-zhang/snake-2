#include "Game.h"
#include<iostream>
#include<cmath>
#include<ctime>
#include <conio.h>
using namespace std;
Game::Game(void)
{
	this->OutTip();
	this->Init();
}
Game::~Game(void)
{
}
void Game::Start()
{
	GotoXY()(this->currentScorePos);
	cout<<this->currentScore;
	GotoXY()(this->maxScorePos);
	cout<<this->maxScore;
	while(true)
	{	
		if(kbhit())
		{
			char ch=getch();
			if(('w'==ch||'s'==ch||'a'==ch||'d'==ch)&&!this->IsContrary(ch))
			{
				snake.Move(ch,false);
				this->OperationAfterMove();
				currentDirection=ch;
			}
		}
		else
		{
			if(this->currentScore<1)
				Sleep(1000);
			else	
				Sleep(1000/sqrt((float)this->currentScore));//�÷�Խ���ٶ�Խ��
			snake.Move(currentDirection,false);
			this->OperationAfterMove();
		}
	}
}
void Game::OutTip()
{
		//���ô��ڴ�С
	HANDLE hOut ;
	CONSOLE_SCREEN_BUFFER_INFO csbi ;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
	GetConsoleScreenBufferInfo(hOut, &csbi) ;
	this->bufferSize.X=80;
	this->bufferSize.Y=25;																
	::SetConsoleScreenBufferSize(hOut, this->bufferSize);
	wall.SetColor(9);
	GotoXY()(MyPoint(0,10));
	cout<<"---------------------------------��ӭ��̰������Ϸ-------------------------------"<<endl<<endl;
	cout<<"-----------------------------------��Ϸ˵������---------------------------------"<<endl<<endl;
	cout<<"-------------w:��-------------s:��--------------a:��-------------d:��-----------"<<endl<<endl;
	cout<<"---------ÿ���10��,���߳ɳ�һ��----------------����Խ��,�����ܵ�Խ��-----------"<<endl<<endl;
	cout<<"---------abcdeΪʳ��,��Ӧ12345��-------------����Ϊ�ϰ������һ�μ�2��--------"<<endl<<endl;
	cout<<"-----------------��ʼ:s-------------------------------�˳�:q--------------------"<<endl<<endl;
	while(true)
	{
		if(kbhit())
		{
			char ch=getch();
			if('s'==ch)
			{
				return;
			}
			else if('q'==ch)
			{
				exit(0);
			}
		}
	}
}
bool Game::IsContrary(char direction)
{
	if(abs(this->currentDirection-direction)=='w'-'s'||abs(this->currentDirection-direction)=='d'-'a')
		return true;
	return false;

}
void Game::Init()
{
	//��Ļ���Ϸ���ʾ��ǰ�÷�����ߵ÷�
	system("cls");
	GotoXY()(MyPoint(0,0));
	cout<<"��ǰ�÷�:";
	this->currentScorePos.x=9;
	this->currentScorePos.y=0;
	GotoXY()(MyPoint(69,0));
	cout<<"��ߵ÷�:";
	this->maxScorePos.x=77;
	this->maxScorePos.y=0;
	this->wallPoint.x=0;
	this->wallPoint.y=1;
	//����ǽ
	wall.SetXlength(79);
	wall.SetYlength(20);
	wall.SetColor(10);
	wall.Paint(this->wallPoint);
	//����
	snake=Snake();
	snake.SetColor(rand()%15+1);
	snake.Paint(MyPoint(bufferSize.X/2+this->wallPoint.x,bufferSize.Y/2+this->wallPoint.y));
	//ʳ��
	srand((unsigned)time(NULL));
	for(int i=0;i<this->foodnum;++i)
	{
		this->food[i].SetFoodKind(Food::FoodKind(rand()%Food::foodKindNum+Food::a));
		foodPos[i].x=this->wallPoint.x+rand()%(wall.GetXlength()-2)+1;
		foodPos[i].y=this->wallPoint.y+rand()%(wall.GetYlength()-2)+1;
		food[i].SetColor(rand()%15+1);
		food[i].Paint(foodPos[i]);
	}
	//�ϰ���
	for(i=0;i<this->obstaclenum;++i)
	{
		obstaclePos[i].x=this->wallPoint.x+rand()%(wall.GetXlength()-2)+1;
		obstaclePos[i].y=this->wallPoint.y+rand()%(wall.GetYlength()-2)+1;
		obstacle[i].SetColor(10);
		obstacle[i].Paint(obstaclePos[i]);
	}
	//Ĭ�ϵĴ��ߵĵ�ǰ�н�����
	this->currentDirection='w';
	this->currentScore=0;
	this->maxScore=0;
}
bool Game::IsHitWall()
{
	MyPoint tempPoint=this->wallPoint;
	//����Ƿ�ײ���ϱߺ��±�
	for(int i=0;i<wall.GetXlength();++i)
	{	
		if(snake.isHitPoint(tempPoint))
			return true;
		tempPoint.y+=wall.GetYlength()-1;
		if(snake.isHitPoint(tempPoint))
			return true;
		++tempPoint.x;
		tempPoint.y-=wall.GetYlength()-1;	
	}
	//����Ƿ�ײ����ߺ��ұ�
	tempPoint=this->wallPoint;
	for(i=0;i<wall.GetYlength()-1;++i)
	{
		++tempPoint.y;
		if(snake.isHitPoint(tempPoint))
			return true;
		tempPoint.x+=wall.GetXlength()-1;
		if(snake.isHitPoint(tempPoint))
			return true;
		tempPoint.x-=wall.GetXlength()-1;
	}
	return false;
}
int Game::IsHitObstacle()
{
	for(int i=0;i<this->obstaclenum;++i)
	{
		if(snake.isHitPoint(this->obstaclePos[i]))
			return i;
	}
	return -1;
}
int Game::IsHitFood()
{
	for(int i=0;i<this->foodnum;++i)
	{
		if(snake.isHitPoint(this->foodPos[i]))
		{
			return i;
		}
	}
	return -1;
}
void Game::OperationAfterMove()
{
	int index=this->IsHitFood();
	if(-1!=index)
	{
		this->currentScore+=this->food[index].ScoreNum();
		GotoXY()(this->currentScorePos);
		cout<<this->currentScore;
		cout<<"   ";
		//ÿ������10�ı������Ժ󣬴��߾ͳɳ�һ��
		if(this->currentScore/10>(this->currentScore-food[index].ScoreNum())/10)
		{
			snake.Move(this->currentDirection,true);
		}
		this->food[index].SetFoodKind(Food::FoodKind(rand()%Food::foodKindNum+Food::a));
		this->foodPos[index].x=this->wallPoint.x+rand()%(wall.GetXlength()-2)+1;
		this->foodPos[index].y=this->wallPoint.y+rand()%(wall.GetYlength()-2)+1;
		this->food[index].SetColor(rand()%15+1);
		this->food[index].Paint(foodPos[index]);
		return;
	}
	index=this->IsHitObstacle();
	if(-1!=index)
	{
		this->currentScore-=2;
		GotoXY()(this->currentScorePos);
		cout<<this->currentScore;
		this->obstaclePos[index].x=this->wallPoint.x+rand()%(wall.GetXlength()-2)+1;
		this->obstaclePos[index].y=this->wallPoint.y+rand()%(wall.GetYlength()-2)+1;
		this->obstacle[index].SetColor(rand()%15+1);
		this->obstacle[index].Paint(obstaclePos[index]);
		return;
	}
	if(snake.isHitBody()||this->IsHitWall())
	{
		this->End();
	}
}
void Game::End()
{
	system("cls");
	wall.SetColor(rand()%15+1);
	GotoXY()(MyPoint(0,this->bufferSize.Y/2));
	cout<<"------------------------------------��Ϸ����------------------------------------"<<endl<<endl;
	cout<<"-------------------------------��ĵ÷ּ�¼��"<<this->currentScore<<"----------------------------------"<<endl<<endl;
	if(this->currentScore>this->maxScore)
	{	
		this->maxScore=this->currentScore;
		cout<<"-----------------------------��ϲ��,���˵÷ּ�¼--------------------------------"<<endl<<endl;
	}
	cout<<"----------y:����-------------------------------------------�������������-------"<<endl<<endl;
	while(true)
	{
		if(kbhit())
		{
			if('y'==getch())
			{
				system("cls");
				int temp=this->maxScore;
				this->Init();
				this->maxScore=temp;
				this->Start();
			}
			else
			{
				exit(0);
			}
		}
	}
}