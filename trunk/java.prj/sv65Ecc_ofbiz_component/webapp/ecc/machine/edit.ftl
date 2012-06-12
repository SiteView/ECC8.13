<#assign data = result.data>
<form method="post"  action="submitUpdateMachine"  class="basic-form" onSubmit="javascript:submitFormDisableSubmits(this)">
<input type="hidden" name="id"  value="${data._id?if_exists}"/>

<div id="_G41_"> <table cellspacing="0" class="basic-table">
  <tr>
   <td class="label">Server Address</td>
   <td colspan="4"><input type="text" name="_host" size="50" value="${data._host?if_exists}"/>
   <span class="tooltip">
	The server address of the remote server (for example, demo.${Static["com.dragonflow.SiteView.Platform"].exampleDomain}).  For HTTP connections, enter the URL of the CGI<br> (for example, http://demo.${Static["com.dragonflow.SiteView.Platform"].exampleDomain}/cgi-bin/remote.sh).  To use the same login credentials for multiple servers, enter multiple server addresses  separated by commas. 
	</span>
   </td>
  </tr>

  <tr>
   <td class="label">OS</td>
   <td colspan="4"><select name="_os" size="1">
    ${Static["com.dragonflow.Page.machinePage"].getOptionsHTML(Static["com.dragonflow.SiteView.Machine"].getAllowedOSs(), data._os?if_exists)}
   </select>
   <span class="tooltip">The operating system (OS) running on the remote server</span>
   </td>
  </tr>

  <tr>
   <td class="label">Connection Method</td>
   <td colspan="4"><select name="_method" size="1">
   ${Static["com.dragonflow.Page.machinePage"].getOptionsHTML(Static["com.dragonflow.SiteView.Machine"].getAllowedMethods(), data._method?if_exists)}
   </select>
   <span class="tooltip">Select the method to use to connect to the remote server. For <b>telnet</b> or <b>rlogin</b>, enter the applicable shell prompt character(s)  in the <b>Prompt</b> field below.</span>
   </td>
  </tr>
  
  	<#include "login.ftl">
  
  <tr>
   <td class="label">Prompt</td>
   <td colspan="4"><input type="text" name="_prompt" size="30" value="${data._prompt?if_exists}"/>
   <span class="tooltip">For <b>telnet</b> and <b>rlogin</b> connections, enter the shell prompt output when the system is ready to accept a command. For example: $  (the default is #)</span>
   </td>
  </tr>

  <tr>
   <td class="label">Login Prompt</td>
   <td colspan="4"><input type="text" name="_loginPrompt" size="30" value="${data._loginPrompt?if_exists}"/>
   <span class="tooltip">For <b>telnet</b> and <b>rlogin</b> connections, the prompt output when the system is waiting for the login to be entered - the default is "ogin:"</span>
   </td>
  </tr>
	
  <tr>
   <td class="label">Password Prompt</td>
   <td colspan="4"><input type="text" name="_passwordPrompt" size="30" value="${data._passwordPrompt?if_exists}"/>
   <span class="tooltip">For <b>telnet</b> connections, the prompt output when the system is waiting for the password to be entered - the default is "assword:"</span>
   </td>

  <tr>
   <td class="label">Secondary Prompt</td>
   <td colspan="4"><input type="text" name="_secondaryPrompt" size="30" value="${data._secondaryPrompt?if_exists}"/>
   <span class="tooltip">Secondary prompt. Separate by ',' for multiple prompts</span>
   </td>
  </tr>
  <tr>
   <td class="label">Secondary Response</td>
   <td colspan="4"><input type="text" name="_secondaryResponse" size="30" value="${data._secondaryResponse?if_exists}"/>
   <span class="tooltip">response to the above prompt. Separate by ',' for multiple responses.</span>
   </td>
  </tr>
  <tr>
   <td class="label">Initialize Shell Environment</td>
   <td colspan="4"><input type="text" name="_initShellEnvironment" size="30" value="${data._initShellEnvironment?if_exists}"/>
   <span class="tooltip">Shell commands to be executed at begining of session. Seperate by ';' for multiple commands.</span>
   </td>
  </tr>
  <#assign isI18N = Static["com.dragonflow.Utils.I18N"].isI18N()>
  <#if isI18N>
  <tr>
   <td class="label">Remote Machine encoding</td>
   <td colspan="4"><input type="text" name="_encoding" size="30"  value="${data._encoding?if_exists}"/>
   <span class="tooltip">Enter code page (ie Cp1252, Shift_JIS, EUC-JP, etc.)</span>
   </td>
  </tr>
  </#if>
  

  <tr>
   <td class="label">Trace</td>
   <td colspan="4"><input type="checkbox" name="_trace" value="on" <#if data._trace?if_exists=="on">checked</#if>/>
   <span class="tooltip">Check this box to trace messages to and from the remote server (messages are  written in the RunMonitor.log file)</span>
   </td>
  </tr>

  <tr>
   <td class="label">Edit and Test</td>
   <td colspan="4"><input type="radio" name="flag" value="test" CHECKED/>
   <span class="tooltip">Check to Add the profile and test the connection</span>
   </td>
  </tr>

  <tr>
   <td class="label">Edit Only</td>
   <td colspan="4"><input type="radio" name="flag" value="edit"/>
   <span class="tooltip">Check to Add the profile only</span>
   </td>
  </tr>

  <tr>
   <td class="label">&nbsp;</td>
   <td><input type="submit" class="buttontext" name="submitButton" value="${uiLabelMap.CommonSave}"/></td>
   <td class="label"></td>
   <td><a class="buttontext" href="machineList">${uiLabelMap.CommonCancel}</a></td>
  </tr>
  
	<#include "adnvacedSSHOptions.ftl">

 </table>
</div>


</form>
