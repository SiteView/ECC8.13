<%
Dim startTime
' -------------�����������---------------
If Len(Request.QueryString("p")) Then
	Response.cookies("rep_trans")("id")=""
	Response.cookies("rep_trans")("name")=""
	Response.cookies("rep_city")("id")=""
	Response.cookies("rep_city")("name")=""

	response.Cookies("rep_sel_failure")("id") = ""
End If

'-----------------------------------------------
If Len(Request.cookies("rep_startTime"))>0 Then 
	startTime=Request.cookies("rep_startTime")
Else
	startTime=""
End If

'---------------�޸�Per,By��cookies---------------
if Len(Trim(Request.QueryString("selPer"))) > 0 then
	selPer = Trim(Request.QueryString("selPer"))
else
	if Len(Trim(Request.cookies("rep_per"))) > 0  then
		selPer = Trim(Request.cookies("rep_per"))
	else
		selPer = "d"
	end if
end if

if Len(Request.QueryString("selBy")) > 0 then
	if Request.QueryString("selBy") = "g" then
'		selBy = "c"
		selBy = "g"
	else
		selBy = Request.QueryString("selBy")
	end if
else
	if Len(Request.cookies("rep_by")) > 0  then
		selBy = Request.cookies("rep_by")
	else
		selBy = "t"
	end if
end if
response.cookies("rep_per") = selPer
response.cookies("rep_by")  = selBy
'response.write selBy

If Len(Request.Cookies("rep_sel_tran")) * Len(Request.Cookies("rep_sel_city")) = 0 then '������һΪ��
	response.Cookies("rep_sel_tran") = request.Cookies("rep_all_tran")
	response.Cookies("rep_sel_city") = request.Cookies("rep_all_city")
End If
'-------------------------------------------------------------------------------
'***********************************************
'* ע�⣺ �벻Ҫ�Ķ������ Include �ļ�������λ�� *
'***********************************************
%>
<!--#Include file="inc/TranCityArray.asp"-->
<%
If Len(Request.Cookies("rep_sel_tran")) * Len(Request.Cookies("rep_sel_city")) > 0 then
	For i=0 to UBound(arrSelTran)
		strTranCooky = strTranCooky & arrSelTran(i,0) & ","
	Next
	strTranCooky = Left(strTranCooky,Len(strTranCooky)-1)
	Response.Cookies("rep_sel_transid") = strTranCooky

	For i=0 to UBound(arrSelCity)
		strCityCooky = strCityCooky & arrSelCity(i,0) & ","
	Next
	strCityCooky = Left(strCityCooky,Len(strCityCooky)-1)
	Response.Cookies("rep_sel_citysid") = strCityCooky
End If
%>
<html>
<head>
<title>��������ⱨ�� www.speed.net.cn �й�����������ר��</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">

</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<%
If Len(Request.QueryString("n"))=0 Then
	If Len(Request.QueryString("oldaction"))>0 Then
		strAction=Request.QueryString("oldaction")
	Else
		strAction="rep_avg_d.asp"
	End If
Else
	strAction=Trim(Request.QueryString("n"))
End If
%>
<FORM METHOD=POST ACTION="<%=strAction%>" name="frmCondition" target="reportFrame" onSubmit="javascript:return applyToCityTran()">
<input type=hidden name=hostid value="<%=request.querystring("hostid")%>">
<input type=hidden name=hostname value="<%=request.querystring("hostname")%>">
<input type=hidden name=cityid value="<%=request.querystring("cityid")%>">
<input type=hidden name=cityname value="<%=request.querystring("cityname")%>">

<%If Len(startTime)>0 Then%>
	<%response.write "<INPUT TYPE=hidden name=selDate value='"&Year(startTime)&"-"&Month(startTime)&"-"&Day(startTime)&" "&Hour(startTime)&":"&Minute(startTime)&"'>"%>

	<%response.write "<input type=hidden name=selYear value="&Year(startTime)&">"%>
	<%response.write "<input type=hidden name=selMonth value="&Month(startTime)&">"%>
	<%response.write "<input type=hidden name=selDay value="&Day(startTime)&">"%>
	<%response.write "<input type=hidden name=selHour value="&Hour(startTime)&">"%>
<%Else%>
	<%response.write "<INPUT TYPE=hidden name=selDate value='"&Year(Now)&"-"&Month(Now)&"-"&Day(Now)&" "&Hour(Now)&":"&Minute(now)&"'>"%>

	<%response.write "<input type=hidden name=selYear value="&Year(Now)&">"%>
	<%response.write "<input type=hidden name=selMonth value="&Month(Now)&">"%>
	<%response.write "<input type=hidden name=selDay value="&Day(Now)&">"%>
	<%response.write "<input type=hidden name=selHour value="&Hour(Now)&">"%>
