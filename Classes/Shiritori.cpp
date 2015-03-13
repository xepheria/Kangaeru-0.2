#include "Shiritori.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>

USING_NS_CC;
using namespace std;

/*
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
string to_string(int t) {
    ostringstream os;
    os << t;
    return os.str();
}
#endif*/

Shiritori::Shiritori(void){

}

Shiritori::~Shiritori(void){
    CC_SAFE_RELEASE(blinkAction);
    //CC_SAFE_RELEASE(backgroundTiles);
}

Scene* Shiritori::createScene(void){
   // 'scene' is an autorelease object
   auto scene = Scene::create();

   // 'layer' is an autorelease object
   auto layer = Shiritori::create();

   // add layer as a child to scene
   scene->addChild(layer);

   // return the scene
   return scene;
}

bool Shiritori::init(){
   if(!Layer::init()){
      return false;
   }
   
   //create background
   auto winSize = Director::getInstance()->getVisibleSize();
   auto background = Sprite::create("gameBackground.jpg");
   background->setScale(winSize.width/background->getContentSize().width);
   background->setPosition(winSize.width/2, winSize.height/2);
   this->addChild(background);     // add a background sprite to watch more obviously

   //back to main menu button
   auto back_label = Label::createWithTTF("Back to Main Menu", "fonts/falcon.ttf", 48);
   auto back_menu = MenuItemLabel::create(back_label, CC_CALLBACK_1(Shiritori::backToMainScene, this));
   auto backMenu = Menu::create(back_menu, nullptr);
   backMenu->setPosition(Point(winSize.width, winSize.height));
   back_menu->setAnchorPoint(Point(1, 1));
   this->addChild(backMenu, 1);
   
   //create menu of existing lists
   menu = Menu::create();
   for(int i = 0; i < UserDefault::getInstance()->getIntegerForKey("numOfLists"); i++){
      string listName = "list" + to_string(i);
      auto addToDaMenu_label = Label::createWithTTF(UserDefault::getInstance()->getStringForKey(listName.c_str()), "fonts/falcon.ttf", 40);
      addToDaMenu_label->enableOutline(Color4B::BLACK, 3);
      auto addToDaMenu = MenuItemLabel::create(addToDaMenu_label, CC_CALLBACK_1(Shiritori::startWithListCallback, this));
      addToDaMenu->setTag(1); //tag indicates this is a user list
      menu->addChild(addToDaMenu);
   }
   menu->setPosition(winSize.width*.75, winSize.height/2);
   menu->alignItemsVerticallyWithPadding(15);
   this->addChild(menu, 1);
   title = Label::createWithTTF("User Lists", "fonts/falcon.ttf", 36);
   title->enableOutline(Color4B::BLACK, 3);
   title->setPosition(winSize.width*.75, winSize.height*.8);
   this->addChild(title);
   
   //create menu of dictionary lists
   menu2 = Menu::create();
   auto N5menu_label = Label::createWithTTF("N5", "fonts/falcon.ttf", 48);
   N5menu_label->enableOutline(Color4B::BLACK, 3);
   auto N5menu = MenuItemLabel::create(N5menu_label, CC_CALLBACK_1(Shiritori::startWithListCallback, this));
   N5menu->setTag(0);
   menu2->addChild(N5menu);
   //*********
   //add more lists here as they are made
   //*********
   menu2->setPosition(winSize.width/4, winSize.height/2);
   menu2->alignItemsVerticallyWithPadding(15);
   this->addChild(menu2, 1);
   title2 = Label::createWithTTF("Default Lists", "fonts/falcon.ttf", 48);
   title2->enableOutline(Color4B::BLACK, 3);
   title2->setPosition(winSize.width/4, winSize.height*.8);
   this->addChild(title2);
   
   //initialize blinking action
   blinkAction = Sequence::create(Blink::create(1.0, 3), Hide::create(), NULL);
   blinkAction->retain();
   //create Sprites
   maru = Sprite::create("maru.png");
   batsu = Sprite::create("batsu.png");
   //backgroundTile1 = Sprite::create("backgroundTile.png");
   //backgroundTile2 = Sprite::create("backgroundTile.png");
   //backgroundTile3 = Sprite::create("backgroundTile.png");
	backgroundTiles.reserve(4);
	tileList.reserve(20);
	//backgroundTiles.retain();
	//tileList.retain();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Shiritori::onTouchBegan,this);
	listener->onTouchEnded = CC_CALLBACK_2(Shiritori::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	
	//tileList.pushBack(starterSprite);





   maru->setPosition(winSize.width/2, winSize.height/2);
   batsu->setPosition(winSize.width/2, winSize.height/2);
   //backgroundTile1->setPosition(winSize.width/5,winSize.height*.75);
   //backgroundTile3->setPosition((winSize.width/5)*3,winSize.height*.75);
   //backgroundTile4->setPosition((winSize.width/5)*4,winSize.height*.75);
   maru->setVisible(false);
   batsu->setVisible(false);

   


   this->addChild(maru);
   this->addChild(batsu);
   
   //init score to 0
   currentScore = 0;
   topScore = 0;
   currentScorelbl = Label::createWithTTF("0", "fonts/falcon.ttf", 60);
   currentScorelbl->setColor(Color3B::ORANGE);
   currentScorelbl->enableOutline(Color4B::BLACK, 1);
   currentScorelbl->setPosition(winSize.width*.33, winSize.height*.05);
   topScorelbl = Label::createWithTTF("0", "fonts/falcon.ttf", 60);
   topScorelbl->setColor(Color3B::RED);
   topScorelbl->enableOutline(Color4B::BLACK, 1);
   topScorelbl->setPosition(winSize.width*.66, winSize.height*.05);
   this->addChild(currentScorelbl);
   this->addChild(topScorelbl);
   
   return true;
}

//back to main menu
void Shiritori::backToMainScene(cocos2d::Ref *pSender){
   //saveData();
   Director::getInstance()->popScene();
}

//start game with chosen list
void Shiritori::startWithListCallback(cocos2d::Ref *pSender){
   auto ref = dynamic_cast<MenuItemLabel*>(pSender);
   
   Label *listLabel = dynamic_cast<Label*>(ref->getLabel());
   string path = listLabel->getString() + ".plist";
   //list is default
   if(ref->getTag() == 0){
      path = "dictionaries/" + path;
      path = FileUtils::getInstance()->fullPathForFilename(path);
      kanjiDict = FileUtils::getInstance()->getValueMapFromFile(path);
   }
   //list is user made
   else {
      path = FileUtils::getInstance()->getWritablePath() + path;
      kanjiDict = FileUtils::getInstance()->getValueMapFromFile(path);
   }


   auto winSize = Director::getInstance()->getVisibleSize();

	for(int i=0; i<4; i++){
		cocos2d::Sprite *spr = Sprite::create("backgroundTile.png");
		cocos2d::Label *lbl = Label::createWithTTF(kanjiDict.at(to_string(0).c_str()).asValueMap().at("Kanji").asString(),"fonts/falcon.ttf",36);
		lbl->setTag(1);
		lbl->setTextColor(Color4B::BLACK);
		lbl->setPosition((spr->getContentSize().width)/2,(spr->getContentSize().height)/2);
		spr->addChild(lbl);
		spr->setTag(0);
		if(i == 3){
			spr->setTag(1);
		}
		backgroundTiles.pushBack(spr);
   		spr->setPosition((winSize.width/5)*(i+1),winSize.height*.25);
		spr->setVisible(false);
		this->addChild(spr);
	}


	starterSprite = Sprite::create("backgroundTile.png");

	cocos2d::Label *starterlbl = Label::createWithTTF(kanjiDict.at(to_string(0).c_str()).asValueMap().at("Kanji").asString(),"fonts/falcon.ttf",36);
	
	starterlbl->setTag(1);
   	starterSprite->setPosition((winSize.width/2),winSize.height/2);

	starterSprite->addChild(starterlbl);
	starterlbl->setTextColor(Color4B::BLACK);
	starterlbl->setPosition((starterSprite->getContentSize().width)/2,(starterSprite->getContentSize().height)/2);
	tileList.pushBack(starterSprite); 
	this->addChild(starterSprite);

	starterSprite->setVisible(false);

   
   menu->setVisible(false);
   menu2->setVisible(false);
   title->setVisible(false);
   title2->setVisible(false);
  
	cocos2d::Sprite *spr;
	for(int i=0; i<4; i++){
		spr = (Sprite *)(backgroundTiles.at(i));
	        spr->setVisible(true);	
	}
		
		spr = (Sprite *)(tileList.at(0)); 		
		spr->setVisible(true);

   /*auto winSize = Director::getInstance()->getVisibleSize();
   question = Label::create("This is an empty question that tests word wrapping if the question is too long.", "fonts/falcon.ttf", 64);
   question->setAlignment(TextHAlignment::CENTER);
   question->setDimensions(winSize.width, winSize.height*.6);
   question->enableOutline(Color4B::BLACK, 4);
   question->setPosition(winSize.width/2, winSize.height*.6);
   this->addChild(question);
   
   ans1 = MenuItemLabel::create(Label::create("answer 1", "fonts/falcon.ttf", 60), this, menu_selector(Shiritori::evaluateAnswer));
   dynamic_cast<Label*>(ans1->getLabel())->enableOutline(Color4B::BLACK, 3);
   ans1->setAnchorPoint(Vec2(1, .5));
   
   ans2 = MenuItemLabel::create(Label::create("answer 2", "fonts/falcon.ttf", 60), this, menu_selector(Shiritori::evaluateAnswer));
   dynamic_cast<Label*>(ans2->getLabel())->enableOutline(Color4B::BLACK, 3);
   ans2->setAnchorPoint(Vec2(0, .5));
   
   ans3 = MenuItemLabel::create(Label::create("answer 3", "fonts/falcon.ttf", 60), this, menu_selector(Shiritori::evaluateAnswer));
   dynamic_cast<Label*>(ans3->getLabel())->enableOutline(Color4B::BLACK, 3);
   ans3->setAnchorPoint(Vec2(1, 2.5));
   
   ans4 = MenuItemLabel::create(Label::create("answer 4", "fonts/falcon.ttf", 60), this, menu_selector(Shiritori::evaluateAnswer));
   dynamic_cast<Label*>(ans4->getLabel())->enableOutline(Color4B::BLACK, 3);
   ans4->setAnchorPoint(Vec2(0, 2.5));
   
   answers = Menu::create(ans1, ans2, ans3, ans4, nullptr);
   answers->setPosition(winSize.width/2, winSize.height/2);
   answers->alignItemsInColumns(2, 2);
   this->addChild(answers);
   */
   askQuestion(0);
}



void Shiritori::askQuestion(float dt){
   //select a kanji from the list for correct answer
   srand(time(NULL));
   int correctIndex = rand() % kanjiDict.size();
   ValueMap correctKanji = kanjiDict.at(to_string(correctIndex).c_str()).asValueMap();
   //get the wrong indexes, make sure they don't match correct index
   int wrongIndex1, wrongIndex2, wrongIndex3;
   do{
      wrongIndex1 = rand() % kanjiDict.size();
      wrongIndex2 = rand() % kanjiDict.size();
      wrongIndex3 = rand() % kanjiDict.size();
   } while (wrongIndex1 == correctIndex || wrongIndex2 == correctIndex || wrongIndex3 == correctIndex || wrongIndex1 == wrongIndex2 || wrongIndex1 == wrongIndex3 || wrongIndex2 == wrongIndex3);
   /*
   //set question type
   //0: kunyomi
   //1: definition
   //2: onyomi
   int questionType = rand() % 3;
   
   //set question to kanji clue
   if(questionType == 0){
      if(correctKanji.find("Kunyomi") != correctKanji.end())
         question->setString(correctKanji.at("Kunyomi").asString());
      else
         question->setString(correctKanji.at("Onyomi").asString());
   }
   else if(questionType == 1){
      question->setString(correctKanji.at("Definition").asString());
   }
   else if(questionType == 2){
      if(correctKanji.find("Onyomi") != correctKanji.end())
         question->setString(correctKanji.at("Onyomi").asString());
      else
         question->setString(correctKanji.at("Kunyomi").asString());
   }
   
   //set the anwers, make sure to set tag on right answer to 1, wrong answers to 0
   int questionOrder = rand() % 4;
   switch(questionOrder){
   case 0:
      //correct answer is ans1
      ans1->setString(correctKanji.at("Kanji").asString());
      ans1->setTag(1);
      //wrong answers
      ans2->setString(kanjiDict.at(to_string(wrongIndex1).c_str()).asValueMap().at("Kanji").asString());
      ans2->setTag(0);
      ans3->setString(kanjiDict.at(to_string(wrongIndex2).c_str()).asValueMap().at("Kanji").asString());
      ans3->setTag(0);
      ans4->setString(kanjiDict.at(to_string(wrongIndex3).c_str()).asValueMap().at("Kanji").asString());
      ans4->setTag(0);
      break;
   case 1:
      //correct answer is ans2
      ans2->setString(correctKanji.at("Kanji").asString());
      ans2->setTag(1);
      //wrong answers
      ans1->setString(kanjiDict.at(to_string(wrongIndex1).c_str()).asValueMap().at("Kanji").asString());
      ans1->setTag(0);
      ans3->setString(kanjiDict.at(to_string(wrongIndex2).c_str()).asValueMap().at("Kanji").asString());
      ans3->setTag(0);
      ans4->setString(kanjiDict.at(to_string(wrongIndex3).c_str()).asValueMap().at("Kanji").asString());
      ans4->setTag(0);
      break;
   case 2:
      //correct answer is ans3
      ans3->setString(correctKanji.at("Kanji").asString());
      ans3->setTag(1);
      //wrong answers
      ans1->setString(kanjiDict.at(to_string(wrongIndex1).c_str()).asValueMap().at("Kanji").asString());
      ans1->setTag(0);
      ans2->setString(kanjiDict.at(to_string(wrongIndex2).c_str()).asValueMap().at("Kanji").asString());
      ans2->setTag(0);
      ans4->setString(kanjiDict.at(to_string(wrongIndex3).c_str()).asValueMap().at("Kanji").asString());
      ans4->setTag(0);
      break;
   case 3:
      //correct answer is ans4
      ans4->setString(correctKanji.at("Kanji").asString());
      ans4->setTag(1);
      //wrong answers
      ans1->setString(kanjiDict.at(to_string(wrongIndex1).c_str()).asValueMap().at("Kanji").asString());
      ans1->setTag(0);
      ans2->setString(kanjiDict.at(to_string(wrongIndex2).c_str()).asValueMap().at("Kanji").asString());
      ans2->setTag(0);
      ans3->setString(kanjiDict.at(to_string(wrongIndex3).c_str()).asValueMap().at("Kanji").asString());
      ans3->setTag(0);
      break;
   }*/
}


bool Shiritori::onTouchBegan(cocos2d::Touch* pTouches, cocos2d::Event* event){
//	CCLOG("in begin\n");
	return true;

/*
	SetIterator i;
	Touch *touch;
	Point tap;
	cocos2d::Sprite *spr;

	for(i=pTouches->begin(); i!=pTouches->end();i++){
		touch = (Touch *)(*i);
		if(touch){
			tap = touch->getLocation();
			for(int p = 0; p < 4; p++){
				spr = (Sprite *)backgroundTiles.at(p);
				if(spr->boundingBox().containsPoint(tap)){
					player->setTouch(touch);
				}
			}
		}
	}
*/
}
void Shiritori::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){

	//Sprite* spr;
	Sprite* spr2;
		for(auto spr : backgroundTiles){
				if(spr->getBoundingBox().containsPoint(convertTouchToNodeSpace(touch))){
					if(spr->getTag() == 1){
					tileList.pushBack(MakeSprite());
					cout << tileList.size() << endl;
					auto sz = ((Sprite*)tileList.at(0))->getContentSize();
						currentScore++;
						if(currentScore > topScore){
							topScore = currentScore;
							topScorelbl->setString(to_string(topScore));
						}
						currentScorelbl->setString(to_string(currentScore));
						//maru->runAction(blinkAction);
					for(int i = 0; i<tileList.size()-1; i++){
   						//auto winSize = Director::getInstance()->getVisibleSize();
						spr2 = (Sprite*)tileList.at(i);
						auto pos = spr2->getPosition();				
						//auto sz = spr2->getContentSize();
						spr2->setPosition(pos.x - sz.width - 5, pos.y);

					}
					}
					else{

						currentScore = 0;
      						currentScorelbl->setString(to_string(currentScore));
      						//batsu->runAction(blinkAction);
						for(int i=1;i<tileList.size();i++){
							spr2 = (Sprite*)tileList.at(i);
							spr2->setVisible(false);
							spr2->removeFromParent();
						}
						tileList.empty();
						tileList.pushBack(starterSprite);
						auto winSize = Director::getInstance()->getVisibleSize();
						starterSprite->setPosition(winSize.width/2,winSize.height/2);
					}

								
				}	
		}
	

/*	CCSetIterator i;
	CCTouch *touch;
	CCPoint tap;
	Sprite *player;

	for(i = pTouches->begin(); i!= pTouches->end(); i++){
		touch = (CCTouch *)(*i);
		if(touch){
			tap = touch->getLocation();
			for(unsigned int p = 0; p<backgroundTiles.size();p++){
				spr = (Sprite *)backgroundTiles.at(p);
				if(spr->boundingBox().containsPoint(tap)){
					cout << "Selected " << p << "\n";
				}
			}
		}
	}*/
}

