<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" --><!-- #include file="inc/getTime.asp" -->

<%
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

Response.Cookies("rep_isdatatable")=""

If Len(Request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=Request.cookies("rep_prf")("id")
End If

If Len(Request.cookies("rep_trans")("id"))>0 Then
	If Len(Request.cookies("rep_city")("id"))>0 then
		sql="exec cq_server_okpercent_w_c_bygroup "& prof_id & "," & Request.cookies("rep_trans")("id") & ","& Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
	Else
		sql="exec cq_server_okpercent_w_c_bytran "& prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	sql="exec cq_server_okpercent_w_c "& prof_id & ",'" & startDate & "','" & endDate & "'"
End If
''response.write sql
''response.end

'/*************** 执行存放存储过程，把数据保存到数组arrOKper中*****************/
Dim iRecCount
Dim iRowCount
Dim iOldId
Dim bRecExists

Set rs=Server.CreateObject("adodb.RecordSet")
rs.Open sql,cnnDragon,1,1

bRecExists = true
If (rs.Bof and rs.Eof) Then
	REM 没有数据情况下的处理
'	Response.Write "<Center>此时段没有数据</Center>"
	bRecExists = false
Else
	arrData = rs.GetRows()
	iRecCount = UBound(arrData,2) + 1
'/***** arrData的结构为Name,Id,HourList,OKPer *****/
End If
rs.Close
Set rs=Nothing

REM 产生新数组以显示数据
If bRecExists Then
	iOldId = 0
	For i=0 To iRecCount - 1
		If CInt(arrData(1,i)) <> iOldId Then
			iRowCount = iRowCount + 1
			iOldId = CInt(arrData(1,i))
		End If
	Next

	Redim arrOKPer(iRowCount-1,3,6)
	iOldId = 0
	iCurrRow = 0
	For i=0 To iRecCount - 1
		If CInt(arrData(1,i)) <> iOldId Then
			iCurrRow = iCurrRow + 1
			iOldId = CInt(arrData(1,i))
			arrOKPer(iCurrRow-1,0,0) = arrData(0,i) 'name
			arrOKPer(iCurrRow-1,1,0) = arrData(1,i) 'id
		End If
		arrOKPer(iCurrRow-1,2,CInt(arrData(2,i))-1) = arrData(2,i)
		arrOKPer(iCurrRow-1,3,CInt(arrData(2,i))-1) = arrData(3,i)
	Next
End If

bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)

%>

<HTML>
<HEAD>
<TITLE>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</TITLE>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
</HEAD>

