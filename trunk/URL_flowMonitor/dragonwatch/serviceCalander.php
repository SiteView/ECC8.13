<HTML>
<HEAD>
<TITLE> ����ʽ����ɹ���ͼ </TITLE>
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
          <td width="55%"><B>����ʽ����ɹ���ͼ</B></td>
          <td width="45%" align="right"><B><?echo $yy?>��<?echo $mm?>��</B></td>
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
$today=date("d"); // ���������
//echo $mm;

if ( (($y%4==0) && ($y%100!=0)) || ($y%400==0) ) $lastDay[2]=29;   // �ж�����

$iFirstDay=mktime(0,0,0,$mm,1,$yy);  // ���ɱ���1�յ�����
$iIndexFirstDay=date("w",$iFirstDay);  // ���㱾��1�������ڼ�

if ($iIndexFirstDay==0) $iIndexFirstDay=7; // ����������գ������ֵΪ7

$iTableLoop=5;  // ���ѭ��������5
if ( ($lastDay[$mm]+$iIndexFirstDay)>35 ) $iTableLoop=6; // �����������ѭ��ӦΪ6��

// �г�ҵ�����̰�����ҵ�����̻����
$obj=new conn;
$obj->print_profile_trans($show, 100);


echo "<br>\n<table border=0 align=center width='100%' cellspacing=1 cellpadding=0><tr><td colspan=7 align=center style='font-size:18px;font-weight:bold'>".$yy."��".$mm."��";
echo "</td></tr>";
echo "<tr bgcolor='#330066' align=center style='color:white'><td>����һ</td><td>���ڶ�</td><td>������</td><td>������</td><td>������</td><td bgcolor='#ff6600' style='color:white'>������</td><td bgcolor='#ff6600' style='color:white'>������</td></tr>";

$iMonthIndex=1;
// ��������һ��
echo "<tr align=left>\r\n";
	for($j=1;$j<=7;$j++)
	{
		if ($j<$iIndexFirstDay)
			echo "<td>&nbsp;</td>";
		else
		{
			//echo "<td>".date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex++,$y))."</td>";
			$tmpdate=date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex,$y));
			$link="<a href='switchToservicerep.asp?time=".$tmpdate."&group=".$show."'>";
			if (date("d",mktime(0,0,0,$mm,$iMonthIndex,$y))>$today && ($mm==date("m")))
				echo "<td><img border=0 width=117 height=80 alt='".$tmpdate."' src='avgobj.php?service=1&show=$show&pid=$profileid&s=".$tmpdate." 00:00&e=".$tmpdate." 23:59'></td>\n";
			else
				echo "<td>".$link."<img border=0 width=117 height=80 alt='�鿴����ɹ��ʱ���' src='avgobj.php?service=1&show=$show&pid=$profileid&s=".$tmpdate." 00:00&e=".$tmpdate." 23:59'></a></td>\n";
			$iMonthIndex++;
		}
	}
echo "</tr>";
// ����������
for($i=2;$i<=$iTableLoop;$i++)
{
	echo "\n<tr align=center>";
	for($j=1;$j<=7;$j++)
		if ($iMonthIndex>$lastDay[$mm])
			echo "<td>&nbsp;</td>";
		else
		{
			$tmpdate=date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex,$y));
			$link="<a href='switchToservicerep.asp?time=".$tmpdate."&group=".$show."'>";
			if (date("d",mktime(0,0,0,$mm,$iMonthIndex,$y))>$today && ($mm==date("m"))) $link="";
//				echo "<td>".$link."<img border=0 width=117 height=80 alt='".date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex,$y))."' src='avgobj.php?show=$show&pid=$profileid&s=".date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex,$y))." 00:00&e=".date("Y-m-d",mktime(0,0,0,$mm,$iMonthIndex++,$y))." 23:59'></a></td>\n";
			if (date("d",$tmpdate)>$today && ($mm==date("m")))
				echo "<td><img border=0 width=117 height=80 alt='".$tmpdate."' src='avgobj.php?service=1&show=$show&pid=$profileid&s=".$tmpdate." 00:00&e=".$tmpdate." 23:59'></td>\n";
			else
				echo "<td>".$link."<img border=0 width=117 height=80 alt='�鿴����ɹ��ʱ���' src='avgobj.php?service=1&show=$show&pid=$profileid&s=".$tmpdate." 00:00&e=".$tmpdate." 23:59'></a></td>\n";
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
