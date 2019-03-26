#pragma once

#ifndef __USEROPERATION_H__
#define __USEROPERATION_H__

#include "cocos2d.h"

class UserOperation :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(UserOperation);

	UserOperation();
	virtual ~UserOperation();

	//手势识别事件
	virtual bool ontouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void ontouchEnd(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	//上下左右
	bool doUp();
	bool doDown();
	bool doLeft();
	bool doRight();
private:
	int firstX, firstY, endX, endY; //定义点击的xy坐标
};

#endif //  __USEROPERATION_H__