 <table cellspacing="0" class="basic-table hover-bar">
    <tr class="header-row">
        <td>${uiLabelMap.svUserId}</td>
        <td>${uiLabelMap.svUserRealName}</td>
        <td>${uiLabelMap.svUserDisabled}</B></td>
        <td><B>&nbsp</B></td>
     </tr>  
     <#list result as table>
      	<#if table.disabled?has_content && table.disabled>
      	<tr>
	        <td>
	        	<a href="<@ofbizUrl>everyUserInfo?userId=${table.id}</@ofbizUrl>"> ${table.id}</a>
	        </td>
	        <td> ${table.realName?if_exists}</td>
	        <td> ${uiLabelMap.svUserYes}</td>
		<#else>
		<tr class="selected">
		<td > 
		 <a href="<@ofbizUrl>everyUserInfo?userId=${table.id}</@ofbizUrl>"> ${table.id}</a>
        </td>
        <td > ${table.realName?if_exists}</td>
        <td > ${uiLabelMap.svUserNot}</td>
		</#if>
	    <td class="button-col">
	           <a href="<@ofbizUrl>editUserInfo?userId=${table.id}</@ofbizUrl>" class="smallSubmit">${uiLabelMap.svUserEdit}</a>
	           <a href="<@ofbizUrl>changePwd?userId=${table.id}</@ofbizUrl>" class="smallSubmit">${uiLabelMap.svUserChangePwd}</a>
	           <a href="<@ofbizUrl>changepermission?userId=${table.id}</@ofbizUrl>" class="smallSubmit">${uiLabelMap.svUserChangePermission}</a>
	    </td>
        </tr>
  
    </#list>
 
</table>
     <hr>
<table cellspacing="0" > 
     <tr>	
	     <td>
	     <a href="<@ofbizUrl>createUser</@ofbizUrl>" class="smallSubmit">${uiLabelMap.svUserAddUser}</a>
	     </td>
     </tr>
</table>

