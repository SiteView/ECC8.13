<FORM ACTION="<@ofbizUrl>saveLogSetting</@ofbizUrl>" method=POST>
<BR><BR>
<CENTER><H1>SiteView Log File Preferences</H1></CENTER>
<BR>
<H2><p>Sustained operations monitoring of web systems can generate a large amount of data. 
SiteView  stores this data in log files on the SiteView machine. 
 The following settings allow you to limit how much data is saved in SiteView  log files.</p></H2>
 <hr>
<TABLE border=0 width=100% cellspacing=0 cellpadding=5>
 <TR>
	 <TD ALIGN=LEFT VALIGN=TOP WIDTH=20%> Daily Logs To Keep:</TD>
	 
	 <TD VALIGN=TOP> <input type=text name=dailyLogKeepDays size=10 value=${setInfo._dailyLogKeepDays}></TD>
	 
	 <TD VALIGN=TOP><span class="tooltip">Enter the number of days of monitoring data to keep. 
	  Once a day, SiteView deletes any logs older than the specified number of days.</span></TD>
</TR>
<TR>
	<TD ALIGN=LEFT VALIGN=TOP WIDTH=20%>Maximum Size of Logs: </TD>
	
	<TD VALIGN=TOP> <input type=text name=dailyLogTotalLimit size=10 value=${setInfo._dailyLogTotalLimit}><P></TD>
	
	<TD VALIGN=TOP><span class="tooltip">Optional, enter the maximum size, in bytes, allowed for all  monitoring logs.
	 Once a day, SiteView checks the total size of all monitoring logs  and removes any old logs that are over the maximum size.
	  If blank, the size is not checked.</span>
	</TD>
</TR> 
</table>
<HR>
<CENTER><H1>Database Logging</H1></CENTER>
<H2><p>SiteView can optionally log a copy of all the monitoring data into a database.
 Any database which supports the JDBC standards can be used, including Microsoft SQL Server and Oracle.
<br><b>(Note:</b> changes to Database Logging preferences do not take effect until SiteView is restarted)
</H2>
<hr>
<TABLE border=0 width=100% cellspacing=0 cellpadding=5>
<TR>
	<TD ALIGN=LEFT VALIGN=TOP WIDTH=20%>Database Connection URL: </TD>
	
	<TD VALIGN=TOP><input type=text name=logJdbcURLSiteViewLog size=40 value=${setInfo._logJdbcURLSiteViewLog}></TD>
	
	<TD VALIGN=TOP><span class="tooltip">Enter the URL to the database connection (for example, if the ODBC connection is called SiteViewLog, the URL would be jdbc:odbc:SiteViewLog)</span>
	</TD>
</TR>
<TR>
	<TD ALIGN=LEFT VALIGN=TOP WIDTH=20%>Database Driver:</TD>
	
	<TD VALIGN=TOP> <input type=text name=logJdbcDriverSiteViewLog size=40 value=${setInfo._logJdbcDriverSiteViewLog}></TD>
	
	<TD VALIGN=TOP>Driver used to connect to the database</TD>
</TR>
<TR>
	<TD ALIGN=LEFT VALIGN=TOP WIDTH=20%>Database Username: </TD>
	
	<TD VALIGN=TOP><input type=text name=logJdbcUserSiteViewLog size=40 value=${setInfo._logJdbcUserSiteViewLog}>
	</TD>
	
	<TD VALIGN=TOP><span class="tooltip">Enter the username used to connect to the database(applies to primary and backup databases).</span>
	</TD>
</TR>
<TR>
	<TD ALIGN=LEFT VALIGN=TOP WIDTH=20%>Database Password:</TD>
	
	<TD VALIGN=TOP>
	<input type=password name=logJdbcPasswordSiteViewLog value=${setInfo._logJdbcPasswordSiteViewLog} size=40>
	
	<TD VALIGN=TOP><span class="tooltip">Enter the password used to connect to the database (applies to primary and backup databases).</span>
	</TD>
</TR>
<TR>
	<TD ALIGN=LEFT VALIGN=TOP WIDTH=20%>Backup Database Connection URL: </TD>
	
	<TD VALIGN=TOP> <input type=text name=logJdbcURLBackupSiteViewLog size=40 value=${setInfo._logJdbcURLBackupSiteViewLog}>
	</TD>
	
	<TD VALIGN=TOP> <span class="tooltip">Optional, enter the database URL to use if the main database connection is not available</span>
	</TD>
</TR>
</TABLE>
<hr>
<BR>
<input type=submit value="Save Changes">
</FORM>