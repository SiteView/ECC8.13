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
	if (cust_name.value.length<3 || isWhitespace(cust_name.value)) {
		alert("�ͻ����Ƴ��Ȳ��ܶ��������ַ�!  ");
		cust_name.focus();
		return false;
		}
	if (isWhitespace(cust_strid.value)) {
		alert("������д�ͻ�����!  ");
		cust_strid.focus();
		return false;
		}
	}
	return true;
}

function isWhitespace(s){
	if (s.length==0) return true;
	for (i=0;i < s.length;i++){
		if (s.charAt(i)!=" ") return false;
	}
	return true;
}
</script>

<%
Dim Rs
Dim sql

'cust_id=Request.QueryString("custid")
Cust_ID =request.cookies("rep_cust_id")
''Cust_Name =request.cookies("rep_Cust_Name")

'ON ERROR RESUME NEXT
sql="SELECT * FROM customers WHERE cust_id = " & Cust_ID
'response.write sql
'response.end
set Rs=Server.CreateObject("ADODB.RecordSet")
Rs.Open sql,dcnDB,1,1
if Rs.Bof And Rs.Eof then
	Rs.Close
	set Rs=Nothing
	Response.Write("<Html><body><P>&nbsp;</P><P>&nbsp;</p>��ͼ�����ݿ�ʱ��������ϵͳ����Ա��ϵ!")
	Response.Write("<p align=right class=chinese><a href='javascript:history.back()'>����ǰҳ...</a>&nbsp;&nbsp;</p></center></body></html>")
	Response.End
end if
Cust_Name  =Rs("Cust_Name")
cust_strid =Rs("cust_strid")
Password   =Rs("password")
Address    =Rs("address")
PostalCode =Rs("postalcode")
Phone      =Rs("phone")
Fax        =Rs("fax")
Email      =Rs("email")

Rs.Close
set Rs=Nothing
''-------------------------------------------------------------------
%>

<body bgcolor="#FFFFFF">
<fieldset style="width:770">
<Legend class="midfont">�༭�ͻ���Ϣ</Legend>
  <table width="770" border="0" cellspacing="0" cellpadding="0">
    <tr> 
      <td> 
        <form action="customer_Edit_save.asp" method="post" name="frmEdit" onsubmit="return checkIt()">
          
        <table border="0" width="100%" class="smallfont" cellpadding="2" cellspacing="1" bgcolor="#000000">
          <tr bgcolor="#CCCCCC"> 
            <td colspan="4" height="12"> 
              <div align="left"><font color="#000000">��*�ŵ�Ϊ������ѡ</font></div>
            </td>
          </tr>
          <tr> 
            <td width="15%" bgcolor="#cccc99" align="right"> 
              <div align="right">��<font color="#FF0033">*</font>�ͻ����� </div>
            </td>
            <td bgcolor="#efefdd" width="39%"> 
              <input type="text" name="cust_name" size="40" maxlength="255" value="<%=Cust_Name%>" class="border">
            </td>
            <td bgcolor="#cccc99" width="12%" align="right"> 
              <div align="right">��<font color="#FF0033">*</font>�ͻ����� </div>
            </td>
            <td bgcolor="#efefdd" width="34%"> 
              <input type="text" name="cust_strid" maxlength="10" value="<%=Cust_StrId%>" class="border">
              <input type="hidden" name="custid" value="<%=cust_id%>">
            </td>
          </tr>
          <tr> 
            <td width="15%" bgcolor="#cccc99" align="right">��ַ </td>
            <td bgcolor="#efefdd" width="39%"> 
              <input type="text" name="address" size="40" maxlength="255" value="<%=Address%>" class="border">
            </td>
            <td bgcolor="#cccc99" width="12%" align="right">�������� </td>
            <td bgcolor="#efefdd" width="34%"> 
              <input type="text" name="postalcode" maxlength="6" value="<%=PostalCode%>" class="border">
            </td>
          </tr>
          <tr> 
            <td width="15%" bgcolor="#cccc99" align="right">�绰 </td>
            <td bgcolor="#efefdd" width="39%"> 
              <input type="text" name="phone" size="40" value="<%=Phone%>" class="border">
            </td>
            <td bgcolor="#cccc99" width="12%" align="right">���� </td>
            <td bgcolor="#efefdd" width="34%"> 
              <input type="text" name="fax" value="<%=Fax%>" class="border">
            </td>
          </tr>
          <tr> 
            <td width="15%" bgcolor="#cccc99" align="right">Email </td>
            <td bgcolor="#efefdd" width="39%"> 
              <input type="text" name="email" size="40" value="<%=Email%>" class="border">
            </td>
            <td bgcolor="#cccc99" width="12%" align="right">&nbsp;</td>
            <td bgcolor="#efefdd" width="34%">&nbsp;</td>
          </tr>
        </table>
          <div align="center"><br>
            <input name="send" type="submit" value="����" >
            <input name="rewrite"  type="reset" value="��д" onclick="location.reload()">
			<input name="send2" type="button" value="����" onclick="history.back(-1)">
          </div>
        </form>
      </td>
    </tr>
  </table>
</Fieldset> 
</body>
</html>
