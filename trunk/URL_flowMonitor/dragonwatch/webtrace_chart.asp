<%
' ������ѡ�ĵ�λ��ת����ͬ��ҳ��
Dim per, url

per=Trim(Request.cookies("rep_per"))

Select Case per
	Case "h" ' Сʱ
		Server.Transfer "webtrace_chart_n.asp"
	Case "d" ' ��
		Server.Transfer "webtrace_chart_d.asp"
	Case "w" ' ����
		Server.Transfer "webtrace_chart_w.asp"
	Case "m" ' ��
		Server.Transfer "webtrace_chart_m.asp"
	Case "q" ' ����
		Server.Transfer "webtrace_chart_q.asp"
	Case "y" ' ��
		Server.Transfer "webtrace_chart_y.asp"
End Select
%>