
<#assign mmv = "mmv"/>
<#assign mm = "mm"/>
<#assign pageIndex = request.getParameter("pageIndex")>
<#if (!pageIndex?has_content || pageIndex == "detail")>
<#assign pageIndex = "normal">
</#if>

<table width="100%"  border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td>
	 <table width="100%"  border="0" cellspacing="0" cellpadding="0" bgcolor="#FFFFFF">
 		 <tr>
    		<td width="16" valign="bottom">
    		<img src="/content/control/ViewSimpleContent?dataResourceId=svr2_r2_c2"></td>
    		<td width="63" class="xh">&nbsp;</td>
   			 <td width="102" height="25" class="green" align="center">解决方案</td>
     		<td width="69" class="xh">&nbsp;</td>
    		<td width="20" valign="bottom">
    		<img src="/content/control/ViewSimpleContent?dataResourceId=svr2_r2_c5"></td>
  		</tr>
  		<tr>
    		<td class="yl">&nbsp;</td>
    		<td colspan="3" class="content"> 
    		<#macro list item spaces>
     		 <table width='100%' cellspacing='0' cellpadding='0' border='0' align='center'>
       			 <tr>
           			<td height='20' style='padding-left:2px;padding-top:3px;' 
          				class='<#if requestParameters.category?if_exists == item.id>${mmv}<#else>${mm}</#if>'>
          				<img src="/content/control/ViewSimpleContent?dataResourceId=svbullet" align="absMiddle">
				      			
             			<a href='${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"pageIndex",pageIndex,"category",item.id,"VIEW_INDEX","","id","")}' target='_self'>
             			<span style='<#if requestParameters.category?if_exists == item.id><#else></#if>'>${item.dispName?if_exists}</span></a>
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


			<table cellspacing='0' cellpadding='0' border='0' align="center" width='140' >
  				<tr>
    				<td>
	 					<#if categoryInfo?has_content>
      					<table width='100%' cellspacing='0' cellpadding='0' border='0' align='center'>
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
	    </td>

    	<td class="yy">&nbsp;</td>
  	</tr>
  	<tr>
    		<td valign="top">
    		<img src="/content/control/ViewSimpleContent?dataResourceId=svr2_r5_c2"></td>
    		<td colspan="3" background="/content/control/ViewSimpleContent?dataResourceId=svr2_r5_c3">&nbsp;</td>
    		<td valign="top">
    		<img src="/content/control/ViewSimpleContent?dataResourceId=svr2_r5_c5"></td>
  	</tr>
</table>