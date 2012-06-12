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
Dim rsFreeId
Dim sql
Dim freeId '可以添加的ID最小值

''---------------------表单提交数据-----------------------------
'Cust_ID =Request.form("custid")
Cust_ID =request.cookies("rep_cust_id")
Profile_Name  =Request.form("Profile_Name")

ATranID = Split(Request.form("selectedtran"),",")
if UBound(ATranID) >=0 then
	for i=0 to UBound(ATranID)
		ATranID(i)=CInt(ATranID(i))
	next
end if

ACityID = Split(Request.form("selectedcity"),",")
if UBound(ACityID) >=0 then
	for i=0 to UBound(ACityID)
		ACityID(i)=CInt(ACityID(i))
	next
end if

''---------------------检验当前记录是否已经被添加----------------------
'ON ERROR RESUME NEXT
set Rs=Server.CreateObject("ADODB.RecordSet")
sql="SELECT * FROM Profile WHERE profile_name = '" & Profile_Name & "'"
Rs.Open sql,dcnDB,1,1
if Not (Rs.Bof And Rs.Eof) then
	Rs.Close
	set Rs=Nothing
	Response.Write("<P>&nbsp;</P><P>&nbsp;</p>预定义文件“<font color='#CC0000'>" & Description & "</font>”已经存在，请核对后重新保存!")
	Response.Write("<p align=right class=chinese><a href='javascript:history.back()'>返回前页...</a>&nbsp;&nbsp;</p></center></body>")
	Response.End
end if
Rs.Close
set Rs=Nothing

'///////////////得到可添加的最小ID/////////////////////////
set rsFreeId=Server.CreateObject("ADODB.Recordset")
sql="Select ISNULL(Max(Profile_Id),0)+1 Freeid From Profile"
rsFreeId.open sql,dcnDB,1,1
freeId=rsFreeId("freeid")
rsFreeId.Close
Set rsFreeId=Nothing

''-------------------------INSERT SQL: Profile--------------------------
sql="INSERT INTO profile(profile_id,profile_name,cust_id) VALUES("
sql=sql & freeId & ",'" & Profile_Name & "'," & Cust_ID & ")"
''response.write(sql)
dcnDB.Execute(sql)

''--------更新包含Transaction和城市-----------
If UBound(AtranID) >=0 then
	For i=0 to UBound(AtranID)
		sql="INSERT INTO profiletran(profile_id,trans_id) VALUES(" & freeID & "," & AtranID(i) & ")"
		''response.write sql
		dcnDB.Execute(sql)
	Next

End if
If UBound(AcityID) >=0 then
	For i=0 to UBound(AcityID)
		sql="INSERT INTO profilecity(profile_id,city_id) VALUES(" & freeId & "," & AcityID(i) & ")"
		''response.write sql
		dcnDB.Execute(sql)
	Next
End if

''-------------------------------

If dcnDB.Errors.Count > 0 then
	Msg="在保存数据时发生如下错误："
	for Each ErrItem In dcnDB.Errors
		Msg=Msg & "<br>Number:" & ErrItem.Number
		Msg=Msg & "<br>Description:" & ErrItem.Description
	next
	dcnDB.Errors.Clear
Else
	Msg="预定义文件“" & Profile_Name & "”已经成功添加进数据库!"
End if
%>
<fieldset style="width:770"> <legend>添加预定义文件</legend> 
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
