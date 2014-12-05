#pragma once
#include "Wall.h"
#include"Food.h"
#include"Obstacle.h"
#include"Snake.h"
#include"GotoXY.h"
#include <stdlib.h>
class Game
{
public:
	Game(void);
	~Game(void);
	void Start();
	void End();
public:
	void OutTip();//�����ʾ�����
private:	
	enum {foodnum=10,obstaclenum=10};//ʳ����Ŀ.�ϰ�����Ŀ
	Wall wall;
	Snake snake;
	Food food[foodnum];
	MyPoint foodPos[foodnum];
	Obstacle obstacle[obstaclenum];
	MyPoint obstaclePos[obstaclenum];
	MyPoint currentScorePos;//��ʾ��ǰ������λ��
	MyPoint maxScorePos;   //��ʾ��߷ֵ�λ��
	int currentScore;
	int maxScore;
	char currentDirection;//���ߵĵ�ǰ���߷���
	MyPoint wallPoint;//ǽ�����Ͻǵ�λ��
	COORD bufferSize; //���ô��ڴ�С
private:
	void OperationAfterMove();//����ÿ��һ��Ӧ�����Ĳ���
	bool IsHitWall();//�жϴ����Ƿ�ײǽ
	int IsHitObstacle();//�жϴ����Ƿ�ײ�ϰ���,-1��ʾûײ���������ʾײ���˵ڼ����ϰ���
	int IsHitFood();//�жϴ����Ƿ�Ե�ʳ��,����-1��ʾû�Ե��������ʾ�Ե��˵ڼ���ʳ��
	void Init();
	bool IsContrary(char direction);//���direction����ߵĵ�ǰ�н������Ƿ��෴
};
