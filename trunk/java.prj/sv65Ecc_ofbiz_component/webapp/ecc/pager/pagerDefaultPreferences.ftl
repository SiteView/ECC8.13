</br>
</br>
<center><h1><b> Default Pager Preferences</b></h1></center>
<h2>These settings allow you to integrate SiteView with a SNMP management console using SiteView SNMP Trap Alerts.</h2>

<hr>
<FORM action="<@ofbizUrl>savePagerSetting</@ofbizUrl>" method=POST>
<TABLE border=0 width=100% cellspacing=0 cellpadding=5>

	<TR>
		<TD>Modem port/path:&nbsp;</td>
		<td><select name=pagerPort size=1 value=${result._pagerPort}>
				<option  value=COM1> COM1 </option>
				<option  value=COM2> COM2 </option>
				<option  value=COM3> COM3 </option>
				<option  value=COM4> COM4 </option>
				<option  value=COM5> COM5 </option>
				<option  value=COM6> COM6 </option>
				<option  value=COM7> COM7 </option>
				<option  value=COM8> COM8 </option>
			</select>
		</TD>
		<td> <span class="tooltip">SiteView Pager Alerts are sent using a modem connected directly to the SiteView server.</span></td>
	</TR>
	
	<TR>
		<TD>Connection speed:&nbsp;</td>
		<TD><select name=pagerSpeed size=1 value=${result._pagerSpeed}>
				<option  value=300> 300 </option>
				<option  value=1200> 1200 </option>
				<option  value=2400> 2400 </option>
				<option  value=9600> 9600 </option>
			</select><span class="tooltip"> baud</span>
		</td>
		<td><span class="tooltip">Use the default speed of 1200 unless your paging service provider tells you otherwise.</span>
		</TD>
	</TR>
</TABLE>

<h3>Pager Connection Options:</h3><hr>
<TABLE border=0 width=100% cellspacing=0><tr><td width=15%></td><td></td><td></td></tr>
	<tr>
		<td colspan=2 valign=top><input type=radio name=pagerType value=alpha ><b>Modem-to-Modem Connection (Preferred)</b></td>
		<td> <span class="tooltip">Send alphanumeric pager messages by connecting to a modem at paging service.<p></span></td>
	</tr>
	<tr>
		<td valign=top><p>Modem number:</p></td>
		<td valign=top><input type=text name=pagerAlphaPhone size=40 value=${result._pagerAlphaPhone}></td>
		<td valign=top><span class="tooltip">Contact your paging service to find out the Modem Number (TAP/IXO number) for paging.</span>  
		<br>  <A href=/SiteView/docs/PagerPref.htm#ModemNumber TARGET=Help>
		Common pager service modem numbers</a>
		</td>
	</tr> 
	<tr>
		<td valign=top><p>PIN number:</p></td>
		<td> <input type=text name=pagerAlphaPIN size=40 value=${result._pagerAlphaPIN}></td>
		<td valign=top><span class="tooltip"><p>Enter the last seven digits of your pager's PIN number.</span>  </td>
	</tr>
	<tr><td colspan=3><hr></td></tr>
	<tr>
		<td colspan=2 valign=top><input type=radio name=pagerType value=direct ><b>Dial and Enter Message</b></td>
		<td valign=top><span class="tooltip">Use a direct phone number to send a numeric page.  Works with most local paging services.<p></span></td>
	</tr>
	<tr>
		<td valign=top><p>Phone number:</p></td><td><input type=text name=pagerDirectPhone size=40 value=${result._pagerDirectPhone}></td>
		<td></td>
	</tr>
	<tr><td colspan=3><hr></td></tr>
	<tr>
		<td colspan=2 valign=top><input type=radio name=pagerType value=option ><b>Dial, Enter Command, and Enter Message</b></td>
		<td valign=top><span class="tooltip">Use a direct number but enter a command before sending a page.  Use this option if your paging company requires a 
		PIN number before sending a page.<p></span>
		</td>
	</tr> 
	<tr>
		<td valign=top><p>Phone number:</p></td><td valign=top> <input type=text name=pagerOptionPhone size=40 value=${result._pagerOptionPhone}></td>
		<td></td>
	</tr>
	<tr>
		<td valign=top><p>Send page command:</p></td>
		<td valign=top> <input type=text name=pagerOption size=40 value=${result._pagerOption}></td>
		<td></td>
	</tr>
	<tr><td colspan=3><hr></td></tr>
	<tr>
		<td colspan=2 valign=top><input type=radio name=pagerType value=custom checked><b>Custom Modem Connection</b></td>
		<td valign=top><span class="tooltip">Use this option if custom modem commands are required.<p></span></td>
	</tr>
	<tr>
		<td valign=top><p>Modem command:</p></td> 
		<td valign=top> <input type=text name=pagerCustom size=40 value=${result._pagerCustom}></td>
		<td></td>
	</tr>
	<tr>
		<td>&nbsp;</td>
		<td colspan=2><span class="tooltip">The modem command string should contain the phone number to dial, any additional digits, followed by $message. 
		 SiteViewreplaces <tt>$message</tt> variable with the message specified in the Pager Alert definitionwhere the message should be inserted. 
		  The comma character creates a short pause.<p></span>
		<span class="tooltip">For example: if the pager company's number is 123-4567, your pager PIN is 333-3333, and each command must be followed by the # key, the Modem command
		might look like <tt>ATDT 123-4567,,333-3333#,,$message#</tt></span>
		<p></td>
	</tr>
</TABLE>

<input type=submit value="Save Changes">

</FORM>