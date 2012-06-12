<br>

<h1>此页面为您对 <font color='blue'>${monuInfo?if_exists.name?if_exists} </font>进行增加子目录操作</h1>
<font color='blue'>注：</font>对于images而言，是保存为数据资源，再进行链接的，所以您在添加或者修改图片是请将图片做成数据资源。
<br>
<hr>

<form id="form1" name="form1" method="post" action="addMonuPage">
  <table width="100%"  border="1" cellpadding="0" cellspacing="0">
  <tr>
      <td>属性名</td>
      <td>
        属性
      </td>
    </tr>
    <tr>
      <td>parentId:</td>
      <td>
        <input type="text" name="parentId" id="parentId" value=${parameters.id?if_exists} readonly="true" width="100%"/>
      </td>
    </tr>
    <tr>
      <td>country:</td>
      <td>
        <input type="text" name="country" id="country" value="US,CN"  width="100%"/>
      </td>
    </tr>
    <tr>
      <td>name:</td>
      <td>
        <input type="text" name="name" id="name"  width="100%" />
      </td>
    </tr>
    <tr>
      <td>images:</td>
      <td>
        <input type="text" name="imagines" size='70' id="imagines" width="100%"/>
      </td>
    </tr>
    <tr>
      <td>link:</td>
      <td>
        <input type="text" name="link" id="link" width="100%"/>
      </td>
    </tr>     
    <tr>
      <td>enName:</td>
      <td>
        <input type="text" name="enName" id="enName" width="100%"/>
      </td>
    </tr>    
    <tr>
      <td>en_images:</td>
      <td>
        <input type="text" name="enImagines" size='70' id="en_imagines" width="100%"/>
      </td>
    </tr>
    <tr>
    	<td align='center'>
    	  <input type="submit" name="submit" id="submit" value="提交" width="100%"/>
    	 </td>  
    	 <td>
    	  <input type="reset" name="reset" id="reset" value="取消" width="100%"/>
    	 </td>  	  
    </tr>
  </table>
</form>