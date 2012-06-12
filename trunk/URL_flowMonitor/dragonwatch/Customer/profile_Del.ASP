<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->
<html>
<head>
<title>客户操作平台</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="include/main.css" type="text/css">
</head>
<body bgcolor="#FFFFFF">
  <%''
Dim Rs
Dim sql

Profile_Id=Request.QueryString("profileid")
'Cust_Id=Request.QueryString("custid")
Cust_ID =request.cookies("rep_cust_id")

'ON ERROR RESUME NEXT

sql1="DELETE FROM Profile WHERE Profile_Id = " & Profile_Id
sql2="DELETE FROM Profiletran WHERE Profile_Id = " & Profile_Id
sql3="DELETE FROM Profilecity WHERE Profile_Id = " & Profile_Id

dcnDB.Execute(sql1)
dcnDB.Execute(sql2)
dcnDB.Execute(sql3)

If dcnDB.Errors.Count > 0 then
	Msg="在删除数据时发生如下错误："
	for Each ErrItem In dcnDB.Errors
		Msg=Msg & "<br>Number:" & ErrItem.Number
		Msg=Msg & "<br>Description:" & ErrItem.Description
	next
	dcnDB.Errors.Clear
Else
	Msg="指定预定义文件已经成功删除!"
End if

''-------------------------------------------------------------------
%>

  <fieldset style="width:770">
  <legend>预定义文件删除</legend> 
    <table width="770" border="0" cellspacing="0" cellpadding="0" height="250">
    <tr> 
      <td align=center>&nbsp;<%=Msg%> </td>
    </tr>
    <tr> 
      <td class="chinese"> 
        <div align="right"><a href="Profile_List.asp?custid=<%=Cust_ID%>">返回</a>...&nbsp;&nbsp;&nbsp;&nbsp;</div>
      </td>
    </tr>
  </table>
        
</fieldset>  
</body>
</html>
