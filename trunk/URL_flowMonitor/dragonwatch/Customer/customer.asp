<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->

<html>
<head>
<title>�ͻ�����ƽ̨</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="customer.css" type="text/css">

</head>
<%
Dim Rs
Dim sql
Cust_Id = Request.cookies("rep_cust_id")
'ON ERROR RESUME NEXT
sql="SELECT * FROM customers WHERE cust_id = " & Cust_Id
'response.write sql
'response.end
'response.write Session("CustId")
Set Rs=Server.CreateObject("ADODB.RecordSet")
Rs.Open sql,dcnDB,1,1
if Rs.Bof And Rs.Eof then
	Rs.Close
	set Rs=Nothing
	Response.Write("<html><body><P>&nbsp;</P><P>&nbsp;</p>��ͼ�����ݿ�ʱ��������ϵͳ����Ա��ϵ!")
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

<body bgcolor="#FFFFFF" text="#000000">
<Table cellpadding="0" cellspacing="0" align="left" width="770">
  <tr>
    <td> 
	<FieldSet style="height:120;"> <Legend Align="left" class="midfont">�ͻ���ϸ��Ϣ</Legend> 
      <table width=100% class="smallfont">
        <tr align=right>
          <td><a href="customer_Edit.asp">�޸�</a></td>
		  <td width="5%"></td>
        </tr>
	 </table>
	  <Table cellpadding="2" cellspacing="1" width="98%" class="smallfont" align="center">
        <tr align="center"> 
          <td width="15%" bgcolor="#cccc99" height="15">�ͻ�����</td>
          <td width="35%" bgcolor="#EFEFDD" height="15">&nbsp;<%=Cust_Name%> </td>
          <td width="15%" bgcolor="#cccc99" height="15">�ͻ�����</td>
          <td width="35%" bgcolor="#EFEFDD" height="15">&nbsp;<%=Cust_StrId%> </td>
  </tr>
  <tr align="center"> 
    <td bgcolor="#cccc99">��ַ</td>
    <td bgcolor="#EFEFDD">&nbsp;<%=Address%> </td>
    <td bgcolor="#cccc99">��������</td>
    <td bgcolor="#EFEFDD">&nbsp;<%=PostalCode%> </td>
  </tr>
  <tr align="center"> 
    <td bgcolor="#cccc99">�绰</td>
    <td bgcolor="#EFEFDD">&nbsp;<%=Phone%> </td>
    <td bgcolor="#cccc99">����</td>
    <td bgcolor="#EFEFDD">&nbsp;<%=Fax%></td>
  </tr>
  <tr align="center"> 
    <td bgcolor="#cccc99">Email</td>
    <td bgcolor="#EFEFDD">&nbsp;<%=Email%></td>
    <td bgcolor="#cccc99">��ע</td>
    <td bgcolor="#EFEFDD">��</td>
  </tr>
</Table>
</FieldSet>
</td></tr>
</Table> 
</body>
</html>