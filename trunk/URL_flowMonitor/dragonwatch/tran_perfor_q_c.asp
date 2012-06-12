<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
On Error Resume Next
' 保存业务流程ID和名称（过滤）
If Len(Request.QueryString("tranid"))>0 Then
	Response.cookies("rep_trans")("id")=Request.QueryString("tranid")
	Response.cookies("rep_trans")("name")=Request.QueryString("tranname")
End If
' 保存城市ID和名称（过滤）
If Len(Request.QueryString("cityid"))>0 Then
	Response.cookies("rep_city")("id")=Request.QueryString("cityid")
	Response.cookies("rep_city")("name")=Request.QueryString("cityname")
End If

Response.cookies("rep_by")="c"

Dim i,j,k,startDate,endDate,prof_id,xStart,xEnd


'=========================================================
' 如果没有指定 Transaction 编号则要转到没有颜色仅有数值和表里
If Len(Request.cookies("rep_trans")("id"))=0 Then
	Server.Transfer "tran_perfor_q_c_nocolor.asp"
End If
'=========================================================

startDate=Request.cookies("rep_datetime")("start")
endDate=Request.cookies("rep_datetime")("end")

xStart=DatePart("ww", DateValue(startDate))
xEnd=DatePart("ww", DateValue(endDate))

If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

If Len(Request.cookies("rep_trans")("id"))>0 Then
	If Len(Request.cookies("rep_city")("id"))>0 Then ' 组
		' 计算正常
		sql="exec yl_tran_perfor_q_c_withid " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & Request.cookies("rep_city")("id") & "','" & startDate & "','" & endDate & "'"
		' 计算失败
		sql2="exec yl_tran_perfor_q_c_withid_failcount " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & Request.cookies("rep_city")("id") & "','" & startDate & "','" & endDate & "'"
	Else
		' 计算正常
		sql="exec yl_tran_perfor_q_c_tranid " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
		' 计算失败
		sql2="exec yl_tran_perfor_q_c_tranid_failcount " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	' 计算正常
	sql="exec yl_tran_perfor_q_c " & prof_id & ",'" & startDate & "','" & endDate & "'"
	' 计算失败
	sql2="exec yl_tran_perfor_q_c_failcount " & prof_id & ",'" & startDate & "','" & endDate & "'"
End If
'response.write sql & "<BR>"
Set rs=Server.CreateObject("adodb.recordset")
Set rs2=Server.CreateObject("adodb.recordset")

rs.Open sql, cnnDragon, 1, 1
If rs.Eof And rs.Bof Then
	Response.Write "<Center>此时段没有数据</Center>"
Else

	Dim strID
	Dim strName
	Dim iRsCols, iRsRows, iRsCols2, iRsRows2
	Dim arrRs, arrRs2

	rs2.Open sql2, cnnDragon, 1, 1
	If rs2.Eof And rs2.Bof Then
	Else
		arrRs2=rs2.GetRows(rs.RecordCount)   ' 把记录集的结果存入数组
		rs2.Close
		Set rs2=Nothing
	End If

	arrRs=rs.GetRows(rs.RecordCount)   ' 把记录集的结果存入数组
	rs.Close
	Set rs=Nothing

	iRsCols=UBound(arrRs) ' 有多少字段
	iRsRows=UBound(arrRs,2) ' 有多少行数据
	iRsRows2=UBound(arrRs2,2) ' 失败结果集有多少行

	' 计算业务流程ID，名称，数据线最大值
	oldid=0
	For i=0 To iRsRows
		If oldid<>CInt(arrRs(1,i)) Then
			strID=strID & arrRs(1,i) & ","
			strName=strName & arrRs(0,i) & ","
			oldid=CInt(arrRs(1,i))
		End If
	Next
	arrID=Split(strID, ",")
	arrName=Split(strName, ",")

	iCount=UBound(arrID)-1 ' 结果共多少个 Transaction

	bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)
