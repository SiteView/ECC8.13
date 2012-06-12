  <table cellspacing="0" class="basic-table hover-bar">
  
     <tr class="header-row">   
        <td>${uiLabelMap.svUserId}</td>
        <td>${result.id}</td>
     </tr>
     
    <tr >
        <td>${uiLabelMap.svUserLogin}</td>
        <td>${result.login?if_exists}</td>
     </tr>
    
     <tr>   
        <td>${uiLabelMap.svUserLdapserver}</td>
        <td>${result.ldapserver?if_exists}</td>
     </tr>   
     
     <tr>   
        <td>${uiLabelMap.svUserSecurityprincipal}</td>
        <td>${result.securityprincipal?if_exists}</td>
     </tr>
     
     <tr>   
        <td>${uiLabelMap.svUserRealName}</td>
        <td>${result.realName?if_exists}</td>
     </tr>
     
     <tr>    
        <td>${uiLabelMap.svUserGroup}</td>
		<td>${result.group?if_exists}</td>
     </tr>
     
     <tr>   
        <td>${uiLabelMap.svUserDisabled}</td>
        <td>
	        <#if result.disabled?has_content>
		     	<#if result.disabled == "Y">
		        ÊÇ
		        <#else>
		        ·ñ
		        </#if>
	        <#else>
	        ·ñ
	        </#if>
         </td>
     </tr>
     <tr>
     <td colspan=2>
     &nbsp
     </td>
     </tr>
	<tr >
	<td colspan=2>
	 <a href="<@ofbizUrl>userinfo?userId=${result.id}</@ofbizUrl>" class="smallSubmit">·µ»Ø</a>
	</td>
	</tr>
</table>



