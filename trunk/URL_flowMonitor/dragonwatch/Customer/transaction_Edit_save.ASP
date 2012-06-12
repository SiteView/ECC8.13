<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->
<!--#INCLUDE file="include\Groupcity.inc"-->
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
trans_Id=Request.form("transid")
'Cust_ID =Request.form("custid")
Cust_ID =request.cookies("rep_cust_id")

Tran_Good   = Request.form("trangood")
Tran_Bad    = Request.form("tranbad")
Tran_Failed = Request.form("tranfailed")
Tran_Url    = Request.form("url")

If Not (IsNumeric(Tran_Good) And IsNumeric(Tran_Bad) And IsNumeric(Tran_Failed)) then
	Response.write("标准设置不是正确的数字格式!")
	Response.End
End If

'///////////////得到可添加的最小ID/////////////////////////
set rsFreeId=Server.CreateObject("ADODB.Recordset")
sql="Select ISNULL(Max(trans_Id),0)+1 Freeid From transactions"
rsFreeId.open sql,dcnDB,1,1
freeId=rsFreeId("freeid")
rsFreeId.Close

sql="Select ISNULL(Max(url_Id),0)+1 Freeurlid From url"
rsFreeId.open sql,dcnDB,1,1
freeUrlId=rsFreeId("freeUrlid")
rsFreeId.Close

Set rsFreeId=Nothing

''-------------更新url,并同时更新所有与当前Transaction相关的Trans_id
''所有被更新的表(共12个):
''--customertranbackbone
''--customertrancity    
''--customerTransaction 
''--profileTran         
''--serverSet          
''--transactionAgent
''--transactionIndustry
''\\--transactionList
''--transactions
''--transactionSet
''--transactionUrl(append new)
''-----Url (append new)

sub UpdateUrl()
	sql="DECLARE @ErrorSave INT SET @ErrorSave = 0 BEGIN TRANSACTION " '用变量保存错误，并开始一个事务
	sql=sql & " UPDATE custTransBackbone    SET trans_id = " & freeId & " WHERE trans_id = " & Trans_Id & " IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
	sql=sql & " UPDATE customertrancity     SET trans_id = " & freeId & " WHERE trans_id = " & Trans_Id & " IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
	sql=sql & " UPDATE customerTransaction  SET trans_id = " & freeId & " WHERE trans_id = " & Trans_Id & " IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
	sql=sql & " UPDATE profileTran          SET trans_id = " & freeId & " WHERE trans_id = " & Trans_Id & " IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
	sql=sql & " UPDATE serverSet            SET trans_id = " & freeId & " WHERE trans_id = " & Trans_Id & " IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
	sql=sql & " UPDATE transactionAgent     SET trans_id = " & freeId & " WHERE trans_id = " & Trans_Id & " IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
	sql=sql & " UPDATE transactionIndustry  SET trans_id = " & freeId & " WHERE trans_id = " & Trans_Id & " IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
''	sql=sql & " UPDATE transactionList      SET trans_id = " & freeId & " WHERE trans_id = " & Trans_Id & " IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
	sql=sql & " UPDATE transactions         SET trans_id = " & freeId & " WHERE trans_id = " & Trans_Id & " IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
	sql=sql & " UPDATE transactionSet       SET trans_id = " & freeId & " WHERE trans_id = " & Trans_Id & " IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"

''	sql=sql & " DELETE FROM transactionUrl WHERE trans_id = " & Trans_Id & " IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
	sql=sql & " INSERT INTO Url(url_id,url) VALUES(" & freeUrlId & ",'" & Tran_Url & "') IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
	sql=sql & " INSERT INTO transactionUrl(trans_id,url_id) VALUES(" & freeId & "," & freeUrlId & ") IF (@@ERROR <> 0) SET @ErrorSave = @@ERROR"
	
	sql=sql & " IF (@ErrorSave <> 0) ROLLBACK ELSE COMMIT"
''	response.write sql
''	response.end
	dcnDB.Execute(sql)
end sub
''----------------------------------------------------------------
'ON ERROR RESUME NEXT
''--transactionSet table--
sql3="UPDATE transactionSet SET "
sql3=sql3 & " good   = " & Tran_Good
sql3=sql3 & " , bad  = " & Tran_Bad
sql3=sql3 & " , Failed = " & Tran_Failed
sql3=sql3 & " WHERE trans_id = " & trans_Id

dcnDB.Execute(sql3)

''------------------如果用户对Url作了更改，则更新链接-------------
if Tran_Url <> "" then
	sql="select u.url from url u,transactionurl tu where u.url_id = tu.url_id and tu.trans_id = " & Trans_ID
	Set rsUrl = server.CreateObject("ADODB.recordset")
	rsUrl.Open sql,dcnDB,1,1
	If Not rsURL.Eof then
		theUrl = rsURL("url")
	End If
	rsURL.Close
	Set rsURL = Nothing
	If Tran_Url <> theUrl then
		Call UpdateUrl()
	End If

end if

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
	Msg="业务流程“" & Trans_Name & "”已经成功修改!"
End if

''-------------------------------------------------------------------
%>
<fieldset style="width:770"> <legend>业务流程修改</legend> 
<table width="770" border="0" cellspacing="0" cellpadding="0" height="250">
    <tr> 
      <td align=center>&nbsp;<%=Msg%> </td>
    </tr>
    <tr> 
      <td class="chinese"> 
        <div align="right"><a href="transaction_List.asp?custid=<%=Cust_ID%>">返回</a>...&nbsp;&nbsp;&nbsp;&nbsp;</div>
      </td>
    </tr>
  </table>
 </fieldset>       
 </body>
</html>
