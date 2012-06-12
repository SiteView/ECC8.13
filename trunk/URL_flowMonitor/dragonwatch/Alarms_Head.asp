<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<%
if len(request.cookies("rep_alert_orderby")) > 0 then
	sAlertOrderBy = request.cookies("rep_alert_orderby")
else
	sAlertOrderBy = "YAseverity+NAname+NAtime+NAaction" '//扩展时修改此字符串
end if
arrOrderBy = split(sAlertOrderBy,"+")
%>
<html>
<head>
<title>游龙网监测报告 www.speed.net.cn 中国互联网性能专家</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
<style>
a {color:#ffffff;text-decoration:underline;}
a:link {color:#ffffff;text-decoration:underline;}
a:hover {color:#ffffff;text-decoration:underline;}
a:visited {color:#ffffff;text-decoration:underline;}
</style>
</head>
<body bgcolor="#FFFFFF" text="#000000" leftmargin="2" topmargin="0" marginwidth="0" marginheight="0">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="44%" bgcolor="#CCCCCC"><b>报警日志</b></td>
    <td width="53%" bgcolor="#CCCCCC" align="right">&nbsp;</td>
  </tr>
  <tr valign="top"> 
    <td colspan="3">
      <table border="0" width="100%">
        <tr> 
          <td align="right"> 
            <div align="right"><b>严重 </b><img src="img/ic_fatl.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr> 
          <td align="right"> 
            <div align="right"><b>一般</b> <img src="img/ic_warn.gif" width="8" height="8"></div>
          </td>
        </tr>
        <tr> 
          <td align="right"> 
            <div align="right"><b>轻微</b> <img src="img/ic_info.gif" width="8" height="8"></div>
          </td>
        </tr>
      </table>  
      <table width="100%" border="0" cellspacing="1" cellpadding="2">
        <tr bgcolor="#330066" valign="middle"> 
          <td width="95"><font color="#ffffff"><img src="img/ic_sevr.gif" width="18" height="18"> 
            <a href="alarms_list.asp?orderby=<%=Mid(arrOrderby(0),3)%>" target="LIST">警报级别</a> <img name="col1" src="img/ic_sort3.gif" width="9" height="8"></font></td>
          <td width="150"><font color="#ffffff"><img src="img/ic_name.gif" width="15" height="17"> 
            <a href="alarms_list.asp?orderby=<%=Mid(arrOrderby(1),3)%>" target="LIST">名称</a> 
            <img name="col2" src="img/ic_sort3.gif" width="9" height="8"></font></td>
          <td width="150"><font color="#ffffff"><img src="img/ic_btime.gif" width="15" height="15"> 
            <a href="alarms_list.asp?orderby=<%=Mid(arrOrderby(2),3)%>" target="LIST">发生时间</a> 
            <img name="col3" src="img/ic_sort3.gif" width="9" height="8"></font></td>
          <td width="120"><font color="#ffffff"><img src="img/ic_acton.gif" width="15" height="18"> 
            <a href="alarms_list.asp?orderby=<%=Mid(arrOrderby(3),3)%>" target="LIST">响应动作</a> 
            <img  name="col4" src="img/ic_sort3.gif" width="9" height="8"></font></td>
          <td width="*"><font color="#ffffff"><img src="img/ic_mess.gif" width="18" height="13"> 
            信息 <img src="img/ic_sort3.gif" width="9" height="8"></font></td>
        </tr>
      </table>
      
    </td>
  </tr>
</table>

</body>
</html>
<!-- #include file="inc/foot.asp" -->
<script language="javascript">
function showImg(s){
	var obj;
	for (i=0;i<=3;i++){
		switch(i){
		case 0: 
			obj=document.all.col1;
			break;
		case 1: 
			obj=document.all.col2;
			break;
		case 2: 
			obj=document.all.col3;
			break;
		case 3: 
			obj=document.all.col4;
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
