<html>
<HEAD>
<TITLE> ����ʽƽ����Ӧʱ��ͼ </TITLE>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net">
<link rel="stylesheet" href="css.css" type="text/css">
</HEAD>
<body>
<%
'response.write request("time")
'response.write request("group")

Response.Cookies("rep_per")="d"  ' ʱ�䵥λ����
Response.Cookies("rep_by")=Request.QueryString("group")  ' ���鷽ʽ

Response.cookies("rep_startTime")=Request.QueryString("time")
%>
<CENTER>������ת��ָ�����ڵķ���ɹ��ʱ��Ժ�...</CENTER>
<SCRIPT LANGUAGE="JavaScript">
<!--
parent.parent.leftFrame.document.all.t5.click();
parent.parent.leftFrame.document.all.a5.click();
//-->
</SCRIPT>
</body>
</html>
