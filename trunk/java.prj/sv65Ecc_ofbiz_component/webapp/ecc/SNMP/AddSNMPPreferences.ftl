<br/>
<br/>
<center><h1><b>Add Additional SNMP Settings</b></h1></center>
<br/>
<form id="form1" name="form1"  action="<@ofbizUrl>saveSNMPsetting</@ofbizUrl>">
  <table width="100%" border="1" height="489">
    <tr>
      <td colspan="3">These settings allow you to integrate SiteView with a SNMP management console using SiteView SNMP Trap Alerts.</td>
    </tr>
    <tr>
      <td colspan="3">   The name of these SNMP settings is used to specify SNMP settings when adding alerts</td>
    </tr>
     <tr>
      <td colspan="3"><input type="hidden" name="id"  value=${result._id} ></td>
    </tr>
    <tr>
      <td colspan="3">Setting Name :<input type="text" name="settingName"  value=${result._name} ></td>
    </tr>
    <tr>
      <td colspan="3">Disabling the SNMP settings prevents alert traps from being sent via that SNMP setting</td>
    </tr>
    <tr>
    <#if result._disabled==null>
      <td colspan="3"><input type="checkbox" name="flag" id="checkbox" />Disabled </td>
      <#else>
      <td colspan="3"><input type="checkbox" name="flag" id="checkbox" checked/>Disabled </td>
     </#if> 
    </tr>
    <tr>
      <td width="116">Send to Host: </td>
      <td width="2206"> <input type="text" name="Host" value=${result._snmpHost} ></td>
      <td width="850"><span class="tooltip">  Enter the host name or IP address of the machine running the SNMP console that will receive SNMP traps. For example, snmp.this-company.com or 206.168.191.20.</span>
     </td>
    </tr>
 
     <tr>
      <td width="116">SNMP Object ID:</td>
      <td width="220">
 						<select name="snmpObjectID" size="1" value=${result._snmpObjectID}>
									<option SELECTED value=.1.3.6.1.4.1.11.2.17.1>HP Open View Event</option>
									<option  value=.1.3.6.1.2.1.1>System - MIB-II</option>
									<option  value=.1.3.6.1.4.1.311.1.1.3.1.2>Microsoft - Vendor MIB</option>
									<option  value=.1.3.6.1.2.1.25.1>System - Host Resources MIB</option>
									<option  value=0>other...</option>
				        </select>
      </td>
      <td width="850"><span class="tooltip"> Select or enter the SNMP object that is sending the trap. For example .1.3.6.1.2.1.1 is the "system" object from MIB-II (RFC 1213).</span>
      </td>
    </tr>
    <tr>
      <td width="116">&nbsp;</td>
      <td width="220"><label>
        other£º<input type="text" name="other" id="textfield" >
      </label></td>
      <td width="850">&nbsp;</td>
    </tr>
 
 <tr>
      <td width="116">SNMP Community: </td>
      <td width="220"> <input type="text" name="snmpCommunity" value=${result._snmpCommunity} ></td>
      <td width="850"><span class="tooltip"> The SNMP community name used for this trap - usually this is "public".</span>
      </td>
    </tr>
    
  
    <tr>
      <td width="1160">Trap ID: </td>
      <td width="220"><label>
       Generic:<select name="snmpGeneric" size="1" id="select" value=${result._snmpGeneric}>
								<option  value=0>cold start</option>
								<option  value=1>warm start</option>
								<option SELECTED value=2>link down</option>
								<option  value=3>link up</option>
								<option  value=6>enterprise specific</option>
				</select>
      </label></td>
      <td width="850"><span class="tooltip"> Generic trap type. If the generic trap type is "enterprise specific", then fill in the specific trap type, which is a number.</span>
      </td>
    </tr>
    <tr>
      <td width="116">&nbsp;</td>
      <td width="220"><label>
       Specific:<input type="text" name="Specific" id="textfield5" value=${result._snmpSpecific}>
      </label></td>
      <td width="7746">&nbsp;</td>
    </tr>


    <tr>
      <td width="116">SNMP Trap version:</td>
      <td width="220"><select name="snmpTrapVersion" size=1 value=${result._snmpTrapVersion}>
			<option SELECTED value=V1>V1</option>
			<option  value=V2>V2c</option></td>
		  </select>	
      <td width="850"><span class="tooltip">This describes what version the SNMP trap will be formatted in when sending to your SNMP host.</span></td>
    </tr>
   
   
    <tr>  
      <td width="116"> <input type="submit" name="button" id="button" value="Ìá½»" /></td>
      <td width="220">&nbsp;</td>
      <td width="850">&nbsp;</td>
    </tr>
    
  </table>

</form>