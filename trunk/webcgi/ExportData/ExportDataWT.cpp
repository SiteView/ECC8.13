#include <iostream>
#include "ExportData.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CExportData::slots_[] = { WSlot_("SaveTime()", false), WSlot_("ShowHideHelp()", false), WSlot_("ExportData()", false), WSlot_("ShowMac()", false), WSlot_() };
WSignal_ CExportData::signals_[] = { WSignal_() };

void CExportData::buildSlotMap(WSlotMap& result)
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
void CExportData::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CExportData::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    SaveTime();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    ShowHideHelp();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    ExportData();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    ShowMac();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CExportData::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
