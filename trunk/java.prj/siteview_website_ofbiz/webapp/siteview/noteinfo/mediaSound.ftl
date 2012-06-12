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
   			 <td width="102" height="25" class="green" align="center">√ΩÃÂ…˘“Ù</td>
     		<td width="69" class="xh">&nbsp;</td>
    		<td width="20" valign="bottom">
    		<img src="/content/control/ViewSimpleContent?dataResourceId=svr2_r2_c5"></td>
  		</tr>
  		<tr>
    		<td class="yl">&nbsp;</td>
    		<td colspan="3" class="content"> 
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
				  			
			    			<#if result?size gt 6>
				  			<td align=right><a style="FONT-WEIGHT: normal; color:#FF6600;" href="${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"pageIndex","normal","mcategory",data.id,"category",data.id)}">∏¸∂‡>>></a>
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
  	 </td>
  </tr>
</table>