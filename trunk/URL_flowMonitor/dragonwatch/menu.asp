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
	Case "alert_list.asp"
		strOnLoad="t11.click();a11.click();"
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
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu1><span onClick="ShowHide(menu1,img_menu1)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>用户体验报告</B></span></font> 
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
 -->
 	  <!-- 平均响应时间 
        <tr> 
          <td height="20" id=t16 onClick="m16.style.color='#330066';t16.style.background='#ffffff';clearother(16)">　　<a id=a16 target="mainFrame" href="main.asp?n=avgCalander.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m16>平均响应时间日历<span></B></font></a></td>
        </tr>
	  <!-- 服务成功率 
        <tr> 
          <td height="20" id=t19 onClick="m19.style.color='#330066';t19.style.background='#ffffff';clearother(19)">　　<a id=a19 target="mainFrame" href="main.asp?n=serviceCalander.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m19>服务成功率日历<span></B></font></a></td>
        </tr>
		-->
</table>
    </td>
  </tr>
<!-- 错误分析 -->
 <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu8><span onClick="ShowHide(menu8,img_menu8)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>错误分析</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu8">
<!-- 业务流程错误分析 -->
        <tr> 
          <td height="20" id=t13 onClick="m13.style.color='#330066';t13.style.background='#ffffff';clearother(13)">　　<a id=a13 target="mainFrame" class="menulink" href="main.asp?n=error_analysis.asp"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m13>业务流程错误分析<span></B></font></a></td>
        </tr>
<!-- 业务流程错误分析（结束） -->
<!-- 业务流程错误列表 -->
        <tr> 
          <td height="20" id=t17 onClick="m17.style.color='#330066';t17.style.background='#ffffff';clearother(17)">　　<a id=a17 target="mainFrame" class="menulink" href="main.asp?n=tran_failReason.asp"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m17>业务流程错误列表<span></B></font></a></td>
        </tr>
<!-- 业务流程错误列表（结束） -->
      </table>
    </td>
  </tr>
<!-- 错误分析（结束） -->
<!-- 月历式图表 --
  <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu7><span onClick="ShowHide(menu7,img_menu7)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>日历式图表</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu7">
	  !-- 平均响应时间 --
        <tr> 
          <td height="20" id=t16 onClick="m16.style.color='#330066';t16.style.background='#ffffff';clearother(16)">　　<a id=a16 target="mainFrame" href="main.asp?n=avgCalander.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m16>平均响应时间<span></B></font></a></td>
        </tr>
	  !-- 服务成功率 --
        <tr> 
          <td height="20" id=t19 onClick="m19.style.color='#330066';t19.style.background='#ffffff';clearother(19)">　　<a id=a19 target="mainFrame" href="main.asp?n=serviceCalander.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m19>服务成功率<span></B></font></a></td>
        </tr>
      </table>
    </td>
  </tr>
!-- 月历式图表（结束） -->

  <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu2><span onClick="ShowHide(menu2,img_menu2)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>业务流程诊断</B></span></font> 
    </td>
  </tr>

<!-- 业务流程分析 -->
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu2">
<!--         <tr> 
          <td height="20" id=t7 onClick="m7.style.color='#330066';t7.style.background='#ffffff';clearother(7)">　　<a id=a7 target="mainFrame" href="main.asp?n=tran_analysis.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m7>业务流程分析<span></B></font></a></td>
        </tr>
 -->
        <tr> 
          <td height="20" id=t8 onClick="m8.style.color='#330066';t8.style.background='#ffffff';clearother(8)">　　<a id=a8 target="mainFrame" href="comp_analysis.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m8>网页组件分析<span></B></font></a></td>
        </tr>
        <tr> 
          <td height="20" id=t18 onClick="m18.style.color='#330066';t18.style.background='#ffffff';clearother(18)">　　<a id=a18 target="mainFrame" href="main.asp?n=page_analysis.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m18>页面分析<span></B></font></a></td>
        </tr>
		<!--
        <tr> 
          <td height="20" id=t12 onClick="m12.style.color='#330066';t12.style.background='#ffffff';clearother(12)">　　<a id=a12 target="mainFrame" href="main.asp?n=webtrace_analysis.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m12>网络路由追踪分析<span></B></font></a></td>
        </tr>
		-->
      </table>
    </td>
  </tr>
