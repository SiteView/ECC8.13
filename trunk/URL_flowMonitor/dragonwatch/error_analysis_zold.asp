<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
On Error Resume Next
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

' ���������������Ӧ��ʱ��
' ѡ��ҵ������ʱ��ҵ������
'If Trim(Request.Form("selBy"))="t" Then
'	Response.cookies("rep_trans")("id")=""
'	Response.cookies("rep_trans")("name")=""
'End If
' ѡ�����ʱ�����
'If Trim(Request.Form("selBy"))="c" Then
'	Response.cookies("rep_city")("id")=""
'	Response.cookies("rep_city")("name")=""
'End If


If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

If Len(Request.cookies("rep_trans")("id"))>0 Then
	If Len(Request.cookies("rep_city")("id"))>0 Then
		sql="exec yl_error_withid " & prof_id & ", " & Request.cookies("rep_trans")("id") & "," & Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
	Else
		sql="exec yl_error_tranid " & prof_id & ", " & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	If Len(Request.cookies("rep_city")("id"))>0 Then
		sql="exec yl_error_cityid " & prof_id & "," & Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
	Else
		sql="exec yl_error_all " & prof_id & ",'" & startDate & "','" & endDate & "'"
	End If
End If

Set rs=Server.CreateObject("adodb.recordset")  ' ȡ����
rs.Open sql, cnnDragon, 1, 1
If rs.RecordCount=0 Then
	Response.Write "<Center>��ʱ��û�д�������</Center>"
Else
	arrRs=rs.GetRows(rs.RecordCount)
	rs.Close
	Set rs=Nothing

	Dim iRsCols, iRsRows, i, j, iMax
	iRsCols=UBound(arrRs) ' �ж����ֶ�
	iRsRows=UBound(arrRs,2) ' �ж���������
	
	iMax=0
	For i=0 To iRsRows
		If CLng(arrRs(3,i))>iMax Then iMax=CLng(arrRs(3,i))
	Next

	' ����
	bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)
%>
<html>
<head>
<title>ҵ�����̴������</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<table width="100%" border="0" cellspacing="1" cellpadding="2">
  <tr> 
    <td width="4%"><img src="img/dots.gif" width="33" height="32"></td>
    <td bgcolor="#CCCCCC" colspan="2"> 
      <table width="100%" border="0" cellspacing="1" cellpadding="3">
        <tr> 
          <td width="23%" height="18"><b>ҵ�����̴������</b></td>
          <td width="77%" height="18" align=right><b> 
            <%
	  If DateDiff("d", DateValue(startDate), DateValue(endDate))=0 Then
			Response.Write Year(startDate) & "��" & Month(startDate) & "��" & Day(startDate) & "��" & Hour(startDate) & "ʱ" & Minute(startDate) & "�� - " & Hour(endDate) & "ʱ" & Minute(endDate) & "��"
	  Else
			Response.Write Year(startDate) & "��" & Month(startDate) & "��" & Day(startDate) & "��" & Hour(startDate) & "ʱ" & Minute(startDate) & "�� - " & Year(endDate) & "��" & Month(endDate) & "��" & Day(endDate) & "��" & Hour(endDate) & "ʱ" & Minute(endDate) & "��"
	  End If
	  %>
            </b></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr> 
    <td colspan="2"> <B>��ǰԤ�����ļ���<%=request.cookies("rep_prf")("name")%><BR>
	<%
		If bShowLink Then
			Response.Write "���ˣ��飬" & Request.cookies("rep_trans")("name") & "��" & Request.cookies("rep_city")("name")
		Else
			If Len(Request.cookies("rep_trans")("id"))>0 Then
				Response.Write "���ˣ�ҵ�����̣�" & Request.cookies("rep_trans")("name")
			ElseIf Len(Request.cookies("rep_city")("id"))>0 Then
				Response.Write "���ˣ����У�" & Request.cookies("rep_city")("name")
			End If
		End If
	%>
	</B>
    </td>
    <td width="26%" rowspan="3" valign="top">
		<%	
			Set rs=cnnDragon.Execute("exec yl_profiletrans " & prof_id)
		%>
			<TABLE>
				<%
				Dim tmpTranID
				If Len(Request.cookies("rep_trans")("id"))=0 Then
					tmpTranID=0
				Else
					tmpTranID=CInt(Request.cookies("rep_trans")("id"))
				End If
				While Not rs.Eof
					If tmpTranID=CInt(rs(0)) Then
				%>
				<TR><TD><font color=gray><%=rs(1)%></font></TD></TR>
					<%Else%>
				<TR><TD><A HREF="error_analysis.asp?trans_id=<%=rs(0)%>&trans_name=<%=rs(1)%>" style="text-decoration:underline;color:blue"><%=rs(1)%></A></TD></TR>
				<%
					End If
					rs.MoveNext
				Wend%>
			</TABLE>
			<BR><BR>
		<%	
			Set rs=cnnDragon.Execute("exec yl_profilecitys " & prof_id)
		%>
			<TABLE>
				<%
				Dim tmpCityID
				If Len(Request.cookies("rep_city")("id"))=0 Then
					tmpCityID=0
				Else
					tmpCityID=CInt(Request.cookies("rep_city")("id"))
				End If
				While Not rs.Eof
					If tmpCityID=CInt(rs(0)) Then
				%>
				<TR><TD><font color=gray><%=rs(1)%></font></TD></TR>
					<%Else%>
				<TR><TD><A HREF="error_analysis.asp?city_id=<%=rs(0)%>&city_name=<%=rs(1)%>" style="text-decoration:underline;color:blue"><%=rs(1)%></A></TD></TR>
				<%
					End If
					rs.MoveNext
				Wend%>
			</TABLE>
		<%Set rs=Nothing%>
	</td>
  </tr>
  <tr>
    <td colspan="2" align="center"> 
      <!-- �������� -->
      <applet name=barchart
	codebase=../classes
	code=NFBarchartApp.class
 width=500 height=300>
        <param name=NFParamScript value = '
