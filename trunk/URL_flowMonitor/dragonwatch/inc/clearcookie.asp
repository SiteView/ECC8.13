<%
' �����COOKIE�������
response.cookies("rep_cust")("name")="" ' �û�����rep_cust_name
response.cookies("rep_cust")("id")="" ' �û�ID��rep_cust_id
response.cookies("rep_prf")("id")="" ' Ԥ�����ļ���ţ�rep_prf_id
response.cookies("rep_prf")("name")="" ' Ԥ�����ļ�����rep_prf_name
response.cookies("rep_per")="" ' ��λ��rep_per
response.cookies("rep_by")="" ' ���鷽ʽ��rep_by
response.cookies("rep_datetime")("start")="" ' ��ʼ����ʱ�䣺rep_startDate
response.cookies("rep_startTime")="" ' ��ʼ����ʱ�䣺rep_startDate
response.cookies("rep_datetime")("end")="" ' ��ֹ����ʱ�䣺rep_endDate
response.cookies("rep_trans")("id")="" ' ҵ������ID��rep_transid
response.cookies("rep_trans")("name")="" ' ҵ���������ƣ�rep_transname
response.cookies("rep_city")("id")=""
response.cookies("rep_city")("name")=""
response.cookies("curr_link")="" ' ��ǰ����
response.cookies("rep_alert_currpage")="" ' ��ǰҳ��
response.cookies("visit")="" ' �û��Ƿ��¼

response.Cookies("rep_all_failure")("id") = ""
response.Cookies("rep_all_failure")("name") = ""
response.Cookies("rep_sel_failure")("id") = ""
%>