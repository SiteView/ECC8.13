<HTML>
<HEAD>
<TITLE> New Document </TITLE>
</HEAD>
<SCRIPT LANGUAGE="JavaScript">
<!--
window.parent.returnValue = "no"
//-->
</SCRIPT>

<BODY BGCOLOR="#FFFFFF">
<%
strSelFilter = Request.form("chkTranFilter")
bUserSubmit = Request.form("userSubmit")

'--------------------------¸ü¸Äcookies-------------------------
If bUserSubmit = "yes" then
	'-----------arrSelFilter(x,1)--------------
	arrFilter1 = Split(strSelFilter,",")
	iFilterUBound = UBound(arrFilter1)
	Redim arrSelFilter(iFilterUBound,1)
	For i=0 To iFilterUBound
		arrFilter2 = Split(arrFilter1(i),"_")
		arrSelFilter(i,0) = arrFilter2(0)
		arrSelFilter(i,1) = arrFilter2(1)
	Next

	For i=0 to UBound(arrSelFilter)
		strFilterCooky = strFilterCooky & arrSelFilter(i,0) & ","
	Next
	strFilterCooky = Left(strFilterCooky,Len(strFilterCooky)-1)
	Response.Cookies("rep_sel_failure")("Id") = strFilterCooky
End If

%>
</BODY>
</HTML>
<%If bUserSubmit = "yes" then %>
<SCRIPT LANGUAGE="JavaScript">
<!--
window.parent.returnValue = "yes";
//-->
</SCRIPT>
<%End if%>

<SCRIPT LANGUAGE="JavaScript">
<!--
window.parent.close();
//-->
</SCRIPT>