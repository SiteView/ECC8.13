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
'Cust_Id =Request.QueryString("custid")
Cust_ID =request.cookies("rep_cust_id")

'ON ERROR RESUME NEXT
''----取出transaction表中的所有字段,backbone,city,industry表中的描述字段---
sql="select t.*, b.description backbone_name,c.cityname, i.industry_name,ct.CustEditable from transactions t,backbone b,city c,industry i "
sql=sql & " ,customertransaction ct where t.backbone_id = b.backbone_id and t.city_id = c.city_id and t.industry_id = i.industry_id "
sql=sql & " and t.trans_id = ct.trans_id and t.trans_id = " & Trans_Id

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
Description  =Rs("Description")
Trans_Name   =Rs("trans_name")
CustEditable =Rs("CustEditable")
Trans_IP     =Rs("ip")
Trans_Alias  =Rs("alias")
Backbone_Name =Rs("backbone_name")
City_Name     =Rs("cityname")
Industry_Name =Rs("industry_name")
''----------------------------------------------
Rs.Close
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
sql="SELECT * FROM customertransaction WHERE trans_id = " & Trans_Id
sql=sql & " AND cust_id = " & Cust_ID
Rs.Open sql,dcnDB,1,1
If Not (Rs.Bof And Rs.Eof) then
	Begin_Time =Rs("begintime")
	End_Time   =Rs("endtime")
end if
Rs.Close
set Rs=Nothing
''-------------------------------------------------------------------
%>

<body bgcolor="#FFFFFF" >
  <table width="770" border="0" cellspacing="0" cellpadding="0">
    <tr>
      <td> 
	  <Fieldset style="width:770">
	  <legend class="midfont">业务流程详细信息</legend>
        
      <table border="0" width="100%" class="smallfont" cellpadding="2" cellspacing="1">
        <tr bgcolor="#CCCCCC"> 
            <td colspan="4" height="12"> 
              
            <div align="center">业务流程详细信息</div>
            </td>
          </tr>
          <tr> 
            <td width="15%" bgcolor="#CCCC99" align="right"> 
              <div align="right">　业务流程名称 </div>
            </td>
            <td bgcolor="EFEFDD" width="32%"> <%=Trans_Name%> </td>
            <td bgcolor="CCCC99" width="10%" align="right"> 
              <div align="right">　别名 </div>
            </td>
            <td bgcolor="EFEFDD" width="43%"> <%=Trans_Alias%> </td>
          </tr>
          <tr> 
            <td width="15%" bgcolor="#CCCC99" align="right">IP </td>
            <td bgcolor="EFEFDD" width="32%"> <%=Trans_IP%> </td>
            <td bgcolor="CCCC99" width="10%" align="right">是否可调整 </td>
            <td bgcolor="EFEFDD" width="43%"> 
              <%
                If CustEditable= "Y" then
                	Response.write "<font color='#ff0000'>是</font>"
                Else
                	Response.write "否"
                End if
                %>
            </td>
          </tr>
          <tr> 
            <td width="15%" bgcolor="#CCCC99" align="right">所属骨干网 </td>
            <td bgcolor="EFEFDD" width="32%"> <%=Backbone_Name%> </td>
            <td bgcolor="CCCC99" width="10%" align="right">所属城市 </td>
            <td bgcolor="EFEFDD" width="43%"> <%=City_Name%> </td>
          </tr>
          <tr> 
            <td width="15%" bgcolor="#CCCC99" align="right">所属行业 </td>
            <td bgcolor="EFEFDD" width="32%"> <%=Industry_Name%> </td>
            <td bgcolor="CCCC99" width="10%" align="right">描述 </td>
            <td bgcolor="EFEFDD" width="43%"> <%=Description%></td>
          </tr>
          <tr bgcolor="#CCCCCC" align="center"> 
            <td colspan="4" height="12"> 
              
            <div align="center">业务流程标准</div>
            </td>
          </tr>
          <tr> 
            <td width="15%" bgcolor="CCCC99" align="right">开始时间 </td>
            <td bgcolor="EFEFDD" width="32%"> <%=Begin_Time%> </td>
            <td bgcolor="CCCC99" width="10%" align="right">结束时间 </td>
            <td bgcolor="EFEFDD" width="43%"> <%=End_Time%> </td>
          </tr>
          <tr> 
            <td width="15%" bgcolor="CCCC99" align="right">标准设置 </td>
            <td bgcolor="EFEFDD" colspan="3">&nbsp;好(good) <%=TranSet_Good%>秒 
              &nbsp;&nbsp;坏(bad) <%=TranSet_Bad%> 秒 &nbsp;&nbsp;失败(failed) <%=TranSet_Failed%>秒 
            </td>
          </tr>
          <tr bgcolor="#CCCCCC"> 
            <td colspan="4" height="12"> 
              
            <div align="center">业务流程测试URL</div>
            </td>
          </tr>
        <%
        Set rsUrl=Server.CreateObject("adodb.recordset")
        sql="select u.url from url u,transactionurl tu where u.url_id = tu.url_id and tu.trans_id = " & Trans_Id
        rsUrl.Open sql,dcndB,1,1
        Do until rsUrl.Eof
        %>
          <tr> 
            <td width="15%" bgcolor="CCCC99" align="right">&nbsp;</td>
            <td bgcolor="EFEFDD" colspan="3"> <%=rsUrl("url")%> </td>
          </tr>
        <%rsUrl.MoveNext
        Loop%>
        </table>
      </td>
  </tr>
</table>
</body>
</html>
