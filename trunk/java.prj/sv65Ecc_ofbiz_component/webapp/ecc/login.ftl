<#if requestAttributes.uiLabelMap?exists><#assign uiLabelMap = requestAttributes.uiLabelMap></#if>

<#assign previousParams = sessionAttributes._PREVIOUS_PARAMS_?if_exists>
<#if previousParams?has_content>
  <#assign previousParams = "?" + previousParams>
</#if>

<#assign username = requestParameters.USERNAME?default((sessionAttributes.autoUserLogin.userLoginId)?default(""))>
<#if username != "">
  <#assign focusName = false>
<#else>
  <#assign focusName = true>
</#if>
<center>
  <div class="screenlet login-screenlet">
    <div class="screenlet-title-bar">
      <h3>${uiLabelMap.CommonRegistered}</h3>
    </div>
    <div class="screenlet-body">
      <form method="post" action="<@ofbizUrl>login${previousParams?if_exists}</@ofbizUrl>" name="loginform">
        <table class="basic-table" cellspacing="0">
          <tr>
            <td class="label">${uiLabelMap.CommonUsername}</td>
            <td><input type="text" name="USERNAME" value="${username}" size="20"/></td>
          </tr>
          <tr>
            <td class="label">${uiLabelMap.CommonPassword}</td>
            <td><input type="password" name="PASSWORD" value="" size="20"/></td>
          </tr>
          <tr>
            <td colspan="2" align="center">
              <input type="submit" value="${uiLabelMap.CommonLogin}"/>
            </td>
          </tr>
        </table>
        <input type="hidden" name="JavaScriptEnabled" value="N"/>
      </form>
    </div>
  </div>
</center>

<script language="JavaScript" type="text/javascript">
  document.loginform.JavaScriptEnabled.value = "Y";
  <#if focusName>
    document.loginform.USERNAME.focus();
  <#else>
    document.loginform.PASSWORD.focus();
  </#if>
</script>
