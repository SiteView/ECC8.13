
<table id="navbar" width=100% align="center" cellpadding="0" cellspacing="0">
	<tr>
	<td vAlign="top" style="padding-top:5">
		<div class="mframe"><b>&gt;&gt;
		<#assign row = 0/>
		<#assign categoryInfoSize = categoryInfo?size/>
		<#assign mcategory = 0>
		<#list categoryInfo?if_exists as forumMessage>
		    <#if (row == 0)>
		    	<#assign mcategory = forumMessage.id>
		    </#if>
			<#if (row != 0)>
				&nbsp;¡ú&nbsp
			</#if>
            <a href='${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"pageIndex","normal","mcategory",mcategory,"category",forumMessage.id)}'>${forumMessage.dispName?if_exists}</a>
            <#assign row = row + 1/>
			<#if (row == categoryInfoSize)>
			<hr><img src='${forumMessage.dispImages?if_exists}'>
			</#if>
		</#list>
 	</td>
	</tr>
</table>

<#assign viewIndex = viewIndex?default(0)>
<#assign lowIndex = viewIndex?int * viewSize?int + 1>
<#assign highIndex = viewIndex?int * viewSize?int + viewSize>

<#--<br/>== viewIndex: ${viewIndex} ==viewSize: ${viewSize} ==lowIndex: ${lowIndex}== highIndex: ${highIndex} == ListSize: ${listSize}-->
<#if result?has_content && result?size gt viewSize>
    <#assign listSize = result?size/>
    <#if highIndex gt listSize><#assign highIndex = listSize></#if> 
    <div class="product-prevnext" align=right>
      <#assign r = listSize?double / viewSize?double />
      <#assign viewIndexMax = Static["java.lang.Math"].ceil(r?double)>
      <select name="pageSelect" class="selectBox" onchange="window.location=this[this.selectedIndex].value;">
        <option value="#">${uiLabelMap.CommonPage} ${viewIndex?int+1} ${uiLabelMap.CommonOf} ${viewIndexMax}</option>
        <#list 1..viewIndexMax as curViewNum>
          <option value="${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"VIEW_SIZE","" + viewSize,"VIEW_INDEX","" + (curViewNum?int-1))}">${uiLabelMap.CommonGotoPage} ${curViewNum}</option>
        </#list>
      </select>
      <b>
        <#if (viewIndex?int >0)>
          <a href="${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"VIEW_SIZE","" + viewSize,"VIEW_INDEX","" + (viewIndex?int-1))}" class="buttontext">${uiLabelMap.CommonPrevious}</a> |
        </#if>
        <#if (listSize?int > 0)>
          <span class="tabletext">${lowIndex} - ${highIndex} ${uiLabelMap.CommonOf} ${listSize}</span>
        </#if>
        <#if highIndex?int < listSize?int>
          | <a href="${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"VIEW_SIZE","" + viewSize,"VIEW_INDEX","" + (viewIndex?int+1))}" class="buttontext">${uiLabelMap.CommonNext}</a>
        </#if>
      </b>
   </div>
</#if>
<#assign row = 0/>
<#assign count = 0/>
<table width='100%' border='0' cellspacing='0' cellpadding='0'>
<#list result?if_exists as forumMessage>
    <tr>
    <#if ((viewIndex?int * viewSize?int) <= row) && (count < viewSize?int )>
    <td width='100%'>
     <span style="height:20;">
           <img src="/siteview/images/d_down.gif" align="middle" alt="*" />&nbsp;
			${forumMessage.createDate?if_exists}
          <a href="#bookmark${forumMessage.id?if_exists}"><span class=tt2>${forumMessage.dispName?if_exists}</span></a>
    </span>
    </td>
    <#assign count = count + 1/>
    <#else>
        <#if (count > 0)>
        <#break>
        </#if>
    </#if>
    <#assign row = row + 1/>
        
    </tr>
    
</#list>
</table>

<#assign row = 0/>
<#assign count = 0/>
<hr size=2>
<table id="_ctl0_DataList3" cellspacing="0" border="0" style="width:100%;border-collapse:collapse;">
<#list result?if_exists as forumMessage>
    <tr>
    <#if ((viewIndex?int * viewSize?int) <= row) && (count < viewSize?int )>
    <td style="width:100%;">
      <table width="100%" cellspacing="0" cellpadding="0" border="0">
        <tr>
          <td class="tl"></td>
          <td class="tm">
               <span>${forumMessage.createDate?if_exists} <A name="#bookmark${forumMessage.id?if_exists}">${forumMessage.dispName?if_exists}</A></span>
          </td>
          <td class="tr"></td>
        </tr>
      </table>
      <table width="100%" cellspacing="0" cellpadding="0" border="0" style="border:1px solid #cccccc;">
        <tr width="100%">
          <td>
            <table width="95%" border="0" align="center">
              <tr>
                <td>
                   <div class="lh">
                   <#if (forumMessage.dispTextData?has_content) >
                   <a href="${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"pageIndex","detail","id",forumMessage.id)}">${forumMessage.dispTitle?if_exists}</a>
                   <#else>
                   ${forumMessage.dispTitle?if_exists}
                   </#if>
                   </div>
                </td>
              </tr>
            </table>
          </td>
        </tr>
      </table>
      <table width="100%" cellspacing="0" cellpadding="0" border="0">
        <tr>
          <td class="bl"></td>
          <td class="bm">&nbsp;</td>
          <td class="br"></td>
        </tr>
      </table>
    </td>
    <#assign count = count + 1/>
    <#else>
        <#if (count > 0)>
        <#break>
        </#if>
    </#if>
    <#assign row = row + 1/>
        
    </tr>
 
</#list>
</table>