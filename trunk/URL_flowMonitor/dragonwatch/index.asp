<!-- #include file="inc/check.asp" -->
<%
p=Split(Request.Form("profile"),"_")
' ��¼��profile��ID�ź�����
response.cookies("rep_prf")("id")=p(0)
response.cookies("rep_prf")("name")=p(1)
' ��¼��ʾ���ͣ�ͼ������ݱ�
response.cookies("rep_isdatatable")=""
%>
<html>
<head>
<title>��������ⱨ�� www.speed.net.cn �й�����������ר��</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<META content=no-cache http-equiv=pragma>
</head>
<frameset rows="47,*" cols="*" frameborder="NO" border="0" framespacing="0"> 
  <frame name="topFrame" scrolling="NO" noresize src="headbar.asp?fullname=<%=Request.Form("fullname")%>&userid=<%=Request.Form("userid")%>" >
  <frameset cols="150,*" frameborder="NO" border="0" framespacing="0" rows="*"> 
    <frame name="leftFrame" noresize scrolling="NO" src="menu.asp">
    <!-- <frame name="mainFrame" src="main.asp"> -->
	<frame name="mainFrame" src="empty2.htm">
  </frameset>
</frameset>
<noframes> 
<body bgcolor="#FFFFFF" text="#000000">
</body>
</noframes> 
</html>

