<HTML>
<H2>Edit E-Mail Alert on Error</H2>
<P>

<FORM ACTION="" method=POST>
<input type=hidden name=page value=alert>
<input type=hidden name=account value="administrator">
<input type=hidden name=operation value="Edit">
<input type=hidden name=group value=_master>
<input type=hidden name=category value=error>
<input type=hidden name=monitor value=_config>
<input type=hidden name=id value=83965249>
<input type=hidden name=class value=Mailto>

<table border=0 cellspacing=4><tr><td><img src="/SiteView/htdocs/artwork/LabelSpacer.gif"></td><td></td><td></td></tr>
<tr><td colspan=3><hr></td></tr>
<B>Alert Subject(s)</B>
<BLOCKQUOTE><DL>
<DT>
<TABLE>
<TR>
<TD><IMG SRC=/SiteView/htdocs/artwork/empty.gif WIDTH=25><select multiple name=targets size=10> 
<option selected value="_master">All Groups
<option  value="__Health__">Health (__Health__)
<option  value="_UIContext=_master">_UIContext=_master (_UIContext=_master)
<option  value="Group0">sssss (Group0)
<option  value="Group0 6">sssss (Group0): 116
<option  value="Group0 7">sssss (Group0): 192.168.0.249</select></TD>
<TD><I></I></TD>
</TR>
</TABLE>
<DD>Select the Groups and Monitors handled by this Alert.  To select several items, hold down the Control key (on most platforms) while clicking item names.
</DL></BLOCKQUOTE>

<tr><td colspan=3><hr></td></tr><TR><TD><B>Send Mail</B></TD>
<TD> (<A HREF=/SiteView/cgi/go.exe/SiteView?page=mailPrefs&account=administrator>Edit E-Mail Preferences</A>)</TD></TR>

<TR><TD ALIGN="RIGHT" VALIGN="TOP">To</TD><TD><TABLE><TR><TD ALIGN="left" VALIGN="top"><SELECT name=_to size=3 multiple >
<OPTION value="_id:"><OPTION SELECTED value="Other">Other</SELECT><br><INPUT TYPE=TEXT NAME=_to SIZE=40 VALUE="tttttt@ggggg.com"></TD></TR><TR><TD ALIGN="left" VALIGN="top"><FONT SIZE=-1>either choose one or more e-mail setting(s), or enter the e-mail address of the person to send the mail to, separate multiple addresses with commas (example: support@dragonflow.com, siteviewsales@dragonflow.com)</FONT></TD></TR></TABLE></TD><TD><I></I></TD></TR><TR><TD ALIGN="RIGHT" VALIGN="TOP">Template</TD><TD><TABLE><TR><TD ALIGN="left" VALIGN="top"><SELECT name=_template size=1>
<OPTION value=".svn">.svn<OPTION value="AllErrors">AllErrors<OPTION SELECTED value="Default">Default<OPTION value="DefaultUser">DefaultUser<OPTION value="NoDetails">NoDetails<OPTION value="NTEventLog">NTEventLog<OPTION value="PagerMail">PagerMail<OPTION value="ShortestMail">ShortestMail<OPTION value="ShortMail">ShortMail<OPTION value="ShortSubject">ShortSubject<OPTION value="Traceroute">Traceroute<OPTION value="WithDiagnostic">WithDiagnostic<OPTION value="XMLMail">XMLMail</SELECT></TD></TR><TR><TD ALIGN="left" VALIGN="top"><FONT SIZE=-1>choose which template to use for formatting the contents of the message.  If you are sending mail to a pager, choose one of the "short" templates.</FONT></TD></TR></TABLE></TD><TD><I></I></TD></TR><TR><TD COLSPAN=3><hr></TD></TR><TR><TD ALIGN=RIGHT VALIGN=TOP><B>When</B></TD>
<TD><TABLE BORDER=0><TR><TD ALIGN=LEFT VALIGN=TOP>
<DL><DT><INPUT TYPE=RADIO NAME=when value=always null>
Always, after the condition has occurred at least 
<input type=text name=alwaysErrorCount size=3 value="1"> times
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<I><B></B></I></DT>
<DD>only cause an Alert after the condition occurs <B>at least</B> this many times, consecutively.
<DT><INPUT TYPE=RADIO NAME=when value=count checked>Once, after condition occurs exactly 
<input type=text name=errorCount size=3 value="1"> times
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<I><B></B></I></DT>
<DD>only cause an Alert after the condition occurs <B>exactly</B> this many times, consecutively.
</DD><DT><INPUT TYPE=RADIO NAME=when value=multiple null>Initial alert 
<input type=text name=multipleStartCount size=3 value="1"> 
and repeat every <input type=text name=multipleErrorCount size=3 value="1"> 
times afterwards
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<I><B></B></I></DT>
<DD>cause an Alert after the condition occurs X consecutive times and repeat the alert every Y consecutive times thereafter.</DD>