DebugSet	= LICENSE;

Background	= (white, NONE, 0, "");

BottomTics      = ("ON", black, "TimesRoman", 12);

LeftTics        = ("ON", black, "TimesRoman", 12);
<%'��ֻȡ��һ����¼ʱ iRsRows ֵΪ0, ����ʱ iMaxֵ��Ϊ0���� iMax\iRsRows ���ִ��ʱ���������On Error Resume Next��������%>
LeftScale       = (0, <%=iMax+iMax\iRsRows%>,<%=iMax\iRsRows%>);
LeftScroll=(0,<%=iMax+iMax\iRsRows%>);
BottomScroll=(0,<%=iRsRows%>);
LegendLayout	= (HORIZONTAL, BOTTOM);

BarLabels	= 
<%
For i=0 To iRsRows
	If i=iRsRows Then
		Response.Write """" & arrRs(0,i) & """" & ";"
	Else
		Response.Write """" & arrRs(0,i) & """" & ","
	End If
Next
%>

LeftTitle	= ("ҵ �� �� �� �� �� �� ��", black, "TimesRoman", 12,90);

Footer		= ("�� �� ״ ̬ ��", black, "TimesRoman", 12);
LeftTitleBox	= (, , 5);

DwellLabel	= ("", black, "Courier", 12);

DwellBox	= (yellow, RAISED, 3);

BarWidth=30;
Bar3DDepth = 0;
Grid		= (lightGray, white, black);
GridLine	= (HORIZONTAL, SOLID, 1);
GraphType	= GROUP;


DataSets	= ("Server #1", );

DataSet1	= 
<%
For i=0 To iRsRows
	If i=iRsRows Then
		Response.Write """" & arrRs(3,i) & """" & ";"
	Else
		Response.Write """" & arrRs(3,i) & """" & ","
	End If
Next
%>
'>
      </applet> 
      <!-- �������ݽ��������³���������ݱ� -->
    </td>
  </tr>
  <tr>
    <td colspan="2">
      <table width="100%" border="0" cellspacing="1" cellpadding="2" style="display:">
        <tr align="center" bgcolor="#330066"> 
          <td width="12%"><font color="#FFFFFF">����״̬��</font></td>
          <td width="22%"><font color="#FFFFFF">��������</font></td>
          <td width="48%"><font color="#FFFFFF">Ӣ������</font></td>
          <td width="9%"><font color="#FFFFFF">�������</font></td>
          <td width="8%"><font color="#FFFFFF">����ռ%</font></td>
        </tr>
        <%
Dim bShowLink, which

If (Len(Request.cookies("rep_trans")("id"))=0 And Len(Request.cookies("rep_city")("id"))=0) Or (Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)Then
	bShowLink=False
Else	
	bShowLink=True
	If Len(Request.cookies("rep_trans")("id"))>0 Then
		which="t"
	Else
		which="c"
	End If
End If

Dim iErrTotal
For i=0 To iRsRows
	iErrTotal=iErrTotal+CInt(arrRs(3,i))
Next

For i=0 To iRsRows
%>
        <tr bgcolor="<%=arrColor(i mod 2)%>"> 
          <td align="center"><!-- ������ -->
		  <%If bShowLink Then%>
		  <A HREF="javascript:openwindow(<%=arrRs(0,i)%>,'<%=which%>')" style="text-decoration:underline"><%=arrRs(0,i)%></A>
		  <%Else%>
		  <%=arrRs(0,i)%>
		  <%End If%>
		  </td>
          <td> 
            <%
		  If CInt(arrRs(0,i))<400 Then
			If CInt(arrRs(0,i))=0 Then
				Response.Write "δ֪ԭ�����"
			Else
				Response.Write "��ҳ�泬��ָ��ʧ��ʱ��"
			End If
		  Else
			Response.Write arrRs(1,i)
		  End If
		  %>
            <br>
          </td>
          <td><%=arrRs(2,i)%><br>
          </td>
          <td align="center"><%=arrRs(3,i)%></td>
          <td align="center"><%=Int((CInt(arrRs(3,i))/iErrTotal)*10000)/100%>%</td>
        </tr>
        <%
Next
%>
      </table><BR>
	  <TABLE>
		  <tr valign="top"> 
			<td height="16" align="center"><img src="img/lamp.gif" width="22" height="22"></td>
			<td valign="baseline" height="16" align="left">���������ʾ��ҵ�����̵Ĵ������ݡ�<a href="#"><font color="#0000FF">����...</font></a></td>
		  </tr>
	  </TABLE>
    </td>
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
function openwindow(code, which)
{
	window.open("error_analysis_"+which+".asp?code="+code,"",'toolbar=FALSE,resizable=1,scrollbars=2,height=400,width=700,screenx=550,screeny=300');
}
//-->
</SCRIPT>