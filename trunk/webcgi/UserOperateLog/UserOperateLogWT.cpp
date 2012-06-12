#include <iostream>
#include "UserOperateLog.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CUserOperateLog::slots_[] = { WSlot_("LogQuery()", false), WSlot_("LogForward()", false), WSlot_("LogBack()", false), WSlot_("ShowHelp()", false), WSlot_() };
WSignal_ CUserOperateLog::signals_[] = { WSignal_() };

void CUserOperateLog::buildSlotMap(WSlotMap& result)
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
void CUserOperateLog::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CUserOperateLog::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    LogQuery();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    LogForward();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    LogBack();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    ShowHelp();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CUserOperateLog::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
