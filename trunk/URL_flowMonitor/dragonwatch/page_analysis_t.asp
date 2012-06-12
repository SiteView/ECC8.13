<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!--#Include file="inc/getTime.asp"-->
<script language=javascript src="inc/setSelBytoTransaction.js"></script>
<%
If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

bFilteredTran = len(request.cookies("rep_trans")("id"))
bFilteredCity = len(request.cookies("rep_city")("id"))
bShowLink = bFilteredTran and bFilteredCity

'******************************************************
'执行存储过程,将程序中将要用到的数据保存到变量或数组中*
'******************************************************
dim rs
dim MaxOverTime   '总反应时间的最大值
dim AllTransCount '总业务流程数
dim arrData       '二维数组,0-Trans_name,1-DSN,2-conn,3-header,4-redir,5-data
''''''''''''''    '6-overtime,7-PageSize,8-totaltrans,9-trans_id
dim arrOneTranTotal(1,100)
dim iRows

if bFilteredCity then
	sql="exec cq_pageanalysis_onecity " & prof_id & ","& request.cookies("rep_city")("id") &",'" & startDate & "','" & EndDate & "'"
else
	sql="exec cq_pageanalysis_tran " & prof_id & ",'" & startDate & "','" & EndDate & "'"
end if
''response.write sql
''response.end

Set rs=Server.CreateObject("adodb.RecordSet")
rs.Open sql,cnnDragon,1,1

iRows=0
MaxOvertime=0.0
iOvertime = 0.0

AllTransCount=0
iTranCount = 0

iOldTranId = 0
iCounter  = 0

Do until rs.Eof
	If Cint(rs("trans_id")) <> iOldTranId Then
		iTranCount = iTranCount + 1
		iOldTranId = Cint(rs("trans_id"))
		iOverTime = Csng(rs("overtime"))
		iPageSize = CLng(rs("pagesize")/10)/100
	Else
		iOverTime = iOvertime +  Csng(rs("overtime"))
		iPagesize = iPagesize +  Clng(rs("pagesize")/10)/100
	End If
	If iOverTime > MaxOverTime then MaxOvertime = iOverTime
	arrOneTranTotal(0,iTranCount) = iOverTime
	arrOneTranTotal(1,iTranCount) = iPageSize

	rs.MoveNext
	iRows = iRows + 1
	iCounter = iCounter + 1
loop

if iRows > 0  then
'	Redim arrData(9,iRows - 1)
	Redim arrData(11,iRows - 1)
	rs.MoveFirst
	For i = 0 to iRows-1
		arrData(0,i)=rs("url")
		arrData(1,i)=rs("dns")
		arrData(2,i)=rs("conn")
		arrData(3,i)=rs("header")
		arrData(4,i)=rs("redir")
		arrData(5,i)=rs("data")
		arrData(6,i)=Csng(rs("overtime"))
		arrData(7,i)=CLng(rs("pagesize")/10)/100  'Bytes to KB
		arrData(8,i)=rs("totaltrans")
		arrData(9,i)=rs("url_id")
		arrData(10,i)=rs("trans_id")
		arrData(11,i)=rs("trans_name")

		'---------------------------------
		AllTransCount = AllTransCount + rs("totaltrans")

		rs.MoveNext

	Next
end if
rs.close
Set rs=Nothing
'******************************
'for i=0 to irows -1
'	for j=0 to 11
'		response.write arrData(j,i) & ","
'	next
'	response.write "<br>"
'next
'response.write "<br>maxovertime:" & MaxOvertime
'response.write "<br>Alltrancount:" & AllTransCount
'response.end

'**********************************************************************
dim MaxScale      '标尺最大刻度
dim MaxPixls      '实际代表的像素数,小于表格单元的实际宽度610

if iRows > 0 then
	'redim arrWidth(4,iRows-1) '由arrData,根据一定的scale计算出每种颜色的宽度.
	redim arrWidth(5,iRows-1) '由arrData,根据一定的scale计算出每种颜色的宽度.+ WhiteSpace Width
end if
redim arrWhichPic(5)
arrWhichPic(0) = "dns.gif"
arrWhichPic(1) = "conn.gif"
arrWhichPic(2) = "header.gif"
arrWhichPic(3) = "redir.gif"
arrWhichPic(4) = "data.gif"
arrWhichPic(5) = "blue_dot.gif"

if iRows > 0  then
	MaxScale = CLng(MaxOverTime*102)/100
	MaxPixls = MaxOvertime * 610 / MaxScale
end if
'如果MaxOvertime小于10秒,则以毫秒为单位显示
if MaxOvertime < 10 then MaxScale = MaxScale * 1000

