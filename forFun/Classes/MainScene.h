#pragma once

#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__
#pragma execution_character_set("utf-8")
#include "cocos2d.h"
#include "Card\CardSprite.h"

class MainScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainScene);

	MainScene();
	virtual ~MainScene();

	//手势识别事件
	virtual bool ontouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void ontouchEnd(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	//上下左右
	bool doUp();
	bool doDown();
	bool doLeft();
	bool doRight();

	//判断游戏是否结束
	void checkGameOver();

private:
	//定义点击的xy坐标
	int firstX, firstY, endX, endY;
	
	//添加卡片
	void addCard(cocos2d::Size visiableSize);
	void autoAddCard();

	//卡片二维数组存储数字
	CardSprite* cardArr[4][4];

	//是否滑动成功
	bool isdo = false;

	//总分数
	int score;
	cocos2d::Label* scoreLabel;

};

#endif //  __MAINSCENE_H__