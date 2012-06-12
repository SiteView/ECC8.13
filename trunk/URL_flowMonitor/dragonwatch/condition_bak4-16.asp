<!-- #include file="inc/check.asp" -->
<%
Dim startTime
' -------------清除过滤条件---------------
If Len(Request.QueryString("p")) Then
	Response.cookies("rep_trans")("id")=""
	Response.cookies("rep_trans")("name")=""
	Response.cookies("rep_city")("id")=""
	Response.cookies("rep_city")("name")=""
'	response.Cookies("rep_all_failure")("id") = ""
'	response.Cookies("rep_all_failure")("name") = ""
	response.Cookies("rep_sel_failure")("id") = ""
End If

'-----------------------------------------------
If Len(Request.cookies("rep_startTime"))>0 Then 
	startTime=Request.cookies("rep_startTime")
Else
	startTime=""
End If

'---------------修改Per,By的cookies---------------
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
		selBy = "c"
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

%>
<html>
<head>
<title>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</title>
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
    <td align="center" width="32">单位</td>
    <td width="75"> 
      <select name="selPer" <%If LCase(Request.QueryString("n"))="avgcalander.asp" Then Response.Write "disabled"%>>
        <option value="h">小时</option>
        <option value="d">天</option>
        <option value="w">星期</option>
        <option value="m">月</option>
        <option value="q">季度</option>
        <option value="y">年</option>
      </select>
    </td>
    <td align="center" width="130"><a href="#" onclick="openCalendar()"><img src="img/starton.gif" alt="点击此钮将弹出一个可选择日期时间的小窗口，方便您选择起始日期和时间" width="89" height="17" border="0"></a></td>
    <td align="center" width="128">
	<div id=datetime>
	<%
	If Len(startTime)>0 Then
		startTime=CDate(startTime)
		Response.Write year(startTime)&"年"&month(startTime)&"月"&day(startTime)&"日"&hour(startTime)&"时"
	Else
		response.write(year(now)&"年"&month(now)&"月"&day(now)&"日"&hour(now)&"时")
	End If
	%>
	</div></td>
    <td align="center" width="24"><a href="#" onclick="diffTime()"><img src="img/left.gif" alt="根据选定的时间单位退后一个单位" width="18" height="18" border="0"></a></td>
    <td align="center" width="24"><a href="#" onclick="addTime()"><img src="img/right.gif" alt="根据选定的时间单位前进一个单位" width="18" height="18" border="0"></a></td>
    <td align="center" width="64"><div id=divBy1>分组方式</div></td>
    <td width="94"> <div id=divBy2>
      <select name="selBy">
        <option value="t" >业务流程</option>
        <option value="c">城市</option>
        <option value="g">组</option>
      </select></div>
    </td>
    <td width="107"><INPUT TYPE="image" SRC="img/apply.gif" title="点击将按所选定的时间单位＋日期时间＋分组方式产生报告"></td>
    <td width="111"><a href="javascript:clearfilter()" style="cursor:hand;"><img src="img/reset.gif" width="89" alt="点击将清除所有过滤条件" height="17" border="0"></a></td>
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
if left(strAction,13) = "per_sum_d.asp" or Instr(Request.QueryString("n"),"error_analysis.as")<>0 Or Instr(Request.QueryString("oldaction"),"error_analysis.as")<>0 then
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
	var sHref="condition.asp?p=clear&oldaction="+document.frmCondition.action+"&selPer="+document.all.selPer.value+"&selBy="+document.all.selBy.value;
	if (window.parent.frames.length > 0) {
		window.parent.frames.conditionFrame.location = sHref; 
	}
}

function applyToCityTran(){
	document.frmCondition.action="main.asp?oldaction="+document.frmCondition.action+"&clearcitytran=yes&selby="+document.all.selBy.value+"&selPer="+document.all.selPer.value+"&starttime="+document.all.selDate.value;
	document.frmCondition.target="mainFrame";
//	alert(document.frmCondition.action);
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

	document.all.datetime.innerHTML=newday.getYear()+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+newday.getHours()+"时";

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
	document.all.datetime.innerHTML=newday.getYear()+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+document.all.selHour.value+"时";

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
	document.all.datetime.innerHTML=newday.getYear()+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+document.all.selHour.value+"时";

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
	document.all.datetime.innerHTML=newday.getYear()+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+document.all.selHour.value+"时";

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
	document.all.datetime.innerHTML=newday.getYear()+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+document.all.selHour.value+"时";

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
		document.all.datetime.innerHTML=document.all.selYear.value+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+document.all.selHour.value+"时";

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
	document.all.datetime.innerHTML=newday.getYear()+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+newday.getHours()+"时";

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
	document.all.datetime.innerHTML=newday.getYear()+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+document.all.selHour.value+"时";

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
	document.all.datetime.innerHTML=newday.getYear()+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+document.all.selHour.value+"时";

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
	document.all.datetime.innerHTML=newday.getYear()+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+document.all.selHour.value+"时";

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
	document.all.datetime.innerHTML=newday.getYear()+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+document.all.selHour.value+"时";

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
		document.all.datetime.innerHTML=document.all.selYear.value+"年"+(parseInt(newday.getMonth())+1)+"月"+newday.getDate()+"日"+document.all.selHour.value+"时";

		document.all.selDate.value=newday.getYear()+"-"+(parseInt(newday.getMonth())+1)+"-"+newday.getDate()+" "+document.all.selHour.value+":00";
}

//-->
</SCRIPT>

<%
If Len(Request.QueryString("p"))>0 Then
%>
<SCRIPT LANGUAGE="JavaScript">
//parent.reportFrame.document.location.reload();
document.frmCondition.submit();
</SCRIPT>
<%
End If
%>

                                                                                                                                                                                                                                                                                                                                                              
