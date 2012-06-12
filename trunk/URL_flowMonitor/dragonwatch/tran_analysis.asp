<!--#Include file="inc/getTime.asp"-->
<%
'***************************************
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

Select Case Request.Querystring("showas")
	Case "table"
		Response.cookies("rep_isdatatable")="_data"
	Case "graph"
		Response.cookies("rep_isdatatable")=""
	Case else
		''Do thing
End Select

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
		Server.Transfer "tran_analysis_c" & Request.cookies("rep_isdatatable") & ".asp"
	Case "g"
		Server.Transfer "tran_analysis_g" & Request.cookies("rep_isdatatable") & ".asp"
	Case else    't or Empty
		Server.Transfer "tran_analysis_t" & Request.cookies("rep_isdatatable") & ".asp"
End Select
' *****************************************
%>

