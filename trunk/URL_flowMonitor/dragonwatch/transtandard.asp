<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<%
Dim prof_id, rs
If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If
sql="select tset.*, t.trans_name from transactionset tset, transactions t where tset.trans_id=t.trans_id and tset.trans_id in(select trans_id from profiletran where profile_id=" & prof_id & ")"

Set rs=cnnDragon.Execute(sql)
%>
<html>
<head>
<title>ҵ�����̱�׼</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="1" topmargin="1" marginwidth="1" marginheight="1">
<table width="100%" border="0" cellspacing="1" cellpadding="0">
  <tr> 
    <td width="1%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="99%" bgcolor="#CCCCCC"><b>ҵ�����̱�׼</b></td>
  </tr>
  <tr valign="top"> 
    <td height="75">&nbsp;</td>
    <td valign="middle" height="75"> 
      <ul>
        <li>ҵ�����̱�׼ȷ�������ϵͳ��������ϵͳ���ܵķ�ʽ</li>
        <li>ҵ�����̱�׼���ڱ���������������ͼ�α�ʾ<br>
          <img src="img/green_dot.gif" width="8" height="8"> ���㡡<img src="img/yellow_dot.gif" width="8" height="8"> 
          ���桡<img src="img/red_dot.gif" width="8" height="8"> Σ�ա�<img src="img/error_bit.gif" width="9" height="9"> ʧ��</li>
      </ul>
    </td>
  </tr>
  <tr valign="top" align="center"> 
    <td colspan="2" height="63"> 
      <table width="95%" border="0" cellspacing="1" cellpadding="3">
        <tr bgcolor="#330066" align="center"> 
          <td width="28%" height="18"><font color="#FFFFFF">ҵ����������</font></td>
          <td width="15%" height="18"><font color="#FFFFFF">����</font></td>
          <td width="23%" height="18"><font color="#FFFFFF">����</font></td>
          <td width="17%" height="18"><font color="#FFFFFF">Σ��</font></td>
          <td width="17%" height="18"><font color="#FFFFFF">ʧ��</font></td>
        </tr>
        <%
		Dim i
		i=0
		If Not (rs.Eof And rs.Bof) Then
			While Not rs.Eof
			%>
        <tr bgcolor="<%=arrColor(i mod 2)%>"> 
          <td width="28%" align="center"><%=rs("trans_name")%></td>
          <td width="15%" align="center">С��<%=rs("good")%>��</td>
          <td width="20%" align="center">���ڵ���<%=rs("good")%>��С��<%=rs("bad")%>��</td>
          <td width="20%" align="center">���ڵ���<%=rs("bad")%>��С��<%=rs("failed")%>��</td>
          <td width="17%" align="center">���ڵ���<%=rs("failed")%>��</td>
        </tr>
        <%
				rs.MoveNext
				i=i+1
			Wend
		End If
		%>
      </table>
    </td>
  </tr>
  <tr valign="top"> 
    <td height="53">&nbsp;</td>
    <td valign="middle" height="53">����ҵ��������Ӧʱ����һ��ҵ��������ɵ���ʱ�䡣<br>
      <font color="#FF0000">����ҵ��������Ӧʱ���ͳ��������ɵ�ҵ�����̣�ʧ�ܵ�ҵ�����̲��ơ�</font></td>
  </tr>
</table>
</body>
</html>
<!-- #include file="inc/foot.asp" -->
