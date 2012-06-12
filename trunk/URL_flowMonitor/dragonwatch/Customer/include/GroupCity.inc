<%
sub InsertCity(custid,tranid,cityid,conn)
	sE=chr(13) & chr(10) & "if @@error <> 0" & chr(13) & chr(10)
	sE=sE &	"begin" & chr(13) & chr(10)
	sE=sE &	"rollback" & chr(13) & chr(10)
	sE=sE &	"return" & chr(13) & chr(10)
	sE=sE &	"end" & chr(13) & chr(10)
	
	s1="INSERT INTO customertrancity(cust_id,trans_id,city_id) VALUES(" & custid & "," & tranid & "," & cityid & ")"
	s="begin transaction"
		s=s & chr(13) & chr(10) & s1 & sE
	''-----------------------------------------------------------------------------------------------------
	Set rs=Server.CreateObject("ADODB.recordset")
	sA="select a.agent_id from agent a where a.city_id = " & cityid '得到cityid对应的所有agent_id
	rs.open sA,conn,1,1
	Do until rs.Eof
		s2="INSERT INTO transactionagent(trans_id,agent_id) VALUES(" & tranid & "," & rs("agent_id") & ")"
		s=s & chr(13) & chr(10) & s2 & sE
		rs.MoveNext
	Loop
	''-----------------------------------------------------------------------------------------------------
	s=s & "if @@trancount > 0 commit"
	rs.close
	set rs=Nothing
	''response.write s
	conn.Execute(s)
end sub

sub DeleteCity(custid,tranid,cityid,conn)
	sE=chr(13) & chr(10) & "if @@error <> 0" & chr(13) & chr(10)
	sE=sE &	"begin" & chr(13) & chr(10)
	sE=sE &	"rollback" & chr(13) & chr(10)
	sE=sE &	"return" & chr(13) & chr(10)
	sE=sE &	"end" & chr(13) & chr(10)
	
	s1="DELETE FROM customertrancity WHERE cust_id = " & custid & " AND trans_id = " & tranid & " AND city_id = " & cityid
	s="begin transaction"
		s=s & chr(13) & chr(10) & s1 & sE
	''-----------------------------------------------------------------------------------------------------
	Set rs=Server.CreateObject("ADODB.recordset")
	sA="select a.agent_id from agent a where a.city_id = " & cityid '得到cityid对应的所有agent_id
	rs.open sA,conn,1,1
	Do until rs.Eof
		s2="DELETE FROM transactionagent WHERE trans_id = " & tranid & " AND agent_id = " & rs("agent_id")
		s=s & chr(13) & chr(10) & s2 & sE
		rs.MoveNext
	Loop
	''-----------------------------------------------------------------------------------------------------
	s=s & "if @@trancount > 0 commit"
	rs.close
	set rs=Nothing
	''response.write s
	conn.Execute(s)
end sub

%>