// JavaScript 文件
document.body.scroll="no";

if(bGeneral == 'true')
{
	document.getElementsByTagName("div")[0].className="panel_view1";
	document.getElementsByTagName("div")[1].className="panel_view1";
}

//document.getElementsByTagName("div")[0].className="panel_view1";
//document.getElementsByTagName("div")[2].className="panel_view1";
//document.getElementsByTagName("div")[3].className="panel_view1";

window.onresize = _OnResize; 

function _OnLoad()
{	
//	var uistyle<-->serveriput
	if(uistyle == "treepanandlist")
	{
		SetTreeViewPanel();
		SetItemPanelHeight();
	}
	else if(uistyle == "treepan")
	{
		SetTreeViewPanel();
	}
	else if(uistyle == "viewpanandlist")
	{
		SetViewPanelHeight();
		SetItemPanelHeight();
	}
	else if(uistyle == "viewpan")
	{
		SetViewPanelHeight();
	}
	else
	{
		
	}
}

function _OnResize()
{
//	var uistyle<-->serveriput
	if(uistyle == "treepanandlist")
	{
		SetTreeViewPanel();
		SetItemPanelHeight();
	}
	else if(uistyle == "treepan")
	{
		SetTreeViewPanel();
	}
	else if(uistyle == "viewpanandlist")
	{
		SetViewPanelHeight();
		SetItemPanelHeight();
	}
	else if(uistyle == "viewpan")
	{
		SetViewPanelHeight();
	}
	else
	{
		
	}
}

//*拖拽  调整treeview--------------------------------------------------------------------------/
var dragObject  = null;

if(uistyle == "treepan" || uistyle == "treepanandlist")
{
	document.onmousemove = resizeTreeTable;
	document.onmouseup = mouseUp;
	document.onmousedown = mouseDown;
}

function resizeTreeTable(evt)
{
//	var treeviewPanel<-->serveriput

	if(dragObject)
	{
		evt = evt || window.event;
		var obj = document.getElementById(treeviewPanel);
		if(evt.clientX < 150 || evt.clientX>450)
		{
			obj.rows[0].cells[1].style.pixelWidth = 5;			
		}
		else
		{
			obj.rows[0].cells[1].style.pixelWidth = 5;
			obj.rows[0].cells[0].style.pixelWidth = evt.clientX;
			document.getElementById("tree_panel").style.width = evt.clientX;
			document.getElementById("view_panel").style.width = document.body.clientWidth-evt.clientX-5;
		}
	}
}

function mouseDown(ev)
{
//	var drag_tree<-->serveriput

	ev = ev || window.event;
	var target = ev.target || ev.srcElement;
	
	if(target.getAttribute("id") == drag_tree)
	{
		dragObject = target;
	}
}

function mouseUp(ev)
{
	dragObject = null;
	iMouseDown = false;
}


//*拖拽  调整treeview--------------------------------------------------------------------------/

function SetTreeViewPanel()
{
	document.getElementById("tree_panel").style.height=document.body.clientHeight;
	document.getElementById("view_panel").style.height=document.body.clientHeight;

//	alert(document.getElementById("tree_panel").parentNode.parentNode.clientWidth);
	if(document.getElementById("tree_panel").parentNode.parentNode.style.display == "none")
		document.getElementById("view_panel").style.width=document.body.clientWidth;
	else
				document.getElementById("view_panel").style.width=document.body.clientWidth-document.getElementById("tree_panel").parentNode.parentNode.clientWidth-5;
}

function SetViewPanelHeight()
{
//	var fullstyle;<-->serveriput
//	alert(document.getElementById("view_panel").style.height);
	if(fullstyle == 'true')
	{
		document.getElementById("view_panel").style.height=document.body.clientHeight;
		document.getElementById("view_panel").style.width=document.body.clientWidth;
//		document.getElementById("view_panel").style.width='100%';
	}
	else
	{
		document.getElementById("view_panel").style.height=document.body.clientHeight - 50;
//		alert(document.getElementById("view_panel").style.height);
	}
}

function SetItemPanelHeight() 
{ 
//	var listpan;<-->serveriput
//	var listtitle;<-->serveriput
//	var listheight;<-->serveriput
//	alert(listpan);
//	alert(listtitle);
//	alert(listheight);
	var pans = listpan.split(",");
	var titles = listtitle.split(",");
	var heights = listheight.split(",");

	for(var i = 0; i < pans.length - 1; i++)
	{
		if(document.getElementById(pans[i]).clientHeight > heights[i])
		{
			document.getElementById(pans[i]).style.height = heights[i];
			document.getElementById(titles[i]).style.width = "98.5%";
		}
	}
}

function ShowPop(page,w,h,msg)
{
    if(navigator.userAgent.toLowerCase().indexOf("msie")+1)
    {
        var feature = "dialogWidth:"+w+"px;dialogHeight:"+h+"px;scroll:no;status:no;resizeable:no;help:no";
        var reValue = window.showModalDialog(page,msg,feature);
        return reValue;
    }
    else
    {
//        var feature = "toolbar=0,scrollbars=no,width=" + w + ",height=" + h;
		var theTop = (window.screen.height-h)/2;
        var theLeft = (window.screen.width-w)/2;
        var feature = "toolbar=0,scrollbars=no,left=" + theLeft + ",top=" + theTop + ",width=" + w + ",height=" + h;
		window.pop = window.open(page,"",feature);
    }
}

/*
function ShowTable(tid)
{
	if (document.getElementById("table"+tid).style.display == "none")
	{
		document.getElementById("table"+tid).style.display="";
		document.getElementById("imgtable"+tid).src="Images/table_pucker.png";
	}
	else
	{
		document.getElementById("table"+tid).style.display="none";
		document.getElementById("imgtable"+tid).src="Images/table_unwrap.png";
	}
}*/

function ShowTreeTable(bShow)
{
//	alert(bShow);
	if(bShow)
	{
		document.getElementById("tree_panel").parentNode.parentNode.style.display = "";
		document.getElementById(drag_tree).style.display = "";
		SetTreeViewPanel();
	}
	else
	{
		document.getElementById("tree_panel").parentNode.parentNode.style.display = "none";	
		document.getElementById(drag_tree).style.display = "none";	
		SetViewPanelHeight();
	}
}
