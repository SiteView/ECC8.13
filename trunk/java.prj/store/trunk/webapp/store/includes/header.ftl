<#--
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-->
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<#-- <!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"> <html> -->
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
    <title><#if title?has_content>${title}<#elseif titleProperty?has_content>${uiLabelMap.get(titleProperty)}</#if>: ${(productStore.storeName)?if_exists}</title>
    <#if layoutSettings.shortcutIcon?has_content>
      <link rel="shortcut icon" href="<@ofbizContentUrl>${layoutSettings.shortcutIcon}</@ofbizContentUrl>" />    
    </#if>
    <#if layoutSettings.javaScripts?has_content>
        <#--layoutSettings.javaScripts is a list of java scripts. -->
        <#list layoutSettings.javaScripts as javaScript>
            <script language="javascript" src="<@ofbizContentUrl>${javaScript}</@ofbizContentUrl>" type="text/javascript"></script>
        </#list>
    </#if>
    <#if layoutSettings.styleSheets?has_content>
        <#--layoutSettings.styleSheets is a list of style sheets. So, you can have a user-specified "main" style sheet, AND a component style sheet.-->
        <#list layoutSettings.styleSheets as styleSheet>
            <link rel="stylesheet" href="<@ofbizContentUrl>${styleSheet}</@ofbizContentUrl>" type="text/css"/>
        </#list>
    </#if>
    ${layoutSettings?if_exists.extraHead?if_exists}

    <#-- Append CSS for catalog -->
    <#if catalogStyleSheet?exists>
        <link rel="stylesheet" href="${catalogStyleSheet}" type="text/css"/>
    </#if>
    <#-- Append CSS for tracking codes -->
    <#if sessionAttributes.overrideCss?exists>
        <link rel="stylesheet" href="${sessionAttributes.overrideCss}" type="text/css"/>
    </#if>
    <#-- Meta tags if defined by the page action -->
    <#if metaDescription?exists>
        <meta name="description" content="${metaDescription}"/>
    </#if>
    <#if metaKeywords?exists>
        <meta name="keywords" content="${metaKeywords}"/>
    </#if>
    
    <#if requireDojo?exists>
        <script type="text/javascript">
          dojo.require("dojo.widget.*");    
        </script>   
    </#if>
</head>

<body>

<div id="ecom-header">
    <div id="left">
        <#if sessionAttributes.overrideLogo?exists>
            <img src="<@ofbizContentUrl>${sessionAttributes.overrideLogo}</@ofbizContentUrl>" alt="Logo"/>
        <#elseif catalogHeaderLogo?exists>
            <img src="<@ofbizContentUrl>${catalogHeaderLogo}</@ofbizContentUrl>" alt="Logo"/>
        <#elseif (productStore.headerLogo)?has_content>
            <img src="<@ofbizContentUrl>${productStore.headerLogo}</@ofbizContentUrl>" alt="Logo"/>
        </#if>
    </div>
    <#-- div id="right"<#if (productStore.headerRightBackground)?has_content> style="background-image: <@ofbizContentUrl>${productStore.headerRightBackground}</@ofbizContentUrl>;"</#if>>
        ${screens.render("component://store/widget/CartScreens.xml#microcart")}
    </div -->
    <div id="right">
            <p>
        <#if person?has_content>
          ${uiLabelMap.CommonWelcome} ${person.firstName?if_exists} ${person.lastName?if_exists} [${userLogin.userLoginId}]
        <#elseif partyGroup?has_content>
          ${uiLabelMap.CommonWelcome} ${partyGroup.groupName?if_exists} [${userLogin.userLoginId}]
        <#else>
          ${uiLabelMap.CommonWelcome}!
        </#if>
        </p>
        <p>${nowTimestamp?datetime?string.short}</p>
        </div>   
</div>

<div id="ecom-header-bar">
    <ul id="left-links">
		<li class="selected" id="header-bar-main"><a href="<@ofbizUrl>main</@ofbizUrl>">${uiLabelMap.PageTitleMain}</a></li>
        <li id="header-bar-solutions"><a href="<@ofbizUrl>solutions</@ofbizUrl>">${uiLabelMap.StoreSolutions}</a></li>
        <li id="header-bar-sales"><a href="<@ofbizUrl>sales</@ofbizUrl>">${uiLabelMap.StoreSales}</a></li>
        <li id="header-bar-products"><a href="<@ofbizUrl>products</@ofbizUrl>">${uiLabelMap.StoreProducts}</a></li>
        <li id="header-bar-downloads"><a href="<@ofbizUrl>downloads</@ofbizUrl>">${uiLabelMap.StoreDownloads}</a></li>
        <li id="header-bar-customers"><a href="<@ofbizUrl>customers</@ofbizUrl>">${uiLabelMap.StoreCustomers}</a></li>
        <li id="header-bar-supports"><a href="<@ofbizUrl>supports</@ofbizUrl>">${uiLabelMap.StoreSupports}</a></li>
        <li id="header-bar-news"><a href="<@ofbizUrl>news</@ofbizUrl>">${uiLabelMap.StoreNews}</a></li>
        <li id="header-bar-company"><a href="<@ofbizUrl>Company</@ofbizUrl>">${uiLabelMap.StoreCompany}</a></li>
    </ul>
    <ul id="right-links">
        <#if userLogin?has_content && userLogin.userLoginId != "anonymous">
            <li id="header-bar-logout"><a href="<@ofbizUrl>logout</@ofbizUrl>">${uiLabelMap.CommonLogout}</a></li>
        <#else/>
            <li id="header-bar-login"><a href="<@ofbizUrl>${checkLoginUrl}</@ofbizUrl>">${uiLabelMap.CommonLogin}</a></li>
        </#if>
        <li id="header-bar-contactus"><a href="<@ofbizUrl>contactus</@ofbizUrl>">${uiLabelMap.CommonContactUs}</a></li>

    </ul>
</div>
