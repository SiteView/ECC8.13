<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!--#Include file="inc/getTime.asp"-->
<script language=javascript src="inc/setSelBytoCity.js"></script>
<%
If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

bFilteredTran = len(request.cookies("rep_trans")("id"))
bFilteredCity = len(request.cookies("rep_city")("id"))

'******************************************************
'ִ�д洢����,�������н�Ҫ�õ������ݱ��浽������������*
'******************************************************
dim rs
dim MaxOverTime   '�ܷ�Ӧʱ������ֵ
dim AllCityCount '��ҵ��������
dim arrData       '��ά����,0-Transaction,1-PageSize,2-overtime,
''''''''''''''    '3-DSN,4-conn,5-header,6-redir,7-data
dim iRows
dim bgc '����ظı䱳��ɫ

Set rs=Server.CreateObject("adodb.RecordSet")
If bFilteredTran then  'ָ����ҵ������
	sql="exec cq_onetrananalysis " & prof_id & "," & request.cookies("rep_trans")("id") & ",'" & startDate & "','" & EndDate & "'"
else
	sql="exec cq_cityanalysis " & prof_id & ",'" & startDate & "','" & EndDate & "'"
end if
''response.write sql
rs.Open sql,cnnDragon,1,1
iRows=0
MaxOvertime=0.0
AllCityCount=0
Do until rs.Eof

	rs.MoveNext
	iRows = iRows + 1
loop

if iRows > 0  then
	Redim arrData(9,iRows - 1)
	rs.MoveFirst
	For i = 0 to iRows-1
		arrData(0,i)=rs("City_name")
		arrData(1,i)=rs("dns")
		arrData(2,i)=rs("conn")
		arrData(3,i)=rs("header")
		arrData(4,i)=rs("redir")
		arrData(5,i)=rs("data")
		arrData(6,i)=Csng(rs("overtime"))
		arrData(7,i)=rs("pagesize")
		arrData(8,i)=rs("totalCity")
		arrData(9,i)=rs("City_id")
		'---------------------------------
		AllCityCount = AllCityCount + rs("totalCity")
		if arrData(2,i) > MaxOverTime then MaxOvertime = arrData(2,i)
''		response.write arrdata(9,i) & "<br>"
		rs.MoveNext

	Next
end if
rs.close
Set rs=Nothing

''response.end
'******************************
%>
<html>
<head>
<title>��������ⱨ�� www.speed.net.cn �й�����������ר��</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
</head>
<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<BR>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> <!-- ����BAR -->
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="44%" bgcolor="#CCCCCC"><b>ҵ�����̷���</b></td>
    <td width="53%" bgcolor="#CCCCCC" align="right"><b>ʱ��:
      <%
	  If DateDiff("d", DateValue(startDate), DateValue(endDate))=0 Then
			Response.Write Year(startDate) & "��" & Month(startDate) & "��" & Day(startDate) & "��" & Hour(startDate) & "ʱ" & Minute(startDate) & "�� - " & Hour(endDate) & "ʱ" & Minute(endDate) & "��"
	  Else
			Response.Write Year(startDate) & "��" & Month(startDate) & "��" & Day(startDate) & "��" & Hour(startDate) & "ʱ" & Minute(startDate) & "�� - " & Year(endDate) & "��" & Month(endDate) & "��" & Day(endDate) & "��" & Hour(endDate) & "ʱ" & Minute(endDate) & "��"
	  End If
	  %>
	  </b></td>
  </tr>
  <tr valign="top">
    <td colspan="3">&nbsp;
      <table width="840" border="0">
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368"><b>��ǰԤ�����ļ��� <%=request.cookies("rep_prf")("name")%></b></td>
          <td width="450" align="right">
            <div align="right"><b>��������ʱ��</b><img src="img/dns.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368"><b>�� <%=AllCityCount%> ��ҵ������</b></td>
          <td width="450" align="right">
            <div align="right"><b>����ʱ��</b> <img src="img/conn.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368">&nbsp;</td>
          <td width="450" align="right">
            <div align="right"><b>��һ�ֽڰ�ʱ��</b> <img src="img/header.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368">&nbsp;</td>
          <td width="450" align="right">
            <div align="right"><b>�ض���ʱ��</b> <img src="img/redir.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368">&nbsp;</td>
          <td width="450" align="right">
            <div align="right"><b>��������ʱ��</b> <img src="img/data.gif" width="8" height="8"></div>
          </td>
        </tr>
      </table>
      <p><b>��ʾ:</b>Ҫ�鿴������ɫ��ʶ,������ָ��һ��ҵ������.
      </p>&nbsp;
      <b><!--#Include file="inc/filter.asp"--></b>
      <table width="820" border="0">
        <tr>
          <td width="840" align="right"><a class='bluelink' href="tran_analysis.asp?showas=graph">��ʾͼ��</a></td>
        </tr>
        <tr>
          <td width="840">
            <table cellspacing=1 cellpadding=3 border=0 bgcolor='#ffffff' width='100%'>
              <tr bgcolor="#330066" align="center"> 
                <td><font color="#FFFFFF"><b>��������</b></font></td>
                <td><font color="#FFFFFF">DNSʱ��(��)</font></td>
                <td><font color="#FFFFFF">����ʱ��(��)</font></td>
                <td><font color="#FFFFFF">��һ�ֽڰ�ʱ��(��)</font></td>
                <td><font color="#FFFFFF">�ض���ʱ��(��)</font></td>
                <td><font color="#FFFFFF">������ʱ��(��)</font></td>
                <td><font color="#FFFFFF">��ʱ��(��)</font></td>
                <td><font color="#FFFFFF">ҳ���С���ֽڡ�</font></td>
                <td><font color="#FFFFFF">ҵ����������</font></td>
                <td><font color="#FFFFFF">����(�ֽ�/��)</font></td>
                <td><font color="#FFFFFF">����</font></td>
              </tr>
              <%
			if iRows > 0 then
				if bFilteredTran then  'ָ����Transaction,��ʾ��ɫ��ʶ
					Set rs=Server.CreateObject("adodb.Recordset")
						'****************************************************************
						'*��TransactionSet����ȡ�����в�ı�׼����������ʾʲô��ɫ��ͼƬ*
						'****************************************************************
						Dim bTranSet  ' as boolean ֻ�д��ڼ���׼��ҵ�����̲�����ʾ

						sql="select * from transactionSet where trans_id = " & request.cookies("rep_trans")("id")
						rs.open sql,cnnDragon,1,1
						bTranSet = false
						if Not (rs.Bof and rs.Eof) then
							iGood   =rs("good")
							iBad    =rs("bad")
							iFailed =rs("failed")
							bTranSet=True
						end if
