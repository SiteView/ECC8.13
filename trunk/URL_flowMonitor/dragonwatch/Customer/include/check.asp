<%
sub RT(s)
	response.write s
end sub
'���Cookie��ʧ,�û����µ�¼
if Not Len(Request.cookies("rep_cust_id")) > 0 then 
	RT "<html>"
	RT "<body>"
	RT "<P>&nbsp;</P>"
	RT "<Center><a href='../'>���µ�¼...</a></Center>"
	RT "</body>"
	RT "</html>"
	response.end
end if
%>