#include <iostream>
#include "AlertHistory.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CAlertHistory::slots_[] = { WSlot_("AlertHistory(const std::string)", false), WSlot_("HistoryBack()", false), WSlot_("HistoryForward()", false), WSlot_("HistoryReturnBtn()", false), WSlot_("AlertQuery()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false),WSlot_("ShowHelp()", false), WSlot_() };
WSignal_ CAlertHistory::signals_[] = { WSignal_() };

void CAlertHistory::buildSlotMap(WSlotMap& result)
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
void CAlertHistory::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CAlertHistory::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    AlertHistory(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    HistoryBack();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    HistoryForward();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    HistoryReturnBtn();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    AlertQuery();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    ExChange();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    ShowHelp();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CAlertHistory::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
