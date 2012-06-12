<br>
<h1>您得到的是 ${monuInfo?if_exists.name?if_exists} 目录下的具体信息，您可以在下表中对记录进行操作。</h1>
</br>

<form id="form1" name="form1" method="post" action="">
  <table width="100%" border="2" cellspacing=0>
  	<tr>
  		<td>标题</td>
  		<td>操作</td>   		
   	</tr>

 	 <#list categoryInfo as result>
  		<#assign category=result?if_exists.category?if_exists>
  	
   		 <tr>
     		 <td>${result.name?if_exists}</td>
      		<td>
        	<a href="displayContentInfo?Id=${result?if_exists.id?if_exists}" >查看内容</a>
    
      	 	<a href="delCategaryInfoPrompt?Id=${result?if_exists.id?if_exists}&category=${result?if_exists.category?if_exists}" >删除</a>
      	
      		</td>
   		 </tr>
 	</#list>
  </table>
 	<br> 
 <br>
 	<h1> <a href="addRecord?myCategory=${parameters.category?if_exists}" >我想要录入相关记录  
 	<font color='blue'>  ${parameters.category?if_exists}</h1></a></font>
	
</form>
