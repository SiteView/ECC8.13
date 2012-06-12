//document.write("<div id='Facilitylist' style='width:200px;height:100px;overflow-y:scroll;overflow-x:hidden;border:1px solid #666666;'></div>");
var objList = new CList("Facilitylist", "Facility");
//objList.AppendItem("aa", "中国", true);
//objList.InsertItem(0, "aa", "大中国", true);
//objList.SetChecked(0, !objList.IsChecked(0));
objList.AppendItem("0", "Kernel", true);
objList.AppendItem("1", "User", true);
objList.AppendItem("2", "Mail", true);
objList.AppendItem("3", "Daemon", true);
objList.AppendItem("4", "Auth", true);
objList.AppendItem("5", "Syslog", true);
objList.AppendItem("6", "Lpr", true);
objList.AppendItem("7", "News", true);
objList.AppendItem("8", "UUCP", true);
objList.AppendItem("9", "Cron", true);
objList.AppendItem("10", "Security", true);
objList.AppendItem("11", "FTP Daemon", true);
objList.AppendItem("12", "NTP", true);
objList.AppendItem("13", "Log audit", true);
objList.AppendItem("14", "Log alert", true);
objList.AppendItem("15", "Clock Daemon", true);
objList.AppendItem("16", "local0", true);
objList.AppendItem("17", "local1", true);
objList.AppendItem("18", "local2", true);
objList.AppendItem("19", "local3", true);
objList.AppendItem("20", "local4", true);
objList.AppendItem("21", "local5", true);
objList.AppendItem("22", "local6", true);
objList.AppendItem("23", "local7", true);
function setFacility()
{
	//document.all(pFacility).setfocus();
	document.all(pFacility).value = "";
	var i=0;
	while(i<objList.GetLength())
	{
		if(objList.IsChecked(i))
		{
			document.all(pFacility).value += i;
			document.all(pFacility).value += ",";
			i++;
		}
		else
		{
			i++;
		}
	}
}
