<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->

<html>
<head>
<title>客户操作平台</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="customer.css" type="text/css">
</head>
<script language=javascript>
function checkIt() {
	with(document.frmEdit) {
	if (oldpass.value.length<3) {
		alert("请您填写老密码!  ");
		oldpass.focus();
		return false;
		}
	if (newpass1.value.length<3) {
		alert("密码长度不能短于三个字符!  ");
		newpass1.focus();
		return false;
		}
	if (newpass2.value != newpass1.value) {
		alert("密码不符，请保持两次输入的密码一致!  ");
		newpass2.focus();
		return false;
		}
	}
	return true;
}

</script>

<%
Cust_ID =request.cookies("rep_cust_id")
%>

<body bgcolor="#FFFFFF">

<FieldSet align=left style="width:770px;">
<Legend class="midfont">修改密码</Legend>
  <table width="770" border="0" cellspacing="0" cellpadding="0" align=center>
    <tr> 
      <td> 
        <form action="password_Edit_save.asp" method="post" name="frmEdit" onsubmit="return checkIt()">
          
        <table border="0" width="401" class="smallfont" cellpadding="2" cellspacing="1" bgcolor="#FFFFFF" align="center">
          <tr bgcolor="#330066"> 
              
            <td colspan="2" bgcolor="#CCCCCC"> 
              <div align="left">&nbsp;</div>
              </td>
            </tr>
            <tr> 
              <td bgcolor="#cccc99" align="right"> 
                <div align="right">旧密码</div>
              </td>
              <td bgcolor="#efefdd"> 
                <input type="password" name="oldpass" maxlength="32" size="40" class="border">
                <input type="hidden" name="custid" value="<%=Cust_Id%>">
              </td>
            </tr>
            <tr bgcolor="#330066"> 
              
            <td colspan="2" bgcolor="#CCCCCC"> 
              <div align="left">&nbsp;</div>
              </td>
            </tr>
            <tr> 
              <td bgcolor="#cccc99" align="right">新密码 </td>
              <td bgcolor="#efefdd"> 
                <input type="password" name="newpass1" maxlength="32" size="40" class="border">
              </td>
            </tr>
            <tr> 
              <td bgcolor="#cccc99" align="right">新密码确认 </td>
              <td bgcolor="#efefdd"> 
                <input type="password" name="newpass2" maxlength="32" size="40" class="border">
              </td>
            </tr>
          </table>
          <div align="center"><br>
            <input name="send" type="submit" value="发送" >
            <input name="rewrite"  type="reset" value="重写" onclick="location.reload()">
            <input name="rewrite" type="button" value="返回" onClick="history.back(-1)">
          </div>
        </form>
      </td>
    </tr>
  </table> 
</FieldSet>
</body>
</html>

