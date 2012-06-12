#include <iostream>
#include "D:\v70\webcgi\showsvgtuopu\ShowSvgTuopu.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CShowSvgTuopu::slots_[] = { WSlot_() };
WSignal_ CShowSvgTuopu::signals_[] = { WSignal_() };

void CShowSvgTuopu::buildSlotMap(WSlotMap& result)
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
void CShowSvgTuopu::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CShowSvgTuopu::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CShowSvgTuopu::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
