<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->

<html>
<head>
<title>�ͻ�����ƽ̨</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="customer.css" type="text/css">
</head>
<script language=javascript>
function checkIt() {
	with(document.frmEdit) {
	if (oldpass.value.length<3) {
		alert("������д������!  ");
		oldpass.focus();
		return false;
		}
	if (newpass1.value.length<3) {
		alert("���볤�Ȳ��ܶ��������ַ�!  ");
		newpass1.focus();
		return false;
		}
	if (newpass2.value != newpass1.value) {
		alert("���벻�����뱣���������������һ��!  ");
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
<Legend class="midfont">�޸�����</Legend>
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
                <div align="right">������</div>
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
              <td bgcolor="#cccc99" align="right">������ </td>
              <td bgcolor="#efefdd"> 
                <input type="password" name="newpass1" maxlength="32" size="40" class="border">
              </td>
            </tr>
            <tr> 
              <td bgcolor="#cccc99" align="right">������ȷ�� </td>
              <td bgcolor="#efefdd"> 
                <input type="password" name="newpass2" maxlength="32" size="40" class="border">
              </td>
            </tr>
          </table>
          <div align="center"><br>
            <input name="send" type="submit" value="����" >
            <input name="rewrite"  type="reset" value="��д" onclick="location.reload()">
            <input name="rewrite" type="button" value="����" onClick="history.back(-1)">
          </div>
        </form>
      </td>
    </tr>
  </table> 
</FieldSet>
</body>
</html>