'由比例得到每片图像的宽度
iOldTranId = 0
iWhiteSpace = 0
for i=0 to iRows - 1
	for j = 0 to 4
		arrWidth(j,i) = CLng(MaxPixls * arrData(j+1,i)/MaxOverTime)
	next
	If i=0 Or arrData(10,i) <> iOldTranId Then
		iOldTranId = arrData(10,i)
		iWhiteSpace = 0
	Else
		iWhiteSpace = iWhiteSpace + arrWidth(0,i-1) + arrWidth(1,i-1) + arrWidth(2,i-1) + arrWidth(3,i-1) + arrWidth(4,i-1) 
	End If
	arrWidth(5,i) = iWhiteSpace
next
%>
<html>
<head>
<title>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
</head>
<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<DIV ID="overDiv" STYLE="position:absolute; visibility:hide;z-index:10"></DIV>
<SCRIPT LANGUAGE=javascript src="inc/overlib.js"></SCRIPT>
<SCRIPT LANGUAGE=javascript>
var width = "250";
var border = "1";
var offsetx = 10;
var offsety = 5;
var fcolor = "#fafad2"; // fore color
var backcolor = "#000000"; //caption backgroud
var textcolor = "#000000";
var capcolor = "#fafad2"; // caption TextColor
var closecolor = "#99FF99";
function STT(value,code){
	var text;
	var timeMisures=" 毫秒"
	if (value>1000){
		var remain;
		remain=Math.floor(value%1000);
		if (remain<100){
			remain="0" + remain;
		}
		value=Math.floor(value/1000)+"."+ remain;
		timeMisures=" 秒"
	}
	switch (code){
		case 1:
			text="域名解析时间 :"+value
			break;
		case 2:
			text="连接时间 :"+value
			break;
		case 3:
			text="第一字节包时间 :"+value
			break;
		case 4:
			text="重定向时间 :"+value
			break;
		case 5:
			text="数据下载时间 :"+value
			break;
	}
	text = text + timeMisures;
	drc(text,'页面分析');
}
function nop(){
	return false;
}

