<%
''****************************************************
''  �õ���ʼ����ʱ��,������ύ������,�����cookies  *
''****************************************************
If Len(Trim(Request.Form("selDate"))) = 0 Then '�û�û���ύ����,��cookies��ȡ��ʱ��
	If Len(Trim(Request.cookies("rep_startTime"))) > 0 Then
		dt = Request.cookies("rep_startTime")
	Else
		dt = Now()
	End If
Else  '�ύ
	' ȷ����ʼ��ֹʱ�䣬����ѡ���ĵ�λ��ͬ��Ӧ�仯
	dt = CDate(Request.Form("selDate"))
End if
If Len(Trim(Request.Form("selPer"))) > 0 then
	strPer = Trim(Request.Form("selPer"))
	strBy  = Trim(Request.Form("selby"))
Else
	if len(Trim(request.cookies("rep_per"))) > 0 then
		strPer = Trim(Request.cookies("rep_per"))
		strBy  = Trim(Request.cookies("rep_by"))
	else
		strPer = "d"
		strBy  = "t"
	end if
End if

yr = Year(dt)
ms = Month(dt)
dy = Day(dt)
Select Case strPer
	Case "h" ' Сʱ
		startDate = yr & "-" & ms & "-" & dy & " " & Hour(dt) & ":" & "00"
		endDate   = yr & "-" & ms & "-" & dy & " " & Hour(dt) & ":" & "59"
	Case "d" ' ��
		startDate = yr & "-" & ms & "-" & dy & " 00:00"
		endDate   = yr & "-" & ms & "-" & dy & " 23:59"
	Case "w" ' ����
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
	Case "m" ' ��
		ld = 31 'һ���µ����һ��LastDay
		for i=28 to 31
			if Not isDate(yr & "-" & ms & "-" & CStr(i)) then
				ld=i-1
				Exit For
			end if
		next
		startDate = yr & "-" & ms & "-1 00:00"
		endDate   = yr & "-" & ms & "-" & CStr(ld) & " 23:59"
	Case "q" ' ����
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
	Case "y" ' ��
			startDate = yr & "-01-01 00:00"
			endDate   = yr & "-12-31 23:59"
	Case Else
		startDate = Date & " 00:00"
		endDate   = Date & " 23:59"
End Select

Response.cookies("rep_per") = strPer
Response.cookies("rep_by")  = strBy
' �������ʱ��
Response.cookies("rep_startTime") = dt
%>