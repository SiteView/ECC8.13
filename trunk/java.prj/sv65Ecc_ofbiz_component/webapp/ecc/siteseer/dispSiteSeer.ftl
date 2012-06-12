<#assign NO_CHANGED_PASSWORD = Static["com.siteview.svecc.service.SiteSeer"].NO_CHANGED_PASSWORD>

<form method="post"  action="saveSiteSeer"  class="basic-form" onSubmit="javascript:submitFormDisableSubmits(this)">

<div id="_G41_"> <table cellspacing="0" class="basic-table">
  <tr>
   <td class="label">SiteSeer Account</td>
   <td colspan="4"><input type="text" name="_siteseerAccount" size="60" value="${data._siteseerAccount?if_exists}"/>
   <span class="tooltip">
	Enter a SiteView display title for your SiteSeer account 
	</span>
   </td>
  </tr>
  <tr>
   <td class="label">SiteSeer Username</td>
   <td colspan="4"><input type="text" name="_siteseerUsername" size="60" value="${data._siteseerUsername?if_exists}"/>
   <span class="tooltip">
	Enter the username required to login to your SiteSeer account
	</span>
   </td>
  </tr>
  <tr>
   <td class="label">SiteSeer Password</td>
   <td colspan="4"><input type="password" name="_siteseerPassword" size="60" value="${NO_CHANGED_PASSWORD}"/>
   <span class="tooltip">
	Enter the password used to login to your SiteSeer account
	</span>
   </td>
  </tr>
  <tr>
   <td class="label">SiteSeer Host</td>
   <td colspan="4"><input type="text" name="_siteseerHost" size="60" value="${data._siteseerHost?if_exists}"/>
   <span class="tooltip">
	Enter the host name for the SiteSeer service.  For example, <tt>siteseer3.dragonflow.com</tt> or <tt>siteseer.dragonflow.com</tt>
	</span>
   </td>
  </tr>

  <tr>
   <td class="label">&nbsp;</td>
   <td><input type="submit" class="buttontext" name="submitButton" value="${uiLabelMap.CommonSave}"/></td>
   <td class="label"></td>
   <td><a class="buttontext" href="main">${uiLabelMap.CommonCancel}</a></td>
  </tr>

  <tr>
   <td class="label">Disabled</td>
   <td colspan="4"><input type="checkbox" name="_siteseerDisabled" value="CHECKED" ${data._siteseerDisabled?if_exists}/>
   <span class="tooltip">Check this box to hide the SiteSeer group on the main SiteView panel</span>
   </td>
  </tr>
   

  <tr>
   <td class="label">SiteSeer Title</td>
   <td colspan="4"><input type="text" name="_siteseerTitle" size="60" value="${data._siteseerTitle?if_exists}"/>
   <span class="tooltip">
	Enter a SiteView display title for your SiteSeer account
	</span>
   </td>
  </tr>
  <tr>
   <td class="label">SiteSeer Proxy</td>
   <td colspan="4"><input type="text" name="_siteseerProxy" size="60" value="${data._siteseerProxy?if_exists}"/>
   <span class="tooltip">
	Enter proxy server name or address if use of a proxy is required to access your SiteSeer account
	</span>
   </td>
  </tr>
  <tr>
   <td class="label">SiteSeer Proxy Username</td>
   <td colspan="4"><input type="text" name="_siteseerProxyUsername" size="60" value="${data._siteseerProxyUsername?if_exists}"/>
   <span class="tooltip">
	Enter the proxy user name if required to access your SiteSeer account
	</span>
   </td>
  </tr>
  <tr>
   <td class="label">SiteSeer Proxy Password</td>
   <td colspan="4"><input type="password" name="_siteseerProxyPassword" size="60" value="${NO_CHANGED_PASSWORD}"/>
   <span class="tooltip">
	Enter the proxy password if required to access your SiteSeer account
	</span>
   </td>
  </tr>

  <tr>
   <td class="label">Hide SiteSeer Group</td>
   <td colspan="4"><input type="checkbox" name="_siteseerHidden" value="CHECKED" ${data._siteseerHidden?if_exists}/>
   <span class="tooltip">Check this box to hide the SiteSeer group on the main SiteView panel</span>
   </td>
  </tr>
  <tr>
   <td class="label">Automatic SiteSeer Login</td>
   <td colspan="4"><input type="checkbox" name="_siteseerLoginInURL" value="CHECKED" ${data._siteseerLoginInURL?if_exists}/>
   <span class="tooltip">Check this box to allow automatic login to SiteSeer by embedding the SiteSeer login and password in the URL</span>
   </td>
  </tr>

  <tr>
   <td class="label">SiteSeer Read Only Username</td>
   <td colspan="4"><input type="text" name="_siteseerReadOnlyUsername" size="60" value="${data._siteseerReadOnlyUsername?if_exists}"/>
   <span class="tooltip">
	Enter the user name used to login <B>read only</B> to your SiteSeer account - this is used for Automatic SiteSeer Login when logged into SiteView as the "user" user.
	</span>
   </td>
  </tr>
  <tr>
   <td class="label">SiteSeer Read Only Password</td>
   <td colspan="4"><input type="password" name="_siteseerReadOnlyPassword" size="60" value="${NO_CHANGED_PASSWORD}"/>
   <span class="tooltip">
	Enter the password used to login <B>read only</B> to your SiteSeer account
	</span>
   </td>
  </tr>
 </table>
</div>


</form>
