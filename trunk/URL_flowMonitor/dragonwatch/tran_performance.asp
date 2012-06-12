<%
' 清除过滤条件（点应用时）
' 选择业务流程时清业务流程
If Trim(Request.Form("selBy"))="t" Then
	Response.cookies("rep_trans")("id")=""
	Response.cookies("rep_trans")("name")=""
End If
' 选择城市时清城市
If Trim(Request.Form("selBy"))="c" Then
	Response.cookies("rep_city")("id")=""
	Response.cookies("rep_city")("name")=""
End If

'================日期时间处理部分由getTime.asp包含文件进行处理

'response.write startDate & "<BR>"
'response.write endDate & "<BR>"
'response.write "rep_startDate:" & request.cookies("rep_datetime")("start")&"<BR>"
'response.write "rep_endDate:" & request.cookies("rep_datetime")("end")&"<BR>"
'response.write request.cookies("rep_per")&"<BR>"
'response.write request.cookies("rep_by")&"<BR>"
'response.end

'====================================================================
' 从整体性能的调用业务流程性能时会传过来tranid+traname或cityid+cityname
' 保存城市ID和名称（过滤）
If Len(Request.QueryString("cityid"))>0 Then
	Response.cookies("rep_city")("id")=Request.QueryString("cityid")
	Response.cookies("rep_city")("name")=Request.QueryString("cityname")

	Response.cookies("rep_by")="t"  ' 转到指定City对多个业务流程
End If
' 保存业务流程ID和名称（过滤）
If Len(Request.QueryString("tranid"))>0 Then
	Response.cookies("rep_trans")("id")=Request.QueryString("tranid")
	Response.cookies("rep_trans")("name")=Request.QueryString("tranname")

	Response.cookies("rep_by")="c"  ' 转到指定Transaction对多个城市
End If
'====================================================================

' *****************************************
' 根据选择条件决定调用哪个页面
' *****************************************
	Select Case Request.cookies("rep_per")
		Case "h" ' 小时
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "tran_perfor_n_t.asp"
				Case "c","g"
					Server.Transfer "tran_perfor_n_c.asp"
				'Case "g"
			End Select
		Case "d" ' 天
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "tran_perfor_d_t.asp"
				Case "c","g"
					Server.Transfer "tran_perfor_d_c.asp"
				'Case "g"
			End Select
		Case "w" ' 星期
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "tran_perfor_w_t.asp"
				Case "c","g"
					Server.Transfer "tran_perfor_w_c.asp"
				'Case "g"
			End Select
		Case "m" ' 月
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "tran_perfor_m_t.asp"
				Case "c","g"
					Server.Transfer "tran_perfor_m_c.asp"
				'Case "g"
			End Select
		Case "q" ' 季度
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "tran_perfor_q_t.asp"
				Case "c","g"
					Server.Transfer "tran_perfor_q_c.asp"
				'Case "g"
			End Select
		Case "y" ' 年
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "tran_perfor_y_t.asp"
				Case "c","g"
					Server.Transfer "tran_perfor_y_c.asp"
				'Case "g"
			End Select
	End Select
' *****************************************
%>