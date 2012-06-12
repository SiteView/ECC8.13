#include <iostream>
#include "svseview.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVSEView::slots_[] = { WSlot_("enterSVSE(const std::string)", false), WSlot_("EditSE(const std::string)", false), WSlot_() };
WSignal_ SVSEView::signals_[] = { WSignal_("showSVSE(string)", false), WSignal_("EditSEByID(string)", false), WSignal_() };

void SVSEView::buildSlotMap(WSlotMap& result)
{
  WTable::buildSlotMap(result);
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
void SVSEView::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void SVSEView::showSVSE(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 0, args);
}

void SVSEView::EditSEByID(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 1, args);
}

bool SVSEView::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    enterSVSE(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    EditSE(*((const std::string *)args[0]));
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVSEView::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
