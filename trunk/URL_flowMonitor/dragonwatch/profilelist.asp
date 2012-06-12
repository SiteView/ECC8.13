<!-- #include file="inc/clearcookie.asp" -->
<!-- #include file="inc/head.asp" -->
<HTML>
<HEAD>
<TITLE> select profile </TITLE>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
</HEAD>

<BODY>
<%
uid=Request.Form("uid")
pwd=Request.Form("pwd")
bFlag=False

Set rs=cnnDragon.Execute("select password, cust_id from customers where cust_strid='" & uid & "'")
If rs.Eof and rs.bof then
else
	if pwd=trim(rs(0)) then
		bFlag=True
		response.cookies("rep_cust")("name")=uid ' 用户名称
		response.cookies("rep_cust")("id")=rs(1) ' 客户编号
	end if
end if

if bFlag then
	Set rs=cnnDragon.Execute("select profile_id, profile_name from profile where cust_id=" & rs(1))
	if rs.eof and rs.bof then
	else
		iCounter=0
		response.write "<form action='index.asp' method=post>"
		do while not rs.eof
			response.write "<input type=radio value='" & rs(0) & "_" & rs(1) & "' name=profile" 
			if iCounter=0 then
				response.write " checked"
			end if
			response.write ">" & rs(1) & "<BR>"
			rs.movenext
			iCounter=iCounter + 1
		loop
		response.write "<input type=hidden name=fullname value='" & request.cookies("rep_cust")("name") & "'>"
		response.write "<input type=hidden name=userid value='" & request.cookies("rep_cust")("id") & "'>"
		response.write "<input type=submit></form>"

		Response.cookies("visit")=uid  ' 标记用户登录
	end if
else
	Response.write "<h1 align=center>无此用户或密码不对！</h1>"
end if

set rs=nothing
%>
</BODY>
</HTML>
<!-- #include file="inc/foot.asp" -->
