
<h2>添加记录信息如下表：</h2>

<hr>
<form action="saveAddedRecord?${parameters.myCategory}" method="post" >
  <table width="100%" border="1" valign="top" cellpadding="0" cellspacing="0">
    <tr>
      <td width="8%">属性</td>
      <td width="92%">值</td>
    </tr>

    <tr>
      <td>country</td>
      <td><input type="text" name="country" id="country"    size="50" value="CN"/></td>
    </tr>
    <tr>
      <td>category</td>
      <td><label><input type="text" name="category" id="category"  value=${parameters.myCategory}  size="50" readonly="true"/></label></td>
    </tr>
    <tr>
      <td>title</td>
      <td><label>
        <textarea name="title" id="title" rows="5" cols="50"></textarea>
      </label></td>
    </tr>
    <tr>
      <td>name</td>
      <td width="100%"><label>
        <input type="text" name="name" id="name"   size="50"/>
      </label></td>
    </tr>
    <tr>
      <td>coname</td>
      <td><label>
        <input type="text" name="coname" id="coname"  size="50"/>
      </label></td>
    </tr>
    <tr>
      <td>text_date</td>
      <td><label>
        <textarea name="text_date" id="text_date" rows="5" cols="50"></textarea>
      </label></td>
    </tr>
    <tr>
      <td>en_name</td>
      <td><label>
        <input type="text" name="en_name" id="en_name"  size="50"/>
      </label></td>
    </tr>
    <tr>
      <td>en_coname</td>
      <td><label>
        <input type="text" name="en_coname" id="en_coname"  size="50"/>
      </label></td>
    </tr>
    <tr>
      <td>en_text_date</td>
      <td><label>
        <textarea name="en_text_date" id="en_text_data" rows="5" cols="50"></textarea>
      </label></td>
    </tr>
    <tr>
      <td><input type="submit" name="submit" id="submit" value="提交" /></td>
      <td><a href="displayInfo?category=${parameters.myCategory}" >
      <input type="button" name="button" id="button" value="返回" /></a>
  </table>
</form>


