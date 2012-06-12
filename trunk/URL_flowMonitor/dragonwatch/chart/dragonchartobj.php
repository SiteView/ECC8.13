<?
class conn
{
	var $PageSize;
	var $conn;

	function conn()
		{
			$this->PageSize=20;
			$this->conn=mssql_pconnect("localhost","dragon","*7EdY#");
			mssql_select_db("test");
		}


	function setPageSize($x)
		{$this->PageSize=$x;}


	function getPageSize()
		{return $this->PageSize;}


	function getBgColor()  // 交替背景色
		{
			static $flag;
			if ($flag=="#ffffff")
				$flag="#f0f0f0";
			else
				$flag="#ffffff";
			return $flag;
		}


	function print_profile_trans($group)  // 列出预定义文件里包含的所有业务流程或城市
		{
			GLOBAL $profileid;
			if ($group=="t")
				$sql="exec yl_profiletrans ".$profileid;
			else
				$sql="exec yl_profilecitys ".$profileid;

			//echo $sql;
			//die;
			$arrColor=Array("0,0,0","0,0,255","255,0,0","0,153,0","153,0,0","255,255,0","0,204,255","153,0,255","255,153,0","128,128,0");
			$rs=mssql_query($sql, $this->conn);
			if (mssql_num_rows($rs)>0)
			{
				echo "<table width='100%' border=0 cellspacing=0 cellpadding=0><tr><td>Y轴最大值为70秒，X轴为0至23时</td><td><table border=0 align=right>";
				while($row=mssql_fetch_row($rs))
				{
					if ($row[0]>10)
						$whichColor=$row[0]%10;
					else
						$whichColor=$row[0]-1;
					echo "<tr><td style='background:rgb($arrColor[$whichColor])'>&nbsp;</td><td>$row[1]</td></tr>";
				}
				echo "</table></td></tr></table>";
			}
		}
}


