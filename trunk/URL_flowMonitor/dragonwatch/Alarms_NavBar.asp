
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
			<FONT class="Verbl8" color=gray>[��ҳ]</FONT>
			<FONT class="Verbl8" COLOR=gray>[��ҳ]</FONT>
		</TD>
		<%
		else
			response.write "<TD width='50%' align=right>"
				response.write "[<a href='alarms_List.asp?moveto=First' TARGET=LIST>&lt;&lt ��ҳ</a>]"
				response.write "[<a href='alarms_List.asp?moveto=Previous' TARGET=LIST>&lt; ��ҳ</a>]"

			response.write "</TD>"
		end if
		if iCurrPage >= iPageCount then
			response.write "<TD width='50%' align=left>"
				response.write "<FONT color=gray>[��ҳ]</FONT>"
				response.write "<FONT COLOR=gray>[βҳ]</FONT>"
			response.write "</TD>"
		else
		%>
		<TD width="50%" ALIGN=left>
			[<a href="alarms_List.asp?moveto=Next" TARGET=LIST>��ҳ &gt;</a>]
			[<a href="alarms_List.asp?moveto=Last" TARGET=LIST>βҳ &gt;&gt;</a>]
		</TD>
		<%End if%>
	</TR>
	<tr valign="top">
		<TD WIDTH=* ALIGN=CENTER  COLSPAN=2 valign="top">
			�� <%=request.querystring("recordscount")%> ������,��ǰ��ʾ <%=request.querystring("min")%> �� <%=request.querystring("max")%> �� &nbsp;&nbsp;--&nbsp;&nbsp;  ������ʱ�� <%=Now()%>
		</TD>
	</TR>
</TABLE>

</body>
</html>
