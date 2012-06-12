#include <iostream>
#include "AlertList.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

//为解决Ticket #112 东方有线ECC邮件报警主题定制问题而修改下面代码。
//苏合 2007-08-02

//+++++++++++++++++++++++++++代码修改开始  苏合 2007-08-02+++++++++++++++++++++++++++
//WSlot_ CAlertList::slots_[] = { WSlot_("AddAlert()", false), WSlot_("BeforeDelAlert()", false), WSlot_("DelAlert()", false), WSlot_("EnableAlert()", false), WSlot_("DisableAlert()", false), WSlot_("SelAll()", false), WSlot_("EditAlert(const std::string)", false), WSlot_("SelNone()", false), WSlot_("SelInvert()", false), WSlot_("SaveAlert()", false), WSlot_("CancelAlert()", false), WSlot_("EmailBtn()", false), WSlot_("SmsBtn()", false), WSlot_("ScriptBtn()", false), WSlot_("SoundBtn()", false), WSlot_("SelfDefineBtn()", false), WSlot_("AlertHistory(const std::string)", false), WSlot_("HistoryBack()", false), WSlot_("HistoryForward()", false), WSlot_("HistoryReturnBtn()", false), WSlot_("BackBtn()", false), WSlot_("SaveAndAddAlert()", false), WSlot_("SelSeverChanged()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_("ShowHelp()", false), WSlot_() };
WSlot_ CAlertList::slots_[] = { WSlot_("AddAlert()", false), WSlot_("BeforeDelAlert()", false), WSlot_("DelAlert()", false), WSlot_("EnableAlert()", false), WSlot_("DisableAlert()", false), WSlot_("SelAll()", false), WSlot_("EditAlert(const std::string)", false), WSlot_("SelNone()", false), WSlot_("SelInvert()", false), WSlot_("SaveAlert()", false), WSlot_("CancelAlert()", false), WSlot_("EmailBtn()", false), WSlot_("SmsBtn()", false), WSlot_("ScriptBtn()", false), WSlot_("SoundBtn()", false), WSlot_("SelfDefineBtn()", false), WSlot_("AlertHistory(const std::string)", false), WSlot_("HistoryBack()", false), WSlot_("HistoryForward()", false), WSlot_("HistoryReturnBtn()", false), WSlot_("BackBtn()", false), WSlot_("SaveAndAddAlert()", false), WSlot_("SelSeverChanged()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_("ShowHelp()", false), WSlot_("ShowEdit()", false), WSlot_() };
//+++++++++++++++++++++++++++代码修改结束  苏合 2007-08-02+++++++++++++++++++++++++++

WSignal_ CAlertList::signals_[] = { WSignal_() };

void CAlertList::buildSlotMap(WSlotMap& result)
{
  WContainerWidget::buildSlotMap(result);
  for (int i = 0; slots_[i].good(); ++i)  {
#ifdef WIN32 
	WSlotInstance_ *pw=new WSlotInstance_(this, slots_ + i);	
		std::string strkey=slots_[i].name();	
		WObject::InsertMap(result,strkey,pw);	
#else  
	result[slots_[i].name()] = new WSlotInstance_(this, slots_ + i);
#endif  
	}
}
void CAlertList::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CAlertList::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    AddAlert();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    BeforeDelAlert();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    DelAlert();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    EnableAlert();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    DisableAlert();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    SelAll();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    EditAlert(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    SelNone();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    SelInvert();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    SaveAlert();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    CancelAlert();
    return true;
  }
  if (slot == slots_ + 11) {
    sender_ = sender;    EmailBtn();
    return true;
  }
  if (slot == slots_ + 12) {
    sender_ = sender;    SmsBtn();
    return true;
  }
  if (slot == slots_ + 13) {
    sender_ = sender;    ScriptBtn();
    return true;
  }
  if (slot == slots_ + 14) {
    sender_ = sender;    SoundBtn();
    return true;
  }
  if (slot == slots_ + 15) {
    sender_ = sender;    SelfDefineBtn();
    return true;
  }
  if (slot == slots_ + 16) {
    sender_ = sender;    AlertHistory(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 17) {
    sender_ = sender;    HistoryBack();
    return true;
  }
  if (slot == slots_ + 18) {
    sender_ = sender;    HistoryForward();
    return true;
  }
  if (slot == slots_ + 19) {
    sender_ = sender;    HistoryReturnBtn();
    return true;
  }
  if (slot == slots_ + 20) {
    sender_ = sender;    BackBtn();
    return true;
  }
  if (slot == slots_ + 21) {
    sender_ = sender;    SaveAndAddAlert();
    return true;
  }
  if (slot == slots_ + 22) {
    sender_ = sender;    SelSeverChanged();
    return true;
  }
  if (slot == slots_ + 23) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 24) {
    sender_ = sender;    ExChange();
    return true;
  }
  if (slot == slots_ + 25) {
	  sender_ = sender;    ShowHelp();
	  return true;
  }
  //为解决Ticket #112 东方有线ECC邮件报警主题定制问题而增加下面代码。
  //苏合 2007-08-02

  //+++++++++++++++++++++++++++代码增加开始  苏合 2007-08-02+++++++++++++++++++++++++++
  if (slot == slots_ + 26) {
	  sender_ = sender;    ShowEdit();
	  return true;
  }
  //+++++++++++++++++++++++++++代码增加结束  苏合 2007-08-02+++++++++++++++++++++++++++
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CAlertList::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
