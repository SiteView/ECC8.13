<table width='760' align='center' border='0' background="/content/control/ViewSimpleContent?dataResourceId=svlicensebg">
	<tr>
		<td><h3>Licenses</h3></td>
	</tr>
	<tr>
		<td><hr><h3>New Licenses</h3><hr></td>
	</tr>
	<tr>
		<td>In order to create a new license, please enter your activation key below and click on the "Create License" button.</td>
	</tr>
	<tr>
		<td align="center"><input type="text" name="license" size='60'><input type="submit" name="create" value="Create license"></td>
	</tr>
	<tr>
		<td>Please note that license upgrades (UPG keys) should be entered in the field at the bottom of license view pages.</td>
	</tr>
	<tr>
		<td><hr><h3>Current Licenses</h3><hr></td>
	</tr>
	<tr>
		<td>
			Click on a license name to enter the license view page.<br>
			<h3>Astaro Security Gateway Software for Home Use</h3><br>
			Astaro Security Gateway V7 is available as a fully functional home use version and is free of charge.
		</td>
	</tr>
	<tr>
		<td>
			<table>
				<tr>
					<td>
					</td>
				</tr>
			</table>
		</td>
	</tr>
	<tr>
		<td align="center">
		<#assign viewIndex = viewIndex?default(0)>
		<#assign lowIndex = viewIndex?int * viewSize?int + 1>
		<#assign highIndex = viewIndex?int * viewSize?int + viewSize>

		<#--<br/>== viewIndex: ${viewIndex} ==viewSize: ${viewSize} ==lowIndex: ${lowIndex}== highIndex: ${highIndex} == ListSize: ${listSize}-->
		<#if result?has_content && result?size gt viewSize>
    		<#assign listSize = result?size>
    		<#if highIndex gt listSize><#assign highIndex = listSize></#if> 
    		<div class="product-prevnext" align=right>
      		<#assign r = listSize?double / viewSize?double >
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
               |<a href="${Static["com.siteview.web.util.Tools"].getRequestUrl(request,"VIEW_SIZE","" + viewSize,"VIEW_INDEX","" + (viewIndex?int+1))}" class="buttontext">${uiLabelMap.CommonNext}</a>
        		</#if>
      		</b>
   		</div>
		</#if>
		</td>
	</tr>
</table>
