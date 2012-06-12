<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" --><!-- #include file="inc/TranCityArray.asp"-->
<html>
<head>
<title>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
<body onLoad="loading.style.display='none'" bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<!-- <div style="font-size:9pt;" id="loading" align="center"><img src="img/clock-ani.gif"><BR>数据查询中...</div> -->
<div id="loading" style="position:absolute; width:115px; height:43px; z-index:10; left: 89px; top: 38px"><br>
  数据查询中...</div>
<%response.flush%>
<%
If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

bExpand = false
if  Instr("hd",Request.cookies("rep_per")) > 0 OR Request.QueryString("expand") = "yes" then bExpand = true
'******************************************************
'执行存储过程,将程序中将要用到的数据保存到变量或数组中*
'******************************************************
dim rs
dim arrWorstTran(5,2) '三个最差业务流程
dim arrWorstCity(5,2) '三个最差城市性能

if bExpand then '如果存在数据则进行操作
	Set rs=Server.CreateObject("adodb.recordSet")
	'最差的三个业务流程----------------------------------------------------------------------
	sql="exec cq_trancondition " & prof_id & ",'" & Session.sessionId & "','" & startDate & "','" & endDate & "'"
	cnnDragon.Execute sql
	sql="select tc.*,t.trans_name from trancondition tc,transactions t where tc.trans_id = t.trans_id and tc.sessionid = '" & Session.sessionId & "'"
	sql=sql & " And Not(good is NULL and warning is NULL and bad is NULL and failed is NULL)"
	sql=sql & " Order by (failed+bad)*10000/allsum DESC"
	rs.open sql,cnnDragon,1,1
	i=0
	Do Until rs.Eof
		miAllsum = rs("allsum")
		arrworsttran(0,i) = rs("trans_id")
		arrworsttran(1,i) = rs("trans_name")
		if isNull(rs("good")) then
			arrworsttran(2,i) = 0
		else
			arrworsttran(2,i) = formatNumber(rs("good")/miAllsum * 100,1)
		end if

		if isNull(rs("warning")) then
			arrworsttran(3,i) = 0
		else
			arrworsttran(3,i) = formatNumber(rs("warning")/miAllsum * 100,1)
		end if

		if isNull(rs("bad")) then
			arrworsttran(4,i) = 0
		else
			arrworsttran(4,i) = formatNumber(rs("bad")/miAllsum * 100,1)
		end if

		if isNull(rs("failed")) then
			arrworsttran(5,i) = 0
		else
			arrworsttran(5,i) = formatNumber(rs("failed")/miAllsum * 100,1)
		end if
		rs.MoveNext
		i=i+1
	Loop
	rs.close
	iTranCount = i
	i=0

	'最差的三个城市--------------------------------------------------------------------------
	sql="exec cq_citycondition " & prof_id & ",'" & Session.sessionId & "','" & startDate & "','" & endDate & "'"
	cnnDragon.Execute sql
	sql="select cc.*,c.cityname from citycondition cc,city c where cc.city_id = c.city_id and cc.sessionid = '" & Session.sessionId & "'"
	sql=sql & " And Not(good is NULL and warning is NULL and bad is NULL and failed is NULL)"
	sql=sql & " Order by (failedper+badper) DESC"
	rs.open sql,cnnDragon,1,1
	Do until rs.Eof
		arrworstCity(0,i) = rs("city_id")
		arrworstCity(1,i) = rs("cityname")
		if isNull(rs("goodper")) then
			arrworstCity(2,i) = 0
		else
			arrworstCity(2,i) = rs("goodper")/10
		end if

		if isNull(rs("warningper")) then
			arrworstCity(3,i) = 0
		else
			arrworstCity(3,i) = rs("warningper")/10
		end if

		if isNull(rs("badper")) then
			arrworstCity(4,i) = 0
		else
			arrworstCity(4,i) = rs("badper")/10
		end if

		if isNull(rs("failedper")) then
			arrworstCity(5,i) = 0
		else
			arrworstCity(5,i) = rs("failedper")/10
		end if
		rs.MoveNext
		i = i+1
	Loop
	rs.close
	iCitycount = i
