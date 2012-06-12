<br>
<br>
<P><CENTER><H1>Schedule Preferences</H1></CENTER><P>
<FORM ACTION=  method=POST>
<P><HR><A NAME=additionalSchedule><h2>Schedules allow you to create named schedules, which you can then specify to trigger monitors.</h2></A><P>
<CENTER>
<TABLE WIDTH="100%" BORDER=2 cellspacing=0><CAPTION align=left><font SIZE=4><b>Schedules</b></font></CAPTION>
	<TR CLASS="tabhead">
		<TH WIDTH="40%">Name</TH>
		<TH WIDTH="20%">Type</TH>
		<TH WIDTH="10%">Edit</TH>
		<TH WIDTH="10%">Del</TH>
	</TR>
	 <#list result as table>
	<TR>
		<TD><B>${table._name}</B></TD>
		<TD >${table._type}</TD>
		 <#if table._id=="no">
		 <td></td>	
    	 <#else>
	    	 <#if table._type=="absolute">
			<TD><A HREF="<@ofbizUrl>editAbsoluteSchedule?id=${table._id}</@ofbizUrl>">Edit</A></TD>
			<#else>
			<TD><A HREF="<@ofbizUrl>editRangeSchedule?id=${table._id}</@ofbizUrl>">Edit</A></TD>
			</#if>
		<TD ><A HREF="<@ofbizUrl>delSchedule?id=${table._id}</@ofbizUrl>">X</A></TD>
		</#if> 
	</TR>
	 </#list>

</TABLE>
</CENTER>
<h2>
<br>
<P><A HREF="<@ofbizUrl>rangeSchedule</@ofbizUrl>"><STRONG>Add additional range schedule</STRONG></A>
<UL>Range schedules can be used to disable or enable monitors in a range of times for each day of the week.  The monitors fire at the monitor's specified frequency when enabled by a range schedule.</UL>
<br>
<P><A HREF="<@ofbizUrl>absoluteSchedule</@ofbizUrl>"><STRONG>Add additional absolute schedule</STRONG></A>
<UL>Absolute schedules can be used to fire monitors at specific times in the day for each day of the week.</UL>
</h2>
</FORM>