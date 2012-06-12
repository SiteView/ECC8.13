; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTimeoutSocket
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SMST39VS.h"
LastPage=0

ClassCount=2

ResourceCount=0
Class1=CSMSServerConnection
Class2=CTimeoutSocket

[CLS:CSMSServerConnection]
Type=0
HeaderFile=SMSServerConnection.h
ImplementationFile=SMSServerConnection.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q

[CLS:CTimeoutSocket]
Type=0
HeaderFile=TimeoutSocket.h
ImplementationFile=TimeoutSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq

