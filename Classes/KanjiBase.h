#ifndef __KANJIBASE_H__
#define __KANJIBASE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include <string>
#include <vector>

class KanjiBase : public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate, public cocos2d::TextFieldDelegate
{
public:
   KanjiBase(void);
   ~KanjiBase(void);

   //create default functions
   CREATE_FUNC(KanjiBase);

   static cocos2d::Scene* createScene();

   virtual bool init() override;
   
   void backToMainScene(cocos2d::Ref *pSender);
   void backToMainMenu(cocos2d::Ref *pSender);
   void N5Callback(cocos2d::Ref *pSender);
   cocos2d::Menu *createKBMenu();
   void addToListCallback(cocos2d::Ref *pSender);
   void addToExistingListCallback(cocos2d::Ref *pSender);
   void createNewListCallback(cocos2d::Ref *pSender);
   void backAddToListCallback(cocos2d::Ref *pSender);
   void returnToAddToListCallback(cocos2d::Ref *pSender);
   void confirmNewListCallback(cocos2d::Ref *pSender);
   
   //table view functions
   virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
   virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
   virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
   virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
   virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
   virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
   
   //wrap text function for displaying kanji information
   std::string wrap(const char*, size_t);
   
   //functions for entering text
   virtual bool onTextFieldAttachWithIME(cocos2d::TextFieldTTF *sender) override;
   virtual bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF *sender) override;
   virtual bool onTextFieldInsertText(cocos2d::TextFieldTTF *sender, const char *text, size_t nLen) override;
   virtual bool onTextFieldDeleteBackward(cocos2d::TextFieldTTF *sender, const char *delText, size_t nLen) override;
   virtual bool onVisit(cocos2d::TextFieldTTF *sender, cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags) override;
    
    //save data function
    //called anytime we return from this scene or close the program from here
    void saveData();
   
private:
   std::vector<std::string> userLists;
   cocos2d::Menu *kanjiBaseMenu;
   cocos2d::ValueMap N5Dict;
   ssize_t numOfCells;
   cocos2d::Menu *kanjiInfoMenu = nullptr;
   cocos2d::MenuItemLabel *kanjiInfoButton;
   cocos2d::Label *kanjiLabel;
   cocos2d::extension::TableView *pTable;
   cocos2d::MenuItemImage *kanjiAddToListButton;
   cocos2d::MenuItemLabel *N5back_menu;
   
   //"add to kanji list" layer that overlays dictionary layer
   bool _addToListScreenUp;
   cocos2d::LayerColor *addToList;
   cocos2d::Sprite *_addToListScreen;
   cocos2d::Menu *_addToListMenu;
   
   //"create new list" layer that overlays "add to kanji list" layer
   bool _createNewListScreenUp;
   cocos2d::LayerColor *createNewList;
   cocos2d::Menu *_createNewListMenu;
   cocos2d::TextFieldTTF *enterListName;
   cocos2d::Menu *_existingListsMenu;
};



#endif // __KANJIBASE_H__
