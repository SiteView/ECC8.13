<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

' ***************************************ȡ�ô�����Ϣ**************************************
Trans_Id = Request.cookies("rep_trans")("id")
City_Id  = Request.cookies("rep_city")("id")
bFilteredTran = Len(Trans_Id)
bFilteredCity = Len(City_Id)

If bFilteredCity Then
	sql = "exec cq_tran_failreason_onecity " & prof_id & "," & City_Id & ",'" & startDate & "','" & endDate & "'"
Else
	sql = "exec cq_tran_failreason " & prof_id & ",'" & startDate & "','" & endDate & "'"
End If

'response.write sql
'response.end

Set rs=Server.CreateObject("adodb.recordset")  ' ȡ����
rs.Open sql, cnnDragon, 1, 1

If rs.RecordCount <= 0 Then
	Response.Write "<p>&nbsp;</P><P align='center'>û�д�����.</P>"
	Response.end
End If

'****************************�õ����еĴ������������������Cooky**************************
dim arrFailure(100,1)
dim strFailId   
dim strFailName 

rs.MoveFirst
While Not rs.Eof
	For i=0 to 100
		If ISNULL(arrFailure(i,0)) OR ISEMPTY(arrFailure(i,0)) then '���
			arrFailure(i,0) = rs("failcode")
			arrFailure(i,1) = rs("message")
			exit for
		Else
			if arrFailure(i,0) = rs("failcode") then Exit for
		End if
	Next
	rs.MoveNext
Wend
For i=0 to 100
	If ISNULL(arrFailure(i,0)) OR ISEMPTY(arrFailure(i,0)) then 
		exit for
	Else
		strFailId   = strFailId   & arrFailure(i,0) & ","
		strFailName = strFailName & arrFailure(i,1) & ","
	End if
Next
Response.cookies("rep_all_failure")("id")  = Left(strFailId,Len(strFailId)-1)
Response.cookies("rep_all_failure")("name")  = Left(strFailName,Len(strFailName)-1)


'****************************  ���ݹ����������ù���   ******************************
strFailCode = Request.Cookies("rep_sel_failure")("Id")
If Len(strFailCode) > 0 Then
	'rs.filter = "failcode IN (" & strFailCode & ")"
	strFilterFail = ""
	arrFailCode = split(strFailCode,",")
	For i=0 To UBound(arrFailCode)
		strFilterFail = strFilterFail & " failcode = " &  arrFailCode(i) & " OR"
	Next
	strFilterFail = Left(strFilterFail,Len(strFilterFail)-3)
	rs.filter = strFilterFail
End If

'*************************************�õ����е�ҵ������*********************************
'��ҵ������ֻ��һ��ʱ��ֱ�����ã�ɾ������Ĺ���
dim arrTran(100,1)
rs.MoveFirst
While Not rs.Eof
	For i=0 to 100
		If ISNULL(arrTran(i,0)) OR ISEMPTY(arrTran(i,0)) OR arrTran(i,0) = 0 then '���
			arrTran(i,0) = rs("trans_id")
			arrTran(i,1) = rs("trans_name")
			exit for
		Else
			if arrTran(i,0) = rs("trans_id") then Exit for
		End if
	Next
	rs.MoveNext
Wend

'*************************************��ҳ��ʾ��¼***************************************
const cnPageSize = 20 REM ÿҳ��ʾ��������¼
iRecCount = rs.RecordCount
If iRecCount > 0  Then
	rs.PageSize = cnPageSize

	iCurrPage  = CINT(Request.QueryString("pageno"))
	If Len(Request.Form("pageno")) > 0 Then iCurrPage = CINT(Request.Form("pageno"))
	iTotalPage = rs.PageCount
	If iCurrPage < 1 Then iCurrPage = 1
	If iCurrPage > iTotalPage then iCurrPage = iTotalPage

	rs.AbsolutePage = iCurrPage
	iRecStart = (iCurrPage - 1) * cnPageSize + 1
	iRecEnd	  = iCurrPage * cnPageSize
	If iRecEnd > iRecCount then iRecEnd = iRecCount
Else
	Response.Write "<p>&nbsp;</P><P align='center'>û�д�����.</P>"
	Response.end
End If
%>
<%bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)%>
<html>
<head>
<title>��������ⱨ�� www.speed.net.cn �й�����������ר��</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
</head>
<SCRIPT LANGUAGE="JavaScript">
<!--
function openFiltersWin(){
	winFilters = window.showModalDialog("tran_failReason_filter.htm",null,"dialogWidth:408px;dialogHeight:370px;")
//	alert(winFilters);
	return winFilters;
}

function closeFiltersWin() {
	if (typeof(winFilters)=="object"){
		winFilters.close();
	}
}

