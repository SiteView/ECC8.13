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
bShowLink = bFilteredTran and bFilteredCity

'******************************************************
'ִ�д洢����,�������н�Ҫ�õ������ݱ��浽������������*
'******************************************************
dim rs
dim MaxOverTime   '�ܷ�Ӧʱ������ֵ
dim AllTransCount '��ҵ��������
dim arrData       '��ά����,0-Trans_name,1-DSN,2-conn,3-header,4-redir,5-data
''''''''''''''    '6-overtime,7-PageSize,8-totaltrans,9-trans_id
dim arrOneTranTotal(1,100)
dim iRows

dim iCityCount
dim iOldCity
dim arrCity(1,100) ' Id, name

if bFilteredTran then
	sql="exec cq_pageanalysis_onetran " & prof_id & ","& request.cookies("rep_trans")("id") &",'" & startDate & "','" & EndDate & "'"
else
	sql="exec cq_pageanalysis_city " & prof_id & ",'" & startDate & "','" & EndDate & "'"
end if
'response.write sql
''response.end

Set rsT=Server.CreateObject("adodb.RecordSet")
Set rs=Server.CreateObject("adodb.RecordSet")
rs.Open sql,cnnDragon,1,1

AllTransCount=0
MaxOvertime=0.0

iCityCount = 0
iOldCityId = 0

Do until rs.Eof
	If Cint(rs("city_id")) <> iOldCityId Then
		iTranCount = iTranCount + 1
		iOldCityId = Cint(rs("city_id"))

		iCityCount = iCityCount + 1
		iOldCityId = Cint(rs("city_id"))
		arrCity(0,iCityCount-1) = Cint(rs("city_id"))
		arrCity(1,iCityCount-1) = rs("city_name")
	End If

	If Cint(rs("trans_id")) <> iOldTranId then
		iOverTime = Csng(rs("overtime"))
		iOldTranId = Cint(rs("trans_id")) 
	Else
		iOverTime = iOvertime +  Csng(rs("overtime"))
	End If

'	If iOverTime > MaxOverTime then MaxOvertime = iOverTime

	rs.MoveNext
	iRows = iRows + 1
loop
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
    <td width="44%" bgcolor="#CCCCCC"><b>ҳ�����</b></td>
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
      <table width="841" border="0">
        <tr> 
          <td width="28">&nbsp;</td>
          <td width="803"><b>��ǰԤ�����ļ��� <%=request.cookies("rep_prf")("name")%></b></td>
        </tr>
        <tr> 
          <td width="28">&nbsp;</td>
          <td width="803"><b><div id=AllTransCount></div></b></td>
        </tr>
      </table>
      <p>&nbsp;</p>
       
      <b><!--#Include file="inc/filter.asp"--></b>
      <table width="820" border="0">
        <tr>
          <td width="840" align="right"><a class='bluelink' href="page_analysis.asp?showas=graph">��ʾͼ��</a></td>
        </tr>
        <tr>
          <td width="840">
<%
For c = 0 to iCityCount -1

	iRows=0
	iOvertime = 0.0

	iTranCount = 0

	iOldTranId = 0
	iCounter  = 0
	rs.filter = ""
	rs.filter = " city_id = " & arrCity(0,c)

	While Not rs.Eof
		If Cint(rs("trans_id")) <> iOldTranId Then
			iTranCount = iTranCount + 1
			iOldTranId = Cint(rs("trans_id"))
			iOverTime = Csng(rs("overtime"))
			iPageSize = CLng(rs("pagesize")/10)/100
		Else
			iOverTime = iOvertime +  Csng(rs("overtime"))
			iPagesize = iPagesize +  CLng(rs("pagesize")/10)/100
		End If
		arrOneTranTotal(0,iTranCount) = iOverTime
		arrOneTranTotal(1,iTranCount) = iPageSize

		rs.MoveNext
		iRows = iRows + 1
		iCounter = iCounter + 1
	Wend
	if iRows > 0  then
	'	Redim arrData(9,iRows - 1)
		Redim arrData(11,iRows - 1)
		rs.MoveFirst
		For i = 0 to iRows-1
			arrData(0,i)=rs("url")
			arrData(1,i)=rs("dns")
			arrData(2,i)=rs("conn")
			arrData(3,i)=rs("header")
			arrData(4,i)=rs("redir")
			arrData(5,i)=rs("data")
			arrData(6,i)=Csng(rs("overtime"))
			arrData(7,i)=CLng(rs("pagesize")/10)/100  'Bytes to KB
			arrData(8,i)=rs("totaltrans")
			arrData(9,i)=rs("url_id")
			arrData(10,i)=rs("trans_id")
			arrData(11,i)=rs("trans_name")

			'---------------------------------
			AllTransCount = AllTransCount + rs("totaltrans")

			rs.MoveNext

		Next
	end if
