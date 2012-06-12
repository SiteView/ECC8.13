<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
Dim sql,rs
sql="exec yl_tran_perfor_failreason_group " & Trim(Request.QueryString("tranid")) & "," & Trim(Request.QueryString("cityid")) & ",'" & Trim(Request.QueryString("dt")) & "','" & Trim(Request.QueryString("dt2")) & "'"

Set rs=cnnDragon.Execute(sql)
%>
<html>
<head>
<title>Untitled Document</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
</head>

<body bgcolor="#FFFFFF" text="#000000">
<table width="100%" border="0" cellspacing="1" cellpadding="0">
  <tr> 
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td bgcolor="#CCCCCC">
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="45%"><b>失败业务流程原因</b></td>
          <td align="right" width="55%"><b>时段: 
            <%
			'startDate=Request.cookies("rep_datetime")("start")
			'endDate=Request.cookies("rep_datetime")("end")
			startDate=Request.QueryString("dt")
			endDate=Request.QueryString("dt2")
	  If DateDiff("d", DateValue(startDate), DateValue(endDate))=0 Then
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时0分 - " & Hour(endDate) & "时59分"
	  Else
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时0分 - " & Year(endDate) & "年" & Month(endDate) & "月" & Day(endDate) & "日" & Hour(endDate) & "时59分"
	  End If
	  %>
            </b></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr align="center" valign="top"> 
    <td colspan="2" height="41"><br>
      <table width="90%" border="0" cellspacing="1" cellpadding="0" height="39">
        <tr bgcolor="#330066" align="center"> 
          <td height="21" width="33%"><font color="#ffffff">日期时间</font></td>
          <td height="21" width="23%"><font color="#ffffff">业务流程名称</font></td>
          <td height="21" width="16%"><font color="#ffffff">所在城市</font></td>
          <td height="21" width="28%"><font color="#ffffff">具体原因</font></td>
        </tr>
		<%
		Dim i
		If rs.Eof And rs.Bof Then
		Else
			i=1
			While Not rs.Eof
		%>
        <tr bgcolor="<%=arrColor(i mod 2)%>"> 
          <td height="19" align="center" width="33%"><%=rs(4)%>&nbsp;</td>
          <td height="19" align="center" width="23%"><%=rs(1)%>&nbsp;</td>
          <td height="19" align="center" width="16%"><%=rs(2)%>&nbsp;</td>
          <td height="19" width="28%"><%If IsNull(rs(3)) Or Len(rs(3))=0 Then%>未知原因错误<%Else%><%=rs(3)%><%End If%>&nbsp;</td>
        </tr>
		<%
				i=i+1
				rs.MoveNext
			Wend
		End If
		%>
      </table>
      <br>
	  <CENTER><A HREF="javascript:window.close();"><IMG SRC="img/sure.gif" WIDTH="61" HEIGHT="23" BORDER=0 ALT=""></A></CENTER>
    </td>
  </tr>
</table>
</body>
</html>
<!-- #include file="inc/foot.asp" -->