// 平均响应时间的图表
class avgobj extends conn
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	function avgobj()
	{
		//Header("Content-type: image/png");
		$this->conn();
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	function avg_d($profileid, $sDate, $eDate, $width, $height, $group)
	{
		if ($group=="t")
		{
			// 计算指定PROFILEID和起止时间的　业务流程平均响应时间（天）业务流程分组
			$sql="exec yl_rep_avg_d $profileid,'$sDate','$eDate'";
		}
		else
		{
			// 计算指定PROFILEID和起止时间的　业务流程平均响应时间（天）城市分组
			$sql="exec yl_rep_avg_d_c $profileid,'$sDate','$eDate'";
		}

		//echo $sql;die;
		
		$rs=mssql_query($sql, $this->conn);
		if (mssql_num_rows($rs)==0)
		{
			$im = imagecreate($width,$height);
			$white = ImageColorAllocate($im, 255,255,255);
			$blue = ImageColorAllocate($im, 0,0,255);
			$dDate = explode (" ", $sDate);
			imagestring($im, 2, 7, 2, $dDate[0], $blue);
			ImagePNG($im);
			ImageDestroy($im);
			return ;
		}

		$xTotal=24; // X轴有多少个刻度
		$yTotal=5;  // Y轴有多少个刻度
		$iStep=2; // 离边距的间隔
		$iXLen=$width-$iStep*3;  // X轴长度
		$iYLen=$height-$iStep*3; // Y轴长度
		$iXStep=ceil($iXLen/$xTotal);  // 画X轴刻度的循环的步长（四舍五入）
		$iYStep=ceil($iYLen/$yTotal);  // 画Y轴刻度的循环的步长（四舍五入）
		$iMax=0; // 数据最大值


		// 指定数据最大值为70秒
		$iMax=70;
		//while($row=mssql_fetch_array($rs))
		//	if ($iMax<$row[3]) $iMax=$row[3];  // 计算数据大值

		// 初始化图像
		$im = imagecreate($width,$height);

		$white = ImageColorAllocate($im, 255,255,255);
		$lightgray=ImageColorAllocate($im, 200,200,200);

		$black = ImageColorAllocate($im, 0,0,0);
		$blue = ImageColorAllocate($im, 0,0,255);
		$red = ImageColorAllocate($im, 255,0,0);
		$green = ImageColorAllocate($im, 0,153,0);
		$darkorange= ImageColorAllocate($im, 153,0,0);
		$yellow = ImageColorAllocate($im, 255,255,0);
		$cyan = ImageColorAllocate($im, 0,204,255);
		$magenta = ImageColorAllocate($im, 153,0,255);
		$orange = ImageColorAllocate($im, 255,153,0);
		$shityellow = ImageColorAllocate($im, 128,128,0);

		$dDate = explode (" ", $sDate);
		imagestring($im, 2, 7, 2, $dDate[0], $blue);

		// 把颜色存入一个数组里
		$arrColor=Array($black,$blue,$red,$green,$darkorange,$yellow,$cyan,$magenta,$orange,$shityellow);

		// 画X轴的刻度
		for ($i=0;$i<$xTotal;$i++)
		{
			$tmpX=$iStep*2+$i*$iXStep;
			imageline($im, $tmpX, $height-$iStep*2, $tmpX, $height-$iStep, $black);
		}

		//$iMax=ceil($iMax+5); // 计算Y轴最大值
		$iYStepValue=$iMax/$yTotal;  // 计算Y轴一个刻度所代表的值大小

		// 画Y轴的刻度
		for ($i=1;$i<=$yTotal;$i++)
		{
			$tmpY=$height-$iStep*2-$i*$iYStep;
			imageline($im, $iStep, $tmpY, $iStep*2, $tmpY, $black);
			imageline($im, $iStep*2, $tmpY, $width-$iStep, $tmpY, $lightgray);
		}

		// 画XY轴
		imageline($im, $iStep, $height-$iStep*2, $width-$iStep, $height-$iStep*2, $black);
		imageline($im, $iStep*2, $iStep, $iStep*2, $height-$iStep, $black);


		mssql_data_seek($rs,0);  // 把数据移动到第一条记录
		$arrLine=Array(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);  // 存24小时的数据值
		$iClock=0;
		$iUseWhichColor=0;
		$tranid=0;
		// 画数据线
		while($row=mssql_fetch_array($rs))
		{
			if ($row[1]!=$tranid)  // 如果tranid变了，则表明第二组值开始，画第一组值的曲线
			{	
				for ($i=0;$i<$xTotal-1;$i++)  // 画曲线
				{
					$X1=$iStep*2+$i*$iXStep;
					$X2=$iStep*2+($i+1)*$iXStep;

					if ($tranid<=10) // 确定画线的颜色值
						$iUseWhichColor=$tranid-1;
					else
						$iUseWhichColor=$tranid%10;
					if (($arrLine[$i]!=0&&$arrLine[$i+1])!=0)  // 线两端点值均不为零时才画线
						imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $arrColor[$iUseWhichColor]);
				}
				//$iUseWhichColor++;
			}
			
			$tranid=$row[1];
			$iClock=$row[2]; // 保存新小时值
			$arrLine[$iClock]=($row[3]*$iYStep)/$iYStepValue;  // 计算Y坐标值
		}

				$iUseWhichColor=$tranid-1;

				if ($tranid>10) $iUseWhichColor=$tranid%10;
				for ($i=0;$i<$xTotal-1;$i++)  // 画曲线值
				{
					$X1=$iStep*2+$i*$iXStep;
					$X2=$iStep*2+($i+1)*$iXStep;

					if (($arrLine[$i]!=0&&$arrLine[$i+1])!=0)  // 线两端点值均不为零时才画线
						imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $arrColor[$iUseWhichColor]);
				}

		//$dDate = explode (" ", $sDate);
		//imagestring($im, 2, 7, 2, $dDate[0], $blue);

		// 输入图像
		ImagePNG($im);
		ImageDestroy($im);
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 画门户网站平均响应时间周走势图
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	function menhu_chart_w($hyid, $sDate, $eDate, $width, $height, $callwhich="")
	{
		// 计算指定行业ID和起止时间的“行业平均响应时间”周走势数据
		if (strLen($callwhich)!=0)
			$sql="exec yl_calc_all_w '$sDate','$eDate'";
		else
			$sql="exec yl_calc_hy_w $hyid,'$sDate','$eDate'";
		//echo $sql;die;
		
		$rs=mssql_query($sql, $this->conn);
		if (mssql_num_rows($rs)==0)
		{
			$im = imagecreate($width,$height);
			$white = ImageColorAllocate($im, 255,255,255);
			$blue = ImageColorAllocate($im, 0,0,255);
			$dDate = explode (" ", $sDate);
			//imagestring($im, 2, 7, 2, $dDate[0], $blue);
			imagestring($im, 2, 7, 2, "No Data!", $blue);
			ImagePNG($im);
			ImageDestroy($im);
			return ;
		}

		$xTotal=7; // X轴有多少个刻度
		$yTotal=5;  // Y轴有多少个刻度
		$iStep=12; // 离边距的间隔
		$iXLen=$width-$iStep*3;  // X轴长度
		$iYLen=$height-$iStep*3; // Y轴长度
		$iXStep=ceil($iXLen/$xTotal)+4;  // 画X轴刻度的循环的步长（四舍五入）
		$iYStep=ceil($iYLen/$yTotal);  // 画Y轴刻度的循环的步长（四舍五入）
		$iMax=0; // 数据最大值


		// 指定数据最大值为70秒
		$iMax=100;
		//while($row=mssql_fetch_array($rs))
		//	if ($iMax<$row[1]) $iMax=$row[1];  // 计算数据大值

		// 初始化图像
		$im = imagecreate($width,$height);

		$white = ImageColorAllocate($im, 255,255,255);
		$lightgray=ImageColorAllocate($im, 200,200,200);

		$black = ImageColorAllocate($im, 0,0,0);
		$blue = ImageColorAllocate($im, 0,0,255);
		$red = ImageColorAllocate($im, 255,0,0);
		$green = ImageColorAllocate($im, 0,153,0);
		$darkorange= ImageColorAllocate($im, 153,0,0);
		$yellow = ImageColorAllocate($im, 255,255,0);
		$cyan = ImageColorAllocate($im, 0,204,255);
		$magenta = ImageColorAllocate($im, 153,0,255);
		$orange = ImageColorAllocate($im, 255,153,0);
		$shityellow = ImageColorAllocate($im, 128,128,0);

		//$dDate = explode (" ", $sDate);
		//$tmpSDate=split(" ",$sDate);
		//$tmpEDate=split(" ",$eDate);
		//imagestring($im, 2, 45, 1, $tmpSDate[0]." To ".$tmpEDate[0], $blue);

		// 把颜色存入一个数组里
		$arrColor=Array($black,$blue,$red,$green,$darkorange,$yellow,$cyan,$magenta,$orange,$shityellow);

		$arrXLabel=Array("Mon","Tue","Wed","Thu","Fri","Sat","Sun");  // X轴标题

		// 画X轴的刻度
		for ($i=0;$i<$xTotal;$i++)
		{
			$tmpX=$iStep*2+$i*$iXStep;
			imageline($im, $tmpX, $height-$iStep*2, $tmpX, $height-$iStep-$iStep/2, $black);
			imageline($im, $tmpX, $height-$iStep*2, $tmpX, $iStep, $lightgray);
			imagestring($im, 2, $tmpX-8, $height-$iStep*2+8, $arrXLabel[$i], $black);
		}

		$iMax=ceil($iMax); // 计算Y轴最大值
		$iYStepValue=$iMax/$yTotal;  // 计算Y轴一个刻度所代表的值大小

		// 画Y轴的刻度
		for ($i=1;$i<=$yTotal;$i++)
		{
			$tmpY=$height-$iStep*2-$i*$iYStep;
			imageline($im, $iStep+$iStep/2, $tmpY, $iStep*2, $tmpY, $black);
			imageline($im, $iStep*2, $tmpY, $width-$iStep, $tmpY, $lightgray);
			imagestring($im, 2, 0, $tmpY-5, $i*$iYStepValue, $black);
		}

		// 画XY轴
		imageline($im, $iStep+$iStep/2, $height-$iStep*2, $width-$iStep, $height-$iStep*2, $black); // X轴
		imageline($im, $iStep*2, $iStep, $iStep*2, $height-$iStep-$iStep/2, $black);  // Y轴
		imagestring($im, 2, 6, $height-$iStep*2-$iStep/2, 0, $black);
		//imagestring($im, 2, 60, 0, "Scale Y: Second", $black);


		mssql_data_seek($rs,0);  // 把数据移动到第一条记录

		$arrLine=Array(0,0,0,0,0,0,0);  // 存7天的数据值
		while($row=mssql_fetch_array($rs))
		{
			$arrLine[$row[0]-1]=($row[1]*$iYStep)/$iYStepValue;  // 计算Y坐标值
		}
		// 画一周的曲线
		for ($i=0;$i<$xTotal-1;$i++)  // 画曲线
		{
			$X1=$iStep*2+$i*$iXStep;
			$X2=$iStep*2+($i+1)*$iXStep;
			imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $red);
		}

		// 输入图像
		ImagePNG($im);
		ImageDestroy($im);
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 画门户网站平均响应时间月走势图
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	function menhu_chart_m($hyid, $sDate, $eDate, $width, $height, $totalday, $callwhich="")
	{
		// 计算指定行业ID和起止时间的“行业平均响应时间”周走势数据
		if (strLen($callwhich)!=0)
			$sql="exec yl_calc_all_m '$sDate','$eDate'";
		else
			$sql="exec yl_calc_hy_m $hyid,'$sDate','$eDate'";
		//echo $sql;die;
		
		$rs=mssql_query($sql, $this->conn);
		if (mssql_num_rows($rs)==0)
		{
			$im = imagecreate($width,$height);
			$white = ImageColorAllocate($im, 255,255,255);
			$blue = ImageColorAllocate($im, 0,0,255);
			$dDate = explode (" ", $sDate);
			//imagestring($im, 2, 7, 2, $dDate[0], $blue);
			imagestring($im, 2, 7, 2, "No Data!", $blue);
			ImagePNG($im);
			ImageDestroy($im);
			return ;
		}

		$xTotal=$totalday; // X轴有多少个刻度
		$yTotal=2;  // Y轴有多少个刻度
		$iStep=12; // 离边距的间隔
		$iXLen=$width-$iStep*3;  // X轴长度
		$iYLen=$height-$iStep*3; // Y轴长度
		$iXStep=ceil($iXLen/$xTotal)-0.2;  // 画X轴刻度的循环的步长（四舍五入）
		$iYStep=ceil($iYLen/$yTotal);  // 画Y轴刻度的循环的步长（四舍五入）
		$iMax=0; // 数据最大值


		// 指定数据最大值为70秒
		$iMax=20;
		//while($row=mssql_fetch_array($rs))
		//	if ($iMax<$row[1]) $iMax=$row[1];  // 计算数据大值

		// 初始化图像
		$im = imagecreate($width,$height);

		$white = ImageColorAllocate($im, 255,255,255);
		$lightgray=ImageColorAllocate($im, 200,200,200);

		$black = ImageColorAllocate($im, 0,0,0);
		$blue = ImageColorAllocate($im, 0,0,255);
		$red = ImageColorAllocate($im, 255,0,0);
		$green = ImageColorAllocate($im, 0,153,0);
		$darkorange= ImageColorAllocate($im, 153,0,0);
		$yellow = ImageColorAllocate($im, 255,255,0);
		$cyan = ImageColorAllocate($im, 0,204,255);
		$magenta = ImageColorAllocate($im, 153,0,255);
		$orange = ImageColorAllocate($im, 255,153,0);
		$shityellow = ImageColorAllocate($im, 128,128,0);

		//$dDate = explode (" ", $sDate);
		//$tmpSDate=split(" ",$sDate);
		//$tmpEDate=split(" ",$eDate);
		//imagestring($im, 2, 45, 1, $tmpSDate[0]." To ".$tmpEDate[0], $blue);

		// 把颜色存入一个数组里
		$arrColor=Array($black,$blue,$red,$green,$darkorange,$yellow,$cyan,$magenta,$orange,$shityellow);

		$arrXLabel=Array("Mon","Tue","Wed","Thu","Fri","Sat","Sun");  // X轴标题

		// 画X轴的刻度
		for ($i=0;$i<$xTotal;$i++)
		{
			$tmpX=$iStep*2+$i*$iXStep;
			imageline($im, $tmpX, $height-$iStep*2, $tmpX, $height-$iStep-$iStep/2, $black);
			imageline($im, $tmpX, $height-$iStep*2, $tmpX, $iStep, $lightgray);
			imagestring($im, 2, $tmpX-2, $height-$iStep*2+8, $i+1, $black);
		}

		$iMax=ceil($iMax); // 计算Y轴最大值
		$iYStepValue=$iMax/$yTotal;  // 计算Y轴一个刻度所代表的值大小

		// 画Y轴的刻度
		for ($i=1;$i<=$yTotal;$i++)
		{
			$tmpY=$height-$iStep*2-$i*$iYStep;
			imageline($im, $iStep+$iStep/2, $tmpY, $iStep*2, $tmpY, $black);
			imageline($im, $iStep*2, $tmpY, $width-$iStep, $tmpY, $lightgray);
			imagestring($im, 2, 0, $tmpY-5, $i*$iYStepValue, $black);
		}

		// 画XY轴
		imageline($im, $iStep+$iStep/2, $height-$iStep*2, $width-$iStep, $height-$iStep*2, $black); // X轴
		imageline($im, $iStep*2, $iStep, $iStep*2, $height-$iStep-$iStep/2, $black);  // Y轴
		imagestring($im, 2, 6, $height-$iStep*2-$iStep/2, 0, $black);
		//imagestring($im, 2, 60, 0, "Scale Y: Second", $black);


		mssql_data_seek($rs,0);  // 把数据移动到第一条记录

		$arrLine=Array(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);  // 存7天的数据值
		while($row=mssql_fetch_array($rs))
		{
			$arrLine[$row[0]-1]=($row[1]*$iYStep)/$iYStepValue;  // 计算Y坐标值
		}
		// 画一周的曲线
		for ($i=0;$i<$xTotal-1;$i++)  // 画曲线
		{
			$X1=$iStep*2+$i*$iXStep;
			$X2=$iStep*2+($i+1)*$iXStep;
			imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $red);
		}

		// 输入图像
		ImagePNG($im);
		ImageDestroy($im);
	}
}
?>