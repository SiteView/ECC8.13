
<h2>��ϸĿ¼��Ϣ���±�</h2>


<form action="saveCategoryInfo?${contentInfo.category}" method="post" >
  <table width="100%" border="1" valign="top" cellpadding="0" cellspacing="0">
    <tr>
      <td width="8%">����</td>
      <td width="92%">ֵ</td>
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
      <td><input type="submit" name="submit" id="submit" value="�ύ" /></td>
      <td><a href="displayInfo?category=${contentInfo.category}" >����</a>
    </tr> 
  </table>
</form>


