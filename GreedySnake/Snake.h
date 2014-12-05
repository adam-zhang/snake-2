#pragma once
#include"Wall.h"
#include"LinkList.cpp"
class Snake
{
public:
	Snake(void);
	~Snake(void);
	void Move(char direction,bool isGrop);//wsad�ֱ������������,isGrop��ʾ�����Ƿ�ɳ���
	void Paint(MyPoint point);//pointΪ��ͷλ��,Ĭ�ϴ�����ֱ����׼�������ߣ����û�ʹ��
	void SetColor(unsigned short color);
	bool isHitBody() ;			//�ж���ͷ�Ƿ�ײ������
	bool isHitPoint(MyPoint point);//�ж���ͷ�Ƿ���õ���ײ;
private:
	void Paint();                  //���ƶ���Ĵ��߻��ƣ����ڲ�ʹ��  
	LinkList<MyPoint> snakePos;     //��������������Ļ�ϵ�λ��
};

