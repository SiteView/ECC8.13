var x;
var y;
var offsetx = 10;
var offsety = 5;
var Width;  		//�û�ҳ����
var Height; 		//�û�ҳ��߶�
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

	if (y-scrollTop >= Height/2){ //��
		if (x-scroolLeft >= Width/2){ //����
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
	var timeMisures=" ����"
	if (value>1000){
		var remain;
		remain=Math.floor(value%1000);
		if (remain<100){
			remain="0" + remain;
		}
		value=Math.floor(value/1000)+"."+ remain;
		timeMisures=" ��"
	}
	switch (code){
		case 1:
			text="Dns ƽ����Ӧʱ�� :"+value 
			break;
		case 2:
			text="ƽ������ʱ�� :"+value
			break;
		case 3:
			text="ͷ����ʱ�� :"+value
			break;
		case 4:
			text="�ض���ʱ�� :"+value
			break;
		case 5:
			text="������ʱ�� :"+value
			break;
	}
	text = text + timeMisures;
	txt="<TABLE WIDTH=250 BORDER=0 CELLPADDING=1 CELLSPACING=0 BGCOLOR=#000000><TR><TD><TABLE WIDTH=100% BORDER=0 CELLPADDING=0 CELLSPACING=0><TR><TD><B><FONT COLOR=#fafad2>ҵ�����̷���</FONT></B></TD></TR></TABLE><TABLE WIDTH=100% BORDER=0 CELLPADDING=2 CELLSPACING=0 BGCOLOR=#fafad2><TR><TD><FONT COLOR=#000000>"+text+"</FONT></TD></TR></TABLE></TD></TR></TABLE>";
	document.all["overDiv"].innerHTML=txt;
	showIt();
	switch (dir) {
		case 1:  //����
			overDiv.style.top=y-divHeight;
			overDiv.style.left=x-divWidth;
			break;
		
		case 2:  //����
			overDiv.style.top=y-divHeight;
			overDiv.style.left=x+offsetx;
			break;
		
		case 3:  //����
			overDiv.style.top=y;
			overDiv.style.left=x+offsetx;
			break;
		
		case 4:  //����
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