%>
           <br>
		   <br>&nbsp;<A class= "bluelink" HREF="page_analysis.asp?cityid=<%=arrCity(0,c)%>&cityname=<%=arrCity(1,c)%>"><%=arrCity(1,c)%></A>
			<table cellspacing=1 cellpadding=3 border=0 bgcolor='#ffffff' width='100%'>
              <tr> 
                <td bgcolor="#330066" align="center"><font color="#FFFFFF"><b>ҳ������</b></font></td>
                <td bgcolor="#330066" align="center"><font color="#FFFFFF">DNSʱ��(��)</font></td>
                <td bgcolor="#330066" align="center"><font color="#FFFFFF">����ʱ��(��)</font></td>
                <td bgcolor="#330066" align="center"><font color="#FFFFFF">��һ�ֽڰ�ʱ��(��)</font></td>
                <td bgcolor="#330066" align="center"><font color="#FFFFFF">�ض���ʱ��(��)</font></td>
                <td bgcolor="#330066" align="center"><font color="#FFFFFF">������ʱ��(��)</font></td>
                <td bgcolor="#330066" align="center"><font color="#FFFFFF">��ʱ��(��)</font></td>
                <td bgcolor="#330066" align="center"><font color="#FFFFFF">ҳ���С���ֽڡ�</font></td>
                <td bgcolor="#330066" align="center"><font color="#FFFFFF">ҵ����������</font></td>
                <td bgcolor="#330066" align="center"><font color="#FFFFFF">����(�ֽ�/��)</font></td>
              </tr>
              <%
			if iRows > 0 then
				iOldTranId = 0
				iCurrTran = 0
				Set rsT=Server.CreateObject("adodb.Recordset")
				For i=0 to iRows-1
					'-------------
					If i=0 Or arrData(10,i) <> iOldTranId Then
						iOldTranId = arrData(10,i)
						iCurrTran = iCurrTran + 1

						'****************************************************************
						'*��TransactionSet����ȡ�����в�ı�׼����������ʾʲô��ɫ��ͼƬ*
						'****************************************************************

						sql="select * from transactionSet where trans_id = '" & arrData(9,iCurrTran-1) & "'"
						rsT.open sql,cnnDragon,1,1

						bTranSet = false
						if Not (rsT.Bof and rsT.Eof) then
							iGood   =rsT("good")
							iBad    =rsT("bad")
							iFailed =rsT("failed")
							bTranSet=True
						end if
						rsT.close
						if arrData(6,i) <= iGood then    '��ʱ��(��)
							theImg = "threshgreen.gif"
						elseif arrData(6,i) > iGood And arrData(6,i) < iBad then '�ϲ���
							theImg = "threshyellow.gif"
						elseif arrData(6,i) > iBad  And arrData(6,i) < iFailed then '�ܲ���
							theImg = "threshred.gif"
						else                          '��
							theImg = "threshblack.gif"
						end if

					  Response.write "<tr bgcolor='#CCCCCC'>" 
					  If bFilteredTran Then
						Response.write "<td>&nbsp;" & arrData(11,i) & "</td>"
					  Else
						Response.write "<td>&nbsp;<a class='bluelink' href='page_analysis.asp?transid=" & arrData(10,i) & "&transname=" & arrData(11,i) & "'>" & arrData(11,i) & "</a></td>"
					  End If
						Response.write "<td colspan='9'>&nbsp;"
							Response.write "�ܴ�С: " & arrOneTranTotal(1,iCurrTran) & " KB&nbsp;&nbsp;&nbsp;"
							Response.write "��ʱ��: " & arrOneTranTotal(0,iCurrTran) &"��s&nbsp;&nbsp;&nbsp;"
							Response.write "ƽ������:" & FormatNumber(arrOneTranTotal(1,iCurrTran) / (arrOneTranTotal(0,iCurrTran)+0.0000001),2) &" KB/s&nbsp;&nbsp;&nbsp;"
							If bTranSet then Response.write "����: &nbsp;<img border=0 src='img\" & theImg & "'>"
						Response.write "</td>"
					  Response.write "</tr>"
					End If
					'**********************************************************
					if i Mod 2 = 0 then
						bgc="#EFEFDD"
					else
						bgc="#CCCC99"
					end if
					response.write "<tr bgcolor='" & bgc & "'>"
					for j=0 to 8
						response.write "<td>&nbsp;"
						response.write arrData(j,i)
						response.write "</td>"
					next
						'download speed
						response.write "<td align=center>&nbsp;" & formatNumber(arrData(7,i)/arrData(6,i),2) &  "</td>"

					Response.write "</tr>"
				Next
			End if
			%>
            </table>

<%Next%>
          </td>
        </tr>
      </table>
      <p>&nbsp;</p>
      <table width="60%" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td width="5%"><a class='bluelink' href="#" onClick="javascript:window.open('page_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></a></td>
          <td width="95%">���������ʾ��ҳ���DNS�����ӡ���һ�ֽڰ����ض����Լ���������ʱ�䣬�������������ڷ����������ĳЩҳ�����Ӧ�ٻ���ԭ�� 
            &nbsp; <a class='bluelink' href="#" onClick="javascript:window.open('page_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">����...</a></td>
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
<%
response.write "<SCRIPT LANGUAGE='JavaScript'>"
response.write "document.all.AllTransCount.innerHTML = '�� " & AllTransCount & " ��ҳ��';"
response.write "</SCRIPT>"

rs.close
Set rs=Nothing
Set rsT=Nothing
%>
<!-- #include file="inc/foot.asp" -->