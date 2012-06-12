</br>
</br>
<center><h1><b> Dynamic Update Sets</b></h1></center>
<h2>
Use SiteView to query a SNMP MIB or JDBC Database for new server addresses and create new monitors dynamically for the server using Monitor Sets.
</h2>

<table  WIDTH="100%" BORDER=2 cellspacing=0>
    <tr>
      <td>Name</td>
      <td>Server</td>
      <td>Edit</td>
      <td>Del</td>
      <td>Check</td>      
    </tr>
     <#list result as table>
    <tr>
		      <td>${table._name}</td>
		      <td>${table._host}</td>
		      <#if table._id=="no">
		       <td></td>	
    	      <#else>
    	      <td> <a href="<@ofbizUrl>AddDynamicPreferences?id=${table._id}</@ofbizUrl>" >Edit</a></td>
		      <td> <a href="<@ofbizUrl>delDynamicseting?id=${table._id}</@ofbizUrl>" >X</a></td>
		      <td> <a href="<@ofbizUrl>checkDynamicseting?id=${table._id}</@ofbizUrl>" >Re-Check</a></td>	
		      </#if>      
    </tr>
    </#list>
</table>
<br/>
 <a href="<@ofbizUrl>AddDynamicPreferences</@ofbizUrl>" class="smallSubmit">Add</a>a Dynamic Update Set 
