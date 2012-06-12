<#assign pageIndex = "normal">

<#assign mmstyle = "color:#293d68;font-weight:bold;"/>
<#macro list item num spaces no>
      
        ${spaces}${no?if_exists}<a href='${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"pageIndex",pageIndex,"category",item.id,"VIEW_INDEX","","id","")}' target='_self'><span style='${mmstyle}'>${item.dispName?if_exists}</span></a>
      <br>
      <#assign category = item.id>
      <#assign items = Static["com.siteview.web.service.WebSiteService"].getCategory1LevelChildren(locale,delegator,category)>
	  <#list items?if_exists as data>
	  <table>
	  	<tr>
	  		<td>
	  			<@list item=data num= (num + 1) spaces = (spaces + "&nbsp;") no=""/>
	  		</td>
	  		<td>
	  			<a href="siteview/webapp/siteview/WEB-INF/controller/editInfo?id=${data.id}" class="smallSubmit">增加${data.id}</a>
	  		</td>	  		
	  		<td>
	  			 <a href="siteview/webapp/siteview/WEB-INF/controller/updateInfo?id=${data.id}" class="smallSubmit">更新${data.id}</a>
	  		</td>	  		
	  		<td>
	  			 <a href="siteview/webapp/siteview/WEB-INF/controller/delInfo?id=${data.id}" class="smallSubmit">删除${data.id}</a>
	  		</td>	  			  		
	  		
	  	</tr>
	  	</table>
      </#list>
</#macro>  
<div class="lframe">
<table cellspacing='0' cellpadding='0' border='0' align="center" width='100%' >
	  <#assign children = Static["com.siteview.web.service.WebSiteService"].getCategory1LevelChildren(locale,delegator,null)>
	  <#assign row = 1>
	  <#list children?if_exists as data>
	   <tr>
	      <td valign=top>
		  	<@list item=data num=3 spaces = "&nbsp;" no=("" + row + ":")/>
		  	<#assign row = row + 1>
	      </td>
	      <td>
	      	<a href="siteview/webapp/siteview/WEB-INF/controller/editInfo?id=${data.id}" class="smallSubmit">增加${data.id}</a>
	      </td>
	      <td>
	      	 
	      </td>
	      <td>
	      
	      </td>
	      
        </tr>
      </#list>

</table>
</div>