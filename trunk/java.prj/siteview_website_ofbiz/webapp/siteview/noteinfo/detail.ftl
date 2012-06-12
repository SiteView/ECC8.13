<table id="navbar" width=100% align="center" cellpadding="0" cellspacing="0">
	<tr>
	<td vAlign="top" style="padding-top:5">
		<div class="mframe"><b>&gt;&gt;
		<#assign row = 0/>
		<#assign categoryInfoSize = categoryInfo?size/>
		<#assign images = ""/>
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
			<#assign images = forumMessage.dispImages?if_exists/>
			</#if>
		</#list>
		&nbsp;¡ú&nbsp
        ${result.dispName?if_exists}
		<hr><img src='${images?if_exists}'>
 	</td>
	</tr>
</table>

<hr size=2>
<table id="_ctl0_DataList3" cellspacing="0" border="0" style="width:100%;border-collapse:collapse;">
    <tr>
    <td style="width:100%;">
      <table width="100%" cellspacing="0" cellpadding="0" border="0">
        <tr>
          <td class="tl"></td>
          <td class="tm">
          ${result.createDate?if_exists}
          <#if result.dispConame?has_content>
          	${result.dispConame?if_exists}
          <#else>
          	${result.dispName?if_exists}
          </#if>
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
		          <#if result.dispTextData?has_content>
		          	${result.dispTextData?if_exists}
		          <#else>
		          	${result.dispTitle?if_exists}
		          </#if>
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
    </tr>
</table>