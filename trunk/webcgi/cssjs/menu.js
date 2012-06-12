var curX = 0;
var curY = 0;

function showbar()
{
	top.document.getElementById('frame_loadBra').style.display="";
}
function hiddenbar()
{
	top.document.getElementById('frame_loadBra').style.display="none";
}

function showMenu(nodeid, nodetype,  upd)
{
	curX = event.clientX - 5;
	curY = event.clientY - 5;
	document.all(curId).value = nodeid;
	document.all(curType).value = nodetype;
	update(upd);
    event.returnValue=false;
    event.cancelBubble=true;
    return false;
}

function runmenu(operateCode)
{
	document.all(curOprCode).value = operateCode;	
	if(update(runMenuButton)== 0)
		showbar();
}

function OpenTest(url) 
{
	window.showModalDialog(url);
}

function setnodetype(nodetype)
{
	document.all(curType).value = nodetype;
}

var _canResize = false;
function resizeTable(objID)
{	
		if(_canResize)
		{
			var obj = document.all(tableName);
			//var oMenuContainer=document.all('oMenuContainer');
			if(event.x < 150 || event.x>450)
			{
				obj.rows[0].cells[1].style.pixelWidth = 5;
				
			}
			else
			{
				obj.rows[0].cells[1].style.pixelWidth = 5;
				obj.rows[0].cells[0].style.pixelWidth = event.x;
				document.getElementById(objID).style.pixelWidth=event.x;
			}
		}
}

function mouseover(obj)
{
	 if (obj.className != 'treelinkactive')
		 obj.className='treelinkover';
}
	
function mouseout(obj)
{
	 if (obj.className != 'treelinkactive')
		 obj.className='treelink';
}

function menumouseover(obj)
{
	 if (obj.className != 'navselected')
		 obj.className='navhover';
}
	
function menumouseout(obj)
{
	 if (obj.className != 'navselected')
		 obj.className='navgeneral';
}

function SetCurfocus(focusId)
{
	document.all(curFocusId).value = focusId
	if(update(setNodeFocusButton)==0)
		showbar();	
}

function MM_goToURL() 
{ //v3.0
  var i, args=MM_goToURL.arguments; document.MM_returnValue = false;
  for (i=0; i<(args.length-1); i+=2) eval(args[i]+".location='"+args[i+1]+"'");
}