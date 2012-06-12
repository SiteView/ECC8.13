</br>
</br>
<center><h1><b>Add Additional Pager Settings</b></h1></center>
</br>
</br>


<FORM action="<@ofbizUrl>saveAddPagerSetting</@ofbizUrl>" method=POST>
<h3>The name of these pager settings is used to specify pagers when adding alerts</h3>
<table><tr><td>
Setting Name:<input type=text size=30 name=additionalPagerName value=${result._name} >
</td></tr>
<tr><td><input type=hidden size=30 name=id value=${result._id} ></td></tr>
</table>
<h3>Disabling the pager settings prevents alert pages from being sent via that pager setting</h3>
<BLOCKQUOTE>
    <#if result._disabled=="no"||result._disabled==null>
      <input type=checkbox  name=disabled >Disabled
      <#else>
     <input type=checkbox name=disabled  checked/>Disabled </td>
     </#if> 
</BLOCKQUOTE>
<h3>Most paging companies use 1200 baud - you only need to change the modem speed if your paging company requires it.</h3>
<BLOCKQUOTE>
<select name=pagerSpeed size=1>
	<option value=300> 300 </option >
	<option value=1200> 1200 </option >
	<option value=2400> 2400  </option >
	<option value=9600> 9600 </option >
</select> <span class="tooltip"> baud </span>
</BLOCKQUOTE>


<h3>Pager Connection Options:</h3><hr>
<TABLE border=0 width=100% cellspacing=0><tr><td width=15%></td><td></td><td></td></tr>
	<tr>
	    <#if result._pagerType=="alpha">
		<td colspan=2 valign=top><input type=radio name=pagerType value=alpha checked><b>Modem-to-Modem Connection (Preferred)</b></td>
		 <#else>
		 <td colspan=2 valign=top><input type=radio name=pagerType value=alpha ><b>Modem-to-Modem Connection (Preferred)</b></td>
		</#if>
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
		 <#if result._pagerType=="direct">
		<td colspan=2 valign=top><input type=radio name=pagerType value=direct checked><b>Dial and Enter Message</b></td>
		 <#else>
		 <td colspan=2 valign=top><input type=radio name=pagerType value=direct><b>Dial and Enter Message</b></td>
		 </#if>
		<td valign=top><span class="tooltip">Use a direct phone number to send a numeric page.  Works with most local paging services.<p></span></td>
	</tr>
	<tr>
		<td valign=top><p>Phone number:</p></td><td><input type=text name=pagerDirectPhone size=40 value=${result._pagerDirectPhone}></td>
		<td></td>
	</tr>
	<tr><td colspan=3><hr></td></tr>
	<tr>
		 <#if result._pagerType=="option">
		<td colspan=2 valign=top><input type=radio name=pagerType value=option checked><b>Dial, Enter Command, and Enter Message</b></td>
		<#else>
		<td colspan=2 valign=top><input type=radio name=pagerType value=option ><b>Dial, Enter Command, and Enter Message</b></td>
		 </#if>
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
		 <#if result._pagerType=="custom">
		<td colspan=2 valign=top><input type=radio name=pagerType value=custom checked><b>Custom Modem Connection</b></td>
		<#else>
		<td colspan=2 valign=top><input type=radio name=pagerType value=custom ><b>Custom Modem Connection</b></td>
		 </#if>
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

<input type=submit value="Save Additional Setting">

<p><HR><CENTER><H1>Advanced Options</H1></CENTER>
</br>
 <table width="589" height="177" border="1">
    <tr>
      <td width="114" rowspan="7"><div align="center">Schedule</div></td>
      <td width="72">Sunday</td>
      <td width="89"><label>
        <select name="select0" size="1" id="select" onChange="SunDayChange();">
          <option value="disabled">disabled</option>
          <option >enabled</option>
        </select>
      </label></td>
      <td width="35">from </td>
      <td width="71"><input type="text" name="scheduleStart0" id="textfield14" /></td>
      <td width="65">to</td>
      <td width="288"><label>
        <input type="text" name="scheduleEnd0" id="textfield" />
      </label></td>
    </tr>
    <tr>
      <td>Monday</td>
      <td><select name="select1" size="1" id="select2">
          <option value="disabled">disabled</option>
          <option >enabled</option>
      </select></td>
      <td>from </td>
      <td><input type="text" name="scheduleStart1" id="textfield13" /></td>
      <td>to</td>
      <td><input type="text" name="scheduleEnd1" id="textfield2" /></td>
    </tr>
    <tr>
      <td>Tuesday</td>
      <td><select name="select2" size="1" id="select3">
         <option value="disabled">disabled</option>
          <option >enabled</option>
      </select></td>
      <td>from </td>
      <td><input type="text" name="scheduleStart2" id="textfield12" /></td>
      <td>to</td>
      <td><input type="text" name="scheduleEnd2" id="textfield3" /></td>
    </tr>
    <tr>
      <td>Wednesday</td>
      <td><select name="select3" size="1" id="select4">
          <option value="disabled">disabled</option>
          <option >enabled</option>
      </select></td>
      <td>from </td>
      <td><input type="text" name="scheduleStart3" id="textfield11" /></td>
      <td>to</td>
      <td><input type="text" name="scheduleEnd3" id="textfield4" /></td>
    </tr>
    <tr>
      <td>Thursday</td>
      <td><select name="select4" size="1" id="select5">
          <option value="disabled">disabled</option>
          <option >enabled</option>
      </select></td>
      <td>from </td>
      <td><input type="text" name="scheduleStart4" id="textfield10" /></td>
      <td>to</td>
      <td><input type="text" name="scheduleEnd4" id="textfield5" /></td>
    </tr>
    <tr>
      <td>Friday</td>
      <td><select name="select5" size="1" id="select6">
          <option value="disabled">disabled</option>
          <option >enabled</option>
      </select></td>
      <td>from </td>
      <td><input type="text" name="scheduleStart5" id="textfield9" /></td>
      <td>to</td>
      <td><input type="text" name="scheduleEnd5" id="textfield6" /></td>
    </tr>
    <tr>
      <td>Saturday</td>
      <td><select name="select6" size="1" id="select7">
        <option value="disabled">disabled</option>
          <option >enabled</option>
      </select></td>
      <td>from </td>
      <td><input type="text" name="scheduleStart6" id="textfield8" /></td>
      <td>to</td>
      <td><input type="text" name="scheduleEnd6" id="textfield7" /></td>
    </tr>
  </table>			
		</td>
	</tr> 
 	<tr>
		<td>
		<h3>optional schedule for these settings to be enabled - for example, enable Sunday from 10:00 to 22:00</h3>
		</td>
	</tr> 
 		
  </table> 
<P>
</FORM>