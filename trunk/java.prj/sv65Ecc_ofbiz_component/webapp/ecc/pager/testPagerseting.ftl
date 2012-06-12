
<CENTER><H2>Pager Test for admin</H2></CENTER><P>

<FORM action="<@ofbizUrl>sendTest</@ofbizUrl>" method=POST>
<input type=hidden name=id value=${result.id}>
Send a test message to the pager.
<p>
Enter the message to send.
<table><tr><td>
<p>Message: <input type=text name=message size=50>
</td></tr></table>
<br>
<p>Using Pager Command: ${result.value}
<p>
<p>&nbsp;</p>
<TABLE border="0" width="90%"><tr><td>

<input type=submit name=send value="Send"> a test Pager message
<td width="25%">&nbsp;</td>
<td align=right><A HREF="<@ofbizUrl>pagerPreferen</@ofbizUrl>">Back to Pager Preferences</A></TD></TR>
</TABLE>
</FORM>
