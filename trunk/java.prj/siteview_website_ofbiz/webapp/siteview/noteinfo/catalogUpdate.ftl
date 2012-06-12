
<h2>详细目录信息如下表：</h2>


<form action="saveCategoryInfo?${contentInfo.category}" method="post" >
  <table width="100%" border="1" valign="top" cellpadding="0" cellspacing="0">
    <tr>
      <td width="8%">属性</td>
      <td width="92%">值</td>
    </tr>
        
        
    <tr>
      <td>name</td>
      <td width="100%"><label>
        <input type="text" name="name" id="name"  value=${contentInfo.name} size="50"/>
      </label></td>
    </tr>
  
    <tr>
      <td>en_name</td>
      <td><label>
        <input type="text" name="en_name" id="en_name" value=${contentInfo.enName} size="50"/>
      </label></td>
    </tr>
    
    
    <tr>
      <td><input type="submit" name="submit" id="submit" value="提交" /></td>
      <td><a href="displayInfo?category=${contentInfo.category}" >返回</a>
    </tr> 
  </table>
</form>


