<%
REM -----直接引用Cookies("rep_all_failure")(key)------------------------------
REM -----但要注意 在ChooseProfile和注销处都要将其清空-------------------
strAllFailId = Request.Cookies("rep_all_failure")("Id")
strAllFailName = Request.Cookies("rep_all_failure")("Name")
strSelFailId = Request.Cookies("rep_sel_failure")("Id")

bAllFilterSelected = false
If Len(strSelFailId) = 0 then bAllFilterSelected = True

'-----------arrAll(x,1)--------------
arrAllFailId = split(strAllFailId,",")
arrAllFailName = split(strAllFailName,",")

'-----------arrSel(x,1)--------------
arrSelFailId = split(strSelFailId,",")

%>
<FORM METHOD="POST" ACTION="tran_failReason_filter_response.asp" NAME="frmFilters">
  <div class=TabsDivs id=TranFilters style="LEFT: 20px; OVERFLOW: auto; POSITION: absolute; TOP: 10px; WIDTH: 360px; Z-INDEX: 10; background-color: #FFFFFF; layer-background-color: #FFFFFF;visibility:hidden;"> 
  <table border=0 cellpadding=1 cellspacing=1 width=100%>
	<tbody> 
	<%
	For i=0 To UBound(arrAllFailId)
		Response.Write "<tr>"
			Response.write "<td><input name=chkTranFilter type=checkbox value='" & arrAllFailId(i) & "_" & arrAllFailName(i) & "'"
			'Whether be selected
			If bAllFilterSelected Then
				Response.Write " CHECKED"
			Else
				For j=0 To UBound(arrSelFailId)
					If CINT(arrAllFailId(i)) = CINT(arrSelFailId(j)) then
						Response.Write " CHECKED"
						Exit For
					End If
				Next
			End If
			Response.write "></td>"
			Response.write "<td><nobr>" & arrAllFailName(i) & "</nobr></td>"
			Response.write "<td width='100%'>&nbsp;</td>"
		Response.Write "</tr>"
	Next
	%>
	<INPUT TYPE="hidden" name="userSubmit" value="no">
	</tbody>
  </table>
</div>

<div class=TabsDivs id=LocFilters style="LEFT: 20px; OVERFLOW: auto; POSITION: absolute; TOP: 10px; WIDTH: 360px; Z-INDEX: 10; background-color: #FFFFFF; layer-background-color: #FFFFFF;visibility:hidden;"> 
  <table border=0 cellpadding=1 cellspacing=1 width=100%>
	<tbody> 
		<tr>
			<td><input name=chkLocFilter type=checkbox CHECKED></td>
			<td>&nbsp;</td>
			<td width='100%'>&nbsp;</td>
		</tr>
		<tr>
			<td><input name=chkLocFilter type=checkbox CHECKED></td>
			<td>&nbsp;</td>
			<td width='100%'>&nbsp;</td>
		</tr>
	</tbody>
  </table>
</div>
</FORM>
