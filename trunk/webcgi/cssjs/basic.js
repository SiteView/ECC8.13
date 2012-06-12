
function _Delclick(_content,btnNums,btnConfirm,upd )
{
	var reValue = DelAlert(_content,btnNums);
	if(reValue == btnConfirm)
		update(upd);
	else
		hiddenbar();
}

function GetClientMessage(_key)
{
	if(_key=="qdjqdhqx")
		return "确认删除吗？";  //IDS_AffirmDelete
	if(_key=="xxts")
		return "消息提示框";	//IDS_MessagePrompt
	if(_key=="qdqx")
		return "确定,取消";		//IDS_ConfirmCancel	
	if(_key=="qd")
		return "确定";			//IDS_Affirm
	if(_key=="gb")
		return "关闭";			//IDS_Close	
	if(_key=="xzlb")
		return "下载列表";		//IDS_DownloadList
}

function DelAlert(_content,_bNames)
{
	if(_bNames == "" || _bNames == undefined)
		return;
	var msg = new Object();
	msg._Title = "";
	msg._Content = _content;
	msg._BtnNum = _bNames;
	var feature = 'dialogWidth:360px;dialogHeight:200px;scroll:no;status:no;resizeable:no;help:no';
	var reValue = window.showModalDialog("/fcgi-bin/showhtm.cgi?confirm.htm",msg,feature);
	return reValue;
}

function AlertLogout(_content,btnNums,btnConfirm)
{
	//if(DelAlert("您确定要注销吗?",GetClientMessage('xxts'),GetClientMessage('qdqx'))==GetClientMessage('qd')) //IDS_LogoutAffirm
	if(DelAlert(_content,btnNums)==btnConfirm) //IDS_LogoutAffirm
	
	{
		return true;
	}
	else
		return false;
}

function OpenTest(url)
{
    window.showModalDialog(url);
}

function showTranslate(_filename)
{
	var urlParh = "/fcgi-bin/Translate.exe?filepath=";
		urlParh += _filename;

	var reValue = window.open(urlParh);
}

function showAlertMsg(_content, btnNums)
{
	var msg = new Object();
	msg._Title = "";
	msg._Content = _content;
	msg._BtnNum = btnNums;
	var feature = 'dialogWidth:360px;dialogHeight:200px;scroll:no;status:no;resizeable:no;help:no';
	window.showModalDialog("/setsucc.htm",msg,feature);
}

function showMonitorCountErr(content_,btnNums)
{
	var msg = new Object();
	msg._Title = "";
	msg._Content = content_; //IDS_PointPoor
	msg._BtnNum = btnNums;
	var feature = 'dialogWidth:360px;dialogHeight:200px;scroll:no;status:no;resizeable:no;help:no';
	window.showModalDialog("/fcgi-bin/showhtm.cgi?confirm.htm",msg,feature);
}


function refreshmonitors(url)
{
	var msg = new Object();
	msg._Title = "";  //IDS_Refresh_Monitor
	var feature = "dialogWidth:750px;dialogHeight:460px;scroll:no;status:no;resizeable:no;edge:raised";
	var reValue = window.showModalDialog(url,msg,feature);
}
function refreshmonitor(monitorid, objid, upd)
{
	document.getElementById(objid).value = monitorid;
	var url = "refresh.exe?monitorid=" + monitorid;
	var msg = new Object();
	msg._Title = ""; //IDS_Refresh_Monitor
	var feature = "dialogWidth:750px;dialogHeight:460px;scroll:no;status:no;resizeable:no;edge:raised";
	var reValue = window.showModalDialog(url,msg,feature);
	update(upd);
}

function currentoperate(svobjectid, objid, udp)
{
	document.getElementById(objid).value = svobjectid;
	if(update(udp)==0)
		showbar();
}

function showtestdevice(url)
{
	var msg = new Object();
	msg._Title = "";  //IDS_TestDevice
	var feature = "dialogWidth:750px;dialogHeight:460px;scroll:no;status:no;resizeable:no;edge:raised";
	var reValue = window.showModalDialog(url,msg,feature);
}

function DependTree(url, objID, udp)
{	var msg = new Object();
	var feature = "dialogWidth:750px;dialogHeight:460px;scroll:no;status:no;resizeable:no;edge:raised";
	var reValue = window.showModalDialog(url,msg,feature);
	if(reValue != 'IDCANCEL' && reValue != undefined)
	{
		document.getElementById(objID).value = reValue;
		update(udp);
	}
}

function showDisable(type, monitorid, objid, upd)
{
	document.getElementById(objid).value = monitorid;
	var url = "disable.exe?disabletype=" + type + "&disableid=" + monitorid;
	var msg = new Object();
	msg._Title = "";   //IDS_DisableEnableMonitor
	var feature = "dialogWidth:500px;dialogHeight:380px;scroll:no;status:no;resizeable:no;edge:raised";
	var reValue = window.showModalDialog(url,msg,feature);
	if(reValue == 'IDOK')
		update(upd);
}

function showDisableUrl(url,upd)
{
	var msg = new Object();
	msg._Title = "";   //IDS_DisableEnableMonitor
	var feature = "dialogWidth:500px;dialogHeight:380px;scroll:no;status:no;resizeable:no;edge:raised";
	var reValue = window.showModalDialog(url,msg,feature);
	if(reValue == 'IDOK')
		update(upd);
}

function  Synchronization(objID1, objID2)
{
	if(document.all(curDeviceID).value == "")
		document.getElementById(objID2).value=document.getElementById(objID1).value;
}

function  ChangePort(selvalue, objID2)
{
	if(selvalue == "Telnet")
		document.getElementById(objID2).value= "23";
	else
		document.getElementById(objID2).value= "22";	
}

function showbar()
{
	top.document.getElementById('frame_loadBra').style.display="";
}

function hiddenbar()
{
	top.document.getElementById('frame_loadBra').style.display="none";
}

function showsmswebsend(error,sending)
{
	if(document.all(pMailTo).value == "")
	{
		document.all(pStateTextArea).innerText = error;
		return;
	}
	document.all(pSendTest).disabled = true;
	document.all(pStateTextArea).innerText = sending;
}

function simpleReport(szurl)
{
	window.open(url);
}

function hidesubtable(iconshow, iconhide, subtable)
{
	document.getElementById(iconhide).style.display="";
	document.getElementById(iconshow).style.display="none";
	document.getElementById(subtable).style.display="none";
}

function showsubtable(iconshow, iconhide, subtable)
{
	document.getElementById(iconhide).style.display="none";
	document.getElementById(iconshow).style.display="";
	document.getElementById(subtable).style.display="";
}

function showDownload(_content)
{
	var msg = new Object();
	msg._Title = GetClientMessage('xzlb');
	msg._Content = _content;
	msg._BtnNum = GetClientMessage('gb');
	var feature = 'dialogWidth:360px;dialogHeight:200px;scroll:no;status:no;resizeable:no;help:no';
	window.showModalDialog("/fcgi-bin/showhtm.cgi?setdownload.htm",msg,feature);
}

function SelSubMenu(subMenu, subItem)
{
	document.all(mainSubMenu).value = subMenu;
	document.all(mainSubItem).value = subItem;
	update(mainMenuSelBtn);
}

function OpenGenReport(url) 
{
 var msg ;
 var feature = 'dialogWidth:360px;dialogHeight:360px;scroll:no;status:no;resizeable:no;help:no';
 window.showModalDialog(url, msg, feature);
}
