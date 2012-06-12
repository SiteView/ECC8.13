<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<html>
<head>
<title>业务流程错误分析</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
<style type="text/css">
<!--
.webtrace {  font-size: 14.8px; font-weight: bold}
-->
</style>
</head>

<body bgcolor="#FFFFFF" text="#000000">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="97%" bgcolor="#CCCCCC"> 
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td width="50%" height="22"><b>业务流程错误分析</b></td>
          <td align="right" width="50%" height="22"><B><%=Request.cookies("rep_city")("name")%></B>&nbsp;</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr align="center"> 
    <td colspan="2"><BR>
<%
If Len(Request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=Request.cookies("rep_prf")("id")
End If

If CInt(Request.QueryString("code"))=200 Then	
	sql="exec yl_error_cityid_grouptran_200 " & prof_id & "," & Request.cookies("rep_city")("id") & ",200,'" & startDate & "','" & endDate & "'"
Else
	sql="exec yl_error_cityid_grouptran " & prof_id & "," & Request.cookies("rep_city")("id") & "," & Request.QueryString("code") & ",'" & startDate & "','" & endDate & "'"
End If

'Set rs=Server.CreateObject("adodb.recordset")
'rs.Open sql, cnnDragon, 1, 1
Set rs=cnnDragon.Execute(sql)
If rs.Eof And rs.Bof Then
	Response.Write "<CENTER>没数据！</CENTER>"
Else
	Dim arrRs, iRows, iMax
	iMax=10
	arrRs=rs.GetRows()
	'arrRs=rs.GetRows(rs.RecordCount)
	iRows=UBound(arrRs,2)
	'Response.Write sql & "<HR>iRows=" & iRows & "<HR>"

	For i=0 To iRows
		If CInt(arrRs(2,i))>iMax Then iMax=CInt(arrRs(2,i))
	Next
%>
<!-- 生成图形 -->
      <applet name=barchart
	codebase=../classes
	code=NFBarchartApp.class
 width=500 height=300>
        <param name=NFParamScript value = '
DebugSet	= LICENSE;

Background	= (white, NONE, 0, "");

BottomTics      = ("ON", black, "TimesRoman", 12);

LeftTics        = ("ON", black, "TimesRoman", 12);

LeftScale       = (0, <%=iMax+10%>,5);
LeftScroll=(0,<%=iMax+10%>);
BottomScroll=(0,1);
LegendLayout	= (HORIZONTAL, BOTTOM);

BarLabels	= 
<%
For i=0 To iRows
	Response.Write """" & arrRs(1,i) & """"
	If i=iRows Then
		Response.Write ";"
	Else
		Response.Write ""
	End If
Next
%>

LeftTitle	= ("业 务 流 程 出 错 次 数", black, "TimesRoman", 12,90);

Footer		= ("错 误 状 态 码", black, "TimesRoman", 12);
LeftTitleBox	= (, , 5);

DwellLabel	= ("", black, "Courier", 12);

DwellBox	= (yellow, RAISED, 3);

BarWidth=30;
Bar3DDepth = 0;
Grid		= (lightGray, white, black);
GridLine	= (HORIZONTAL, SOLID, 1);
GraphType	= GROUP;


DataSets	= ("Server #1", );

DataSet1	= 
<%
For i=0 To iRows
	Response.Write """" & arrRs(2,i) & """"
	If i=iRows Then
		Response.Write ";"
	Else
		Response.Write ""
	End If
Next
%>
'>
      </applet> 
<%End If%>
<!-- 生成图形结束 -->
    </td>
  </tr>
</table>
</body>
</html>
<%
Set rs=Nothing
%>
<!-- #include file="inc/foot.asp" -->
