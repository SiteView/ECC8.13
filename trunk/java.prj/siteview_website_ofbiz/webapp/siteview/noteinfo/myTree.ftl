<#assign pageIndex = "normal">

<#macro list item  spaces no>
      <table width="100%">
       	<tr>
         	<td>

        		${spaces}${no?if_exists}<font size=2>${item.dispName?if_exists}</font>
        	</td>
       	</tr>
      </table>
    
      <#assign category = item.id>
      <#assign items = Static["com.siteview.web.service.WebSiteService"].getCategory1LevelChildren(locale,delegator,category)>
	  <#list items?if_exists as data>
	 
		  <table width='100%'>
		  	<tr>
		  		<td valign=top>
		  		
		  			<@list item=data spaces=(spaces+"&nbsp;"+"&nbsp;") no=""/>
		  		</td>		  		  		
		  	</tr>
		  </table>		  	
      </#list>
</#macro>  


<#macro list1 item spaces no>      
    
      <#assign category = item.id>
      <#assign items = Static["com.siteview.web.service.WebSiteService"].getCategory1LevelChildren(locale,delegator,category)>
	 
	  <#list items?if_exists as data>
		 <#if data.id.length()!=3>
		 <table width='100%'>
		  	<tr>
		  		<td valign=top>
		  			<font size=2><a href="updateMenuInfo?id=${data.id}" class="smallSubmit">编辑${data.id}</a></font>
		  		</td>	  		
		  		<td valign=top>
		  			 <font size=2><a href="addInfo?id=${data.id}" class="smallSubmit">增加${data.id}</a></font>
		  		</td>
		  		 		
		  	</tr>
	 	   </table>	
	 	   <#else>
	 	   	<table width='100%'>
		  	<tr>
		  		<td valign=top>
		  			<font size=2><a href="updateMenuInfo?id=${data.id}" class="smallSubmit">编辑${data.id}</a></font>
		  		</td>	  		
		  		<td valign=top>
		  			 <font size=2><a href="displayInfo?category=${data.id} " class="smallSubmit">查看${data.id}</a></font>
  			
		  		</td>
		  		 		
		  	</tr>
	 	   </table>	
	 	   </#if>
		  <table width='100%'>
		  	<tr>
		  		<td valign=top>
		  		
		  			<@list1 item=data spaces=(spaces+"&nbsp;"+"&nbsp;") no=""/>
		  		</td>		  			
		  	</tr>
		  </table>			 
	  	</#list>
</#macro>  

<table cellspacing='0' cellpadding='0' border='0' align="center" width='100%' >
	  <#assign children = Static["com.siteview.web.service.WebSiteService"].getCategory1LevelChildren(locale,delegator,"")>
	  <#assign row = 1>
	  <#assign row1 = 1>
	  <tr>
	  
	  	<td><font size=5>所有目录：</font></td>
	  	<td><font size=5>操作：</font></td>
	  </tr>
	  <#list children?if_exists as data>
	   <tr>
	      <td valign=top width='50%'>
		  
		  	<@list item=data  spaces="&nbsp;"  no=("" + row + ":")/>
		  	<#assign row = row + 1>
	      </td>
	      <td valign=top width='50%'>
	      <font size=4><a href="addInfo?id=${data.id}" class="smallSubmit">增加${data.id}</a></font><br>
	<@list1 item=data  spaces="&nbsp;"  no=("" + row1 + ":")/>  
		  	<#assign row1 = row1 + 1>
		  	
	      </td>	      
        </tr>
      </#list>
</table>
