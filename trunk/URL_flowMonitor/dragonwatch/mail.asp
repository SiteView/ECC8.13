<!-- #include file="inc/head.asp" -->
<!-- <h2 align=center>开放时间：16:00至18:00</h2> -->
<%
response.end
uid="mailbox" 'Request.Form("uid")
pwd="flowmailbox" 'Request.Form("pwd")
bFlag=False

If Len(uid) > 0 And Len(pwd)>0 then '用户登录
	Set rs=cnnDragon.Execute("select password, cust_id , cust_name from customers where cust_strid='" & uid & "'")
	If rs.Eof and rs.bof then
		Msg="用户名不存在 " & uid 
	else
		if pwd=trim(rs(0)) then
			bFlag=True
			CustId   = rs(1)
			FullUserName=rs("cust_name")
			response.cookies("rep_cust_name")=uid ' 用户名称
			response.cookies("rep_cust_id")=CustId ' 客户编号
		else
			Msg="密码不符"
		end if
	end if
	rs.close
	Set rs=Nothing
Else '返回
	if Len(Request.cookies("rep_cust_id")) > 0 then
		CustId=Request.cookies("rep_cust_id")
		uid=Request.cookies("rep_cust_name")
		bFlag=True
	else
		Response.redirect "/"
'		Response.redirect "/newreport"
	end if
End if

Response.Cookies("visit")="dragon"
sql2="insert into userlog(user_strid,userip,visitdate)  values('"& FullUserName &"','"&_
      		Request.ServerVariables("REMOTE_ADDR")&"',getdate())"

      	cnnDragon.Execute(sql2)
%>
<html>
<head>
<title>游龙科技</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="dragon.css" type="text/css">
</head>
<SCRIPT LANGUAGE="JavaScript">
<!--
function submit1()
{
	document.all.form1.action="index.asp";
	document.all.form1.submit();
}

function submit2()
{
	document.all.form1.action="customer/main.asp";
	document.all.form1.submit();
}

function FocusOnOk(){
	if (document.all.submitButton) {
		document.all.submitButton.focus();
	}
}
//-->
</SCRIPT>
<body topmargin="0" leftmargin="0" marginheight="0" marginwidth="0" bgcolor="#ffffff" text="#000000" link="#FFFFFF" vlink="#FFFFFF" alink="#FFFFFF" onLoad="FocusOnOk();">
<table border="0" cellspacing="0" cellpadding="0" height="631">
  <tr> 
    <td height="37" align="center" valign=middle"> 
      <table width="780" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td height=1 bgcolor="cccc99"></td>
        </tr>
        <tr> 
          <td height=17 bgcolor="#330066" align="left" valign="middle"> <img src="customer/imgs/logolist.gif" width="141" height="42" vspace="10" hspace="10"> 
          </td>
        </tr>
        <tr>
          <td height=18 bgcolor="#CCCCCC" align="right" valign="middle">      
            <%
            If bFlag then
	            Response.Write "<table width='200' border='0' cellspacing='1' cellpadding='1' bgcolor='#FFFFFF' class='smalltext'>"
	              Response.Write "<tr align='center' bgcolor='cccc99'>" 
	                If Left(UCase(uid),5) = "DEMO_" then
	                	Response.write "<td width='46%'><font color='#999999'>&lt; 客户管理 &gt;</font></td>"
	                Else
	                	Response.write "<td width='46%'><a href='customer/main.asp'><font color='#000000'>〖客户管理〗</font></a></td>"
	                End If
	                Response.Write "<td width='54%'><a href='logout.asp'><font color='#000000'>〖返回〗</font></a></td>"
	              Response.Write "</tr>"
	            Response.Write "</table>" 
            End If
            %>
</td>
        </tr>
      </table>
	  <CENTER>
	  </CENTER>
    </td>
  </tr>
  <tr>
    <td height="480" valign="top" align=center class="unnamed1"> <fieldset style="width:770;height:200"> 
      <Legend class="middlefont">请选择预定义文件</Legend><br>
  	<form name=form1 action="index.asp" method="post">
	    <table width="80%" border="0" cellspacing="1" cellpadding="2" class="middlefont">
