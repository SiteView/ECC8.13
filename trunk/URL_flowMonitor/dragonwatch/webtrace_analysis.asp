<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
'On Error Resume Next
%>
<html>
<head>
<title>����·��׷�ٷ���</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
<style type="text/css">
<!--
.webtrace {  font-size: 14.8px; font-weight: bold}
-->
</style>
<SCRIPT LANGUAGE="JavaScript" src="inc/tip.js"></SCRIPT>
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<!-- tip -->
<!-- #include file="inc/tip.asp" -->
<!-- tip -->
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td colspan="2" height="22"><font color="#003399"><span class="webtrace"><font color="#000066">
      </font></span></font><font color="#000066"><span class="webtrace">����·��׷�ٷ�����<font color="#6E6E6E" size=2>
	  ���г���
	  </font> </span></font></td>
  </tr>
  <tr> 
    <td colspan="2"> 
      <hr size=1>
    </td>
  </tr>
  <tr> 
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="97%" bgcolor="#CCCCCC"> 
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="28%" height="22"><b>����·��׷�ٷ���</b></td>
          <td align="right" width="72%" height="22"><b>ʱ��:
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
  <%
  'On Error Resume Next
  Dim tracetimes, sql, tmprs, tracetimes_unreach

'  Set rsSites=cnnDragon.Execute("exec yl_profiletrans " & Request.cookies("rep_prf")("id"))
'  Set rsSites=cnnDragon.Execute("select id,host from profilehost where profile_id=" & Request.cookies("rep_prf")("id"))
  Set rsSites=cnnDragon.Execute("select id,host from custhost where custid=" & Request.cookies("rep_cust")("id"))
  If rsSites.Eof And rsSites.Bof Then
		' ���û����
		'server.transfer "nodata.htm"
		'Response.Write "hello"
  Else
  Set tmprs=Server.CreateObject("adodb.recordset")
  While Not rsSites.Eof
		  ' ����ָ��ʱ���ڹ�TRACE�˶��ٴ�
		  'sql="exec yl_tracetimes " & rsSites(0) & ",'" & startDate & "','" & endDate & "'" 
		  'response.write sql
		  'tmprs.Open sql, cnnDragon, 1, 1
		  'If tmprs.Eof And tmprs.Bof Then
			'	tracetimes=0
		  'Else
		'		tracetimes=CInt(tmprs.RecordCount)
		  'End If
		  'tmprs.close

		  ' ����ָ��ʱ����TRACE�˴������м��� unreach ��
		  'sql="exec yl_tracetimes_unreach " & rsSites(0) & ",'" & startDate & "','" & endDate & "'" 
		  'response.write sql
		  'tmprs.Open sql, cnnDragon, 1, 1
		  'If tmprs.Eof And tmprs.Bof Then
			'	tracetimes_unreach=0
		  'Else
			'	tracetimes_unreach=CInt(tmprs.RecordCount)
		  'End If
		  'tmprs.close
  %>
  <!-- ѭ���г�����վ�� -->
  <tr align="center"> 
		<%
		'////////////////////////////////////////////////////////////////////////////////////////////
		' ȡ WEBTRACE �Ĳ��Խ��
		'////////////////////////////////////////////////////////////////////////////////////////////
		Dim iMax, iAvg, rs, arrError, iErrorRows, iError, arrUnreach, iUnreachRows, iUnreach

		Set rserror=Server.CreateObject("adodb.recordset")
		Set rsunreach=Server.CreateObject("adodb.recordset")
		' ����WEBTRACE��������ֵ
		sql="exec yl_webtrace " & Request.cookies("rep_prf")("id") & "," & rsSites(0) & ",'" & startDate & "','" & endDate & "'"
		' ����TRACE��ERROR�ĸ���
		sqlerror="exec yl_webtrace_error " & Request.cookies("rep_prf")("id") & "," & rsSites(0) & ",'" & startDate & "','" & endDate & "'"
		' ����TRACE��unreachable�ĸ���
		sqlunreach="exec yl_webtrace_unreach " & Request.cookies("rep_prf")("id") & "," & rsSites(0) & ",'" & startDate & "','" & endDate & "'"

		rserror.Open sqlerror, cnnDragon, 1, 1
		rsunreach.Open sqlunreach, cnnDragon, 1, 1

		If rserror.Eof And rserror.Bof Then  ' ���û�д���ѭ������Ϊ��
			iErrorRows=-1
		Else
			arrError=rserror.GetRows(rserror.RecordCount)  ' ȡ���д����¼������
			iErrorRows=UBound(arrError,2)	' ��������ж�����
		End If

		If rsunreach.Eof And rsunreach.Bof Then  ' ���û��unreach��ѭ������Ϊ��
			iUnreachRows=-1
		Else
			arrUnreach=rsunreach.GetRows(rsunreach.RecordCount)  ' ȡ����unreach��¼������
			iUnreachRows=UBound(arrUnreach,2)	' ����unreach�ж�����
		End If
		
		Set rserror=Nothing
		Set rsunreach=Nothing
		'response.write sql & "<HR>"
		Set rs=cnnDragon.Execute(sql)
		If rs.Eof And rs.Bof Then
			Response.Write "<td colspan=2 align=center>û������</td>"
		Else
		%>
    <td colspan="2"><br><b>���г��е� <%=rsSites(1)%></b><br>
      <br>
      <table width="97%" border="1" cellspacing="0" cellpadding="2">
        <tr align="center" bgcolor="#CCCCCC"> 
          <td height="17" width="13%">����</td>
          <td height="17" width="18%"><font color="#000000">������</font></td>
          <td height="17" width="32%"><font color="#000000"><img src="img/darkblue.gif" height=13 width=8>ƽ��DNSʱ�䣨���룩 
            <img src="img/lightblue.gif" height=13 width=8>ƽ��·��ʱ�䣨���룩</font></td>
          <td height="17" width="9%"><font color="#000000">���ֵ</font></td>
          <td height="17" width="9%"><font color="#000000">ƽ�������</font></td>
          <td height="17" width="7%"><font color="#FF0000">������</font></td>
          <td height="17" width="12%"><font color="#FF0000">���ɴ�/�ܴ���</font></td>
        </tr>
		<%
			Do While Not rs.Eof

			' ����trace�ܴ���
  		  sql="exec yl_tracetimes '" & rs(10) & "'," & rsSites(0) & "," & rs(11) & ",'" & startDate & "','" & endDate & "'" 
		  tmprs.Open sql, cnnDragon, 1, 1
		  If tmprs.Eof and tmprs.Bof Then
			tracetimes=0
		  Else
			tracetimes=tmprs.RecordCount
		  End If
		  tmprs.close
		  
			' ����trace��unreach�ܴ���
  		  sql="exec yl_tracetimes_unreach '" & rs(10) & "'," & rsSites(0) & "," & rs(11) & ",'" & startDate & "','" & endDate & "'" 
		  tmprs.Open sql, cnnDragon, 1, 1
		  If tmprs.Eof and tmprs.Bof Then
			tracetimes_unreach=0
		  Else
			tracetimes_unreach=tmprs.RecordCount
		  End If
		  tmprs.close
		%>
        <tr> 
          <td width="13%" align="center"><a href="webtrace_chart.asp?tranid=<%=rsSites(0)%>&tranname=<%=rsSites(1)%>&cityid=<%=rs(11)%>&cityname=<%=rs(1)%>"><%=rs(1)%></a></td>
          <td width="18%" align="center"><%=rs(10)%></td>
		  <%
		  iAvg=CInt(rs(3))
		  If CInt(rs(4))>iAvg Then iAvg=CInt(rs(4))
		  If CInt(rs(5))>iAvg Then iAvg=CInt(rs(5))
		  %>
          <td width="32%"><img src="img/darkblue.gif" height=13 width=<%=CInt(80*(CInt(rs(2))/100))%>><img src="img/lightblue.gif" height=13 width=<%=CInt(80*(iAvg/100))%>  style="cursor:hand;" onMouseOver="showtip(0,this,event,'ƽ��·��ʱ�䣺<%=iAvg%> ���룬ƽ��DNSʱ�䣺<%=CInt(rs(2))%> ����')" onMouseOut="hidetip()">
		  <%
		  If iAvg<10 Then
			Response.Write "<10"
		  Else
			Response.Write iAvg
		  End If
		  %>&nbsp;</td>
		  <%
		  iMax=CInt(rs(6))
		  If CInt(rs(7))>iMax Then iMax=CInt(rs(7))
		  If CInt(rs(8))>iMax Then iMax=CInt(rs(8))
		  %>
          <td width="9%" align="center"><%=iMax%></td>
          <td width="9%" align="center"><%=rs(9)\tracetimes%></td>
          <td width="7%" align="center">
		  <%
		  ' ��ӡ�������
		  iError=0
		  For i=0 To iErrorRows
			If Trim(rs(1))=Trim(arrError(1,i)) Then
				iError=arrError(2,i)
				Exit For
			End If
		  Next
		  Response.Write iError
		  %>
		  </td>
          <td width="12%" align="center">
		  <%
		  ' ��ӡ unreach �ĸ���
		  'iUnreach=0
		  'For i=0 To iUnreachRows
			'If Trim(rs(1))=Trim(arrUnreach(1,i)) Then
			'	iUnreach=arrUnreach(2,i)
			'	Exit For
			'End If
		  'Next
		  'Response.Write iUnreach
		  Response.Write tracetimes_unreach
		  %>
		  /<%=tracetimes%></td>
        </tr>
		<%
				rs.MoveNext
			Loop
		%>
      </table>
      <br>
    </td>
	<%End If%>
  </tr>
  <%
	rsSites.MoveNext
  Wend
  End If
  %>
  <!-- ѭ���г�����վ�㣨������ -->
</table>
</body>
</html>
<%
Set rs=Nothing
%>
<!-- #include file="inc/foot.asp" -->