<%End If%>

<table width="811" border="0" cellspacing="2" cellpadding="0">
  <tr>
    <td align="center" width="32">��λ</td>
    <td width="75"> 
      <select name="selPer" <%If LCase(Request.QueryString("n"))="avgcalander.asp" Then Response.Write "disabled"%>>
        <option value="h">Сʱ</option>
        <option value="d">��</option>
        <option value="w">����</option>
        <option value="m">��</option>
        <option value="q">����</option>
        <option value="y">��</option>
      </select>
    </td>
    <td align="center" width="130"><a href="#" onclick="openCalendar()"><img src="img/starton.gif" alt="�����ť������һ����ѡ������ʱ���С���ڣ�������ѡ����ʼ���ں�ʱ��" width="89" height="17" border="0"></a></td>
    <td align="center" width="128">
	<div id=datetime>
	<%
	If Len(startTime)>0 Then
		startTime=CDate(startTime)
		Response.Write year(startTime)&"��"&month(startTime)&"��"&day(startTime)&"��"&hour(startTime)&"ʱ"
	Else
		response.write(year(now)&"��"&month(now)&"��"&day(now)&"��"&hour(now)&"ʱ")
	End If
	%>
	</div></td>
    <td align="center" width="24"><a href="#" onclick="diffTime()"><img src="img/left.gif" alt="����ѡ����ʱ�䵥λ�˺�һ����λ" width="18" height="18" border="0"></a></td>
    <td align="center" width="24"><a href="#" onclick="addTime()"><img src="img/right.gif" alt="����ѡ����ʱ�䵥λǰ��һ����λ" width="18" height="18" border="0"></a></td>
    <td align="center" width="64"><div id=divBy1>���鷽ʽ</div></td>
    <td width="94"> <div id=divBy2>
      <select name="selBy">
        <option value="t" >ҵ������</option>
        <option value="c">����</option>
		<%
		If Instr(Request.QueryString("n"),"error_analysis.asp")<>0  Then
			Response.write "<option value='g'>������</option>"
		Else
			Response.write "<option value='g'>��</option>"
		End if
		%>
      </select></div>
    </td>
    <td width="107"><INPUT TYPE="image" SRC="img/apply.gif" title="���������ѡ����ʱ�䵥λ������ʱ�䣫���鷽ʽ��������"></td>
    <td width="111"><a href="javascript:clearfilter()" style="cursor:hand;"><img src="img/reset.gif" width="89" alt="�����������й�������" height="17" border="0"></a></td>
  </tr>
</table>
</FORM>
</body>

</html>

<script language=javascript>
function showhideBy(b){
	if (b){
		document.all.divBy1.style.visibility="visible";
		document.all.divBy2.style.visibility="visible";
	}else{
		document.all.divBy1.style.visibility="hidden";
		document.all.divBy2.style.visibility="hidden";
	}
}
</script>

<%
'if left(strAction,13) = "per_sum_d.asp" or Instr(Request.QueryString("n"),"error_analysis.as")<>0 Or Instr(Request.QueryString("oldaction"),"error_analysis.as")<>0 then
if left(strAction,13) = "per_sum_d.asp" then
	response.write "<script language=javascript>"
		response.write "showhideBy(0)"
	response.write "</script>"
end if

If Len(selPer)>0 Then
%>
<SCRIPT LANGUAGE="JavaScript">
document.frmCondition.selPer.value="<%=Request.cookies("rep_Per")%>";
</SCRIPT>
<%
End If
%>
<%
If Len(selBy)>0 Then
%>
<SCRIPT LANGUAGE="JavaScript">
document.frmCondition.selBy.value="<%=Request.cookies("rep_by")%>";
</SCRIPT>
<%
End If
%>

<SCRIPT LANGUAGE="JavaScript">
<!--
function clearfilter(){
//	document.frmCondition.action="condition.asp?p=clear&oldaction="+document.frmCondition.action+"&selPer="+document.all.selPer.value+"&selBy="+document.all.selBy.value;
//	document.frmCondition.target="_self";
//	document.frmCondition.submit();
	var sHref="condition.asp?p=clear&oldaction="+document.frmCondition.action+"&selPer="+document.all.selPer.value+"&selBy="+document.all.selBy.value+"&hostid="+document.all.hostid.value+"&hostname="+document.all.hostname.value+"&cityid="+document.all.cityid.value+"&cityname="+document.all.cityname.value;
	if (window.parent.frames.length > 0) {
		window.parent.frames.conditionFrame.location = sHref; 
	}
}

