<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<html>
<head>
<title>网络路由追踪分析</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
<SCRIPT LANGUAGE="JavaScript" src="inc/tip.js"></SCRIPT>
<style type="text/css">
<!--
.webtrace {  font-size: 14.8px; font-weight: bold}
-->
</style>
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<!-- tip -->
<!-- #include file="inc/tip.asp" -->
<!-- tip -->
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td colspan="2" height="22"><font color="#003399"><span class="webtrace"><font color="#000066">
      </font></span></font><font color="#000066"><span class="webtrace">网络路由追踪分析：<font color="#6E6E6E" size=2>
	  从<%=Request.QueryString("cityname")%>到<%=Request.QueryString("tranname")%>所在主机
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
            </b>&nbsp;</td>
        </tr>
      </table>
    </td>
  </tr>
  <!-- 取WEBTRACE按时间列表的结果 -->
  <%
  'on error resume next
  Dim i, j, iError, sql, rs, arrErr, iErrRows, iAvg, iPage, strQueryString
  
  sql="exec yl_webtrace_bytime_error " & Request.QueryString("tranid") & ", " & Request.QueryString("cityid") & ",'" & startDate & "','" & endDate & "'"
  'response.write sql
  Set rs=Server.CreateObject("adodb.recordset")
  rs.Open sql, cnnDragon, 1, 1  '  计算WEBTRACE错误个数
  If rs.Eof And rs.Bof Then
		iErrRows=-1
  Else
		arrErr=rs.GetRows(rs.RecordCount)
		iErrRows=UBound(arrErr,2)
  End If

  rs.close

  ' 分页
  If Len(Request("page"))=0 Then
		iPage=1
  Else
		iPage=CInt(Request("page"))
  End If

  ' 取WEBTRACE按时间排序的结果
  sql="exec yl_webtrace_bytime " & Request.QueryString("tranid") & ", " & Request.QueryString("cityid") & ",'" & startDate & "','" & endDate & "'"
  rs.Open sql, cnnDragon, 1, 1

  If rs.Bof And rs.Eof Then
  Else
		rs.PageSize=20
		rs.AbsolutePage=iPage
  %>
  <tr align="center"> 
    <td colspan="2"><br>
	<%
		strQueryString="&tranid=" & Request.QueryString("tranid") & "&tranname=" & Request.QueryString("tranname") & "&cityid=" & Request.QueryString("cityid") & "&cityname=" & Request.QueryString("cityname")
		Response.Write "[<A HREF='webtrace_detail_d.asp?page=1" & strQueryString & "'>首页</A>] "
		If iPage>1 Then
			Response.Write "[<A HREF='webtrace_detail_d.asp?page=" & iPage-1 & strQueryString &"'>上页</A>] "
		Else
			Response.Write "[<font color='#cccccc'>上页</font>] "
		End If
		If iPage<rs.PageCount Then
			Response.Write "[<A HREF='webtrace_detail_d.asp?page=" & iPage+1 & strQueryString & "'>下页</A>] "
		Else
			Response.Write "[<font color='#cccccc'>上页</font>] "
		End If
		Response.Write "[<A HREF='webtrace_detail_d.asp?page=" & rs.PageCount & strQueryString &"'>尾页</A>]"
	%>
      <table width="95%" border="1" cellspacing="0" cellpadding="2">
        <tr align="center" bgcolor="#CCCCCC"> 
          <td height="17" width="19%">测试时间<font color="#000000"></font></td>
          <td height="17" width="46%"><font color="#000000"><img src="img/darkblue.gif" height=13 width=8>平均DNS时间（毫秒） 
            <img src="img/lightblue.gif" height=13 width=8>平均路由时间（毫秒）</font></td>
          <td height="17" width="17%"><font color="#FF0000">错误数</font></td>
          <td height="17" width="18%"><font color="#000000">结点数</font></td>
        </tr>
		<%
		For i=1 To rs.PageSize
			If rs.Eof Then Exit For
		'While Not rs.Eof
		%>
        <tr> 
          <td align="center" width="19%"><a href="javascript:webtracedetail('<%=rs(0)%>')">
		  <%=rs(0)%>
		  </a></td>
		  <%
		  iAvg=CInt(rs(2))
		  If CInt(rs(3))>iAvg Then iAvg=CInt(rs(3))
		  If CInt(rs(4))>iAvg Then iAvg=CInt(rs(4))
		  %>
          <td width="46%"><img src="img/darkblue.gif" height=13 width=<%=CInt(80*(CInt(rs(1))/100))%>><img src="img/lightblue.gif" height=13 width=<%=CInt(80*(iAvg/100))%> style="cursor:hand;" onMouseOver="showtip(0,this,event,'平均路由时间：<%=iAvg%> 毫秒，平均DNS时间：<%=CInt(rs(1))%> 毫秒')" onMouseOut="hidetip()">
		  <%
		  If iAvg<10 Then
			Response.Write "<10"
		  Else
			Response.Write iAvg
		  End If
		  %>&nbsp;</td>
          <td align="center" width="17%">
		  <%
		  iError=0
		  'Response.write iErrRows & "<BR>" & rs(0) & "<BR>"
		  For j=0 To iErrRows
				If rs(0)=arrErr(0,j) Then
					iError=arrErr(8,j)
					Exit For
				End If
		  Next
		  Response.Write iError
		  %>
		  </td>
          <td align="center" width="18%"><%=rs(8)%></td>
        </tr>
		<%
			rs.MoveNext
		'Wend
		Next
		%>
      </table>
      <br>
    </td>
  </tr>
  <%End If%>
  <!-- 取WEBTRACE按时间列表的结果 -->
</table>
</body>
</html>
<%
Set rs=Nothing
%>
<!-- #include file="inc/foot.asp" -->

<SCRIPT LANGUAGE="JavaScript">
function webtracedetail(strtime)
{
	window.open("webtrace_detail.asp?mtime="+strtime+"&tranid=<%=Request.QueryString("tranid")%>&tranname=<%=Request.QueryString("tranname")%>&cityid=<%=Request.QueryString("cityid")%>&cityname=<%=Request.QueryString("cityname")%>","",'toolbar=FALSE,resizable=1,scrollbars=2,height=360,width=700,screenx=550,screeny=300');
}

// 以下代码WEBTRACE用到
var x=parent.frames.conditionFrame.document;
x.all.hostid.value="<%=Request.QueryString("tranid")%>";
x.all.hostname.value="<%=Request.QueryString("tranname")%>";
x.all.cityid.value="<%=Request.QueryString("cityid")%>";
x.all.cityname.value="<%=Request.QueryString("cityname")%>";
x.frmCondition.action="webtrace_detail_d.asp";
</SCRIPT>
