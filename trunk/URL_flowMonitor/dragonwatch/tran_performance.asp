<%
' ���������������Ӧ��ʱ��
' ѡ��ҵ������ʱ��ҵ������
If Trim(Request.Form("selBy"))="t" Then
	Response.cookies("rep_trans")("id")=""
	Response.cookies("rep_trans")("name")=""
End If
' ѡ�����ʱ�����
If Trim(Request.Form("selBy"))="c" Then
	Response.cookies("rep_city")("id")=""
	Response.cookies("rep_city")("name")=""
End If

'================����ʱ�䴦������getTime.asp�����ļ����д���

'response.write startDate & "<BR>"
'response.write endDate & "<BR>"
'response.write "rep_startDate:" & request.cookies("rep_datetime")("start")&"<BR>"
'response.write "rep_endDate:" & request.cookies("rep_datetime")("end")&"<BR>"
'response.write request.cookies("rep_per")&"<BR>"
'response.write request.cookies("rep_by")&"<BR>"
'response.end

'====================================================================
' ���������ܵĵ���ҵ����������ʱ�ᴫ����tranid+traname��cityid+cityname
' �������ID�����ƣ����ˣ�
If Len(Request.QueryString("cityid"))>0 Then
	Response.cookies("rep_city")("id")=Request.QueryString("cityid")
	Response.cookies("rep_city")("name")=Request.QueryString("cityname")

	Response.cookies("rep_by")="t"  ' ת��ָ��City�Զ��ҵ������
End If
' ����ҵ������ID�����ƣ����ˣ�
If Len(Request.QueryString("tranid"))>0 Then
	Response.cookies("rep_trans")("id")=Request.QueryString("tranid")
	Response.cookies("rep_trans")("name")=Request.QueryString("tranname")

	Response.cookies("rep_by")="c"  ' ת��ָ��Transaction�Զ������
End If
'====================================================================

' *****************************************
' ����ѡ���������������ĸ�ҳ��
' *****************************************
	Select Case Request.cookies("rep_per")
		Case "h" ' Сʱ
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "tran_perfor_n_t.asp"
				Case "c","g"
					Server.Transfer "tran_perfor_n_c.asp"
				'Case "g"
			End Select
		Case "d" ' ��
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "tran_perfor_d_t.asp"
				Case "c","g"
					Server.Transfer "tran_perfor_d_c.asp"
				'Case "g"
			End Select
		Case "w" ' ����
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "tran_perfor_w_t.asp"
				Case "c","g"
					Server.Transfer "tran_perfor_w_c.asp"
				'Case "g"
			End Select
		Case "m" ' ��
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "tran_perfor_m_t.asp"
				Case "c","g"
					Server.Transfer "tran_perfor_m_c.asp"
				'Case "g"
			End Select
		Case "q" ' ����
			Select Case Request.cookies("rep_by")
				Case "t"
					Server.Transfer "tran_perfor_q_t.asp"
				Case "c","g"
					Server.Transfer "tran_perfor_q_c.asp"
				'Case "g"
			End Select
		Case "y" ' ��
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