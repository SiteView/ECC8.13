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
If Len(Request.cookies("rep_city")("id"))>0 Then
	If Len(Request.cookies("rep_trans")("id"))>0 Then
		sql="exec yl_rep_avg_d_withid " & prof_id & "," & Request.cookies("rep_city")("id") & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	Else
		sql="exec yl_rep_avg_d_bycityid " & prof_id & "," & Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	sql="exec yl_rep_avg_d " & prof_id & ",'" & startDate & "','" & endDate & "'"
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
	arrTrans_id=Split(strTrans_id, ",")
	arrTrans_name=Split(strTrans_name, ",")

	iCountTrans=UBound(arrTrans_id)-1 ' ��Ԥ�����ļ��������ٸ� Transaction

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
          <td width="287" align="right"><A class='bluelink' HREF="rep_avg_d.asp?showchart=1">ͼ��</A></td>
          <td width="47" align="right">&nbsp;</td>
        </tr>
        <tr>
          <td colspan="3" align="center" valign="top">
<!-- ���ݱ� -->
<%
x=Split(startDate," ") ' ȡ����

ReDim arrLineSet(iCountTrans,23)
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
	If Len(Request.cookies("rep_city")("id"))>0 Then
		url="rep_avg_d_data.asp"
	Else
		url="rep_avg_d_c_data.asp"
	End If
	bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)

	For i=0 To iCountTrans
		If bShowLink Then
	%>
	<td><FONT COLOR="#ffffff"><%=arrTrans_name(i)%></FONT></td>
	<%
		Else
	%>
	<td><A HREF="<%=url%>?selby=c&trans_id=<%=arrTrans_id(i)%>&trans_name=<%=arrTrans_name(i)%>" style="text-decoration:underline"><FONT COLOR="#ffffff"><%=arrTrans_name(i)%></FONT></A></td>
	<%
		End If
	Next
	%>
  </tr>
  <%
  For i=0 To 23
  %>
  <tr bgcolor="<%=arrColor(i mod 2)%>" align=center>
    <td><A HREF="javascript:goLink(<%=i%>)" style="text-decoration:underline"><%=FormatDateTime(DateValue(x(0)), vbLongDate) & " " & i & ":00"%></A></td>
	<%
	For j=0 To iCountTrans
		%><td><%=arrLineSet(j,i)%></td><%
	Next
	%>
  </tr>
  <%
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
<SCRIPT LANGUAGE="JavaScript">
<!--
function goLink(h)
{
	var y=<%=Year(DateValue(startDate))%>;
	var m=<%=Month(DateValue(startDate))%>;
	var d=<%=Day(DateValue(startDate))%>;
	parent.frames.conditionFrame.document.all.selPer.value="h";
	location.href="rep_avg_n_t_data.asp?per=h&d="+y+"-"+m+"-"+d+" "+h+":00&s="+y+"-"+m+"-"+d+" "+h+":00";
}

parent.frames.conditionFrame.document.frmCondition.selPer.value="d";
//-->
</SCRIPT>
<SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToTransaction.js"></SCRIPT>
<%If bShowLink Then%><SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToGroup.js"></SCRIPT><%End If%>