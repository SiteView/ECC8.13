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
Profile_Id=Request.form("profileid")
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


''----------------------------------------------------------------
'ON ERROR RESUME NEXT
sql="UPDATE profile SET "
sql=sql & " profile_name = '" & Profile_Name & "'"
sql=sql & " where profile_id = " & Profile_Id

dcnDB.Execute(sql)

''----------------------Add Or Remove TranItems-----------
Dim AOldTrans() '数据库中已经存在的,包含在该profile中的transaction
Dim bFound      '用户选择的transaction是否存在 True or False

Set Rs=Server.CreateObject("ADODB.RecordSet")
sql="select t.trans_id,t.trans_name from transactions t,profiletran pt where t.trans_id = pt.trans_id and pt.profile_id = " & Profile_Id
Rs.Open sql,dcndB,1,1
If Rs.Bof And Rs.Eof then '如果数据库中原来没有记录,则与新增Transaction执行一样的添加程序
	If UBound(AtranID) >=0 then
		For i=0 to UBound(AtranID)
			sql="INSERT INTO profiletran(profile_id,trans_id) VALUES(" & Profile_Id & "," & AtranID(i) & ")"
			''response.write sql
			dcnDB.Execute(sql)
		Next
	End if
Else
	ReDim AOldTrans(Rs.RecordCount-1)
	oldIndex=0
	Do Until Rs.Eof
		AOldTrans(oldIndex)=Rs("trans_id")
		Rs.MoveNext
		oldIndex=oldIndex+1
	Loop
	
	'遍历用户选择的每一个Transaction,数据库中如果没有则添加
	If UBound(AtranID) >=0 then
		For i=0 to UBound(AtranID)
			bFound=False
			For j=0 to UBound(AOldTrans)
				if AtranID(i)=AOldTrans(j) then
					bFound=True
					Exit For
				end if
			Next
			If bFound=false then '如果没找到则添加
				sql="INSERT INTO profiletran(profile_id,trans_id) VALUES(" & Profile_Id & "," & AtranID(i) & ")"
				''response.write sql
				dcnDB.Execute(sql)
			End if
		
		Next
	End If
	'遍历数据库中的每一个Transaction,如果用户没有选择则删除
	For i=0 to UBound(AOldTrans)
		bFound=False
		If UBound(AtranID) >=0 then
			For j=0 to UBound(AtranID)
				if AOldTrans(i)=AtranID(j) then
					bFound=True
					Exit For
				end if
			Next
		Else
			bFound=False
		End If
		If bFound=False then '如果没找到则删除
			sql="DELETE FROM profiletran where profile_id = " & Profile_Id & " and trans_id = " & AOldTrans(i)
			''response.write sql
			dcnDB.Execute(sql)
		End if
	
	Next
End If
Rs.close
Set Rs=Nothing

''----------------------Add Or Remove CityItems-----------
Dim AOldCities() '数据库中已经存在的,包含在该城市组中的城市

Set Rs=Server.CreateObject("ADODB.RecordSet")
sql="select c.city_id,c.cityname from city c,profilecity pc where c.city_id = pc.city_id and pc.profile_id = " & Profile_Id
Rs.Open sql,dcndB,1,1
If Rs.Bof And Rs.Eof then '如果数据库中原来没有记录,则与新增城市组执行一样的添加程序
	If UBound(AcityID) >=0 then
		For i=0 to UBound(AcityID)
			sql="INSERT INTO profilecity(profile_id,city_id) VALUES(" & Profile_Id & "," & AcityID(i) & ")"
			''response.write sql
			dcnDB.Execute(sql)
		Next
	End if
Else
	ReDim AOldCities(Rs.RecordCount-1)
	oldIndex=0
	Do Until Rs.Eof
		AOldCities(oldIndex)=Rs("city_id")
		Rs.MoveNext
		oldIndex=oldIndex+1
	Loop
	
	'遍历用户选择的每一个城市,数据库中如果没有则添加
	If UBound(ACityID) >=0 then
		For i=0 to UBound(ACityID)
			bFound=False
			For j=0 to UBound(AOldCities)
				if ACityID(i)=AOldCities(j) then
					bFound=True
					Exit For
				end if
			Next
			If bFound=false then '如果没找到则添加
				sql="INSERT INTO profilecity(profile_id,city_id) VALUES(" & Profile_Id & "," & AcityID(i) & ")"
				''response.write sql
				dcnDB.Execute(sql)
			End if
		
		Next
	End If
	'遍历数据库中的每一个城市,如果用户没有选择则删除
	For i=0 to UBound(AOldCities)
		bFound=False
		If UBound(ACityID) >=0 then
			For j=0 to UBound(ACityID)
				if AOldCities(i)=ACityID(j) then
					bFound=True
					Exit For
				end if
			Next
		Else
			bFound=False
		End If
		If bFound=False then '如果没找到则删除
			sql="DELETE FROM profilecity where profile_id = " & Profile_Id & " and city_id = " & AOldCities(i)
			''response.write sql
			dcnDB.Execute(sql)
		End if
	
	Next
End If
Rs.close
Set Rs=Nothing

''----------------------If Error occurs-------------------
If dcnDB.Errors.Count > 0 then
	Msg="在保存数据时发生如下错误："
	for Each ErrItem In dcnDB.Errors
		Msg=Msg & "<br>Number:" & ErrItem.Number
		Msg=Msg & "<br>Description:" & ErrItem.Description
	next
	dcnDB.Errors.Clear
	dcnDB.RollBackTrans
Else
'	dcnDB.CommitTrans
	Msg="预定义文件“" & Profile_Name & "”已经成功修改!"
End if

''-------------------------------------------------------------------
'response.write(sql)
'response.end
%>
<fieldset style="width:770"> <legend>编辑预定义文件</legend> 
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

