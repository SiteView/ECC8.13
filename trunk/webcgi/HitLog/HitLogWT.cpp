#include <iostream>
#include "E:\SiteViewECC\v72_1\webcgi\HitLog\HitLog.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CHitLog::slots_[] = { WSlot_("ShowHideHelp()", false), WSlot_("LogQuery()", false), WSlot_("ShowFunc()", false), WSlot_("ShowKey()", false), WSlot_("LogPrevious()", false), WSlot_("LogNext()", false), WSlot_("LogStaPrevious()", false), WSlot_("LogStaNext()", false), WSlot_("ExportExcel()", false), WSlot_("ChangePage()", false), WSlot_() };
WSignal_ CHitLog::signals_[] = { WSignal_() };

void CHitLog::buildSlotMap(WSlotMap& result)
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
void CHitLog::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CHitLog::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    ShowHideHelp();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    LogQuery();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    ShowFunc();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    ShowKey();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    LogPrevious();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    LogNext();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    LogStaPrevious();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    LogStaNext();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    ExportExcel();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    ChangePage();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CHitLog::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
