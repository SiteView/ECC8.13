<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<%
dim rsU 'as recordset
dim rsC 'as recordset
dim iUrlcount
dim iCitycount
dim arrUrl()
dim arrCity()

Profile_id = request.cookies("rep_prf")("id")
sql="select cu.url from customerurl cu, profile p where p.cust_id = cu.cust_id and p.profile_id = " & Profile_id
Set rsU=Server.Createobject("adodb.RecordSet")
rsU.open sql,cnnDragon,1,1
iUrlcount = rsU.recordCount
if iUrlcount > 0 then
	Redim arrUrl(iUrlcount-1)
end if
'rsU.Movefirst
for i=0 to iUrlcount-1
	arrUrl(i) = rsU("url")
	rsU.moveNext
next
rsU.Close
Set rsU=Nothing

''----------------------------取得ProfileId对应的所有cityname,url-----------------------
sql=      "select ct.cityname, ag.url  "
sql=sql & "from Agent ag,cityagent cg ,profilecity pc ,city ct  "
sql=sql & "where ag.agent_id = cg.agent_id  "
sql=sql & "and cg.city_id = pc.city_id and ct.city_id = pc.city_id "
sql=sql & "and pc.profile_id =" & Profile_Id

Set rsC=Server.Createobject("adodb.RecordSet")
rsC.open sql,cnnDragon,1,1
iCitycount = rsC.recordCount
if iCitycount > 0 then
	Redim arrCity(iCitycount - 1,1)
end if
rsC.Movefirst
for i=0 to iCitycount-1
	arrCity(i,0) = rsC("cityname")
	arrCity(i,1) = rsC("url")
	rsC.moveNext
next

rsC.close
Set rsC=Nothing
%>
<html>
<head>
<title>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">

</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<form name="frmHead" method="post" action="comp_analysis_reprot.asp">
  <table border="0" cellspacing="0" cellpadding="0">
    <tr valign="bottom">
      <td align="right">&nbsp; 网址: </td>
      <td> 
	  <INPUT TYPE="text" NAME="selUrl" size=35>
<!--         <select name="selUrl">
        <%
        if iUrlCount > 0 then
        	For i=0 to iurlcount-1
        		response.write "<option value='" & arrUrl(i) & "'>" & arrUrl(i) & "</option>"
        	next
        end if
        %>
        </select>
 -->      </td>
      <td align="right">&nbsp;&nbsp;城市: </td>
      <td> 
        <select name="selCity">
		<!--
		<%
		if iCitycount > 0 then
			for i=0 to iCitycount-1
				response.write "<option value='" & arrCity(i,1) & "'>" & arrCity(i,0) & "</option>"
			next
		end if
		%>-->
		response.write "<option value='http://www.siteview.com/transaction/transaction1.exe'>北京  </option>"

        </select>
      </td>
      <td>&nbsp;<a href="#" onclick="javascript:return go();"><img src="img/apply.gif" border=0 width="89" height="17"></a></td>
    </tr>
  </table>
</form>
</body>

</html>
<!-- #include file="inc/foot.asp" -->
<script language=javascript>
function go(){
	var sUrl;
	var sCity;
	var wheretogo;
	sUrl=document.frmHead.selUrl.value;
	sCity=document.frmHead.selCity.value;
//	wheretogo="http://192.168.1.133/dbserver/dbserver.dll?" + sCity + "?2test+" + sUrl;
	wheretogo="http://www.speed.net.cn/scripts/dbserverchines.dll?" + sCity + "?0test+" + sUrl;
	parent.compReport.location.href=wheretogo;
	return;
}

</script>