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

<#-- Render the category page -->
<!-- Wan.Luo 2008.5.7 -->
<#if requestAttributes.productCategoryId?has_content>
  ${screens.render("component://ecc/widget/CommonScreen.xml#menuItem_main")}
<#else>
  <center><h2>${uiLabelMap.eccNoPROMOTIONCategory}</h2></center>
</#if>

<!-- <h1> testsdf <\h1> -->