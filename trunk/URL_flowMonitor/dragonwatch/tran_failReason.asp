<!-- #include file="inc/check.asp" -->
<%
'***************************************
'    根据查询参数,设定cookies的值      *
'***************************************
'For each item in Request.Cookies
'	Response.write Item & " -- " & Request.Cookies(Item) & "<br>"
'Next
'Response.end
if len(request.Querystring("trans_id")) > 0 then
	Response.cookies("rep_trans")("id")  =request.Querystring("trans_id")
	Response.cookies("rep_trans")("name")=request.Querystring("trans_name")
end if
if len(request.Querystring("city_id")) > 0 then
	Response.cookies("rep_city")("id")  =request.Querystring("city_id")
	Response.cookies("rep_city")("name")=request.Querystring("city_name")
end if

bFilteredTran = len(request.cookies("rep_trans")("id"))
bFilteredCity = len(request.cookies("rep_city")("id"))

if bFilteredTran And bFilteredCity then
	response.cookies("rep_by") = "g"
else
	if bFilteredTran then response.cookies("rep_by") = "c"
	if bFilteredCity then response.cookies("rep_by") = "t"
end if
'***************************************

'************************************
'   根据选择条件决定调用哪个页面    *
'************************************
Select Case Request.cookies("rep_by")
	Case "c"
		Server.Transfer "tran_failReason_c.asp"
	Case "g"
		Server.Transfer "tran_failReason_c.asp"
	Case "t"   
		Server.Transfer "tran_failReason_t.asp"
	Case else    't or Empty
'		Server.Transfer "tran_failReason_t.asp"
response.write response.cookies("rep_by")
End Select
' *****************************************

%>
<html>
<head>
<title>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<BR>test
</body>
</html>
