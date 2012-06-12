#include "preview.h"

#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WTextArea"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WCheckBox"

CSVPreview::CSVPreview(WContainerWidget *parent):
WTable(parent)
{
    int nRow = numRows();
    new WText("<SCRIPT language='JavaScript' src='/menu.js'></SCRIPT>", elementAt(nRow, 0));

    nRow++;
    m_pDeviceShow = new SVDevice(elementAt(nRow, 0),    NULL);
    if(m_pDeviceShow)
        m_pDeviceShow->hide();

    nRow ++;
    m_pMonitorShow = new SVMonitor(elementAt(nRow, 0),    NULL);
    if(m_pMonitorShow)
        m_pMonitorShow->hide();

    setStyleClass("t1");
}

void CSVPreview::refresh()
{
    string szDeviceIndex("_win");
    int nMTID = 5;
    int nSize =4095;
    int nPreviewType = 0;
    char szQuery[4096]={0};
    char szMsg[128] = {0};

    GetEnvironmentVariable( "QUERY_STRING", szQuery, nSize);
	//char * tmpquery;
	//tmpquery = getenv( "QUERY_STRING");
	//if(tmpquery)
	//	strcpy(szQuery,tmpquery);
    
    char *pType = strstr(szQuery, "type=");
    if(pType)
    {
        pType += strlen("type=");
        
        sscanf(pType, "%d", &nPreviewType);
    }

    sprintf(szMsg, "Preview type is : %d, type is %s", nPreviewType, pType);
    PrintDebugString(szMsg);
    PrintDebugString(szQuery);

    if(nPreviewType == 0)
    {
        pType = NULL;
        pType = strstr(szQuery, "preview=");
        if(pType)
        {
            char *pTemp = new char[strlen(pType)];
            if(pTemp)
            {
                memset(pTemp, 0, strlen(pTemp));
                pType += strlen("preview=");
                sscanf(pType, "%s", pTemp);
                szDeviceIndex = pTemp;
                delete []pTemp;
            }
        }

        if(m_pDeviceShow)
        {
            m_pDeviceShow->show();
            m_pDeviceShow->ClearData(szDeviceIndex,appSelf);
        }

        if(m_pMonitorShow)
            m_pMonitorShow->hide();
    }
    else
    {  
        if(m_pDeviceShow)
            m_pDeviceShow->hide();

        pType = NULL;
        pType = strstr(szQuery, "preview=");
        if(pType)
        {
            pType += strlen("preview=");
            sscanf(pType, "%d", &nMTID);
        }

        if(m_pMonitorShow)
        {
            m_pMonitorShow->show();
            m_pMonitorShow->showMonitorParam(nMTID, appSelf);
        }
    }
}
