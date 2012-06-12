<!--#Include file="inc/getTime.asp"-->
<%
''***************************************
'    根据查询参数,设定cookies的值      *
'***************************************
if len(request.Querystring("transid")) > 0 then
	Response.cookies("rep_trans")("id")  =request.Querystring("transid")
	Response.cookies("rep_trans")("name")=request.Querystring("transname")
end if
if len(request.Querystring("cityid")) > 0 then
	Response.cookies("rep_city")("id")  =request.Querystring("cityid")
	Response.cookies("rep_city")("name")=request.Querystring("cityname")
end if

bFilteredTran = len(request.cookies("rep_trans")("id"))
bFilteredCity = len(request.cookies("rep_city")("id"))
if bFilteredTran > 0 And bFilteredCity > 0 then bShowLink = true

'if bShowLink then
'	response.cookies("rep_by") = "g"
'else
'	if bFilteredTran > 0 then response.cookies("rep_by") = "c"
'	if bFilteredCity > 0 then response.cookies("rep_by") = "t"
'end if
'***************************************
'response.write Request.cookies("rep_by") & Len(Request.cookies("rep_by"))
'response.end
'************************************
'   根据选择条件决定调用哪个页面    *
'************************************
Select Case Request.cookies("rep_by")
	Case "c"
		Server.Transfer "error_analysis_c.asp"
	Case "t"
		Server.Transfer "error_analysis_t.asp"
	Case "g"    'error
		Server.Transfer "error_analysis_e.asp"
End Select
' *****************************************
%>