%>
<html>
<head>
<title>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
<SCRIPT LANGUAGE="JavaScript" src="inc/tip.js"></SCRIPT>
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<!-- tip -->
<!-- #include file="inc/tip.asp" -->
<!-- tip -->
<table width="100%" border="0" cellspacing="1" cellpadding="0">
  <tr>
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td bgcolor="#CCCCCC" colspan="2">
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="38%"><b>业务流程性能分析</b></td>
          <td width="62%" align="right"><b>时段:
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
    <td colspan="2" height="11">&nbsp;</td>
    <td width="20%" height="11">&nbsp;</td>
  </tr>
  <tr>
    <td colspan="2" height="18">
      <p><b>当前预定义文件：<%=Request.cookies("rep_prf")("name")%><br>
		  <!-- #include file="inc/filter.asp" -->
		</b></p>
    </td>
    <td width="20%" height="18" align="right">
      <table border="0" cellspacing="1" cellpadding="0" width="151">
        <tr>
          <td width="108" align="center">好</td>
          <td width="40"><img src="img/green_dot.gif" width="8" height="8"></td>
        </tr>
        <tr>
          <td width="108" align="center">警告</td>
          <td width="40"><img src="img/yellow_dot.gif" width="8" height="8"></td>
        </tr>
        <tr>
          <td width="108" align="center">坏</td>
          <td width="40"><img src="img/red_dot.gif" width="8" height="8"></td>
        </tr>
        <tr>
          <td width="108" align="center">失败（一个或多个）</td>
          <td width="40"><img src="img/error_bit.gif" width="9" height="9"></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td colspan="3">
      <table width="100%" border="1" cellspacing="0" cellpadding="0">
        <tr>
          <td width="15%" align="center">时段</td>

		  <%
			Dim t,arrQueryString()
			Redim arrQueryString(xEnd-xStart+1)
			t=DateValue(startDate)
			For i=xStart To xEnd
				arrQueryString(xEnd-i)="per=w&d="&t&" 00:00"&"&s=" & t & " 00:00" & "&e=" & DateAdd("d",6,t) & " 23:59"
				%><td align="center" height="25" style="cursor:hand;"><A class='bluelink' HREF="tran_perfor_w_t.asp?<%=arrQueryString(xEnd-i)%>" style="text-decoration:underline"><%=Month(t)&"/"&Day(t)%></td></A><%
				t=DateAdd("d",7,t)
			Next
		  %>
        </tr>
		<%
		'==================
		' 把数据分入多个数组
		Dim failcount,status,avgTime,okCount
		ReDim arrTime(iCount,xEnd)
		ReDim arrTime2(iCount,xEnd)
		ReDim arrCount(iCount,xEnd)
		Redim arrCount2(iCount,xEnd)
		ReDim arrStatus(iCount,xEnd)

		failcount=0
		avgTime=0
		okCount=0
		status=0
		oldid=0
		j=0
		For i=0 To iRsRows
			If oldid<>CInt(arrRs(1,i)) Then
				j=j+1
				oldid=CInt(arrRs(1,i))
				For k=0 To iRsRows2
					If arrRs(1,i)=arrRs2(1,k) Then
						arrTime2(j-1,arrRs2(2,k))=arrRs2(3,k)
						arrCount2(j-1,arrRs2(2,k))=arrRs2(4,k)
					End If
				Next
			End If
			arrTime(j-1,CInt(arrRs(2,i)))=arrRs(3,i)
			arrCount(j-1,CInt(arrRs(2,i)))=arrRs(4,i)
			arrStatus(j-1,CInt(arrRs(2,i)))=arrRs(5,i)
		Next
		'==================
		Dim url
		If Len(Request.cookies("rep_trans")("id"))>0 Then ' 如果有transid则调用自己
			url="tran_perfor_q_c.asp"
		Else
			url="tran_perfor_q_t.asp"
		End If
		For i=0 To iCount
		%>
        <tr>
		<%If bShowLink Then%>
          <td width="15%" height="30" align="center"><%=arrName(i)%></td>
		<%Else%>
          <td width="15%" height="30" align="center"><A class='bluelink' style="text-decoration:underline" HREF="<%=url%>?cityid=<%=arrID(i)%>&cityname=<%=arrName(i)%>"><%=arrName(i)%></A>&nbsp;</td>
		<%End If%>
		  <%
			t=DateValue(startDate)
			For j=xStart To xEnd
				If Len(arrCount2(i,j))>0 Then
					failcount=arrCount2(i,j)
				Else
					failcount=0
				End If
				If Len(arrStatus(i,j))>0 Then
					status=arrStatus(i,j)
				Else
					status=0
				End If
				If Len(arrTime(i,j))>0 Then
					avgTime=arrTime(i,j)
				Else
					avgTime=0
				End If
				If Len(arrCount(i,j))>0 Then
					okCount=arrCount(i,j)
				Else
					okCount=0
				End If

				If bShowLink Then
				%>
				<td bgcolor="<%=arrColor2(status)%>" align="center" style="cursor:hand;" onMouseOver="showtip(<%=status%>,this,event,'平均响应时间：<%=avgTime%> 秒，完成 <%=okCount%> 个业务流程<BR>失败 <%=failcount%> 个业务流程')" onMouseOut="hidetip()">
				&nbsp;<%If Len(arrTime2(i,j))>0 Then%><img src="img/error_bit.gif" onClick="failreason(<%=Request.cookies("rep_trans")("id")%>,<%=Request.cookies("rep_city")("id")%>,'<%=t & " 00:00"%>','<%=DateAdd("d",6,t) & " 23:59"%>')"><%Else%>&nbsp;&nbsp;<%End If%>&nbsp;
				</td>
				<%
				Else
				%>
				<td onClick="location.href='tran_perfor_w_t.asp?cityid=<%=arrID(i)%>&cityname=<%=arrName(i)%>&<%=arrQueryString(xEnd-j)%>'" bgcolor="<%=arrColor2(status)%>" align="center" style="cursor:hand;" onMouseOver="showtip(<%=status%>,this,event,'平均响应时间：<%=avgTime%> 秒，完成 <%=okCount%> 个业务流程<BR>失败 <%=failcount%> 个业务流程')" onMouseOut="hidetip()">
				&nbsp;<%If Len(arrTime2(i,j))>0 Then%><img src="img/error_bit.gif"><%Else%>&nbsp;&nbsp;<%End If%>&nbsp;
				</td>
				<%
				End If

				t=DateAdd("d",7,t)
			Next
		  %>
        </tr>
		<%Next%>
      </table>
      <br>
    </td>
  </tr>
  <tr>
    <td width="3%" align="center"><A class='bluelink' HREF="#" onclick="javascript:window.open('tran_perfor_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img src="img/lamp.gif" width="22" height="22" border="0"></A></td>
    <td colspan="2"> 用不同颜色代表业务流程平均响应时间和失败的业务流程。 <A class='bluelink' HREF="#" onclick="javascript:window.open('tran_perfor_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">更多...</A> </td>
  </tr>
</table>
</body>
</html>
<%
End If
%>
<!-- #include file="inc/foot.asp" -->
<SCRIPT LANGUAGE="JavaScript">parent.frames.conditionFrame.document.all.selPer.value="q";</SCRIPT>
<SCRIPT LANGUAGE="JavaScript" src="inc/failreason.js"></SCRIPT>
<SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToCity.js"></SCRIPT>
<%If bShowLink Then%><SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToGroup.js"></SCRIPT><%End If%>
