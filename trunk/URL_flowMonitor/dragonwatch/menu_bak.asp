<!-- #include file="inc/check.asp" -->
<%
Dim strOnLoad
Select Case LCase(Request.cookies("curr_link"))
	Case "per_sum_d.asp"
		strOnLoad="t1.click();a1.click();"
	Case "tran_performance.asp"
		strOnLoad="t2.click();a2.click();"
'	Case "per_sum_d.asp"
'		strOnLoad="t3.click()"
	Case "rep_avg_d.asp"
		strOnLoad="t4.click();a4.click();"
	Case "service_okpercent_d.asp"
		strOnLoad="t5.click();a5.click();"
'	Case "per_sum_d.asp"
'		strOnLoad="t6.click()"
	Case "tran_analysis.asp"
		strOnLoad="t7.click();a7.click();"
	Case "comp_analysis.asp"
		strOnLoad="t8.click();a8.click();"
	Case "alarms_log.asp"
		strOnLoad="t9.click();a9.click();"
'	Case "per_sum_d.asp"
'		strOnLoad="t10.click()"
	Case Else
		strOnLoad="showAVG()"
End Select
%>
<html>
<head>
<title>菜单页</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net kenny kenny.jin@dragonflow.net">
<link rel="stylesheet" href="css.css" type="text/css">
<!-- <base target="mainFrame"> -->
</head>

<body onLoad="<%=strOnLoad%>" style="background:#330066" bgcolor="#330066" text="#000000" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0"><br>
<table width="100%" border="0" cellspacing="1" cellpadding="0">
  <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu1><span onClick="ShowHide(menu1,img_menu1)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>性能报告</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu1">
        <tr> 
          <td height="20" id=t1 onClick="m1.style.color='#330066';t1.style.background='#ffffff';clearother(1)">　　<a id=a1 target="mainFrame" class="menulink" href="main.asp?n=per_sum_d.asp"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m1>整体性能<span></B></font></a></td>
        </tr>
        <tr> 
          <td height="20" id=t2 onClick="m2.style.color='#330066';t2.style.background='#ffffff';clearother(2)">　　<a id=a2 target="mainFrame" class="menulink" href="main.asp?n=tran_performance.asp"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m2>业务流程性能<span></B></font></a></td>
        </tr>
<!--         <tr> 
          <td height="20" id=t3 onClick="m3.style.color='#330066';t3.style.background='#ffffff';clearother(3)">　　<a id=a3 target="mainFrame" href="empty.htm" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m3>行业性能<span></B></font></a></td>
        </tr>
 -->        <tr> 
          <td height="20" id=t4 onClick="m4.style.color='#330066';t4.style.background='#ffffff';clearother(4)">　　<a id=a4 target="mainFrame" href="main.asp?n=rep_avg_d.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m4>平均响应时间<span></B></font></a></td>
        </tr>
        <tr> 
          <td height="20" id=t5 onClick="m5.style.color='#330066';t5.style.background='#ffffff';clearother(5)">　　<a id=a5 target="mainFrame" href="main.asp?n=service_okpercent_d.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m5>服务成功率<span></B></font></a></td>
        </tr>
<!--         <tr> 
          <td height="20" id=t6 onClick="m6.style.color='#330066';t6.style.background='#ffffff'"><a target="mainFrame" href="main.asp?n=server_performance.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>　　<span id=m6>服务器端性能<span></B></font></a></td>
        </tr>
 -->      </table>
    </td>
  </tr>
  <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu2><span onClick="ShowHide(menu2,img_menu2)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>业务流程诊断</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu2">
        <tr> 
          <td height="20" id=t7 onClick="m7.style.color='#330066';t7.style.background='#ffffff';clearother(7)">　　<a id=a7 target="mainFrame" href="main.asp?n=tran_analysis.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m7>业务流程分析<span></B></font></a></td>
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
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu3">
        <tr> 
          <td height="20" id=t8 onClick="m8.style.color='#330066';t8.style.background='#ffffff';clearother(8)">　　<a id=a8 target="mainFrame" href="comp_analysis.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m8>网页组件分析<span></B></font></a></td>
        </tr>
      </table>
    </td>
  </tr>
  <!---------------------------------------- Alerts ------------------------------------------>
  <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu4><span onClick="ShowHide(menu4,img_menu4)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>报警</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu4">
        <tr> 
          <td height="20" id=t9 onClick="m9.style.color='#330066';t9.style.background='#ffffff';clearother(9)">　　<a id=a9 target="mainFrame" href="alarms_log.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m9>报警日志<span></B></font></a></td>
        </tr>
      </table>
    </td>
  </tr>

  <!-- <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu5><span onClick="ShowHide(menu5,img_menu5)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>帮助</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu5">
        <tr> 
          <td height="20" id=t10 onClick="m10.style.color='#330066';t10.style.background='#ffffff';clearother(10)">　　<a target="mainFrame" href="empty.htm" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m10>快速指导<span></B></font></a></td>
        </tr> -->
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


