<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!--#Include file="inc/getTime.asp"-->
<%
If Len(request.cookies("rep_prf")("id"))=0 Then
	prof_id=0
Else
	prof_id=request.cookies("rep_prf")("id")
End If

bFilteredTran = len(request.cookies("rep_trans")("id"))
bFilteredCity = len(request.cookies("rep_city")("id"))

'**************************************************************************************
if bFilteredCity And bFilteredTran then
	response.write "<script language=javascript src='inc/setSelBytoGroup.js'></script>"
else
	response.write "<script language=javascript src='inc/setSelBytoCity.js'></script>"
end if


'******************************************************
'ִ�д洢����,�������н�Ҫ�õ������ݱ��浽������������*
'******************************************************
dim rs
dim MaxOverTime   '�ܷ�Ӧʱ������ֵ
dim AllCityCount '��ҵ��������
dim arrData       '��ά����,0-City_name,1-DSN,2-conn,3-header,4-redir,5-data
''''''''''''''    '6-overtime,7-PageSize,8-totalCity,9-City_id
dim iRows

Set rs=Server.CreateObject("adodb.RecordSet")
If bFilteredTran then  '��ʾ����Transaction ����������
	sql="exec cq_onetrananalysis " & prof_id & ","& Request.cookies("rep_trans")("id") &",'" & startDate & "','" & EndDate & "'"
else
	sql="exec cq_cityanalysis " & prof_id & ",'" & startDate & "','" & EndDate & "'"
end if
''response.write sql
''response.end
rs.Open sql,cnnDragon,1,1
iRows=0
MaxOvertime=0.0
AllCityCount=0
Do until rs.Eof

	rs.MoveNext
	iRows = iRows + 1
loop

theOnlyCityCount = 0
ActiveCityId=request.cookies("rep_city")("id")
if iRows > 0  then
	Redim arrData(9,iRows - 1)
	rs.MoveFirst
	For i = 0 to iRows-1
		arrData(0,i)=rs("City_name")
		arrData(1,i)=rs("dns")
		arrData(2,i)=rs("conn")
		arrData(3,i)=rs("header")
		arrData(4,i)=rs("redir")
		arrData(5,i)=rs("data")
		arrData(6,i)=Csng(rs("overtime"))
		arrData(7,i)=Cint(rs("pagesize")/10)/100  'Bytes to KB
		arrData(8,i)=rs("totalCity")
		arrData(9,i)=rs("City_id")

		'---------------------------------
		AllCityCount = AllCityCount + rs("totalCity")
		if bFilteredTran And bFilteredCity then
			if arrData(9,i)	= Cint(ActivecityId) then
				MaxOverTime = arrData(6,i)
				theOnlycityCount = arrData(8,i)
			end if
		else  '//ֻȡҪ��ʾ��city��Overtime
			if arrData(6,i) > MaxOverTime then MaxOvertime = arrData(6,i)
		end if
		rs.MoveNext

	Next
end if
rs.close
Set rs=Nothing

'response.end
'******************************
%>
<html>
<head>
<title>��������ⱨ�� www.speed.net.cn �й�����������ר��</title>
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
	var timeMisures=" ����"
	if (value>1000){
		var remain;
		remain=Math.floor(value%1000);
		if (remain<100){
			remain="0" + remain;
		}
		value=Math.floor(value/1000)+"."+ remain;
		timeMisures=" ��"
	}
	switch (code){
		case 1:
			text="��������ʱ�� :"+value
			break;
		case 2:
			text="����ʱ�� :"+value
			break;
		case 3:
			text="��һ�ֽڰ�ʱ�� :"+value
			break;
		case 4:
			text="�ض���ʱ�� :"+value
			break;
		case 5:
			text="��������ʱ�� :"+value
			break;
	}
	text = text + timeMisures;
	drc(text,'ҵ�����̷���');
}
function nop(){
	return false;
}

</SCRIPT>
<BR>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> <!-- ����BAR -->
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="44%" bgcolor="#CCCCCC"><b>ҵ�����̷���</b></td>
    <td width="53%" bgcolor="#CCCCCC" align="right"><b>ʱ��:
      <%
	  If DateDiff("d", DateValue(startDate), DateValue(endDate))=0 Then
			Response.Write Year(startDate) & "��" & Month(startDate) & "��" & Day(startDate) & "��" & Hour(startDate) & "ʱ" & Minute(startDate) & "�� - " & Hour(endDate) & "ʱ" & Minute(endDate) & "��"
	  Else
			Response.Write Year(startDate) & "��" & Month(startDate) & "��" & Day(startDate) & "��" & Hour(startDate) & "ʱ" & Minute(startDate) & "�� - " & Year(endDate) & "��" & Month(endDate) & "��" & Day(endDate) & "��" & Hour(endDate) & "ʱ" & Minute(endDate) & "��"
	  End If
	  %>
	  </b></td>
  </tr>
  <tr valign="top">
    <td colspan="3">&nbsp;
      <table width="840" border="0">
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368"><b>��ǰԤ�����ļ��� <%=request.cookies("rep_prf")("name")%></b></td>
          <td width="450" align="right">
            <div align="right"><b>��������ʱ��</b><img src="img/dns.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368"><b>��
            <%
          if theOnlyCityCount = 0 then
          	response.write AllCityCount
          else
          	response.write theOnlyCityCount
          end if
          %>
            ��ҵ������</b></td>
          <td width="450" align="right">
            <div align="right"><b>����ʱ��</b> <img src="img/conn.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368">&nbsp;</td>
          <td width="450" align="right">
            <div align="right"><b>��һ�ֽڰ�ʱ��</b> <img src="img/header.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368">&nbsp;</td>
          <td width="450" align="right">
            <div align="right"><b>�ض���ʱ��</b> <img src="img/redir.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr>
          <td width="28">&nbsp;</td>
          <td width="368">&nbsp;</td>
          <td width="450" align="right">
            <div align="right"><b>��������ʱ��</b> <img src="img/data.gif" width="8" height="8"></div>
          </td>
        </tr>
      </table>
      <p>&nbsp;</p>&nbsp;
      <b><!--#Include file="inc/filter.asp"--></b>
      <table width="820" border="0">
        <tr>
          <td width="840" align="right"><a class='bluelink' href="tran_analysis.asp?showas=table">���ݱ�</a></td>
        </tr>
        <tr>
          <td width="840">
		<!--#Include file="inc/grouptable.asp"-->
          </td>
        </tr>
      </table>
      <p>&nbsp;</p>
      <table width="60%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="5%">&nbsp;<A class='bluelink' HREF="#" onclick="javascript:window.open('tran_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></A></td>
          <td width="95%">���������ʾ��ҵ�����̵�DNS�����ӡ���һ�ֽڰ����ض����Լ���������ʱ�䣬���ô˱�����ڷ����������ĳЩҵ��������Ӧ�ٻ���ԭ��&nbsp;<A class='bluelink' HREF="#" onclick="javascript:window.open('tran_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">����...</A></td>
        </tr>
      </table>

    </td>
  </tr>
</table>
</body>
</html>
<!-- #include file="inc/foot.asp" -->
