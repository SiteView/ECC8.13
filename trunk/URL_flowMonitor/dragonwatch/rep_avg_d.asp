<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
' 保存过滤条件
If Len(Request.QueryString("trans_id"))>0 Then
	Response.cookies("rep_trans")("id")=Request.QueryString("trans_id")
	Response.cookies("rep_trans")("name")=Request.QueryString("trans_name")
Else
	'Response.cookies("rep_trans")("id")=""
	'Response.cookies("rep_trans")("name")=""
End If
If Len(Request.QueryString("city_id"))>0 Then
	Response.cookies("rep_city")("id")=Request.QueryString("city_id")
	Response.cookies("rep_city")("name")=Request.QueryString("city_name")
Else
	'Response.cookies("rep_city")("id")=""
	'Response.cookies("rep_city")("name")=""
End If
'===========================================================================

' 清除过滤条件（点应用时）
' 选择业务流程时清业务流程
If Trim(Request.Form("selBy"))="t" Then
	Response.cookies("rep_trans")("id")=""
	Response.cookies("rep_trans")("name")=""
End If
' 选择城市时清城市
If Trim(Request.Form("selBy"))="c" Then
	Response.cookies("rep_city")("id")=""
	Response.cookies("rep_city")("name")=""
End If

'response.write request.cookies("rep_trans")("id")&"<BR>"
'response.write request.cookies("rep_trans")("name")&"<BR>"
'response.write request.cookies("rep_city")("id")&"<BR>"
'response.write request.cookies("rep_city")("name")&"<BR>"


' *****************************************
' 根据选择条件决定调用哪个页面
	Select Case Request.cookies("rep_per")
		Case "h" ' 小时
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "rep_avg_n_t" & Request.cookies("rep_isdatatable") & ".asp"
				Case "c","g"
					Server.Transfer "rep_avg_n_c" & Request.cookies("rep_isdatatable") & ".asp"
				'Case "g"
			End Select
		Case "d" ' 天
			Select Case Request.cookies("rep_by")
				Case "t"
					If Len(Request.cookies("rep_isdatatable"))<>0 Then
						If Len(Request.QueryString("showchart"))=0 Then
							Server.Transfer "rep_avg_d_data.asp"
						End If
					End If
				Case "c","g"
					Server.Transfer "rep_avg_d_c" & Request.cookies("rep_isdatatable") & ".asp"
				'Case "g"
			End Select
		Case "w" ' 星期
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "rep_avg_w_t" & Request.cookies("rep_isdatatable") & ".asp"
				Case "c","g"
					Server.Transfer "rep_avg_w_c" & Request.cookies("rep_isdatatable") & ".asp"
				'Case "g"
			End Select
		Case "m" ' 月
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "rep_avg_m_t" & Request.cookies("rep_isdatatable") & ".asp"
				Case "c","g"
					Server.Transfer "rep_avg_m_c" & Request.cookies("rep_isdatatable") & ".asp"
				'Case "g"
			End Select
		Case "q" ' 季度
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "rep_avg_q_t" & Request.cookies("rep_isdatatable") & ".asp"
				Case "c","g"
					Server.Transfer "rep_avg_q_c" & Request.cookies("rep_isdatatable") & ".asp"
				'Case "g"
			End Select
		Case "y" ' 年
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "rep_avg_y_t" & Request.cookies("rep_isdatatable") & ".asp"
				Case "c","g"
					Server.Transfer "rep_avg_y_c" & Request.cookies("rep_isdatatable") & ".asp"
				'Case "g"
			End Select
	End Select
' *****************************************

Response.cookies("rep_isdatatable")=""

'response.write startDate & "<BR>"
'response.write endDate & "<BR>"
'response.end

If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

' 取得平均响应时间
If Len(Request.cookies("rep_city")("id"))>0 Then
	If Len(Request.cookies("rep_trans")("id"))>0 Then
		sql="exec yl_rep_avg_d_withid " & prof_id & "," & Request.cookies("rep_city")("id") & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	Else
		sql="exec yl_rep_avg_d_bycityid " & prof_id & "," & Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	sql="exec yl_rep_avg_d " & prof_id & ",'" & startDate & "','" & endDate & "'"
