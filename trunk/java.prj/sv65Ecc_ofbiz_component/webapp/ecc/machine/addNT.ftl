<form method="post"  action="submitAddMachineNT"  class="basic-form" onSubmit="javascript:submitFormDisableSubmits(this)">

<div id="_G41_"> <table cellspacing="0" class="basic-table">
  <tr>
   <td class="label">NT Server Address</td>
   <td colspan="4"><input type="text" name="_host" size="50"/>
   <span class="tooltip">Enter the UNC style name (example:  \\machinename) or the IP address of the remote machine.  To use the same login credentials for multiple servers, enter multiple server addresses  separated by commas.</span>
   </td>
  </tr>

  <tr>
   <td class="label">Connection Method</td>
   <td colspan="4"><select name="_method" size="1">
   ${Static["com.dragonflow.Page.ntmachinePage"].getOptionsHTML(Static["com.dragonflow.SiteView.Machine"].getNTAllowedMethods(), "")}
   </select>
   <span class="tooltip">Select the method used to connect to the remote server. Requires that applicable services be enabled on the remote machine</span>
   </td>
  </tr>
	
	<#include "login.ftl">

  <tr>
   <td class="label">Trace</td>
   <td colspan="4"><input type="checkbox" name="_trace" value="on"/>
   <span class="tooltip">Check to enable trace messages to and from the remote NT server in the RunMonitor.log file</span>
   </td>
  </tr>

  <tr>
   <td class="label">Add and Test</td>
   <td colspan="4"><input type="radio" name="flag" value="test" CHECKED/>
   <span class="tooltip">Check to Add the profile and test the connection</span>
   </td>
  </tr>

  <tr>
   <td class="label">Add Only</td>
   <td colspan="4"><input type="radio" name="flag" value="add"/>
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
