
<#-- Main Heading -->
<table width="100%" cellpadding="0" cellspacing="0" border="0">
  <tr>
    <td align="left">
      <h1>
      </h1>
    </td>
    <td align="right">
      <#if showOld>
        <a href="<@ofbizUrl>employeelist?companyId=${parameters.companyId?if_exists}</@ofbizUrl>" class="buttontext">${uiLabelMap.PartyHideOld}</a>&nbsp;&nbsp;
      <#else>
        <a href="<@ofbizUrl>employeelist?SHOW_OLD=true&companyId=${parameters.companyId?if_exists}</@ofbizUrl>" class="buttontext">${uiLabelMap.PartyShowOld}</a>&nbsp;&nbsp;
      </#if>
      <#if (productStore.enableDigProdUpload)?if_exists == "Y">
      &nbsp;<a href="<@ofbizUrl>digitalproductlist</@ofbizUrl>" class="buttontext">${uiLabelMap.CommonDigitalProductUpload}</a>
      </#if>
    </td>
  </tr>
</table>
<br/>

<!--add by dingbing.xu start--->
<div class="screenlet">
    <div class="screenlet-header">
        <div class="boxlink">
            <a href="<@ofbizUrl>editemployee?companyId=${parameters.companyId?if_exists}</@ofbizUrl>" class="submenutextright">${uiLabelMap.CommonCreateNew}</a>
        </div>
        <div class="boxhead">${company.groupName?if_exists}&nbsp;-&nbsp;${uiLabelMap.EmployeeList}</div>
    </div>
    <div class="screenlet-body">
  <#if employeelist?has_content>
    <table width="100%" border="0" cellpadding="0">
      <tr align="left" valign="bottom">
        <th class="tableheadtext">${uiLabelMap.EmployeeID}</th>
        <th class="tableheadtext" width="5">&nbsp;</th>
        <th class="tableheadtext">${uiLabelMap.EmployeeName}</th>
        <th class="tableheadtext">&nbsp;</th>
        
      </tr>

      <#list employeelist as employee>
          <tr><td colspan="7"><hr class="sepbar"/></td></tr>
          <tr>
            <td align="right" valign="top" width="10%">
              <div class="tabletext">${employee.get("partyId",locale)}&nbsp;<b></b></div>
            </td>
            <td width="5">&nbsp;</td>
            <td >
            <#if employee_relation_list[employee_index]?exists>  
            <#if employee_relation_list[employee_index] = "EX_EMPLOYMENT" >
            <a href="<@ofbizUrl>editemployee?SHOW_OLD=${parameters.SHOW_OLD?if_exists}&employeeId=${employee.get("partyId",locale)}&companyId=${parameters.companyId}</@ofbizUrl>" style="text-decoration: line-through">${employee.get("firstName",locale)}&nbsp;${employee.get("lastName",locale)}</a>&nbsp;
            <b>${uiLabelMap.CommonCancellation}</b>
            <#else>
            <a href="<@ofbizUrl>editemployee?SHOW_OLD=${parameters.SHOW_OLD?if_exists}&employeeId=${employee.get("partyId",locale)}&companyId=${parameters.companyId}</@ofbizUrl>" >${employee.get("firstName",locale)}&nbsp;${employee.get("lastName",locale)}</a>&nbsp;
            </#if>
            </#if>
           
            </td>
            <td width="5">&nbsp;</td>
            <td align=right>
            <div>
            <#if employee_relation_list[employee_index]?exists>  
            <#if employee_relation_list[employee_index] = "EMPLOYMENT" >
            <a href="<@ofbizUrl>removeEmployee?SHOW_OLD=${parameters.SHOW_OLD?if_exists}&employeeId=${employee.get("partyId",locale)}&companyId=${parameters.companyId}</@ofbizUrl>" class="buttontext">
              ${uiLabelMap.CommonNoUse}</a>&nbsp;&nbsp;
            <#else>
            <a href="<@ofbizUrl>reUseEmployee?SHOW_OLD=${parameters.SHOW_OLD?if_exists}&employeeId=${employee.get("partyId",locale)}&companyId=${parameters.companyId}</@ofbizUrl>" class="buttontext">
              ${uiLabelMap.CommonReUse}</a>&nbsp;&nbsp;
            </#if>
            </#if>
            </div>
              
          </tr>
      </#list>

    </table>
  <#else>
    <p>${uiLabelMap.noEmployeeInformation}.</p><br/>
  </#if>
    </div>
</div>
<!--add by dingbing.xu end--->