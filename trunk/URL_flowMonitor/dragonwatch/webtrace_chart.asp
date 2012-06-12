<%
' 根据所选的单位跳转到不同的页面
Dim per, url

per=Trim(Request.cookies("rep_per"))

Select Case per
	Case "h" ' 小时
		Server.Transfer "webtrace_chart_n.asp"
	Case "d" ' 天
		Server.Transfer "webtrace_chart_d.asp"
	Case "w" ' 星期
		Server.Transfer "webtrace_chart_w.asp"
	Case "m" ' 月
		Server.Transfer "webtrace_chart_m.asp"
	Case "q" ' 季度
		Server.Transfer "webtrace_chart_q.asp"
	Case "y" ' 年
		Server.Transfer "webtrace_chart_y.asp"
End Select
%>