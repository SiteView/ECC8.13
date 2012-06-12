<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!-- #include file="inc/getTime.asp" --><!-- #include file="inc/TranCityArray.asp"-->
<html>
<head>
<title>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
<script language="JavaScript">
<!--
function MM_reloadPage(init) {  //reloads the window if Nav4 resized
  if (init==true) with (navigator) {if ((appName=="Netscape")&&(parseInt(appVersion)==4)) {
    document.MM_pgW=innerWidth; document.MM_pgH=innerHeight; onresize=MM_reloadPage; }}
  else if (innerWidth!=document.MM_pgW || innerHeight!=document.MM_pgH) location.reload();
}
MM_reloadPage(true);
// -->
</script>
</head>
<script language=javascript>
function showhideBy(b){
	if (window.parent.frames){
		if (b){
			window.parent.frames.conditionFrame.document.all.divBy1.style.visibility="visible";
			window.parent.frames.conditionFrame.document.all.divBy2.style.visibility="visible";
		}else{
			window.parent.frames.conditionFrame.document.all.divBy1.style.visibility="hidden";
			window.parent.frames.conditionFrame.document.all.divBy2.style.visibility="hidden";
		}
	}
}
</script>

<body onLoad="loading.style.display='none'" bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<!-- <div style="font-size:9pt;" id="loading" align="center"><img src="img/clock-ani.gif"><BR>数据查询中...</div> -->
<div id="loading" style="position:absolute; width:115px; height:84px; z-index:1; left: 394px; top: 173px"><img src="img/clock-ani.gif"><BR>
  数据查询中...</div>

<%response.flush%>
<%
If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

'******************************************************
'执行存储过程,将程序中将要用到的数据保存到变量或数组中*
'******************************************************
dim rs
dim iGood,iWarning,iBad,iFailed,iAllSum
dim arrProfileCondition(3) 'good,warn,bad,failed四个数据

dim arr_all_tran(5,100)   '所有Tran
dim arr_all_city(5,100)   '所有City
dim arrWorstTran(5,2) '三个最差业务流程
dim arrWorstCity(5,2) '三个最差城市性能
dim bEmpty            '数据是否为空
dim iCityCount        '城市数目
dim iValidCity
dim iTranCount        '业务流程数目
dim iValidTran
dim iAlarmNums        '报警数目

'整体性能--------------------------------------------------------------------------------
sql="exec cq_profilecondition " & prof_id & ",'" & startDate & "','" & endDate & "'"
'response.write sql
'response.end
Set rs=Server.CreateObject("adodb.recordSet")

rs.Open sql,cnnDragon,1,1
if rs.Eof And rs.Bof then '如果数据为空
	bEmpty = true
	iAllSum = 0
	iFailed = 100
else
	do until rs.Eof
		arrProfileCondition(rs("status") - 1) = rs("status_count")
		rs.MoveNext
	Loop
	iAllSum = arrProfileCondition(0) + arrProfileCondition(1) + arrProfileCondition(2) + arrProfileCondition(3)
	iGood		= formatnumber(arrProfileCondition(0) * 100 / iAllSum,1)
	iWarning	= formatnumber(arrProfileCondition(1) * 100 / iAllSum,1)
	iBad			= formatnumber(arrProfileCondition(2) * 100 / iAllSum,1)
	iFailed		= formatnumber(arrProfileCondition(3) * 100 / iAllSum,1)

	bEmpty = false
