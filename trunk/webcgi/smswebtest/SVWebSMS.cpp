// SVWebSMS.cpp: implementation of the CSVWebSMS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SVWebSMS.h"

#define MAX_BUFF_LEN 256
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSVWebSMS::CSVWebSMS()
{
    pSender = NULL;
}

CSVWebSMS::~CSVWebSMS()
{

}

int CSVWebSMS::Init()
{
    CoInitialize(NULL);//Initialize COM Library
    int nRet = 0;
	//  公钥文件的物理位置:
    char chPublicKeyPath[MAX_BUFF_LEN] = {0};
    //sprintf(chPublicKeyPath, "%s\\PublicKey\\pub.txt", FuncGetInstallRootPath());
	//  服务器端接收的ASP页面的URL
	_bstr_t bstrServerSiteURL("http://sms.bmcc.com.cn/GatewayAPI/SMSIIGateWay.asp");
	//
	HRESULT hr = S_OK;

	hr = pSender.CreateInstance("SMSend.UMSmSend");
	if( SUCCEEDED(hr) && (NULL != pSender) )
	{
		///////////////////////////////////////////////////////////
		//
		// 设置组件接口所需要的参数
		//
		//  第一个:公钥文件的物理位置     
		pSender->SetPkpath(chPublicKeyPath);
		//
		//  第二个:服务器端接收的ASP页面的URL
		pSender->SetServerSite(bstrServerSiteURL);
    }
    else
    {
        return 1;
    }
    return nRet;
}

BOOL CSVWebSMS::SendSMS(CString strSMS, CString strPhone)
{
    BOOL bRet = TRUE;
    char chSMSXML[1024] = {0};
    sprintf(chSMSXML, "<?xml version=\"1.0\"?><message><EntCode>62016161</EntCode>" \
    "<EntUserID>%s</EntUserID><password>%s</password><Content>%s</Content>" \
    "<DestMobileNumber>%s</DestMobileNumber><URGENT_Flag>1</URGENT_Flag>" \
    "<ScheduledTime></ScheduledTime><Batch_SendID></Batch_SendID><DataType>15" \
    "</DataType><SrcNumber></SrcNumber></message>", strUser, strPwd, strSMS, 
    strPhone);

    try
    {
	    ///////////////////////////////////////////////////////////
	    //
	    // 实际发送短消息XML给服务器
	    //
	    // 第一个参数257代表采用RSA加密算法
	    // 第二个参数就是短消息XML
        pSender->LoadSendXML("257", chSMSXML);
	    ///////////////////////////////////////////////////////////
	    //
	    // 发送短消息XML之后，可以通过以下两个方法得到服务器方的反馈
	    //  1:GetResponseText(通过这个方法可以取到服务器端返回的responseText)
	    //  2:GetHTTPPostStatus(通过这个方法可以取到服务器端返回的状态值,即200、404、500之类的值)   
	    _bstr_t bstrServerResponseText = pSender->GetResponseText();
        int nCode = GetResponseCode(bstrServerResponseText);
        if(nCode != 0 )
        {
            return -1;
        }
    }
    catch(...)
    {
        printf("Unkown Error");
        return -1;
    }
    return 0;
}

BSTR CSVWebSMS::UTF2GB(LPCSTR lp, int nLen)
{
   BSTR str = NULL;
   int nConvertedLen = MultiByteToWideChar(CP_UTF8, 0, lp,
     nLen, NULL, NULL);
 
   // BUG FIX #1 (from Q241857): only subtract 1 from 
   // the length if the source data is nul-terminated
   if (nLen == -1)
      nConvertedLen--;
 
   str = ::SysAllocStringLen(NULL, nConvertedLen);
   if (str != NULL)
   {
     MultiByteToWideChar(CP_UTF8, 0, lp, nLen, str, nConvertedLen);
   }
   return str;
}

const char* CSVWebSMS::GetErrMsg(int nErrCode)
{
    switch(nErrCode)
    {
    case 1:
        return "Create SMS COM object failed";
        break;
    case 10:
        return "Com library error";
        break;
    case -1:
        return "Create DOM document failed";
        break;
    case -2:
        return "Load config file failed";
        break;
    case -3:
        return "Get single node failed";
        break;
    case -4:
        return "Get attribute map failed";
        break;
    case -41:
        return "Get user name failed";
        break;
    case -410:
        return "Get user name value failed";
        break;
    case -42:
        return "Get  password failed";
        break;
    case -420:
        return "Get password value failed";
        break;
    }
    return "Unknow error";
}

int CSVWebSMS::GetResponseCode(_bstr_t bstrResponse)
{
    char chResponse[1024], chTmp[1024] ;
    sprintf(chResponse, "%s", (char*)bstrResponse);

    strlwr(chResponse);
    char *chTemp = strstr(chResponse, "<errornumber>");
    if(chTemp)
    {
        sprintf(chTmp, "%s", chTemp + strlen("<errornumber>"));
        chTemp = strstr(chTmp, "</errornumber>");
        if(chTemp)
        {
            int nCode = strlen(chTmp) - strlen(chTemp);
            memset(chResponse, 0, strlen(chResponse));
            strncpy(chResponse, chTmp, nCode);
            chResponse[nCode] = '\0';
            return atoi(chResponse);
        }
        else
        {
            return -2;
        }
    }
    else
    {
        return -1;
    }
}
