<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
Dim hostid, hostnmae, cityid, cityname
hostid=Request.QueryString("tranid")
hostname=Request.QueryString("tranname")
cityid=Request.QueryString("cityid")
cityname=Request.QueryString("cityname")
%>
<html>
<head>
<title>����·��׷�ٷ���</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
<style type="text/css">
<!--
.webtrace {  font-size: 14.8px; font-weight: bold}
-->
</style>
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td colspan="2" height="22"><font color="#003399"><span class="webtrace"><font color="#000066">
      </font></span></font><font color="#000066"><span class="webtrace">����·��׷�ٷ�����<font color="#6E6E6E" size=2>
	  ��<%=cityname%>��<%=hostname%>��������
	  </font> </span></font></td>
  </tr>
  <tr> 
    <td colspan="2"> 
      <hr size=1>
    </td>
  </tr>
  <tr> 
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="97%" bgcolor="#CCCCCC"> 
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="28%" height="22"><b>����·��׷�ٷ���</b></td>
          <td align="right" width="72%" height="22"><b>ʱ��:
            <%
	  If DateDiff("d", DateValue(startDate), DateValue(endDate))=0 Then
			Response.Write Year(startDate) & "��" & Month(startDate) & "��" & Day(startDate) & "��" & Hour(startDate) & "ʱ" & Minute(startDate) & "�� - " & Hour(endDate) & "ʱ" & Minute(endDate) & "��"
	  Else
			Response.Write Year(startDate) & "��" & Month(startDate) & "��" & Day(startDate) & "��" & Hour(startDate) & "ʱ" & Minute(startDate) & "�� - " & Year(endDate) & "��" & Month(endDate) & "��" & Day(endDate) & "��" & Hour(endDate) & "ʱ" & Minute(endDate) & "��"
	  End If
	  %>
            </b>&nbsp;</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr align="center"> 
    <td colspan="2"><br>
      <a href="webtrace_detail_d.asp?tranid=<%=hostid%>&tranname=<%=hostname%>&cityid=<%=cityid%>&cityname=<%=cityname%>">�鿴�������ݱ�</a> <br><BR>
<!-- ͼ�� -->
<%
'==============================================================================================================
' ���㻭�����õ����ݣ����ȣ�
Dim i,j,k, arrRs(), arrErr(), sql, arrTmp, iAvg, iAvgMax, iErrMax, xStart, xEnd, iWeeks

xStart=DatePart("ww", DateValue(startDate))
xEnd=DatePart("ww", DateValue(endDate))

iWeeks=xEnd-xStart+1

Redim arrRs(xEnd), arrErr(xEnd)

iAvgMax=0
iErrMax=0

For i=0 To 12
	arrErr(i)=0
Next

sql="exec yl_webtrace_q " & hostid & "," & cityid & ",'" & startDate & "','" & endDate & "'"
'response.write sql
Set rs=Server.CreateObject("adodb.recordset")
rs.open sql, cnnDragon, 1, 1   ' ����һ�����ڸ��ܵ�ƽ��·��ʱ�䣨���룩

If NOT(rs.Eof And rs.Bof) Then
	While Not rs.Eof
		iAvg=(CInt(rs(2))+CInt(rs(3))+CInt(rs(4)))/3
		arrRs(CInt(rs(10)))=iAvg
		rs.MoveNext
	Wend
End If

rs.close
sql="exec yl_webtrace_q_error " & hostid & "," & cityid & ",'" & startDate & "','" & endDate & "'"
'response.write sql
rs.open sql, cnnDragon, 1, 1   ' ����һ�����ڸ��ܵĴ������

If NOT(rs.Eof And rs.Bof) Then
	While Not rs.Eof
		arrErr(CInt(rs(2)))=CInt(rs(1))
		rs.MoveNext
	Wend
End If

For i=xStart To xEnd
	If iAvgMax<arrRs(i) Then iAvgMax=arrRs(i)
	If iErrMax<arrErr(i) Then iErrMax=arrErr(i)
