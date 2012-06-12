#include <iostream>
#include "preview.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CSVPreview::slots_[] = { WSlot_() };
WSignal_ CSVPreview::signals_[] = { WSignal_() };

void CSVPreview::buildSlotMap(WSlotMap& result)
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
void CSVPreview::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CSVPreview::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  return WTable::triggerSlot(sender, slot, args);
}
bool CSVPreview::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