end if
rs.close
if Not bEmpty then '如果存在数据则进行操作
	'最差的三个业务流程----------------------------------------------------------------------
	sql="exec cq_trancondition " & prof_id & ",'" & startDate & "','" & endDate & "'"
	rs.open sql,cnnDragon,1,1

	iTranCount = 0
	iOldtranId = 0
	Do Until rs.Eof
		if CInt(rs("trans_id")) <> iOldtranId then
			iOldtranId = rs("trans_id")
			iTranCount = iTranCount + 1
			arr_all_tran(0,iTranCount-1) = rs("trans_id")
			arr_all_tran(1,iTranCount-1) = rs("trans_name")
		end if
		arr_all_tran(rs("status")+1,iTranCount-1) = rs("status_count")

		rs.MoveNext
	Loop

	rs.Close
	'>>对aaAlltran()进行排序
	For i=0 to iTranCount -1
		For j=i+1 To iTranCount-1
			If (arr_all_tran(4,j) + arr_all_tran(5,j)) / (arr_all_tran(2,j) + arr_all_tran(3,j)+arr_all_tran(4,j) + arr_all_tran(5,j)) > (arr_all_tran(4,i) + arr_all_tran(5,i)) / (arr_all_tran(2,i) + arr_all_tran(3,i)+arr_all_tran(4,i) + arr_all_tran(5,i)) then
				'交换
				arr_all_tran(0,100) = arr_all_tran(0,i)
				arr_all_tran(1,100) = arr_all_tran(1,i)
				arr_all_tran(2,100) = arr_all_tran(2,i)
				arr_all_tran(3,100) = arr_all_tran(3,i)
				arr_all_tran(4,100) = arr_all_tran(4,i)
				arr_all_tran(5,100) = arr_all_tran(5,i)

				arr_all_tran(0,i) = arr_all_tran(0,j)
				arr_all_tran(1,i) = arr_all_tran(1,j)
				arr_all_tran(2,i) = arr_all_tran(2,j)
				arr_all_tran(3,i) = arr_all_tran(3,j)
				arr_all_tran(4,i) = arr_all_tran(4,j)
				arr_all_tran(5,i) = arr_all_tran(5,j)

				arr_all_tran(0,j) = arr_all_tran(0,100)
				arr_all_tran(1,j) = arr_all_tran(1,100)
				arr_all_tran(2,j) = arr_all_tran(2,100)
				arr_all_tran(3,j) = arr_all_tran(3,100)
				arr_all_tran(4,j) = arr_all_tran(4,100)
				arr_all_tran(5,j) = arr_all_tran(5,100)
			End If
		Next
	Next
	
	'>>
	For i=0 to 2
		arrWorstTran(0,i) = arr_all_Tran(0,i)
		arrWorstTran(1,i) = arr_all_Tran(1,i)
		iSumTran = arr_all_Tran(2,i) + arr_all_Tran(3,i)+ arr_all_Tran(4,i) + arr_all_Tran(5,i) + 0.000001
		for j=2 to 5
			arrWorstTran(j,i) = FormatNumber(arr_all_Tran(j,i) * 100 / iSumTran , 1)
		next
	Next

'	for i=0 to iTranCount - 1
'		for j=0 to 5
'			response.write arrWorstTran(j,i) & " , "
'		next
'		response.write "<br>"
'	Next


'最差的三个城市--------------------------------------------------------------------------
	sql="exec cq_citycondition " & prof_id & ",'" & startDate & "','" & endDate & "'"
	rs.open sql,cnnDragon,1,1

	iCityCount = 0
	iOldCityId = 0
	Do Until rs.Eof
		if CInt(rs("City_id")) <> iOldCityId then
			iOldCityId = rs("City_id")
			iCityCount = iCityCount + 1
			arr_all_City(0,iCityCount-1) = rs("City_id")
			arr_all_City(1,iCityCount-1) = rs("City_name")
		end if
		arr_all_City(rs("status")+1,iCityCount-1) = rs("status_count")

		rs.MoveNext
	Loop

	rs.Close
	'>>对aaAllCity()进行排序
	For i=0 to iCityCount -1
		For j=i+1 To iCityCount-1
			If (arr_all_City(4,j) + arr_all_City(5,j)) / (arr_all_City(2,j) + arr_all_City(3,j)+arr_all_City(4,j) + arr_all_City(5,j)) > (arr_all_City(4,i) + arr_all_City(5,i)) / (arr_all_City(2,i) + arr_all_City(3,i)+arr_all_City(4,i) + arr_all_City(5,i)) then
				'交换
				arr_all_City(0,100) = arr_all_City(0,i)
				arr_all_City(1,100) = arr_all_City(1,i)
				arr_all_City(2,100) = arr_all_City(2,i)
				arr_all_City(3,100) = arr_all_City(3,i)
				arr_all_City(4,100) = arr_all_City(4,i)
				arr_all_City(5,100) = arr_all_City(5,i)

				arr_all_City(0,i) = arr_all_City(0,j)
				arr_all_City(1,i) = arr_all_City(1,j)
				arr_all_City(2,i) = arr_all_City(2,j)
				arr_all_City(3,i) = arr_all_City(3,j)
				arr_all_City(4,i) = arr_all_City(4,j)
				arr_all_City(5,i) = arr_all_City(5,j)

				arr_all_City(0,j) = arr_all_City(0,100)
				arr_all_City(1,j) = arr_all_City(1,100)
				arr_all_City(2,j) = arr_all_City(2,100)
				arr_all_City(3,j) = arr_all_City(3,100)
				arr_all_City(4,j) = arr_all_City(4,100)
				arr_all_City(5,j) = arr_all_City(5,100)
			End If
		Next
	Next
	
	'>>
	For i=0 to 2
		arrWorstCity(0,i) = arr_all_City(0,i)
		arrWorstCity(1,i) = arr_all_City(1,i)
		iSumTran = arr_all_City(2,i) + arr_all_City(3,i)+ arr_all_City(4,i) + arr_all_City(5,i) + 0.000001
		for j=2 to 5
			arrWorstCity(j,i) = FormatNumber(arr_all_City(j,i) * 100 / iSumTran , 1)
		next
	Next

