<% Option Explicit %>
<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<%
Dim rs,sql
On Error Resume Next
'=============================================
' ɾ������
'=============================================
If Len(Trim(Request.Form("alertid")))>0 and Len(Request.Form("edit"))=0 Then
	sql="delete from alert where alert.alert_id in (" & Trim(Request.Form("alertid")) & ")"
	cnnDragon.Execute sql
	sql="delete from alertplan where alert_id in (" & Trim(Request.Form("alertid")) & ")"
	cnnDragon.Execute sql
End If
'=============================================
' ɾ��������������
'=============================================

'=============================================
' ����ALERT
'=============================================
If Len(Trim(Request.Form("alertname")))>0 And Len(Request.Form("edit"))>0 Then
	sql="update alert set alert_name='" & Trim(Request.Form("alertname")) & "',"
	sql=sql & "alert_action=" & Trim(Request.Form("raAction")) & ","
	sql=sql & "alert_message='" & Trim(Request.Form("alertmessage")) & "',"
	sql=sql & "alert_severity_id=" & Trim(Request.Form("alertlevel")) & ","
	sql=sql & "alert_description='" & Trim(Request.Form("alertdescript")) & "',"
	sql=sql & "alert_category_id=" & Trim(Request.Form("raType"))
	If Len(Trim(Request.Form("ckTransaction")))>0 Then
		sql=sql & ",trans_id=" & Trim(Request.Form("transactions"))
	Else
		sql=sql & ",trans_id=0"
	End If
	If Len(Trim(Request.Form("ckCity")))>0 Then
		sql=sql & ",city_id=" & Trim(Request.Form("citys"))
	Else
		sql=sql & ",city_id=0"
	End If
	sql=sql & ",email='" & Trim(Request.Form("email")) & "'"
	sql=sql & ",sms='" & Trim(Request.Form("sms")) & "'"
	sql=sql & " where alert_id=" & Request.Form("alertid")
	'Response.Write sql & "<HR>" ' ���� alert ���SQL
	cnnDragon.Execute sql

	sql="update alertplan set "
	Select Case CInt(Trim(Request.Form("raType")))
		Case 1
			sql=sql & "alert_param=0,time_frame=60,code=" & Request.Form("errcode")
		Case 2
			sql=sql & "code=NULL,alert_param=" & Trim(Request.Form("txtType2")) & ",time_frame=" & Request.Form("selType2")
		Case 3
			sql=sql & "code=NULL,alert_param=" & Trim(Request.Form("txtType3")) & ",time_frame=" & Request.Form("selType3")
		Case Else
			sql=sql & "code=NULL,alert_param=0,time_frame=60"
	End Select
	sql=sql & " where alert_id=" & Request.Form("alertid")
	'Response.Write sql & "<HR>" ' ���� alertplan ���SQL
	cnnDragon.Execute sql
End If
'=============================================
' ����ALERT��������
'=============================================

'=============================================
' ������ALERT
'=============================================
If Len(Trim(Request.Form("alertname")))>0 And Len(Request.Form("edit"))=0 Then
	sql="insert into alert values('" & Trim(Request.Form("alertname")) & "'," & Trim(Request.Form("raAction"))
	sql=sql & ",'" & Trim(Request.Form("alertmessage")) & "'," & Trim(Request.Form("alertlevel"))
	sql=sql & ",'" & Trim(Request.Form("alertdescript")) & "'," & Trim(Request.Form("raType"))
	sql=sql & "," & Request.cookies("rep_prf")("id") & ","
	If Len(Trim(Request.Form("ckTransaction")))>0 Then
		sql=sql & Trim(Request.Form("transactions")) & ","
	Else
		sql=sql & "0,"
	End If
	If Len(Trim(Request.Form("ckCity")))>0 Then
		sql=sql & Trim(Request.Form("citys")) & ","
	Else
		sql=sql & "0,"
	End If
	sql=sql & "getdate(),'" & Trim(Request.Form("email")) & "','" & Trim(Request.Form("sms")) & "')"

	'response.write sql & "<HR>" ' ����alert��ĵ�SQL���

	Dim alert_id
	cnnDragon.Execute sql

	Set rs=cnnDragon.Execute("select @@IDENTITY as nowid") ' ȡ��INSERT���alert_idֵ
	'Response.write rs(0)
	If IsNull(rs(0)) Then
		alert_id=0
	Else
		alert_id=CLng(rs(0))
	End If

	'-----------------------------------------------------
	sql="insert into alertplan values(" & alert_id & ","
	Select Case CInt(Trim(Request.Form("raType")))
		Case 1
			sql=sql & "1, 0,60," & Request.Form("errcode")
		Case 2
			sql=sql & "2, " & Trim(Request.Form("txtType2")) & "," & Request.Form("selType2") & ",NULL"
		Case 3
			sql=sql & "3, " & Trim(Request.Form("txtType3")) & "," & Request.Form("selType3") & ",NULL"
		Case Else
			sql=sql & "0, 0, 0"
	End Select
	sql=sql & ",getdate())"
	cnnDragon.Execute sql  ' ���浽 alertplan ��
