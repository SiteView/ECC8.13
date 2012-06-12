#include <iostream>
#include "WTreeNode.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ WTreeNode::slots_[] = { WSlot_("collapse()", true), WSlot_("expand()", true), WSlot_("select()", true), WSlot_("OnTreeNodeCheck()", false), WSlot_("OnRightClick()", false), WSlot_() };
WSignal_ WTreeNode::signals_[] = { WSignal_("addmonitor()", false), WSignal_() };

void WTreeNode::buildSlotMap(WSlotMap& result)
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
void WTreeNode::buildSignalMap(WSignalMap& result)
{
  WCompositeWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void WTreeNode::addmonitor()
{
  void **args = 0;
  triggerSignal(signals_ + 0, args);
}

bool WTreeNode::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    collapse();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    expand();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    select();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    OnTreeNodeCheck();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    OnRightClick();
    return true;
  }
  return WCompositeWidget::triggerSlot(sender, slot, args);
}
bool WTreeNode::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    undoCollapse();
    return true;
  }
  if (slot == slots_ + 1) {
    undoExpand();
    return true;
  }
  if (slot == slots_ + 2) {
    undoSelect();
    return true;
  }
  return WCompositeWidget::undoTriggerSlot(slot, args);
}