<%	if bFlag then%>
          <tr> 
            <td align="left" height="6" bgcolor="#CCCCCC"><b>选择预定义文件</b></td>
          </tr>
      <%
		sql="select profile_id, profile_name from profile where cust_id=" & CustId
		Set rs=cnnDragon.Execute(sql)

       	i=0
       	Do Until rs.Eof
        	Response.write "<tr>"
	        	'Response.write "<td width='33'>&nbsp;</td>"
	        	Response.write "<td bgcolor='#cccc99'>&nbsp;<input type='radio' value='" & rs(0) & "_" & rs(1) & "' name=profile"
				if i=0 then
					response.write " checked"
				end if
				response.write ">" & rs(1) & "</td>"
        	
        	Response.write "</tr>"
        	rs.MoveNext
        	i=i+1

		Loop
        rs.close
        Set rs=Nothing
        
		response.write "<input type=hidden name=fullname value='" & uid & "'>"
		response.write "<input type=hidden name=userid value='" & CustId & "'>"
	Else
		Response.write "<tr><td><center>" & Msg & "</center></td></tr>"
		Response.write "<tr><td>&nbsp;</td></tr>"
		Response.write "<tr><td align='center'><a href='http://www.speed.net.cn/'><font color='#0000ff'>返回</font></a></td></tr>"
	End if
       
        %>
<%	if bFlag then%>
          <tr> 
            <td align="center" height="44"> 
              <input type="image" border="0" id="submitButton" name="imageField" src="img/ok_g.gif" width="58" height="18">
            </td>
          </tr>
<%End If%>
			<tr><td>
				<!-- 加入applet判断 -->
<SCRIPT Language="JavaScript" src="inc/checkbrowser.js">
</SCRIPT>
<SCRIPT Language="JavaScript">
//
// This page assumes that the location of the Installable
// JAR and CAB is in a sibling directory called classes
//
function checkForBrowser()
{
	if(is.nav4up && is.minor >= 4.06)
	{
		downloadNow();
	}
}

function downloadNow ()
{
	installed_version = netscape.softupdate.Trigger.GetVersionInfo("java/download/visualmining/netcharts");
	vi = new netscape.softupdate.VersionInfo(3, 6, 0, 0);
	if(installed_version != null && vi.compareTo(installed_version)==0)
	{
		alert("The Java Component classes are already installed.");
	}
	if (navigator.javaEnabled())
	{
		trigger = netscape.softupdate.Trigger;
		if (trigger.UpdateEnabled())
		{
			//must create a fully qualified URL
			var href = document.location.href;
			var loc = href.substring(0, href.substring(0,href.lastIndexOf("/")).lastIndexOf("/")+1)+"classes/install.jar";
			trigger.ConditionalSoftwareUpdate( loc, "java/download/visualmining/netcharts", vi, trigger.DEFAULT_MODE);
		}
		else
		{
			alert("Enable SmartUpdate before running this script.");
		}
	}
	else
	{
		alert("Enable Java before running this script.");
	}
}
</SCRIPT>
<script Language="JavaScript">
checkForBrowser();
if(is.ie4up)
{
	//document.writeln("<span style='font-size:9pt'><center>注：软件只能在IE下浏览</center><br><div align=left><ul><li>新增了数据表格功能，您可以方便的在图表和数据表之间自由切换。<li>新增了图表的多种时间查询条件。<li>功能更为强大，图表数目达到百余种。<li>监测数据更为精确，您可以轻松掌握自己网站的一举一动。<li>新增了报警日志功能。<li>自定义起始时间功能，使您方便的查看各时段的网站性能表现。<li>新增加了帮助系统，使您更加得心应手的使用。</ul><div></span><p>");
	document.writeln('<applet code="netcharts.apps.NFBarchartApp" codebase="../classes" width="300" height="100">');
	document.writeln("<param name='NFParamScript' value='");
	document.writeln('Header = ("",black,"宋体");');
	document.writeln('HeaderBox = (white);');
	document.writeln('Background = (white);');
	document.writeln("'>");
	document.writeln('<param name="useslibrary" value="NetCharts">');
	document.writeln('<param name="useslibrarycodebase" value="../classes/install.cab">');
	document.writeln('<param name="useslibraryversion" value="3,6,0,0">');
	document.writeln('</applet>');

}
else if(is.nav4up && is.minor >= 4.06)
{
	document.writeln("Starting Installation...<p>");
	document.writeln("Please answer <b>'Grant'</b> to all questions asked.<p>");
	document.writeln("You will be prompted to restart Communicator when the installation is complete.");
}
else
{
	document.writeln("需要Netscape 4.06或Internet Explorer 4.0以上版本.");
}
</script>
				<!-- 加入applet判断 -->
			</td></tr>
        </table>
		<CENTER>
		</CENTER>
	  </form>
	  </fieldset> </td>
  </tr>
  <tr>
    <td height="15" align="left" valign="top" bgcolor="#330066">&nbsp;</td>
  </tr>
</table>
<CENTER>
</CENTER>
<!--
注：软件只能在IE下浏览新增了数据表格功能，您可以方便的在图表和数据表之间自由切换。新增了图表的多种时间查询条件。功能更为强大，图表数目达到百余种。监测数据更为精确，您可以轻松掌握自己网站的一举一动。新增了报警日志功能。自定义起始时间功能，使您方便的查看各时段的网站性能表现。
-->
</body>
</html>
<!-- #include file="inc/foot.asp" -->
