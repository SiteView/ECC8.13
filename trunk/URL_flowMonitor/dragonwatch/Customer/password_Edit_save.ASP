<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->

<html>
<head>
<title>客户操作平台</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="include/main.css" type="text/css">
</head>
<body bgcolor="#FFFFFF" >
<%
Dim Rs
Dim sql

''---------------------表单提交数据-----------------------------
'cust_id=Request.form("custid")
Cust_ID =request.cookies("rep_cust_id")
OldPass   =Request.form("oldpass")
NewPass   =Request.form("newpass1")

'ON ERROR RESUME NEXT
''-------------------首先检验用户的老密码是否正确---------------
Set Rs=Server.CreateObject("ADODB.RecordSet")
sql="SELECT * FROM customers WHERE cust_id = " & Cust_Id & " AND password = '" & OldPass & "'"
Rs.Open sql,dcnDB,1,1
If Rs.Bof And Rs.Eof then '用户老密码错
	Response.Write "老密码输入有误！"
	Response.end
End If
Rs.Close
Set Rs=Nothing

''----------------------UPDATE SQL -----------------------
sql="UPDATE customers SET "
sql=sql & " password  = '" & NewPass & "'"
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
	Msg="密码已经成功修改!"
End if

''-------------------------------------------------------------------
%>
<fieldset style="width:770"> <legend>修改密码</legend> 
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
