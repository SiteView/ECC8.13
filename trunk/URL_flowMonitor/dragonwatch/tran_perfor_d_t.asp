<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
'On Error Resume Next
' �������ID�����ƣ����ˣ�
If Len(Request.QueryString("cityid"))>0 Then
	Response.cookies("rep_city")("id")=Request.QueryString("cityid")
	Response.cookies("rep_city")("name")=Request.QueryString("cityname")
End If
' ����ҵ������ID�����ƣ����ˣ�
If Len(Request.QueryString("tranid"))>0 Then
	Response.cookies("rep_trans")("id")=Request.QueryString("tranid")
	Response.cookies("rep_trans")("name")=Request.QueryString("tranname")
End If

Response.cookies("rep_by")="t"

Dim i,j,k,startDate,endDate,prof_id


startDate=Request.cookies("rep_datetime")("start")
endDate=Request.cookies("rep_datetime")("end")

If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

If Len(Request.cookies("rep_city")("id"))>0 Then
	If Len(Request.cookies("rep_trans")("id"))>0 Then ' ��
		' ��������
		sql="exec yl_tran_perfor_d_t_withid " & prof_id & "," & Request.cookies("rep_city")("id") & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
		' ����ʧ��
		sql2="exec yl_tran_perfor_d_t_withid_failcount " & prof_id & "," & Request.cookies("rep_city")("id") & "," & Request.cookies("rep_trans")("id") & ",'" & startDate & "','" & endDate & "'"
	Else
		' ��������
		sql="exec yl_tran_perfor_d_t_cityid " & prof_id & "," & Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
		' ����ʧ��
		sql2="exec yl_tran_perfor_d_t_cityid_failcount " & prof_id & "," & Request.cookies("rep_city")("id") & ",'" & startDate & "','" & endDate & "'"
	End If
Else
	' ��������
	sql="exec yl_tran_perfor_d_t " & prof_id & ",'" & startDate & "','" & endDate & "'"
	' ����ʧ��
	sql2="exec yl_tran_perfor_d_t_failcount " & prof_id & ",'" & startDate & "','" & endDate & "'"
End If

'response.write sql & "<BR>"
'response.write sql2 & "<BR>"
Set rsTrans=Server.CreateObject("adodb.recordset")
Set rs=Server.CreateObject("adodb.recordset")
Set rs2=Server.CreateObject("adodb.recordset")

rsTrans.Open "exec yl_profiletrans " & prof_id, cnnDragon, 1, 1
rs.Open sql, cnnDragon, 1, 1
rs2.Open sql2, cnnDragon, 1, 1

If (rs.Eof And rs.Bof) And (rs2.Eof And rs2.Bof) Then
	Response.Write "<Center>��ʱ��û������</Center>"
Else

'	iCount=UBound(arrID)-1 ' ��������ٸ� Transaction
	iCount=rsTrans.RecordCount ' ��������ٸ� Transaction

	bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)
%>
<html>
<head>
<title>��������ⱨ�� www.speed.net.cn �й�����������ר��</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
<SCRIPT LANGUAGE="JavaScript" src="inc/tip.js"></SCRIPT>
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<!-- tip -->
<!-- #include file="inc/tip.asp" -->
<!-- tip -->
<table width="100%" border="0" cellspacing="1" cellpadding="0">
  <tr>
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td bgcolor="#CCCCCC" colspan="2">
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="38%"><b>ҵ���������ܷ���</b></td>
          <td width="62%" align="right"><b>ʱ��:
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
    <td colspan="2" height="11">&nbsp;</td>
    <td width="20%" height="11">&nbsp;</td>
  </tr>
  <tr>
    <td colspan="2" height="18">
      <p><b>��ǰԤ�����ļ���<%=Request.cookies("rep_prf")("name")%><br>
		  <!-- #include file="inc/filter.asp" -->
		</b></p>
    </td>
    <td width="20%" height="18" align="right">
      <table border="0" cellspacing="1" cellpadding="0" width="151">
        <tr>
          <td width="108" align="center">��</td>
          <td width="40"><img src="img/green_dot.gif" width="8" height="8"></td>
        </tr>
        <tr>
          <td width="108" align="center">����</td>
          <td width="40"><img src="img/yellow_dot.gif" width="8" height="8"></td>
        </tr>
        <tr>
          <td width="108" align="center">��</td>
          <td width="40"><img src="img/red_dot.gif" width="8" height="8"></td>
        </tr>
        <tr>
          <td width="108" align="center">ʧ�ܣ�һ��������</td>
          <td width="40"><img src="img/error_bit.gif" width="9" height="9"></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td colspan="3">
      <table width="100%" border="1" cellspacing="0" cellpadding="0">
        <tr>
          <td width="15%">&nbsp;</td>
          <td colspan="24"> <!-- ���� -->
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td width="4%"><img src="img/night.gif" width="43" height="31"></td>
                <td align="center" width="38%">����</td>
                <td width="16%" align="center"><img src="img/noon.gif" width="30" height="32"></td>
                <td width="37%" align="center">����</td>
                <td width="5%"><img src="img/night.gif" width="43" height="31"></td>
              </tr>
            </table>
          </td>
        </tr>
        <tr>
          <td width="15%" align="center">ʱ��</td>
		  <%
			Dim t,arrQueryString()
			Redim arrQueryString(23)
			t=DateValue(startDate)

			For i=0 To 23
				arrQueryString(i)="per=h&d=" &t& " " & i & ":00&s="& t & " " & i & ":00&e=" & t & " " & i & ":59"
				%><td align="center" height="25" style="cursor:hand;"><A class='bluelink' HREF="tran_perfor_n_t.asp?<%=arrQueryString(i)%>" style="text-decoration:underline"><%If i>9 Then%><%=i%><%Else%><%="0"&i%><%End If%></A></td><%
			Next
		  %>
        </tr>
		<%
		'==================
		' �����ݷ���������
		'Dim failcount,status,avgTime,okCount
		'ReDim arrTime(iCount,23)
		'ReDim arrTime2(iCount,23)
		'ReDim arrCount(iCount,23)
		'Redim arrCount2(iCount,23)
		'ReDim arrStatus(iCount,23)

		'failcount=0
		'avgTime=0
		'okCount=0
		'status=0
		'oldid=0
		'j=0
		'For i=0 To iRsRows
		'	If oldid<>CInt(arrRs(1,i)) Then
		'		j=j+1
		'		oldid=CInt(arrRs(1,i))
		'		For k=0 To iRsRows2
		'			If arrRs(1,i)=arrRs2(1,k) Then
		'				arrTime2(j-1,arrRs2(2,k))=arrRs2(3,k)
		'				arrCount2(j-1,arrRs2(2,k))=arrRs2(4,k)
		'			End If
		'		Next
		'	End If
		'	arrTime(j-1,CInt(arrRs(2,i)))=arrRs(3,i)
		'	arrCount(j-1,CInt(arrRs(2,i)))=arrRs(4,i)
		'	arrStatus(j-1,CInt(arrRs(2,i)))=arrRs(5,i)
		'Next
		'==================
		Dim url
		If Len(Request.cookies("rep_city")("id"))>0 Then ' �����transid������Լ�
			url="tran_perfor_d_t.asp"
		Else
			url="tran_perfor_d_c.asp"
		End If

		Dim theid, arrErr(), iErrs
		' ѭ��Ԥ�����ļ�������������ҵ������
		Do While Not rsTrans.Eof
			Response.Write "<tr>"
