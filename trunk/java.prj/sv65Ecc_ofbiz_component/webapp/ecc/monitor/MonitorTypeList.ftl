<#if types?has_content>

<table cellspacing="0" class="basic-table hover-bar">
    <#list types as type>
    <tr>
        <td>${type.className?if_exists}</td>
        <td>${type.title?if_exists}</td>
        <td>${type.description?if_exists}</td>
        <td class="button-col align-float">
            <a href="<@ofbizUrl>createMonitor?className=${type.className?if_exists}&groupId=${groupId?if_exists}</@ofbizUrl>" class="smallSubmit">Create</a>&nbsp;
         </td>
     </tr>   
    </#list>
    
</table>
</#if>
