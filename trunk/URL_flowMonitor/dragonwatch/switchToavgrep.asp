<html>
<HEAD>
<TITLE> 月历式平均响应时间图 </TITLE>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net">
<link rel="stylesheet" href="css.css" type="text/css">
</HEAD>
<body>
<%
'response.write request("time")
'response.write request("group")

Response.Cookies("rep_per")="d"  ' 时间单位：天
Response.Cookies("rep_by")=Request.QueryString("group")  ' 分组方式

Response.cookies("rep_startTime")=Request.QueryString("time")
%>
<CENTER>正在跳转到指定日期的平均响应时间图表，稍候...</CENTER>
<SCRIPT LANGUAGE="JavaScript">
<!--
parent.parent.leftFrame.document.all.t4.click();
parent.parent.leftFrame.document.all.a4.click();
//-->
</SCRIPT>
</body>
</html>
