#include <iostream>
#include "StatsReportList.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CStatsReportList::slots_[] = { WSlot_("FastGenReport()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_("SelAll()", false), WSlot_("SelNone()", false), WSlot_("SelInvert()", false), WSlot_("BeforeDelList()", false), WSlot_("DelList()", false), WSlot_("ReturnMainReport()", false), WSlot_() };
WSignal_ CStatsReportList::signals_[] = { WSignal_() };

void CStatsReportList::buildSlotMap(WSlotMap& result)
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
void CStatsReportList::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CStatsReportList::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    FastGenReport();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    ExChange();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    SelAll();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    SelNone();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    SelInvert();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    BeforeDelList();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    DelList();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    ReturnMainReport();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CStatsReportList::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
