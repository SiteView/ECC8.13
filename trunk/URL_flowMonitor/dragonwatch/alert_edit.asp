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
	Response.Write "<CENTER>没有找到符合条件的数据！</CENTER>"
Else
%>
<html>
<head>
<title>报警设置</title>
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
          <td width="58%"><b>报警修改</b></td>
          <td width="42%" align="right"><!-- #include file="inc/alertmenu.asp" --></td>
        </tr>
      </table>
      
    </td>
  </tr>
  <tr> 
    <td colspan="2">
	<TABLE align=left><TR><TD align=left><B>当前预定义文件：<%=Request.cookies("rep_prf")("name")%></B></TD></TR></TABLE>
	</td>
  </tr>
  <tr align="center" valign="top"> 
    <td colspan="2">
	
      <table width="97%" border="0" cellspacing="2" cellpadding="0">
        <tr> 
          <td width="28%" align="center" valign="top"> <fieldset style="height:90"> 
            <legend>选择报警范围</legend> 
            <table border="0" cellspacing="2" cellpadding="0" height="16">
              <tr bgcolor="#EFEFDD"> 
                <td bgcolor="#EFEFDD" width="34" align="center"> 
                  <input type="checkbox" value="1" <%If CLng(rsbase("trans_id"))>0 Then Response.Write "checked"%> name="ckTransaction" onClick="if(this.checked){frmpost.transactions.disabled=false;}else{frmpost.transactions.disabled=true;frmpost.transactions.value='';}">
                </td>
                <td bgcolor="#EFEFDD" width="68">业务流程：</td>
                <td width="120"> 
				<%
sql="select ts.trans_id,ts.trans_name from transactions ts, profiletran pt where pt.profile_id=" & Request.cookies("rep_prf")("id") & " and pt.trans_id=ts.trans_id"
Set rs=cnnDragon.Execute(sql)
				%>
                  <select name="transactions" <%If Not(CLng(rsbase("trans_id"))>0) Then Response.Write "disabled"%>>
                    <option value="" selected>--所有业务流程--</option>
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
                <td width="68">城市：</td>
                <td width="120"> 
