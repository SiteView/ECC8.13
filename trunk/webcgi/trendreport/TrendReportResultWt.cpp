#include <iostream>
#include "TrendReportResult.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CTrendReportResult::slots_[] = { WSlot_("DataBack()", false), WSlot_("DataForward()", false), WSlot_("DataReturn()", false), WSlot_("NormalBtn()", false), WSlot_("ErrorBtn()", false), WSlot_("WarnningBtn()", false), WSlot_("SaveExcelBtn()", false), WSlot_() };
WSignal_ CTrendReportResult::signals_[] = { WSignal_() };

void CTrendReportResult::buildSlotMap(WSlotMap& result)
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
void CTrendReportResult::buildSignalMap(WSignalMap& result)
{
	WTable::buildSignalMap(result);
	for (int i = 0; signals_[i].good(); ++i)
		result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CTrendReportResult::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
	if (slot == slots_ + 0) {
		sender_ = sender;    DataBack();
		return true;
	}
	if (slot == slots_ + 1) {
		sender_ = sender;    DataForward();
		return true;
	}
	if (slot == slots_ + 2) {
		sender_ = sender;    DataReturn();
		return true;
	}
	if (slot == slots_ + 3) {
		sender_ = sender;    NormalBtn();
		return true;
	}
	if (slot == slots_ + 4) {
		sender_ = sender;    ErrorBtn();
		return true;
	}
	if (slot == slots_ + 5) {
		sender_ = sender;    WarnningBtn();
		return true;
	}
	if (slot == slots_ + 6) {
		sender_ = sender;    SaveExcelBtn();
		return true;
	}
	return WTable::triggerSlot(sender, slot, args);
}
bool CTrendReportResult::undoTriggerSlot(const WSlot_ *slot, void **args)
{
	return WTable::undoTriggerSlot(slot, args);
}
