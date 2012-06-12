<BR>
 <P><CENTER><H1>Schedule Preferences</H1></CENTER><P>
 <FORM ACTION="<@ofbizUrl>updateRangSchedule</@ofbizUrl>" method=POST>
 
 <table>
 <tr>
 <td><P>Schedule name:</td>
  <td> <INPUT type=hidden VALUE=${result._id} NAME=id> </td>
 <td> <INPUT type=text VALUE=${result._name} NAME=name> </td>
 <td><span class="tooltip">Enter a display name for this schedule.</span></td>
 <BR>
  
  <table width="589" height="177" border="1">
    <tr>
     
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
  <BR>
  <P>Schedule time range for monitors to be enabled or disabled - for example,
   to enable on Sunday from 10:00 to 22:00<BR>To enter 2 ranges in the same day,
    separate values by a comma. For example,
     a schedule to enable monitors from  midnight to 1 a.m. and then again from 5 a.m. to 10 p.m. would be entered as 
     <tt>00:00,05:00</tt> in the &quot;from&quot; textbox, and <tt>01:00,22:00</tt> in the &quot;to&quot; textbox.
 <br>     <br>  
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
  