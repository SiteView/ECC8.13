<%
	If Len(Request.Form("profile_id"))>0 Then
		Response.cookies("rep_trans")("id")=""
		Response.cookies("rep_trans")("name")=""
		Response.cookies("rep_city")("id")=""
		Response.cookies("rep_city")("name")=""
		x=Split(Request.Form("profile_id"),"`")
		Response.cookies("rep_prf")("id")=x(0)
		Response.cookies("rep_prf")("name")=x(1)
%>
		<script language="JavaScript">
		window.opener.document.all.profilename.innerText="<%=x(1)%>";
		window.opener.parent.mainFrame.conditionFrame.document.frmCondition.submit();
		window.close();
		</script>
		<%
		Response.End
	End If
%>
<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<html>
<head>
<title>选择预定义文件</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net">
<link rel="stylesheet" href="css.css" type="text/css">
</head>

<body bgcolor="#FFFFFF" text="#000000" topmargin="0" marginheight="0">
<FORM METHOD=POST ACTION="chooseprofile.asp" name="frmpost" onSubmit="return check()">

<%
	userid=Request.QueryString("custid")
	'If Len(Request.cookies("rep_cust")("id"))>0 Then
	'	userid=Request.cookies("rep_cust")("id")
	'Else
	'	userid=0
	'End If
	sql="select profile_id, profile_name from profile where cust_id=" & userid
	Set rs=cnnDragon.Execute(sql)
	If Not (Rs.Eof And Rs.Bof) Then
%>
<table width="100%" border="0" cellspacing="2" cellpadding="0">
  <tr> 
    <td height="31" width="3%"><img src="img/dots.gif" width="33" height="32"></td>
    <td height="31" bgcolor="#CCCCCC" width="97%"><b>选择预定义文件</b></td>
  </tr>
  <tr> 
    <td colspan="2" height="5"></td>
  </tr>
  <tr valign="top" align="center"> 
    <td colspan="2"> 
      <table width="85%" border="0" cellspacing="2" cellpadding="0">
<%
	iCounter=0
	Do While Not rs.Eof
%>
        <tr bgcolor="#CCCC99"> 
          <td width="4%" align="center"> 
            <input type="radio" name="profile_id" value="<%=rs(0)%>`<%=rs(1)%>"
            <%if iCounter=0 then response.write " checked"%>
            >
          </td>
          <td width="96%"><%=rs(1)%>&nbsp;</td>
        </tr>
<%
		rs.MoveNext
		iCounter=iCounter+1
	Loop
%>
      </table>
      <br>
      <input type="image" border="0" name="imageField" src="img/sure.gif" width="61" height="23">
    </td>
  </tr>
</table>
<%
	End If
%>
</FORM>

</body>
</html>
<!-- #include file="inc/foot.asp" -->
<SCRIPT LANGUAGE="JavaScript">
<!--
function check()
{	
	flag=false;
	if (typeof(frmpost.profile_id.length)=="undefined") {return true;}
	var len=frmpost.profile_id.length;
	for (i=0;i<len;i++)
	{
		if (frmpost.profile_id[i].checked) flag=true;
	}
	if (!flag) alert("请选择一个预定义文件!");
	return flag;
}
//-->
</SCRIPT>