<%
sql="select c.city_id,c.cityname,c.city_strid from profilecity pc, city c where pc.profile_id=" & Request.cookies("rep_prf")("id") & " and c.city_id=pc.city_id"
Set rs=cnnDragon.Execute(sql)
%>
				  <select name="citys" <%If Not(CLng(rsbase("city_id"))>0) Then Response.Write "disabled"%>>
                    <option value="" selected>--所有城市--</option>
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
          <td width="72%" valign="top"><fieldset style="height:90"> <legend>选择报警类型</legend> 
            <table border="0" cellspacing="2" cellpadding="0" width="480">
              <tr> 
                <td width="146" bgcolor="#cccc99"> 
                  <input type="radio" name="raType" value="1" <%If CInt(rsbase("alert_category_id"))=1 Then Response.Write "checked"%> onClick="type2.style.display='none';type3.style.display='none';">
                  业务流程一旦失败</td>
                <td width="328" bgcolor="#EFEFDD">
				<!-- 选择错误类型 -->
				<SELECT NAME="errcode">
				<option value="-1" <%If Int(rsbase("code"))=-1 Then Response.Write "selected"%>>所有错误</option>
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
				<!-- 选择错误类型 -->
				&nbsp; </td>
              </tr>
              <tr> 
                <td width="146" bgcolor="#cccc99"> 
                  <input type="radio" name="raType" value="2" <%If CInt(rsbase("alert_category_id"))=2 Then Response.Write "checked"%> onClick="type2.style.display='';type3.style.display='none';">
                  平均响应时间大于</td>
                <td width="328" bgcolor="#EFEFDD"> 
                  <table id=type2 border="0" cellspacing="0" cellpadding="0" width="284" style="display:none">
                    <tr> 
                      <td> 
                        <input type="text" name="txtType2" size="10" class="unnamed1" value="<%=rsbase("alert_param")%>">
                        秒　时间周期： 
                        <select name="selType2">
                          <option value="60" selected>60</option>
                        </select>
                        分</td>
                    </tr>
                  </table>
                </td>
              </tr>
              <tr> 
                <td width="146" bgcolor="#cccc99"> 
                  <input type="radio" name="raType" value="3" <%If CInt(rsbase("alert_category_id"))=3 Then Response.Write "checked"%> onClick="type3.style.display='';type2.style.display='none';">
                  平均成功率小于</td>
                <td width="328" bgcolor="#EFEFDD"> 
                  <table border="0" id=type3 cellspacing="0" cellpadding="0" width="284" style="display:none">
                    <tr> 
                      <td> 
                        <input type="text" name="txtType3" size="10" class="unnamed1" value="<%=rsbase("alert_param")%>" maxlength=3>
                        %　时间周期： 
                        <select name="selType3">
                          <option value="60" selected>60</option>
                        </select>
                        分</td>
                    </tr>
                  </table>
                </td>
              </tr>
            </table>
            </fieldset> </td>
        </tr>
        <tr align="left" valign="top"> 
          <td colspan="2" height="157"> <fieldset><legend>警告基本信息</legend>
            <table border="0" cellspacing="3" cellpadding="0">
              <tr> 
                <td bgcolor="#cccc99">警报名称：</td>
                <td bgcolor="#EFEFDD"> 
                  <input type="text" name="alertname" class="unnamed1" size="40" value="<%=rsbase("alert_name")%>">
                </td>
                <td bgcolor="#cccc99">警报等级：</td>
                <td bgcolor="#EFEFDD"> 
                  <select name="alertlevel">
                    <option value="1" <%If CInt(rsbase("alert_severity_id"))=1 Then Response.Write "selected"%> style="background:#000099;color:#ffffff;">轻微警告</option>
                    <option value="2" <%If CInt(rsbase("alert_severity_id"))=2 Then Response.Write "selected"%> style="background:#FFcc00;color:#000000;">普通警告</option>
                    <option value="3" <%If CInt(rsbase("alert_severity_id"))=3 Then Response.Write "selected"%> style="background:#FF0000;color:#ffffff;">严重警告</option>
                  </select>
                </td>
              </tr>
              <tr> 
                <td bgcolor="#cccc99">警告信息：</td>
                <td bgcolor="#EFEFDD"> 
                  <textarea name="alertmessage" cols="50" rows="5" class="unnamed1"><%=rsbase("alert_message")%></textarea>
                </td>
                <td bgcolor="#cccc99">警告描述：<BR>(<A HREF="javascript:builddes()" style="text-decoration:underline;color:blue;">自动生成</A>)</td>
                <td bgcolor="#EFEFDD"> 
                  <textarea name="alertdescript" cols="50" rows="5" class="unnamed1" readonly><%=rsbase("alert_description")%></textarea>
                </td>
              </tr>
              <tr> 
                <td bgcolor="#cccc99">警告动作：</td>
                <td colspan="3" bgcolor="#EFEFDD"> 
                  <input type="radio" name="raAction" value="1" checked onClick="frmpost.email.disabled=true;frmpost.sms.disabled=true;">
                  存在警报日志里 <BR>
                   <input type="radio" name="raAction" <%If Len(rsbase("email"))<>0 Then Response.Write "checked"%> value="2" onClick="frmpost.email.disabled=false;frmpost.sms.disabled=true;">
                  发Email　　请填写Email地址：
                  <input type="text" value="<%=rsbase("email")%>" name="email" class="unnamed1" size="30" disabled>
				  <!--<BR>
                   <input type="radio" name="raAction" <%If Len(rsbase("sms"))<>0 Then Response.Write "checked"%> value="3" onClick="frmpost.email.disabled=true;frmpost.sms.disabled=false;">
                   发手机短信　　请填写手机号：
                  <input type="text" value="<%=rsbase("sms")%>" name="sms" class="unnamed1" size="15" disabled>
				  <BR><FONT COLOR="red">注：当选择发EMAIL或发手机短信时，如果发生警报，警报信息仍会存一份在警报日志里！</FONT> -->
                </td>
              </tr>
            </table></fieldset>
          </td>
        </tr>
        <tr align="center"> 
          <td colspan="2"> 
            <input type="submit" name="Submit" value="确　定">
            　 
            <input type="button" value="重　填" onClick="location.reload();">
            　 
            <input type="button" value="返　回" onClick="history.back()">
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
function builddes()  // 生成报警描述
{
	var fw="";
	var str="";
	var when="";
	var ra;
	var i;

	if ((!frmpost.ckTransaction.checked) && (!frmpost.ckCity.checked))
		{
			fw="所有业务流程＋所有城市";
		}
	else if (frmpost.ckTransaction.checked && (!frmpost.ckCity.checked))
		{
			fw=frmpost.transactions.options[frmpost.transactions.selectedIndex].innerText+"＋所有城市";
		}
	else if (frmpost.ckCity.checked && (!frmpost.ckTransaction.checked))
		{
			fw="所有业务流程＋"+frmpost.citys.options[frmpost.citys.selectedIndex].innerText;
		}
	else
		{
			fw=frmpost.transactions.options[frmpost.transactions.selectedIndex].innerText+"＋"+frmpost.citys.options[frmpost.citys.selectedIndex].innerText;
		}

	for(i=0;i<frmpost.raType.length;i++)
		{
			if (frmpost.raType[i].checked) ra=parseInt(frmpost.raType[i].value);
		}

	switch(ra)
	{
		case 1:
			when="业务流程一旦失败";
			break;
		case 2:
			when="平均响应时间大于"+frmpost.txtType2.value+"秒 (时间周期："+frmpost.selType2.value+"分)";
			break;
		case 3:
			when="平均成功率小于"+frmpost.txtType3.value+"% (时间周期："+frmpost.selType3.value+"分)";
			break;
	}

	str="在 "+fw+" 范围内，当 "+when+" 即报警。";

	frmpost.alertdescript.value=str;
}


function check()
{
	if (frmpost.alertname.value.length==0)
		{
			alert("请填入警报名称！");
			frmpost.alertname.focus();
			return false;
		}

	if (frmpost.ckTransaction.checked && (frmpost.transactions.value.length==0))
		{
			alert("请指定一个具体的业务流程！");
			frmpost.transactions.focus();
			return false;
		}

	if (frmpost.ckCity.checked && (frmpost.citys.value.length==0))
		{
			alert("请指定一个具体的城市！");
			frmpost.citys.focus();
			return false;
		}

	if (frmpost.raType[1].checked)
		{
			var x=parseInt(frmpost.txtType2.value);
			if ((x<1 || x>1000) || isNaN(x))
				{
					alert("在平均响应时间里请填入正确的秒值！");
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
					alert("在平均成功率里请填入正确的百分比（1-100）！");
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
				{alert("请填入EMAIL地址！");return false;}
			break;
		case 3:
			if (frmpost.sms.value=="")
				{alert("请填入手机号！");return false;}
			else
				{
					//if (frmpost.sms.value.length!=11)
					//	{alert("请填入11位手机号！");return false;}
				}
			break;
	}

	builddes()  // 生成报警描述
	if (window.confirm("确定提交数据吗？"))
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