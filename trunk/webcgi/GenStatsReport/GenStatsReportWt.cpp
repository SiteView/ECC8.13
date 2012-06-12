#include <iostream>
#include "GenStatsReport.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CGenStatsReport::slots_[] = { WSlot_("FastGenReport()", false), WSlot_("Close()", false), WSlot_() };
WSignal_ CGenStatsReport::signals_[] = { WSignal_() };

void CGenStatsReport::buildSlotMap(WSlotMap& result)
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
void CGenStatsReport::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CGenStatsReport::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    FastGenReport();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Close();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CGenStatsReport::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
