<%
If Len(Request.cookies("visit"))=0 Then
	Response.Write "<center>请您登录！</center><BR>"
	Response.Write "<center><input type=button value='登录' onClick='location.href=""logout.asp""'></center><BR>"
	Response.End
End If

Sub fnD(str)
	Response.Write str
	Response.End
End Sub

Function getSelBy(str)
	Select Case str
		Case "t"
			getSelBy="业务流程"
		Case "c"
			getSelBy="城市"
		Case "g"
			getSelBy="城市"
	End Select
End Function

Function tripLast(str)
	str=Trim(str)
	If Len(str)>=1 Then tripLast=Left(str,Len(str)-1)
End Function 
%>