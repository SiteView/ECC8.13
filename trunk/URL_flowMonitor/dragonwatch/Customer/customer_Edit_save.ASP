<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->

<html>
<head>
<title>客户操作平台</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="include/main.css" type="text/css">
</head>
<body bgcolor="#FFFFFF">
<%
Dim Rs
Dim sql

''---------------------表单提交数据-----------------------------
'cust_id=Request.form("custid")
Cust_ID =request.cookies("rep_cust_id")
Cust_strid =Request.form("cust_strid")
Cust_Name  =Request.form("cust_name")
Address    =Request.form("address")
PostalCode =Request.form("postalcode")
Phone      =Request.form("phone")
Fax        =Request.form("fax")
Email      =Request.form("email")

'ON ERROR RESUME NEXT
''----------------------UPDATE SQL -----------------------
sql="UPDATE customers SET "
sql=sql & " cust_strid  = '" & cust_strid & "'"
sql=sql & " , Cust_Name = '" & Cust_Name  & "'"
sql=sql & " , address   = '" & Address    & "'"
sql=sql & " , postalcode= '" & PostalCode & "'"
sql=sql & " , phone     = '" & Phone      & "'"
sql=sql & " , fax       = '" & Fax        & "'"
sql=sql & " , email     = '" & Email      & "'"
sql=sql & " WHERE cust_id = " & cust_id
''response.write(sql)
''response.end
dcnDB.Execute(sql)

If dcnDB.Errors.Count > 0 then
	Msg="在保存数据时发生如下错误："
	for Each ErrItem In dcnDB.Errors
		Msg=Msg & "<br>Number:" & ErrItem.Number
		Msg=Msg & "<br>Cust_Name:" & ErrItem.Cust_Name
	next
	dcnDB.Errors.Clear
Else
	Msg="客户“" & Cust_Name & "”已经成功修改!"
End if

''-------------------------------------------------------------------
%>
<fieldset style="width:770"> <legend>客户信息修改</legend> 
<table width="770" border="0" cellspacing="0" cellpadding="0" height="250">
    <tr> 
      <td align=center>&nbsp;<%=Msg%> </td>
    </tr>
    <tr> 
      <td class="chinese"> 
        <div align="right"><a href="customer.asp">返回</a>...&nbsp;&nbsp;&nbsp;&nbsp;</div>
      </td>
    </tr>
  </table>
        
 </fieldset>
</body>
</html>
