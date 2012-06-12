//#pragma once
#ifndef		DRAGONFLOW_ENTITYITEM
#define		DRAGONFLOW_ENTITYITEM

#include "MonitorCall.h"

class EntityItem
{
public:
	EntityItem(void);
	~EntityItem(void);

	String strName;
	String strValue;

};

typedef std::list<EntityItem *>  CEntityItemList;


#endif