Sprite* Shiritori::MakeSprite(){
	//kanjiDict.at(to_string(wrongIndex1).c_str()).asValueMap().at("Kanji").asString()
	auto winSize = Director::getInstance()->getVisibleSize();
	cocos2d::Sprite *spr = Sprite::create("backgroundTile.png");
	cocos2d::Label *lbl = Label::createWithTTF(kanjiDict.at(to_string(0).c_str()).asValueMap().at("Kanji").asString(),"fonts/falcon.ttf",36);
	lbl->setTag(1);
	lbl->setTextColor(Color4B::BLACK);
	lbl->setPosition((spr->getContentSize().width)/2,(spr->getContentSize().height)/2);
	spr->addChild(lbl);
	spr->setPosition(winSize.width/2,winSize.height/2);
	spr->setTag(0);
	spr->setVisible(true);
	this->addChild(spr);
	return spr;
}


void Shiritori::evaluateAnswer(Ref *pSender){
   MenuItemLabel *ref = dynamic_cast<MenuItemLabel*>(pSender);
   //cocos2d::Sprite *ans = (Sprite *)pSender;
   if(ref->getTag() == 0){
      topScore++;
      topScorelbl->setString(to_string(topScore));
      batsu->runAction(blinkAction);
   }
   else if(ref->getTag() == 1){
      currentScore++;
      currentScorelbl->setString(to_string(currentScore));
      maru->runAction(blinkAction);
	//cocos2d::Sprite *spr = (Sprite *)(tileList.at(tileList.size()-1));
	//cocos2d::Label *lbl = (Label *)(sprite->getChildByTag(1));
	
   }
   else
      cout << "wat" << endl;
   
   //wait until animation done
   this->scheduleOnce(schedule_selector(Shiritori::askQuestion), 1.5f);
}
