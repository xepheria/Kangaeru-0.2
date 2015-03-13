#ifndef __MATCHINGGAME_H__
#define __MATCHINGGAME_H__

#include "cocos2d.h"

class MatchingGame : public cocos2d::Layer
{
public:
   MatchingGame(void);
   ~MatchingGame(void);
   
   //create default functions
   CREATE_FUNC(MatchingGame);
   
   static cocos2d::Scene *createScene();
   
   virtual bool init() override;
   
   //return to main menu
   void backToMainScene(cocos2d::Ref *pSender);
   
   //start game with chosen list
   void startWithListCallback(cocos2d::Ref *pSender);
   void askQuestion(float dt);
   void evaluateAnswer(cocos2d::Ref *pSender);
   
private:
   cocos2d::Menu *menu;
   cocos2d::Menu *menu2;
   cocos2d::Label *title;
   cocos2d::Label *title2;
   
   cocos2d::Label *errorMsg;
   
   cocos2d::ValueMap kanjiDict;
   
   cocos2d::Label *question;
   cocos2d::MenuItemLabel *ans1;
   cocos2d::MenuItemLabel *ans2;
   cocos2d::MenuItemLabel *ans3;
   cocos2d::MenuItemLabel *ans4;
   cocos2d::Menu *answers;
   cocos2d::Sequence *blinkAction;
   cocos2d::Sprite *maru;
   cocos2d::Sprite *batsu;
   
   //score display
   int currentCorrect;
   int currentWrong;
   cocos2d::Label *correctScore;
   cocos2d::Label *wrongScore;
};

#endif // __MATCHINGGAME_H__
