if (!document.layers&&!document.all) 
	event="test"

function showtip(status,current,e,text)
	{
		if (document.all&&document.readyState=="complete")
			{
				c1=Array("#ffffff","#009e63","#ffcf00","#ce0000","")  // 内容栏的颜色
				c2=Array("#666666","darkgreen","#484848","darkred","")  // 标题条的颜色
				c3=Array("#000000","#ffffff","#000000","#ffffff","") // text字体的颜色
				c4=Array("#ffffff","#ffffff","#ffcf00","#ffffff","") // ‘统计数据’字体的颜色
				str="<table width='100%' cellspacing=1 bgcolor='#000000'><tr bgcolor='"+c2[status]+"'><td><font color='"+c4[status]+"'>统计数据</font></td></tr><tr bgcolor='"+c1[status]+"'><td height='25'><font color='"+c3[status]+"'>"+text+"</font></td></tr></table>"
				//document.all.tooltip2.innerHTML='<marquee style="border:1px solid black">'+text+'</marquee>'
				document.all.tooltip2.innerHTML=str
				document.all.tooltip2.style.pixelLeft=event.clientX+document.body.scrollLeft+10
				document.all.tooltip2.style.pixelTop=event.clientY+document.body.scrollTop+10
				document.all.tooltip2.style.visibility="visible"
			}
		/*else if (document.layers)
			{
				document.tooltip2.document.nstip.document.write('<b>'+text+'</b>')
				document.tooltip2.document.nstip.document.close()
				document.tooltip2.document.nstip.left=0
				currentscroll=setInterval("scrolltip()",100)
				document.tooltip2.left=e.pageX+10
				document.tooltip2.top=e.pageY+10
				document.tooltip2.visibility="show"
		}*/
	}

function hidetip()
	{
		if (document.all)
			document.all.tooltip2.style.visibility="hidden"
		else if (document.layers)
			{
				clearInterval(currentscroll)
				document.tooltip2.visibility="hidden"
			}
	}

function scrolltip()
	{
		if (document.tooltip2.document.nstip.left>=-document.tooltip2.document.nstip.document.width)
			document.tooltip2.document.nstip.left-=5
		else
			document.tooltip2.document.nstip.left=150
	}

