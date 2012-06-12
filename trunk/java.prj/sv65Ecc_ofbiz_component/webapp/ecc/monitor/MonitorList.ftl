<table cellspacing="0" class="basic-table hover-bar">
    <tr class="header-row-2">
        <td><B>${Static["com.siteview.ecc.util.MonitorIniValueReader"].getCommonValue("_name","label")}</B></td>
        <td><B>${Static["com.siteview.ecc.util.MonitorIniValueReader"].getCommonValue("category","label")}</B></td>
        <td><B>${Static["com.siteview.ecc.util.MonitorIniValueReader"].getCommonValue("_class","label")}</B></td>
        <td><B>${Static["com.siteview.ecc.util.MonitorIniValueReader"].getCommonValue("_alertDisabled","label")}</B></td>
        <td><B>${Static["com.siteview.ecc.util.MonitorIniValueReader"].getCommonValue("_frequency","label")}</B></td>
        
        <td><B>${Static["com.siteview.ecc.util.MonitorIniValueReader"].getCommonValue("stateString","label")}</B></td>
        <td><B>${Static["com.siteview.ecc.util.MonitorIniValueReader"].getCommonValue("groupID","label")}</B></td>
        <td><B>&nbsp</B></td>
        <td><B>&nbsp</B></td>
        <td><B>&nbsp</B></td>
     </tr>   
<#if monitors?has_content>
    <#list monitors as monitor>
    <tr>
        <td>
            ${monitor._name?if_exists}&nbsp;
        </td>
        <td>
        <#if (monitor.category == "good") >
        	<image src="/svecc/images/status/okay.gif">
        <#elseif (monitor.category == "error")>
        	<image src="/svecc/images/status/error.gif">
        <#elseif (monitor.category == "nodata")>
        	<image src="/svecc/images/status/disabled.gif">
        </#if>
        </td>
        <td>${monitor._class?if_exists}</td>
        <td>${monitor._alertDisabled?if_exists}</td>
        <td>${monitor._frequency?if_exists}</td>
        <td>${monitor.stateString?if_exists}</td>
        <td>${monitor.groupID?if_exists}</td>
        
        <td class="button-col" width=50px>
            <a href="<@ofbizUrl>editMonitor?groupId=${groupId?if_exists}&id=${monitor._id}&className=com.dragonflow.StandardMonitor.PingMonitor</@ofbizUrl>" class="smallSubmit">Edit</a>&nbsp;
         </td>
        <td class="button-col" width=50px>
            <a href="<@ofbizUrl>deleteMonitor?id=${monitor._id}&groupId=${groupId?if_exists}</@ofbizUrl>" class="smallSubmit">Delete</a>&nbsp;
         </td>
        <td class="button-col" width=50px>
            <a href="javascript:reflash('${groupId?if_exists}','${monitor._id}');" class="smallSubmit">Test</a>&nbsp;
         </td>
     </tr>   
    </#list>
</#if>
</table>