function applyToCityTran(){
	document.frmCondition.action="main.asp?oldaction="+document.frmCondition.action+"&clearcitytran=yes&selby="+document.all.selBy.value+"&selPer="+document.all.selPer.value+"&starttime="+document.all.selDate.value+"&hostid="+document.all.hostid.value+"&hostname="+document.all.hostname.value+"&cityid="+document.all.cityid.value+"&cityname="+document.all.cityname.value;
	document.frmCondition.target="mainFrame";
	//alert(document.frmCondition.action);
//	return false;
	document.frmCondition.submit();
	return false;
}

function openCalendar()
{
	window.open("calender.htm","calender","height=300,width=220,scrollbars=no,toolbar=no,title=no")
}

function doSubmit()
{
	frmCondition.submit();
}

function diffTime()
{
	switch(document.all.selPer.value)
	{
		case "h":
			diffHour();
			break;
		case "d":
			diffDay();
			break;
		case "w":
			diffWeek();
			break;
		case "m":
			diffMonth();
			break;
		case "q":
			diffQuarter();
			break;
		case "y":
			diffYear();
			break;
	}
}

function addTime()
{
	switch(document.all.selPer.value)
	{
		case "h":
			addHour();
			break;
		case "d":
			addDay();
			break;
		case "w":
			addWeek();
			break;
		case "m":
			addMonth();
			break;
		case "q":
			addQuarter();
			break;
		case "y":
			addYear();
			break;
	}
}

function diffHour()
{
	var newday=new Date(document.all.selYear.value,parseInt(document.all.selMonth.value)-1,document.all.selDay.value,(parseInt(document.all.selHour.value)-1),0,0);
	document.all.selDay.value=newday.getDate();
	document.all.selMonth.value=newday.getMonth()+1;
	document.all.selYear.value=newday.getYear();
	document.all.selHour.value=newday.getHours();
		
	if(document.all.selYear.value<1000)
	{
		document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
	}

	document.all.datetime.innerHTML=newday.getYear()+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+newday.getHours()+"ʱ";

	document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+newday.getHours()+":00";
}

function diffDay()
{
	var newday=new Date(document.all.selYear.value,parseInt(document.all.selMonth.value)-1,parseInt(document.all.selDay.value)-1);
	document.all.selDay.value=newday.getDate();
	document.all.selMonth.value=newday.getMonth()+1;
	document.all.selYear.value=newday.getYear();

	if(document.all.selYear.value<1000)
	{
		document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
	}
	document.all.datetime.innerHTML=newday.getYear()+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+document.all.selHour.value+"ʱ";

	document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+document.all.selHour.value+":00";

}

function diffWeek()
{
	var newday=new Date(document.all.selYear.value,parseInt(document.all.selMonth.value)-1,parseInt(document.all.selDay.value-7));
	document.all.selDay.value=newday.getDate();
	document.all.selMonth.value=newday.getMonth()+1;
	document.all.selYear.value=newday.getYear();

	if(document.all.selYear.value<1000)
	{
		document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
	}
	document.all.datetime.innerHTML=newday.getYear()+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+document.all.selHour.value+"ʱ";

	document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+document.all.selHour.value+":00";
}

function diffMonth()
{
	var newday=new Date(document.all.selYear.value,parseInt(document.all.selMonth.value-1)-1,document.all.selDay.value);
	document.all.selDay.value=newday.getDate();
	document.all.selYear.value=newday.getYear();
	document.all.selMonth.value=newday.getMonth()+1;

	if(document.all.selYear.value<1000)
	{
		document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
	}
	document.all.datetime.innerHTML=newday.getYear()+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+document.all.selHour.value+"ʱ";

	document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+document.all.selHour.value+":00";
}

function diffQuarter()
{
	var newday=new Date(document.all.selYear.value,parseInt(document.all.selMonth.value-4),document.all.selDay.value);
	document.all.selDay.value=newday.getDate();
	document.all.selYear.value=newday.getYear();
	document.all.selMonth.value=newday.getMonth()+1;

	if(document.all.selYear.value<1000)
	{
		document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
	}
	document.all.datetime.innerHTML=newday.getYear()+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+document.all.selHour.value+"ʱ";

	document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+document.all.selHour.value+":00";
}