End If
'response.write sql
Set rs=Server.CreateObject("adodb.recordset")  ' 取数据
rs.Open sql, cnnDragon, 1, 1
If rs.RecordCount=0 Then
	Response.Write "<Center>此时段没有数据</Center>"
Else

	arrRs=rs.GetRows(rs.RecordCount)
	rs.Close
	Set rs=Nothing

	iRsCols=UBound(arrRs) ' 有多少字段
	iRsRows=UBound(arrRs,2) ' 有多少行数据
	Dim strTrans_id
	Dim strTrans_name
	iMax=0 ' 最大数值

	' 计算业务流程ID，名称，数据线最大值
	oldid=0
	For i=0 To iRsRows
		If iMax<CInt(arrRs(3,i)) Then iMax=CInt(arrRs(3,i))
		If oldid<>CInt(arrRs(1,i)) Then
			strTrans_id=strTrans_id & arrRs(1,i) & ","
			strTrans_name=strTrans_name & arrRs(0,i) & ","
			oldid=CInt(arrRs(1,i))
		End If
	Next
	arrTrans_id=Split(strTrans_id, ",")
	arrTrans_name=Split(strTrans_name, ",")

	iCountTrans=UBound(arrTrans_id)-1 ' 此预定义文件包括多少个 Transaction

%>
<html>
<head>
<title>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<BR>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> <!-- 标题BAR -->
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="44%" bgcolor="#CCCCCC"><font class=VerdanaDB10><b>业务流程时辰平均响应时间&nbsp;</b></font></td>
    <td width="53%" bgcolor="#CCCCCC" align="right"><font class=VerdanaDB10><b>时段:
      <%
	  If DateDiff("d", DateValue(startDate), DateValue(endDate))=0 Then
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时" & Minute(startDate) & "分 - " & Hour(endDate) & "时" & Minute(endDate) & "分"
	  Else
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时" & Minute(startDate) & "分 - " & Year(endDate) & "年" & Month(endDate) & "月" & Day(endDate) & "日" & Hour(endDate) & "时" & Minute(endDate) & "分"
	  End If
	  %>
	  </b></font></td>
  </tr>
  <tr valign="top">
    <td colspan="3">&nbsp; <br>
      <table border="0" cellspacing="3" cellpadding="0">
        <tr>
          <td colspan="3" align="left">
		  <B><%bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)%>
		  当前预定义文件：<%=request.cookies("rep_prf")("name")%><BR>
		  <!-- #include file="inc/filter.asp" -->
		  </B>
		  </td>
          <td rowspan="3" width="187" align="left" valign="top" id=trans>
            <table cellpadding="1" width="100" cellspacing="2" border="0">
			<%
			If Len(Request.cookies("rep_city")("id"))>0 Then
				url="rep_avg_d.asp"
			Else
				url="rep_avg_d_c.asp"
			End If


			For i=0 To iCountTrans
				If bShowLink Then
			%>
			<tr>
				<td><%=arrTrans_name(i)%></td>
			</tr>
			<%
				Else
			%>
			<tr>
				<td><A class='bluelink' HREF="<%=url%>?selby=c&trans_id=<%=arrTrans_id(i)%>&trans_name=<%=arrTrans_name(i)%>" style="text-decoration:underline"><%=arrTrans_name(i)%></A></td>
			</tr>
			<%
				End If
			Next
			%>
            </table>
          </td>
        </tr>
        <tr>
          <td width="308" align="right">&nbsp;</td>
          <td width="287" align="right"><A class='bluelink' HREF="rep_avg_d_data.asp">数据表</A></td>
          <td width="47" align="right">&nbsp;</td>
        </tr>
        <tr>
          <td colspan="3" align="center" valign="top">
		  <applet name=xychart codebase="../classes" code="NFXYChartApp.class" width=550 height=300 VIEWASTEXT align=center>
              <param	name=NFParamScript	value = '

	Background	= (White, NONE);

	Footer	= ("",black,"TimesRoman",12,0 );
	Grid		= (lightGray, white, black);
	GridLine	= (HORIZONTAL, SOLID, 1);

	DwellLabel      = ("", white, "Courier", 12);
	DwellBox        = (red, SHADOW, 4);

	Legend		= ("", black, "TimesRoman", 12);
	BottomScroll=(0,23);

	LegendLayout	= (HORIZONTAL, BOTTOM);

	Header		= ("", black, "TimesRoman", 14);
	HeaderBox	= (white, RAISED, 0);

	RightTitle	= ("    ", white, "TimesRoman", 14);
	<%
	On Error Resume Next
	ReDim arrLineSet(iCountTrans,23)
	oldid=0
	j=0
	For i=0 To iRsRows
		If oldid<>CInt(arrRs(1,i)) Then
			j=j+1
			oldid=CInt(arrRs(1,i))
		End If
		arrLineSet(j-1,CInt(arrRs(2,i)))=arrRs(3,i)
	Next
	For i=0 To iCountTrans
		Response.Write "LineSet" & i+1 & "="
		str=""
		For j=0 To 23
			If Not (IsEmpty(arrLineSet(i,j))) Then Response.Write "(" & j & "," & arrLineSet(i,j) & "), "
		Next
		Response.Write ";" & vbCrLf
	Next
	iMax=iMax+10
	%>
