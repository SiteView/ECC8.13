<?
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ࣺconn
// ���ܣ��������ݿ�
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


	function getBgColor()  // ���汳��ɫ
		{
			static $flag;
			if ($flag=="#ffffff")
				$flag="#f0f0f0";
			else
				$flag="#ffffff";
			return $flag;
		}


	function print_profile_trans($group, $max=70)  // �г�Ԥ�����ļ������������ҵ������
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
					echo "<table width='100%' border=0 cellspacing=0 cellpadding=0><tr><td>Y�����ֵΪ70�룬X��Ϊ0��23ʱ</td><td><table border=0 align=right>";
				else
					echo "<table width='100%' border=0 cellspacing=0 cellpadding=0><tr><td>�ٷֱ����ֵΪ100%��X��Ϊ0��23ʱ</td><td><table border=0 align=right>";
				
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
// �ࣺavgobj
// ���ܣ���ÿ�յ�ƽ����Ӧʱ��ͼ��ҵ�����̣����У�
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
			// ����ָ��PROFILEID����ֹʱ��ġ�ҵ������ƽ����Ӧʱ�䣨�죩ҵ�����̷���
			$sql="exec yl_rep_avg_d $profileid,'$sDate','$eDate'";
			$sql2="exec yl_profiletrans $profileid";
		}
		else
		{
			// ����ָ��PROFILEID����ֹʱ��ġ�ҵ������ƽ����Ӧʱ�䣨�죩���з���
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

		// ��ӡ����
		$dDate = explode (" ", $sDate);
		$splitdate = explode ("-", $dDate[0]);
		imagestring($im, 3, 7, 2, $splitdate[2], $black);

		// ����ɫ����һ��������
		$arrColor=Array($black,$blue,$red,$green,$darkorange,$yellow,$cyan,$magenta,$orange,$shityellow);

		// ����PROFILE��ID��ѯԤ�����������ĳ��л�ҵ�����̣���Ϊ�����У���ҵ�����̣�������ɫ
		$rs2=mssql_query($sql2, $this->conn);
		$iIndex=0;
		while($row=mssql_fetch_row($rs2))
		{
				$arrColor2[$row[0]]=$arrColor[$iIndex++];
				if ($iIndex==10) $iIndex=0;
		}


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
		$iUseWhichColor=-1;
		$tranid=0;
		// ��������
		while($row=mssql_fetch_array($rs))
		{
			if ($row[1]!=$tranid)  // ���tranid���ˣ�������ڶ���ֵ��ʼ������һ��ֵ������
			{	
				/*
				if ($tranid<=10) // ȷ�����ߵ���ɫֵ
					$iUseWhichColor=$tranid-1;
				else
					$iUseWhichColor=$tranid%10;
				*/
				//echo $iUseWhichColor; //die;

				//========================================================================================
				// ѡ���ߵĵ�һ����������ֵ
				for ($i=0;$i<$xTotal;$i++)  // ������
				{
					if ($arrLine[$i]!=0)
					{
						$draw_line_startX=$i;
						$draw_line_startY=$arrLine[$i];
						break;
					}
				}
				// ѭ�����黭����
				while($draw_line_startX<$xTotal-1)
				{
					for ($i=$draw_line_startX+1;$i<$xTotal;$i++)  // ���ҽ�������������ֵ
					{
						if ($arrLine[$i]!=0)
						{
							$draw_line_endX=$i;
							$draw_line_endY=$arrLine[$i];
							break;
						}
					}
					// ��������λ��
					$X1=$iStep*2+$draw_line_startX*$iXStep;
					$X2=$iStep*2+$draw_line_endX*$iXStep;
					// ����
					//imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor[$iUseWhichColor]);
					imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor2[$tranid]);
				//echo $iUseWhichColor; 
					// ����Ҳ�������������꼰��ֵ��Ӧʹ��ʼ�����꣨��ѭ����������ֵΪX����ֵ���Ա�����ѭ��
					if ($draw_line_startX==$draw_line_endX)
						$draw_line_startX=$xTotal-1;
					else
						$draw_line_startX=$draw_line_endX;
					$draw_line_startY=$draw_line_endY;//die;
				}
				//========================================================================================

				/*  ������δ����ǾɵĻ��ߵĳ�����Ϊ�ͻ��Ĳ���ʱ���п��ܳ���2Сʱ��3Сʱ��4Сʱ���ּ�����Ի��߷������Ϊ���ϵķ���
				for ($i=0;$i<$xTotal-1;$i++)  // ������
				{
					$X1=$iStep*2+$i*$iXStep;
					$X2=$iStep*2+($i+1)*$iXStep;

					if (($arrLine[$i]!=0&&$arrLine[$i+1])!=0)  // �����˵�ֵ����Ϊ��ʱ�Ż���
						imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $arrColor[$iUseWhichColor]);
				}
				*/
				$iUseWhichColor++;
				if ($iUseWhichColor==10) $iUseWhichColor=0;
				$arrLine=Array(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);  // ��24Сʱ������ֵ
			}
			
			$tranid=$row[1];
			$iClock=$row[2]; // ������Сʱֵ
			$arrLine[$iClock]=($row[3]*$iYStep)/$iYStepValue;  // ����Y����ֵ
		}

				//$iUseWhichColor=$tranid-1;

				//if ($tranid>10) $iUseWhichColor=$tranid%10;

				//========================================================================================
				// ѡ���ߵĵ�һ����������ֵ
				for ($i=0;$i<$xTotal;$i++)  // ������
				{
					if ($arrLine[$i]!=0)
					{
						$draw_line_startX=$i;
						$draw_line_startY=$arrLine[$i];
						break;
					}
				}
				// ѭ�����黭����
				while($draw_line_startX<$xTotal-1)
				{
					for ($i=$draw_line_startX+1;$i<$xTotal;$i++)  // ���ҽ�������������ֵ
					{
						if ($arrLine[$i]!=0)
						{
							$draw_line_endX=$i;
							$draw_line_endY=$arrLine[$i];
							break;
						}
					}
					// ��������λ��
					$X1=$iStep*2+$draw_line_startX*$iXStep;
					$X2=$iStep*2+$draw_line_endX*$iXStep;
					// ����
					//imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor[$iUseWhichColor]);
					imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor2[$tranid]);

					// ����Ҳ�������������꼰��ֵ��Ӧʹ��ʼ�����꣨��ѭ����������ֵΪX����ֵ���Ա�����ѭ��
					if ($draw_line_startX==$draw_line_endX)
						$draw_line_startX=$xTotal-1;
					else
						$draw_line_startX=$draw_line_endX;
					$draw_line_startY=$draw_line_endY;
				}
				//========================================================================================

		// ����ͼ��
		ImagePNG($im);
		ImageDestroy($im);
	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ࣺserviceobj
