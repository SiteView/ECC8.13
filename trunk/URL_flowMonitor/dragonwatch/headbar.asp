<!-- #include file="inc/check.asp" -->
<%
If Len(Request.QueryString("fullname"))>0 Then
	Response.cookies("rep_cust")("name")=Request.QueryString("fullname")
End If
If Len(Request.QueryString("userid"))>0 Then
	Response.cookies("rep_cust")("id")=Request.QueryString("userid")
End If
%>
<html>
<head>
<title>��������ⱨ�� www.speed.net.cn �й�����������ר��</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<table width="100%" border="0" cellspacing="2" cellpadding="0">
  <tr> 
    <td colspan="2" bgcolor="#330066" height="17" valign="middle">&nbsp;</td>
    <td height="17" width="7%" bgcolor="#FF6600" align="center" valign="middle"><font color="#FFFFFF">��<a href="helpfile/help_main.htm" target="mainFrame"><font color="#FFFFFF">����</font></a>��</font></td>
    <td height="17" width="8%" bgcolor="#FFCC00" align="center" valign="middle">��<a href="mailto:contact@dragonflow.net"><font color="#000000">����</font></a>��</td>
    <td rowspan="2" width="7%" align="center"><img src="img/logo.gif" width="40" height="46"></td>
  </tr>
  <tr> 
    <td width="26%"><img src="img/logout.gif" width="89" height="18" style="cursor:hand" onClick="logout()">��<img style="cursor:hand;" onClick="ChooseProfile()" src="img/profile.gif" width="89" height="18"></td>
    <td colspan="3">��ǰԤ�����ļ���<span id="profilename"><%=request.cookies("rep_prf")("name")%></span>����������ǰ�û���<%=request.cookies("rep_cust")("name")%></td>
  </tr>
</table>
</body>
</html>
<script language="JavaScript">
function logout()
{
	//x=window.confirm("ȷ��ע����");
	//if (x)
		parent.location.href="logout.asp";
		//parent.location.href="login.asp";
}

function ChooseProfile() 
{
	//openChildWin(url,"ChooseProfile.asp",'toolbar=FALSE,resizable=1,scrollbars=2,height=400,width=400,screenx=500,screeny=500')
	window.open("ChooseProfile.asp?custid=<%=Request.QueryString("userid")%>","",'toolbar=FALSE,resizable=1,scrollbars=2,height=300,width=400,screenx=550,screeny=300');
}

function ShowNotice()
{
	alert("���ڽ���...");
}
</script>

