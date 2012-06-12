// 当分级时要调用 tran_perfor_failreason_group.asp (有时间范围　大于几点小于几点)
// 具体到几时几分时调用　tran_perfor_failreason.asp　（没有时间范围，直接指定具体时间）
function failreason(tranid,cityid,dt,dt2)
{
	window.open("tran_perfor_failreason_group.asp?cityid="+cityid+"&tranid="+tranid+"&dt="+dt+"&dt2="+dt2,"",'toolbar=FALSE,resizable=1,scrollbars=2,height=260,width=700,screenx=550,screeny=300');
}

var iFrame;
var Tranobj;
var Locobj;
var currTab;
var tbTranImage;
var tbLocImage;

var sImgsPath = 'IMG/';
function InitActiveFilters()
{
	iFrame  = window.frames.iframe_Filters;
	Tranobj = iFrame.document.all.TranFilters;
	Locobj  = iFrame.document.all.LocFilters;
	Tabsobj = getLayer('Tabs');

	showLayer(Tranobj)
	hideLayer(Locobj)
	currTab = 'TranFilters'

	tbTranImage = document.all("TranImage");
	tbLocImage = document.all("LocImage");
}

function switchTab(chosen)
{
	switch (chosen)
	{
		case 'Transactions':
			showLayer(Tranobj);
			hideLayer(Locobj);
			tbTranImage.src = sImgsPath + "tb_trans1.gif"
			tbLocImage.src = sImgsPath + "tb_locat2.gif"
			currTab='TranFilters';
			break;
		case 'Locations':
			hideLayer(Tranobj);
			showLayer(Locobj);
			tbTranImage.src = sImgsPath + "tb_trans2.gif"
			tbLocImage.src = sImgsPath + "tb_locat1.gif"
			currTab='LocFilters';
			break;
		default:
			showLayer(Tranobj);
			hideLayer(Locobj);
			currTab='TranFilters';
	}
	return false;		
}

function setFilters(set)
{
	var chkboxTran = iFrame.document.frmFilters.chkTranFilter;
	var chkboxLoc = iFrame.document.frmFilters.chkLocFilter;
	var TranEmpty = true;
	var LocEmpty  = true;

	if (chkboxTran[0])
	{
		for (i=0;i<chkboxTran.length ;i++ )
		{
			if (chkboxTran(i).checked)
			{
				TranEmpty = false;
			}
		}
	}else{
		if (chkboxTran.checked) TranEmpty = false;
	}

	for (i=0;i<chkboxLoc.length ;i++ )
	{
		if (chkboxLoc(i).checked)
		{
			LocEmpty = false;
		}
	}

	if (set)
	{
		if (TranEmpty)
		{
			alert("请至少选择一个错误码.")
			return false;
		}
		if (LocEmpty)
		{
			alert("请至少选择一个城市.")
			return false;
		}
		iFrame.document.frmFilters.userSubmit.value = "yes";
	}
//	iFrame.document.frmFilters.action="";
	iFrame.document.frmFilters.submit();
	return true;
}


// this function is for selectAll/None/Invert
function selectAction(action)
{
	var chkboxControl;
	//currTab- global variable indicating the current tab
	switch (currTab)
	{
		case 'TranFilters':
			chkboxControl = iFrame.document.frmFilters.chkTranFilter;
			break;
		case 'LocFilters':
			chkboxControl = iFrame.document.frmFilters.chkLocFilter;
			break;
	}	
	switch (action)
	{
		case 'All':
			selectAll(chkboxControl,true);		
			break;
		case 'None':
			selectAll(chkboxControl,false);
			break;
		case 'Invert':
			selectAll(chkboxControl,null);
	}	
}

function selectAll(chkboxControl,bAll)
{
var currControl;
	if (chkboxControl[0])
	{
		for (i=0;i<chkboxControl.length;i++)
		{
			currControl = chkboxControl[i];
			if (bAll==null)
			{
				currControl.checked = !currControl.checked
			}
			else
			{
				currControl.checked = bAll;
			}
		}
	}else{
			currControl = chkboxControl;
			if (bAll==null)
			{
				currControl.checked = !currControl.checked
			}
			else
			{
				currControl.checked = bAll;
			}
		
	}
}

function nop()
{
	return false;
}

function closeWin(win){
	if (typeof(win)=='object')
	{
		win.close();
	}
}
/*
basic functions:
*/
function getLayer(name) {
    return eval('document.all.' + name);
}

function hideLayer(layer) {
    layer.style.visibility = "hidden";
}

function showLayer(layer) {
    layer.style.visibility = "visible";
}

function inheritLayer(layer) {
    layer.style.visibility = "inherit";
}

function setBgImage(layer, src) {
    layer.style.backgroundImage = "url(" + src + ")";
}

