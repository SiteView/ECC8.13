<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->

<html>
<head>
<title>管理平台</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<script language="javascript" src="include\Select.js"></script>
<link rel="stylesheet" href="customer.css" type="text/css">
</head>
<%
Dim Rs
Dim sql

Profile_Id=Request.QueryString("profileid")
Cust_ID =request.cookies("rep_cust_id")

'ON ERROR RESUME NEXT
sql="SELECT * FROM Profile WHERE Profile_Id = " & Profile_Id
set Rs=Server.CreateObject("ADODB.RecordSet")
Rs.Open sql,dcnDB,1,1
if Rs.Bof And Rs.Eof then
	Rs.Close
	set Rs=Nothing
	Response.Write("<html><body><P>&nbsp;</P><P>&nbsp;</p>试图打开数据库时出错，请与系统管理员联系!")
	Response.Write("<p align=right class=chinese><a href='javascript:history.back()'>返回前页...</a>&nbsp;&nbsp;</p></center></body></html>")
	Response.End
end if
''------------取出所有修改字段值,放入变量内--------------------------
Profile_Name   =Rs("Profile_Name")

''----------------------------------------------
Rs.Close
set Rs=Nothing
''-------------------------------------------------------------------
%>

<script language=javascript>
function checkIt() {
	with(document.frmEdit) {
	if (isWhitespace(Profile_Name.value)) {
		alert("请您填写预定义文件名称!  ");
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

  <table width="770" border="0" cellspacing="0" cellpadding="0">
    <tr> 
      <td> 
	  <fieldset style="width=770">
	  <legend class="midfont">修改预定义文件</legend>
        <form action="Profile_Edit_save.asp" method="post" name="frmEdit" onsubmit="return checkIt()">
          
        <table border="0" width="100%" class="smallfont" cellpadding="2" cellspacing="1">
          <tr bgcolor="#330066"> 
            <td colspan="2" height="12" bgcolor="#CCCCCC"> 
              <div align="left"><font color="#000000">标*号的为必填或必选</font></div>
            </td>
          </tr>
          <tr> 
            <td width="14%" bgcolor="#cccc99" align="right"> 
              <div align="right">　<font color="#FF0033">*</font>预定义文件名称 </div>
            </td>
            <td bgcolor="#efefdd" width="86%"> 
              <input type="text" name="Profile_Name" size="35" maxlength="50" value="<%=Profile_Name%>" class="border">
              <input type="hidden" name="profileid" value="<%=Profile_Id%>">
              <input type="hidden" name="custid" value="<%=Cust_ID%>">
            </td>
          </tr>
          <tr bgcolor="#330066"> 
            <td colspan="2" height="12" bgcolor="#CCCCCC"> 
              <div align="left"><font color="#000000">请选择该Profile的定义业务流程</font></div>
            </td>
          </tr>
          <tr> 
            <td width="14%" bgcolor="#cccc99" align="right">&nbsp;</td>
            <td bgcolor="#efefdd" width="86%"> 
              <table width="35%" border="0" class="smallfont">
                <tr> 
                  <td width="21%">该客户的所有业务流程</td>
                  <td width="11%">&nbsp;</td>
                  <td width="68%">选择的业务流程</td>
                </tr>
                <tr> 
                  <td width="21%"> 
                    <select name="AllTran" size="8" multiple style="width:120" class="border">
                      <%
						Set rsTran=Server.CreateObject("adodb.Recordset")
						sql="select distinct t.trans_id,t.trans_name from transactions t,customertransaction ct where t.trans_id = ct.trans_id and ct.cust_id = " & Cust_Id
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
                      <input type="button" name="additem" value="增加&gt;&gt;" onClick="javascript:AddItem('AllTran','SelectedTran','')">
                    </p>
                    <p> 
                      <input type="button" name="deleteitem" value="删除&lt;&lt;" onClick="javascript:DeleteItem('SelectedTran')">
                    </p>
                  </td>
                  <td width="68%"> 
                    <select name="SelectedTran" size="8" multiple style="width:120" class="border">
                      <%
						Set rsTran=Server.CreateObject("adodb.Recordset")
						sql="select t.trans_id,t.trans_name from transactions t,profiletran pt where t.trans_id = pt.trans_id and pt.profile_id = " & Profile_Id
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
                </tr>
              </table>
            </td>
          </tr>
          <tr bgcolor="#330066"> 
            <td colspan="2" height="12" bgcolor="#CCCCCC"> 
              <div align="left"><font color="#000000">请选择该Profile的定义城市</font></div>
            </td>
          </tr>
          <tr> 
            <td width="14%" bgcolor="#cccc99" align="right">&nbsp;</td>
            <td bgcolor="#efefdd" width="86%"> 
              <table width="35%" border="0" class="smallfont">
                <tr> 
                  <td width="21%">该客户的所有城市</td>
                  <td width="11%">&nbsp;</td>
                  <td width="68%">选择的城市</td>
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
                      <input type="button" name="additem" value="增加&gt;&gt;" onClick="javascript:AddItem('AllCity','SelectedCity','')">
                    </p>
                    <p> 
                      <input type="button" name="deleteitem" value="删除&lt;&lt;" onClick="javascript:DeleteItem('SelectedCity')">
                    </p>
                  </td>
                  <td width="68%"> 
                    <select name="SelectedCity" size="8" multiple style="width:120" class="border">
                      <%
						Set rsCity=Server.CreateObject("adodb.Recordset")
						sql="select c.city_id,c.cityname from city c,profilecity pc where c.city_id = pc.city_id and pc.profile_id = " & Profile_Id
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
                </tr>
              </table>
            </td>
          </tr>
        </table>
          <div align="center"><br>
            <input name="send" type="submit" value="发送"  OnClick="javascript:SelectTotal('SelectedTran');SelectTotal('SelectedCity')">
            <input name="rewrite" type="reset" value="重写" onClick="location.reload()">
            <input name="rewrite" type="button" value="返回" onClick="history.back(-1)">
          </div>
        </form>
		</fieldset>
      </td>
    </tr>
  </table>
        
  
</body>
</html>
