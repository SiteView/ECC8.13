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
	WhichPage=CInt(WhichPage)
end if

''-------------------�򿪼�¼��-----------------------------------
set Rs=Server.CreateObject("ADODB.RecordSet")
sql="select t.trans_id,t.trans_name,ct.begintime,ct.endtime,ct.CustEditable from transactions t,customertransaction ct "
sql=sql & " where t.trans_id = ct.trans_id and ct.cust_id = " & Cust_Id
sql=sql & " and t.active = '1'"
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
<table width="770" border="0">
  <tr> 
    <td valign="top" align="left">
	<fieldset style="width:770;height=80">
	<Legend class="midfont">ҵ������</Legend>
      <table width="100%" border="0" cellspacing="1" bordercolordark="#FFFFFF" cellpadding="2" class="smallfont">
        <tr bgcolor="330066"> 
          <td colspan="5" bgcolor="#CCCCCC"><font color="#000000">��������<%=RecCount%>����¼����ǰ��ʾ��<%=CurrMinPage%>������<%=CurrMaxPage%>�� 
            &nbsp;&nbsp; 
            <%
          If PageCount > 1 then '�ṩ��ҳ����
          	Response.Write("��<font color='#CC0000'>" & PageCount & "</font>ҳ:&nbsp;")
          	For i=0 to PageCount - 1
          		If WhichPage=i+1 then '��ǰҳ�治�ṩ��ת����
          			Response.Write(i+1)
          		else
          			Response.Write("<a href='transaction_List.asp?custid=" & cust_id & "&whichpage=" & i+1 & "'>" & i+1 & "</a>")
          		end if
          		Response.Write(" ") '�ÿո��
          	Next
          End If
          %>
            </font></td>
        </tr>
        <tr align="center" bgcolor="#cccc99"> 
          <td width="22%"> 
            <div align="center"><b>ҵ����������</b></div>
          </td>
          <td width="14%"><b>��ʼʱ��</b></td>
          <td width="14%"><b>����ʱ��</b></td>
          <td width="37%"><b>���Գ���</b></td>
          <td width="13%"> 
            <div align="center"><b>�޸�</b></div>
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
          If Rs("endtime") < Now then ''�Ѿ�����
          	Response.Write "<font color='#cc0000'>(�ѹ���)</font>"
          End If
          %>
          </td>
          <td width="37%" align="center">&nbsp; 
            <%
          'ѭ���г����еĲ��Գ���
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
            ��׼���� 
            <%
          If Rs("CustEditable") = "Y" then
          	Response.Write "<font color=red>�޸�</font>"
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

