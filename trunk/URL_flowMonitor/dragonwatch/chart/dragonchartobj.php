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


	function getBgColor()  // ���汳��ɫ
		{
			static $flag;
			if ($flag=="#ffffff")
				$flag="#f0f0f0";
			else
				$flag="#ffffff";
			return $flag;
		}


	function print_profile_trans($group)  // �г�Ԥ�����ļ������������ҵ�����̻����
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
				echo "<table width='100%' border=0 cellspacing=0 cellpadding=0><tr><td>Y�����ֵΪ70�룬X��Ϊ0��23ʱ</td><td><table border=0 align=right>";
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


// ƽ����Ӧʱ���ͼ��
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
			// ����ָ��PROFILEID����ֹʱ��ġ�ҵ������ƽ����Ӧʱ�䣨�죩ҵ�����̷���
			$sql="exec yl_rep_avg_d $profileid,'$sDate','$eDate'";
		}
		else
		{
			// ����ָ��PROFILEID����ֹʱ��ġ�ҵ������ƽ����Ӧʱ�䣨�죩���з���
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

		$xTotal=24; // X���ж��ٸ��̶�
		$yTotal=5;  // Y���ж��ٸ��̶�
		$iStep=2; // ��߾�ļ��
		$iXLen=$width-$iStep*3;  // X�᳤��
		$iYLen=$height-$iStep*3; // Y�᳤��
		$iXStep=ceil($iXLen/$xTotal);  // ��X��̶ȵ�ѭ���Ĳ������������룩
		$iYStep=ceil($iYLen/$yTotal);  // ��Y��̶ȵ�ѭ���Ĳ������������룩
		$iMax=0; // �������ֵ


		// ָ���������ֵΪ70��
		$iMax=70;
		//while($row=mssql_fetch_array($rs))
		//	if ($iMax<$row[3]) $iMax=$row[3];  // �������ݴ�ֵ

		// ��ʼ��ͼ��
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

		// ����ɫ����һ��������
		$arrColor=Array($black,$blue,$red,$green,$darkorange,$yellow,$cyan,$magenta,$orange,$shityellow);

		// ��X��Ŀ̶�
		for ($i=0;$i<$xTotal;$i++)
		{
			$tmpX=$iStep*2+$i*$iXStep;
			imageline($im, $tmpX, $height-$iStep*2, $tmpX, $height-$iStep, $black);
		}

		//$iMax=ceil($iMax+5); // ����Y�����ֵ
		$iYStepValue=$iMax/$yTotal;  // ����Y��һ���̶��������ֵ��С

		// ��Y��Ŀ̶�
		for ($i=1;$i<=$yTotal;$i++)
		{
			$tmpY=$height-$iStep*2-$i*$iYStep;
			imageline($im, $iStep, $tmpY, $iStep*2, $tmpY, $black);
			imageline($im, $iStep*2, $tmpY, $width-$iStep, $tmpY, $lightgray);
		}

		// ��XY��
		imageline($im, $iStep, $height-$iStep*2, $width-$iStep, $height-$iStep*2, $black);
		imageline($im, $iStep*2, $iStep, $iStep*2, $height-$iStep, $black);


		mssql_data_seek($rs,0);  // �������ƶ�����һ����¼
		$arrLine=Array(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);  // ��24Сʱ������ֵ
		$iClock=0;
		$iUseWhichColor=0;
		$tranid=0;
		// ��������
		while($row=mssql_fetch_array($rs))
		{
			if ($row[1]!=$tranid)  // ���tranid���ˣ�������ڶ���ֵ��ʼ������һ��ֵ������
			{	
				for ($i=0;$i<$xTotal-1;$i++)  // ������
				{
					$X1=$iStep*2+$i*$iXStep;
					$X2=$iStep*2+($i+1)*$iXStep;

					if ($tranid<=10) // ȷ�����ߵ���ɫֵ
						$iUseWhichColor=$tranid-1;
					else
						$iUseWhichColor=$tranid%10;
					if (($arrLine[$i]!=0&&$arrLine[$i+1])!=0)  // �����˵�ֵ����Ϊ��ʱ�Ż���
						imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $arrColor[$iUseWhichColor]);
				}
				//$iUseWhichColor++;
			}
			
			$tranid=$row[1];
			$iClock=$row[2]; // ������Сʱֵ
			$arrLine[$iClock]=($row[3]*$iYStep)/$iYStepValue;  // ����Y����ֵ
		}

				$iUseWhichColor=$tranid-1;

				if ($tranid>10) $iUseWhichColor=$tranid%10;
				for ($i=0;$i<$xTotal-1;$i++)  // ������ֵ
				{
					$X1=$iStep*2+$i*$iXStep;
					$X2=$iStep*2+($i+1)*$iXStep;

					if (($arrLine[$i]!=0&&$arrLine[$i+1])!=0)  // �����˵�ֵ����Ϊ��ʱ�Ż���
						imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $arrColor[$iUseWhichColor]);
				}

		//$dDate = explode (" ", $sDate);
		//imagestring($im, 2, 7, 2, $dDate[0], $blue);

		// ����ͼ��
		ImagePNG($im);
		ImageDestroy($im);
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���Ż���վƽ����Ӧʱ��������ͼ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	function menhu_chart_w($hyid, $sDate, $eDate, $width, $height, $callwhich="")
	{
		// ����ָ����ҵID����ֹʱ��ġ���ҵƽ����Ӧʱ�䡱����������
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

		$xTotal=7; // X���ж��ٸ��̶�
		$yTotal=5;  // Y���ж��ٸ��̶�
		$iStep=12; // ��߾�ļ��
		$iXLen=$width-$iStep*3;  // X�᳤��
		$iYLen=$height-$iStep*3; // Y�᳤��
		$iXStep=ceil($iXLen/$xTotal)+4;  // ��X��̶ȵ�ѭ���Ĳ������������룩
		$iYStep=ceil($iYLen/$yTotal);  // ��Y��̶ȵ�ѭ���Ĳ������������룩
		$iMax=0; // �������ֵ


		// ָ���������ֵΪ70��
		$iMax=100;
		//while($row=mssql_fetch_array($rs))
		//	if ($iMax<$row[1]) $iMax=$row[1];  // �������ݴ�ֵ

		// ��ʼ��ͼ��
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

		// ����ɫ����һ��������
		$arrColor=Array($black,$blue,$red,$green,$darkorange,$yellow,$cyan,$magenta,$orange,$shityellow);

		$arrXLabel=Array("Mon","Tue","Wed","Thu","Fri","Sat","Sun");  // X�����

		// ��X��Ŀ̶�
		for ($i=0;$i<$xTotal;$i++)
		{
			$tmpX=$iStep*2+$i*$iXStep;
			imageline($im, $tmpX, $height-$iStep*2, $tmpX, $height-$iStep-$iStep/2, $black);
			imageline($im, $tmpX, $height-$iStep*2, $tmpX, $iStep, $lightgray);
			imagestring($im, 2, $tmpX-8, $height-$iStep*2+8, $arrXLabel[$i], $black);
		}

		$iMax=ceil($iMax); // ����Y�����ֵ
		$iYStepValue=$iMax/$yTotal;  // ����Y��һ���̶��������ֵ��С

		// ��Y��Ŀ̶�
		for ($i=1;$i<=$yTotal;$i++)
		{
			$tmpY=$height-$iStep*2-$i*$iYStep;
			imageline($im, $iStep+$iStep/2, $tmpY, $iStep*2, $tmpY, $black);
			imageline($im, $iStep*2, $tmpY, $width-$iStep, $tmpY, $lightgray);
			imagestring($im, 2, 0, $tmpY-5, $i*$iYStepValue, $black);
		}

		// ��XY��
		imageline($im, $iStep+$iStep/2, $height-$iStep*2, $width-$iStep, $height-$iStep*2, $black); // X��
		imageline($im, $iStep*2, $iStep, $iStep*2, $height-$iStep-$iStep/2, $black);  // Y��
		imagestring($im, 2, 6, $height-$iStep*2-$iStep/2, 0, $black);
		//imagestring($im, 2, 60, 0, "Scale Y: Second", $black);


		mssql_data_seek($rs,0);  // �������ƶ�����һ����¼

		$arrLine=Array(0,0,0,0,0,0,0);  // ��7�������ֵ
		while($row=mssql_fetch_array($rs))
		{
			$arrLine[$row[0]-1]=($row[1]*$iYStep)/$iYStepValue;  // ����Y����ֵ
		}
		// ��һ�ܵ�����
		for ($i=0;$i<$xTotal-1;$i++)  // ������
		{
			$X1=$iStep*2+$i*$iXStep;
			$X2=$iStep*2+($i+1)*$iXStep;
			imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $red);
		}

		// ����ͼ��
		ImagePNG($im);
		ImageDestroy($im);
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���Ż���վƽ����Ӧʱ��������ͼ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	function menhu_chart_m($hyid, $sDate, $eDate, $width, $height, $totalday, $callwhich="")
	{
		// ����ָ����ҵID����ֹʱ��ġ���ҵƽ����Ӧʱ�䡱����������
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

		$xTotal=$totalday; // X���ж��ٸ��̶�
		$yTotal=2;  // Y���ж��ٸ��̶�
		$iStep=12; // ��߾�ļ��
		$iXLen=$width-$iStep*3;  // X�᳤��
		$iYLen=$height-$iStep*3; // Y�᳤��
		$iXStep=ceil($iXLen/$xTotal)-0.2;  // ��X��̶ȵ�ѭ���Ĳ������������룩
		$iYStep=ceil($iYLen/$yTotal);  // ��Y��̶ȵ�ѭ���Ĳ������������룩
		$iMax=0; // �������ֵ


		// ָ���������ֵΪ70��
		$iMax=20;
		//while($row=mssql_fetch_array($rs))
		//	if ($iMax<$row[1]) $iMax=$row[1];  // �������ݴ�ֵ

		// ��ʼ��ͼ��
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

		// ����ɫ����һ��������
		$arrColor=Array($black,$blue,$red,$green,$darkorange,$yellow,$cyan,$magenta,$orange,$shityellow);

		$arrXLabel=Array("Mon","Tue","Wed","Thu","Fri","Sat","Sun");  // X�����

		// ��X��Ŀ̶�
		for ($i=0;$i<$xTotal;$i++)
		{
			$tmpX=$iStep*2+$i*$iXStep;
			imageline($im, $tmpX, $height-$iStep*2, $tmpX, $height-$iStep-$iStep/2, $black);
			imageline($im, $tmpX, $height-$iStep*2, $tmpX, $iStep, $lightgray);
			imagestring($im, 2, $tmpX-2, $height-$iStep*2+8, $i+1, $black);
		}

		$iMax=ceil($iMax); // ����Y�����ֵ
		$iYStepValue=$iMax/$yTotal;  // ����Y��һ���̶��������ֵ��С

		// ��Y��Ŀ̶�
		for ($i=1;$i<=$yTotal;$i++)
		{
			$tmpY=$height-$iStep*2-$i*$iYStep;
			imageline($im, $iStep+$iStep/2, $tmpY, $iStep*2, $tmpY, $black);
			imageline($im, $iStep*2, $tmpY, $width-$iStep, $tmpY, $lightgray);
			imagestring($im, 2, 0, $tmpY-5, $i*$iYStepValue, $black);
		}

		// ��XY��
		imageline($im, $iStep+$iStep/2, $height-$iStep*2, $width-$iStep, $height-$iStep*2, $black); // X��
		imageline($im, $iStep*2, $iStep, $iStep*2, $height-$iStep-$iStep/2, $black);  // Y��
		imagestring($im, 2, 6, $height-$iStep*2-$iStep/2, 0, $black);
		//imagestring($im, 2, 60, 0, "Scale Y: Second", $black);


		mssql_data_seek($rs,0);  // �������ƶ�����һ����¼

		$arrLine=Array(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);  // ��7�������ֵ
		while($row=mssql_fetch_array($rs))
		{
			$arrLine[$row[0]-1]=($row[1]*$iYStep)/$iYStepValue;  // ����Y����ֵ
		}
		// ��һ�ܵ�����
		for ($i=0;$i<$xTotal-1;$i++)  // ������
		{
			$X1=$iStep*2+$i*$iXStep;
			$X2=$iStep*2+($i+1)*$iXStep;
			imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $red);
		}

		// ����ͼ��
		ImagePNG($im);
		ImageDestroy($im);
	}
}
?>