function diffYear()
{
		var newday=new Date(parseInt(document.all.selYear.value)-1,parseInt(document.all.selMonth.value)-1,document.all.selDay.value);
		document.all.selDay.value=newday.getDate();
		document.all.selYear.value=newday.getYear();

		if(document.all.selYear.value<1000)
		{
			document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
		}
		document.all.datetime.innerHTML=document.all.selYear.value+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+document.all.selHour.value+"ʱ";

		document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+document.all.selHour.value+":00";
}

function addHour()
{
	var newday=new Date(document.all.selYear.value,parseInt(document.all.selMonth.value)-1,document.all.selDay.value,parseInt(document.all.selHour.value)+1,0,0);
	document.all.selDay.value=newday.getDate();
	document.all.selMonth.value=newday.getMonth()+1;
	document.all.selYear.value=newday.getYear();
	document.all.selHour.value=newday.getHours();

	if(document.all.selYear.value<1000)
	{
		document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
	}
	document.all.datetime.innerHTML=newday.getYear()+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+newday.getHours()+"ʱ";

	document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+newday.getHours()+":00";
}

function addDay()
{
	var newday=new Date(document.all.selYear.value,parseInt(document.all.selMonth.value)-1,parseInt(document.all.selDay.value)+1);
	document.all.selDay.value=newday.getDate();
	document.all.selMonth.value=newday.getMonth()+1;
	document.all.selYear.value=newday.getYear();

	if(document.all.selYear.value<1000)
	{
		document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
	}
	document.all.datetime.innerHTML=newday.getYear()+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+document.all.selHour.value+"ʱ";

	document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+document.all.selHour.value+":00";
}

function addWeek()
{
	var newday=new Date(document.all.selYear.value,parseInt(document.all.selMonth.value)-1,parseInt(document.all.selDay.value)+7);
	document.all.selDay.value=newday.getDate();
	document.all.selMonth.value=newday.getMonth()+1;
	document.all.selYear.value=newday.getYear();

	if(document.all.selYear.value<1000)
	{
		document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
	}
	document.all.datetime.innerHTML=newday.getYear()+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+document.all.selHour.value+"ʱ";

	document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+document.all.selHour.value+":00";

}

function addMonth()
{
	var newday=new Date(document.all.selYear.value,parseInt(document.all.selMonth.value),document.all.selDay.value);
	document.all.selDay.value=newday.getDate();
	document.all.selMonth.value=newday.getMonth()+1;
	document.all.selYear.value=newday.getYear();

	if(document.all.selYear.value<1000)
	{
		document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
	}
	document.all.datetime.innerHTML=newday.getYear()+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+document.all.selHour.value+"ʱ";

	document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+document.all.selHour.value+":00";
}

function addQuarter()
{
	var newday=new Date(document.all.selYear.value,parseInt(document.all.selMonth.value)+2,document.all.selDay.value);
	document.all.selDay.value=newday.getDate();
	document.all.selMonth.value=newday.getMonth()+1;
	document.all.selYear.value=newday.getYear();

	if(document.all.selYear.value<1000)
	{
		document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
	}
	document.all.datetime.innerHTML=newday.getYear()+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+document.all.selHour.value+"ʱ";

	document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+document.all.selHour.value+":00";
}

function addYear()
{
		var newday=new Date(parseInt(document.all.selYear.value)+1,parseInt(document.all.selMonth.value)-1,document.all.selDay.value);
		document.all.selDay.value=newday.getDate();
		document.all.selMonth.value=newday.getMonth()+1;
		document.all.selYear.value=newday.getYear();

		if(document.all.selYear.value<1000)
		{
			document.all.selYear.value=parseInt(document.all.selYear.value)+1900;
		}
		document.all.datetime.innerHTML=document.all.selYear.value+"��"+(parseInt(newday.getMonth())+1)+"��"+newday.getDate()+"��"+document.all.selHour.value+"ʱ";

		document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+document.all.selHour.value+":00";
}

//-->
</SCRIPT>

<%
If Len(Request.QueryString("p"))>0 Then
%>
<SCRIPT LANGUAGE="JavaScript">
//parent.reportFrame.document.location.reload();
//document.frmCondition.submit();
applyToCityTran();
</SCRIPT>
<%
End If

' �����WEBTRACE��ҳ������ʾ���鷽ʽ
If Instr(LCase(Request.QueryString("n")), "webtrace")>0 Then
%>
<SCRIPT LANGUAGE="JavaScript">
divBy1.style.display="none";
divBy2.style.display="none";
</SCRIPT>
<%
End If
%>
