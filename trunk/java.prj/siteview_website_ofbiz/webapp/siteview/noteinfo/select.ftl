<div class="lframe">
<#assign mmv = "mmv"/>
<#assign mm = "mm"/>
<#assign mmvstyle = "color:#ff9900;font-weight:bold;"/>
<#assign mmstyle = "color:#293d68;font-weight:bold;"/>
<#assign pageIndex = request.getParameter("pageIndex")>
<#if (!pageIndex?has_content || pageIndex == "detail")>
<#assign pageIndex = "normal">
</#if>

<#macro list item spaces>
      <table width='100%' cellspacing='0' cellpadding='0' border='0' align='center'>
        <tr>
           <td height='20' style='padding-left:2px;padding-top:3px;' class='<#if requestParameters.category?if_exists == item.id>${mmv}<#else>${mm}</#if>'>
           		&nbsp;${spaces?if_exists}
             <a href='${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"pageIndex",pageIndex,"category",item.id,"VIEW_INDEX","","id","")}' target='_self'>
             <span style='<#if requestParameters.category?if_exists == item.id>${mmvstyle}<#else>${mmstyle}</#if>'>${item.dispName?if_exists}</span></a>
           </td>
        </tr>
        <tr>
          <td height='1'></td>
        </tr>
      </table>
      <#assign category = item.id>
      <#assign items = Static["com.siteview.web.service.WebSiteService"].getCategory1LevelChildren(locale,delegator,category)>
	  <#list items?if_exists as data>
	  	<@list item=data spaces= (spaces + "&nbsp;")/>
      </#list>
</#macro>  

<table width='140' cellspacing='0' cellpadding='0' border='0' align="center">
  <tr>
    <td height='23'>
      <img src='/content/control/ViewSimpleContent?dataResourceId=svdaleimutop2'/>
    </td>
  </tr>
</table>


<table cellspacing='0' cellpadding='0' border='0' align="center" width='140' >
  <tr>
    <td>
	 <#if categoryInfo?has_content>
      <table width='100%' cellspacing='0' cellpadding='0' border='0' align='center'>
        <tr>
          <td height='20' style='padding-left:2px;padding-top:3px;' class='mmv'>&nbsp;
           <a href='${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"pageIndex",pageIndex,"category",categoryInfo.id,"VIEW_INDEX","","id","")}' target='_self'> <span style='color:#ff9900;font-weight:bold;'>${categoryInfo.dispName?if_exists}</span></a>
          </td>
        </tr>
        <tr>
          <td height='1'></td>
        </tr>
      </table>
      </#if>

	  <#list children?if_exists as data>
	  	<@list item=data spaces="&nbsp;"/>
      </#list>
    </td>
  </tr>
</table>
<table width='140' cellspacing='0' cellpadding='0' border='0' align='center'>
  <tr>
    <td height='22'>
      <img src='/content/control/ViewSimpleContent?dataResourceId=sv2-pro2-function'/>
    </td>
  </tr>
</table>

</div>