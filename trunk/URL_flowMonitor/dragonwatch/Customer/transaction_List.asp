<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->
<%
Const CN_PAGE_SIZE=25 '您可以修改此值，以确定每页显示的记录数
Cust_ID =request.cookies("rep_cust_id")

''---------------------判断用户选择了显示第几页------------------
WhichPage=Request.QueryString("whichpage")
if WhichPage="" Or WhichPage = NULL then
	WhichPage=1
else
	WhichPage=CInt(WhichPage)
end if

''-------------------打开记录集-----------------------------------
set Rs=Server.CreateObject("ADODB.RecordSet")
sql="select t.trans_id,t.trans_name,ct.begintime,ct.endtime,ct.CustEditable from transactions t,customertransaction ct "
sql=sql & " where t.trans_id = ct.trans_id and ct.cust_id = " & Cust_Id
sql=sql & " and t.active = '1'"
'response.write(sql)
'response.end
Rs.open sql,dcnDB,1,1

''-------------------决定显示第几页-------------------------------
RecExists=0 	'是否检索出记录
PageCount=0 	'页面总数
RecCount =0 	'记录总数
CurrMinPage=0 	'当前显示的第一条记录
CurrMaxPage=0 	'当前显示的最后一条记录
if Not (Rs.Bof And Rs.Eof) then
	Rs.PageSize=CN_PAGE_SIZE
	PageCount=Rs.Pagecount 'intPages记录了数据的页面数
	if WhichPage < 1 then WhichPage=1
	if WhichPage > PageCount then WhichPage=PageCount
	Rs.AbsolutePage=WhichPage
	RecExists=1
	RecCount =Rs.RecordCount
	CurrMinPage=(WhichPage - 1) * CN_PAGE_SIZE + 1
	CurrMaxPage=(WhichPage) * CN_PAGE_SIZE
	If CurrMaxPage > RecCount then CurrMaxPage=RecCount
end if
''----------------------------------------------------------------
%>
<html>
<head>
<title>客户操作平台</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="customer.css" type="text/css">
</head>

<body bgcolor="#FFFFFF">
<table width="770" border="0">
  <tr> 
    <td valign="top" align="left">
	<fieldset style="width:770;height=80">
	<Legend class="midfont">业务流程</Legend>
      <table width="100%" border="0" cellspacing="1" bordercolordark="#FFFFFF" cellpadding="2" class="smallfont">
        <tr bgcolor="330066"> 
          <td colspan="5" bgcolor="#CCCCCC"><font color="#000000">共检索出<%=RecCount%>条记录，当前显示第<%=CurrMinPage%>条至第<%=CurrMaxPage%>条 
            &nbsp;&nbsp; 
            <%
          If PageCount > 1 then '提供翻页链接
          	Response.Write("共<font color='#CC0000'>" & PageCount & "</font>页:&nbsp;")
          	For i=0 to PageCount - 1
          		If WhichPage=i+1 then '当前页面不提供跳转链接
          			Response.Write(i+1)
          		else
          			Response.Write("<a href='transaction_List.asp?custid=" & cust_id & "&whichpage=" & i+1 & "'>" & i+1 & "</a>")
          		end if
          		Response.Write(" ") '用空格格开
          	Next
          End If
          %>
            </font></td>
        </tr>
        <tr align="center" bgcolor="#cccc99"> 
          <td width="22%"> 
            <div align="center"><b>业务流程名称</b></div>
          </td>
          <td width="14%"><b>开始时间</b></td>
          <td width="14%"><b>结束时间</b></td>
          <td width="37%"><b>测试城市</b></td>
          <td width="13%"> 
            <div align="center"><b>修改</b></div>
          </td>
        </tr>
        <%
       	If Not Rs.Eof Then
       	Set rsCity = Server.CreateObject("ADODB.Recordset")
       	For i=1 to CN_PAGE_SIZE
       	%>
        <tr bgcolor="efefdd"> 
          <td width="22%">&nbsp; <a href="transaction_Detail.asp?custid=<%=Cust_ID%>&transid=<%=Rs("trans_id")%>"><%=Rs("trans_name")%></a></td>
          <td width="14%" align="center">&nbsp;<%=Rs("begintime")%></td>
          <td width="14%" align="center">&nbsp; 
            <%
          Response.Write Rs("endtime")
          If Rs("endtime") < Now then ''已经过期
          	Response.Write "<font color='#cc0000'>(已过期)</font>"
          End If
          %>
          </td>
          <td width="37%" align="center">&nbsp; 
            <%
          '循环列出所有的测试城市
			sql="select c.city_id,c.cityname from city c,customertrancity ctc where c.city_id = ctc.city_id and ctc.trans_id = " & Rs("trans_id")
			rsCity.Open sql,dcnDB,1,1
			Do Until rsCity.Eof
				Response.Write rsCity("cityname") & ";"
				rsCity.MoveNext
			loop
			rsCity.Close
          %>
          </td>
          <td width="13%" align="center">&nbsp; <a href="transaction_Edit.asp?custid=<%=Cust_ID%>&transid=<%=Rs("trans_id")%>"> 
            标准设置 
            <%
          If Rs("CustEditable") = "Y" then
          	Response.Write "<font color=red>修改</font>"
          End if
          %>
            </a> </td>
        </tr>
        <%
        	Rs.MoveNext
        	If Rs.Eof then Exit For
        Next

		Set rsCity=Nothing
        End If
        %>
      </table>
      </FieldSet>
    </td>
  </tr>
</table>
<%
Rs.Close
Set Rs=Nothing
%>
</body>
</html>

