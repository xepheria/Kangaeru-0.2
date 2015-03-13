#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"
#include "KanjiBase.h"
#include "MatchingGame.h"
#include "Shiritori.h"

class MainMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    //functions for menu item callbacks
    void menuCloseCallback(cocos2d::Ref *pSender);
    void menuGame1Callback(cocos2d::Ref *pSender);
    void menuGame2Callback(cocos2d::Ref *pSender);
    void menuGame3Callback(cocos2d::Ref *pSender);
    
    //change scenes
    void transitionToKanjiBaseScene();
    void toKanjiBaseScene();
    void toGameScene();
    void toGame2Scene();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_H__
