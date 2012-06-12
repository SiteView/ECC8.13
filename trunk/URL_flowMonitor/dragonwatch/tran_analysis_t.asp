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

'******************************************************
'执行存储过程,将程序中将要用到的数据保存到变量或数组中*
'******************************************************
dim rs
dim MaxOverTime   '总反应时间的最大值
dim AllTransCount '总业务流程数
dim arrData       '二维数组,0-Trans_name,1-DSN,2-conn,3-header,4-redir,5-data
''''''''''''''    '6-overtime,7-PageSize,8-totaltrans,9-trans_id
dim iRows

if bFilteredCity then
	sql="exec cq_onecityanalysis " & prof_id & ","& request.cookies("rep_city")("id") &",'" & startDate & "','" & EndDate & "'"
else
	sql="exec cq_trananalysis " & prof_id & ",'" & startDate & "','" & EndDate & "'"
end if
''response.write sql
''response.end

Set rs=Server.CreateObject("adodb.RecordSet")
rs.Open sql,cnnDragon,1,1
iRows=0
MaxOvertime=0.0
AllTransCount=0
Do until rs.Eof

	rs.MoveNext
	iRows = iRows + 1
loop

if iRows > 0  then
	Redim arrData(9,iRows - 1)
	rs.MoveFirst
	For i = 0 to iRows-1
		arrData(0,i)=rs("trans_name")
		arrData(1,i)=rs("dns")
		arrData(2,i)=rs("conn")
		arrData(3,i)=rs("header")
		arrData(4,i)=rs("redir")
		arrData(5,i)=rs("data")
		arrData(6,i)=Csng(rs("overtime"))
		arrData(7,i)=Cint(rs("pagesize")/10)/100  'Bytes to KB
		arrData(8,i)=rs("totaltrans")
		arrData(9,i)=rs("trans_id")

		'---------------------------------
		AllTransCount = AllTransCount + rs("totaltrans")
		if arrData(6,i) > MaxOverTime then MaxOvertime = arrData(6,i)

		rs.MoveNext

	Next
end if
rs.close
Set rs=Nothing
'******************************
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
	drc(text,'业务流程分析');
}
function nop(){
	return false;
}

</SCRIPT>
<BR>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> <!-- 标题BAR -->
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="44%" bgcolor="#CCCCCC"><b>业务流程分析</b></td>
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
          <td width="368"><b>共 <%=AllTransCount%> 个业务流程</b></td>
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
      <p>&nbsp;</p>
      <b><!--#Include file="inc/filter.asp"--></b>
      <table width="820" border="0">
        <tr>
          <td width="840" align="right"><a class='bluelink' href="tran_analysis.asp?showas=table">数据表</a></td>
        </tr>
        <tr>
          <td width="840">&nbsp;
          <!--#Include file="inc/trantable.asp"-->
          </td>
        </tr>
      </table>
      <p>&nbsp;</p>
      <table width="60%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="5%"><A class='bluelink' HREF="#" onclick="javascript:window.open('tran_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></A></td>
          <td width="95%">这个报告显示了业务流程的DNS、连接、第一字节包、重定向以及数据下载时间，利用这个报告便于分析检查引起某些业务流程的响应迟缓的原因。
            &nbsp; <A class='bluelink' HREF="#" onclick="javascript:window.open('tran_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">更多...</A></td>
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

