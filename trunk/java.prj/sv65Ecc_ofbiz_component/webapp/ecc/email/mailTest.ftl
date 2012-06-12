
<form id="form1" name="form1" method="post" action="<@ofbizUrl>testSendMail</@ofbizUrl>">

   <table cellspacing="4"> 
	      <tr class="header-row">	      
			 <td colspan="3"><div align="center"><h1>E-mail Test</h1></div></td>	
	      </tr>  
	       
   <tr>
	   <td>
	   Send a test message using e-mail. 
	   </td>
   </tr>   
   <tr>
	   <td>
	   Enter the e-mail address where the message will be sent. For example, support@mercury.com. Separate multiple addresses using commas.
	   </td>
   </tr>
   <tr>
	   <td>
	   E-mail Address:<input type="text" name="emailAddress"  size="50"/>
	   </td>
   </tr>
   <tr>
	   <td>
	   Mail Server: ${result.mailServer} <input type="hidden" name="Mailerver"  value="${result.mailServer}" size="50"/>
	   </td>
   </tr>
   <tr>
	   <td>
	   Backup Mail Server:${result.mailServerBackup}<input type="hidden" name="BackupMailServer"  value="${result.mailServerBackup}" size="50"/>
	   </td>
   </tr>
    <tr>
	   <td>
	     <input type="submit" name=""  value="${uiLabelMap._sendEmail}" /> <span class="tooltip">a test e-mail message.</span> 
	   </td>
   </tr>
  </table> 
  <p><center>
    <label>
   <A HREF="<@ofbizUrl>emailPreference</@ofbizUrl>">${uiLabelMap.returnemailPreference}</A>
    </label>
    </center>
  </p>
</form>