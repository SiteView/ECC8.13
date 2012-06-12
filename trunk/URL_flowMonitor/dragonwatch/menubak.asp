<!-- #include file="inc/check.asp" -->
<html>
<head>
<title>菜单页</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
<base target="mainFrame">
</head>

<body style="background:#330066" bgcolor="#330066" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0"><br>
<table width="100%" border="0" cellspacing="1" cellpadding="0">
  <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu1><span onClick="ShowHide(menu1,img_menu1)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>性能报告</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="114" border="0" cellspacing="4" cellpadding="0" id="menu1">
        <tr> 
          <td width="17">&nbsp;</td>
          <td width="93"><a class="menulink" href="#"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>整体性能</B></font></a></td>
        </tr>
        <tr> 
          <td width="17">&nbsp;</td>
          <td width="93"><a class="menulink" href="#"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>业务流程性能</B></font></a></td>
        </tr>
        <tr> 
          <td width="17">&nbsp;</td>
          <td width="93"><a href="main.asp?n=industry_performance.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>行业性能</B></font></a></td>
        </tr>
        <tr> 
          <td width="17">&nbsp;</td>
          <td width="93"><a href="main.asp?n=rep_avg_d.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>平均响应时间</B></font></a></td>
        </tr>
        <tr> 
          <td width="17">&nbsp;</td>
          <td width="93"><a href="#" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>服务成功率</B></font></a></td>
        </tr>
        <tr> 
          <td width="17">&nbsp;</td>
          <td width="93"><a href="#" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>服务器端性能</B></font></a></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu2><span onClick="ShowHide(menu2,img_menu2)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>业务流程诊断</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="114" border="0" cellspacing="4" cellpadding="0" id="menu2">
        <tr> 
          <td width="17">&nbsp;</td>
          <td width="93"><a href="#" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>业务流程分析</B></font></a></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu3><span onClick="ShowHide(menu3,img_menu3)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>网页分析</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="114" border="0" cellspacing="4" cellpadding="0" id="menu3">
        <tr> 
          <td width="17">&nbsp;</td>
          <td width="93"><a href="#" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>网页组件分析</B></font></a></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu4><span onClick="ShowHide(menu4,img_menu4)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>帮助</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="114" border="0" cellspacing="4" cellpadding="0" id="menu4">
        <tr> 
          <td width="17">&nbsp;</td>
          <td width="93"><a href="#" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>快速指导</B></font></a></td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<font color="#FFFFFF"><br>
</font><br>
<br>
<br>
</body>
</html>
<SCRIPT LANGUAGE="JavaScript">
<!--
function ShowHide(which,whichimg)
{
	bShowHide=(which.style.display=="");
	if (bShowHide)
	{
		which.style.display="none";
		whichimg.src="img/plus.gif";
	}
	else
	{
		which.style.display="";
		whichimg.src="img/minus.gif";
	}
}
//-->
</SCRIPT>