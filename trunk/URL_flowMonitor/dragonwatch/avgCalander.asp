<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
On Error Resume Next
Dim dDate

dDate=DateValue(request.cookies("rep_starttime"))

If Err.Number<>0 Then dDate=Date

strQueryString="?profileid=" & Request.cookies("rep_prf")("id") & "&yy=" & Year(dDate) & "&mm=" & Month(dDate) & "&dd=" & Day(dDate)

'Response.Write strQueryString & "<HR>"

'Response.Write Request.cookies("rep_by")

If  Request.cookies("rep_by")="c" Then
%>
	<SCRIPT LANGUAGE="JavaScript">
	<!--
	location.href="avgCalander.php<%=strQueryString & "&show=c"%>";
	//-->
	</SCRIPT>
<%	'response.write "城市"
	' Server.Transfer "http://dragon04/php/chart/avgCalander_city.php" & strQueryString
'	Response.Redirect "http://dragon04/php/chart/avgCalander_city.php" & strQueryString
Else
%>
	<SCRIPT LANGUAGE="JavaScript">
	<!--
	location.href="avgCalander.php<%=strQueryString & "&show=t"%>";
	//-->
	</SCRIPT>
<%
	'response.write "业务流程"
	' Server.Transfer "http://dragon04/php/chart/avgCalander.php" & strQueryString
	'Response.Redirect "http://dragon04/php/chart/avgCalander.php" & strQueryString
End If
%>
