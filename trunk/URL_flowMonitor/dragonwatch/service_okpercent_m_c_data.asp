<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" --><!-- #include file="inc/getTime.asp" -->

<%

If Len(Request.QueryString("trans_id"))>0 Then
	Response.cookies("rep_trans")("id")=Request.QueryString("trans_id")
	Response.cookies("rep_trans")("name")=Request.QueryString("trans_name")
End If

If Len(Request.QueryString("city_id"))>0 Then
	Response.cookies("rep_city")("id")=Request.QueryString("city_id")
	Response.cookies("rep_city")("name")=Request.QueryString("city_name")
End If



			arrLastDay=Array(31,28,31,30,31,30,31,31,30,31,30,31)
			y=Year(startDate)
			If ((y MOD 4=0) AND (y MOD 100<>0)) OR (y MOD 400=0) Then
				arrLastDay(1)=29
			End if

DayLength=arrLastDay(Month(StartDate)-1)-1

Response.Cookies("rep_isdatatable")="_data"



If Len(Request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=Request.cookies("rep_prf")("id")
End If

If Len(Request.cookies("rep_trans")("id"))>0 Then
	If Len(Request.cookies("rep_city")("id"))>0 then
		sql="exec cq_server_okpercent_m_c_bygroup "& prof_id & "," & Request.cookies("rep_trans")("id") & ","& Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
	Else
		sql="exec cq_server_okpercent_m_c_bytran "& prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	sql="exec cq_server_okpercent_m_c "& prof_id & ",'" & startDate & "','" & endDate & "'"
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

	Redim arrOKPer(iRowCount-1,3,DayLength)
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

x=Split(startDate," ")
h=Hour(startDate)
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
    <td width="44%" bgcolor="#CCCCCC"><font class=VerdanaDB10><b>业务流程服务成功率&nbsp;</b></font></td>
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
		  <B>
		  当前预定义文件：<%=request.cookies("rep_prf")("name")%><BR>
		  <!-- #include file="inc/filter.asp" -->
		  </B>
		  </td>
        </tr>
        <tr>
          <td width="308" align="right">&nbsp;</td>
          <td width="287" align="right"><A class='bluelink' HREF="service_okpercent_m_c.asp?showchart=1">图表</A></td>
          <td width="47" align="right">&nbsp;</td>
        </tr>
        <tr>
          <td colspan="3" align="center" valign="top">

<table width="85%" border="0" cellspacing="1" cellpadding="3">

  <tr bgcolor="#330066" align=center>
	<td align="center"><font color="#ffffff">时段</font></td>
	<%
			If Len(Request.cookies("rep_city")("id"))>0 Then
				url="service_okpercent_m_c_data.asp"
			Else
				url="service_okpercent_m_t_data.asp"
			End If


	For m=0 to iRowCount-1
		If bShowLink then
			Response.Write "<td align='center'><font color='#ffffff'>"&request.cookies("rep_trans")("name")&"</font></td>"
		Else
			Response.Write "<td align='center'><a href="&url&"?selBy=t&city_id="&arrOKPer(m,1,0)&"&city_name="&arrOKPer(m,0,0)&"><font color='#ffffff'>"&arrOKPer(m,0,0)&"</font></td>"
		End if
	Next
	%>
  </tr>

    <%

		For n=0 to DayLength
			Response.Write "<tr bgcolor='"&arrColor(n mod 2)&"' align='center'>"
			Response.Write "<td><a href="&Chr(34)&"javascript:goLink("&n+1&")"&Chr(34)&">"&Year(StartDate)&"年"&Month(StartDate)&"月"&n+1&"日</td>"

			For j=0 to iRowCount-1
				If IsEmpty(arrOKPer(j,2,n)) Then
					Response.Write("<td>&nbsp;</td>")
				Else
					Response.Write "<td>"& arrOKPer(j,3,n) &"%</td>"
				End If
			Next
		Response.Write "</tr>"
		Next
	%>

</table>

		</td>
        </tr>
        <tr align="left">
          <td colspan="4">
		  <A class='bluelink' HREF="#" onclick="javascript:window.open('service_okpercent_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></A>这个报告显示了业务流程的服务成功率。
             &nbsp; <A class='bluelink' HREF="#" onclick="javascript:window.open('service_okpercent_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">更多...</A></td>
        </tr>
      </table>
  </tr>
</table>
</body>
</html>

<SCRIPT LANGUAGE="JavaScript">
<!--
function goLink(n)
{
	var y=<%=Year(startDate)%>;
	var m=<%=Month(startDate)%>;
	parent.frames.conditionFrame.document.all.selPer.value="d"
	location.href="service_okpercent_d_data.asp?per=d&d="+y+"-"+m+"-"+n+" 0:00&s="+y+"-"+m+"-"+n+" 0:0&e="+y+"-"+m+"-"+n+" 23:59"
}
//-->
</SCRIPT>
<!-- #include file="inc/foot.asp" -->
<SCRIPT LANGUAGE="JavaScript" src="inc/setSelByTocity.js"></SCRIPT>
<%If bShowLink Then%><SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToGroup.js"></SCRIPT><%End If%>