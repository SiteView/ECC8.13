<!--#Include file="inc/head.asp"-->
<html>
<head>
<title>Untitled</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
</head>
<%
'�������õ���Cookies:
'1. "rep_alert_orderby" like "YAname+NDtime"�Ƿ��Դ��ֶ�����,����˳��+������ֶ���
'2. "rep_alert_currpage"
const RowsPerPage = 25

dim rs
dim iAlertCount		'������Ŀ
dim sOrderBy		'����ʽ
dim sOrderDesc		'�Ƿ�DESC
dim iP				'����ָ��
		
'//------------------------------------------�õ�����ʽ����------------------------------------
if len(request.cookies("rep_alert_orderby")) > 0 then
	sAlertOrderBy = request.cookies("rep_alert_orderby")
else
	sAlertOrderBy = "YAseverity+NAname+NAtime+NAaction" '//��չʱ�޸Ĵ��ַ���
end if
arrOrderBy = split(sAlertOrderBy,"+")

'//---------�����û�������ѡ������ʽ,����ϴε�����ʽҲ�����ַ�ʽ,����˵��name,��ô���෴�ķ�ʽ����;
'//������ϴε�����ʽ��ͬ,���µ�����ʽ��������,����Ĵ�С˳���մ��ֶε�����ʽ.-----------------
sOrderby = Request.QueryString("orderby")
if len(sOrderby) > 0 then
	iP = 0
	for i = 0 to UBound(arrOrderBy)
		if Mid(arrOrderBy(i),3) = sOrderby then
			iP = i
			Exit for
		end if
	
	next
	
	if Left(arrOrderBy(iP),1) = "Y" then 	'�ϴ��ǰ��մ��ֶ�����
		if Mid(arrOrderBy(iP),2,1) = "D" then
			sOrderDesc = "A"
		else
			sOrderDesc = "D"
		End if
	else
		sOrderDesc = Mid(arrOrderBy(iP),2,1)
	end if
else
	for i = 0 to UBound(arrOrderBy)
		if Left(arrOrderBy(i),1) = "Y" then
			iP = i
			Exit for
		end if
	next
	sOrderBy = Mid(arrOrderBy(iP),3)
	sOrderDesc = Mid(arrOrderBy(iP),2,1)
end if
''response.write "�����ֶ�Ϊ:" & sOrderby
''response.write "<br>����:" & sOrderDesc

'//---------------------------����sOrderBy,sOrderDesc��ϳɲ�ѯ�ַ���,��ִ��-----------------------------
select case sOrderBy
	case "severity" 
		sOrder = "asv.alert_level"
	case "name"
		sOrder = "a.alert_name"
	case "time"
		sOrder = "al.occutime"
	case "action"
		sOrder = "a.alert_action"
end select
if sOrderDesc = "D" then
	sOrder = sOrder & " Desc"
End if

sql="select a.alert_id, a.alert_name, a.alert_message,al.occutime,asv.alert_severity_name,asv.alert_level,aa.alert_action_descript from alert a,alertlog al,alertseverity asv,alertaction aa "
sql=sql & " where a.alert_id = al.alert_id and a.alert_severity_id = asv.alert_severity_id and a.alert_action = aa.alert_action_id "
sql=sql & " and a.profile_id = " & Request.cookies("rep_prf")("id")
sql=sql & " order by " & sOrder

'response.write sql
'response.end

Set rs=Server.CreateObject("adodb.RecordSet")
rs.open sql,cnnDragon,1,1

''---------------------�ж��û�ѡ������ʾ�ڼ�ҳ------------------
if len(request.cookies("rep_alert_currpage")) > 0 then
	iCurrPage = Cint(request.cookies("rep_alert_currpage"))
else
	iCurrPage = 0
end if

select case Request.QueryString("moveto")
	case "Next"
		iCurrPage = iCurrPage + 1
	case "Last"
		iCurrPage = iTotalPages
	case "Previous"
		iCurrPage = iCurrPage - 1
	case "First"
		iCurrPage = 1
end select

''-------------------������ʾ�ڼ�ҳ-------------------------------
RecExists=0 	'�Ƿ��������¼
PageCount=0 	'ҳ������
RecCount =0 	'��¼����
CurrMinPage=0 	'��ǰ��ʾ�ĵ�һ����¼
CurrMaxPage=0 	'��ǰ��ʾ�����һ����¼
if Not (Rs.Bof And Rs.Eof) then
	Rs.PageSize= RowsPerPage
	PageCount=Rs.Pagecount 'intPages��¼�����ݵ�ҳ����
	if iCurrPage < 1 then iCurrPage = 1
	if iCurrPage > PageCount then iCurrPage = PageCount

	Rs.AbsolutePage = iCurrPage
	RecExists=1
	RecCount = Rs.RecordCount
	CurrMinPage=(iCurrPage - 1) * RowsPerPage + 1
	CurrMaxPage=(iCurrPage) * RowsPerPage
	If CurrMaxPage > RecCount then CurrMaxPage=RecCount
