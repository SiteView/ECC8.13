		  <%
		  Dim strFilter
		  If bShowLink Then
			strFilter="过滤：组，" & Request.cookies("rep_trans")("name") & "，" & Request.cookies("rep_city")("name")
		  Else
			If Len(Request.cookies("rep_trans")("name"))>0 Then
				strFilter="过滤：" & getSelBy(Request.cookies("rep_by")) & "，" & Request.cookies("rep_trans")("name")
			ElseIf Len(Request.cookies("rep_city")("name"))>0 Then
				strFilter="过滤：" & getSelBy(Request.cookies("rep_by")) & "，" & Request.cookies("rep_city")("name")
			End If
		  End If
		  %>
		  <%=strFilter%>