<DT><INPUT TYPE=RADIO NAME=when value=maxErrors null>Once, after 
<input type=text name=maxErrorCount size=3 value="1"> group errors
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<I><B></B></I></DT>
<DD>cause an alert the first time that any monitor in this group gets this many consecutive error readings</DD>
<DT><INPUT TYPE=RADIO NAME=when value=allErrors >Once, when all monitors of this group are in error</B></I></DT>

<DD>cause an alert when all of the monitors in the group are in error</DD>

</TD></TR></TABLE></TD></TR><tr><td colspan=3><hr></td></tr>
</TABLE>
<P>
<input type=submit value=Update> E-Mail Alert</input>

<p><HR><H3>Advanced Options</H3>
<table border=0 cellspacing=4><tr><td><img src="/SiteView/htdocs/artwork/LabelSpacer.gif"></td><td></td><td></td></tr>


<TR><TD ALIGN=RIGHT>Disable Alert</TD>
<TD></TD></TR><TR><td>&nbsp;</td><TD ALIGN=LEFT>

<TABLE BORDER=0><TR>

<TR><TD ALIGN=LEFT><INPUT TYPE=RADIO NAME=alertDisable VALUE=undo 
checked>
Enable Alert</TD></TR>

<TD ALIGN=LEFT><INPUT TYPE=radio NAME=alertDisable VALUE=permanent 
>
Disable alert permanently</INPUT></TD></TR>

<TR><TD ALIGN=LEFT><INPUT TYPE=radio NAME=alertDisable VALUE=timed
> Disable alerts for the next 

<INPUT TYPE=TEXT SIZE=5 NAME=disableAlertTime VALUE=10>
<SELECT SIZE=1 NAME=disableAlertUnits>
<OPTION>seconds<OPTION SELECTED>minutes<OPTION>hours<OPTION>days
</SELECT>

<TR><TD ALIGN=LEFT><INPUT TYPE=RADIO NAME=alertDisable VALUE=scheduled
>

Disable on a one-time schedule from <input type=text size=5 maxlength=5 name=startTimeTime value="09:49"> <input type=text size=10 maxlength=11 name=startTimeDate value="8/5/08">  to <input type=text size=5 maxlength=5 name=endTimeTime value="10:49"> <input type=text size=10 maxlength=11 name=endTimeDate value="8/5/08"> </TD></TR>

</TABLE></TD></TR>

