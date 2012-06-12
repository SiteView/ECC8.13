<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" -->
<%
If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

' ***************************************取得错误信息**************************************
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

Set rs=Server.CreateObject("adodb.recordset")  ' 取数据
rs.Open sql, cnnDragon, 1, 1

If rs.RecordCount <= 0 Then
	Response.Write "<p>&nbsp;</P><P align='center'>没有错误发生.</P>"
	Response.end
End If

'****************************得到所有的错误码各描述，并存入Cooky**************************
dim arrFailure(100,1)
dim strFailId   
dim strFailName 

rs.MoveFirst
While Not rs.Eof
	For i=0 to 100
		If ISNULL(arrFailure(i,0)) OR ISEMPTY(arrFailure(i,0)) then '添加
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


'****************************  根据过滤条件设置过滤   ******************************
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

'*************************************得到所有的业务流程*********************************
'当业务流程只有一个时，直接引用，删除下面的过程
dim arrTran(100,1)
rs.MoveFirst
While Not rs.Eof
	For i=0 to 100
		If ISNULL(arrTran(i,0)) OR ISEMPTY(arrTran(i,0)) OR arrTran(i,0) = 0 then '添加
			arrTran(i,0) = rs("trans_id")
			arrTran(i,1) = rs("trans_name")
			exit for
		Else
			if arrTran(i,0) = rs("trans_id") then Exit for
		End if
	Next
	rs.MoveNext
Wend

'*************************************分页显示记录***************************************
const cnPageSize = 20 REM 每页显示多少条记录
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
	Response.Write "<p>&nbsp;</P><P align='center'>没有错误发生.</P>"
	Response.end
End If
%>
<%bShowLink=(Len(Request.cookies("rep_trans")("id"))>0 And Len(Request.cookies("rep_city")("id"))>0)%>
<html>
<head>
<title>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</title>
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
  <tr> <!-- 标题BAR -->
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="44%" bgcolor="#CCCCCC"><font class=VerdanaDB10><b>业务流程失败原因</b></font></td>
    <td width="53%" bgcolor="#CCCCCC" align="right"><font class=VerdanaDB10><b>时段:
      <%
	  If DateDiff("d", DateValue(startDate), DateValue(endDate))=0 Then
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时" & Minute(startDate) & "分 - " & Hour(endDate) & "时" & Minute(endDate) & "分"
	  Else
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时" & Minute(startDate) & "分 - " & Year(endDate) & "年" & Month(endDate) & "月" & Day(endDate) & "日" & Hour(endDate) & "时" & Minute(endDate) & "分"
	  End If
	  %>
	  </b></font></td>
  </tr>
  <tr valign="top">
    <td colspan="3">
      <table width="820" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td width="417"><b>&nbsp;&nbsp;当前预定义文件：<%=Request.cookies("rep_prf")("name")%><br>
            &nbsp; 
            <!--#Include file="inc/filter.asp"-->
            </b> <br>
            &nbsp;&nbsp;&nbsp;<a class="bluelink" href="#" onClick="if (openFiltersWin()=='yes') refreshReport();return false">过滤错误条件</A> 
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
                <td width="132"><font color="#ffffff">日期时间</font></td>
                <td width="106"><font color="#ffffff">业务流程名称</font></td>
                <td width="104"><font color="#ffffff">所在城市</font></td>
                <td width="196"><font color="#ffffff">错误描述</font></td>
                <td width="258"><font color="#ffffff">具体原因</font></td>
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
                  未知原因错误 
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
              [<a href="tran_failReason.asp?pageno=<%=1%>">&lt;&lt; 首页</a>] [<a href="tran_failReason.asp?pageno=<%=iCurrPage - 1%>">&lt; 
              上页</a>] 
              <%Else%>
              <font class="Verbl8" color=gray>[首页]</font> <font class="Verbl8" color=gray>[上页]</font> 
              <%End If%>
              <%If iCurrPage < itotalPage Then%>
              [<a href="tran_failReason.asp?pageno=<%=iCurrPage + 1%>">下页 &gt;</a>] 
              [<a href="tran_failReason.asp?pageno=<%=iTotalPage%>">尾页 &gt;&gt;</a>] 
              <%Else%>
              <font class="Verbl8" color=gray>[下页]</font> <font class="Verbl8" color=gray>[尾页]</font> 
              &nbsp; 
              <%End If%>
              <input type="text" name="pageno" size="4" maxlength="4">
              页 
              <input type="submit" name="Submit" value="Go">
            </td>
          </tr>
        </form>
        <tr align="center"> 
          <td colspan="2">共 <%=iRecCount%> 条错误信息,当前显示 <%=iRecStart%> 到 <%=iRecEnd%> 
            条</td>
          <br>
        </tr>
        <tr> 
          <td colspan="2">&nbsp;<a class='bluelink' href="#" onClick="javascript:window.open('tran_failreason_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></a> 
            这个报告显示了每个失败的业务流程发生的时间，所在城市及错误的具体原因。 <a class='bluelink' href="#" onClick="javascript:window.open('tran_failreason_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">更多...</a></td>
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