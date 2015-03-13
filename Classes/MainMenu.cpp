#include "MainMenu.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //cocos vector to hold menu items
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems;
    
    //game 1
    auto pGame1Item_label = Label::createWithTTF("Kanji Lists", "fonts/falcon.ttf", 72);
    pGame1Item_label->enableOutline(Color4B::BLACK, 1);
    auto *pGame1Item = MenuItemLabel::create(pGame1Item_label, CC_CALLBACK_1(MainMenu::menuGame1Callback, this));
    pMenuItems.pushBack(pGame1Item); //add to list
    
    //game 2
    auto pGame2Item_label = Label::createWithTTF("Matching Game", "fonts/falcon.ttf", 72);
    pGame2Item_label->enableOutline(Color4B::BLACK, 1);
    auto *pGame2Item = MenuItemLabel::create(pGame2Item_label, CC_CALLBACK_1(MainMenu::menuGame2Callback, this));
    pMenuItems.pushBack(pGame2Item);
    
    //game 3
    auto pGame3Item_label = Label::createWithTTF("Shiritori", "fonts/falcon.ttf", 72);
    pGame3Item_label->enableOutline(Color4B::BLACK, 1);
    auto *pGame3Item = MenuItemLabel::create(pGame3Item_label, CC_CALLBACK_1(MainMenu::menuGame3Callback, this));
    pMenuItems.pushBack(pGame3Item);
    
    //close menu
    auto pCloseItem_label = Label::createWithTTF("Quit", "fonts/falcon.ttf", 72);
    pCloseItem_label->enableOutline(Color4B::BLACK, 1);
    auto *pCloseItem = MenuItemLabel::create(pCloseItem_label, CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
    pMenuItems.pushBack(pCloseItem); //add to list
    
    cocos2d::Menu *pMenu = cocos2d::Menu::createWithArray(pMenuItems); //create menu

    pMenu->alignItemsVerticallyWithPadding(25);

    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("漢ガエル", "fonts/falcon.ttf", 84);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "MainMenu" splash screen"
    auto sprite = Sprite::create("MainMenubackground.jpg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //scale sprite
    sprite->setScale(visibleSize.height/sprite->getContentSize().height);

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}

//Kanji Database
void MainMenu::menuGame1Callback(cocos2d::Ref *pSender){
   toKanjiBaseScene();
}

//Matching Game
void MainMenu::menuGame2Callback(cocos2d::Ref *pSender){
   toGameScene();
}

//Shiritori
void MainMenu::menuGame3Callback(cocos2d::Ref *pSender){
   toGame2Scene();
}

//Close game
void MainMenu::menuCloseCallback(cocos2d::Ref *pSender){
    Director::getInstance()->end();
    exit(0);
}

//game scene
void MainMenu::toGameScene()
{
   //get the game scene and run it.
   auto scene = MatchingGame::createScene();
   Director::getInstance()->pushScene(scene);
}

void MainMenu::toGame2Scene(){
   auto scene = Shiritori::createScene();
   Director::getInstance()->pushScene(scene);
}

//kanji lists access
void MainMenu::toKanjiBaseScene()
{
    //get the kanjibase scene and run it.
    auto scene = KanjiBase::createScene();
    Director::getInstance()->pushScene(scene);
    //what is diff between replaceScene and pushScene?
}

/*//transition to kanji base
void MainMenu::transitionToKanjiBaseScene(){
   toKanjiBaseScene();
}*/
