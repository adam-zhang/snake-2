#pragma once
#include "Wall.h"
class Food
{
public:
	enum FoodKind //ʳ������
	{
		a='a',b,c,d,e
	};
	Food(void);
	explicit Food(FoodKind foodKind);
	~Food(void);
	int ScoreNum();   //��ʳ��ķ���
	void Paint(MyPoint point);//��ʳ�������point��
	void SetColor(unsigned short color);
	static  int foodKindNum;
	void SetFoodKind(FoodKind foodKind);
private:
	FoodKind foodKind;
};
