#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "Card\CardSprite.h"

USING_NS_CC;


MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}


Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto Layer = MainScene::create();
	scene->addChild(Layer);
	return scene;
}


// on "init" you need to initialize your instance
bool MainScene::init()
{

	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//添加并且设置背景
	auto layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(180, 170, 160, 255));
	this->addChild(layerColorBG);

	//点击监听事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::ontouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MainScene::ontouchEnd, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//添加卡片到场景中
	cocos2d::Size windowSize = Director::getInstance()->getVisibleSize();
	addCard(windowSize);

	//初始化总数label
	score = 0;
	auto scoreLabel2 = cocos2d::Label::createWithSystemFont("分数", "HirakakuProN-W6", 100);
	scoreLabel2->setPosition(Point(windowSize.width / 4, windowSize.height - 200));
	scoreLabel2->setSystemFontSize(100);
	this->addChild(scoreLabel2);

	scoreLabel = cocos2d::Label::createWithSystemFont("0", "HirakakuProN-W6", 100);
	scoreLabel->setPosition(Point(windowSize.width / 4+200, windowSize.height - 200));
	scoreLabel->setSystemFontSize(100);
	this->addChild(scoreLabel);

	return true;
}


//手势识别事件
bool MainScene::ontouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event) {
	Point touchPix = touch->getLocation();
	firstX = touchPix.x;
	firstY = touchPix.y;
	return true;
};
void MainScene::ontouchEnd(cocos2d::Touch* touch, cocos2d::Event* unused_event) {
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
			if (doRight()) 
			{
				autoAddCard();
				checkGameOver();
			}
		}
		else
			//左
		{
			if (doLeft())
			{
				autoAddCard();
				checkGameOver();
			};
		}
	}
	else
	{
		if (endY + 5>0)
			//上
		{
			if (doUp()) 
			{
				autoAddCard(); 
				checkGameOver();
			}
			
		}
		else
			//下
		{
			if (doDown())
			{
				autoAddCard();
				checkGameOver();
			}
		}
	}
};
//上下左右
bool MainScene::doUp() {
	log("up");
	isdo = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)  //向右需要从最右边开始排序
		{
			for (int y1 = y - 1; y1 >= 0; y1--)
			{
				if (cardArr[x][y1]->getNumber()>0) //判断旁边的图片是否为空，不为空就进行下面的逻辑运算
				{
					if (cardArr[x][y]->getNumber() <= 0) //判断自己是不是为空，如果为空，则把旁边一张图片移过来
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y++;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()) //判断旁边的图片是不是和自己一样，如果一样，自己则*2，旁边的图片变为空
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);

						//添加分数
						score += cardArr[x][y]->getNumber();
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString()	);

						isdo = true;
					}
					break; //找到不为空的卡片做了或者加法后就跳出该次循环
				}
			}
		}
	}


	return isdo;
};
bool MainScene::doDown() {
	log("down");
	isdo = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int y1 = y + 1; y1 < 4; y1++)
			{
				if (cardArr[x][y1]->getNumber()>0) //判断旁边的图片是否为空，不为空就进行下面的逻辑运算
				{
					if (cardArr[x][y]->getNumber() <= 0) //判断自己是不是为空，如果为空，则把旁边一张图片移过来
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y--;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()) //判断旁边的图片是不是和自己一样，如果一样，自己则*2，旁边的图片变为空
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);

						//添加分数
						score += cardArr[x][y]->getNumber();
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
};
bool MainScene::doLeft() {
	log("left");
	isdo = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int x1 = x + 1; x1 < 4; x1++)
			{
				if (cardArr[x1][y]->getNumber()>0) //判断旁边的图片是否为空，不为空就进行下面的逻辑运算
				{   
					if (cardArr[x][y]->getNumber() <= 0) //判断自己是不是为空，如果为空，则把旁边一张图片移过来
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x--; //让X往前退一步再做一个运算
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()) //判断旁边的图片是不是和自己一样，如果一样，自己则*2，旁边的图片变为空
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2); 
						cardArr[x1][y]->setNumber(0);

						//添加分数
						score += cardArr[x][y]->getNumber();
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
};
bool MainScene::doRight() {
	log("right");
	isdo = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--)  //向右需要从最右边开始排序
		{
			for (int x1 = x - 1; x1 >= 0; x1--)
			{
				if (cardArr[x1][y]->getNumber()>0) //判断旁边的图片是否为空，不为空就进行下面的逻辑运算
				{
					if (cardArr[x][y]->getNumber() <= 0) //判断自己是不是为空，如果为空，则把旁边一张图片移过来
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x++;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()) //判断旁边的图片是不是和自己一样，如果一样，自己则*2，旁边的图片变为空
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);

						//添加分数
						score += cardArr[x][y]->getNumber();
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
};


void MainScene::addCard(cocos2d::Size visiableSize) {
	int width = (visiableSize.width-30) / 4;
	//CardSprite* card = CardSprite::creatCardSprite(2, width, width, width*0+15 , width*0+15 +visiableSize.height / 4);
	//addChild(card);
	//4*4单元格
	int i = 1;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0;  x < 4; x++)
		{
			CardSprite* card = CardSprite::creatCardSprite(0, width, width, width*x+22 , width*y+22 +visiableSize.height / 4);
			addChild(card);
			i++;
			cardArr[x][y] = card;
		}
	}
	autoAddCard();
	autoAddCard();
	autoAddCard();
	autoAddCard();
	autoAddCard();
}

void MainScene::autoAddCard() {
	int x = CCRANDOM_0_1() * 4;
	int y = CCRANDOM_0_1() * 4;

	if (cardArr[x][y]->getNumber()>0)
	{
		autoAddCard();
	}
	else
	{
		cardArr[x][y]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
	}
}

void MainScene::checkGameOver() 
{
	bool isOver = true;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (cardArr[x][y]->getNumber()==0||
				(x > 0 && cardArr[x][y]->getNumber()== cardArr[x - 1][y]->getNumber())||
				(x < 3 && cardArr[x][y]->getNumber()== cardArr[x + 1][y]->getNumber())||
				(y >0  && cardArr[x][y]->getNumber() == cardArr[x][y-1]->getNumber()) || 
				(y < 3 && cardArr[x][y]->getNumber() == cardArr[x][y+1]->getNumber()))
			{
				isOver = false;
			}
		}
	}
	if (isOver)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
	}
}