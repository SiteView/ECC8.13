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

Response.cookies("rep_isdatatable")=""

'response.write startDate & "<BR>"
'response.write endDate & "<BR>"
'response.end

If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

' ȡ��ƽ����Ӧʱ��(�Գ���)
If Len(Request.cookies("rep_trans")("id"))>0 Then
	If Len(Request.cookies("rep_city")("id"))>0 Then
		sql="exec yl_rep_avg_y_c_withid " & prof_id & "," & Request.cookies("rep_trans")("id") & "," & Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
	Else
		sql="exec yl_rep_avg_y_c_bytranid " & prof_id & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	sql="exec yl_rep_avg_y_c " & prof_id & ",'" & startDate & "','" & endDate & "'"
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
	Dim strCitys_id ' ����б��
	Dim strCitys_name ' ��������� ������������
	iMax=0 ' �����ֵ

	' �������ID�����ƣ����������ֵ
	oldid=0
	For i=0 To iRsRows
		If iMax<CInt(arrRs(3,i)) Then iMax=CInt(arrRs(3,i))
		If oldid<>CInt(arrRs(1,i)) Then
			strCitys_id=strCitys_id & arrRs(1,i) & ","
			strCitys_name=strCitys_name & arrRs(0,i) & ","
			oldid=CInt(arrRs(1,i))
		End If
	Next
	arrCitys_id=Split(strCitys_id, ",")
	arrCitys_name=Split(strCitys_name, ",")

	iCountCitys=UBound(arrCitys_id)-1 ' ��Ԥ�����ļ��������ٸ�����

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
    <td width="44%" bgcolor="#CCCCCC"><font class=VerdanaDB10><b>����ʱ��ƽ����Ӧʱ��&nbsp;</b></font></td>
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
          <td rowspan="3" width="187" align="left" valign="top" id=trans>
            <table cellpadding="1" width="100" cellspacing="2" border="0">
			<%
			If Len(Request.cookies("rep_trans")("id"))>0 Then
				url="rep_avg_y_c.asp"
			Else
				url="rep_avg_y_t.asp"
			End If
			bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)
			For i=0 To iCountCitys
				If bShowLink Then
			%>
			<tr>
				<td><%=arrCitys_name(i)%></td>
			</tr>
			<%
				Else
			%>
			<tr>
				<td><A class='bluelink' HREF="<%=url%>?selby=t&city_id=<%=arrCitys_id(i)%>&city_name=<%=arrCitys_name(i)%>" style="text-decoration:underline"><%=arrCitys_name(i)%></A></td>
			</tr>
			<%
				End If
			Next
			%>
            </table>
          </td>
        </tr>
        <tr>
          <td width="308" align="right">&nbsp;</td>
          <td width="287" align="right"><A class='bluelink' HREF="rep_avg_y_c_data.asp">���ݱ�</A></td>
          <td width="47" align="right">&nbsp;</td>
        </tr>
        <tr>
          <td colspan="3" align="center" valign="top">
		  <applet name=linechart codebase="../classes" code="NFLineChartApp.class" width=550 height=300 VIEWASTEXT align=center>
              <param	name=NFParamScript	value = '

	Background	= (White, NONE);

	GraphType	= ROWS;

	Footer	= ("",black,"TimesRoman",12,0 );
	Grid		= (lightGray, white, black);
	GridLine	= (HORIZONTAL, SOLID, 1);

	DwellLabel      = ("", white, "Courier", 12);
	DwellBox        = (red, SHADOW, 4);

	Legend		= ("", black, "TimesRoman", 12);
	BottomScroll=(0,12);

	LegendLayout	= (HORIZONTAL, BOTTOM);

	Header		= ("", black, "TimesRoman", 14);
	HeaderBox	= (white, RAISED, 0);



	RightTitle	= ("    ", white, "TimesRoman", 14);
	<%
	'On Error Resume Next
	ReDim arrLineSet(iCountCitys,11)
	oldid=0
	j=0
	For i=0 To iRsRows
		If oldid<>CInt(arrRs(1,i)) Then
			j=j+1
			oldid=CInt(arrRs(1,i))
		End If
		arrLineSet(j-1,CInt(arrRs(2,i))-1)=arrRs(3,i)
	Next
	For i=0 To iCountCitys
		Response.Write "LineSet" & i+1 & "="
		str=""
		For j=0 To 11
			If j=11 Then
				Response.Write arrLineSet(i,j) & ";"
			Else
				Response.Write arrLineSet(i,j) & ","
			End If
		Next
		Response.Write vbCrLf
	Next
	iMax=iMax+10
	%>
LineSets =
     <%
	For i=0 To iCountCitys
		If i=iCountCitys Then
			Response.Write "(""" & arrCitys_name(i) & """,);"
		Else
			Response.Write "(""" & arrCitys_name(i) & """,),"
		End If
	Next
	 %>
LineStyle =
	<%
	For i=0 To iCountCitys
		If i=iCountCitys Then
			Response.Write "(SOLID,2,);"
		Else
			Response.Write "(SOLID,2,),"
		End If
	Next
	%>
LineSymbol =
	<%
	For i=0 To iCountCitys
		If i=iCountCitys Then
			Response.Write "(DIAMOND, 6,BOTH, black,1 );"
		Else
			Response.Write "(DIAMOND, 6,BOTH, black,1 ),"
		End If
	Next
	%>
LeftScale =

    (0,<%=iMax%>,<%=iMax\10%>);
	LeftScroll=(0,<%=iMax%>);


LeftTitle	= ("     ƽ����Ӧʱ�� (��)",black,"TimesRoman",12,90 );

LeftFormat   = ( , "%f");
BottomFormat   = ( , "%d");
BottomTics	= ("ON", darkgray, "@TimesRoman", 12, 90);

BottomLabels	="1��","2��","3��","4��","5��","6��","7��","8��","9��","10��","11��","12��";
LeftTics	= ("ON", darkgray, "@TimesRoman", 12);
LeftTitleBox	= (white, SHADOW, 0);

'>
            </applet></td>
        </tr>
        <tr align="left">
          <td colspan="4">
		  <A class='bluelink' HREF="#" onclick="javascript:window.open('rep_avg_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></A>���������ʾ�˳��е�ʱ��ƽ����Ӧʱ�䡣
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