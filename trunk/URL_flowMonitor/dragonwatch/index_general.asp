<!-- #include file="../inc/head.asp" -->
<HTML>
<HEAD>
<TITLE> 游龙综合指数 </TITLE>
<META NAME="Author" CONTENT="Jin Zhe">
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<style type="text/css">
<!--
body,table,tr,td,p,font,pre {  font-family:arial; font-size: 10.5pt}
-->
</style>
</head>

<body bgcolor="#FFFFFF" text="#000000">
<%
If Len(Request.Form("stime"))=0 Then
%>
<FORM METHOD=POST ACTION="index_general.asp">
开始时间:<INPUT TYPE="text" NAME="stime" value="<%=Date%>"><br>
结束时间:<input type="text" name="etime" value="<%=date%>"><INPUT TYPE="submit">
</FORM>
<%
Else
	stime=DateValue(Request.Form("stime"))
	etime=DateValue(Request.Form("etime"))
	stime=stime & " 00:00"
	etime=etime & " 23:59"
	DayEnd=Day(CDate(etime))
	MaxTime=0
	MinTime=100

dim avgtime,arrTrans(20,2)
dim arrDay(30)

sql="select convert(varchar(10),convert(decimal(10,2),AVG(t_total)/10000))"
sql=sql&" from transactionlist tl,agent ag,transactions ts where"
sql=sql&" (tl.measurement_time between '" & stime & "' and '" & etime & "')"
sql=sql&" and tl.trans_id in (select trans_id from profiletran where profile_id='151')"
sql=sql&" and tl.status<4"
sql=sql&" and ts.trans_id=tl.trans_id"
sql=sql&" and ag.agent_id=tl.agent_id"
sql=sql&" and ag.city_id in (select city_id from profilecity where profile_id='151')"

set rs=cnnDragon.Execute(sql)
avgtime=rs(0)

sql="select ts.trans_name,convert(varchar(10),convert(decimal(10,2),AVG(t_total)/10000))"
sql=sql&" from transactionlist tl,agent ag,transactions ts where"
sql=sql&" (tl.measurement_time between '" & stime & "' and '" & etime & "')"
sql=sql&" and tl.trans_id in (select trans_id from profiletran where profile_id='151')"
sql=sql&" and tl.status<4"
sql=sql&" and ts.trans_id=tl.trans_id"
sql=sql&" and ag.agent_id=tl.agent_id"
sql=sql&" and ag.city_id in (select city_id from profilecity where profile_id='151')"
sql=sql&" group by ts.trans_name"
sql=sql&" order by convert(varchar(10),convert(decimal(10,2),AVG(t_total)/10000))"

set rs=cnnDragon.Execute(sql)
for i=0 to 19
	arrTrans(i,0)=rs(0)
	arrTrans(i,1)=rs(1)
	rs.movenext
next

sql="select convert(varchar(10),convert(decimal(10,2),AVG(t_total)/10000))"
sql=sql&" from transactionlist tl,agent ag,transactions ts where"
sql=sql&" (tl.measurement_time between '" & stime & "' and '" & etime & "')"
sql=sql&" and tl.trans_id in (select trans_id from profiletran where profile_id='151')"
sql=sql&" and tl.status<4"
sql=sql&" and ts.trans_id=tl.trans_id"
sql=sql&" and ag.agent_id=tl.agent_id"
sql=sql&" and ag.city_id in (select city_id from profilecity where profile_id='151')"
sql=sql&" group by datepart(dd,measurement_time)"

set rs=cnnDragon.Execute(sql)
for i=0 to dayend-1
	arrDay(i)=rs(0)
	if arrDay(i)>MaxTime then MaxTime=arrDay(i)
	if arrDay(i)<MinTime then MinTime=arrDay(i)
	rs.movenext
next

MaxTime=Int(MaxTime)+2
MinTime=Int(MinTime)-2
Diff=Int((MaxTime-MinTime)/5)
%>
测量时段：<%=stime%>到<%=etime%>
<p>
平均响应时间：<%=avgtime%>秒
<hr>

<table border="1">
<%
for i=0 to 19
%>
<tr>
<td><%=arrTrans(i,0)%></td>
<td><%=arrTrans(i,1)%></td>
</tr>
<%next%>
</table>
<hr>

<table border="1">
<%
for i=0 to dayend-1
%>
<tr>
<td><%=i+1%></td>
<td><%=arrDay(i)%></td>
</tr>
<%
next
%>
</table>
<hr>

<applet name=xychart codebase="../../classes" code="NFXYChartApp.class" width=500 height=180 VIEWASTEXT align=center>
<param	name=NFParamScript	value = '

Background	= (white, NONE);

Footer	= ("",black,"TimesRoman",12,0 );
Grid		= (lightGray, white, black);
GridLine	= (HORIZONTAL, SOLID, 1);

DwellLabel      = ("", white, "Courier", 12);
DwellBox        = (red, SHADOW, 4);

Legend		= ("", black, "TimesRoman", 12);

LegendLayout	= (HORIZONTAL, BOTTOM);

Header		= ("", black, "TimesRoman", 14);
HeaderBox	= (white, RAISED, 0);

RightTitle	= ("    ", white, "TimesRoman", 14);
LineSet1=
<%
for i=0 to dayend-1
	if i<>dayend-1 then
		response.write "(" & i & "," & arrDay(i) & "),"
	else
		response.write "(" & i & "," & arrDay(i) & ");"
	end if
next
%>

LineSets =
     ("综合平均",);
LineStyle =
	(SOLID,2,);
LineSymbol =
	(DIAMOND, 6,BOTH, black,1 );
LeftScale =
<%response.write "(" & MinTime & "," & MaxTime & "," & Diff & ");"%>
LeftTitle	= ("    游龙综合指数曲线 (秒)",black,"TimesRoman",12,90 );

LeftFormat   = ( , "%f");
BottomFormat   = ( , "%d");
BottomTics	= ("ON", darkgray, "@TimesRoman", 12, 90);
BottomScale=(0,<%=DayEnd-1%>,1);

BottomLabels=
<%
for i=1 to dayend
	if i<>dayend then
		response.write i & ","
	else
		response.write i & ";"
	end if
next
%>
LeftTics	= ("ON", darkgray, "@TimesRoman", 12);
LeftTitleBox	= (white, SHADOW, 0);

'>
</applet>

</BODY>
</HTML>
<%End If%>
<!-- #include file="../inc/foot.asp" -->
