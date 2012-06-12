<form id="form1" name="AdditionSettingform" method="post" action="<@ofbizUrl>SaveAdditionSetting</@ofbizUrl>">

   <table cellspacing="4"> 
	      <tr class="header-row">	      
			 <td colspan="3"><div align="center"><h1>Add Additional E-mail Setting</h1></div></td>	
	      </tr>  
	<tr>
		<td>
		    The name of these e-mail settings is used to specify e-mail targets when adding alerts
		</td>
	</tr>       
	<tr>
		<td>
		<input type="hidden" name="id" value="${result._id?if_exists}"/>
		Setting Name :<input type="text" name="SettingName" value="${result._name?if_exists}" size="50"/>
		</td>
	</tr> 
	<tr>
		<td>
		The e-mail addresses that alerts will be sent to when using the e-mail setting. Separate multiple 
		addresses with commas (example: support@mercury.com, sitescopesales@mercury.com)
		</td>
	</tr> 
	<tr>
		<td>
		E-mail To:<input type="text" name="emailTo" value="${result._email?if_exists}" size="50"/>
		</td>
	</tr> 	  
	<tr>
		<td>
		Disabling the e-mail settings prevents alert e-mail messages from being sent via that e-mail setting
		</td>
	</tr> 
	<tr>
		<#if result._disabled?has_content>
		<td>
		 <input type="checkbox" name="additionalMailDisabled1" id="pp" checked/><span class="tooltip">Disabled</span>
		</td>
		<#else>
		<td>
		 <input type="checkbox" name="additionalMailDisabled" id="pp2" /><span class="tooltip">Didabled</span>
		</td>
		</#if>
	</tr> 
	<tr>
		<td>
		 <div align="center"><h2>Advanced Options</h2></div></td>
		</td>
	</tr>	
	<tr>
		<td>
		<b>Template :</b>        <select name="additionalMailTemplate"  id="pp3" value=" ${result._template?if_exists}">
											<OPTION value=".svn">.svn</OPTION>
											<OPTION value="AllErrors">AllErrors</OPTION>
											<OPTION value="Default">Default</OPTION>
											<OPTION value="DefaultUser">DefaultUser</OPTION>
											<OPTION value="NoDetails">NoDetails</OPTION>
											<OPTION value="NTEventLog">NTEventLog</OPTION>
											<OPTION value="PagerMail">PagerMail</OPTION>
											<OPTION value="ShortestMail">ShortestMail</OPTION>
											<OPTION value="ShortMail">ShortMail</OPTION>
											<OPTION value="ShortSubject">ShortSubject</OPTION>
											<OPTION value="Traceroute">Traceroute</OPTION>
											<OPTION value="WithDiagnostic">WithDiagnostic</OPTION>
											<OPTION value="XMLMail">XMLMail</OPTION>
                            	 </select>

		</td>
	</tr>
	<tr>
		<td>
		 optional template to use with this e-mail settings - if a template is selected, 
		 this template will be used for sending the alert to this e-mail setting
		</td>
	</tr> 
	<tr>
		<td>
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
		optional schedule for these settings to be enabled - for example, enable Sunday from 10:00 to 22:00
		</td>
	</tr> 
 		
  </table> 
  <p>
    <label>
    <input type="submit" name="" id="" value="${uiLabelMap.commitSet}" />
    </label>
  </p>

</form>
