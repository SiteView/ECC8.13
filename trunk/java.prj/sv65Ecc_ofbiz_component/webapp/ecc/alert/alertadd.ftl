<HTML>
	<script language="javascript">
	function getRadioValue(name){
	var radioes = document.getElementsByName(name); 
	for(var i=0;i<radioes.length;i++)
	{
	     if(radioes[i].checked){
	      return radioes[i].value;
	     }
	}
	return "";
	}

	function  change(){   
	  document.getElementById("category_alert").value= getRadioValue('category');
	  document.getElementById("class_alert").value= getRadioValue('class');
//	  alert(document.getElementById("class_alert").value);
	  }
	</script>
	

	<FORM method="post" action="<@ofbizUrl>alertDefine</@ofbizUrl>" name="AlertAddForm">
		<input name="category_alert"   type="hidden" value="error">
		<input name="class_alert"   type="hidden" value="Mailto">
		<input name="alertid"   type="hidden" value="none">
		<input name="define_flag"   type="hidden" value="Add">
		<TABLE BORDER=0 CELLSPACING=0>
			<tr>
				<td width="150"><h3>Alerting on:</h3></td>
				<td>&nbsp;&nbsp;&nbsp;</td><td valign="top"><b>Choose the monitor status that should trigger the alert </b></td>
			</tr>
		</TABLE>
		<TABLE BORDER=0 CELLSPACING=4 width="50%">
			<TR>
				<td><INPUT TYPE=RADIO NAME=category value=error checked><b>Error</b> </td>
				<td><INPUT TYPE=RADIO NAME=category value=warning><b>Warning</b> </td>
				<td><INPUT TYPE=RADIO NAME=category value=good><b>Ok</b></td>
			</tr>
		</table>
		<HR>
		<TABLE BORDER=0 CELLSPACING=0>
			<tr>
				<td width="150"><h3>Alert Type</h3></td>
				<td>&nbsp;&nbsp;&nbsp;</td>
				<td valign="top"><b>Choose the type of alert to create</b></td>
			</tr>
		</TABLE>
		<TABLE BORDER=0 CELLSPACING=4 WIDTH=90%>
			<TR valign="top">
				<TD valign="top">
				<TD><input type=radio checked name=class value="Mailto"></TD>
				<TD valign="top" width="180">E-Mail Alert</TD>
				<TD valign="top">Sends an alert message via e-mail.</TD>
				<TD valign="top"><A HREF=/SiteView/docs/AlertMailto.htm TARGET=Help>Help</A></TD>
			</TR>
			<TR valign="top">
				<TD valign="top">
				<TD><input type=radio  name=class value="Page"></TD>
				<TD valign="top" width="180">Pager Alert</TD>
				<TD valign="top">Sends an alert message via a alphanumeric or numeric pager.</TD>
				<TD valign="top"><A HREF=/SiteView/docs/AlertPage.htm TARGET=Help>Help</A></TD>
			</TR>
			<TR valign="top">
				<TD valign="top">
				<TD><input type=radio  name=class value="Run"></TD>
				<TD valign="top" width="180">Script Alert</TD>
				<TD valign="top">Runs a shell script on this machine or a remote machine.</TD>
				<TD valign="top"><A HREF=/SiteView/docs/AlertRun.htm TARGET=Help>Help</A></TD>
			</TR>
			<TR valign="top">
				<TD valign="top">
				<TD><input type=radio  name=class value="SNMPTrap"></TD>
				<TD valign="top" width="180">SNMP Trap Alert</TD>
				<TD valign="top">Sends an SNMP trap.</TD>
				<TD valign="top"><A HREF=/SiteView/docs/AlertSNMPTrap.htm TARGET=Help>Help</A></TD>
			</TR>
			<TR valign="top">
				<TD valign="top">
				<TD><input type=radio  name=class value="Sound"></TD>
				<TD valign="top" width="180">Sound Alert</TD>
				<TD valign="top">Plays an alert sound on the machine where SiteView is running.</TD>
				<TD valign="top"><A HREF=/SiteView/docs/AlertSound.htm TARGET=Help>Help</A></TD>
			</TR>
		</TABLE>
		<BR>&nbsp;&nbsp;<INPUT TYPE=SUBMIT VALUE="Define Alert" onclick="return change();">
		<BR>
		<HR>
		<TABLE BORDER=0 CELLSPACING=0>
			<tr>
				<td width="180"><h3>Advanced Alerts</h3></td>
				<td>&nbsp;&nbsp;&nbsp;</td>
				<td valign="top"><b>For specific needs of complex environments and may  require additional setup</b></td>
			</tr>
		</TABLE>
		<TABLE BORDER=0 CELLSPACING=4 WIDTH=90%>
			<TR valign="top">
				<TD valign="top">
				<TD><input type=radio  name=class value="DatabaseAlert"></TD>
				<TD valign="top" width="180">Database Alert</TD>
				<TD valign="top">Send an alert to a database by calling a stored procedure or inserting a record</TD>
				<TD valign="top"><A HREF=/SiteView/docs/AlertDatabase.htm TARGET=Help>Help</A></TD>
			</TR>
			<TR valign="top">
				<TD valign="top">
				<TD><input type=radio  name=class value="Disable"></TD>
				<TD valign="top" width="180">Disable or Enable Monitor(s) Alert</TD>
				<TD valign="top">Disables or enables a set of groups or monitors.</TD>
				<TD valign="top"><A HREF=/SiteView/docs/AlertDisable.htm TARGET=Help>Help</A></TD>
			</TR>
			<TR valign="top">
				<TD valign="top">
				<TD><input type=radio  name=class value="NTLogEvent"></TD>
				<TD valign="top" width="180">Log Event Alert</TD>
				<TD valign="top">Logs an event to the Windows NT Event Log</TD>
				<TD valign="top"><A HREF=/SiteView/docs/AlertNTLogEvent.htm TARGET=Help>Help</A></TD>
			</TR>
			<TR valign="top">
				<TD valign="top">
				<TD><input type=radio  name=class value="Post"></TD>
				<TD valign="top" width="180">Post Alert</TD>
				<TD valign="top">Sends an alert message via submitting a form to a CGI script.</TD>
				<TD valign="top"><A HREF=/SiteView/docs/AlertPost.htm TARGET=Help>Help</A></TD>
			</TR>
			<TR valign="top">
				<TD valign="top">
				<TD><input type=radio  name=class value="SMS"></TD>
				<TD valign="top" width="180">SMS Alert</TD>
				<TD valign="top">Send an alert using wireless Short Message Service.</TD>
				<TD valign="top"><A HREF=/SiteView/docs/AlertSMS.htm TARGET=Help>Help</A></TD>
			</TR>
		</TABLE>
	</FORM>
</HTML>
