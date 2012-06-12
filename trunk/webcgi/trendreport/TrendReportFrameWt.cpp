#include <iostream>
#include "TrendReportFrame.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ TrendReportFrame::slots_[] = { WSlot_("TrendReportQuery()", false), WSlot_("ReportQueryResponse()", false), WSlot_("Query2HourText()", false), WSlot_("Query4HourText()", false), WSlot_("Query8HourText()", false), WSlot_("Query1DayText()", false), WSlot_("Query3DayText()", false), WSlot_("Query5DayText()", false), WSlot_("Query1WeekText()", false), WSlot_("QueryCurWeekText()", false), WSlot_("Query1MonthText()", false), WSlot_("Query3MonthText()", false), WSlot_("Query6MonthText()", false), WSlot_("QueryCurDayText()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_() };
WSignal_ TrendReportFrame::signals_[] = { WSignal_() };

void TrendReportFrame::buildSlotMap(WSlotMap& result)
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
void TrendReportFrame::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool TrendReportFrame::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    TrendReportQuery();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    ReportQueryResponse();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    Query2HourText();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    Query4HourText();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    Query8HourText();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    Query1DayText();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    Query3DayText();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    Query5DayText();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    Query1WeekText();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    QueryCurWeekText();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    Query1MonthText();
    return true;
  }
  if (slot == slots_ + 11) {
    sender_ = sender;    Query3MonthText();
    return true;
  }
  if (slot == slots_ + 12) {
    sender_ = sender;    Query6MonthText();
    return true;
  }
  if (slot == slots_ + 13) {
    sender_ = sender;    QueryCurDayText();
    return true;
  }
  if (slot == slots_ + 14) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 15) {
    sender_ = sender;    ExChange();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool TrendReportFrame::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
