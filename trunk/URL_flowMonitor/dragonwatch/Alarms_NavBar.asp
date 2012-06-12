
<html>
<HEAD>
<TITLE>navigation</TITLE>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
<style>
a {color:#0000ff;text-decoration:underline;}
a:link {color:#0000ff;text-decoration:underline;}
a:hover {color:#0000ff;text-decoration:underline;}
a:visited {color:#0000ff;text-decoration:underline;}
a:vlink {color:#ff0000;text-decoration:underline;}
</style>
</head>
<BODY bgcolor="#ffffff"  leftmargin=0 topmargin=0>
<P>	
<TABLE width="100%" border=0  cellspacing=1 cellpadding=1 ALIGN=left>
	<TR>
		<%
		if len(request.QueryString("pagecount")) > 0 then
			iPageCount = CInt(request.QueryString("pagecount"))
		else
			iPageCount = 0
		end if
		iCurrPage  = Cint(request.cookies("rep_alert_currpage"))
		if iCurrPage <= 1 then
		%>
		<TD width="50%" align=right>
			<FONT class="Verbl8" color=gray>[首页]</FONT>
			<FONT class="Verbl8" COLOR=gray>[上页]</FONT>
		</TD>
		<%
		else
			response.write "<TD width='50%' align=right>"
				response.write "[<a href='alarms_List.asp?moveto=First' TARGET=LIST>&lt;&lt 首页</a>]"
				response.write "[<a href='alarms_List.asp?moveto=Previous' TARGET=LIST>&lt; 上页</a>]"

			response.write "</TD>"
		end if
		if iCurrPage >= iPageCount then
			response.write "<TD width='50%' align=left>"
				response.write "<FONT color=gray>[下页]</FONT>"
				response.write "<FONT COLOR=gray>[尾页]</FONT>"
			response.write "</TD>"
		else
		%>
		<TD width="50%" ALIGN=left>
			[<a href="alarms_List.asp?moveto=Next" TARGET=LIST>下页 &gt;</a>]
			[<a href="alarms_List.asp?moveto=Last" TARGET=LIST>尾页 &gt;&gt;</a>]
		</TD>
		<%End if%>
	</TR>
	<tr valign="top">
		<TD WIDTH=* ALIGN=CENTER  COLSPAN=2 valign="top">
			共 <%=request.querystring("recordscount")%> 条警报,当前显示 <%=request.querystring("min")%> 到 <%=request.querystring("max")%> 条 &nbsp;&nbsp;--&nbsp;&nbsp;  最后更新时间 <%=Now()%>
		</TD>
	</TR>
</TABLE>

</body>
</html>
