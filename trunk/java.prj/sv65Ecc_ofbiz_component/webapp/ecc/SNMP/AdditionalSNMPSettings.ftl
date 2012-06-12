</br>
</br>
<h2>Additional SNMP settings allow you to create named settings, which you can then specify when creating SNMP trap alerts.</h2>
<h1><b>Additional SNMP Settings</b></h1>

<table  WIDTH="100%" BORDER=2 cellspacing=0>
    <tr>
      <td>Name</td>
      <td>Host</td>
      <td>Object ID</td>
      <td>Trap</td>
      <td>Edit</td>
      <td>Test</td>
      <td>Del</td>
    </tr>
     <#list result as table>
    <tr>
		      <td>${table._name}</td>
		      <td>${table._snmpHost}</td>
		      <td>${table._snmpObjectID}</td>
		      <td>${table._snmpGeneric}</td>
		      <#if table._id=="no">
		       <td></td>	
    	      <#else>
    	      <td> <a href="<@ofbizUrl>editSNMPseting?id=${table._id}</@ofbizUrl>" >Edit</a></td>
		      <td> <a href="<@ofbizUrl>testSNMPseting?id=${table._id}</@ofbizUrl>" >Test</a></td>
		      <td> <a href="<@ofbizUrl>delSNMPseting?id=${table._id}</@ofbizUrl>" >X</a></td>	
		      </#if>      
    </tr>
    </#list>
</table>
<br/>
 <a href="<@ofbizUrl>AddSNMPPreferences</@ofbizUrl>" class="smallSubmit">Add</a>additional SNMP setting 