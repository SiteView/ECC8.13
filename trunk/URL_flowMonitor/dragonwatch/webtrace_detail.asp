<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<html>
<head>
<title>����·��׷�ٷ���</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
<style type="text/css">
<!--
.webtrace {  font-size: 14.8px; font-weight: bold}
-->
</style>
</head>

<body bgcolor="#FFFFFF" text="#000000">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="97%" bgcolor="#CCCCCC"> 
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td width="50%" height="22"><b>����·��׷�ٷ��� (<%=Request.QueryString("mtime")%>)</b></td>
          <td align="right" width="50%" height="22"><B><font color="#6E6E6E" size=2>
	  ��<%=Request.QueryString("cityname")%>��<%=Request.QueryString("tranname")%>��������
	  </font></B>&nbsp;</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr align="center"> 
    <td colspan="2"><br>
      <table width="90%" border="1" cellspacing="0" cellpadding="2">
        <tr bgcolor="#CCCCCC" align="center"> 
          <td width="11%">�����</td>
          <td width="33%">������</td>
          <td width="23%">IP��ַ</td>
          <td width="14%"><font color="#FF0000">������</font></td>
          <td width="19%">ʱ�䣨���룩</td>
        </tr>
		<%
		' ȡһ��TRACE�ľ�������
		Dim rs, i, sql, iRows, arrRs, iErrs, j
		sql="exec yl_webtrace_detail " & Request.QueryString("tranid") & "," & Request.QueryString("cityid") & ",'" & Request.QueryString("mtime") & "'"
		'Response.Write sql

		Set rs=Server.CreateObject("adodb.recordset")
		rs.Open sql, cnnDragon, 1, 1
		If rs.Eof And rs.Bof Then
		Else
			arrRs=rs.GetRows(rs.RecordCount)
			iRows=UBound(arrRs,2)
			For i=0 To iRows-1
		%>
        <tr>
          <td width="11%" align="center"><%=i+1%></td>
          <td width="33%" align="center"><%=arrRs(7,i)%></td>
          <td width="23%" align="center"><%=arrRs(8,i)%></td>
          <td width="14%" align="center">
		  <%
		  iErrs=0
		  If CInt(arrRs(9,i))=0 Then iErrs=iErrs+1
		  If CInt(arrRs(10,i))=0 Then iErrs=iErrs+1
		  If CInt(arrRs(11,i))=0 Then iErrs=iErrs+1
		  Response.Write iErrs
		  %>
		  </td>
          <td width="19%">
		  <%
		  If iErrs=3 Then
				Response.Write "N/A"
		  Else
				If iErrs=0 Then iErrs=3-iErrs
				j=CInt((CDBL(arrRs(9,i))+CDBL(arrRs(10,i))+CDBL(arrRs(11,i)))/iErrs)
				%>
				<img src="img/lightblue.gif" height=13 width=<%=CInt(30*(j/100))%>>
				<%
				If j<10 Then
					Response.Write "<10"
				Else
					Response.Write j
				End If
				%>
				<%
		  End If
		  %>
		  &nbsp;</td>
        </tr>
		<%	Next 
		i=iRows
		%>
        <tr bgcolor="#CCCCCC"> 
          <td width="11%" align="center"><%=i+1%></td>
          <td width="33%" align="center"><%=arrRs(7,i)%></td>
          <td width="23%" align="center"><%=arrRs(8,i)%></td>
          <td width="14%" align="center">
		  <%
		  iErrs=0
		  If CInt(arrRs(9,i))=0 Then iErrs=iErrs+1
		  If CInt(arrRs(10,i))=0 Then iErrs=iErrs+1
		  If CInt(arrRs(11,i))=0 Then iErrs=iErrs+1
		  Response.Write iErrs
		  %>
		  </td>
          <td width="19%">
		  <%
		  If iErrs=3 Then
				Response.Write "N/A"
		  Else
				If iErrs=0 Then iErrs=3-iErrs
				j=CInt((CDBL(arrRs(9,i))+CDBL(arrRs(10,i))+CDBL(arrRs(11,i)))/iErrs)
				%>
				<img src="img/lightblue.gif" height=13 width=<%=CInt(30*(j/100))%>>
				<%
				If j<10 Then
					Response.Write "<10"
				Else
					Response.Write j
				End If
				%>
				<%
		  End If
		  %>
		  &nbsp;</td>
        </tr>
		<%End If%>
      </table>
    </td>
  </tr>
</table>
</body>
</html>
<%
Set rs=Nothing
%>
<!-- #include file="inc/foot.asp" -->