'	for i=0 to iCityCount - 1
'		for j=0 to 5
'			response.write arrWorstCity(j,i) & " , "
'		next
'		response.write "<br>"
'	Next
'	response.end

	If iTranCount > 3 then iTranCount = 3
	If iCityCount > 3 then iCityCount  =3

	'设置报警单元数目----------------------------------------------------------
	iAlarmHigh	= 0
	iAlarmNormal= 0
	iAlarmLow	= 0
	sql="exec cq_alertNotices " & prof_id &  ", '" & startDate & "', '" & endDate & "'"
	rs.open sql,cnnDragon,1,1
	If Not (rs.Bof And rs.Eof) then
		iAlarmHigh	= rs("severity_High")
		iAlarmNormal= rs("severity_Normal")
		iAlarmLow	= rs("severity_Low")
	End If

	iAlarmCount = iAlarmHigh + iAlarmNormal + iAlarmLow
	If iAlarmCount > 0 Then
		iPixlHigh	= CInt(iAlarmHigh   / iAlarmCount * 168)
		iPixlNormal = CInt(iAlarmNormal / iAlarmCount * 168)
		iPixlLow	= 168 - iPixlHigh - iPixlNormal
	End If
	rs.Close
end if
''response.write iPixlHigh & ";" & iPixlNormal & ";" & iPixlLow
set rs=Nothing
'******************************
%>
<BR>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="44%" bgcolor="#CCCCCC"><b>性能表现</b></td>
    <td width="53%" bgcolor="#CCCCCC" align="right"><b>时段:
      <%
	  If DateDiff("d", DateValue(startDate), DateValue(endDate))=0 Then
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时" & Minute(startDate) & "分 - " & Hour(endDate) & "时" & Minute(endDate) & "分"
	  Else
			Response.Write Year(startDate) & "年" & Month(startDate) & "月" & Day(startDate) & "日" & Hour(startDate) & "时" & Minute(startDate) & "分 - " & Year(endDate) & "年" & Month(endDate) & "月" & Day(endDate) & "日" & Hour(endDate) & "时" & Minute(endDate) & "分"
	  End If
	  %>
	  </b></td>
  </tr>
  <tr valign="top">
    <td colspan="3">&nbsp; <br>
      <table border="0" cellspacing="3" cellpadding="0" width="876">
        <tr align="left">
          <td colspan="3" height="175">
            <%
		if bEmpty then
			response.write "<center>没有整体性能数据.</center>"
		else
		%>
            <table border=0 width="100%">
              <tr>
                <td><b>所有业务流程平均性能: </b></td>
              </tr>
              <tr></tr>
              <tr>
                <td height="126">
                  <table align=left border=0 width="50%">
                    <tr align=left valign=top>
                      <td>
                        <table align=left border=0 cellpadding=0 cellspacing=0 width=150>
                          <tr align=left>
                            <td align=left valign=center><img height=8 src="img/green_dot.gif" width=8></td>
                            <td align=left valign=center>优秀 (<%=iGood%>%) &nbsp;</td>
                          </tr>
                          <tr align=left>
                            <td align=left valign=center><img height=8 src="img/yellow_dot.gif" width=8></td>
                            <td align=left valign=center>警告 (<%=iWarning%>%) &nbsp;</td>
                          </tr>
                          <tr align=left>
                            <td align=left valign=center><img height=8 src="img/red_dot.gif" width=8></td>
                            <td align=left valign=center>危险 (<%=iBad%>%) &nbsp;</td>
                          </tr>
                          <tr align=left>
                            <td align=left valign=center><img height=8 src="img/black_dot.gif" width=8></td>
                            <td align=left valign=center>失败 (<%=iFailed%>%) &nbsp;</td>
                          </tr>
                        </table>
                      </td>
                      <td width=100> <applet name=piechart codebase="../classes" code=NFPiechartApp.class width=100 height=100 id=Applet1 VIEWASTEXT>
                          <param	name=NFParamScript value='
					Background	= (White, NONE);
					LabelPos      = 0.5;
					SliceBorder = (DOTTED ,0 , );
					Pie3DDepth = 0;
                    DwellLabel    = ("", black, "Courier", 12);
					DwellBox      = (white, SHADOW, 2);
					Slices        =
					<% Response.Write " ("
					   Response.Write iGood
					   Response.Write   ", x009966,),"
					   Response.Write " ("
					   Response.Write iWarning
					   Response.Write ", xFFCC33, ),"
					   Response.Write " ("
					   Response.Write iBad
					   Response.Write  ", xCC0000,),   "
					   Response.Write " ("
					   Response.Write iFailed
					   Response.Write  ", black,);   "

					   %>
                     ActiveLabels=("<%=iGood%>%"),("<%=iWarning%>%"),("<%=iBad%>%"),("<%=iFailed%>%");

				'>
                        </applet> </td>
                    </tr>
                  </table>
                </td>
              </tr>
            </table>
            <%end if%>
          </td>
          <td width="371" height="175">
            <table width="100%" border="0">
              <tr>
                <td><font class=VerBl8><b>业务流程统计:</b></font></td>
              </tr>
              <tr>
                <td height="126"><font class=VerBl8><nobr>业务流程测试数据个数: <%=iAllSum%></nobr><br>
                  <nobr>业务流程成功率: <%=Int(100-iFailed)%>%</nobr></font>
                  <p>&nbsp;</p>
                </td>
              </tr>
            </table>
          </td>
        </tr>
        <%if Not bEmpty then%>
        <tr align="left">
          <td colspan="3" height="82">
            <table width="100%" border="0">
              <tr>
                <td colspan="3"><b><font class=VerBl8><b>性能最差的三个业务流程性能:</b></font></b></td>
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
                    	response.write "<a class='bluelink' href='tran_performance.asp?tranid=" & arrWorstTran(0,i) & "&tranname=" & arrWorstTran(1,i) & "' onclick='parent.parent.leftFrame.document.all.t2.click();parent.conditionFrame.location.href=""condition.asp?n=tran_performance.asp"";showhideBy(1)'>" & Cstr(i+1) & "." & arrWorstTran(1,i) & "</a>"
                    	response.write "</td></tr>"
                    next
                    %>
                  </table>
                </td>
              </tr>
            </table>
          </td>
          <td width="371" height="82">
            <table width="100%" border="0">
              <tr>
                <td colspan="3"><b><font class=VerBl8><b>性能最差的三个城市:</b></font></b></td>
              </tr>
              <tr valign="top">
                <td width="17%">
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
                <td width="41%">
                  <table width="100%" border="0">
                    <tr align="center" valign="top">
                      <%for i=0 to iCityCount-1%>
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
					   Response.Write arrWorstCity(2,i) 'goodper
					   Response.Write   ", x009966,),"
					   Response.Write " ("
					   Response.Write arrWorstCity(3,i) 'warningper
					   Response.Write ", xFFCC33, ),"
					   Response.Write " ("
					   Response.Write arrWorstCity(4,i) 'badper

					   Response.Write  ", xCC0000,),   "

					   Response.Write " ("
					   Response.Write arrWorstCity(5,i) 'failedper

					   Response.Write  ", black,); "
					  %>

                    ActiveLabels=("<%=arrWorstCity(2,i)%> %"),("<%=arrWorstCity(3,i)%>%"),("<%=arrWorstCity(4,i)%>%"),("<%=arrWorstCity(5,i)%>%");

				'>
                        </applet></td>
                      <%Next%>
                      <td>&nbsp;</td>
                    </tr>
                    <tr align="center" valign="top">
                      <%
                      for i=0 to iCityCount-1
                      	response.write "<td>" & Cstr(i+1) & "</td>"
                      next
                      %>
                    </tr>
                  </table>
                </td>
                <td width="42%">
                  <table width="100%" border="0">
                    <tr>
                      <td><font
                  class=VerBl8><b>城市:</b></font></td>
                    </tr>
                    <%
                    for i=0 to iCityCount - 1
                    	response.write "<tr><td>"
                    	response.write "<a class='bluelink' href='tran_performance.asp?cityid=" & arrWorstCity(0,i) & "&cityname=" & arrWorstCity(1,i) & "' onclick='parent.parent.leftFrame.document.all.t2.click();parent.conditionFrame.location.href=""condition.asp?n=tran_performance.asp"";showhideBy(1)'>" & Cstr(i+1) & "." & arrWorstCity(1,i) & "</a>"
                    	response.write "</td></tr>"
                    next
                    %>
                  </table>
                </td>
              </tr>
            </table>
          </td>
        </tr>
        <tr align="left">
          <td colspan="3" height="50">&nbsp;</td>
          <td width="371" height="50">&nbsp;</td>
        </tr>
        <tr align="left">
          <td colspan="3">
		<% If iAlarmCount >0 Then %>
			<table width="100%" border="0">
              <tr>
                <td colspan="2"><b><font class=VerBl8><b>发生的报警:</b></font></b></td>
              </tr>
              <tr valign="top">
                <td width="22%">
                  <table align=left border=0 cellpadding=0 cellspacing=0 width=95%>
                    <tr align=left>
                      <td align=left valign=center><img height=8 src="img/green_dot.gif" width=8></td>
                      <td align=left valign=center>轻微(<%=iAlarmLow%>)</td>
                    </tr>
                    <tr align=left>
                      <td align=left valign=center><img height=8 src="img/yellow_dot.gif" width=8></td>
                      <td align=left valign=center>一般(<%=iAlarmNormal%>)</td>
                    </tr>
                    <tr align=left>
                      <td align=left valign=center><img height=8 src="img/red_dot.gif" width=8></td>
                      <td align=left valign=center>严重(<%=iAlarmHigh%>)</td>
                    </tr>
                  </table>
                </td>
                <td width="78%">
                  <table border="0" cellspacing="0" cellpadding="0" width="345">
                    <tr>
                      <td width="181"><img src="img/AlertBar_top.gif" width="168" height="32"></td>
                      <td width="659"></td>
                    </tr>
                    <tr>
                      <td width="181"><%
					If iPixlLow		<> 0 then Response.write "<a href='#' title='" & iAlarmLow & "个轻微报警'><img src='img/green_dot.gif' width='" & iPixlLow & "' height='6' border='0'></a>"
					If iPixlNormal	<> 0 then Response.write "<a href='#' title='" & iAlarmNormal & "个一般报警'><img src='img/yellow_dot.gif' width='" & iPixlNormal & "' height='6' border='0'></a>"
					If iPixlHigh	<> 0 then Response.write "<a href='#' title='" & iAlarmHigh & "个严重报警'><img src='img/red_dot.gif' width='" & iPixlHigh & "' height='6' border='0'></a>"
					%></td>
                      <td width="659"></td>
                    </tr>
                    <tr>
                      <td width="181"><img src="img/AlertBar_bottom1.gif" width="168" height="32"></td>
                      <td width="659"> &nbsp;共<%=iAlarmCount%>个报警 </td>
                    </tr>
                    <tr>
                      <td width="181"></td>
                      <td width="659"></td>
                    </tr>
                  </table>

                </td>
              </tr>
            </table>
		<% Else %>
		  <table width="100%" border="0">
			<tr>
			  <td width="10%">&nbsp;</td>
			  <td width="90%">没有报警发生.</td>
			</tr>
		  </table>
		<% End If %>
		  </td>
          <td width="371">&nbsp;</td>
        </tr>
        <%end if%>
      </table>
      <p><span id=linegraph> </span> <span id=description> </span> </p>
    </td>
  </tr>
</table>
</body>
</html>
<!-- #include file="inc/foot.asp" -->