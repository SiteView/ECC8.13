<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->
<%Cust_ID =request.cookies("rep_cust_id")
%>
<html>
<head>
<title>����ƽ̨</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<script language="javascript" src="include\Select.js"></script>
<link rel="stylesheet" href="customer.css" type="text/css">
</head>
<script language=javascript>
function checkIt() {
	with(document.frmEdit) {
	if (isWhitespace(Profile_Name.value)) {
		alert("������дԤ�����ļ�����!  ");
		Profile_Name.focus();
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
<body bgcolor="#FFFFFF">
<FieldSet style="width=770">
<Legend class="midfont">����Ԥ�����ļ�</Legend>
  <table width="770" border="0" cellspacing="0" cellpadding="0">
    <tr> 
      <td> 
        <form action="Profile_Add_save.asp" method="post" name="frmEdit" onSubmit="return checkIt()">
          
        <table border="0" width="100%" class="smallfont" cellpadding="2" cellspacing="1">
          <tr bgcolor="#330066"> 
            <td colspan="2" height="12" bgcolor="#CCCCCC"> 
              <div align="left"><font color="#000000">��*�ŵ�Ϊ������ѡ</font></div>
            </td>
          </tr>
          <tr> 
            <td width="13%" bgcolor="#cccc99" align="right"> 
              <div align="right"><font color="#FF0033">*</font>Ԥ�����ļ����� </div>
            </td>
            <td bgcolor="#efefdd" width="87%"> 
              <input type="text" name="Profile_Name" size="35" maxlength="50" class="border">
              <input type="hidden" name="custid" value="<%=Cust_ID%>">
            </td>
          </tr>
          <tr bgcolor="#330066"> 
            <td colspan="2" height="12" bgcolor="#CCCCCC"> 
              <div align="left"><font color="#000000">��ѡ���Profile�Ķ���ҵ������</font></div>
            </td>
          </tr>
          <tr> 
            <td width="13%" bgcolor="#cccc99" align="right">&nbsp;</td>
            <td bgcolor="#efefdd" width="87%"> 
              <table width="60%" border="0" class="smallfont">
                <tr> 
                  <td width="21%">�ÿͻ�������ҵ������</td>
                  <td width="11%">&nbsp;</td>
                  <td width="68%">ѡ���ҵ������</td>
                </tr>
                <tr> 
                  <td width="21%"> 
                    <select name="AllTran" size="8" multiple style="width:120" class="border">
                      <%
						Set rsTran=Server.CreateObject("adodb.Recordset")
						sql="select distinct t.trans_id,t.trans_name from transactions t,customertransaction ct where t.trans_id = ct.trans_id and ct.cust_id = "
						sql=sql & Cust_Id
						sql=sql & " AND t.active = '1'"
						rsTran.Open sql,dcnDB,1,1
						Do Until rsTran.Eof
							Response.Write "<option value=" & rsTran("trans_id") & " >" & rsTran("trans_name") & "</option>"
							rsTran.MoveNext
						loop
						rsTran.Close
						Set rsTran=Nothing
						%>
                    </select>
                  </td>
                  <td width="11%"> 
                    <p> 
                      <input type="button" name="additem" value="����&gt;&gt;" onClick="javascript:AddItem('AllTran','SelectedTran','')">
                    </p>
                    <p> 
                      <input type="button" name="deleteitem" value="ɾ��&lt;&lt;" onClick="javascript:DeleteItem('SelectedTran')">
                    </p>
                  </td>
                  <td width="68%"> 
                    <select name="SelectedTran" size="8" multiple style="width:120" class="border">
                    </select>
                  </td>
                </tr>
              </table>
            </td>
          </tr>
          <tr bgcolor="#330066"> 
            <td colspan="2" height="12" bgcolor="#CCCCCC"> 
              <div align="left"><font color="#000000">��ѡ���Profile�Ķ������</font></div>
            </td>
          </tr>
          <tr> 
            <td width="13%" bgcolor="#cccc99" align="right">&nbsp;</td>
            <td bgcolor="#efefdd" width="87%"> 
              <table width="35%" border="0" class="smallfont">
                <tr> 
                  <td width="21%">�ÿͻ������г���</td>
                  <td width="11%">&nbsp;</td>
                  <td width="68%">ѡ��ĳ���</td>
                </tr>
                <tr> 
                  <td width="21%"> 
                    <select name="AllCity" size="8" multiple style="width:120" class="border">
                      <%
						Set rsCity=Server.CreateObject("adodb.Recordset")
						sql="select distinct c.city_id,c.cityname from city c,customertrancity ctc where c.city_id = ctc.city_id and ctc.cust_id = " & Cust_Id
						rsCity.Open sql,dcnDB,1,1
						Do Until rsCity.Eof
							Response.Write "<option value=" & rsCity("city_id") & " >" & rsCity("cityname") & "</option>"
							rsCity.MoveNext
						loop
						rsCity.Close
						Set rsCity=Nothing
						%>
                    </select>
                  </td>
                  <td width="11%"> 
                    <p> 
                      <input type="button" name="additem" value="����&gt;&gt;" onClick="javascript:AddItem('AllCity','SelectedCity','')">
                    </p>
                    <p> 
                      <input type="button" name="deleteitem" value="ɾ��&lt;&lt;" onClick="javascript:DeleteItem('SelectedCity')">
                    </p>
                  </td>
                  <td width="68%"> 
                    <select name="SelectedCity" size="8" multiple style="width:120" class="border">
                    </select>
                  </td>
                </tr>
              </table>
            </td>
          </tr>
        </table>
          <div align="center"><br>
            <input name="send" type="submit" value="����"  onClick="javascript:SelectTotal('SelectedTran');SelectTotal('SelectedCity')">
            <input name="rewrite"  type="reset" value="��д" onclick="location.reload()">
            <input name="rewrite" type="button" value="����" onClick="history.back(-1)">
          </div>
        </form>
      </td>
    </tr>
  </table>
</fieldset>
</body>
</html>