'//						response.write iGood & " ; " & iBad & " ; " & iFailed & "<br>"
						rs.close
						'**********************************************************
					Set rs=Nothing
					For i=0 to iRows-1
						'-------------
						if i Mod 2 = 0 then
							bgc="#EFEFDD"
						else
							bgc="#CCCC99"
						end if

						response.write "<tr bgcolor='" & bgc & "'>"
						for j=0 to 8
							response.write "<td>&nbsp;"
							if j=0 then response.write "<a href='tran_analysis.asp?cityid=" & arrData(9,i) & "&cityname=" & arrData(0,i) & "'>"   'Links
							response.write arrData(j,i)
							if j=0 then response.write "</a>"   'Links
							response.write "</td>"
						next
						'download speed
						response.write "<td align=center>&nbsp;" & formatNumber(arrData(7,i)/arrData(6,i),2) &  "</td>"

						if arrData(6,i) <= iGood then    '��ʱ��(��)
							theImg = "threshgreen.gif"
						elseif arrData(6,i) > iGood And arrData(6,i) < iBad then '�ϲ���
							theImg = "threshyellow.gif"
						elseif arrData(6,i) > iBad  And arrData(6,i) < iFailed then '�ܲ���
							theImg = "threshred.gif"
						else                          '��
							theImg = "threshblack.gif"
						end if
						response.write "<td align=center>&nbsp;"
						if bTranSet then
							response.write "<img src='img/" & theImg & "'>"
						end if
						response.write "</td></tr>"
					Next
				else
					For i=0 to iRows-1
						'-------------
						if i Mod 2 = 0 then
							bgc="#EFEFDD"
						else
							bgc="#CCCC99"
						end if

						response.write "<tr bgcolor='" & bgc & "'>"
						for j=0 to 8
							response.write "<td>&nbsp;"
							if j=0 then response.write "<a href='tran_analysis.asp?Cityid=" & arrData(9,i) & "&Cityname=" & arrData(0,i) & "'>"   'Links
							response.write arrData(j,i)
							if j=0 then response.write "</a>"   'Links
							response.write "</td>"
						next
						'download speed
						response.write "<td align=center>&nbsp;" & formatNumber(arrData(7,i)/arrData(6,i),2) &  "</td>"

						response.write "<td align=center>&nbsp;</td>"
						response.write "</tr>"
					Next
				end if
			End if
			%>
            </table>
          </td>
        </tr>
      </table>
      <p>&nbsp;</p>
      <table width="60%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="5%"><A class='bluelink' HREF="#" onclick="javascript:window.open('tran_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></A></td>
          <td width="95%">���������ʾ��ҵ�����̵�DNS�����ӡ���һ�ֽڰ����ض����Լ���������ʱ�䣬�������������ڷ����������ĳЩҵ�����̵���Ӧ�ٻ���ԭ��
            &nbsp; <A class='bluelink' HREF="#" onclick="javascript:window.open('tran_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">����...</A></td>
        </tr>
      </table>
      <p><span id="subtitle"> </span> </p>
      <p>&nbsp;</p>
      <p><span id=linegraph> </span> <span id=description> </span> </p>
    </td>
  </tr>
</table>
</body>
</html>
<!-- #include file="inc/foot.asp" -->
