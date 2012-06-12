<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->

<html>
<head>
<title>客户操作平台</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="customer.css" type="text/css">
</head>
<%
Dim Rs
Dim sql

trans_Id=Request.QueryString("transid")
'Cust_Id=Request.QueryString("custid")
Cust_ID =request.cookies("rep_cust_id")

'ON ERROR RESUME NEXT
set Rs=Server.CreateObject("ADODB.RecordSet")
''-------------标准设置值--------------------------------------------
sql="SELECT * FROM transactionSet WHERE trans_id = " & Trans_Id
Rs.Open sql,dcnDB,1,1
If Not (Rs.Bof And Rs.Eof) then
	TranSet_Good   =Rs("good")
	TranSet_Bad    =Rs("bad")
	TranSet_Failed =Rs("failed")
end if
Rs.Close
''-------------开始和结束时间----------------------------------------
sql="SELECT CustEditable FROM customertransaction WHERE trans_id = " & Trans_Id
sql=sql & " AND cust_id = " & Cust_ID
Rs.Open sql,dcnDB,1,1
If Not (Rs.Bof And Rs.Eof) then
	CustEditable=Rs("CustEditable")
end if
Rs.Close
set Rs=Nothing
''-------------------------------------------------------------------
%>

<body bgcolor="#FFFFFF">
  <table width="770" border="0" cellspacing="0" cellpadding="0">
    <tr> 
      <td>
	  <fieldset style="width:770"> 
	  <legend class="midfont">业务流程标准设置</legend>
        <form action="transaction_Edit_save.asp" method="post" name="frmEdit">
          
        <table border="0" class="smallfont" cellpadding="2" cellspacing="1" align="center">
          <tr bgcolor="#CCCCCC"> 
            <td colspan="4" height="12"> 
              <div align="left">标<font color="#FF0033">*</font>号的为必填或必选</div>
              </td>
            </tr>
            <tr> 
              
            <td bgcolor="#cccc99" align="right"><font color="#FF0033">*</font>业务流程标准设置 
            </td>
              
            <td bgcolor="#efefdd" colspan="3">&nbsp;好(good) 
              <input type="text" name="trangood" size="3" maxlength="3" value="<%=TranSet_Good%>" class="border">
                秒 &nbsp;&nbsp;坏(bad) 
                
              <input type="text" name="tranbad" size="3" maxlength="3" value="<%=TranSet_Bad%>" class="border">
                秒 &nbsp;&nbsp;失败(failed) 
                
              <input type="text" name="tranfailed" size="3" maxlength="3" value="<%=TranSet_Failed%>" class="border">
                秒 
                <input type="hidden" name="transid" value="<%=trans_id%>">
              </td>
            </tr>
            <%If CustEditable = "Y" then 
            	sql="select u.url from url u,transactionurl tu where u.url_id = tu.url_id and tu.trans_id = " & Trans_ID
            	Set rsUrl = server.CreateObject("ADODB.recordset")
            	rsUrl.Open sql,dcnDB,1,1
            	If Not rsURL.Eof then
            		theUrl = rsURL("url")
            	End If
            	rsURL.Close
            	Set rsURL = Nothing
            %>
            <tr>
              
            <td bgcolor="#cccc99" align="right">该业务流程测试URL </td>
              
            <td bgcolor="#efefdd" colspan="3"> 
              <input type="text" name="url" size="60" value="<%=theURL%>" class="border">
              </td>
            </tr>
            <%End If%>
          </table>
          <div align="center"><br>
            <input name="send" type="submit" value="发送" >
            <input name="rewrite"  type="reset" value="重写" >
          </div>
        </form>
     </fieldset> 
	  </td>
    </tr>
  </table>
        
 
</body>
</html>
