#include <iostream>
#include "addsvse.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVAddSE::slots_[] = { WSlot_("backPreview()", false), WSlot_("saveSVSE()", false), WSlot_("showHelp()", false), WSlot_() };
WSignal_ SVAddSE::signals_[] = { WSignal_("EditSVSESucc(string,string)", false), WSignal_("AddSVSESucc(string,string)", false), WSignal_("backSVSEView()", false), WSignal_() };

void SVAddSE::buildSlotMap(WSlotMap& result)
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
void SVAddSE::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void SVAddSE::EditSVSESucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 0, args);
}

void SVAddSE::AddSVSESucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 1, args);
}

void SVAddSE::backSVSEView()
{
  void **args = 0;
  triggerSignal(signals_ + 2, args);
}

bool SVAddSE::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    backPreview();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    saveSVSE();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    showHelp();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVAddSE::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