function ShowNotice(x)
{alert("正在建设，敬请期待...");}


function clearother(skipwhich)
{
	var bgcolor="#330066";
	var fontcolor="#ffffff";
	switch(skipwhich)
	{
		case 1:
			t2.style.background=bgcolor;
			m2.style.color=fontcolor;
			//t3.style.background=bgcolor;
			//m3.style.color=fontcolor;
			t4.style.background=bgcolor;
			m4.style.color=fontcolor;
			t5.style.background=bgcolor;
			m5.style.color=fontcolor;
			//t6.style.background=bgcolor;
			//m6.style.color=fontcolor;
			t7.style.background=bgcolor;
			m7.style.color=fontcolor;
			t8.style.background=bgcolor;
			m8.style.color=fontcolor;
			t9.style.background=bgcolor;
			m9.style.color=fontcolor;
			//t10.style.background=bgcolor;
			//m10.style.color=fontcolor;
			break;
		case 2:
			t1.style.background=bgcolor;
			m1.style.color=fontcolor;
			//t3.style.background=bgcolor;
			//m3.style.color=fontcolor;
			t4.style.background=bgcolor;
			m4.style.color=fontcolor;
			t5.style.background=bgcolor;
			m5.style.color=fontcolor;
			//t6.style.background=bgcolor;
			//m6.style.color=fontcolor;
			t7.style.background=bgcolor;
			m7.style.color=fontcolor;
			t8.style.background=bgcolor;
			m8.style.color=fontcolor;
			t9.style.background=bgcolor;
			m9.style.color=fontcolor;
			//t10.style.background=bgcolor;
			//m10.style.color=fontcolor;
			break;
		case 3:
			t1.style.background=bgcolor;
			m1.style.color=fontcolor;
			t2.style.background=bgcolor;
			m2.style.color=fontcolor;
			t4.style.background=bgcolor;
			m4.style.color=fontcolor;
			t5.style.background=bgcolor;
			m5.style.color=fontcolor;
			//t6.style.background=bgcolor;
			//m6.style.color=fontcolor;
			t7.style.background=bgcolor;
			m7.style.color=fontcolor;
			t8.style.background=bgcolor;
			m8.style.color=fontcolor;
			t9.style.background=bgcolor;
			m9.style.color=fontcolor;
			//t10.style.background=bgcolor;
			//m10.style.color=fontcolor;
			break;
		case 4:
			t1.style.background=bgcolor;
			m1.style.color=fontcolor;
			t2.style.background=bgcolor;
			m2.style.color=fontcolor;
			//t3.style.background=bgcolor;
			//m3.style.color=fontcolor;
			t5.style.background=bgcolor;
			m5.style.color=fontcolor;
			//t6.style.background=bgcolor;
			//m6.style.color=fontcolor;
			t7.style.background=bgcolor;
			m7.style.color=fontcolor;
			t8.style.background=bgcolor;
			m8.style.color=fontcolor;
			t9.style.background=bgcolor;
			m9.style.color=fontcolor;
			//t10.style.background=bgcolor;
			//m10.style.color=fontcolor;
			break;
		case 5:
			t1.style.background=bgcolor;
			m1.style.color=fontcolor;
			t2.style.background=bgcolor;
			m2.style.color=fontcolor;
			//t3.style.background=bgcolor;
			//m3.style.color=fontcolor;
			t4.style.background=bgcolor;
			m4.style.color=fontcolor;
			//t6.style.background=bgcolor;
			//m6.style.color=fontcolor;
			t7.style.background=bgcolor;
			m7.style.color=fontcolor;
			t8.style.background=bgcolor;
			m8.style.color=fontcolor;
			t9.style.background=bgcolor;
			m9.style.color=fontcolor;
			//t10.style.background=bgcolor;
			//m10.style.color=fontcolor;
			break;
		case 6:
			t1.style.background=bgcolor;
			m1.style.color=fontcolor;
			t2.style.background=bgcolor;
			m2.style.color=fontcolor;
			//t3.style.background=bgcolor;
			//m3.style.color=fontcolor;
			t4.style.background=bgcolor;
			m4.style.color=fontcolor;
			t5.style.background=bgcolor;
			m5.style.color=fontcolor;
			t7.style.background=bgcolor;
			m7.style.color=fontcolor;
			t8.style.background=bgcolor;
			m8.style.color=fontcolor;
			t9.style.background=bgcolor;
			m9.style.color=fontcolor;
			//t10.style.background=bgcolor;
			//m10.style.color=fontcolor;
			break;
		case 7:
			t1.style.background=bgcolor;
			m1.style.color=fontcolor;
			t2.style.background=bgcolor;
			m2.style.color=fontcolor;
			//t3.style.background=bgcolor;
			//m3.style.color=fontcolor;
			t4.style.background=bgcolor;
			m4.style.color=fontcolor;
			t5.style.background=bgcolor;
			m5.style.color=fontcolor;
			//t6.style.background=bgcolor;
			//m6.style.color=fontcolor;
			t8.style.background=bgcolor;
			m8.style.color=fontcolor;
			t9.style.background=bgcolor;
			m9.style.color=fontcolor;
			//t10.style.background=bgcolor;
			//m10.style.color=fontcolor;
			break;
		case 8:
			t1.style.background=bgcolor;
			m1.style.color=fontcolor;
			t2.style.background=bgcolor;
			m2.style.color=fontcolor;
			//t3.style.background=bgcolor;
			//m3.style.color=fontcolor;
			t4.style.background=bgcolor;
			m4.style.color=fontcolor;
			t5.style.background=bgcolor;
			m5.style.color=fontcolor;
			//t6.style.background=bgcolor;
			//m6.style.color=fontcolor;
			t7.style.background=bgcolor;
			m7.style.color=fontcolor;
			t9.style.background=bgcolor;
			m9.style.color=fontcolor;
			//t10.style.background=bgcolor;
			//m10.style.color=fontcolor;
			break;
		case 9:
			t1.style.background=bgcolor;
			m1.style.color=fontcolor;
			t2.style.background=bgcolor;
			m2.style.color=fontcolor;
			//t3.style.background=bgcolor;
			//m3.style.color=fontcolor;
			t4.style.background=bgcolor;
			m4.style.color=fontcolor;
			t5.style.background=bgcolor;
			m5.style.color=fontcolor;
			//t6.style.background=bgcolor;
			//m6.style.color=fontcolor;
			t7.style.background=bgcolor;
			m7.style.color=fontcolor;
			t8.style.background=bgcolor;
			m8.style.color=fontcolor;
			//t10.style.background=bgcolor;
			//m10.style.color=fontcolor;
			break;
		case 10:
			t1.style.background=bgcolor;
			m1.style.color=fontcolor;
			t2.style.background=bgcolor;
			m2.style.color=fontcolor;
			//t3.style.background=bgcolor;
			//m3.style.color=fontcolor;
			t4.style.background=bgcolor;
			m4.style.color=fontcolor;
			t5.style.background=bgcolor;
			m5.style.color=fontcolor;
			//t6.style.background=bgcolor;
			//m6.style.color=fontcolor;
			t7.style.background=bgcolor;
			m7.style.color=fontcolor;
			t8.style.background=bgcolor;
			m8.style.color=fontcolor;
			t9.style.background=bgcolor;
			m9.style.color=fontcolor;
			break;
	}
}

function showAVG()
{
	t4.click();  // 调用平均响应时间
	parent.mainFrame.document.location.href="main.asp";
}
//-->
</SCRIPT>