<br>
<h1>���õ����� ${monuInfo?if_exists.name?if_exists} Ŀ¼�µľ�����Ϣ�����������±��жԼ�¼���в�����</h1>
</br>

<form id="form1" name="form1" method="post" action="">
  <table width="100%" border="2" cellspacing=0>
  	<tr>
  		<td>����</td>
  		<td>����</td>   		
   	</tr>

 	 <#list categoryInfo as result>
  		<#assign category=result?if_exists.category?if_exists>
  	
   		 <tr>
     		 <td>${result.name?if_exists}</td>
      		<td>
        	<a href="displayContentInfo?Id=${result?if_exists.id?if_exists}" >�鿴����</a>
    
      	 	<a href="delCategaryInfoPrompt?Id=${result?if_exists.id?if_exists}&category=${result?if_exists.category?if_exists}" >ɾ��</a>
      	
      		</td>
   		 </tr>
 	</#list>
  </table>
 	<br> 
 <br>
 	<h1> <a href="addRecord?myCategory=${parameters.category?if_exists}" >����Ҫ¼����ؼ�¼  
 	<font color='blue'>  ${parameters.category?if_exists}</h1></a></font>
	
</form>