Next
' ���㻭�����õ����ݣ�������
'==============================================================================================================
%>
<applet name=combochart
	codebase=../classes
	code=NFComboChartApp.class
	width=600 height=350>


<param	name=NFParamScript value = '


DwellLabel      = ("", white, "Courier", 12);
DwellBox        = (red, SHADOW, 4);
Background    = (white, RECESS, 0);

Header        = ("");

HeaderBox     = (lightGray, RAISED, 0);

GraphType     = STACK;

BottomScroll=(0,<%=iWeeks%>);
BottomScale=(0,<%=iWeeks%>);
Footer	= ("",black,"TimesRoman",12,0 );
Legend		= ("", black, "TimesRoman", 12);
LegendLayout	= (HORIZONTAL, BOTTOM);
DataSets      =("ƽ��·��ʱ�䣨���룩", x6666FF);
DataSet1      = 
<%
For i=xStart To xEnd
	Response.Write arrRs(i)
	If i=xEnd Then
		Response.Write ";"
	Else
		Response.Write ","
	End If
Next
%>
BarLabels     = 
<%
j=DateValue(startDate)
Select Case WeekDay(j)
Case 1
	j=DateAdd("d",1,j)
Case 2
Case 3
	j=DateAdd("d",-1,j)
Case 4
	j=DateAdd("d",-2,j)
Case 5
	j=DateAdd("d",-3,j)
Case 6
	j=DateAdd("d",-4,j)
Case 7
	j=DateAdd("d",-5,j)
End Select

k=DateAdd("d",6,j)
For i=xStart To xEnd
	If i=xEnd Then
	%>"<%=Month(j) & "-" & Day(j) & "��" & Month(k) & "-" & Day(k)%>";<%
	Else
	%>"<%=Month(j) & "-" & Day(j) & "��" & Month(k) & "-" & Day(k)%>",<%
	End If
	j=DateAdd("d",7,j)
	k=DateAdd("d",6,j)
Next
%>
LineSets      = ("�������",red,);
LineSet1      = 
<%
For i=xStart To xEnd
	Response.Write "(" & i-1 & "," & arrErr(i) & ")"
	If i=xEnd Then
		Response.Write ";"
	Else
		Response.Write ","
	End If
Next
%>
LineStyle =	(SOLID,2,);
LeftScale = (0,<%=iAvgMax+5%>, <%=(iAvgMax+5)\10%>);
LeftScroll=(0,<%=iAvgMax+5%>);
BottomTics    = ("ON", black, "TimesRoman", 12, 90);


LeftFormat        = (INTEGER, "%d");

LeftTics          = ("ON", black, "TimesRoman", 12);

LeftTitle	= ("ƽ��·��ʱ�䣨���룩", black, "TimesRoman", 12,90);
RightTics         = ("ON", black, "TimesRoman", 12);

RightScale        = (0, <%=iErrMax+10%>, <%=(iErrMax+10)\10%>);

RightTitle	= ("�� �� �� ��", black, "TimesRoman", 12,90);
RightFormat	  = (INTEGER);


Bar3DDepth = 0;
Grid		= (lightGray, white, black);
GridLine	= (HORIZONTAL, SOLID, 1);
'>
</applet>

<!-- ͼ�� -->
	  <br>
    </td>
  </tr>
</table>
</body>
</html>
<%
Set rs=Nothing
%>
<!-- #include file="inc/foot.asp" -->
<SCRIPT LANGUAGE="JavaScript">
<!--
var x=parent.frames.conditionFrame.document;
x.all.hostid.value="<%=hostid%>";
x.all.hostname.value="<%=hostname%>";
x.all.cityid.value="<%=cityid%>";
x.all.cityname.value="<%=cityname%>";
x.frmCondition.action="webtrace_chart.asp";
//-->
</SCRIPT>