<!-- 网络诊断 
  <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu5><span onClick="ShowHide(menu5,img_menu5)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>网络诊断</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu5">
      </table>
    </td>
  </tr>-->
<!-- 网络诊断（结束）
  <tr>
    <td><font color="#FFFFFF"><img src="img/minus.gif" width="9" height="9" id=img_menu3><span onClick="ShowHide(menu3,img_menu3)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>网页分析</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu3">
      </table>
    </td>
  </tr> -->

    <tr style="display:none">
    <td><font color="#FFFFFF"><img src="img/plus.gif" width="9" height="9" id=img_menu22><span onClick="ShowHide(menu22,img_menu22)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>SiteView</B></span></font> 
    </td>
  </tr>
  <tr style="display:none">
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu22" style="display:none">
        <tr> 
          <td height="20" id=t20 onClick="m20.style.color='#330066';t20.style.background='#ffffff';clearother(20)">　　<a id=a20 target="_blank" href="http://demo.siteview.com:6688" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m20>SiteView监测系统<span></B></font></a></td>
        </tr>
      </table>
    </td>
  </tr>

  <!---------------------------------------- Alerts -----------------------------------
  <tr>
    <td><font color="#FFFFFF"><img src="img/plus.gif" width="9" height="9" id=img_menu4><span onClick="ShowHide(menu4,img_menu4)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>报警</B></span></font> 
    </td>
  </tr>------->
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu4" style="display:none">
        <tr> 
          <td height="20" id=t9 onClick="m9.style.color='#330066';t9.style.background='#ffffff';clearother(9)">　　<a id=a9 target="mainFrame" href="alarms_log.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m9>报警日志<span></B></font></a></td>
        </tr>
	  <!-- Transaction 标准 -->
        <tr> 
          <td height="20" id=t14 onClick="m14.style.color='#330066';t14.style.background='#ffffff';clearother(14)">　　<a id=a14 href="javascript:showStandard()" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m14>业务流程标准<span></B></font></a></td>
        </tr>
	  <!-- Transaction 标准 -->
        <tr> 
          <td height="20" id=t11 onClick="m11.style.color='#330066';t11.style.background='#ffffff';clearother(11)">　　<a id=a11 target="mainFrame" href="alert_list.asp" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m11>报警设置<span></B></font></a></td>
        </tr>
      </table>
    </td>
  </tr>

 <tr>
    <td><font color="#FFFFFF"><img src="img/plus.gif" width="9" height="9" id=img_menu6><span onClick="ShowHide(menu6,img_menu6)" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B>帮助</B></span></font> 
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" border="0" cellspacing="0" cellpadding="0" id="menu6" style="display:none">
        <tr> 
          <td height="20" id=t10 onClick="m10.style.color='#330066';t10.style.background='#ffffff';clearother(10)">　　<a target="mainFrame" href="helpfile/help_main.htm" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m10>快速指导<span></B></font></a></td>
        </tr>
        <tr> 
          <td height="20" id=t15 onClick="m15.style.color='#330066';t15.style.background='#ffffff';clearother(10)">　　<a href="#" onclick="javascript:window.open('about.htm','about','height=320,width=400,scrollbars=no,toolbar=no,title=no');m15.style.color='#330066';t15.style.background='#ffffff';clearother(15)" class="menulink"><font color="#ffffff" onMouseOut="this.className='white'" onMouseOver="this.className='highlight'"><B><span id=m15>版本信息<span></B></font></a></td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<br>
<a href="http://www.siteview.com" target="_blank"><img src="img/adv.gif" border=0></a>
<br>
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
	for (i=1;i<=20;i++)
	{
		if (i==3||i==6||i==7||i==skipwhich) continue;

		x="t"+i;
		y="m"+i;
		document.all(x).style.background=bgcolor;
		document.all(y).style.color=fontcolor;
	}
}

function showAVG()
{
	t4.click();  // 调用平均响应时间
	parent.mainFrame.document.location.href="main.asp";
}

function showStandard()
{
	window.open("transtandard.asp","","toolbar=FALSE,resizable=1,scrollbars=2,height=450,width=800,screenx=550,screeny=300");
}
//-->
</SCRIPT>