<%
Dim cnnDragon
Set cnnDragon=Server.CreateObject("adodb.connection")
cnnDragon.open "Provider=sqloledb;UID=dragon;PWD=*7EdY#;database=newtest;"

Dim arrColor(2)
arrColor(0)="#EFEFDD"
arrColor(1)="#CCCC99"

Dim arrColor2(4)
arrColor2(0)="#ffffff"
arrColor2(1)="#009e63"
arrColor2(2)="ffcf00"
arrColor2(3)="ce0000"
arrColor2(4)="#ffffff"

'If Len(Request.ServerVariables("SCRIPT_NAME"))>0 And Request.ServerVariables("REMOTE_ADDR")<>"210.12.66.98" 'Then
'If Len(Request.ServerVariables("SCRIPT_NAME"))>0 Then
'	sql="insert into pagevisit values('" & Request.ServerVariables("SCRIPT_NAME") & "',getdate(),'" & 'Request.Cookies("rep_cust")("name") & "','" & Request.ServerVariables("REMOTE_ADDR") & "','" & 'Request.ServerVariables("HTTP_USER_AGENT") & "')"
'	cnnDragon.Execute sql
'End If
%>