</SCRIPT>
<BR>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> <!-- 标题BAR -->
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="44%" bgcolor="#CCCCCC"><b>页面分析</b></td>
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
    <td colspan="3">&nbsp;
      <table width="840" border="0">
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368"><b>当前预定义文件： <%=request.cookies("rep_prf")("name")%></b></td>
          <td width="450" align="right">
            <div align="right"><b>域名解析时间</b><img src="img/dns.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368"><b>共 <%=AllTransCount%> 个页面</b></td>
          <td width="450" align="right">
            <div align="right"><b>连接时间</b> <img src="img/conn.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368">&nbsp;</td>
          <td width="450" align="right">
            <div align="right"><b>第一字节包时间</b> <img src="img/header.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368">&nbsp;</td>
          <td width="450" align="right">
            <div align="right"><b>重定向时间</b> <img src="img/redir.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368">&nbsp;</td>
          <td width="450" align="right">
            <div align="right"><b>数据下载时间</b> <img src="img/data.gif" width="8" height="8"></div>
          </td>
        </tr>
      </table>
      <p><b>
        <!--#Include file="inc/filter.asp"-->
        </b> </p>
      <table width="820" border="0">
        <tr>
          <td width="840" align="right"><a class='bluelink' href="page_analysis.asp?showas=table">数据表</a></td>
        </tr>
        <tr>
          <td width="840">&nbsp; 
            <table width="820" border="0" cellspacing=1 style="boder:0" bgcolor="#666666">
              <tr bgcolor="#FFFFFF"> 
                <td width="100">&nbsp;页面名称</td>
                <td width="47">大小(KB)</td>
                <td width="45">速率(KB/s)</td>
                <td width="610" nowrap>分析数据</td>
              </tr>
        <%
		If iRows > 0 then
			iOldTranId = 0
			iCurrTran = 0
			For i=0 to iRows-1
		%>
			<%
			If i=0 Or arrData(10,i) <> iOldTranId Then
				iOldTranId = arrData(10,i)
				iCurrTran = iCurrTran + 1
			%>
			  <tr> 
                <td colspan="4">
                  <table width="100%" border="0" cellspacing="0" cellpadding="0">
                    <tr bgcolor="#CCCCCC"> 
                      <td width="31%">&nbsp;<a class='bluelink' href="page_analysis.asp?transid=<%=arrData(10,i)%>&transname=<%=arrData(11,i)%>"><%=arrData(11,i)%></a> 
                      </td>
                      <td width="24%">&nbsp;总大小:<%=arrOneTranTotal(1,iCurrTran)%> KB</td>
                      <td width="20%">&nbsp;总下载时间:<%=arrOneTranTotal(0,iCurrTran)%> s</td>
                      <td width="25%">&nbsp;平均速率:<%=FormatNumber(arrOneTranTotal(1,iCurrTran) / (arrOneTranTotal(0,iCurrTran)+0.0000001),2)%> KB/s</td>
                    </tr>
                  </table>
                </td>
              </tr>
			  <%End If%>
			  <tr height=25 nowrap bgcolor="#FFFFFF"> 
                <td width=100>&nbsp;
				<%
				If Len(arrData(0,i)) > 25 Then
					Response.write "..." & Right(arrData(0,i),20)
				Else
					Response.write arrData(0,i)
				End If
				%>
				</td>
			    <td width=47>&nbsp;<%=arrData(7,i)%></td>
			    <td width=45>&nbsp;<%=formatNumber(arrData(7,i)/arrData(6,i),2)%></td>
			    <td width=610 nowrap valign=top> 
                  <%
			If arrWidth(5,i) <> 0 then Response.write "<IMG src='img/" & arrWhichPic(5) & "' height='1' width='" & arrWidth(5,i) & "' border=0>"
			for j=0 to 4
				if arrData(j+1,i) > 0 then
					Response.write "<A href='#' onMouseOver='return STT(" & arrData(j+1,i)*1000 & "," & j+1 & ")'"
					response.write " onMouseOut='return nd()'"
					response.write " onClick='return nop()'>"
					Response.write "<IMG src='img/" & arrWhichPic(j) & "' height='15' width='" & arrWidth(j,i) & "' border=0></A>"
				end if
			next
			%>
                </td>
			</tr>
			<%
			Next
		End if
		%>
              <tr bgcolor="#FFFFFF"> 
                <td width="100">&nbsp;刻度(单位: 
                  <%
				dim x
				if MaxOverTime >= 10 then
				x=0.1
				else
				response.write "毫"
				x=100	
				end if
				%>
                  秒)</td>
                <td width="47">&nbsp;</td>
                <td width="45">&nbsp;</td>
                <td width="610"> 
                  <table border="0" cellspacing="0" cellpadding="0" valign="top">
                    <tr valign="top"> 
                      <td width="122" align=RIGHT valign="top"><img src="img/conn_grey.gif" width="120" height="2" valign="top"><img src="img/conn_grey.gif" width="3" height="15"></td>
                      <td width="122" align=RIGHT valign="top"><img src="img/conn_grey.gif" width="120" height="2" valign="top"><img src="img/conn_grey.gif" width="3" height="15"></td>
                      <td width="122" align=RIGHT valign="top"><img src="img/conn_grey.gif" width="120" height="2" valign="top"><img src="img/conn_grey.gif" width="3" height="15"></td>
                      <td width="122" align=RIGHT valign="top"><img src="img/conn_grey.gif" width="120" height="2" valign="top"><img src="img/conn_grey.gif" width="3" height="15"></td>
                      <td width="122" align=RIGHT valign="top"><img src="img/conn_grey.gif" width="120" height="2" valign="top"><img src="img/conn_grey.gif" width="3" height="15"></td>
                    </tr>
                  </table>
                  <table border="0" cellspacing="0" cellpadding="0" valign="top">
                    <tr align="right"> 
                      <td width="122">&nbsp;<%=MaxScale*1/5%></td>
                      <td width="122">&nbsp;<%=MaxScale*2/5%></td>
                      <td width="122">&nbsp;<%=MaxScale*3/5%></td>
                      <td width="122">&nbsp;<%=MaxScale*4/5%></td>
                      <td width="122">&nbsp;<%=MaxScale%></td>
                    </tr>
                  </table>
                </td>
              </tr>
            </table>
            
          </td>
        </tr>
      </table>
      <p>&nbsp;</p>
      <table width="60%" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td width="5%"><a class='bluelink' href="#" onClick="javascript:window.open('page_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></a></td>
          <td width="95%">这个报告显示了页面的DNS、连接、第一字节包、重定向以及数据下载时间，利用这个报告便于分析检查引起某些页面的响应迟缓的原因。 
            &nbsp; <a class='bluelink' href="#" onClick="javascript:window.open('page_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">更多...</a></td>
        </tr>
      </table>
      <p><span id="subtitle"> </span> </p>
      <p>&nbsp;</p>
      <p><span id=linegraph> </span> <span id=description> </span> </p>
    </td>
  </tr>
</table>
</body>
</html>
<!-- #include file="inc/foot.asp" -->
