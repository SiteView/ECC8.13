<br>
<P><CENTER><H1>Schedule Preferences</H1></CENTER><P>

<FORM ACTION="<@ofbizUrl>saveAbsoluteSchedule</@ofbizUrl>" method=POST>
<table>
<tr>
<td><P>Schedule name: </td><td><INPUT VALUE="" NAME=name> </td><td><span class="tooltip">Enter a display name for this schedule.</span></td>
</tr>
</table>
<BR>
<TABLE CELLPADDING=0 BORDER=0 CELLSPACING=0>
	<TR>
		<TD>Sunday</TD>
		<TD>&nbsp;at:&nbsp;</TD>
		<TD><INPUT TYPE=TEXT NAME=scheduleAt0 SIZE=20 VALUE=""></TD>
	</TR>
	<TR>
		<TD>Monday</TD>
		<TD>&nbsp;at:&nbsp;</TD>
		<TD><INPUT TYPE=TEXT NAME=scheduleAt1 SIZE=20 VALUE=""></TD>
	</TR>
	<TR>
		<TD>Tuesday</TD>
		<TD>&nbsp;at:&nbsp;</TD>
		<TD><INPUT TYPE=TEXT NAME=scheduleAt2 SIZE=20 VALUE=""></TD>
	</TR>
	<TR>
		<TD>Wednesday</TD>
		<TD>&nbsp;at:&nbsp;</TD>
		<TD><INPUT TYPE=TEXT NAME=scheduleAt3 SIZE=20 VALUE=""></TD>
	</TR>
	<TR>
		<TD>Thursday</TD>
		<TD>&nbsp;at:&nbsp;</TD>
		<TD><INPUT TYPE=TEXT NAME=scheduleAt4 SIZE=20 VALUE=""></TD>
	</TR>
	<TR>
		<TD>Friday</TD>
		<TD>&nbsp;at:&nbsp;</TD>
		<TD><INPUT TYPE=TEXT NAME=scheduleAt5 SIZE=20 VALUE=""></TD>
	</TR>
	<TR>
		<TD>Saturday</TD>
		<TD>&nbsp;at:&nbsp;</TD>
		<TD><INPUT TYPE=TEXT NAME=scheduleAt6 SIZE=20 VALUE=""></TD>
	</TR>
</TABLE>
<br>
<P>Absolute schedule of events for monitors. Separate times ranges in the same day must be separated by a &quot;,&quot; (comma). 
 For example, entering <tt>2:30,4,15:44</tt> will trigger events at 2:30am, 4:00am, and 3:44pm for a given day.
<br><br>
 <TABLE border="0" width="90%">
	<tr>
		<td>
		<INPUT TYPE=SUBMIT VALUE="Save Changes"></TD><td width="25%">&nbsp;
		</td>
		<td align=right><A HREF="<@ofbizUrl>schedulePreferences</@ofbizUrl>">Back to Schedule Preferences</A>
		</TD>
	</TR>
</TABLE>
</FORM> 
 