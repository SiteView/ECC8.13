<#assign NO_CHANGED_PASSWORD = Static["com.siteview.svecc.service.General"].NO_CHANGED_PASSWORD>

<form method="post"  action="saveGeneral"  class="basic-form" onSubmit="javascript:submitFormDisableSubmits(this)">

<div id="_G41_"> <table cellspacing="0" class="basic-table">

  <tr>
   <td class="label">Locale-specific Date and Time</td>
   <td colspan="4"><input type="checkbox" name="_localeEnabled" value="CHECKED" ${data._localeEnabled?if_exists}/>
   <span class="tooltip">Enables the display of dates and times in a locale-specific manner. The default is the United States format.
   <br>See the General Preferences Help page for more information about over-riding the default time and date locale used by ${Static["com.dragonflow.SiteView.Platform"].productName}.
   </span>
   </td>
	</tr>

  <tr>
   <td class="label">International Version</td>
   <td colspan="4"><input type="checkbox" name="_isI18N" value="CHECKED" ${data._isI18N?if_exists}/>
   <span class="tooltip">Enables ${Static["com.dragonflow.SiteView.Platform"].productName} to work with multiple character sets. When checked, all character encodings will be honored (for example, foreign language web pages).  When unchecked, only the local system encoding is honored.
   </span>
   </td>
	</tr>

  <tr>
   <td class="label">Number of backups per file</td>
   <td colspan="4"><input type="text" name="_backups2Keep" size="5" value="${data._backups2Keep?if_exists}"/>
   <span class="tooltip">
	Enter the number of backups per file that you would like to keep. ${Static["com.dragonflow.SiteView.Platform"].productName} will name them with a .bak.1, .bak.2,...bak.#, where 1 is the lastest backup file.
	</span>
   </td>
  </tr>

  <tr>
   <td class="label">Operator Acknowledgement</td>
   <td colspan="4"><input type="checkbox" name="_acknowledgeMonitors" value="CHECKED" ${data._acknowledgeMonitors?if_exists}/>
   <span class="tooltip">
   Enables Operator Acknowledgement Functionality. Allows users to click on a monitor status icon and enter an acknowledgement text and time.
   </span>
   </td>
	</tr>

  <tr>
   <td class="label">Alert Icons</td>
   <td colspan="4"><input type="checkbox" name="_alertIconLink" value="CHECKED" ${data._alertIconLink?if_exists}/>
   <span class="tooltip">
   Enables display of alert information for groups and monitors.
   </span>
   </td>
	</tr>

  <tr>
   <td class="label">Report Icons</td>
   <td colspan="4"><input type="checkbox" name="_reportIconLink" value="CHECKED" ${data._reportIconLink?if_exists}/>
   <span class="tooltip">
   Enables display of report information for groups and monitors.
   </span>
   </td>
	</tr>

  <tr>
   <td class="label">Groups per Row</td>
   <td colspan="4"><input type="text" name="_mainGaugesPerRow" size="5" value="${data._mainGaugesPerRow?if_exists}"/>
   <span class="tooltip">
	Enter the number of group names to display in each row on the main SiteView Screen.
	</span>
   </td>
  </tr>

  <tr>
   <td class="label">Blue Gauges</td>
   <td colspan="4"><input type="checkbox" name="_displayGauges" value="CHECKED" ${data._displayGauges?if_exists}/>
   <span class="tooltip">
   Enable the display blue gauges for monitors and groups.
   </span>
   </td>
	</tr>

  <tr>
   <td class="label">Suspend Monitors</td>
   <td colspan="4"><input type="checkbox" name="_suspendMonitors" value="CHECKED" ${data._suspendMonitors?if_exists}/>
   <span class="tooltip">
   Suspend all monitors. When checked, all monitors will be suspended. When unchecked, all monitors will start running according to their previous configuration.
   </span>
   </td>
	</tr>


  <tr>
   <td colspan="5">
   <b><u>Default Authentication Credentials</u></b>
   </td>
  </tr>

  <tr>
   <td class="label">Username</td>
   <td colspan="4"><input type="text" name="_defaultAuthUsername" size="30" value="${data._defaultAuthUsername?if_exists}"/>
   <span class="tooltip">
	Enter the default username to be used for authentication with remote systems.  Both "username" and "DOMAIN\username" are valid formats.
	</span>
   </td>
  </tr>
 
  <tr>
   <td class="label">Password</td>
   <td colspan="4"><input type="password" name="_defaultAuthPassword" size="30" value="${NO_CHANGED_PASSWORD}"/>
   <span class="tooltip">
	Enter the default password to be used for authentication with remote systems.
	</span>
   </td>
  </tr>
 
  <tr>
   <td class="label">When to Authenticate</td>
   <td colspan="4"><select size=1 name=_defaultAuthWhenToAuthenticate>
	${Static["com.dragonflow.Page.generalPrefsPage"].getOptionsHTML(Static["com.dragonflow.StandardPreference.GeneralDefaultPreferences"].getAuthOn401DropDown(), data._defaultAuthWhenToAuthenticate?if_exists)}
   </select>
   <span class="tooltip">
	When are the user/password to be sent with URL requests?
	</span>
   </td>
  </tr>
  <tr>
   <td class="label">&nbsp;</td>
   <td><input type="submit" class="buttontext" name="submitButton" value="${uiLabelMap.CommonSave}"/></td>
   <td class="label"></td>
   <td><a class="buttontext" href="main">${uiLabelMap.CommonCancel}</a></td>
  </tr>
 
  </table>
</div>


</form>
