<!-- #include file="include/check.asp" -->
<!-- #include file="include/head.asp" -->
<%
Const CN_PAGE_SIZE=25 '�������޸Ĵ�ֵ����ȷ��ÿҳ��ʾ�ļ�¼��
Cust_ID =request.cookies("rep_cust_id")

''---------------------�ж��û�ѡ������ʾ�ڼ�ҳ------------------
WhichPage=Request.QueryString("whichpage")
if WhichPage="" Or WhichPage = NULL then
	WhichPage=1
else
	WhichPage=Cint(WhichPage)
end if

''-------------------�򿪼�¼��-----------------------------------
set Rs=Server.CreateObject("ADODB.RecordSet")
sql= "select p.* from profile p where p.cust_id = " & Cust_Id
'response.write(sql)
'response.end
Rs.open sql,dcnDB,1,1

''-------------------������ʾ�ڼ�ҳ-------------------------------
RecExists=0 	'�Ƿ��������¼
PageCount=0 	'ҳ������
RecCount =0 	'��¼����
CurrMinPage=0 	'��ǰ��ʾ�ĵ�һ����¼
CurrMaxPage=0 	'��ǰ��ʾ�����һ����¼
if Not (Rs.Bof And Rs.Eof) then
	Rs.PageSize=CN_PAGE_SIZE
	PageCount=Rs.Pagecount 'intPages��¼�����ݵ�ҳ����
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
<title>�ͻ�����ƽ̨</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="customer.css" type="text/css">
</head>

<body bgcolor="#FFFFFF">

<table width="770">
<tr>
<td>
<FieldSet style="width:770">
<Legend class="midfont">Ԥ�����ļ�</Legend>
<table width="98%" border="0" class="smallfont">
  <tr> 
    <td align="right"><a href="Profile_Add.asp?custid=<%=Cust_ID%>">����Ԥ�����ļ�</a></td>
  </tr>
</table>
<table width="98%" border="0">
  <tr> 
    <td valign="top" align="center">
            <table width="98%" border="0" cellspacing="1" bordercolordark="#FFFFFF" cellpadding="2" class="smallfont">
              <tr bgcolor="330066"> 
                <td colspan="4" class="smallfont" bgcolor="#CCCCCC"><font color="#000000">��������<%=RecCount%>����¼����ǰ��ʾ��<%=CurrMinPage%>������<%=CurrMaxPage%>�� 
                  &nbsp;&nbsp; 
                  <%
          If PageCount > 1 then '�ṩ��ҳ����
          	Response.Write("��<font color='#CC0000'>" & PageCount & "</font>ҳ:&nbsp;")
          	For i=0 to PageCount - 1
          		If WhichPage=i+1 then '��ǰҳ�治�ṩ��ת����
          			Response.Write(i+1)
          		else
          			Response.Write("<a href='Profile_List.asp?custid=" & cust_id & "&whichpage=" & i+1 & "'>" & i+1 & "</a>")
          		end if
          		Response.Write(" ") '�ÿո��
          	Next
          End If
          %>
                  </font></td>
              </tr>
              <tr align="center"> 
                <td width="54%" bgcolor="#cccc99"> 
                  <div align="center"><b>Ԥ�����ļ�����</b></div>
                </td>
                <td width="27%" bgcolor="#cccc99"><b>��������</b></td>
                <td width="10%" bgcolor="#cccc99"> 
                  <div align="center"><b>�޸�</b></div>
                </td>
                <td width="9%" bgcolor="#cccc99"> 
                  <div align="center"><b>ɾ��</b></div>
                </td>
              </tr>
              <%
       	If Not Rs.Eof Then
       	For i=1 to CN_PAGE_SIZE
       	%>
              <tr bgcolor="#efefdd"> 
                <td width="54%">&nbsp;<%=Rs("Profile_Name")%></td>
                <td width="27%" align="center">&nbsp;<%=Rs("Profile_Date")%></td>
                <td width="10%" align="center">&nbsp;<a href="Profile_Edit.asp?custid=<%=Cust_ID%>&profileid=<%=Rs("Profile_Id")%>">�޸�</a></td>
                <td width="9%" align="center">&nbsp;<a href="javascript:if(confirm('ȷʵҪɾ��Ԥ�����ļ� <%=Rs("Profile_Name")%> ��?'))document.location='Profile_Del.asp?custid=<%=Cust_ID%>&profileid=<%=Rs("Profile_Id")%>'">ɾ��</a></td>
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
