<%
'�Ѷ���ı���������:
'MaxOverTime '�ܷ�Ӧʱ������ֵ
' arrData       '��ά����,0-City_name,1-DSN,2-conn,3-header,4-redir,5-data
''''''''''''    '6-overtime,7-PageSize,8-totalCity,9-City_id
'iRows       '����
'iCols       '����(��֪=8)
Const iCols=8
Const TDWidth=610  '��ʾͼƬ�ı��Ԫ�Ŀ��(����Ϊ��λ)

'**********************************************************************
dim MaxScale      '������̶�
dim MaxPixls      'ʵ�ʴ����������,С�ڱ��Ԫ��ʵ�ʿ��610
dim ActiveCityId  '��ǰҪ��ʾ��city��ID

ActiveCityId = Request.cookies("rep_city")("id")
if iRows > 0 then
	redim arrWidth(4,iRows-1) '��arrData,����һ����scale�����ÿ����ɫ�Ŀ��.
end if
redim arrWhichPic(4)
arrWhichPic(0) = "dns.gif"
arrWhichPic(1) = "conn.gif"
arrWhichPic(2) = "header.gif"
arrWhichPic(3) = "redir.gif"
arrWhichPic(4) = "data.gif"

if iRows > 0  then
	MaxScale = CInt(MaxOverTime*102)/100
	MaxPixls = MaxOvertime * 610 / MaxScale
end if
'���MaxOvertimeС��10��,���Ժ���Ϊ��λ��ʾ
if MaxOvertime < 10 then MaxScale = MaxScale * 1000

'�ɱ����õ�ÿƬͼ��Ŀ��
for i=0 to iRows - 1
	for j = 0 to 4
		arrWidth(j,i) = CInt(MaxPixls * arrData(j+1,i)/(MaxOverTime+0.000001))
	next
next

%>
<table width="820" border="1" cellspacing=0>
  <tr> 
    <td width="100">&nbsp;</td>
    <td width="47">��С(KB)</td>
    <td width="45">����(KB/s)</td>
    <td width="610" nowrap>��������</td>
  </tr>
  <%
  If iRows > 0 then
	If bFilteredCity And bFilteredTran then
	    For i=0 to iRows-1
			'ֻ��ʾ��ǰ��Transaction����
			if arrData(9,i) = Cint(ActiveCityId) then
				Response.Write "<tr height=25>"
				Response.write "<td width=100>&nbsp;" & arrData(0,i) & "</td>"
				Response.write "<td width=47>&nbsp;" & arrData(7,i) & "</td>"
				Response.write "<td width=45>&nbsp;" & formatNumber(arrData(7,i)/arrData(6,i),2) & "</td>"
				response.write "<td width=610 nowrap valign=top>"
				for j=0 to 4
					Response.write "<A href='#' onMouseOver='return STT(" & arrData(j+1,i)*1000 & "," & j+1 & ")'"
					response.write " onMouseOut='return nd()'"
					response.write " onClick='return nop()'>"
					Response.write "<IMG src='img/" & arrWhichPic(j) & "' height='15' width='" & arrWidth(j,i) & "' border=0></A>"
				next
				response.write "</td>"
				Response.write "</tr>"
	    	else
				Response.Write "<tr height=25>"
				Response.write "<td width=100>&nbsp;" & arrData(0,i) & "</td>"
				Response.write "<td width=47>&nbsp;N/A</td>"
				Response.write "<td width=45>&nbsp;N/A</td>"
				response.write "<td width=610 nowrap valign=top>"
				response.write "</td>"
				Response.write "</tr>"
	    	end if
	    Next
  	else
	    For i=0 to iRows-1
			Response.Write "<tr height=25>"
			Response.write "<td width=100>&nbsp;<a class='bluelink' href='tran_analysis.asp?cityid=" & arrData(9,i) & "&cityname=" & arrData(0,i) & "'>" & arrData(0,i) & "</a></td>"
			Response.write "<td width=47>&nbsp;" & arrData(7,i) & "</td>"
			Response.write "<td width=45>&nbsp;" & formatNumber(arrData(7,i)/arrData(6,i),2) & "</td>"
			response.write "<td width=610 nowrap valign=top>"
			for j=0 to 4
				Response.write "<A href='#' onMouseOver='return STT(" & arrData(j+1,i)*1000 & "," & j+1 & ")'"
				response.write " onMouseOut='return nd()'"
				response.write " onClick='return nop()'>"
				Response.write "<IMG src='img/" & arrWhichPic(j) & "' height='15' width='" & arrWidth(j,i) & "' border=0></A>"
			next
			response.write "</td>"
			Response.write "</tr>"
	    Next
  	
  	end if
  End if
  %>
  <tr> 
    <td width="100">&nbsp;�̶�(��λ: 
      <%
    dim x
    if MaxOverTime >= 10 then
    	x=0.1
	else
    	response.write "��"
		x=100	
    end if
    %>��)</td>
    <td width="47">&nbsp;</td>
    <td width="45">&nbsp;</td>
    <td width="610"> 
      <table border="0" cellspacing="0" cellpadding="0" valign="top">
        <tr valign="top"> 
          <td width="122" ALIGN=RIGHT valign="top"><img src="img/conn_grey.gif" width="120" height="2" valign="top"><img src="img/conn_grey.gif" width="3" height="15"></td>
          <td width="122" ALIGN=RIGHT valign="top"><img src="img/conn_grey.gif" width="120" height="2" valign="top"><img src="img/conn_grey.gif" width="3" height="15"></td>
          <td width="122" ALIGN=RIGHT valign="top"><img src="img/conn_grey.gif" width="120" height="2" valign="top"><img src="img/conn_grey.gif" width="3" height="15"></td>
          <td width="122" ALIGN=RIGHT valign="top"><img src="img/conn_grey.gif" width="120" height="2" valign="top"><img src="img/conn_grey.gif" width="3" height="15"></td>
          <td width="122" ALIGN=RIGHT valign="top"><img src="img/conn_grey.gif" width="120" height="2" valign="top"><img src="img/conn_grey.gif" width="3" height="15"></td>
        </tr>
      </table>
      <table border="0" cellspacing="0" cellpadding="0" valign="top">
        <tr align="right"> 
          <td width="122">&nbsp;<%=(MaxScale-x)*1/5 +x%></td>
          <td width="122">&nbsp;<%=(MaxScale-x)*2/5 +x%></td>
          <td width="122">&nbsp;<%=(MaxScale-x)*3/5 +x%></td>
          <td width="122">&nbsp;<%=(MaxScale-x)*4/5 +x%></td>
          <td width="122">&nbsp;<%=MaxScale%></td>
        </tr>
      </table>
    </td>
  </tr>
</table>
