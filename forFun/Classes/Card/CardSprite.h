#pragma once

#ifndef __CARDSPRITE_H__
#define __CARDSPRITE_H__
#pragma execution_character_set("utf-8")
#include "cocos2d.h"

class CardSprite :public cocos2d::Sprite    
{
public:
	//初始化数字卡片
	static CardSprite* creatCardSprite(int number,int width,int height,float cardx,int cardy);
	virtual bool init();
	CREATE_FUNC(CardSprite);
    
	//设置数字
	void setNumber(int num);
	//获取数字
	int getNumber();

private:
	int number;
	void enemyinit(int numbers, int width, int height, float cardx, int cardy);

	//定义显示数字的控件
	cocos2d::Label* labCardNumber;
	//定义数字控件的背景
	cocos2d::LayerColor* layerColorBG;
};

#endif