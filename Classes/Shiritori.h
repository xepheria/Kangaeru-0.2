#ifndef __Shiritori_H__
#define __Shiritori_H__

#include "cocos2d.h"

class Shiritori : public cocos2d::Layer
{
public:
   Shiritori(void);
   ~Shiritori(void);
   
   //create default functions
   CREATE_FUNC(Shiritori);
   
   static cocos2d::Scene *createScene();
   
   virtual bool init() override;
   
   //return to main menu
   void backToMainScene(cocos2d::Ref *pSender);
   
   //start game with chosen list
   void startWithListCallback(cocos2d::Ref *pSender);
   void askQuestion(float dt);
   void evaluateAnswer(cocos2d::Ref *pSender);
   cocos2d::Sprite* MakeSprite();
   bool  onTouchBegan(cocos2d::Touch*, cocos2d::Event*); 
   void  onTouchEnded(cocos2d::Touch*, cocos2d::Event*);   
private:
   cocos2d::Menu *menu;
   cocos2d::Menu *menu2;
   cocos2d::Label *title;
   cocos2d::Label *title2;
   
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
   cocos2d::Vector<cocos2d::Sprite*> backgroundTiles;   
   cocos2d::Vector<cocos2d::Sprite*> tileList;
   //score display
   int currentScore;
   int topScore;
   cocos2d::Label *currentScorelbl;
   cocos2d::Label *topScorelbl;
   cocos2d::Sprite* starterSprite;
};

#endif // __MATCHINGGAME_H__
