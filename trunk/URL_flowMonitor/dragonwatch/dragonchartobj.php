<?
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 类：conn
// 功能：连接数据库
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class conn
{
	var $PageSize;
	var $conn;

	function conn()
		{
			$this->PageSize=20;
			$this->conn=mssql_pconnect("localhost","dragon","*7EdY#");
			//$this->conn=mssql_pconnect("localhost","sa","");
			mssql_select_db("newtest");
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


	function print_profile_trans($group, $max=70)  // 列出预定义文件里包含的所有业务流程
		{
			GLOBAL $profileid;
			if ($group=="t")
				$sql="exec yl_profiletrans $profileid";
			else
				$sql="exec yl_profilecitys $profileid";

			//echo $sql;
			//die;
			$arrColor=Array("0,0,0","0,0,255","255,0,0","0,153,0","153,0,0","255,255,0","0,204,255","153,0,255","255,153,0","128,128,0");
			$rs=mssql_query($sql, $this->conn);
			if (mssql_num_rows($rs)>0)
			{
				if ($max==70)
					echo "<table width='100%' border=0 cellspacing=0 cellpadding=0><tr><td>Y轴最大值为70秒，X轴为0至23时</td><td><table border=0 align=right>";
				else
					echo "<table width='100%' border=0 cellspacing=0 cellpadding=0><tr><td>百分比最大值为100%，X轴为0至23时</td><td><table border=0 align=right>";
				
				$iColorIndex=0;
				while($row=mssql_fetch_row($rs))
				{
					/*
					if ($row[0]>10)
						$whichColor=$row[0]%10;
					else
						$whichColor=$row[0]-1;
					echo "<tr><td style='background:rgb($arrColor[$whichColor])'>&nbsp;</td><td>$row[1]</td></tr>";
					*/
					echo "<tr><td style='background:rgb($arrColor[$iColorIndex])'>&nbsp;</td><td>$row[1]</td></tr>";
					$iColorIndex++;
					if ($iColorIndex==10) $iColorIndex=0;
				}
				echo "</table></td></tr></table>";
			}
		}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 类：avgobj
// 功能：画每日的平均响应时间图表（业务流程，城市）
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class avgobj extends conn
{
	function avgobj()
	{
		Header("Content-type: image/png");
		$this->conn();
	}

	
	function avg_d($profileid, $sDate, $eDate, $width, $height, $group)
	{
		if ($group=="t")
		{
			// 计算指定PROFILEID和起止时间的　业务流程平均响应时间（天）业务流程分组
			$sql="exec yl_rep_avg_d $profileid,'$sDate','$eDate'";
			$sql2="exec yl_profiletrans $profileid";
		}
		else
		{
			// 计算指定PROFILEID和起止时间的　业务流程平均响应时间（天）城市分组
			$sql="exec yl_rep_avg_d_c $profileid,'$sDate','$eDate'";
			$sql2="exec yl_profilecitys $profileid";
		}

		//echo $sql;die;
		
		$rs=mssql_query($sql, $this->conn);
		if (mssql_num_rows($rs)==0)
		{
			$im = imagecreate($width,$height);
			$white = ImageColorAllocate($im, 255,255,255);
			$blue = ImageColorAllocate($im, 0,0,255);
			$black = ImageColorAllocate($im, 0,0,0);
			$dDate = explode (" ", $sDate);
			$splitdate = explode ("-", $dDate[0]);
			imagestring($im, 3, 7, 2, $splitdate[2], $black);
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

		// 打印日期
		$dDate = explode (" ", $sDate);
		$splitdate = explode ("-", $dDate[0]);
		imagestring($im, 3, 7, 2, $splitdate[2], $black);

		// 把颜色存入一个数组里
		$arrColor=Array($black,$blue,$red,$green,$darkorange,$yellow,$cyan,$magenta,$orange,$shityellow);

		// 根据PROFILE＿ID查询预定义所包含的城市或业务流程，并为各城市（或业务流程）分配颜色
		$rs2=mssql_query($sql2, $this->conn);
		$iIndex=0;
		while($row=mssql_fetch_row($rs2))
		{
				$arrColor2[$row[0]]=$arrColor[$iIndex++];
				if ($iIndex==10) $iIndex=0;
		}


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
		$iUseWhichColor=-1;
		$tranid=0;
		// 画数据线
		while($row=mssql_fetch_array($rs))
		{
			if ($row[1]!=$tranid)  // 如果tranid变了，则表明第二组值开始，画第一组值的曲线
			{	
				/*
				if ($tranid<=10) // 确定画线的颜色值
					$iUseWhichColor=$tranid-1;
				else
					$iUseWhichColor=$tranid%10;
				*/
				//echo $iUseWhichColor; //die;

				//========================================================================================
				// 选择画线的第一起点坐标和数值
				for ($i=0;$i<$xTotal;$i++)  // 画曲线
				{
					if ($arrLine[$i]!=0)
					{
						$draw_line_startX=$i;
						$draw_line_startY=$arrLine[$i];
						break;
					}
				}
				// 循环数组画曲线
				while($draw_line_startX<$xTotal-1)
				{
					for ($i=$draw_line_startX+1;$i<$xTotal;$i++)  // 查找结束点的坐标和数值
					{
						if ($arrLine[$i]!=0)
						{
							$draw_line_endX=$i;
							$draw_line_endY=$arrLine[$i];
							break;
						}
					}
					// 计算坐标位置
					$X1=$iStep*2+$draw_line_startX*$iXStep;
					$X2=$iStep*2+$draw_line_endX*$iXStep;
					// 画线
					//imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor[$iUseWhichColor]);
					imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor2[$tranid]);
				//echo $iUseWhichColor; 
					// 如果找不到结束点的坐标及数值，应使起始点坐标（即循环变量）的值为X轴终值，以便跳出循环
					if ($draw_line_startX==$draw_line_endX)
						$draw_line_startX=$xTotal-1;
					else
						$draw_line_startX=$draw_line_endX;
					$draw_line_startY=$draw_line_endY;//die;
				}
				//========================================================================================

				/*  下面这段代码是旧的画线的程序，因为客户的测试时间有可能出现2小时，3小时，4小时这种间隔所以画线方法需变为以上的方法
				for ($i=0;$i<$xTotal-1;$i++)  // 画曲线
				{
					$X1=$iStep*2+$i*$iXStep;
					$X2=$iStep*2+($i+1)*$iXStep;

					if (($arrLine[$i]!=0&&$arrLine[$i+1])!=0)  // 线两端点值均不为零时才画线
						imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $arrColor[$iUseWhichColor]);
				}
				*/
				$iUseWhichColor++;
				if ($iUseWhichColor==10) $iUseWhichColor=0;
				$arrLine=Array(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);  // 存24小时的数据值
			}
			
			$tranid=$row[1];
			$iClock=$row[2]; // 保存新小时值
			$arrLine[$iClock]=($row[3]*$iYStep)/$iYStepValue;  // 计算Y坐标值
		}

				//$iUseWhichColor=$tranid-1;

				//if ($tranid>10) $iUseWhichColor=$tranid%10;

				//========================================================================================
				// 选择画线的第一起点坐标和数值
				for ($i=0;$i<$xTotal;$i++)  // 画曲线
				{
					if ($arrLine[$i]!=0)
					{
						$draw_line_startX=$i;
						$draw_line_startY=$arrLine[$i];
						break;
					}
				}
				// 循环数组画曲线
				while($draw_line_startX<$xTotal-1)
				{
					for ($i=$draw_line_startX+1;$i<$xTotal;$i++)  // 查找结束点的坐标和数值
					{
						if ($arrLine[$i]!=0)
						{
							$draw_line_endX=$i;
							$draw_line_endY=$arrLine[$i];
							break;
						}
					}
					// 计算坐标位置
					$X1=$iStep*2+$draw_line_startX*$iXStep;
					$X2=$iStep*2+$draw_line_endX*$iXStep;
					// 画线
					//imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor[$iUseWhichColor]);
					imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor2[$tranid]);

					// 如果找不到结束点的坐标及数值，应使起始点坐标（即循环变量）的值为X轴终值，以便跳出循环
					if ($draw_line_startX==$draw_line_endX)
						$draw_line_startX=$xTotal-1;
					else
						$draw_line_startX=$draw_line_endX;
					$draw_line_startY=$draw_line_endY;
				}
				//========================================================================================

		// 输入图像
		ImagePNG($im);
		ImageDestroy($im);
	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 类：serviceobj
// 功能：画每日的服务成功率图表（业务流程，城市）
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class serviceobj extends conn
{
	function serviceobj()
	{
		//Header("Content-type: image/png");
		$this->conn();
	}

	
	function service_d($profileid, $sDate, $eDate, $width, $height, $group)
	{
		if ($group=="t")
		{
			// 计算指定PROFILEID和起止时间的　服务成功率（天）业务流程分组
			$sql="exec cq_server_okpercent_d_t $profileid,'$sDate','$eDate'";
			$sql2="exec yl_profiletrans $profileid";
		}
		else
		{
			// 计算指定PROFILEID和起止时间的　服务成功率（天）城市分组
			$sql="exec cq_server_okpercent_d_c $profileid,'$sDate','$eDate'";
			$sql2="exec yl_profilecitys $profileid";
		}

		//echo $sql;die;
		
		$rs=mssql_query($sql, $this->conn);
		if (mssql_num_rows($rs)==0)
		{
			$im = imagecreate($width,$height);
			$white = ImageColorAllocate($im, 255,255,255);
			$blue = ImageColorAllocate($im, 0,0,255);
			$black = ImageColorAllocate($im, 0,0,0);
			$dDate = explode (" ", $sDate);
			$splitdate = explode ("-", $dDate[0]);
			imagestring($im, 3, 7, 62, $splitdate[2], $black);
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


		// 指定数据最大值为100秒
		$iMax=100;
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

		// 打印日期
		$dDate = explode (" ", $sDate);
		$splitdate = explode ("-", $dDate[0]);
		imagestring($im, 3, 7, 62, $splitdate[2], $black);

		// 把颜色存入一个数组里
		$arrColor=Array($black,$blue,$red,$green,$darkorange,$yellow,$cyan,$magenta,$orange,$shityellow);

		// 根据PROFILE＿ID查询预定义所包含的城市或业务流程，并为各城市（或业务流程）分配颜色
		$rs2=mssql_query($sql2, $this->conn);
		$iIndex=0;
		while($row=mssql_fetch_row($rs2))
		{
				$arrColor2[$row[0]]=$arrColor[$iIndex++];
				if ($iIndex==10) $iIndex=0;
		}

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
		$iUseWhichColor=-1;
		$tranid=0;
		// 画数据线
		while($row=mssql_fetch_array($rs))
		{
			if ($row[1]!=$tranid)  // 如果tranid变了，则表明第二组值开始，画第一组值的曲线
			{	
				/*
				if ($tranid<=10) // 确定画线的颜色值
					$iUseWhichColor=$tranid-1;
				else
					$iUseWhichColor=$tranid%10;
				*/

				//========================================================================================
				// 选择画线的第一起点坐标和数值
				for ($i=0;$i<$xTotal;$i++)  // 画曲线
				{
					if ($arrLine[$i]!=0)
					{
						$draw_line_startX=$i;
						$draw_line_startY=$arrLine[$i];
						break;
					}
				}
				// 循环数组画曲线
				while($draw_line_startX<$xTotal-1)
				{
					for ($i=$draw_line_startX+1;$i<$xTotal;$i++)  // 查找结束点的坐标和数值
					{
						if ($arrLine[$i]!=0)
						{
							$draw_line_endX=$i;
							$draw_line_endY=$arrLine[$i];
							break;
						}
					}
					// 计算坐标位置
					$X1=$iStep*2+$draw_line_startX*$iXStep;
					$X2=$iStep*2+$draw_line_endX*$iXStep;
					// 画线
					imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor2[$tranid]);

					// 如果找不到结束点的坐标及数值，应使起始点坐标（即循环变量）的值为X轴终值，以便跳出循环
					if ($draw_line_startX==$draw_line_endX)
						$draw_line_startX=$xTotal-1;
					else
						$draw_line_startX=$draw_line_endX;
					$draw_line_startY=$draw_line_endY;
				}
				//========================================================================================

				/*  下面这段代码是旧的画线的程序，因为客户的测试时间有可能出现2小时，3小时，4小时这种间隔所以画线方法需变为以上的方法
				for ($i=0;$i<$xTotal-1;$i++)  // 画曲线
				{
					$X1=$iStep*2+$i*$iXStep;
					$X2=$iStep*2+($i+1)*$iXStep;

					if (($arrLine[$i]!=0&&$arrLine[$i+1])!=0)  // 线两端点值均不为零时才画线
						imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $arrColor[$iUseWhichColor]);
				}
				//$iUseWhichColor++;
				*/
				$iUseWhichColor++;
				if ($iUseWhichColor==10) $iUseWhichColor=0;
				$arrLine=Array(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);  // 存24小时的数据值
			}
			
			$tranid=$row[1];
			$iClock=$row[2]; // 保存新小时值
			$arrLine[$iClock]=($row[3]*$iYStep)/$iYStepValue;  // 计算Y坐标值
		}

				//$iUseWhichColor=$tranid-1;

				//if ($tranid>10) $iUseWhichColor=$tranid%10;

				//========================================================================================
				// 选择画线的第一起点坐标和数值
				for ($i=0;$i<$xTotal;$i++)  // 画曲线
				{
					if ($arrLine[$i]!=0)
					{
						$draw_line_startX=$i;
						$draw_line_startY=$arrLine[$i];
						break;
					}
				}
				// 循环数组画曲线
				while($draw_line_startX<$xTotal-1)
				{
					for ($i=$draw_line_startX+1;$i<$xTotal;$i++)  // 查找结束点的坐标和数值
					{
						if ($arrLine[$i]!=0)
						{
							$draw_line_endX=$i;
							$draw_line_endY=$arrLine[$i];
							break;
						}
					}
					// 计算坐标位置
					$X1=$iStep*2+$draw_line_startX*$iXStep;
					$X2=$iStep*2+$draw_line_endX*$iXStep;
					// 画线
					imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor2[$tranid]);

					// 如果找不到结束点的坐标及数值，应使起始点坐标（即循环变量）的值为X轴终值，以便跳出循环
					if ($draw_line_startX==$draw_line_endX)
						$draw_line_startX=$xTotal-1;
					else
						$draw_line_startX=$draw_line_endX;
					$draw_line_startY=$draw_line_endY;
				}
				//========================================================================================

		// 输入图像
		ImagePNG($im);
		ImageDestroy($im);
	}
}
?>