#include <iostream>
#include "BackupRestore.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CBackupRestore::slots_[] = { WSlot_("Backup()", false), WSlot_("BackupData()", false), WSlot_("Restore()", false), WSlot_("ShowHideHelp()", false), WSlot_("trueRestore()", false), WSlot_() };
WSignal_ CBackupRestore::signals_[] = { WSignal_() };

void CBackupRestore::buildSlotMap(WSlotMap& result)
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
void CBackupRestore::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CBackupRestore::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    Backup();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    BackupData();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    Restore();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    ShowHideHelp();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    trueRestore();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CBackupRestore::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