end if
''----------------------------------------------------------------
response.cookies("rep_alert_currpage")=iCurrPage
'******************************
'//----------------------------------���cookies�ַ���,��дcookies��ֵ------------------------------
sAlertOrderBy=""
for i=0 to UBound(arrOrderby) - 1
	if i = iP then
		sAlertOrderBy = sAlertOrderBy & "Y" & sOrderDesc & Mid(arrOrderby(i),3) & "+"
	else
		sAlertOrderBy = sAlertOrderBy & "N" & Mid(arrOrderby(i),2,1) & Mid(arrOrderby(i),3) & "+"
	end if
next
if iP = UBound(arrOrderby) then
	sAlertOrderBy = sAlertOrderBy & "Y" & sOrderDesc & Mid(arrOrderby(i),3)
else
	sAlertOrderBy = sAlertOrderBy & "N" & Mid(arrOrderby(i),2,1) & Mid(arrOrderby(i),3)
end if
response.cookies("rep_alert_orderby") = sAlertOrderBy

'//------------------------------------��ʾͼƬ�Ĳ���imgToBeShow----------------------------------------------
arrOrderBy = split(sAlertOrderBy,"+")
imgToBeShow=""
for i=0 to UBound(arrOrderBy)
	if left(arrOrderby(i),1) = "N" then
		imgTobeshow = imgTobeShow & "C"
	else
		if Mid(arrOrderby(i),2,1) = "D" then
			imgTobeshow = imgTobeShow & "A"
		else
			imgTobeshow = imgTobeShow & "B"
		end if
	end if
next
''response.write "<br>cookies:" & request.cookies("rep_alert_orderby")
%>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="2" topmargin="0" marginwidth="1" marginheight="1"
<%response.write "onload='javascript:showImg(""" & imgToBeshow & """)'"%>
>
<%
'if RecExists = 1 then
response.write "<table width='100%' border=0 cellspacing=1 cellpadding=2>"
	for i=0 to RowsPerPage-1
		if i Mod 2 = 0 then '���汳��ɫ
			bgc = "#efefdf"
		else
			bgc = "#cccc99"
		end if
		if Not rs.Eof then
			select case rs("alert_level") '�����ȼ�ͼƬ
				case 1
					svimg = "img/ic_info.gif"
				case 2
					svimg = "img/ic_warn.gif"
				case 3
					svimg = "img/ic_fatl.gif"
			end select
		end if
		if Rs.Eof then
			response.write "<tr bgcolor='" & bgc & "' valign='top'>"
				response.write "<td width=95><CENTER>&nbsp;</center></td>"
				response.write "<td width=150>&nbsp;</td>"
				response.write "<td width=150>&nbsp;</td>"
				response.write "<td width=120>&nbsp;</td>"
				response.write "<td width=*>&nbsp;</td>"
			response.write "</tr>"
		else
			response.write "<tr bgcolor='" & bgc & "' valign='top'>"
				response.write "<td width=95><CENTER>&nbsp;<IMG SRC='" & svimg & "' >&nbsp;</CENTER></td>"
				response.write "<td width=150>&nbsp;" & rs("alert_name") & "</td>"
				response.write "<td width=150>&nbsp;" & rs("occutime") & "</td>"
				response.write "<td width=120>&nbsp;" & rs("alert_action_descript") & "</td>"
				response.write "<td width=*>&nbsp;" & rs("alert_message") & "</td>"
			response.write "</tr>"
			rs.MoveNext
		end if
	next
response.write "</table>"
'end if
%>
</body>
</html>
<%
rs.close
Set rs=Nothing
response.write "<script language='javascript'>"
response.write "if (window.parent.frames.length > 0 ){"
	response.write "window.parent.frames.NAVBAR.location ='Alarms_NavBar.asp?recordsCount=" & RecCount & "&pagecount=" & pagecount & "&min=" & CurrMinPage & "&max=" & CurrMaxPage & "';"
response.write "};"

response.write "</script>"
%>
<!--#Include file="inc/foot.asp"-->
<script language="javascript">
function showImg(s){
	var obj;
	for (i=0;i<=3;i++){
		switch(i){
		case 0: 
			obj=parent.HEADER.document.all.col1;
			break;
		case 1: 
			obj=parent.HEADER.document.all.col2;
			break;
		case 2: 
			obj=parent.HEADER.document.all.col3;
			break;
		case 3: 
			obj=parent.HEADER.document.all.col4;
			break;
		}
		switch(s.charAt(i)){
		case "A": 
			obj.src="img/ic_sort1.gif";
			break;
		case "B": 
			obj.src="img/ic_sort2.gif";
			break;
		case "C": 
			obj.src="img/ic_sort3.gif";
			break;
		}
	}
//	document.all.col1.src = "img/ic_sort1.gif";
}

</script>