function refreshReport(){
	document.location.reload();
}
//-->
</SCRIPT>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<BR>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> <!-- ����BAR -->
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="44%" bgcolor="#CCCCCC"><font class=VerdanaDB10><b>ҵ������ʧ��ԭ��</b></font></td>
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
    <td colspan="3">
      <table width="820" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td width="417"><b>&nbsp;&nbsp;��ǰԤ�����ļ���<%=Request.cookies("rep_prf")("name")%><br>
            &nbsp; 
            <!--#Include file="inc/filter.asp"-->
            </b> <br>
            &nbsp;&nbsp;&nbsp;<a class="bluelink" href="#" onClick="if (openFiltersWin()=='yes') refreshReport();return false">���˴�������</A> 
          </td>
          <td width="403"> 
            <table border="0" cellspacing="0" cellpadding="0" width="399" align="right">
              <tr> 
                <td> 
                  <%
					Response.Write "<td><table border=0>"
					For i=0 to 100
						If ISNULL(arrTran(i,0)) OR ISEMPTY(arrTran(i,0)) OR arrTran(i,0) = 0 then
							response.Write "</table></td>"
							exit for 
						End If
						If i Mod 4 = 0 Then Response.Write "</table></td><td><table border=0>"
						response.write "<tr><td>&nbsp;<a class= 'bluelink' href='tran_failReason.asp?trans_id=" & arrTran(i,0) & "&trans_name=" & arrTran(i,1) & "'>" & arrTran(i,1) & "</a></td></tr>"
					Next
				%>
                </td>
              </tr>
            </table>
          </td>
        </tr>
        <tr> 
          <td width="417"> &nbsp;&nbsp;</td>
          <td width="403">&nbsp; </td>
        </tr>
        <tr> 
          <td colspan="2" align="center"> 
            <table border="0" cellspacing="1" cellpadding="0" width="802">
              <tr bgcolor="#330066" align="center"> 
                <td width="132"><font color="#ffffff">����ʱ��</font></td>
                <td width="106"><font color="#ffffff">ҵ����������</font></td>
                <td width="104"><font color="#ffffff">���ڳ���</font></td>
                <td width="196"><font color="#ffffff">��������</font></td>
                <td width="258"><font color="#ffffff">����ԭ��</font></td>
              </tr>
              <%
			If iRecCount > 0  Then
			  For i=0 to cnPageSize - 1
			  %>
              <tr bgcolor="<%=arrColor(i mod 2)%>"> 
                <td align="center" width="132"><%=rs("measurement_time")%>&nbsp;</td>
                <td align="center" width="106"><%=rs("trans_name")%>&nbsp;</td>
                <td align="center" width="104"><%=rs("cityname")%>&nbsp;</td>
                <td width="196">&nbsp;<%=rs("short_descp")%></td>
                <td width="258"> &nbsp; 
                  <%If IsNull(rs("message")) Or Len(rs("message"))=0 Then%>
                  δ֪ԭ����� 
                  <%Else%>
                  <%=rs("message")%> 
                  <%End If%>
                </td>
              </tr>
              <%
				rs.MoveNext
				If rs.Eof Then Exit For
			  Next
			End If
			  %>
            </table>
          </td>
        </tr>
        <tr> 
          <td colspan="2">&nbsp;</td>
        </tr>
        <form name="frmPageno" method="post" action="tran_failReason.asp">
          <tr align="center"> 
            <td colspan="2"> 
              <%If iCurrPage > 1 then%>
              [<a href="tran_failReason.asp?pageno=<%=1%>">&lt;&lt; ��ҳ</a>] [<a href="tran_failReason.asp?pageno=<%=iCurrPage - 1%>">&lt; 
              ��ҳ</a>] 
              <%Else%>
              <font class="Verbl8" color=gray>[��ҳ]</font> <font class="Verbl8" color=gray>[��ҳ]</font> 
              <%End If%>
              <%If iCurrPage < itotalPage Then%>
              [<a href="tran_failReason.asp?pageno=<%=iCurrPage + 1%>">��ҳ &gt;</a>] 
              [<a href="tran_failReason.asp?pageno=<%=iTotalPage%>">βҳ &gt;&gt;</a>] 
              <%Else%>
              <font class="Verbl8" color=gray>[��ҳ]</font> <font class="Verbl8" color=gray>[βҳ]</font> 
              &nbsp; 
              <%End If%>
              <input type="text" name="pageno" size="4" maxlength="4">
              ҳ 
              <input type="submit" name="Submit" value="Go">
            </td>
          </tr>
        </form>
        <tr align="center"> 
          <td colspan="2">�� <%=iRecCount%> ��������Ϣ,��ǰ��ʾ <%=iRecStart%> �� <%=iRecEnd%> 
            ��</td>
          <br>
        </tr>
        <tr> 
          <td colspan="2">&nbsp;<a class='bluelink' href="#" onClick="javascript:window.open('tran_failreason_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></a> 
            ���������ʾ��ÿ��ʧ�ܵ�ҵ�����̷�����ʱ�䣬���ڳ��м�����ľ���ԭ�� <a class='bluelink' href="#" onClick="javascript:window.open('tran_failreason_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">����...</a></td>
        </tr>
      </table>
      <p>&nbsp;</p>
      </td>
  </tr>
</table>
</body>
</html>
<%
rs.Close
Set rs = Nothing
%>
<!-- #include file="inc/foot.asp" -->
<SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToTransaction.js"></SCRIPT>
<%If bShowLink Then%><SCRIPT LANGUAGE="JavaScript" src="inc/setSelByToGroup.js"></SCRIPT><%End If%>