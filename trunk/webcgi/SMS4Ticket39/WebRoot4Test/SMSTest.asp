<%
  dim smallCode, srcMobile, destMobile, content, linkId, workFlage, user, password
  smallCode = request.querystring("smallCode")
  srcMobile = request.querystring("srcMobile")
  destMobile = request.querystring("destMobile")
  content = request.querystring("content")
  linkId = request.querystring("linkId")
  workFlage = request.querystring("workFlage")
  user = request.querystring("user")
  password = request.querystring("password")
  if smallCode = "" then
%>
��������
<%
  else
%>
���Ų���
smallCode=<%=smallCode%>
srcMobile=<%=srcMobile%>
destMobile=<%=destMobile%>
content=<%=content%>
linkId=<%=linkId%>
workFlage=<%=workFlage%>
user=<%=user%>
password=<%=password%>

<%
  end if
%>