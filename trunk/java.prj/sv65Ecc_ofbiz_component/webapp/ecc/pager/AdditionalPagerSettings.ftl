</br>
</br>
<h2>Additional pager settings allow you to create named settings, which you can then specify when creating pager alerts.</h2>
<h1><b>Additional Pager Settings</b></h1>

<table  WIDTH="100%" BORDER=2 cellspacing=0>
    <tr>
      <td>Name</td>
      <td>Status</td>
      <td>Type</td>
      <td>Phone</td>
      <td>PIN</td>
      <td>Edit</td>
      <td>Test</td>
      <td>Del</td>
    </tr>
     <#list result as table>
    <tr>
		      <td>${table._name}</td>
		      <td>${table._disabled}</td>
		      <td>${table._pagerType}</td>
		      <td>${table._pagerAlphaPhone}</td>
		      <td>${table._pagerAlphaPIN}</td>
		      <#if table._id=="no">
		       <td></td>	
    	      <#else>
    	      <td> <a href="<@ofbizUrl>editPagerseting?id=${table._id}</@ofbizUrl>" >Edit</a></td>
		      <td> <a href="<@ofbizUrl>testPagerseting?id=${table._id}</@ofbizUrl>" >Test</a></td>
		      <td> <a href="<@ofbizUrl>delPagerseting?id=${table._id}</@ofbizUrl>" >X</a></td>	
		      </#if>      
    </tr>
    </#list>
</table>
<br/>
 <a href="<@ofbizUrl>AddPagerPreferences</@ofbizUrl>" class="smallSubmit">Add</a>additional pager setting 