#include <iostream>
#include "Translate.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CTranslate::slots_[] = { WSlot_("EditIDSValue(const std::string)", false), WSlot_("EditReturn(int)", false), WSlot_() };
WSignal_ CTranslate::signals_[] = { WSignal_() };

void CTranslate::buildSlotMap(WSlotMap& result)
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
void CTranslate::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CTranslate::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    EditIDSValue(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    EditReturn(*((int *)args[0]));
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CTranslate::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
