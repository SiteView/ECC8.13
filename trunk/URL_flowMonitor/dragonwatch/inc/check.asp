<%
If Len(Request.cookies("visit"))=0 Then
	Response.Write "<center>������¼��</center><BR>"
	Response.Write "<center><input type=button value='��¼' onClick='location.href=""logout.asp""'></center><BR>"
	Response.End
End If

Sub fnD(str)
	Response.Write str
	Response.End
End Sub

Function getSelBy(str)
	Select Case str
		Case "t"
			getSelBy="ҵ������"
		Case "c"
			getSelBy="����"
		Case "g"
			getSelBy="����"
	End Select
End Function

Function tripLast(str)
	str=Trim(str)
	If Len(str)>=1 Then tripLast=Left(str,Len(str)-1)
End Function 
%>