%>
          <td width="15%" height="30" align="center"><A class='bluelink' style="text-decoration:underline" HREF="<%=url%>?tranid=<%=rsTrans(0)%>&tranname=<%=rsTrans(1)%>"><%=rsTrans(1)%></A>&nbsp;</td>
<%			
			Redim cell(23) 
			For i=0 To 23
				rs2.Filter="trans_name='" & rsTrans(1) & "' and list=" & i
				If rs2.Eof Then
					iErrs=0
				Else
					iErrs=rs2(4)
				End If
				'cell(i)="<td style='cursor:hand;' align=center>&nbsp;</td>"
				cell(i)="<td onClick=" & Chr(34) & "location.href='tran_perfor_n_c.asp?tranid=" & rsTrans(0) & "&tranname=" & rsTrans(1) & "&" & arrQueryString(i) & "'" & Chr(34) & " align='center' style='cursor:hand;' onMouseOver=" & Chr(34) & "showtip(0,this,event,'ƽ����Ӧʱ�䣺0 �룬��� 0 ��ҵ������<BR>ʧ�� " & iErrs & " ��ҵ������')" & Chr(34) & " onMouseOut='hidetip()'>&nbsp;</td>"
				rs2.Filter=""
			Next

			rs.Filter="trans_name='" & rsTrans(1) & "'"
			'i=0
			While Not rs.Eof
				'cell(CInt(rs(2)))="<td style='cursor:hand;' bgcolor='" & arrColor2(CInt(rs(5))) & "'>&nbsp;</td>"
				rs2.Filter="trans_name='" & rsTrans(1) & "' and list=" & CInt(rs(2))
				If rs2.Eof Then
					iErrs=0
				Else
					iErrs=rs2(4)
				End If
				cell(Int(rs(2)))="<td onClick=" & Chr(34) & "location.href='tran_perfor_n_c.asp?tranid=" & rsTrans(0) & "&tranname=" & rsTrans(1) & "&" & arrQueryString(Int(rs(2))) & "'" & Chr(34) & " bgcolor='" & arrColor2(CInt(rs(5))) & "' align='center' style='cursor:hand;' onMouseOver=" & Chr(34) & "showtip(" & CInt(rs(5)) & ",this,event,'ƽ����Ӧʱ�䣺" & rs(3) & " �룬��� " & rs(4) & " ��ҵ������<BR>ʧ�� " & iErrs & " ��ҵ������')" & Chr(34) & " onMouseOut='hidetip()'>&nbsp;</td>"
				rs.MoveNext
				'i=i+1
				rs2.Filter=""
			Wend

				rs2.Filter=""
				rs2.Filter="trans_name='" & rsTrans(1) & "'"
			While Not rs2.Eof
				theid=CInt(rs2(2))
				cell(theid)=Left(cell(theid),Len(cell(theid))-5) & "<img src='img/error_bit.gif'>&nbsp;</td>"
				rs2.MoveNext
			Wend

			Response.Write Join(cell)
			Response.Write "</tr>" & vbCrLf
			rsTrans.MoveNext
		Loop
%>
      </table>
      <br>
    </td>
  </tr>
  <tr>
    <td width="3%" align="center"><A class='bluelink' HREF="#" onclick="javascript:window.open('tran_perfor_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img src="img/lamp.gif" width="22" height="22" border="0"></A></td>
    <td colspan="2"> �ò�ͬ��ɫ����ҵ������ƽ����Ӧʱ���ʧ�ܵ�ҵ�����̡� <A class='bluelink' HREF="#" onclick="javascript:window.open('tran_perfor_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">����...</A> </td>
  </tr>
</table>
</body>
</html>
<%
End If
%>
<!-- #include file="inc/foot.asp" -->
<SCRIPT LANGUAGE="JavaScript">parent.frames.conditionFrame.document.all.selPer.value="d";</SCRIPT>
<SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToTransaction.js"></SCRIPT>
<%If bShowLink Then%><SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToGroup.js"></SCRIPT><%End If%>
