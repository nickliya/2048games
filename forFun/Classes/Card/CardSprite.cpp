#include "Card\CardSprite.h"

USING_NS_CC;

void CardSprite::enemyinit(int numbers, int width, int height, float cardx, int cardy) {
	number = numbers;

	//设置卡片的背景
	layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(200, 190, 180, 255), width-10, height-10);//背景和原sprite之间有10间距的大小
	layerColorBG->setPosition(Point(cardx, cardy));

	//把数字添加到卡片上,如果大于0则显示
	if (number>0)
	{
		
		labCardNumber = cocos2d::Label::createWithSystemFont(StringUtils::toString(number), "HirakakuProN-W6", 100);
		labCardNumber->setPosition(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2);
		layerColorBG->addChild(labCardNumber);
	}
	else
	{
		labCardNumber = cocos2d::Label::createWithSystemFont("", "HirakakuProN-W6", 100);
		labCardNumber->setPosition(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2);
		layerColorBG->addChild(labCardNumber);
	}

	this->addChild(layerColorBG);
};

//创建卡片
CardSprite* CardSprite::creatCardSprite(int number, int width, int height, float cardx, int cardy) {
	//自定义类的写法，属于模板写法
	CardSprite* enemy = new CardSprite();
	if (enemy && enemy->init())
	{
		enemy->autorelease();
		enemy->enemyinit(number, width, height, cardx, cardy);

		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool CardSprite::init() {
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}


//设置数字
void CardSprite::setNumber(int num) {
	number = num;

	//更新控件上的数字
	if (number>0)
	{
		labCardNumber->setString(__String::createWithFormat("%i", number)->getCString()); //固定写法
	}
	else
	{
		labCardNumber->setString("");
	}
	//设置数字大小
	if (number>=0)
	{
		labCardNumber->setSystemFontSize(100);
	}
	if (number >= 16)
	{
		labCardNumber->setSystemFontSize(90);
	}
	if (number >= 128)
	{
		labCardNumber->setSystemFontSize(80);
	}
	if (number >= 1024)
	{
		labCardNumber->setSystemFontSize(70);
	}

	//设置数字的颜色
	if (number == 0)
	{
		layerColorBG->setColor(cocos2d::Color3B(200, 190, 180));
	}
	if (number == 2)
	{
		layerColorBG->setColor(cocos2d::Color3B(240,230,220));
	}
	if (number == 4)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 220, 200));
	}
	if (number == 8)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 180, 120));
	}
	if (number == 16)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 120, 90));
	}
	if (number == 32)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 90, 60));
	}
	if (number == 64)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 90, 60));
	}
	if (number == 128)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 90, 60));
	}
	if (number == 256)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 200, 70));
	}
	if (number == 512)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 200, 70));
	}
	if (number == 1024)
	{
		layerColorBG->setColor(cocos2d::Color3B(0, 130, 0));
	}
	if (number == 2048)
	{
		layerColorBG->setColor(cocos2d::Color3B(0, 130, 0));
	}
}

//获取数字
int CardSprite::getNumber() {
	return number;
}
