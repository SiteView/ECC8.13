 <table cellspacing="0" class="basic-table hover-bar">
    <tr class="header-row">
        <td>${uiLabelMap.machineHeadName}</td>
        <td>${uiLabelMap.machineHeadHost}</td>
        <td>${uiLabelMap.machineHeadState}</B></td>
        <td>${uiLabelMap.machineHeadMethod}</td>
        <td>${uiLabelMap.machineHeadEdit}</td>
        <td>${uiLabelMap.machineHeadTest}</B></td>
        <td>${uiLabelMap.machineHeadDel}</B></td>
        <td><B>&nbsp</B></td>
    </tr>
    <#list machineMap as machine>
    	<tr>
    		<td>${machine._name?if_exists}</td>
    		<td>${machine._host?if_exists}</td>
    		<td>${machine._status?if_exists}</td>
    		<td>${machine._method?if_exists}</td>
    		<td><a href="<@ofbizUrl>updateMachine?idx=${machine.idx}</@ofbizUrl>"> ${uiLabelMap.machineHeadEdit}</a></td>
    		<td>${machine._host?if_exists}</td>
    		<td><a href="<@ofbizUrl>updateMachine?idx=${machine.idx}</@ofbizUrl>"> ${uiLabelMap.machineHeadDel}</a></td>
    	</tr>
    </#list>
 </table>
      <hr>
<table cellspacing="0" > 
     <tr>	
	     <td>
	     <a href="<@ofbizUrl>addMachine</@ofbizUrl>" class="smallSubmit">${uiLabelMap.machineHeadAdd}</a>
	     </td>
     </tr>
</table>