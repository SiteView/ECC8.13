
<div>
	<table cellspacing="0" class="basic-table hover-bar" border="1">
	    <tr class="header-row">
	        <td>${uiLabelMap.tbc_svAlertOn}</td>
	        <td>${uiLabelMap.tbc_svAlertGroup}</td>
	        <td>${uiLabelMap.tbc_svAlertFor}</td>
	        <td>${uiLabelMap.tbc_svAlertDo}</td>
	        <td>${uiLabelMap.tbc_svAlertHistory}</td>
	        <td>${uiLabelMap.tbc_svAlertEdit}</td>
	        <td>${uiLabelMap.tbc_svAlertTest}</td>
	        <td>${uiLabelMap.tbc_svAlertDelete}</td>
	     </tr>
	<#if alertslist?has_content>
	    <#list alertslist as hashmap>
	    <tr border="1">
	        <td>${hashmap.get("on")}</td>
	        <td>${hashmap.get("groupName")}</td>
	        <td>${hashmap.get("for")}</td>
	        <td>${hashmap.get("do")}</td>
	        <td width=50px>
				<a href="<@ofbizUrl>alertHistory?alertid=${hashmap.get("id")}</@ofbizUrl>" class="smallSubmit">${uiLabelMap.tbc_svAlertHistory}</a>
	        </td>
	        <td width=50px>
				<a href="<@ofbizUrl>alertDefine?alertid=${hashmap.get("id")}&define_flag=Update&category_alert=none&class_alert=none</@ofbizUrl>" class="smallSubmit">${uiLabelMap.tbc_svAlertEdit}</a>
	         </td>
	        <td class="button-col" width=50px>
	            <a href="<@ofbizUrl>alertTest?alertid='${hashmap.get("id")}'</@ofbizUrl>" class="smallSubmit">${uiLabelMap.tbc_svAlertTest}</a>
	         </td>
	        <td class="button-col" width=50px>
	            <a href="<@ofbizUrl>alertDelete?alertid=${hashmap.get("id")}</@ofbizUrl>" class="smallSubmit">${uiLabelMap.tbc_svAlertDelete}</a>
	         </td>
	     </tr>   
	    </#list>
	</#if>
	</table>
</div>