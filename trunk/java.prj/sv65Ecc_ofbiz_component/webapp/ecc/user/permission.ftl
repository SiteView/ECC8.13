
<form id="form1" name="form1" method="post" action="<@ofbizUrl>savePermission?id=${requestParameters.userId}</@ofbizUrl>">
<div id="_G19_"> 
   <table cellspacing="4"> 
      <tr class="header-row">
        <td class="label"><div align="right">Permission Operation:</div></td>
        <td></td>		
        <td></td>
     </tr>   
    <tr class="header-row">
        <td ><div align="right"><strong>个人ID：</strong></div></td>
        <td >${requestParameters.userId}</td>		
        <td></td>
     </tr>   
	   <#list result as table>  
		   <tr>
			<#if table.label?has_content>	
				 <td class="label"><div align="right">${table.label}&nbsp &nbsp</div></td>
			<#else>	
				<td></td> 
			</#if>	
			
			<#if table.attrValue?has_content&&table.attrValue==true>	
				 <td> <input type="checkbox" name="${table.attrName}" value="Y" checked="checked" /></td>
			<#else>
				<td> <input type="checkbox" name="${table.attrName}" value="Y"  /></td>
			</#if>
				 
			<#if table.description?has_content>	
				 <td ><div align="left"><span class="tooltip">${table.description}</span></div></td>
			<#else>	
				<td></td> 
			</#if>				 
				 
		   </tr>
	   </#list> 
   </table>
</div> 
    <input type="submit"  id="" value="提交" />
  <div align="center"><a  href="<@ofbizUrl>userinfo</@ofbizUrl>">${uiLabelMap.CommonGoBack}</a></div>
</form>