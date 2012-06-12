<#assign categoryid = "1">
<table width="100%"  border="0" cellspacing="0" cellpadding="0"  valign="top">
	<tr>
        <td class="blue" width=124 height=31>案 例 集 锦</td>
        <td width="191" class="dot">&nbsp;</td>		
	</tr>
	
    <tr>
         <td colspan="2">	   
	           <table width="100%"  border="0" cellspacing="0" cellpadding="0" bgcolor="#FFFFFF">
                  <tr>
					<td width="49%" valign="top">
	
						<table width="100%"  border="0" cellspacing="0" cellpadding="0" valign="top">
 							<tr>
								<td valign="top">
									<#if result?has_content && result?size gt 0>
									<#assign row = 0/>
 									<#list result?if_exists as data>
 									<#if (row >= 9)>
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
        					 	<td valign="top" width="51%">
        					 	<img src="/content/control/ViewSimpleContent?dataResourceId=svFly[1]zh"></td>
    						</tr>
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
				  							<td align=right><a style="FONT-WEIGHT: normal; color:#FF6600;" href="${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"pageIndex","normal","mcategory",data.id,"category",data.id)}">更多>>></a>
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
						</table>
					</td>
  				</tr>
			</table>
		</td>     
    </tr>
</table>

  
	