// ���ܣ���ÿ�յķ���ɹ���ͼ��ҵ�����̣����У�
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
			// ����ָ��PROFILEID����ֹʱ��ġ�����ɹ��ʣ��죩ҵ�����̷���
			$sql="exec cq_server_okpercent_d_t $profileid,'$sDate','$eDate'";
			$sql2="exec yl_profiletrans $profileid";
		}
		else
		{
			// ����ָ��PROFILEID����ֹʱ��ġ�����ɹ��ʣ��죩���з���
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

		$xTotal=24; // X���ж��ٸ��̶�
		$yTotal=5;  // Y���ж��ٸ��̶�
		$iStep=2; // ��߾�ļ��
		$iXLen=$width-$iStep*3;  // X�᳤��
		$iYLen=$height-$iStep*3; // Y�᳤��
		$iXStep=ceil($iXLen/$xTotal);  // ��X��̶ȵ�ѭ���Ĳ������������룩
		$iYStep=ceil($iYLen/$yTotal);  // ��Y��̶ȵ�ѭ���Ĳ������������룩
		$iMax=0; // �������ֵ


		// ָ���������ֵΪ100��
		$iMax=100;
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

		// ��ӡ����
		$dDate = explode (" ", $sDate);
		$splitdate = explode ("-", $dDate[0]);
		imagestring($im, 3, 7, 62, $splitdate[2], $black);

		// ����ɫ����һ��������
		$arrColor=Array($black,$blue,$red,$green,$darkorange,$yellow,$cyan,$magenta,$orange,$shityellow);

		// ����PROFILE��ID��ѯԤ�����������ĳ��л�ҵ�����̣���Ϊ�����У���ҵ�����̣�������ɫ
		$rs2=mssql_query($sql2, $this->conn);
		$iIndex=0;
		while($row=mssql_fetch_row($rs2))
		{
				$arrColor2[$row[0]]=$arrColor[$iIndex++];
				if ($iIndex==10) $iIndex=0;
		}

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
		$iUseWhichColor=-1;
		$tranid=0;
		// ��������
		while($row=mssql_fetch_array($rs))
		{
			if ($row[1]!=$tranid)  // ���tranid���ˣ�������ڶ���ֵ��ʼ������һ��ֵ������
			{	
				/*
				if ($tranid<=10) // ȷ�����ߵ���ɫֵ
					$iUseWhichColor=$tranid-1;
				else
					$iUseWhichColor=$tranid%10;
				*/

				//========================================================================================
				// ѡ���ߵĵ�һ����������ֵ
				for ($i=0;$i<$xTotal;$i++)  // ������
				{
					if ($arrLine[$i]!=0)
					{
						$draw_line_startX=$i;
						$draw_line_startY=$arrLine[$i];
						break;
					}
				}
				// ѭ�����黭����
				while($draw_line_startX<$xTotal-1)
				{
					for ($i=$draw_line_startX+1;$i<$xTotal;$i++)  // ���ҽ�������������ֵ
					{
						if ($arrLine[$i]!=0)
						{
							$draw_line_endX=$i;
							$draw_line_endY=$arrLine[$i];
							break;
						}
					}
					// ��������λ��
					$X1=$iStep*2+$draw_line_startX*$iXStep;
					$X2=$iStep*2+$draw_line_endX*$iXStep;
					// ����
					imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor2[$tranid]);

					// ����Ҳ�������������꼰��ֵ��Ӧʹ��ʼ�����꣨��ѭ����������ֵΪX����ֵ���Ա�����ѭ��
					if ($draw_line_startX==$draw_line_endX)
						$draw_line_startX=$xTotal-1;
					else
						$draw_line_startX=$draw_line_endX;
					$draw_line_startY=$draw_line_endY;
				}
				//========================================================================================

				/*  ������δ����ǾɵĻ��ߵĳ�����Ϊ�ͻ��Ĳ���ʱ���п��ܳ���2Сʱ��3Сʱ��4Сʱ���ּ�����Ի��߷������Ϊ���ϵķ���
				for ($i=0;$i<$xTotal-1;$i++)  // ������
				{
					$X1=$iStep*2+$i*$iXStep;
					$X2=$iStep*2+($i+1)*$iXStep;

					if (($arrLine[$i]!=0&&$arrLine[$i+1])!=0)  // �����˵�ֵ����Ϊ��ʱ�Ż���
						imageline($im, $X1, $height-$iStep*2-$arrLine[$i], $X2, $height-$iStep*2-$arrLine[$i+1], $arrColor[$iUseWhichColor]);
				}
				//$iUseWhichColor++;
				*/
				$iUseWhichColor++;
				if ($iUseWhichColor==10) $iUseWhichColor=0;
				$arrLine=Array(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);  // ��24Сʱ������ֵ
			}
			
			$tranid=$row[1];
			$iClock=$row[2]; // ������Сʱֵ
			$arrLine[$iClock]=($row[3]*$iYStep)/$iYStepValue;  // ����Y����ֵ
		}

				//$iUseWhichColor=$tranid-1;

				//if ($tranid>10) $iUseWhichColor=$tranid%10;

				//========================================================================================
				// ѡ���ߵĵ�һ����������ֵ
				for ($i=0;$i<$xTotal;$i++)  // ������
				{
					if ($arrLine[$i]!=0)
					{
						$draw_line_startX=$i;
						$draw_line_startY=$arrLine[$i];
						break;
					}
				}
				// ѭ�����黭����
				while($draw_line_startX<$xTotal-1)
				{
					for ($i=$draw_line_startX+1;$i<$xTotal;$i++)  // ���ҽ�������������ֵ
					{
						if ($arrLine[$i]!=0)
						{
							$draw_line_endX=$i;
							$draw_line_endY=$arrLine[$i];
							break;
						}
					}
					// ��������λ��
					$X1=$iStep*2+$draw_line_startX*$iXStep;
					$X2=$iStep*2+$draw_line_endX*$iXStep;
					// ����
					imageline($im, $X1, $height-$iStep*2-$draw_line_startY, $X2, $height-$iStep*2-$draw_line_endY, $arrColor2[$tranid]);

					// ����Ҳ�������������꼰��ֵ��Ӧʹ��ʼ�����꣨��ѭ����������ֵΪX����ֵ���Ա�����ѭ��
					if ($draw_line_startX==$draw_line_endX)
						$draw_line_startX=$xTotal-1;
					else
						$draw_line_startX=$draw_line_endX;
					$draw_line_startY=$draw_line_endY;
				}
				//========================================================================================

		// ����ͼ��
		ImagePNG($im);
		ImageDestroy($im);
	}
}
?>