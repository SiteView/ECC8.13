#include <iostream>
#include "MonitorDetail.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CMonitorDetail::slots_[] = { WSlot_("LogForward()", false), WSlot_("LogBack()", false), WSlot_("ExportExcel()", false), WSlot_("AutoClickHiddenBtn()", false), WSlot_() };
WSignal_ CMonitorDetail::signals_[] = { WSignal_() };

void CMonitorDetail::buildSlotMap(WSlotMap& result)
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
void CMonitorDetail::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CMonitorDetail::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    LogForward();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    LogBack();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    ExportExcel();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    AutoClickHiddenBtn();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CMonitorDetail::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
