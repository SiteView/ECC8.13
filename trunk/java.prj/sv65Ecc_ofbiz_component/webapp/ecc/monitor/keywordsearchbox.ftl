<form name="keywordsearchform" method="post" action="<@ofbizUrl>listMonitorType</@ofbizUrl>" style="margin: 0;">
	<input type="hidden" name="groupId" value="${requestParameters.groupId?if_exists}">
  <span class="label">${uiLabelMap.Keywords}:</span><input type="text"name="SEARCH_STRING" size="20" maxlength="50" value="${requestParameters.SEARCH_STRING?if_exists}"/>
  <span class="label">
    ${uiLabelMap.CommonNoContains}
  </span>
  <input type="checkbox" name="SEARCH_CONTAINS" value="N" <#if requestParameters.SEARCH_CONTAINS?if_exists == "N">checked="checked"</#if>/>
  &nbsp;
  <a href="javascript:document.keywordsearchform.submit()" class="buttontext">${uiLabelMap.CommonFind}</a>
</form>
