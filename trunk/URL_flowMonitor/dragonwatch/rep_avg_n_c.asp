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

Response.cookies("rep_isdatatable")=""

'response.write startDate & "<BR>"
'response.write endDate & "<BR>"
'response.end

If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

' 取得平均响应时间(以城市)
If Len(Request.cookies("rep_trans")("id"))>0 Then
	If Len(Request.cookies("rep_city")("id"))>0 Then
		sql="exec yl_rep_avg_n_c_withid " & prof_id & "," & Request.cookies("rep_trans")("id") & "," & Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
	Else
		sql="exec yl_rep_avg_n_c_bytranid " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	sql="exec yl_rep_avg_n_c " & prof_id & ",'" & startDate & "','" & endDate & "'"
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
	Dim strCitys_id ' 存城市编号
	Dim strCitys_name ' 存城市名称 （以上两个）
	iMax=0 ' 最大数值

	' 计算城市ID，名称，数据线最大值
	oldid=0
	For i=0 To iRsRows
		If iMax<CInt(arrRs(3,i)) Then iMax=CInt(arrRs(3,i))
		If oldid<>CInt(arrRs(1,i)) Then
			strCitys_id=strCitys_id & arrRs(1,i) & ","
			strCitys_name=strCitys_name & arrRs(0,i) & ","
			oldid=CInt(arrRs(1,i))
		End If
	Next
	arrCitys_id=Split(strCitys_id, ",")
	arrCitys_name=Split(strCitys_name, ",")

	iCountCitys=UBound(arrCitys_id)-1 ' 此预定义文件包括多少个城市

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
    <td width="44%" bgcolor="#CCCCCC"><font class=VerdanaDB10><b>城市时辰平均响应时间&nbsp;</b></font></td>
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
			If Len(Request.cookies("rep_trans")("id"))>0 Then
				url="rep_avg_n_c.asp"
			Else
				url="rep_avg_n_t.asp"
			End If
			bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)
			For i=0 To iCountCitys
				If bShowLink Then
			%>
			<tr>
				<td><%=arrCitys_name(i)%></td>
			</tr>
			<%
				Else
			%>
			<tr>
				<td><A class='bluelink' HREF="<%=url%>?selby=t&city_id=<%=arrCitys_id(i)%>&city_name=<%=arrCitys_name(i)%>" style="text-decoration:underline"><%=arrCitys_name(i)%></A></td>
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
          <td width="287" align="right"><A class='bluelink' HREF="rep_avg_n_c_data.asp">数据表</A></td>
          <td width="47" align="right">&nbsp;</td>
        </tr>
        <tr>
          <td colspan="3" align="center" valign="top">
		  <applet name=linechart codebase="../classes" code="NFLineChartApp.class" width=750 height=300 VIEWASTEXT align=center>
              <param	name=NFParamScript	value = '

	Background	= (White, NONE);

	GraphType	= ROWS;

	Footer	= ("",black,"TimesRoman",12,0 );
	Grid		= (lightGray, white, black);
	GridLine	= (HORIZONTAL, SOLID, 1);

	DwellLabel      = ("", white, "Courier", 12);
	DwellBox        = (red, SHADOW, 4);

	Legend		= ("", black, "TimesRoman", 12);
	BottomScroll=(0,60);

	LegendLayout	= (HORIZONTAL, BOTTOM);

	Header		= ("", black, "TimesRoman", 14);
	HeaderBox	= (white, RAISED, 0);



	RightTitle	= ("    ", white, "TimesRoman", 14);
	<%
	'On Error Resume Next
	ReDim arrLineSet(iCountCitys,59)
	oldid=0
	j=0
	For i=0 To iRsRows
		If oldid<>CInt(arrRs(1,i)) Then
			j=j+1
			oldid=CInt(arrRs(1,i))
		End If
		arrLineSet(j-1,CInt(arrRs(2,i)))=arrRs(3,i)
	Next
	For i=0 To iCountCitys
		Response.Write "LineSet" & i+1 & "="
		str=""
		For j=0 To 59
			If j=59 Then
				Response.Write arrLineSet(i,j) & ";"
			Else
				Response.Write arrLineSet(i,j) & ","
			End If
		Next
		Response.Write vbCrLf
	Next
	iMax=iMax+10
	%>
LineSets =
     <%
	For i=0 To iCountCitys
		If i=iCountCitys Then
			Response.Write "(""" & arrCitys_name(i) & """,);"
		Else
			Response.Write "(""" & arrCitys_name(i) & """,),"
		End If
	Next
	 %>
LineStyle =
	<%
	For i=0 To iCountCitys
		If i=iCountCitys Then
			Response.Write "(SOLID,2,);"
		Else
			Response.Write "(SOLID,2,),"
		End If
	Next
	%>
LineSymbol =
	<%
	For i=0 To iCountCitys
		If i=iCountCitys Then
			Response.Write "(DIAMOND, 6,BOTH, black,1 );"
		Else
			Response.Write "(DIAMOND, 6,BOTH, black,1 ),"
		End If
	Next
	%>
LeftScale =

    (0,<%=iMax%>,<%=iMax\10%>);
	LeftScroll=(0,<%=iMax%>);


LeftTitle	= ("     平均响应时间 (秒)",black,"TimesRoman",12,90 );

LeftFormat   = ( , "%f");
BottomFormat   = ( , "%d");
BottomTics	= ("ON", darkgray, "@TimesRoman", 12, 90);

BottomLabels	=
<%
b=Hour(startDate)
For i=0 To 59
	If i=59 Then
		%>"<%=b&":"&i%>";<%
	Else
		%>"<%=b&":"&i%>",<%
	End If
Next
%>
LeftTics	= ("ON", darkgray, "@TimesRoman", 12);
LeftTitleBox	= (white, SHADOW, 0);

'>
            </applet></td>
        </tr>
        <tr align="left">
          <td colspan="4">
		  <A class='bluelink' HREF="#" onclick="javascript:window.open('rep_avg_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></A>这个报告显示了城市的时辰平均响应时间。
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
<SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToCity.js"></SCRIPT>
<%If bShowLink Then%><SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToGroup.js"></SCRIPT><%End If%>