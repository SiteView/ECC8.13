


#include "appendmassrecord.h"
#include "MonitorSchedule.h"
#include <svdbapi.h>
#include <svdbtype.h>



extern Util *putil;

CAppendMassRecord::CAppendMassRecord()
{
}

CAppendMassRecord::~CAppendMassRecord()
{
	std::list<SingelRecord> listrcd;
	putil->AppendThenClearAllRecords(listrcd);
}

void CAppendMassRecord::run()
{
	while(true)
	{
		std::list<SingelRecord> listrcd;
		int count(0);
		if( (count=putil->AppendThenClearAllRecords(listrcd))>0 )
			cout<<"AppendMass "<<count<<" records done,"<<" slept "<<Univ::msappend<<" ms."<<endl;
		else if(count<0)
			cout<<"AppendMassRecord failed!"<<endl;
		ThreadEx::sleep(Univ::msappend);	
	}
}