<html>
<head>
<title>�ͻ�����ƽ̨</title>
<meta http-equiv="Ŀ¼����" content="�ı�/html; �ַ���=gb2312">
</head>
<script language=javascript>
function checkIt() {
	with(document.frmLogin) {
	if (Custname.value.length<3) {
		alert("�û�����Ӧ������λ�ַ�!  ");
		Custname.focus();
		return false;
		}
	if (password.value.length<3) {
		alert("���벻Ӧ������λ�ַ�! :( ");
		password.focus();
		return false;
		}
	}
	return true;
}
</script>

<body bgcolor="#FFFFFF">
<h2 align="center">�ͻ���¼</h2>
<br>
<table width="100%" border="0">
  <tr>
    <td>
      <form method="post" action="Customer.asp" name="frmLogin" onsubmit="return checkIt()">
        <table border="0" align="center">
          <tr> 
            <td align="right">�û�����</td>
            <td> 
              <input type="text" name="Custname" value="yulei">
            </td>
          </tr>
          <tr> 
            <td align="right">���</td>
            <td> 
              <input type="password" name="password" value="yulei">
            </td>
          </tr>
          <tr align="center"> 
            <td colspan="2"> 
              <input type="submit" name="Submit" value=" ��¼ ">
              <input type="reset" name="clearform" value=" ��� ">
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
