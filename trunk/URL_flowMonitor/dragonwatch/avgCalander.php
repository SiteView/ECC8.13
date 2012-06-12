<HTML>
<HEAD>
<TITLE> 月历式平均响应时间图 </TITLE>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="Author" content="YuLei numen@263.net">
<link rel="stylesheet" href="css.css" type="text/css">
</HEAD>

<BODY leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<table width="100%" border="0" cellspacing="1" cellpadding="0">
  <tr>
    <td width="1%"><img src="img/dots.gif" width="33" height="32"></td>
    <td width="99%" bgcolor="#CCCCCC">
      <table width="100%" border="0" cellspacing="1" cellpadding="3">
        <tr>
          <td width="55%"><B>日历式平均响应时间图</B></td>
          <td width="45%" align="right"><B><?echo $yy?>年<?echo $mm?>月</B></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr><td colspan=2>

<?
require("dragonchartobj.php");

$lastDay=Array(0,31,28,31,30,31,30,31,31,30,31,30,31);
//$y=$yy;
$y=$yy;
$today=date("d"); // 今天的日期
//echo $mm;

if ( (($y%4==0) && ($y%100!=0)) || ($y%400==0) ) $lastDay[2]=29;   // 判断闰年

$iFirstDay=mktime(0,0,0,$mm,1,$yy);  // 生成本月1日的日期
$iIndexFirstDay=date("w",$iFirstDay);  // 计算本月1日是星期几

if ($iIndexFirstDay==0) $iIndexFirstDay=7; // 如果是星期日，则改其值为7

$iTableLoop=5;  // 表格循环次数是5
if ( ($lastDay[$mm]+$iIndexFirstDay)>35 ) $iTableLoop=6; // 如果超长则表格循环应为6次

// 列出业务流程包含的业务流程或城市
$obj=new conn;
$obj->print_profile_trans($show);


echo "<br>\n<table border=0 align=center width='100%' cellspacing=1 cellpadding=0><tr><td colspan=7 align=center style='font-size:18px;font-weight:bold'>".$yy."年".$mm."月";
echo "</td></tr>";
echo "<tr bgcolor='#330066' align=center style='color:white'><td>星期一</td><td>星期二</td><td>星期三</td><td>星期四</td><td>星期五</td><td bgcolor='#ff6600' style='color:white'>星期六</td><td bgcolor='#ff6600' style='color:white'>星期日</td></tr>";

$iMonthIndex=1;
// 打月历第一行
echo "<tr align=left>\r\n";
	for($j=1;$j<=7;$j++)
	{
		if ($j<$iIndexFirstDay)
			echo "<td>&nbsp;</td>";
		else
		{
			//echo "<td>".date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex++,$y))."</td>";
			$tmpdate=date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex,$y));
			$link="<a href='switchToavgrep.asp?time=".$tmpdate."&group=".$show."'>";
			if ((date("d",mktime(0,0,0,$mm,$iMonthIndex,$y))>$today) && ($mm==date("m")))
				echo "<td><img border=0 width=117 height=80 alt='".$tmpdate."' src='avgobj.php?show=$show&pid=$profileid&s=".$tmpdate." 00:00&e=".$tmpdate." 23:59'></td>\n";
			else  // 加链接
				echo "<td>".$link."<img border=0 width=117 height=80 alt='查看平均响应时间报表' src='avgobj.php?show=$show&pid=$profileid&s=".$tmpdate." 00:00&e=".$tmpdate." 23:59'></a></td>\n";
			$iMonthIndex++;
		}
	}
echo "</tr>";
// 打月历后几行
for($i=2;$i<=$iTableLoop;$i++)
{
	echo "\n<tr align=center>";
	for($j=1;$j<=7;$j++)
		if ($iMonthIndex>$lastDay[$mm])
			echo "<td>&nbsp;</td>";
		else
		{
			$tmpdate=date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex,$y));
			$link="<a href='switchToavgrep.asp?time=".$tmpdate."&group=".$show."'>";
			if (date("d",mktime(0,0,0,$mm,$iMonthIndex,$y))>$today && ($mm==date("m"))) $link="";
//				echo "<td>".$link."<img border=0 width=117 height=80 alt='".date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex,$y))."' src='avgobj.php?show=$show&pid=$profileid&s=".date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex,$y))." 00:00&e=".date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex++,$y))." 23:59'></a></td>\n";
			if ((date("d",mktime(0,0,0,$mm,$iMonthIndex,$y))>$today) && ($mm==date("m")))
				echo "<td><img border=0 width=117 height=80 alt='".$tmpdate."' src='avgobj.php?show=$show&pid=$profileid&s=".$tmpdate." 00:00&e=".$tmpdate." 23:59'></td>\n";
			else
				echo "<td>".$link."<img border=0 width=117 height=80 alt='查看平均响应时间报表' src='avgobj.php?show=$show&pid=$profileid&s=".$tmpdate." 00:00&e=".$tmpdate." 23:59'></a></td>\n";
			$iMonthIndex++;
		}
	echo "</tr>";
}

echo "</table>";
?>
  </td></tr>
</table>
</BODY>
</HTML>
