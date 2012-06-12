<#assign categoryid = "1">
<div class="mframe">
    <table border="0" align="center" width="100%" valign="top">
	<tr>
		<td valign="top">
		   <table border="0" width="100%">
		   <tr>
			<#if categoryInfo?has_content && categoryInfo?size gt 0>
			<#assign row = 0/>
			<#list categoryInfo?if_exists as data>
			    <#assign categoryid = data.id>
				<#if ((row + 1) == categoryInfo?size)>
				  <td align=left><span class="tt">
				  ${Static["com.siteview.web.util.Tools"].subContentStringOrialBytes(data.dispName?if_exists,20)}
				  </span></td>
			    <#if result?size gt 6>
				  <td align=right><a style="FONT-WEIGHT: normal; color:#FF6600;" href="${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"pageIndex","normal","mcategory",data.id,"category",data.id)}">more...</a>
				  </td>
			    </#if>
				</#if>
			    <#assign row = row + 1/>
			</#list>
			</#if>
			</tr>
		   </table>
		</td>
	</tr>
	<tr>
		<td valign="top">
<#if result?has_content && result?size gt 0>
<#assign row = 0/>
 		<#list result?if_exists as data>
 		<#if (row >= 6)>
 		<#break>
 		</#if>
		    <table border="0" width="100%">
			<tr>
				<td height="15">
					<img src="/content/control/ViewSimpleContent?dataResourceId=svbullet" align="absMiddle">
						${data.createDate?if_exists}
					<span ><a href="${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"pageIndex","detail","mcategory",categoryid,"category",categoryid,"id",data.id)}">
					   ${Static["com.siteview.web.util.Tools"].subContentStringOrialBytes(data.dispName?if_exists,24)} 
					</a></span>
				</td>
			</tr>
		    </table>
		<#assign row = row + 1/>
		</#list>
</#if>
         </td>
    </tr>
    </table>									
</div>
