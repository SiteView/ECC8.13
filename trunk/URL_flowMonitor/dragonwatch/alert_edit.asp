<%Option Explicit%>
<!-- #include file="inc/check.asp" -->
<!-- #include file="inc/head.asp" -->
<%
'On Error Resume Next
Dim rs, sql, rsbase, alertid
If Len(Request.QueryString("alertid"))>0 Then
	alertid=CLng(Request.QueryString("alertid"))
Else
	alertid=0
End If

sql="select a.*,b.alert_param,b.time_frame,b.code from alert a, alertplan b where a.alert_id=" & alertid & " and a.alert_id=b.alert_id"
Set rsbase=cnnDragon.Execute(sql)
If rsbase.Eof And rsbase.Bof Then
	Response.Write "<CENTER>û���ҵ��������������ݣ�</CENTER>"
Else
%>
<html>
<head>
<title>��������</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" href="css.css" type="text/css">
<style type="text/css">
<!--
.unnamed1 {  border: #333333; border-style: solid; border-top-width: 1px; border-right-width: 1px; border-bottom-width: 1px; border-left-width: 1px}
-->
</style>
</head>

<body onLoad="fnOnLoad()" bgcolor="#FFFFFF" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<FORM METHOD=POST ACTION="alert_list.asp" name=frmpost onSubmit="return check()">
<INPUT TYPE="hidden" name=alertid value="<%=Request.QueryString("alertid")%>">
<INPUT TYPE="hidden" name=edit value="1">

<BR>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td width="1%" height="2"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="99%" bgcolor="#CCCCCC" height="2" align="center" valign="middle"> 
      <table width="100%" border="0" cellspacing="0" cellpadding="0" height="21">
        <tr>
          <td width="58%"><b>�����޸�</b></td>
          <td width="42%" align="right"><!-- #include file="inc/alertmenu.asp" --></td>
        </tr>
      </table>
      
    </td>
  </tr>
  <tr> 
    <td colspan="2">
	<TABLE align=left><TR><TD align=left><B>��ǰԤ�����ļ���<%=Request.cookies("rep_prf")("name")%></B></TD></TR></TABLE>
	</td>
  </tr>
  <tr align="center" valign="top"> 
    <td colspan="2">
	
      <table width="97%" border="0" cellspacing="2" cellpadding="0">
        <tr> 
          <td width="28%" align="center" valign="top"> <fieldset style="height:90"> 
            <legend>ѡ�񱨾���Χ</legend> 
            <table border="0" cellspacing="2" cellpadding="0" height="16">
              <tr bgcolor="#EFEFDD"> 
                <td bgcolor="#EFEFDD" width="34" align="center"> 
                  <input type="checkbox" value="1" <%If CLng(rsbase("trans_id"))>0 Then Response.Write "checked"%> name="ckTransaction" onClick="if(this.checked){frmpost.transactions.disabled=false;}else{frmpost.transactions.disabled=true;frmpost.transactions.value='';}">
                </td>
                <td bgcolor="#EFEFDD" width="68">ҵ�����̣�</td>
                <td width="120"> 
				<%
sql="select ts.trans_id,ts.trans_name from transactions ts, profiletran pt where pt.profile_id=" & Request.cookies("rep_prf")("id") & " and pt.trans_id=ts.trans_id"
Set rs=cnnDragon.Execute(sql)
				%>
                  <select name="transactions" <%If Not(CLng(rsbase("trans_id"))>0) Then Response.Write "disabled"%>>
                    <option value="" selected>--����ҵ������--</option>
					<%
					If Not (rs.Eof And rs.Bof) Then
						Do While Not rs.Eof
							If CLng(rs(0))=CLng(rsbase("trans_id")) Then
								Response.Write "<option value=" & rs(0) & " selected>" & rs(1) & "</option>"
							Else
								Response.Write "<option value=" & rs(0) & ">" & rs(1) & "</option>"
							End If
							rs.MoveNext
						Loop
					End IF 
					%>
                  </select>
                </td>
              </tr>
              <tr bgcolor="#EFEFDD"> 
                <td align="center" width="34"> 
                  <input type="checkbox" value="1" <%If CLng(rsbase("city_id"))>0 Then Response.Write "checked"%> name="ckCity" onClick="if(this.checked){frmpost.citys.disabled=false;}else{frmpost.citys.disabled=true;frmpost.citys.value='';}">
                </td>
                <td width="68">���У�</td>
                <td width="120"> 
<%
sql="select c.city_id,c.cityname,c.city_strid from profilecity pc, city c where pc.profile_id=" & Request.cookies("rep_prf")("id") & " and c.city_id=pc.city_id"
Set rs=cnnDragon.Execute(sql)
%>
				  <select name="citys" <%If Not(CLng(rsbase("city_id"))>0) Then Response.Write "disabled"%>>
                    <option value="" selected>--���г���--</option>
					<%
					If Not (rs.Eof And rs.Bof) Then
						Do While Not rs.Eof
							If CLng(rs(0))=CLng(rsbase("city_id")) Then
								Response.Write "<option value=" & rs(0) & " selected>" & rs(1) & "</option>"
							Else
								Response.Write "<option value=" & rs(0) & ">" & rs(1) & "</option>"
							End If
							rs.MoveNext
						Loop
					End IF 
					%>
                  </select>
                </td>
              </tr>
            </table>
            </fieldset> </td>
          <td width="72%" valign="top"><fieldset style="height:90"> <legend>ѡ�񱨾�����</legend> 
            <table border="0" cellspacing="2" cellpadding="0" width="480">
              <tr> 
                <td width="146" bgcolor="#cccc99"> 
                  <input type="radio" name="raType" value="1" <%If CInt(rsbase("alert_category_id"))=1 Then Response.Write "checked"%> onClick="type2.style.display='none';type3.style.display='none';">
                  ҵ������һ��ʧ��</td>
                <td width="328" bgcolor="#EFEFDD">
				<!-- ѡ��������� -->
				<SELECT NAME="errcode">
				<option value="-1" <%If Int(rsbase("code"))=-1 Then Response.Write "selected"%>>���д���</option>
				<%
				Set rs=cnnDragon.Execute("select code,message from status_code order by code")
				Do While Not rs.Eof
					If Int(rsbase("code"))=Int(rs(0)) Then
						Response.Write "<option value='" & rs(0) & "' selected>" & rs(0) & "-" & rs(1) & "</option>"
					Else
						Response.Write "<option value='" & rs(0) & "'>" & rs(0) & "-" & rs(1) & "</option>"
					End If
					rs.MoveNext
				Loop
				'Set rstmp=Nothing
				%>
				</SELECT>
				<!-- ѡ��������� -->
				&nbsp; </td>
              </tr>
              <tr> 
                <td width="146" bgcolor="#cccc99"> 
                  <input type="radio" name="raType" value="2" <%If CInt(rsbase("alert_category_id"))=2 Then Response.Write "checked"%> onClick="type2.style.display='';type3.style.display='none';">
                  ƽ����Ӧʱ�����</td>
                <td width="328" bgcolor="#EFEFDD"> 
                  <table id=type2 border="0" cellspacing="0" cellpadding="0" width="284" style="display:none">
                    <tr> 
                      <td> 
                        <input type="text" name="txtType2" size="10" class="unnamed1" value="<%=rsbase("alert_param")%>">
                        �롡ʱ�����ڣ� 
                        <select name="selType2">
                          <option value="60" selected>60</option>
                        </select>
                        ��</td>
                    </tr>
                  </table>
                </td>
              </tr>
              <tr> 
                <td width="146" bgcolor="#cccc99"> 
                  <input type="radio" name="raType" value="3" <%If CInt(rsbase("alert_category_id"))=3 Then Response.Write "checked"%> onClick="type3.style.display='';type2.style.display='none';">
                  ƽ���ɹ���С��</td>
                <td width="328" bgcolor="#EFEFDD"> 
                  <table border="0" id=type3 cellspacing="0" cellpadding="0" width="284" style="display:none">
                    <tr> 
                      <td> 
                        <input type="text" name="txtType3" size="10" class="unnamed1" value="<%=rsbase("alert_param")%>" maxlength=3>
                        %��ʱ�����ڣ� 
                        <select name="selType3">
                          <option value="60" selected>60</option>
                        </select>
                        ��</td>
                    </tr>
                  </table>
                </td>
              </tr>
            </table>
            </fieldset> </td>
        </tr>
        <tr align="left" valign="top"> 
          <td colspan="2" height="157"> <fieldset><legend>���������Ϣ</legend>
            <table border="0" cellspacing="3" cellpadding="0">
              <tr> 
                <td bgcolor="#cccc99">�������ƣ�</td>
                <td bgcolor="#EFEFDD"> 
                  <input type="text" name="alertname" class="unnamed1" size="40" value="<%=rsbase("alert_name")%>">
                </td>
                <td bgcolor="#cccc99">�����ȼ���</td>
                <td bgcolor="#EFEFDD"> 
                  <select name="alertlevel">
                    <option value="1" <%If CInt(rsbase("alert_severity_id"))=1 Then Response.Write "selected"%> style="background:#000099;color:#ffffff;">��΢����</option>
                    <option value="2" <%If CInt(rsbase("alert_severity_id"))=2 Then Response.Write "selected"%> style="background:#FFcc00;color:#000000;">��ͨ����</option>
                    <option value="3" <%If CInt(rsbase("alert_severity_id"))=3 Then Response.Write "selected"%> style="background:#FF0000;color:#ffffff;">���ؾ���</option>
                  </select>
                </td>
              </tr>
              <tr> 
                <td bgcolor="#cccc99">������Ϣ��</td>
                <td bgcolor="#EFEFDD"> 
                  <textarea name="alertmessage" cols="50" rows="5" class="unnamed1"><%=rsbase("alert_message")%></textarea>
                </td>
                <td bgcolor="#cccc99">����������<BR>(<A HREF="javascript:builddes()" style="text-decoration:underline;color:blue;">�Զ�����</A>)</td>
                <td bgcolor="#EFEFDD"> 
                  <textarea name="alertdescript" cols="50" rows="5" class="unnamed1" readonly><%=rsbase("alert_description")%></textarea>
                </td>
              </tr>
              <tr> 
                <td bgcolor="#cccc99">���涯����</td>
                <td colspan="3" bgcolor="#EFEFDD"> 
                  <input type="radio" name="raAction" value="1" checked onClick="frmpost.email.disabled=true;frmpost.sms.disabled=true;">
                  ���ھ�����־�� <BR>
                   <input type="radio" name="raAction" <%If Len(rsbase("email"))<>0 Then Response.Write "checked"%> value="2" onClick="frmpost.email.disabled=false;frmpost.sms.disabled=true;">
                  ��Email��������дEmail��ַ��
                  <input type="text" value="<%=rsbase("email")%>" name="email" class="unnamed1" size="30" disabled>
				  <!--<BR>
                   <input type="radio" name="raAction" <%If Len(rsbase("sms"))<>0 Then Response.Write "checked"%> value="3" onClick="frmpost.email.disabled=true;frmpost.sms.disabled=false;">
                   ���ֻ����š�������д�ֻ��ţ�
                  <input type="text" value="<%=rsbase("sms")%>" name="sms" class="unnamed1" size="15" disabled>
				  <BR><FONT COLOR="red">ע����ѡ��EMAIL���ֻ�����ʱ���������������������Ϣ�Ի��һ���ھ�����־�</FONT> -->
                </td>
              </tr>
            </table></fieldset>
          </td>
        </tr>
        <tr align="center"> 
          <td colspan="2"> 
            <input type="submit" name="Submit" value="ȷ����">
            �� 
            <input type="button" value="�ء���" onClick="location.reload();">
            �� 
            <input type="button" value="������" onClick="history.back()">
          </td>
        </tr>
      </table>
      <BR>
	</td>
  </tr>
</table>

</FORM>
</body>
</html>
<SCRIPT LANGUAGE="JavaScript">
<!--
<%
If Len(rsbase("email"))<>0 Then
	Response.Write "frmpost.email.disabled=false;"
End If
If Len(rsbase("sms"))<>0 Then
	Response.Write "frmpost.sms.disabled=false;"
End If
%>
//-->
</SCRIPT>
<%
	Set rsbase=Nothing
End If
%>
<!-- #include file="inc/foot.asp" -->

<SCRIPT LANGUAGE="JavaScript">
<!--
function builddes()  // ���ɱ�������
{
	var fw="";
	var str="";
	var when="";
	var ra;
	var i;

	if ((!frmpost.ckTransaction.checked) && (!frmpost.ckCity.checked))
		{
			fw="����ҵ�����̣����г���";
		}
	else if (frmpost.ckTransaction.checked && (!frmpost.ckCity.checked))
		{
			fw=frmpost.transactions.options[frmpost.transactions.selectedIndex].innerText+"�����г���";
		}
	else if (frmpost.ckCity.checked && (!frmpost.ckTransaction.checked))
		{
			fw="����ҵ�����̣�"+frmpost.citys.options[frmpost.citys.selectedIndex].innerText;
		}
	else
		{
			fw=frmpost.transactions.options[frmpost.transactions.selectedIndex].innerText+"��"+frmpost.citys.options[frmpost.citys.selectedIndex].innerText;
		}

	for(i=0;i<frmpost.raType.length;i++)
		{
			if (frmpost.raType[i].checked) ra=parseInt(frmpost.raType[i].value);
		}

	switch(ra)
	{
		case 1:
			when="ҵ������һ��ʧ��";
			break;
		case 2:
			when="ƽ����Ӧʱ�����"+frmpost.txtType2.value+"�� (ʱ�����ڣ�"+frmpost.selType2.value+"��)";
			break;
		case 3:
			when="ƽ���ɹ���С��"+frmpost.txtType3.value+"% (ʱ�����ڣ�"+frmpost.selType3.value+"��)";
			break;
	}

	str="�� "+fw+" ��Χ�ڣ��� "+when+" ��������";

	frmpost.alertdescript.value=str;
}


function check()
{
	if (frmpost.alertname.value.length==0)
		{
			alert("�����뾯�����ƣ�");
			frmpost.alertname.focus();
			return false;
		}

	if (frmpost.ckTransaction.checked && (frmpost.transactions.value.length==0))
		{
			alert("��ָ��һ�������ҵ�����̣�");
			frmpost.transactions.focus();
			return false;
		}

	if (frmpost.ckCity.checked && (frmpost.citys.value.length==0))
		{
			alert("��ָ��һ������ĳ��У�");
			frmpost.citys.focus();
			return false;
		}

	if (frmpost.raType[1].checked)
		{
			var x=parseInt(frmpost.txtType2.value);
			if ((x<1 || x>1000) || isNaN(x))
				{
					alert("��ƽ����Ӧʱ������������ȷ����ֵ��");
					frmpost.txtType2.focus();
					return false;
				}
		}

	if (frmpost.raType[2].checked)
		{
			var x=parseInt(frmpost.txtType3.value);
			//alert(x);
			if ((x<1 || x>100) || isNaN(x))
				{
					alert("��ƽ���ɹ�������������ȷ�İٷֱȣ�1-100����");
					frmpost.txtType3.focus();
					return false;
				}
		}

	var x=1;
	if (frmpost.raAction[1].checked) x=2;
	if (frmpost.raAction[2].checked) x=3;
	switch(x)
	{
		case 1:
			
			break;
		case 2:
			if (frmpost.email.value=="")
				{alert("������EMAIL��ַ��");return false;}
			break;
		case 3:
			if (frmpost.sms.value=="")
				{alert("�������ֻ��ţ�");return false;}
			else
				{
					//if (frmpost.sms.value.length!=11)
					//	{alert("������11λ�ֻ��ţ�");return false;}
				}
			break;
	}

	builddes()  // ���ɱ�������
	if (window.confirm("ȷ���ύ������"))
			return true;
	else
		return false;
}

function resetfrm()
{
	frmpost.ckTransaction.checked=false;
	frmpost.ckCity.checked=false;
	frmpost.transactions.disabled=true;
	frmpost.citys.disabled=true;
	type2.style.display="none";
	type3.style.display="none";
	frmpost.raType[0].checked=true;
	frmpost.alertname.value="";
	frmpost.alertmessage.value="";
	frmpost.alertdescript.value="";
	frmpost.alertlevel.value="1";
	frmpost.txtType2.value="";
	frmpost.txtType3.value="";
	frmpost.selType2.value="60";
	frmpost.selType3.value="60";
}

function fnOnLoad()
{
	if (frmpost.raType[1].checked)
		{
			frmpost.txtType3.value="";
			type2.style.display="";
		}
	else if (frmpost.raType[2].checked)
		{
			frmpost.txtType2.value="";
			type3.style.display="";
		}
}

//-->
</SCRIPT>