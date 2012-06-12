<#assign id = requestParameters.id?if_exists>
<#if !id?has_content>
	<#assign id = requestAttributes.monitorid?if_exists>
</#if>

<script type="text/javascript">
    YAHOO.util.Event.on(window,'load',reflash ("${requestParameters.groupId?if_exists}","${id?if_exists}"));
</script>
<a href="<@ofbizUrl>listGroup?groupId=${requestParameters.groupId?if_exists}&id=${id?if_exists}</@ofbizUrl>">${uiLabelMap.sveccGotoGroupList}</a>