<!-- #include file="inc/check.asp" -->
<html>
<head>
<title>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
</head>
<%
' 清除一些COOKIE值
'Response.cookies("rep_per")=""
'Response.cookies("rep_by")=""
'Response.cookies("rep_datetime")("start")=""
'Response.cookies("rep_datetime")("end")=""
'Response.cookies("rep_isdatatable")=""
'Response.cookies("rep_trans")("id")=""
'Response.cookies("rep_trans")("name")=""
'Response.cookies("rep_city")("id")=""
'Response.cookies("rep_city")("name")=""
strUserClicked=request.QueryString("n")
If Len(request.QueryString("n"))=0 Then
	strUserClicked=request.QueryString("oldaction")
End If
strN=request.cookies("curr_link")

if len(strN)=0 then 'Cookies丢失
	strN="rep_avg_d.asp"
	response.cookies("curr_link")=strN
else 'Cookies存在
	if len(strUserClicked) > 0 And strN <> strUserClicked then '保证用户单击了不同的链接
		strN=strUserClicked
		response.cookies("curr_link")=strN
	end if
end if
'------------从组提交到City或Tran时,清除对应的cookies--------
'必须保证必须是用户单击"应用"时才执行
if Len(Request.QueryString("clearcitytran")) > 0 then
	if Len(Request.cookies("rep_city")("id")) And Request.QueryString("selby")="c" then
		Response.cookies("rep_city")("id") = ""
		Response.cookies("rep_city")("name") = ""
	end if
	if Len(Request.cookies("rep_trans")("id")) And Request.QueryString("selby")="t" then
		Response.cookies("rep_trans")("id") = ""
		Response.cookies("rep_trans")("name") = ""
	end if
	if Len(request.QueryString("selBy"))> 0 then
		response.cookies("rep_by") = request.QueryString("selBy")
	end if
	if Len(request.QueryString("selPer"))> 0 then
		response.cookies("rep_per") = request.QueryString("selPer")
	end if
	if Len(request.QueryString("starttime"))> 0 then
		response.cookies("rep_startTime") = request.QueryString("startTime")
	end if
end if

%>
<frameset rows="26,*" frameborder="NO" border="0" framespacing="0" cols="*"> 
  <frame name="conditionFrame" scrolling="yes" noresize src="condition.asp?n=<%=strN%>" >
  <frame name="reportFrame" scrolling="yes" src="<%=strN%>">
</frameset>
<noframes> 
<body bgcolor="#FFFFFF" text="#000000">
</body>
</noframes> 
</html>

