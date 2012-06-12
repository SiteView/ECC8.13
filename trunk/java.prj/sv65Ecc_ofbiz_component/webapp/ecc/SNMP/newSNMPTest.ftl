<form action="<@ofbizUrl>SNMPSend</@ofbizUrl>" >

<center><h1><b>SNMP Trap Test for ${result._name}</b></h1></center>

<br/>
Send a test SNMP trap. 
<br/>
Enter a message to be sent with the trap. 
<br/>
<table>
<tr>
<td>
SNMP Message:<input type="text" name="message" size="35">
</td>
</tr>
<tr>
<td>
<input type="hidden" name="id" size="35" value=${result._id}>
</td>
</tr>
</table>

<br/>
<input type="hidden" name="_snmpHost" value=${result._snmpHost}>
Send to Host:${result._snmpHost}
<br/>
<input type="hidden" name="_snmpObjectID" value=${result._snmpObjectID}>
SNMP Object ID:${result._snmpObjectID}
<br/>
<input type="hidden" name="_snmpCommunity" value=${result._snmpCommunity}>
SNMP Community:${result._snmpCommunity}
<br/>
<input type="hidden" name="_snmpGeneric" value=${result._snmpGeneric}>
Generic Trap ID:${result._snmpGeneric}
<br/>
<input type="hidden" name="_snmpSpecific" value=${result._snmpSpecific}>
Specific Trap ID:${result._snmpSpecific}
<br/>

Specific Trap Version:${result._snmpTrapVersion}
<br/>
<input type="submit" name="button" id="button" value="Ìá½»" />

<p align="right"> <a href="<@ofbizUrl>SNMPPreference</@ofbizUrl>">Back to SNMP Preferences </a></p>
</form