var x;
var y;
var offsetx = 10;
var offsety = 5;
var Width;  		//用户页面宽度
var Height; 		//用户页面高度
var divWidth;		//
var divHeight;  	//
var overDivTimerID;
var	dir = 1;

document.onmousemove = mouseMove

function mouseMove() {
	Width=document.body.clientWidth;
	Height=document.body.clientHeight;
	divWidth=overDiv.clientWidth;
	divHeight=overDiv.clientHeight;

	scrollTop=50;
	scrollLeft=0;
	scrollTop=document.body.scrollTop;
	scrollLeft=document.body.scrollLeft;

//	x=event.x+document.body.scrollLeft; 
//	y=event.y+document.body.scrollTop;
	x=event.x+scrollLeft; 
	y=event.y+scrollTop;

	if (y-scrollTop >= Height/2){ //上
		if (x-scroolLeft >= Width/2){ //左上
			dir=1;
		}else{
			dir=2;
		}	
	}else{
		if (x-scroolLeft >= Width/2){
			dir=3;
		}else{
			dir=4;
		}		
	}
	
}

function showTooltips(value,code){
	var text;
	var timeMisures=" 毫秒"
	if (value>1000){
		var remain;
		remain=Math.floor(value%1000);
		if (remain<100){
			remain="0" + remain;
		}
		value=Math.floor(value/1000)+"."+ remain;
		timeMisures=" 秒"
	}
	switch (code){
		case 1:
			text="Dns 平均响应时间 :"+value 
			break;
		case 2:
			text="平均连接时间 :"+value
			break;
		case 3:
			text="头数据时间 :"+value
			break;
		case 4:
			text="重定向时间 :"+value
			break;
		case 5:
			text="数据流时间 :"+value
			break;
	}
	text = text + timeMisures;
	txt="<TABLE WIDTH=250 BORDER=0 CELLPADDING=1 CELLSPACING=0 BGCOLOR=#000000><TR><TD><TABLE WIDTH=100% BORDER=0 CELLPADDING=0 CELLSPACING=0><TR><TD><B><FONT COLOR=#fafad2>业务流程分析</FONT></B></TD></TR></TABLE><TABLE WIDTH=100% BORDER=0 CELLPADDING=2 CELLSPACING=0 BGCOLOR=#fafad2><TR><TD><FONT COLOR=#000000>"+text+"</FONT></TD></TR></TABLE></TD></TR></TABLE>";
	document.all["overDiv"].innerHTML=txt;
	showIt();
	switch (dir) {
		case 1:  //左上
			overDiv.style.top=y-divHeight;
			overDiv.style.left=x-divWidth;
			break;
		
		case 2:  //右上
			overDiv.style.top=y-divHeight;
			overDiv.style.left=x+offsetx;
			break;
		
		case 3:  //右下
			overDiv.style.top=y;
			overDiv.style.left=x+offsetx;
			break;
		
		case 4:  //左下
			overDiv.style.top=y;
			overDiv.style.left=x-divWidth;
			break;
		}
}


function checkDelay(){
	showIt();
	Window.clearTimeout(overDivTimerID);
}

function showIt(){
	overDiv.style.visibility="visible";
	overDiv.style.top=y;
	overDiv.style.left=x;
}

function hideIt(){
	overDiv.style.visibility="hidden";
}
