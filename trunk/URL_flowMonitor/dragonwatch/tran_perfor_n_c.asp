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

Dim i,j,k,startDate,endDate,prof_id


'=========================================================
' 如果没有指定 Transaction 编号则要转到没有颜色仅有数值和表里
If Len(Request.cookies("rep_trans")("id"))=0 Then
	Server.Transfer "tran_perfor_n_c_nocolor.asp"
End If
'=========================================================

startDate=Request.cookies("rep_datetime")("start")
endDate=Request.cookies("rep_datetime")("end")

If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

If Len(Request.cookies("rep_trans")("id"))>0 Then
	If Len(Request.cookies("rep_city")("id"))>0 Then ' 组
		' 计算正常
		sql="exec yl_tran_perfor_n_c_withid " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & Request.cookies("rep_city")("id") & "','" & startDate & "','" & endDate & "'"
		' 计算失败
		sql2="exec yl_tran_perfor_n_c_withid_failcount " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & Request.cookies("rep_city")("id") & "','" & startDate & "','" & endDate & "'"
	Else
		' 计算正常
		sql="exec yl_tran_perfor_n_c_tranid " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
		' 计算失败
		sql2="exec yl_tran_perfor_n_c_tranid_failcount " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	' 计算正常
	sql="exec yl_tran_perfor_n_c " & prof_id & ",'" & startDate & "','" & endDate & "'"
	' 计算失败
	sql2="exec yl_tran_perfor_n_c_failcount " & prof_id & ",'" & startDate & "','" & endDate & "'"
End If

'response.write sql & "<BR>"
'response.write sql2 & "<BR>"
Set rs=Server.CreateObject("adodb.recordset")
Set rs2=Server.CreateObject("adodb.recordset")
Set rsV=Server.CreateObject("adodb.recordset")  '　取业务流程中包含的TRANSID或CITYID

rsV.Open "exec yl_profilecitys " & prof_id, cnnDragon, 1, 1

rs.Open sql, cnnDragon, 1, 1  ' 计算各分钟的平均响应时间值，及性能级别
rs2.Open sql2, cnnDragon, 1, 1  ' 计算错误的业务流程在哪个时间发生

' 有可能会出现下面四种情况
' 1　有正常的值，无错误
' 2　有正常的值，有错误
' 3　无正常的值，无错误
' 4　无正常的值，有错误－－此种情况要详细考虑！！！

If rs.Eof And rs.Bof And rs2.Eof And rs2.Bof Then  ' 当RS和RS2都没有数据时才能确定此时段没有数据！
	Response.Write "<Center>此时段没有数据</Center>"
Else
	iCount=rsV.RecordCount ' 结果共多少个 city

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
<table width="200%" border="0" cellspacing="1" cellpadding="0">
  <tr>
    <td width="1%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="199%" bgcolor="#CCCCCC" colspan="2">
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="38%"><b>业务流程性能分析</b></td>
          <td width="62%" align="right"><b>时段:
            <%
	  If DateDiff("d", DateValue(startDate), DateValue(endDate))=0 Then
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时0分 - " & Hour(endDate) & "时0分"
	  Else
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时0分 - " & Year(endDate) & "年" & Month(endDate) & "月" & Day(endDate) & "日" & Hour(endDate) & "时0分"
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
          <td align="center">时段</td>
		  <%
			'Dim theHour=Hour(CDate(startDate))
			For i=0 To 59
				%><td align="center" height="25"><span style="text-decoration:underline"><%If i>9 Then%><%=i%><%Else%><%="0"&i%><%End If%></span></td><%
			Next
		  %>
        </tr>
		<%
		Dim cell()
		Dim url
		If Len(Request.cookies("rep_trans")("id"))>0 Then ' 如果有transid则调用自己
			url="tran_perfor_n_c.asp"
		Else
			url="tran_perfor_n_t.asp"
		End If

		strDateTime=DateValue(startDate) & " " & Hour(TimeValue(startDate)) & ":"

		While Not rsV.Eof
			rs.Filter="cityid=" & rsV(0)  ' 根据城市ID进行过滤正常值记录集
			If bShowLink Then
				Response.Write "<tr align=center><td>" & rsV(1) & "</td>"
			Else
				Response.Write "<tr align=center><td><A class='bluelink' style='text-decoration:underline' HREF='" & url & "?cityid=" & rsV(0) & "&cityname=" & rsV(1) & "'>" & rsV(1) & "</td>"
			End If
			Redim cell(59) 
			For i=0 To 59
				cell(i)="<td style='cursor:hand;'>&nbsp;</td>"
			Next
			While Not rs.Eof
				cell(CInt(rs(2)))="<td style='cursor:hand;' bgcolor='" & arrColor2(CInt(rs(5))) & "'>&nbsp;</td>"
				rs.MoveNext
			Wend

			rs2.Filter="cityid=" & rsV(0)  ' 根据城市ID进行过滤错误值记录集
			While Not rs2.Eof
				theid=CInt(rs2(2))
				cell(theid)=Left(cell(theid),Len(cell(theid))-5) & "<img src='img/error_bit.gif' onClick=" & chr(34) & "failreason(" & Request.cookies("rep_trans")("id") & "," & rsV(0) & ",'" & strDateTime & theid & "')" & chr(34) & ">&nbsp;</td>"
				rs2.MoveNext
			Wend

			Response.Write Join(cell)
			Response.Write "</tr>"
			rsV.MoveNext
			Response.Flush
		Wend
		%>
      </table>
      <br>
    </td>
  </tr>
  <tr>
    <td width="3%" align="center"><A class='bluelink' HREF="#" onclick="javascript:window.open('tran_perfor_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img src="img/lamp.gif" width="22" height="22" border="0"></A></td>
    <td colspan="2"> 用不同颜色代表业务流程平均响应时间和失败的业务流程。 <a class='bluelink' HREF="#" onclick="javascript:window.open('service_okpercent_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">更多...</A> </td>
  </tr>
</table>
</body>
</html>
<%
End If
%>
<!-- #include file="inc/foot.asp" -->
<SCRIPT LANGUAGE="JavaScript">parent.frames.conditionFrame.document.all.selPer.value="h";</SCRIPT>
<SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToCity.js"></SCRIPT>
<%If bShowLink Then%><SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToGroup.js"></SCRIPT><%End If%>
<SCRIPT LANGUAGE="JavaScript">
function failreason(tranid,cityid,dt)
{
	window.open("tran_perfor_failreason.asp?cityid="+cityid+"&tranid="+tranid+"&dt="+dt,"",'toolbar=FALSE,resizable=1,scrollbars=2,height=260,width=700,screenx=550,screeny=300');
}
</SCRIPT>