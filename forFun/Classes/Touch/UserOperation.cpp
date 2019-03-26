#include "UserOperation.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


UserOperation::UserOperation()
{
}


UserOperation::~UserOperation()
{
}


Scene* UserOperation::createScene()
{
	auto scene = Scene::create();
	auto Layer = UserOperation::create();
	scene->addChild(Layer);
	return scene;
}


// on "init" you need to initialize your instance
bool UserOperation::init()
{

	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//点击监听事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(UserOperation::ontouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(UserOperation::ontouchEnd, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}


//手势识别事件
bool UserOperation::ontouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event) {
	Point touchPix = touch->getLocation();
	firstX = touchPix.x;
	firstY = touchPix.y;
	return true;
};
void UserOperation::ontouchEnd(cocos2d::Touch* touch, cocos2d::Event* unused_event) {
	//计算XY轴的值
	Point touchPix = touch->getLocation();
	endX = touchPix.x - firstX;
	endY = touchPix.y - firstY;
	//用绝对值判断是上下还是左右,如果x>y，即为左右，否则为y
	if (abs(endX)>abs(endY))
	{
		if (endX + 5>0)
			//右
		{
			doRight();
		}
		else
			//左
		{
			doLeft();
		}
	}
	else
	{
		if (endY + 5>0)
			//上
		{
			doUp();
		}
		else
			//下
		{
			doDown();
		}
	}
};
//上下左右
bool UserOperation::doUp() {
	log("up");
	return true;
};
bool UserOperation::doDown() {
	log("down");
	return true;
};
bool UserOperation::doLeft() {
	log("left");
	return true;
};
bool UserOperation::doRight() {
	log("right");
	return true;
};