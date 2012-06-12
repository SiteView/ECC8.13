<%
sub RT(s)
	response.write s
end sub
'如果Cookie丢失,用户重新登录
if Not Len(Request.cookies("rep_cust_id")) > 0 then 
	RT "<html>"
	RT "<body>"
	RT "<P>&nbsp;</P>"
	RT "<Center><a href='../'>重新登录...</a></Center>"
	RT "</body>"
	RT "</html>"
	response.end
end if
%>