end if
''response.write iPixlHigh & ";" & iPixlNormal & ";" & iPixlLow
set rs=Nothing
'******************************
%>
<table border="0" cellspacing="3" cellpadding="0" width="478">
  <% If Not bExpand Then %>
  <tr align="left"> 
    <td colspan="3" height="50"> 
      <table width="100%" border="0">
        <tr> 
          <td><b><font class=VerBl8><b><img src="img/arrow_right.gif" width="13" height="13"><font class=VerBl8><b><a href="per_sum_d_3tran.asp?expand=yes">性能最差的三个业务流程:</a></b></font></b></font></b></td>
        </tr>
        <tr valign="top"> 
          <td>单击链接查看性能最差的三个业务流程.</td>
        </tr>
      </table>
    </td>
  </tr>
  <% Else %>
  <tr align="left"> 
    <td colspan="3" height="82"> 
      <table width="100%" border="0">
        <tr> 
          <td colspan="3"><b><font class=VerBl8><b>性能最差的三个业务流程:</b></font></b></td>
        </tr>
        <tr valign="top"> 
          <td width="17%" height="62"> 
            <table align=left border=0 cellpadding=0 cellspacing=0 width=67>
              <tr align=left> 
                <td align=left valign=center><img height=8 src="img/green_dot.gif" width=8></td>
                <td align=left valign=center>优秀</td>
              </tr>
              <tr align=left> 
                <td align=left valign=center><img height=8 src="img/yellow_dot.gif" width=8></td>
                <td align=left valign=center>警告</td>
              </tr>
              <tr align=left> 
                <td align=left valign=center><img height=8 src="img/red_dot.gif" width=8></td>
                <td align=left valign=center>危险</td>
              </tr>
              <tr align=left> 
                <td align=left valign=center><img height=8 src="img/black_dot.gif" width=8></td>
                <td align=left valign=center>失败</td>
              </tr>
            </table>
          </td>
          <td width="41%" height="62"> 
            <table width="100%" border="0">
              <tr align="center" valign="top"> 
                <%for i=0 to iTranCount-1%>
                <td width="55"><applet name=piechart codebase="../classes" code=NFPiechartApp.class width=55 height=55 id=Applet1 VIEWASTEXT>
                    " 
                    <param	name=NFParamScript value='
					Background	= (White, NONE);
					LabelPos      = 0.7;
					Pie3DDepth = 0;
					SliceBorder = (DOTTED ,0 , );
					DwellLabel    = ("", black, "Courier", 12);
					DwellBox      = (white, SHADOW, 2);
					Slices        =
					<%
					 Response.Write " ("
					   Response.Write arrWorstTran(2,i) 'goodper
					   Response.Write   ", x009966,),"
					   Response.Write " ("
					   Response.Write arrWorstTran(3,i) 'warningper
					   Response.Write ", xFFCC33, ),"
					   Response.Write " ("
					   Response.Write arrWorstTran(4,i) 'badper

					   Response.Write  ", xCC0000,),   "

					   Response.Write " ("
					   Response.Write arrWorstTran(5,i) 'failedper

					   Response.Write  ", black,); "
					  %>

                    ActiveLabels=("<%=arrWorstTran(2,i)%> %"),("<%=arrWorstTran(3,i)%>%"),("<%=arrWorstTran(4,i)%>%"),("<%=arrWorstTran(5,i)%>%");

				'>
                  </applet></td>
                <%Next%>
                <td>&nbsp;</td>
              </tr>
              <tr align="center" valign="top"> 
                <%
                      for i=0 to iTranCount-1
                      	response.write "<td>" & Cstr(i+1) & "</td>"
                      next
                      %>
              </tr>
            </table>
          </td>
          <td width="42%" height="62"> 
            <table width="100%" border="0">
              <tr> 
                <td><font
                  class=VerBl8><b>业务流程:</b></font></td>
              </tr>
              <%
                    for i=0 to iTranCount - 1
                    	response.write "<tr><td>"

                    	response.write "<a class='bluelink' href='#' onclick='parent.parent.parent.leftFrame.document.all.t2.click();"
						response.write "parent.parent.frames.conditionFrame.location.href=""condition.asp?n=tran_performance.asp"";"
						response.write "parent.parent.reportFrame.location.href=""tran_performance.asp?tranid=" & arrWorstTran(0,i) & "&tranname=" & arrWorstTran(1,i) 
						response.write """;'>" & Cstr(i+1) & "." & arrWorstTran(1,i) & "</a>"
						
						response.write "</td></tr>"
                    next
                    %>
            </table>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <%End If%>
</table>
</body>
</html>
<!-- #include file="inc/foot.asp" -->