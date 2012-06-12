#include <iostream>
#include "addgroup.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVAddGroup::slots_[] = { WSlot_("backPreview()", false), WSlot_("saveGroup()", false), WSlot_("showHelp()", false), WSlot_("Translate()", false), WSlot_() };
WSignal_ SVAddGroup::signals_[] = { WSignal_("editGroupName(string,string)", false), WSignal_("addGroupName(string,string)", false), WSignal_("backMain()", false), WSignal_() };

void SVAddGroup::buildSlotMap(WSlotMap& result)
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
void SVAddGroup::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void SVAddGroup::editGroupName(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 0, args);
}

void SVAddGroup::addGroupName(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 1, args);
}

void SVAddGroup::backMain()
{
  void **args = 0;
  triggerSignal(signals_ + 2, args);
}

bool SVAddGroup::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    backPreview();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    saveGroup();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    showHelp();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    Translate();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVAddGroup::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
