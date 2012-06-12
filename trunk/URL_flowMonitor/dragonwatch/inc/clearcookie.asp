<%
' 清除掉COOKIE里的数据
response.cookies("rep_cust")("name")="" ' 用户名：rep_cust_name
response.cookies("rep_cust")("id")="" ' 用户ID：rep_cust_id
response.cookies("rep_prf")("id")="" ' 预定义文件编号：rep_prf_id
response.cookies("rep_prf")("name")="" ' 预定义文件名：rep_prf_name
response.cookies("rep_per")="" ' 单位：rep_per
response.cookies("rep_by")="" ' 分组方式：rep_by
response.cookies("rep_datetime")("start")="" ' 起始日期时间：rep_startDate
response.cookies("rep_startTime")="" ' 起始日期时间：rep_startDate
response.cookies("rep_datetime")("end")="" ' 终止日期时间：rep_endDate
response.cookies("rep_trans")("id")="" ' 业务流程ID：rep_transid
response.cookies("rep_trans")("name")="" ' 业务流程名称：rep_transname
response.cookies("rep_city")("id")=""
response.cookies("rep_city")("name")=""
response.cookies("curr_link")="" ' 当前链接
response.cookies("rep_alert_currpage")="" ' 当前页面
response.cookies("visit")="" ' 用户是否登录

response.Cookies("rep_all_failure")("id") = ""
response.Cookies("rep_all_failure")("name") = ""
response.Cookies("rep_sel_failure")("id") = ""
%>