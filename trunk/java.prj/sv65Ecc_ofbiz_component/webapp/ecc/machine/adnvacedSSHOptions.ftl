  <tr>
   <td colspan="5"><H3>SSH Advanced Options</H3>
   </td>
  </tr>
  
  <tr>
   <td class="label">SSH Client</td>
   <td colspan="4"><select name="_sshClient" size="1">
   ${Static["com.dragonflow.Page.ntmachinePage"].getOptionsHTML(Static["com.dragonflow.SiteView.Machine"].getAllowedSshConnectionMethods(), data?if_exists._sshClient?if_exists)}
   </select>
   <span class="tooltip">Select the client to use to connect to the remote server.</span>
   </td>
  </tr>

  <tr>
   <td class="label">Port Number</td>
   <td colspan="4"><input type="text" name="_sshPort" size="2" value="${data?if_exists._sshPort?if_exists}"/>
   <span class="tooltip">Enter the port number that the ssh server is running on. <b> Default is 22. </b></span>
   </td>
  </tr>

  <tr>
   <td class="label">Disable Connection Caching</td>
   <td colspan="4"><input type="checkbox" name="_disableCache" <#if data?if_exists._disableCache?if_exists=="on">checked</#if>/>
   <span class="tooltip">Check this box to disable caching of SSH connections. </span>
   </td>
  </tr>
  <tr>
   <td class="label">Connection Limit</td>
   <td colspan="4"><input type=text name=_sshConnectionsLimit size=2 value="${data?if_exists._sshConnectionsLimit?if_exists}"/>
   <span class="tooltip">Enter the maximum number of open connections allowed for this remote.</span>
   </td>
  </tr>

  <tr>
   <td class="label">SSH Authentication Method</td>
   <td colspan="4"><select name="_sshAuthMethod" size="1">
   ${Static["com.dragonflow.Page.ntmachinePage"].getOptionsHTML(Static["com.dragonflow.SiteView.Machine"].getAllowedSshAuthMethods(), data?if_exists._sshAuthMethod?if_exists)}
   </select>
   <span class="tooltip">Select the client to use to connect to the remote server.</span>
   </td>
  </tr>
  <tr>
   <td class="label">Key File for SSH connections</td>
   <td colspan="4"><input type=text name=_keyFile size=50 value="${data?if_exists._keyFile?if_exists}"/>
   <span class="tooltip">Enter the path to the file containing the private key for this SSH connection. <b> Only valid if authentication method is "Key File".</span>
   </td>
  </tr>

  <tr>
   <td class="label">SSH Version 2 Only</td>
   <td colspan="4"><input type="checkbox" name="_version2" <#if data?if_exists._version2?if_exists=="on">checked</#if>/>
   <span class="tooltip">Check this box to force SSH to only use SSH protocol version 2. <b> ( This SSH option is only supported using the internal java libraries connection method) </b></span>
   </td>
  </tr>
  <tr>
   <td class="label">Custom Commandline</td>
   <td colspan="4"><input type=text name=_sshCommand size=50 value="${data?if_exists._sshCommand?if_exists}"/>
   <span class="tooltip">Enter the command for execution of external ssh client.  For substituion with above options use $host$, $user$ and $password$ respectivly. <b> This setting is for only for connections using an external process.</b></span>
   </td>
  </tr>