<tr><td colspan=3><hr></td></tr><TR><TD ALIGN=LEFT VALIGN=TOP COLSPAN=2><p><b>Global and Group Alert Filtering</b></p></TD><TD></TD></TR>
<TR><TD>&nbsp;</TD></TR><TR><TD ALIGN=RIGHT VALIGN=TOP>Name Match</TD><TD><TABLE BORDER=0><TR><TD ALIGN=LEFT><input type=text name=nameMatchString size=50 value=""></TD></TR><TR><TD><FONT SIZE=-1>The text to match in the Name string of the monitor before this alert is triggered. For
example, entering <B><tt>URL:</tt></B> means this alert will only be triggered for monitors whose name contains the string "<tt>URL:</tt>". The match is case sensitive.</FONT></TD></TR></TABLE></TD></TR>
<TR><TD ALIGN=RIGHT VALIGN=TOP>Status Match</TD><TD><TABLE BORDER=0><TR><TD ALIGN=LEFT><input type=text name=statusMatchString size=50 value=""></TD></TR><TR><TD><FONT SIZE=-1>The text to match in the Status string of the monitor before this alert is triggered. For
example, entering <B><tt>timeout</tt></B> triggers this alert only for monitors whose status contains the string "<tt>timeout</tt>". The match is case sensitive.</FONT></TD></TR></TABLE></TD></TR>
<TR><TD ALIGN=RIGHT VALIGN=TOP>Monitor Type </TD><TD><TABLE><TR><TD ALIGN=LEFT VALIGN=TOP><select size=1 name=classMatchString><option value=Any Monitor>Any Monitor </option>
<option value=ApacheMonitor>Apache Server</option>
<option value=ASPMonitor>ASP Server</option>
<option value=BandwidthMonitor>Formula Composite</option>
<option value=BrowsableSNMPMonitor>SNMP by MIB</option>
<option value=CheckPointMonitor>CheckPoint Firewall-1</option>
<option value=CiscoMonitor>Cisco Works</option>
<option value=CitrixMonitor>Citrix Server</option>
<option value=ColdFusionMonitor>ColdFusion Server</option>
<option value=CompositeMonitor>Composite</option>
<option value=CPUMonitor>CPU Utilization</option>
<option value=DatabaseMonitor>Database Query</option>
<option value=DB2Monitor>DB2</option>
<option value=DirectoryMonitor>Directory</option>
<option value=DiskSpaceMonitor>Disk Space</option>
<option value=DNSMonitor>DNS</option>
<option value=EBusinessTransactionMonitor>eBusiness Chain</option>
<option value=EJBMonitor>EJB</option>
<option value=FileMonitor>File</option>
<option value=FTPMonitor>FTP</option>
<option value=IISServerMonitor>IIS Server</option>
<option value=IPMIMonitor>IPMI</option>
<option value=LDAPMonitor>LDAP</option>
<option value=LinkMonitor>Link Check</option>
<option value=LogMonitor>Log File</option>
<option value=MailMonitor>Mail</option>
<option value=MAPIMonitor>MAPI</option>
<option value=MemoryMonitor>Memory</option>
<option value=NetscapeMonitor>iPlanet Server</option>
<option value=NetworkBandwidthMonitor>Network Bandwidth</option>
<option value=NetworkMonitor>Network</option>
<option value=NewsMonitor>Connects to a news (NNTP) server and verifies that groups can be retrieved.</option>
<option value=NTCounterMonitor>Windows Performance Counter</option>
<option value=NTDialupMonitor>Windows Dial-up</option>
<option value=NTEventLogMonitor>Windows Event Log</option>
<option value=Oracle9iMonitor>Oracle9i Application Server</option>
<option value=OracleJDBCMonitor>Oracle Database</option>
<option value=PDHMonitor>Windows Resources</option>
<option value=PingMonitor>Ping</option>
<option value=PortMonitor>Port</option>
<option value=RadiusMonitor>Radius</option>
<option value=RealMediaPlayerMonitor>Real Media Player</option>
<option value=RealMonitor>Real Media Server</option>
<option value=RTSPMonitor>RTSP</option>
<option value=SAPMonitor>SAP</option>
<option value=ScriptMonitor>Script</option>
<option value=ServiceMonitor>Service</option>
<option value=SilverStreamMonitor>SilverStream Server</option>
<option value=SNMPMonitor>SNMP</option>
<option value=SNMPTrapMonitor>SNMP Trap</option>
<option value=SQLServerMonitor>SQL Server</option>
<option value=SunOneMonitor>SunONE WebServer</option>
<option value=SybaseMonitor>Sybase</option>
<option value=testPingMonitor>testPing</option>
<option value=TivoliDmPassiveMonitor>Tivoli DM (Passive)</option>
<option value=TuxedoMonitor>Tuxedo</option>
<option value=URLContentMonitor>URL Content</option>
<option value=URLListMonitor>URL List</option>
<option value=URLMonitor>URL</option>
<option value=URLSequenceMonitor>URL Sequence</option>
<option value=WebLogic6xMonitor>WebLogic Application Server</option>
<option value=WebServerMonitor>Web Server</option>
<option value=WebServiceMonitor>Web Service</option>
<option value=WebSphereMonitor>WebSphere Application Server</option>
<option value=WebSphereServletMonitor>WebSphere Performance Servlet</option>
<option value=WindowsMediaMonitor>Windows Media Server</option>
<option value=WindowsMediaPlayerMonitor>Windows Media Player</option>
</select>
</TD></TR><TR><TD><FONT SIZE=-1>Select the type of monitor that will trigger this alert. Only monitors of this type within the group(s) selected in <b>Alert Subject(s)</b> above will trigger this alert.
</FONT></TD></TR></TABLE></TD><TD><I></I></TD></TR>
</TABLE>
</FORM>
<table class=fine border=0 cellspacing=0 width=500 align=center><tr><td><p class=fine align=center><a href="http://www.dragonflow.com/" target="web"><img src=/SiteView/htdocs/artwork/DragonFlow2_Websafe_xsml.gif  border="" alt=""></a> <p>
<p class=fine align=center><small>SiteView , <a href="http://www.dragonflow.com/company/copyright.html" target="web"> Copyright &copy; 2004 </a> , All rights reserved.
</small></p>
</center>
</td></tr></table></BODY>
</HTML>
