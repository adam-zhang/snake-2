#pragma once
#include"Wall.h"
class Obstacle
{
public:
	Obstacle(void);
	~Obstacle(void);
	void Paint(MyPoint point);//���ϰ��������point��
	void SetColor(unsigned short color);       
};

