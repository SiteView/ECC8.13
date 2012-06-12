<#assign viewIndex = viewIndex?default(0)>
<#assign lowIndex = viewIndex?int * viewSize?int + 1>
<#assign highIndex = viewIndex?int * viewSize?int + viewSize>
<#--<br/>== viewIndex: ${viewIndex} ==viewSize: ${viewSize} ==lowIndex: ${lowIndex}== highIndex: ${highIndex} == ListSize: ${listSize}-->
<#if result?has_content && result?size gt 0>
    <#assign listSize = result?size/>
    <#if highIndex gt listSize><#assign highIndex = listSize></#if> 
    <div class="product-prevnext">
      <#assign r = listSize?double / viewSize?double />
      <#assign viewIndexMax = Static["java.lang.Math"].ceil(r?double)>
      <select name="pageSelect" class="selectBox" onchange="window.location=this[this.selectedIndex].value;">
        <option value="#">${uiLabelMap.CommonPage} ${viewIndex?int+1} ${uiLabelMap.CommonOf} ${viewIndexMax}</option>
        <#list 1..viewIndexMax as curViewNum>
          <option value="<@ofbizUrl>${url}?VIEW_SIZE=${viewSize}&VIEW_INDEX=${curViewNum?int-1}</@ofbizUrl>">${uiLabelMap.CommonGotoPage} ${curViewNum}</option>
        </#list>
      </select>
      <b>
        <#if (viewIndex?int >0)>
          <a href="<@ofbizUrl>${url}?VIEW_SIZE=${viewSize}&VIEW_INDEX=${viewIndex?int-1}</@ofbizUrl>" class="buttontext">${uiLabelMap.CommonPrevious}</a> |
        </#if>
        <#if (listSize?int > 0)>
          <span class="tabletext">${lowIndex} - ${highIndex} ${uiLabelMap.CommonOf} ${listSize}</span>
        </#if>
        <#if highIndex?int < listSize?int>
          | <a href="<@ofbizUrl>${url}?VIEW_SIZE=${viewSize}&VIEW_INDEX=${viewIndex?int+1}</@ofbizUrl>" class="buttontext">${uiLabelMap.CommonNext}</a>
        </#if>
      </b>
   </div>
</#if>
<#assign row = 0/>
<#assign count = 0/>
<#list result?if_exists as forumMessage>
	<#if ((viewIndex?int * viewSize?int) <= row) && (count < viewSize?int )>
 	<div class="tableheadtext">
          <a href="<@ofbizUrl>showDetail?id=${forumMessage.id?if_exists}</@ofbizUrl>" class="buttontext">${forumMessage.name?if_exists}</a> |
		
	</div>
    <hr/>
    <#assign count = count + 1/>
    <#else>
    <#break>
    </#if>
    <#assign row = row + 1/>
</#list>
