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
	WhichPage=Cint(WhichPage)
end if

''-------------------打开记录集-----------------------------------
set Rs=Server.CreateObject("ADODB.RecordSet")
sql= "select p.* from profile p where p.cust_id = " & Cust_Id
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

<table width="770">
<tr>
<td>
<FieldSet style="width:770">
<Legend class="midfont">预定义文件</Legend>
<table width="98%" border="0" class="smallfont">
  <tr> 
    <td align="right"><a href="Profile_Add.asp?custid=<%=Cust_ID%>">新增预定义文件</a></td>
  </tr>
</table>
<table width="98%" border="0">
  <tr> 
    <td valign="top" align="center">
            <table width="98%" border="0" cellspacing="1" bordercolordark="#FFFFFF" cellpadding="2" class="smallfont">
              <tr bgcolor="330066"> 
                <td colspan="4" class="smallfont" bgcolor="#CCCCCC"><font color="#000000">共检索出<%=RecCount%>条记录，当前显示第<%=CurrMinPage%>条至第<%=CurrMaxPage%>条 
                  &nbsp;&nbsp; 
                  <%
          If PageCount > 1 then '提供翻页链接
          	Response.Write("共<font color='#CC0000'>" & PageCount & "</font>页:&nbsp;")
          	For i=0 to PageCount - 1
          		If WhichPage=i+1 then '当前页面不提供跳转链接
          			Response.Write(i+1)
          		else
          			Response.Write("<a href='Profile_List.asp?custid=" & cust_id & "&whichpage=" & i+1 & "'>" & i+1 & "</a>")
          		end if
          		Response.Write(" ") '用空格格开
          	Next
          End If
          %>
                  </font></td>
              </tr>
              <tr align="center"> 
                <td width="54%" bgcolor="#cccc99"> 
                  <div align="center"><b>预定义文件名称</b></div>
                </td>
                <td width="27%" bgcolor="#cccc99"><b>定义日期</b></td>
                <td width="10%" bgcolor="#cccc99"> 
                  <div align="center"><b>修改</b></div>
                </td>
                <td width="9%" bgcolor="#cccc99"> 
                  <div align="center"><b>删除</b></div>
                </td>
              </tr>
              <%
       	If Not Rs.Eof Then
       	For i=1 to CN_PAGE_SIZE
       	%>
              <tr bgcolor="#efefdd"> 
                <td width="54%">&nbsp;<%=Rs("Profile_Name")%></td>
                <td width="27%" align="center">&nbsp;<%=Rs("Profile_Date")%></td>
                <td width="10%" align="center">&nbsp;<a href="Profile_Edit.asp?custid=<%=Cust_ID%>&profileid=<%=Rs("Profile_Id")%>">修改</a></td>
                <td width="9%" align="center">&nbsp;<a href="javascript:if(confirm('确实要删除预定义文件 <%=Rs("Profile_Name")%> 吗?'))document.location='Profile_Del.asp?custid=<%=Cust_ID%>&profileid=<%=Rs("Profile_Id")%>'">删除</a></td>
              </tr>
              <%
        	Rs.MoveNext
        	If Rs.Eof then Exit For
        Next

        End If
        %>
            </table>
    </td>
  </tr>
</table>
<%
Rs.Close
Set Rs=Nothing
%>
</FieldSet>
</td>
</tr>
</table>
</body>
</html>
