<br>

<h1>此页面为您对目录  <font color='blue'> ${monuInfo?if_exists.name?if_exists} </font>  进行编辑目录操作</h1>
<hr>

<form id="form1" name="form1" method="post" action="saveEditmonu">
  <table width="100%"  border="1" cellpadding="0" cellspacing="0">
  <tr>
      <td>属性名</td>
      <td>
        属性值
      </td>
    </tr>
    <tr>
      <td>id:</td>
      <td>
        <input type="text" name="id" id="id"  readonly="true" width="100%" value=${monuInfo?if_exists.id?if_exists}>
      </td>
    </tr>
    <tr>
      <td>parentId:</td>
      <td>
        <input type="text" name="parentId" readonly="true" width="100%" id="parentId" value=${monuInfo?if_exists.parentid?if_exists} >
      </td>
    </tr>    
    <tr>
      <td>country:</td>
      <td>
        <input type="text" name="country" id="country"  width="100%" value=${monuInfo?if_exists.country?if_exists}>
      </td>
    </tr>       
    <tr>
      <td>name:</td>
      <td>
        <input type="text" name="name" id="name"  width="100%" value=${monuInfo?if_exists.name?if_exists} >
      </td>
    </tr>     
    <tr>
      <td>images:</td>
      <td>
        <input type="text" name="images" id="images"   size="70" value=${monuInfo?if_exists.images?if_exists}>
      </td>
    </tr>  
    <tr>
      <td>link:</td>
      <td>
        <input type="text" name="link" id="link" value=${monuInfo?if_exists.link?if_exists}  >
      </td>
    </tr>      
    <tr>
      <td>enName:</td>
      <td>
        <input type="text" name="enName" id="enName" value=${monuInfo?if_exists.enName?if_exists}  >
      </td>
    </tr>     
    <tr>
      <td>enImages:</td>
      <td>
        <input type="text" name="enImages" id="enImages"  size="70" value=${monuInfo?if_exists.enImages?if_exists}>
      </td>
    </tr>    

    <tr>
    	<td>
    	  <input type="submit" name="submit" id="submit" value="提交" width="100%"/>
    	 </td>  
    	 <td>
    	 <td>
    	 </td>  	  
    </tr>
  </table>
  <br><a href="systemMaintenance" >返回</a>

  
</form>
