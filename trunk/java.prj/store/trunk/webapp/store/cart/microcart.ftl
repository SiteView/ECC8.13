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
<#assign shoppingCart = sessionAttributes.shoppingCart?if_exists>
<#if shoppingCart?has_content>
    <#assign shoppingCartSize = shoppingCart.size()>
<#else>
    <#assign shoppingCartSize = 0>
</#if>
<div id="microcart">
    <div>
        <#if (shoppingCartSize > 0)>
            ${uiLabelMap.EcommerceCartHas} <span id="microCartQuantity">${shoppingCart.getTotalQuantity()}</span>
            <#if shoppingCart.getTotalQuantity() == 1>${uiLabelMap.OrderItem}<#else/>${uiLabelMap.OrderItems}</#if>,
            <span id="microCartTotal"><@ofbizCurrency amount=shoppingCart.getGrandTotal() isoCode=shoppingCart.getCurrency()/></span>
        <#else>
            ${uiLabelMap.OrderShoppingCartEmpty}
        </#if>
        &nbsp;&nbsp;
    </div>
    <div>
      <a href="<@ofbizUrl>view/showcart</@ofbizUrl>">[${uiLabelMap.OrderViewCart}]</a>
      <#if (shoppingCartSize > 0)>
          <a href="<@ofbizUrl>quickcheckout</@ofbizUrl>">[${uiLabelMap.OrderCheckoutQuick}]</a>
      <#else>
          <span class="disabled">[${uiLabelMap.OrderCheckoutQuick}]</span>
      </#if>
      &nbsp;&nbsp;
    </div>
</div>
