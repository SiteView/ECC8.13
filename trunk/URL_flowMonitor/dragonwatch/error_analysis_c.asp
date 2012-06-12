<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<script language=javascript src="inc/setSelBytoCity.js"></script>
<%
'On Error Resume Next
If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

bFilteredTran = Len(Request.cookies("rep_trans")("id"))
bFilteredCity = Len(Request.cookies("rep_city")("id"))
bShowLink = bFilteredTran > 0 And bFilteredCity > 0

sql = "exec cq_erranalysis_c " & prof_id & ",'" & startDate & "','" & endDate & "'"
If bFilteredTran Then sql = "exec cq_erranalysis_c_onetran " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"

''response.write sql
''response.end
Set rs=Server.CreateObject("adodb.recordset")  ' 取数据
rs.Open sql, cnnDragon, 1, 1

bRecExists = true
If rs.RecordCount=0 Then
'	Response.Write "<Center>此时段没有错误发生！</Center>"
	bRecExists = false
Else
	arrRs=rs.GetRows(rs.RecordCount)
	rs.Close
	Set rs=Nothing

	Dim iRsCols, iRsRows, i, j, iMax
	iRsCols=UBound(arrRs) ' 有多少字段
	iRsRows=UBound(arrRs,2) ' 有多少行数据
	
	iMax=0
	For i=0 To iRsRows
		If CLng(arrRs(2,i))>iMax Then iMax=CLng(arrRs(2,i))
	Next
End If
	' 过滤
%>
<html>
<head>
<title>业务流程错误分析</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<table width="100%" border="0" cellspacing="1" cellpadding="2">
  <tr> 
    <td width="4%"><img src="img/dots.gif" width="33" height="32"></td>
    <td bgcolor="#CCCCCC" colspan="2"> 
      <table width="100%" border="0" cellspacing="1" cellpadding="3">
        <tr> 
          <td width="23%" height="18"><b>业务流程错误分析</b></td>
          <td width="77%" height="18" align=right><b> 
            <%
	  If DateDiff("d", DateValue(startDate), DateValue(endDate))=0 Then
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时" & Minute(startDate) & "分 - " & Hour(endDate) & "时" & Minute(endDate) & "分"
	  Else
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时" & Minute(startDate) & "分 - " & Year(endDate) & "年" & Month(endDate) & "月" & Day(endDate) & "日" & Hour(endDate) & "时" & Minute(endDate) & "分"
	  End If
	  %>
            </b></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr> 
    <td colspan="2"> <B>当前预定义文件：<%=request.cookies("rep_prf")("name")%><BR>
      <!--#include file="inc/filter.asp"-->
      </B> </td>
    <td width="26%" rowspan="4" valign="top"> 
	<BR>
      <%	
			Set rs=cnnDragon.Execute("exec yl_profiletrans " & prof_id)
		%>
      <TABLE>
        <%
				Dim tmpTranID
				If Len(Request.cookies("rep_trans")("id"))=0 Then
					tmpTranID=0
				Else
					tmpTranID=CInt(Request.cookies("rep_trans")("id"))
				End If
				While Not rs.Eof
					If tmpTranID=CInt(rs(0)) Then
				%>
        <TR>
          <TD><font color=gray><%=rs(1)%></font></TD>
        </TR>
        <%Else%>
        <TR>
          <TD><A HREF="error_analysis.asp?transid=<%=rs(0)%>&transname=<%=rs(1)%>" style="text-decoration:underline;color:blue"><%=rs(1)%></A></TD>
        </TR>
        <%
					End If
					rs.MoveNext
				Wend%>
      </TABLE>
      <BR>
      <BR>
      <%Set rs=Nothing%>
    </td>
  </tr>
<%If bRecExists Then%>
  <tr> 
    <td colspan="2" align="center"> 
      <!-- 具体内容 -->
      <applet name=barchart
	codebase=../classes
	code=NFBarchartApp.class
 width=500 height=300>
        <param name=NFParamScript value = '
DebugSet	= LICENSE;

Background	= (white, NONE, 0, "");

BottomTics      = ("ON", gray, "TimesRoman", 12, 90);

LeftTics        = ("ON", black, "TimesRoman", 12);
<%'
If iRsRows = 0 then
	iLeftScale = 0
Else
	iLeftScale = iMax\iRsRows
End If
%>
LeftScale       = (0, <%=iMax+iLeftScale%>,<%=iLeftScale%>);
LeftScroll=(0,<%=iMax+iLeftScale%>);
BottomScroll=(0,<%=iRsRows%>);
LegendLayout	= (HORIZONTAL, BOTTOM);

BarLabels	= 
<%
For i=0 To iRsRows
	If i=iRsRows Then
		Response.Write """" & arrRs(1,i) & """" & ";"
	Else
		Response.Write """" & arrRs(1,i) & """" & ","
	End If
Next
%>

LeftTitle	= ("业 务 流 程 出 错 次 数", black, "TimesRoman", 12,90);

Footer		= ("", black, "TimesRoman", 12);
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
For i=0 To iRsRows
	If i=iRsRows Then
		Response.Write """" & arrRs(2,i) & """" & ";"
	Else
		Response.Write """" & arrRs(2,i) & """" & ","
	End If
Next
%>
'>
      </applet> 
      <!-- 具体内容结束，以下程序产生数据表 -->
    </td>
  </tr>
  <tr>
    <td colspan="2" align="center" height="20">&nbsp;</td>
  </tr>
  <tr> 
    <td colspan="2"> 
      <table width="100%" border="0" cellspacing="1" cellpadding="2" style="display:">
        <tr align="center" bgcolor="#330066"> 
          <td width="48%"><font color="#FFFFFF">城市</font></td>
          <td width="9%"><font color="#FFFFFF">错误次数</font></td>
          <td width="8%"><font color="#FFFFFF">错误占%</font></td>
        </tr>
        <%

Dim iErrTotal
For i=0 To iRsRows
	iErrTotal=iErrTotal+CInt(arrRs(2,i))
Next

For i=0 To iRsRows
%>
        <tr bgcolor="<%=arrColor(i mod 2)%>"> 
          <td><%=arrRs(1,i)%><br>
          </td>
          <td align="center"><%=arrRs(2,i)%></td>
          <td align="center"><%=Int((CInt(arrRs(2,i))/iErrTotal)*10000)/100%>%</td>
        </tr>
        <%
Next
%>
      </table>
      <BR>
      <TABLE>
        <tr valign="top"> 
          <td height="16" align="center"><a class='bluelink' href="#" onClick="javascript:window.open('error_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img src="img/lamp.gif" width="22" height="22" border="0"></a></td>
          <td valign="baseline" height="16" align="left">这个报告显示了业务流程的错误数据　<a class='bluelink' href="#" onClick="javascript:window.open('error_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">更多...</a></td>
        </tr>
      </TABLE>
    </td>
  </tr>
<%Else%>
  <tr> 
    <td colspan="2" align="center">没有错误发生.</td>
    <td valign="top">&nbsp;</td>
  </tr>
<%End If%>
</table>
</body>
</html>
<!-- #include file="inc/foot.asp" -->

