<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
' �����������
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
'===========================================================================

' �������ʱ��
Response.cookies("rep_datetime")("start")=startDate
Response.cookies("rep_datetime")("end")=endDate

response.cookies("rep_isdatatable")="_data"

'response.write startDate & "<BR>"
'response.write endDate & "<BR>"
'response.end

If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

' ȡ��ƽ����Ӧʱ��
If Len(Request.cookies("rep_trans")("id"))>0 Then
	If Len(Request.cookies("rep_city")("id"))>0 Then
		sql="exec yl_rep_avg_q_c_withid " & prof_id & "," & Request.cookies("rep_trans")("id") & "," & Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
	Else
		sql="exec yl_rep_avg_q_c_bytranid " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	sql="exec yl_rep_avg_q_c " & prof_id & ",'" & startDate & "','" & endDate & "'"
End If
'response.write sql
Set rs=Server.CreateObject("adodb.recordset")  ' ȡ����
rs.Open sql, cnnDragon, 1, 1
If rs.RecordCount=0 Then
	Response.Write "<Center>��ʱ��û������</Center>"
Else

	arrRs=rs.GetRows(rs.RecordCount)
	rs.Close
	Set rs=Nothing

	iRsCols=UBound(arrRs) ' �ж����ֶ�
	iRsRows=UBound(arrRs,2) ' �ж���������
	Dim strTrans_id
	Dim strTrans_name
	iMax=0 ' �����ֵ

	' ����ҵ������ID�����ƣ����������ֵ
	oldid=0
	For i=0 To iRsRows
		If iMax<CInt(arrRs(3,i)) Then iMax=CInt(arrRs(3,i))
		If oldid<>CInt(arrRs(1,i)) Then
			strTrans_id=strTrans_id & arrRs(1,i) & ","
			strTrans_name=strTrans_name & arrRs(0,i) & ","
			oldid=CInt(arrRs(1,i))
		End If
	Next
	arrCitys_id=Split(strTrans_id, ",")
	arrCitys_name=Split(strTrans_name, ",")

	iCountCitys=UBound(arrCitys_id)-1 ' ��Ԥ�����ļ��������ٸ� Transaction

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
    <td width="44%" bgcolor="#CCCCCC"><font class=VerdanaDB10><b>ҵ������ʱ��ƽ����Ӧʱ��&nbsp;</b></font></td>
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
		  <B><%bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)%>
		  ��ǰԤ�����ļ���<%=request.cookies("rep_prf")("name")%><BR>
		  <!-- #include file="inc/filter.asp" -->
		  </B>
		  </td>
        </tr>
        <tr>
          <td width="308" align="right">&nbsp;</td>
          <td width="287" align="right"><A class='bluelink' HREF="rep_avg_q_c.asp">ͼ��</A></td>
          <td width="47" align="right">&nbsp;</td>
        </tr>
        <tr>
          <td colspan="3" align="center" valign="top">
<!-- ���ݱ� -->
<%
x=Split(startDate," ") ' ȡ����
a=DateValue(x(0))
' ����X��Ŀ̶�ֵ���ӵڣ����ڵ��ڣ�����
xStart=DatePart("ww", DateValue(startDate))
xEnd=DatePart("ww", DateValue(endDate))

ReDim arrLineSet(iCountCitys,xEnd)
oldid=0
j=0
For i=0 To iRsRows
	If oldid<>CInt(arrRs(1,i)) Then
		j=j+1
		oldid=CInt(arrRs(1,i))
	End If
	arrLineSet(j-1,CInt(arrRs(2,i)))=arrRs(3,i)
Next
%>
<table width="85%" border="0" cellspacing="1" cellpadding="3">
  <tr bgcolor="#330066" align=center>
                <td align="center"><font color="#ffffff">ʱ��</font></td>
	<%
	If Len(Request.cookies("rep_trans")("id"))>0 Then
		url="rep_avg_q_c_data.asp"
	Else
		url="rep_avg_q_t_data.asp"
	End If
	bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)

	For i=0 To iCountCitys
		If bShowLink Then
	%>
		<td><font color="#ffffff"><%=arrCitys_name(i)%></font></td>
	<%
		Else
	%>
		<td><A HREF="<%=url%>?selby=t&city_id=<%=arrCitys_id(i)%>&city_name=<%=arrCitys_name(i)%>" style="color:#ffffff;text-decoration:underline"><%=arrCitys_name(i)%></A></td>
	<%
		End If
	Next
	%>
  </tr>
  <%
	x=DateValue(startDate)
  For i=xStart To xEnd
Select Case WeekDay(x)
Case 1
	x=DateAdd("d",1,x)
Case 2
Case 3
	x=DateAdd("d",-1,x)
Case 4
	x=DateAdd("d",-2,x)
Case 5
	x=DateAdd("d",-3,x)
Case 6
	x=DateAdd("d",-4,x)
Case 7
	x=DateAdd("d",-5,x)
End Select
	y=DateAdd("d",6,x)
  %>
  <tr bgcolor="<%=arrColor(i mod 2)%>" align=center>
    <td><A HREF="rep_avg_w_c_data.asp?per=w&d=<%=x&" "&Hour(startDate)&":00"%>&s=<%=x%>&e=<%=y%>" style="text-decoration:underline"><%=(Year(x) & "��" & Month(x) & "��" & Day(x) & "�� �� " & Month(y) & "��" & Day(y) & "��")%></A></td>
	<%
	For j=0 To iCountCitys
		%><td><%=arrLineSet(j,i)%></td><%
	Next
	%>
  </tr>
  <%
	x=DateAdd("d",1,y)
  Next
  %>
</table>
<!-- ���ݱ���� -->
			</td>
        </tr>
        <tr align="left">
          <td colspan="4">
		  <A class='bluelink' HREF="#" onclick="javascript:window.open('rep_avg_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></A>���������ʾ��ҵ�����̵�ʱ��ƽ����Ӧʱ�䡣
             &nbsp; <A class='bluelink' HREF="#" onclick="javascript:window.open('rep_avg_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">����...</A></td>
        </tr>
      </table>
      <span id="subtitle"><br>
      </span> <span id="trimscreen">
      <form name="TrimForm" onsubmit="return false;">
      </form>
      </span> <span id=linegraph> </span> <span id=description> </span> </td>
  </tr>
</table>
</body>
</html>
<%
End If
%>
<!-- #include file="inc/foot.asp" -->
<SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToCity.js"></SCRIPT>
<%If bShowLink Then%><SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToGroup.js"></SCRIPT><%End If%>