<BODY bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<br>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> <!-- 标题BAR -->
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="44%" bgcolor="#CCCCCC"><font class=VerdanaDB10><b>服务成功率&nbsp;</b></font></td>
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
	<%If bRecExists Then%>
      <table border="0" cellspacing="3" cellpadding="0">
        <tr>
          <td colspan="3" align="left">
		  <B>
		  <%bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)%>
		  当前预定义文件：<%=request.cookies("rep_prf")("name")%><BR>
		  <!-- #include file="inc/filter.asp" -->
		  </B>
		  </td>
          <td rowspan="3" width="187" align="left" valign="top" id=trans>
            <table cellpadding="1" width="100" cellspacing="2" border="0">
						<%
			If Len(Request.cookies("rep_city")("id"))>0 Then
				url="service_okpercent_w_c.asp"
			Else
				url="service_okpercent_w_t.asp"
			End If
			%>

			<%
			For i=0 To iRowCount-1
			If bShowLink Then
			%>
			<tr>
				<td><%=Request.cookies("rep_trans")("name")%></td>
			</tr>
			<%Else%>
			<tr>
				<td><A class='bluelink' HREF="<%=url%>?selBy=t&city_id=<%=arrOKPer(i,1,0)%>&city_name=<%=arrOKPer(i,0,0)%>" style="text-decoration:underline"><%=arrOKPer(i,0,0)%></A></td>
			</tr>
			<%End If
			Next%>
            </table>
          </td>
        </tr>
        <tr>
          <td width="308" align="right">&nbsp;</td>
          <td width="287" align="right"><A class='bluelink' HREF="service_okpercent_w_c_data.asp">数据表</A></td>
          <td width="47" align="right">&nbsp;</td>
        </tr>
        <tr>
          <td colspan="3" align="center" valign="top">
		  <applet name=linechart codebase="../classes" code="NFLineChartApp.class" width=550 height=300 VIEWASTEXT align=center>
              <param	name=NFParamScript	value = '

	Background	= (White, NONE);

	GraphType	= ROWS;

	Footer	= ("时辰",black,"TimesRoman",12,0 );
	Grid		= (lightGray, white, black);
	GridLine	= (HORIZONTAL, SOLID, 1);

	DwellLabel      = ("", white, "Courier", 12);
	DwellBox        = (red, SHADOW, 4);

	Legend		= ("", black, "TimesRoman", 12);
	BottomScroll=(0,6);

	LegendLayout	= (HORIZONTAL, BOTTOM);

	Header		= ("", black, "TimesRoman", 14);
	HeaderBox	= (white, RAISED, 0);

	RightTitle	= ("    ", white, "TimesRoman", 14);

	<%
	For i=0 to iRowCount-1
		Response.Write "LineSet"& i+1 &"="
		For j=1 to 6
			'If Not IsEmpty(arrOKPer(i,2,j)) Then
				Response.Write arrOKPer(i,3,j) & ","
			'End If
		Next

		'If Not IsEmpty(arrOKPer(i,2,0)) Then
			Response.Write arrOKPer(i,3,0)
		'End If
		response.write ";"
	Next
	%>

LineSets =
     <%
	For i=0 To iRowCount-1
		If i=iRowCount-1 Then
			Response.Write "(""" & arrOKPer(i,0,0) & """,);"
		Else
			Response.Write "(""" & arrOKPer(i,0,0) & """,),"
		End If
	Next
	 %>
LineStyle =
	<%
	For i=0 To iRowCount-1
		If i=iRowCount-1 Then
			Response.Write "(SOLID,2,);"
		Else
			Response.Write "(SOLID,2,),"
		End If
	Next
	%>
LineSymbol =
	<%
	For i=0 To iRowCount-1
		If i=iRowCount-1 Then
			Response.Write "(DIAMOND, 6,BOTH, black,1 );"
		Else
			Response.Write "(DIAMOND, 6,BOTH, black,1 ),"
		End If
	Next
	%>
LeftScale =

    (0,105,10);
	LeftScroll=(0,105);


LeftTitle	= ("     服务成功率(百分比%)",black,"TimesRoman",12,90 );

LeftFormat   = (INTEGER , "%d %");
BottomFormat   = ( , "%d");
BottomTics	= ("ON", darkgray, "@TimesRoman", 12, 90);

BottomLabels	="星期一","星期二","星期三","星期四","星期五","星期六","星期日";
LeftTics	= ("ON", darkgray, "@TimesRoman", 12);
LeftTitleBox	= (white, SHADOW, 0);

'>
            </applet>
			</td>
        </tr>
        <tr align="left">
          <td colspan="4">
		  <A class='bluelink' HREF="#" onclick="javascript:window.open('service_okpercent_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></A>这个报告显示了业务流程的服务成功率。
            &nbsp; <A class='bluelink' HREF="#" onclick="javascript:window.open('service_okpercent_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">更多...</A></td>
        </tr>
      </table>
	  <%Else
	  	Response.Write "<Center>此时段没有数据</Center>"
	  %>
	  <%End If%>
      <span id="subtitle"><br>
      </span> <span id="trimscreen">
      <form name="TrimForm" onsubmit="return false;">
      </form>
      </span> <span id=linegraph> </span> <span id=description> </span> </td>
  </tr>

</TABLE>
</BODY>
</HTML>
<SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToCity.js"></SCRIPT>
<%If bShowLink Then%><SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToGroup.js"></SCRIPT><%End If%>
<!-- #include file="inc/foot.asp" -->