LineSets =
     <%
	For i=0 To iCountTrans
		If i=iCountTrans Then
			Response.Write "(""" & arrTrans_name(i) & """,);"
		Else
			Response.Write "(""" & arrTrans_name(i) & """,),"
		End If
	Next
	 %>
LineStyle =
	<%
	For i=0 To iCountTrans
		If i=iCountTrans Then
			Response.Write "(SOLID,2,);"
		Else
			Response.Write "(SOLID,2,),"
		End If
	Next
	%>
LineSymbol =
	<%
	For i=0 To iCountTrans
		If i=iCountTrans Then
			Response.Write "(DIAMOND, 6,BOTH, black,1 );"
		Else
			Response.Write "(DIAMOND, 6,BOTH, black,1 ),"
		End If
	Next
	%>
LeftScale =

    (0,<%=iMax%>,<%=iMax\10%>);
	LeftScroll=(0,<%=iMax%>);

LeftTitle	= ("     平均响应时间曲线 (秒)",black,"TimesRoman",12,90 );

LeftFormat   = ( , "%f");
BottomFormat   = ( , "%d");
BottomTics	= ("ON", darkgray, "@TimesRoman", 12, 90);

BottomLabels	=
	    "0:00","1:00","2:00","3:00","4:00","5:00","6:00","7:00","8:00","9:00","10:00",
	    "11:00","12:00","13:00","14:00","15:00","16:00","17:00","18:00","19:00",
	    "20:00","21:00","22:00","23:00";
LeftTics	= ("ON", darkgray, "@TimesRoman", 12);
LeftTitleBox	= (white, SHADOW, 0);

'>
            </applet>

		</td>
        </tr>
        <tr align="left">
          <td colspan="4">
		  <A class='bluelink' HREF="#" onclick="javascript:window.open('rep_avg_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><A class='bluelink' HREF="#" onclick="javascript:window.open('rep_avg_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></A></A>这个报告显示了业务流程的时辰平均响应时间。
            &nbsp; <A class='bluelink' HREF="#" onclick="javascript:window.open('rep_avg_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">更多...</A></td>
        </tr>
      </table>
      <span id="subtitle"><br>
      </span> <span id="trimscreen">
      <form name="TrimForm" onsubmit="return false;">
      </form>
      </span> <span id=linegraph> </span> <span id=description> </span> </td>
  </tr>
</table>
</body>
</html>
<%
End If
%>
<!-- #include file="inc/foot.asp" -->
<SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToTransaction.js"></SCRIPT>
<%If bShowLink Then%><SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToGroup.js"></SCRIPT><%End If%>
