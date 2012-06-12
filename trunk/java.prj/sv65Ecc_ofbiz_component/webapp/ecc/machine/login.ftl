  <tr>
   <td class="label">Login</td>
   <td colspan="4"><input type="text" name="_login" size="50" value="${data?if_exists._login?if_exists}"/>
   <span class="tooltip">Enter the login for the remote server. <br>For a domain login, include the domain name before the user login (example: <i>domainname\user</i>). <br>For a local or standalone login, include the machine name before the user login  (example: <i>machinename\user</i>).</span>
   </td>
  </tr>

  <tr>
   <td class="label">Password</td>
   <td colspan="4"><input type="password" name="_password" size="50" value="${data?if_exists._password?if_exists}"/>
   <span class="tooltip">The password for the remote server or the passphrase for the SSH key file.</span>
   </td>
  </tr>
  <tr>
   <td class="label">Title</td>
   <td colspan="4"><input type="text" name="_name" size="50" value="${data?if_exists._name?if_exists}"/>
   <span class="tooltip">Optional title describing the remote server. The default title is the server address</span>
   </td>
  </tr>
