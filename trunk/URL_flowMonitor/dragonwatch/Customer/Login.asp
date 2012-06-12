<html>
<head>
<title>客户操作平台</title>
<meta http-equiv="目录类型" content="文本/html; 字符集=gb2312">
</head>
<script language=javascript>
function checkIt() {
	with(document.frmLogin) {
	if (Custname.value.length<3) {
		alert("用户名不应短于三位字符!  ");
		Custname.focus();
		return false;
		}
	if (password.value.length<3) {
		alert("密码不应短于三位字符! :( ");
		password.focus();
		return false;
		}
	}
	return true;
}
</script>

<body bgcolor="#FFFFFF">
<h2 align="center">客户登录</h2>
<br>
<table width="100%" border="0">
  <tr>
    <td>
      <form method="post" action="Customer.asp" name="frmLogin" onsubmit="return checkIt()">
        <table border="0" align="center">
          <tr> 
            <td align="right">用户名：</td>
            <td> 
              <input type="text" name="Custname" value="yulei">
            </td>
          </tr>
          <tr> 
            <td align="right">口令：</td>
            <td> 
              <input type="password" name="password" value="yulei">
            </td>
          </tr>
          <tr align="center"> 
            <td colspan="2"> 
              <input type="submit" name="Submit" value=" 登录 ">
              <input type="reset" name="clearform" value=" 清除 ">
            </td>
          </tr>
        </table>
      </form>
    </td>
  </tr>
</table>
<p>&nbsp;
</p>
</body>
</html>
