<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<!--#Include file="inc/getTime.asp"-->
<script language=javascript src="inc/setSelBytoCity.js"></script>
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
'ִ�д洢����,�������н�Ҫ�õ������ݱ��浽������������*
'******************************************************
dim rs
dim MaxOverTime   '�ܷ�Ӧʱ������ֵ
dim AllTransCount '��ҵ��������
dim arrData       '��ά����,0-Trans_name,1-DSN,2-conn,3-header,4-redir,5-data
''''''''''''''    '6-overtime,7-PageSize,8-totaltrans,9-trans_id
dim arrOneTranTotal(1,100)
dim iRows

dim iCityCount
dim iOldCity
dim arrCity(1,100) ' Id, name
dim MaxScale      '������̶�
dim MaxPixls      'ʵ�ʴ����������,С�ڱ��Ԫ��ʵ�ʿ��610

if bFilteredTran then
	sql="exec cq_pageanalysis_onetran " & prof_id & ","& request.cookies("rep_trans")("id") &",'" & startDate & "','" & EndDate & "'"
else
	sql="exec cq_pageanalysis_city " & prof_id & ",'" & startDate & "','" & EndDate & "'"
end if
''response.write sql
''response.end

Set rs=Server.CreateObject("adodb.RecordSet")
rs.Open sql,cnnDragon,1,1

AllTransCount=0
MaxOvertime=0.0

iCityCount = 0
iOldCityId = 0

Do until rs.Eof
	If Cint(rs("city_id")) <> iOldCityId Then 'һ���µĳ���
		iTranCount = iTranCount + 1
		iOldCityId = Cint(rs("city_id"))

		iCityCount = iCityCount + 1
		iOldCityId = Cint(rs("city_id"))
		arrCity(0,iCityCount-1) = Cint(rs("city_id"))
		arrCity(1,iCityCount-1) = rs("city_name")
		iOverTime = Csng(rs("overtime"))
		iOldTranId = Cint(rs("trans_id")) 
	Else
		If Cint(rs("trans_id")) <> iOldTranId then
			iOverTime = Csng(rs("overtime"))
			iOldTranId = Cint(rs("trans_id")) 
		Else
			iOverTime = iOvertime +  Csng(rs("overtime"))
		End If
	End If

	If iOverTime > MaxOverTime then MaxOvertime = iOverTime

	rs.MoveNext
	iRows = iRows + 1
loop
if iRows > 0  then
	MaxScale = CLng(MaxOverTime*102)/100
	MaxPixls = MaxOvertime * 610 / MaxScale
end if
'���MaxOvertimeС��10��,���Ժ���Ϊ��λ��ʾ
if MaxOvertime < 10 then MaxScale = MaxScale * 1000

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
	drc(text,'ҳ�����');
}
function nop(){
	return false;
}

</SCRIPT>
<BR>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> <!-- ����BAR -->
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="44%" bgcolor="#CCCCCC"><b>ҳ�����</b></td>
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
          <td width="368"><b><div id=AllTransCount><%=AllTransCount%></div></b></td>
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
      <p><b>
        <!--#Include file="inc/filter.asp"-->
        </b> </p>
      <table width="820" border="0">
        <tr>
          <td width="840" align="right"><a class='bluelink' href="page_analysis.asp?showas=table">���ݱ�</a></td>
        </tr>
        <tr>
          <td width="840">&nbsp; 
<%
For c = 0 to iCityCount -1

	iRows=0
	iOvertime = 0.0

	iTranCount = 0

	iOldTranId = 0
	iCounter  = 0
