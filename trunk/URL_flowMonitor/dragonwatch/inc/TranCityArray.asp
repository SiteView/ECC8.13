<%
'/********************************************************************************
'/把从Cookies中取出的字符串转化为数组，Include此文件以后，可以直接引用下列数组和变量:
'/ arrAllTran(x,1)	-- 二维数组，对应于所有业务流程的ID和NAME。
'/ arrAllCity(x,1)	-- 二维数组，对应于所有城市的ID和NAME。
'/ arrSelTran(x,1)	-- 二维数组，对应于所有被选择的业务流程的ID和NAME。
'/ arrSelCity(x,1)	-- 二维数组，对应于所有被选择的城市的ID和NAME。
'/ bAllTranSelected	-- 是否所有的业务流程都被用户选择，在用户指定过滤条件前为TRUE。
'/ bAllCitySelected	-- 是否所有的城市都被用户选择，在用户指定过滤条件前为TRUE。

'/********************************************************************************
Dim arrSelTran
Dim arrSelCity
Dim arrAllTran
Dim arrAllCity
Dim bAllTranSelected
Dim bAllCitySelected

bAllTranSelected = false
bAllCitySelected = false

strAllTran = Request.Cookies("rep_all_tran")
strAllCity = Request.Cookies("rep_all_city")
strSelTran = Request.Cookies("rep_sel_tran")
strSelCity = Request.Cookies("rep_sel_city")

'-----------arrSelTran(x,1)--------------
arrTran1 = Split(strSelTran,",")
iTranUBound = UBound(arrTran1)
Redim arrSelTran(iTranUBound,1)
For i=0 To iTranUBound
	arrTran2 = Split(arrTran1(i),"_")
	arrSelTran(i,0) = arrTran2(0)
	arrSelTran(i,1) = arrTran2(1)
Next

'-----------arrSelCity(x,1)--------------
arrCity1 = Split(strSelCity,",")
iCityUBound = UBound(arrCity1)
Redim arrSelCity(iCityUBound,1)
For i=0 To iCityUBound
	arrCity2 = Split(arrCity1(i),"_")
	arrSelCity(i,0) = arrCity2(0)
	arrSelCity(i,1) = arrCity2(1)
Next

'-----------arrAllTran(x,1)--------------
arrTran1 = Split(strAllTran,",")
iTranUBound = UBound(arrTran1)
Redim arrAllTran(iTranUBound,1)
For i=0 To iTranUBound
	arrTran2 = Split(arrTran1(i),"_")
	arrAllTran(i,0) = arrTran2(0)
	arrAllTran(i,1) = arrTran2(1)
Next

'-----------arrAllCity(x,1)--------------
arrCity1 = Split(strAllCity,",")
iCityUBound = UBound(arrCity1)
Redim arrAllCity(iCityUBound,1)
For i=0 To iCityUBound
	arrCity2 = Split(arrCity1(i),"_")
	arrAllCity(i,0) = arrCity2(0)
	arrAllCity(i,1) = arrCity2(1)
Next

If UBound(arrAllTran) = UBound(arrSelTran) then bAllTranSelected = true
If UBound(arrAllCity) = UBound(arrSelCity) then bAllCitySelected = true
If Len(strSelTran) = 0 Then bAllTranSelected = true
If Len(strSelCity) = 0 Then bAllCitySelected = true
%>