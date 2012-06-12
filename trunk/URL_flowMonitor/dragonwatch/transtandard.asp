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
<title>业务流程标准</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="1" topmargin="1" marginwidth="1" marginheight="1">
<table width="100%" border="0" cellspacing="1" cellpadding="0">
  <tr> 
    <td width="1%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="99%" bgcolor="#CCCCCC"><b>业务流程标准</b></td>
  </tr>
  <tr valign="top"> 
    <td height="75">&nbsp;</td>
    <td valign="middle" height="75"> 
      <ul>
        <li>业务流程标准确定本监测系统报告您的系统性能的方式</li>
        <li>业务流程标准将在报告中用以下四种图形表示<br>
          <img src="img/green_dot.gif" width="8" height="8"> 优秀　<img src="img/yellow_dot.gif" width="8" height="8"> 
          警告　<img src="img/red_dot.gif" width="8" height="8"> 危险　<img src="img/error_bit.gif" width="9" height="9"> 失败</li>
      </ul>
    </td>
  </tr>
  <tr valign="top" align="center"> 
    <td colspan="2" height="63"> 
      <table width="95%" border="0" cellspacing="1" cellpadding="3">
        <tr bgcolor="#330066" align="center"> 
          <td width="28%" height="18"><font color="#FFFFFF">业务流程名称</font></td>
          <td width="15%" height="18"><font color="#FFFFFF">优秀</font></td>
          <td width="23%" height="18"><font color="#FFFFFF">警告</font></td>
          <td width="17%" height="18"><font color="#FFFFFF">危险</font></td>
          <td width="17%" height="18"><font color="#FFFFFF">失败</font></td>
        </tr>
        <%
		Dim i
		i=0
		If Not (rs.Eof And rs.Bof) Then
			While Not rs.Eof
			%>
        <tr bgcolor="<%=arrColor(i mod 2)%>"> 
          <td width="28%" align="center"><%=rs("trans_name")%></td>
          <td width="15%" align="center">小于<%=rs("good")%>秒</td>
          <td width="20%" align="center">大于等于<%=rs("good")%>秒小于<%=rs("bad")%>秒</td>
          <td width="20%" align="center">大于等于<%=rs("bad")%>秒小于<%=rs("failed")%>秒</td>
          <td width="17%" align="center">大于等于<%=rs("failed")%>秒</td>
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
    <td valign="middle" height="53">　　业务流程响应时间是一个业务流程完成的总时间。<br>
      <font color="#FF0000">　　业务流程响应时间仅统计正常完成的业务流程，失败的业务流程不计。</font></td>
  </tr>
</table>
</body>
</html>
<!-- #include file="inc/foot.asp" -->