'	rs.filter = ""
	rs.filter = "city_id = " & arrCity(0,c)
	Do until rs.Eof
		If Cint(rs("trans_id")) <> iOldTranId Then
			iTranCount = iTranCount + 1
			iOldTranId = Cint(rs("trans_id"))
			iOverTime = Csng(rs("overtime"))
			iPageSize = CLng(rs("pagesize")/10)/100
		Else
			iOverTime = iOvertime +  Csng(rs("overtime"))
			iPagesize = iPagesize +  CLng(rs("pagesize")/10)/100
		End If
		arrOneTranTotal(0,iTranCount) = iOverTime
		arrOneTranTotal(1,iTranCount) = iPageSize
'		If iOverTime > MaxOverTime then MaxOvertime = iOverTime

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

	if iRows > 0 then
		'redim arrWidth(4,iRows-1) '��arrData,����һ����scale�����ÿ����ɫ�Ŀ��.
		redim arrWidth(5,iRows-1) '��arrData,����һ����scale�����ÿ����ɫ�Ŀ��.+ WhiteSpace Width
	end if
	redim arrWhichPic(5)
	arrWhichPic(0) = "dns.gif"
	arrWhichPic(1) = "conn.gif"
	arrWhichPic(2) = "header.gif"
	arrWhichPic(3) = "redir.gif"
	arrWhichPic(4) = "data.gif"
	arrWhichPic(5) = "blue_dot.gif"


	'�ɱ����õ�ÿƬͼ��Ŀ��
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
            <br>
			<br>
            &nbsp;<a class="bluelink" href="page_analysis.asp?cityid=<%=arrCity(0,c)%>&cityname=<%=arrCity(1,c)%>"><%=arrCity(1,c)%></a> 
            <table width="820" border="0" cellspacing=1 style="boder:0" bgcolor="#666666">
              <tr bgcolor="#FFFFFF"> 
                <td width="100">&nbsp;ҳ������</td>
                <td width="47">��С(KB)</td>
                <td width="45">����(KB/s)</td>
                <td width="610" nowrap>��������</td>
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
                      <td width="31%">&nbsp;
						<%If bFilteredTran Then
						response.write arrData(11,i)
						Else%>
						<a class='bluelink' href="page_analysis.asp?transid=<%=arrData(10,i)%>&transname=<%=arrData(11,i)%>"><%=arrData(11,i)%></a> 
						<%End If%>
                      </td>
                      <td width="24%">&nbsp;�ܴ�С:<%=arrOneTranTotal(1,iCurrTran)%> KB</td>
                      <td width="20%">&nbsp;������ʱ��:<%=arrOneTranTotal(0,iCurrTran)%> s</td>
                      <td width="25%">&nbsp;ƽ������:<%=FormatNumber(arrOneTranTotal(1,iCurrTran) / (arrOneTranTotal(0,iCurrTran)+0.0000001),2)%> KB/s</td>
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
                <td width="100">&nbsp;�̶�(��λ: 
                  <%
				dim x
				if MaxOverTime >= 10 then
				x=0.1
				else
				response.write "��"
				x=100	
				end if
				%>
                  ��)</td>
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
<%Next%>
          </td>
        </tr>
      </table>
      <p>&nbsp;</p>
      <table width="60%" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td width="5%"><a class='bluelink' href="#" onClick="javascript:window.open('page_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')"><img border=0 src="img/lamp.gif" width="22" height="22"></a></td>
          <td width="95%">���������ʾ��ҳ���DNS�����ӡ���һ�ֽڰ����ض����Լ���������ʱ�䣬�������������ڷ����������ĳЩҳ�����Ӧ�ٻ���ԭ�� 
            &nbsp; <a class='bluelink' href="#" onClick="javascript:window.open('page_analysis_help.htm','tips','height=400,width=500,scrollbars=no,toolbar=no,title=no')">����...</a></td>
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
<%
response.write "<SCRIPT LANGUAGE='JavaScript'>"
response.write "document.all.AllTransCount.innerHTML = '�� " & AllTransCount & " ��ҳ��';"
response.write "</SCRIPT>"

	rs.close
	Set rs=Nothing
%>
<!-- #include file="inc/foot.asp" -->
