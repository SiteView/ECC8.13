<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" --><!-- #include file="inc/getTime.asp" -->

<%

If Len(Request.QueryString("trans_id"))>0 Then
	Response.cookies("rep_trans")("id")=Request.QueryString("trans_id")
	Response.cookies("rep_trans")("name")=Request.QueryString("trans_name")
Else
	'Response.cookies("rep_trans")("id")=""
	'Response.cookies("rep_trans")("name")=""
End If
If Len(Request.QueryString("city_id"))>0 Then
	Response.cookies("rep_city")("id")=Request.QueryString("city_id")
	Response.cookies("rep_city")("name")=Request.QueryString("city_name")
Else
	'Response.cookies("rep_city")("id")=""
	'Response.cookies("rep_city")("name")=""
End If

Response.Cookies("rep_isdatatable")="_data"


If Len(Request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=Request.cookies("rep_prf")("id")
End If

If Len(Request.cookies("rep_trans")("id"))>0 Then
	If Len(Request.cookies("rep_city")("id"))>0 then
		sql="exec cq_server_okpercent_n_c_bygroup "& prof_id & "," & Request.cookies("rep_trans")("id") & ","& Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
	Else
		sql="exec cq_server_okpercent_n_c_bytran "& prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	sql="exec cq_server_okpercent_n_c "& prof_id & ",'" & startDate & "','" & endDate & "'"
End If
''response.write sql
''response.end

'/*************** ִ�д�Ŵ洢���̣������ݱ��浽����arrOKper��*****************/
Dim iRecCount
Dim iRowCount
Dim iOldId
Dim bRecExists

Set rs=Server.CreateObject("adodb.RecordSet")
rs.Open sql,cnnDragon,1,1

bRecExists = true
If (rs.Bof and rs.Eof) Then
	REM û����������µĴ���
'	Response.Write "<Center>��ʱ��û������</Center>"
	bRecExists = false
Else
	arrData = rs.GetRows()
	iRecCount = UBound(arrData,2) + 1
'/***** arrData�ĽṹΪName,Id,HourList,OKPer *****/
End If
rs.Close
Set rs=Nothing

REM ��������������ʾ����
If bRecExists Then
	iOldId = 0
	For i=0 To iRecCount - 1
		If CInt(arrData(1,i)) <> iOldId Then
			iRowCount = iRowCount + 1
			iOldId = CInt(arrData(1,i))
		End If
	Next

	Redim arrOKPer(iRowCount-1,3,59)
	iOldId = 0
	iCurrRow = 0
	For i=0 To iRecCount - 1
		If CInt(arrData(1,i)) <> iOldId Then
			iCurrRow = iCurrRow + 1
			iOldId = CInt(arrData(1,i))
			arrOKPer(iCurrRow-1,0,0) = arrData(0,i) 'name
			arrOKPer(iCurrRow-1,1,0) = arrData(1,i) 'id
		End If
		arrOKPer(iCurrRow-1,2,CInt(arrData(2,i))) = arrData(2,i)
		arrOKPer(iCurrRow-1,3,CInt(arrData(2,i))) = arrData(3,i)
	Next
End If

bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)

x=Split(startDate," ")
h=Hour(startDate)
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
    <td width="44%" bgcolor="#CCCCCC"><font class=VerdanaDB10><b>ҵ�����̷���ɹ���&nbsp;</b></font></td>
    <td width="53%" bgcolor="#CCCCCC" align="right"><font class=VerdanaDB10><b>ʱ��:
      <%
	  If DateDiff("d", DateValue(startDate), DateValue(endDate))=0 Then
			Response.Write Year(startDate) & "��" & Month(startDate) & "��" & Day(startDate) & "��" & Hour(startDate) & "ʱ" & Minute(startDate) & "�� - " & Hour(endDate) & "ʱ" & Minute(endDate) & "��"
	  Else
			Response.Write Year(startDate) & "��" & Month(startDate) & "��" & Day(startDate) & "��" & Hour(startDate) & "ʱ" & Minute(startDate) & "�� - " & Year(endDate) & "��" & Month(endDate) & "��" & Day(endDate) & "��" & Hour(endDate) & "ʱ" & Minute(endDate) & "��"
	  End If
	  %>
	  </b></font></td>
  </tr>
  <tr valign="top">
    <td colspan="3">&nbsp; <br>
      <table border="0" cellspacing="3" cellpadding="0">
        <tr>
          <td colspan="3" align="left">
		  <B>
		  ��ǰԤ�����ļ���<%=request.cookies("rep_prf")("name")%><BR>
		  <!-- #include file="inc/filter.asp" -->
		  </B>
		  </td>
        </tr>
        <tr>
          <td width="308" align="right">&nbsp;</td>
          <td width="287" align="right"><A class='bluelink' HREF="service_okpercent_n_c.asp?showchart=1">ͼ��</A></td>
          <td width="47" align="right">&nbsp;</td>
        </tr>
        <tr>
          <td colspan="3" align="center" valign="top">

<table width="85%" border="0" cellspacing="1" cellpadding="3">

  <tr bgcolor="#330066" align=center>
	<td align="center"><font color="#ffffff">ʱ��</font></td>
	<%
			If Len(Request.cookies("rep_city")("id"))>0 Then
				url="service_okpercent_n_c_data.asp"
			Else
				url="service_okpercent_n_t_data.asp"
			End If


	For m=0 to iRowCount-1
		If bShowLink then
			Response.Write "<td align='center'><font color='#ffffff'>"&request.cookies("rep_trans")("name")&"</font></td>"
		Else
			Response.Write "<td align='center'><a href="&url&"?selBy=t&city_id="&arrOKPer(m,1,0)&"&city_name="&arrOKPer(m,0,0)&"><font color='#ffffff'>"&arrOKPer(m,0,0)&"</font></td>"
		End if
	Next
	%>
  </tr>

    <%

		For n=0 to 59
			Response.Write "<tr bgcolor='"&arrColor(n mod 2)&"' align='center'>"
			Response.Write "<td>"&FormatDateTime(DateValue(x(0)), vbLongDate)&" "&h&":"&n&"</td>"

			For j=0 to iRowCount-1
				If IsEmpty(arrOKPer(j,2,n)) Then
					Response.Write("<td>&nbsp;</td>")
				Else
					Response.Write "<td>"&arrOKPer(j,3,n)&"%</td>"
				End If
			Next
		Response.Write "</tr>"
		Next
	%>

</table>

		</td>
        </tr>
        <tr align="left">
          <td colspan="4">
		  <A class='bluelink' HREF="#" onclick="javascript:window.open('service_okpercent_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></A>���������ʾ��ҵ�����̵ķ���ɹ��ʡ�
             &nbsp; <A class='bluelink' HREF="#" onclick="javascript:window.open('service_okpercent_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">����...</A></td>
        </tr>
      </table>
  </tr>
</table>
</body>
</html>
<SCRIPT LANGUAGE="JavaScript" src="inc/setSelByTocity.js"></SCRIPT>
<%If bShowLink Then%><SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToGroup.js"></SCRIPT><%End If%>
<!-- #include file="inc/foot.asp" -->