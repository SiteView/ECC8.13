<table cellspacing="0" class="basic-table hover-bar">
	<tr >
		<#if parameters.userId?has_content >
			<td>
				 <a href="<@ofbizUrl>changePwd?userId=${parameters.userId}</@ofbizUrl>" class="smallSubmit">${uiLabelMap.CommonGoBack}</a>
			</td>
		<#else>
			<td>
			 <a href="<@ofbizUrl>userinfo</@ofbizUrl>" class="smallSubmit"> ${uiLabelMap.CommonGoBack}</a>
			</td>
		</#if>	

	</tr>
</table>
