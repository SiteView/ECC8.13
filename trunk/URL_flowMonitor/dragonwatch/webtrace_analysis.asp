<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
'On Error Resume Next
%>
<html>
<head>
<title>网络路由追踪分析</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
<style type="text/css">
<!--
.webtrace {  font-size: 14.8px; font-weight: bold}
-->
</style>
<SCRIPT LANGUAGE="JavaScript" src="inc/tip.js"></SCRIPT>
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<!-- tip -->
<!-- #include file="inc/tip.asp" -->
<!-- tip -->
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td colspan="2" height="22"><font color="#003399"><span class="webtrace"><font color="#000066">
      </font></span></font><font color="#000066"><span class="webtrace">网络路由追踪分析：<font color="#6E6E6E" size=2>
	  所有城市
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
          <td width="28%" height="22"><b>网络路由追踪分析</b></td>
          <td align="right" width="72%" height="22"><b>时段:
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
  <%
  'On Error Resume Next
  Dim tracetimes, sql, tmprs, tracetimes_unreach

'  Set rsSites=cnnDragon.Execute("exec yl_profiletrans " & Request.cookies("rep_prf")("id"))
'  Set rsSites=cnnDragon.Execute("select id,host from profilehost where profile_id=" & Request.cookies("rep_prf")("id"))
  Set rsSites=cnnDragon.Execute("select id,host from custhost where custid=" & Request.cookies("rep_cust")("id"))
  If rsSites.Eof And rsSites.Bof Then
		' 如果没数据
		'server.transfer "nodata.htm"
		'Response.Write "hello"
  Else
  Set tmprs=Server.CreateObject("adodb.recordset")
  While Not rsSites.Eof
		  ' 计算指定时段内共TRACE了多少次
		  'sql="exec yl_tracetimes " & rsSites(0) & ",'" & startDate & "','" & endDate & "'" 
		  'response.write sql
		  'tmprs.Open sql, cnnDragon, 1, 1
		  'If tmprs.Eof And tmprs.Bof Then
			'	tracetimes=0
		  'Else
		'		tracetimes=CInt(tmprs.RecordCount)
		  'End If
		  'tmprs.close

		  ' 计算指定时段内TRACE了次数中有几次 unreach 的
		  'sql="exec yl_tracetimes_unreach " & rsSites(0) & ",'" & startDate & "','" & endDate & "'" 
		  'response.write sql
		  'tmprs.Open sql, cnnDragon, 1, 1
		  'If tmprs.Eof And tmprs.Bof Then
			'	tracetimes_unreach=0
		  'Else
			'	tracetimes_unreach=CInt(tmprs.RecordCount)
		  'End If
		  'tmprs.close
  %>
  <!-- 循环列出监测的站点 -->
  <tr align="center"> 
		<%
		'////////////////////////////////////////////////////////////////////////////////////////////
		' 取 WEBTRACE 的测试结果
		'////////////////////////////////////////////////////////////////////////////////////////////
		Dim iMax, iAvg, rs, arrError, iErrorRows, iError, arrUnreach, iUnreachRows, iUnreach

		Set rserror=Server.CreateObject("adodb.recordset")
		Set rsunreach=Server.CreateObject("adodb.recordset")
		' 计算WEBTRACE各个参数值
		sql="exec yl_webtrace " & Request.cookies("rep_prf")("id") & "," & rsSites(0) & ",'" & startDate & "','" & endDate & "'"
		' 计算TRACE中ERROR的个数
		sqlerror="exec yl_webtrace_error " & Request.cookies("rep_prf")("id") & "," & rsSites(0) & ",'" & startDate & "','" & endDate & "'"
		' 计算TRACE中unreachable的个数
		sqlunreach="exec yl_webtrace_unreach " & Request.cookies("rep_prf")("id") & "," & rsSites(0) & ",'" & startDate & "','" & endDate & "'"

		rserror.Open sqlerror, cnnDragon, 1, 1
		rsunreach.Open sqlunreach, cnnDragon, 1, 1

		If rserror.Eof And rserror.Bof Then  ' 如果没有错误，循环变量为零
			iErrorRows=-1
		Else
			arrError=rserror.GetRows(rserror.RecordCount)  ' 取所有错误记录到数组
			iErrorRows=UBound(arrError,2)	' 计算错误有多少行
		End If

		If rsunreach.Eof And rsunreach.Bof Then  ' 如果没有unreach，循环变量为零
			iUnreachRows=-1
		Else
			arrUnreach=rsunreach.GetRows(rsunreach.RecordCount)  ' 取所有unreach记录到数组
			iUnreachRows=UBound(arrUnreach,2)	' 计算unreach有多少行
		End If
		
		Set rserror=Nothing
		Set rsunreach=Nothing
		'response.write sql & "<HR>"
		Set rs=cnnDragon.Execute(sql)
		If rs.Eof And rs.Bof Then
			Response.Write "<td colspan=2 align=center>没有数据</td>"
		Else
		%>
    <td colspan="2"><br><b>所有城市到 <%=rsSites(1)%></b><br>
      <br>
      <table width="97%" border="1" cellspacing="0" cellpadding="2">
        <tr align="center" bgcolor="#CCCCCC"> 
          <td height="17" width="13%">城市</td>
          <td height="17" width="18%"><font color="#000000">主机名</font></td>
          <td height="17" width="32%"><font color="#000000"><img src="img/darkblue.gif" height=13 width=8>平均DNS时间（毫秒） 
            <img src="img/lightblue.gif" height=13 width=8>平均路由时间（毫秒）</font></td>
          <td height="17" width="9%"><font color="#000000">最大值</font></td>
          <td height="17" width="9%"><font color="#000000">平均结点数</font></td>
          <td height="17" width="7%"><font color="#FF0000">错误数</font></td>
          <td height="17" width="12%"><font color="#FF0000">不可达/总次数</font></td>
        </tr>
		<%
			Do While Not rs.Eof

			' 计算trace总次数
  		  sql="exec yl_tracetimes '" & rs(10) & "'," & rsSites(0) & "," & rs(11) & ",'" & startDate & "','" & endDate & "'" 
		  tmprs.Open sql, cnnDragon, 1, 1
		  If tmprs.Eof and tmprs.Bof Then
			tracetimes=0
		  Else
			tracetimes=tmprs.RecordCount
		  End If
		  tmprs.close
		  
			' 计算trace中unreach总次数
  		  sql="exec yl_tracetimes_unreach '" & rs(10) & "'," & rsSites(0) & "," & rs(11) & ",'" & startDate & "','" & endDate & "'" 
		  tmprs.Open sql, cnnDragon, 1, 1
		  If tmprs.Eof and tmprs.Bof Then
			tracetimes_unreach=0
		  Else
			tracetimes_unreach=tmprs.RecordCount
		  End If
		  tmprs.close
		%>
        <tr> 
          <td width="13%" align="center"><a href="webtrace_chart.asp?tranid=<%=rsSites(0)%>&tranname=<%=rsSites(1)%>&cityid=<%=rs(11)%>&cityname=<%=rs(1)%>"><%=rs(1)%></a></td>
          <td width="18%" align="center"><%=rs(10)%></td>
		  <%
		  iAvg=CInt(rs(3))
		  If CInt(rs(4))>iAvg Then iAvg=CInt(rs(4))
		  If CInt(rs(5))>iAvg Then iAvg=CInt(rs(5))
		  %>
          <td width="32%"><img src="img/darkblue.gif" height=13 width=<%=CInt(80*(CInt(rs(2))/100))%>><img src="img/lightblue.gif" height=13 width=<%=CInt(80*(iAvg/100))%>  style="cursor:hand;" onMouseOver="showtip(0,this,event,'平均路由时间：<%=iAvg%> 毫秒，平均DNS时间：<%=CInt(rs(2))%> 毫秒')" onMouseOut="hidetip()">
		  <%
		  If iAvg<10 Then
			Response.Write "<10"
		  Else
			Response.Write iAvg
		  End If
		  %>&nbsp;</td>
		  <%
		  iMax=CInt(rs(6))
		  If CInt(rs(7))>iMax Then iMax=CInt(rs(7))
		  If CInt(rs(8))>iMax Then iMax=CInt(rs(8))
		  %>
          <td width="9%" align="center"><%=iMax%></td>
          <td width="9%" align="center"><%=rs(9)\tracetimes%></td>
          <td width="7%" align="center">
		  <%
		  ' 打印错误个数
		  iError=0
		  For i=0 To iErrorRows
			If Trim(rs(1))=Trim(arrError(1,i)) Then
				iError=arrError(2,i)
				Exit For
			End If
		  Next
		  Response.Write iError
		  %>
		  </td>
          <td width="12%" align="center">
		  <%
		  ' 打印 unreach 的个数
		  'iUnreach=0
		  'For i=0 To iUnreachRows
			'If Trim(rs(1))=Trim(arrUnreach(1,i)) Then
			'	iUnreach=arrUnreach(2,i)
			'	Exit For
			'End If
		  'Next
		  'Response.Write iUnreach
		  Response.Write tracetimes_unreach
		  %>
		  /<%=tracetimes%></td>
        </tr>
		<%
				rs.MoveNext
			Loop
		%>
      </table>
      <br>
    </td>
	<%End If%>
  </tr>
  <%
	rsSites.MoveNext
  Wend
  End If
  %>
  <!-- 循环列出监测的站点（结束） -->
</table>
</body>
</html>
<%
Set rs=Nothing
%>
<!-- #include file="inc/foot.asp" -->
