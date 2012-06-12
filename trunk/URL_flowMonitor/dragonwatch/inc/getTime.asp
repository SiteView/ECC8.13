<SCRIPT LANGUAGE="JavaScript">
<!--
function setConditionTime(y,m,d,h)
{
	var invoke=parent.frames.conditionFrame.frmCondition;
	invoke.selYear.value=y;
	invoke.selMonth.value=m;
	invoke.selDay.value=d;
	invoke.selHour.value=h;
	invoke.selDate.value=y+"-"+m+"-"+d+" "+h+":00";
	parent.frames.conditionFrame.datetime.innerText=y+"年"+m+"月"+d+"日"+h+"时";
}
//-->
</SCRIPT>
<%
on error resume next

If len(request.querystring("selby"))>0 Then
	Response.cookies("rep_by")=request.querystring("selby")
End If


If Len(Request.QueryString("per"))>0 Then
	Response.cookies("rep_per")=Request.QueryString("per")
	Response.cookies("rep_startTime")=Request.QueryString("d")
	Dim tmpD
	tmpD=CDate(Request.QueryString("d"))
	Response.Write "<script>setConditionTime(" & Year(tmpD) & "," & Month(tmpD) & "," & Day(tmpD) & "," & Hour(tmpD) & ");</script>"
End If
''****************************************************
''  得到开始结束时间,如果是提交的数据,则更新cookies  *
''****************************************************

If Len(Trim(Request.Form("selDate"))) = 0 Then '用户没有提交数据,从cookies中取得时间
	If Len(Trim(Request.cookies("rep_startTime"))) > 0 Then
		dt = Request.cookies("rep_startTime")
	Else
		dt = Now()
	End If
Else  '提交
	' 确定起始终止时间，根据选定的单位不同相应变化
	dt = CDate(Request.Form("selDate"))
End if

If Len(Trim(Request.Form("selPer"))) > 0 then
	strPer = Trim(Request.Form("selPer"))
Else
	if len(Trim(request.cookies("rep_per"))) > 0 then
		strPer = Trim(Request.cookies("rep_per"))
	else
		strPer = "d"
	end if
End if

If Len(Trim(Request.Form("selBy"))) > 0 then
	strBy  = Trim(Request.Form("selby"))
Else
	if len(Trim(request.cookies("rep_by"))) > 0 then
		strBy  = Trim(Request.cookies("rep_by"))
	else
		strBy  = "t"
	end if
End if

if not isdate(dt) then
	dt = now
end if
'response.write isdate(dt) & "<BR>"

yr = Year(dt)
ms = Month(dt)
dy = Day(dt)
Select Case strPer
	Case "h" ' 小时
		startDate = yr & "-" & ms & "-" & dy & " " & Hour(dt) & ":" & "00"
		endDate   = yr & "-" & ms & "-" & dy & " " & Hour(dt) & ":" & "59"
	Case "d" ' 天
		startDate = yr & "-" & ms & "-" & dy & " 00:00"
		endDate   = yr & "-" & ms & "-" & dy & " 23:59"
	Case "w" ' 星期
		wd  = CDate(yr & "-" & ms & "-" & dy)
		wds = CDate(wd & " 00:00")
		wde = CDate(DateAdd("d",6,wd) & " 23:59")
		Select Case WeekDay(dt)
			Case 1 'vbSunday
				startDate = DateAdd("d",-6,wds)
				endDate   = DateAdd("d",-6,wde)
			Case 2 'vbMonday
				startDate = wds
				endDate   = wde
			Case 3 'vbTuesday
				startDate = DateAdd("d",-1,wds)
				endDate   = DateAdd("d",-1,wde)
			Case 4 'vbWednesday
				startDate = DateAdd("d",-2,wds)
				endDate   = DateAdd("d",-2,wde)
			Case 5 'vbThursday
				startDate = DateAdd("d",-3,wds)
				endDate   = DateAdd("d",-3,wde)
			Case 6 'vbFriday
				startDate = DateAdd("d",-4,wds)
				endDate   = DateAdd("d",-4,wde)
			Case 7 'vbSaturday
				startDate = DateAdd("d",-5,wds)
				endDate   = DateAdd("d",-5,wde)
		End Select
	Case "m" ' 月
		LastDay=Array(31,28,31,30,31,30,31,31,30,31,30,31)
		y=Year(dt)
		If ((y mod 4=0) and (y mod 100<>0)) Or (y mod 400=0) Then LastDay(1)=29  ' 闰年

		startDate=y & "-" & Month(dt) & "-01 00:00"
		endDate=y & "-" & Month(dt) & "-" & LastDay(Month(dt)-1) & " 23:59"

		'ld = 31 '一个月的最后一天LastDay
		'for i=28 to 31
		'	if Not isDate(yr & "-" & ms & "-" & CStr(i)) then
		'		ld=i-1
		'		Exit For
		'	end if
		'next
		'startDate = yr & "-" & ms & "-1 00:00"
		'endDate   = yr & "-" & ms & "-" & CStr(ld) & " 23:59"
	Case "q" ' 季度
		Select Case ms
			Case 1,2,3
				startDate = yr & "-01-01 00:00"
				endDate   = yr & "-03-31 23:59"
			Case 4,5,6
				startDate = yr & "-04-01 00:00"
				endDate   = yr & "-06-30 23:59"
			Case 7,8,9
				startDate = yr & "-07-01 00:00"
				endDate   = yr & "-09-30 23:59"
			Case 10,11,12
				startDate = yr & "-10-01 00:00"
				endDate   = yr & "-12-31 23:59"
		End Select
	Case "y" ' 年
			startDate = yr & "-01-01 00:00"
			endDate   = yr & "-12-31 23:59"
	Case Else
		startDate = Date & " 00:00"
		endDate   = Date & " 23:59"
End Select

Response.cookies("rep_per") = strPer
Response.cookies("rep_by")  = strBy
' 保存测试时间
Response.cookies("rep_startTime") = dt
Response.cookies("rep_datetime")("start")  = startDate
Response.cookies("rep_datetime")("end")    = endDate
'response.write "s="&startDate & "<HR>"
'response.write "e="&enddate & "<HR>"
'response.write "per="&strPer
'response.end
%>
