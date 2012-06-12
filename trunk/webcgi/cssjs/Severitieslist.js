//document.write("<div id='Severitieslist' style='width:200px;height:100px;overflow-y:scroll;overflow-x:hidden;border:1px solid #666666;'></div>");
var objList1 = new CList("Severitieslist", "Severities");
//objList1.AppendItem("aa", "中国", true);
//objList1.InsertItem(0, "aa", "大中国", true);
//objList1.SetChecked(0, !objList1.IsChecked(0));
objList1.AppendItem("0", "Emergency", true);
objList1.AppendItem("1", "Alert", true);
objList1.AppendItem("2", "Critical", true);
objList1.AppendItem("3", "Error", true);
objList1.AppendItem("4", "Warning", true);
objList1.AppendItem("5", "Notice", true);
objList1.AppendItem("6", "Informational", true);
objList1.AppendItem("7", "Debug", true);
//pSeverities
function setSeverities()
{
	var strSeverities = "";
	
	var i=0;
	while(i<objList1.GetLength())
	{
		if(objList1.IsChecked(i))
		{
			strSeverities += i;
			strSeverities += ",";
			i++;
		}
		else
		{
			i++;
		}
	}	
//	alert(strSeverities);
	//document.all(pSeverities).setfocus();
	document.all(pSeverities).value = strSeverities;
	update(pQueryBtn);
}