End If
'=============================================
' ������ALERT��������
'=============================================
sql="select a.alert_severity_id,a.alert_id,a.alert_name,ase.alert_severity_name,ac.alert_action_descript,a.alert_description from alert a, alertaction ac, alertseverity ase"
sql=sql & " where a.profile_id=" & Request.cookies("rep_prf")("id")
sql=sql & " and a.alert_action=ac.alert_action_id and a.alert_severity_id=ase.alert_level order by a.alert_id desc"
Set rs=cnnDragon.Execute(sql)  ' ȡָ�� alert_id �ı�����Ϣ
If rs.Eof And rs.Bof Then	
	Response.Write "<CENTER>û�����þ�����</CENTER><BR><CENTER><A HREF='alert_add.asp'>����¾���</A></CENTER>"
	Response.End
Else
%>
<html>
<head>
<title>��������</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
</head>

<body bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<BR>
<FORM METHOD=POST ACTION="alert_list.asp" name=frmpost>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td width="1%" height="2"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="99%" bgcolor="#CCCCCC" height="2" align="center" valign="middle"> 
      <table width="100%" border="0" cellspacing="0" cellpadding="0" height="21">
        <tr>
          <td width="58%"><b>�����б�</b></td>
          <td width="42%" align="right"><!-- #include file="inc/alertmenu.asp" -->����<A HREF="javascript:delselected()">ɾ��ѡ�еı���</A>��</td>
        </tr>
      </table>
      
    </td>
  </tr>
  <tr align="center"> 
    <td colspan="2"><br>
	  <TABLE width="100%" border="0" cellspacing="0" cellpadding="0">
	  <TR><TD align=right><INPUT TYPE="checkbox" NAME="ckAll" onClick="fnckAll()">ѡ��ȫ��</TD></TR>
	  </TABLE>
      <table border="0" cellspacing="1" cellpadding="3" width="100%">
        <tr bgcolor="#330066" align="center"> 
            <td width="16%" height="20"><font color="#FFFFFF"><IMG SRC="img/ic_name.gif" WIDTH="15" HEIGHT="17" BORDER=0 ALT="">��������</font></td>
            <td width="11%" height="20"><font color="#FFFFFF"><IMG SRC="img/ic_sevr.gif" WIDTH="18" HEIGHT="18" BORDER=0 ALT="">��������</font></td>
            <td width="13%" height="20"><font color="#FFFFFF"><IMG SRC="img/ic_acton.gif" WIDTH="15" HEIGHT="18" BORDER=0 ALT="">������������</font></td>
            <td width="50%" height="20"><font color="#FFFFFF"><IMG SRC="img/ic_mess.gif" WIDTH="18" HEIGHT="13" BORDER=0 ALT="">��������</font></td>
          <td width="5%" height="20"><font color="#FFFFFF">�༭</font></td>
          <td width="5%" height="20"><font color="#FFFFFF">ɾ��</font></td>
        </tr>
        <%
		Dim i
		i=0
		While Not rs.Eof
		%>
        <tr bgcolor="<%=arrColor(i mod 2)%>"> 
            <td width="16%"><%=rs("alert_name")%>&nbsp;</td>
            <td width="11%" align=center> 
              <%
		  Select Case CInt(rs("alert_severity_id"))
			Case 3
				Response.Write "<img src='img/ic_fatl.gif'>"
			Case 2
				Response.Write "<img src='img/ic_warn.gif'>"
			Case 1
				Response.Write "<img src='img/ic_info.gif'>"
			Case Else
				'Response.Write ""
		  End Select
		  %>
              ��<%=rs("alert_severity_name")%> </td>
            <td width="13%" align=center><%=rs("alert_action_descript")%></td>
            <td width="50%"><%=rs("alert_description")%>&nbsp;</td>
          <td width="5%" align="center"><a href="alert_edit.asp?alertid=<%=rs("alert_id")%>">�༭</a></td>
          <td width="5%" align="center">
            <input type="checkbox" name="alertid" value="<%=rs("alert_id")%>">
          </td>
        </tr>
        <%
			rs.MoveNext
			i=i+1
		Wend
		%>
      </table>  
      <br>
    </td>
  </tr>
</table>

</FORM>
</body>
</html>
<%
End If
%>
<!-- #include file="inc/foot.asp" -->
<SCRIPT LANGUAGE="JavaScript">
<!--
function fnckAll()
{
	if (frmpost.ckAll.checked)
	{
		if (typeof(frmpost.alertid.length)=="undefined")
		{
			frmpost.alertid.checked=true;
		}
		else
		{
			for (i=0;i<frmpost.alertid.length;i++)
				frmpost.alertid[i].checked=true;
		}
	}
	else
	{
		if (typeof(frmpost.alertid.length)=="undefined")
		{
			frmpost.alertid.checked=false;
		}
		else
		{
			for (i=0;i<frmpost.alertid.length;i++)
				frmpost.alertid[i].checked=false;
		}
	}
}

function delselected()
{
	if (typeof(frmpost.alertid.length)=="undefined") {frmpost.submit();return;}
	//return ;
	for (i=0;i<frmpost.alertid.length;i++)
	{
		if (frmpost.alertid[i].checked==true) {frmpost.submit();return;}
	}
	alert("������ѡ��һ��������");
}
//-->
</SCRIPT>