#include <iostream>
#include "WMenuNode.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ WMenuNode::slots_[] = { WSlot_("collapse()", true), WSlot_("expand()", true), WSlot_() };
WSignal_ WMenuNode::signals_[] = { WSignal_() };

void WMenuNode::buildSlotMap(WSlotMap& result)
{
  WCompositeWidget::buildSlotMap(result);
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
void WMenuNode::buildSignalMap(WSignalMap& result)
{
  WCompositeWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool WMenuNode::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    collapse();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    expand();
    return true;
  }
  return WCompositeWidget::triggerSlot(sender, slot, args);
}
bool WMenuNode::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    undoCollapse();
    return true;
  }
  if (slot == slots_ + 1) {
    undoExpand();
    return true;
  }
  return WCompositeWidget::undoTriggerSlot(slot, args);
}
