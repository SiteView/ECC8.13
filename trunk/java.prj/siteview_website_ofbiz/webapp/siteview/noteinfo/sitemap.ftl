<#assign pageIndex = "normal">

<#assign mmstyle = "color:#293d68;font-weight:bold;"/>
<#macro list item num spaces no>
      
        ${spaces}${no?if_exists}<a href='${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"pageIndex",pageIndex,"category",item.id,"VIEW_INDEX","","id","")}' target='_self'><span style='${mmstyle}'>${item.dispName?if_exists}</span></a>
      <br>
      <#assign category = item.id>
      <#assign items = Static["com.siteview.web.service.WebSiteService"].getCategory1LevelChildren(locale,delegator,category)>
	  <#list items?if_exists as data>
	  	<@list item=data num= (num + 1) spaces = (spaces + "&nbsp;") no=""/>
      </#list>
</#macro>  
<div class="lframe">
<table cellspacing='0' cellpadding='0' border='0' align="center" width='100%' >
  <tr>
	  <#assign children = Static["com.siteview.web.service.WebSiteService"].getCategory1LevelChildren(locale,delegator,null)>
	  <#assign row = 1>
	  <#list children?if_exists as data>
      <td valign=top>
	  	<@list item=data num=3 spaces = "&nbsp;" no=("" + row + ":")/>
	  	<#assign row = row + 1>
      </td>
      </#list>
  </tr>
</table>
</div>