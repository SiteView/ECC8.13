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

trans_Id=Request.QueryString("transid")
'Cust_Id=Request.QueryString("custid")
Cust_ID =request.cookies("rep_cust_id")

'ON ERROR RESUME NEXT
set Rs=Server.CreateObject("ADODB.RecordSet")
''-------------��׼����ֵ--------------------------------------------
sql="SELECT * FROM transactionSet WHERE trans_id = " & Trans_Id
Rs.Open sql,dcnDB,1,1
If Not (Rs.Bof And Rs.Eof) then
	TranSet_Good   =Rs("good")
	TranSet_Bad    =Rs("bad")
	TranSet_Failed =Rs("failed")
end if
Rs.Close
''-------------��ʼ�ͽ���ʱ��----------------------------------------
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
	  <legend class="midfont">ҵ�����̱�׼����</legend>
        <form action="transaction_Edit_save.asp" method="post" name="frmEdit">
          
        <table border="0" class="smallfont" cellpadding="2" cellspacing="1" align="center">
          <tr bgcolor="#CCCCCC"> 
            <td colspan="4" height="12"> 
              <div align="left">��<font color="#FF0033">*</font>�ŵ�Ϊ������ѡ</div>
              </td>
            </tr>
            <tr> 
              
            <td bgcolor="#cccc99" align="right"><font color="#FF0033">*</font>ҵ�����̱�׼���� 
            </td>
              
            <td bgcolor="#efefdd" colspan="3">&nbsp;��(good) 
              <input type="text" name="trangood" size="3" maxlength="3" value="<%=TranSet_Good%>" class="border">
                �� &nbsp;&nbsp;��(bad) 
                
              <input type="text" name="tranbad" size="3" maxlength="3" value="<%=TranSet_Bad%>" class="border">
                �� &nbsp;&nbsp;ʧ��(failed) 
                
              <input type="text" name="tranfailed" size="3" maxlength="3" value="<%=TranSet_Failed%>" class="border">
                �� 
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
              
            <td bgcolor="#cccc99" align="right">��ҵ�����̲���URL </td>
              
            <td bgcolor="#efefdd" colspan="3"> 
              <input type="text" name="url" size="60" value="<%=theURL%>" class="border">
              </td>
            </tr>
            <%End If%>
          </table>
          <div align="center"><br>
            <input name="send" type="submit" value="����" >
            <input name="rewrite"  type="reset" value="��д" >
          </div>
        </form>
     </fieldset> 
	  </td>
    </tr>
  </table>
        
 
</body>
</html>
