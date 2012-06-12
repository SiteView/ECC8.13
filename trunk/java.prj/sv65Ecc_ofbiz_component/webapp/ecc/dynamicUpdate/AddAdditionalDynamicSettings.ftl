<p><H1>Add</H1>

<FORM ACTION="<@ofbizUrl>saveSetting</@ofbizUrl>" method=POST>


<TABLE cellspacing="0" class="basic-table">
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Template Set: 
	<input type="hidden" name=id size=50 value=${result._id}>
	</TD>
	  <TD ALIGN=LEFT VALIGN=TOP>
			<select size=1 name=set><option value=.svn>.svn</option>
				<option value=PingAndSnmpByMIB.mset>PingAndSnmpByMIB.mset</option>
				<option value=PingAndSnmpByMIB.mset.bak>PingAndSnmpByMIB.mset.bak</option>
				<option value=PingGroup.mset>PingGroup.mset</option>
			</select>
	  </TD>
	 <TD><span class="tooltip">Select the Monitor Set Template used to create new monitors.</span>
	 </TD>

</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Monitor Set Subgroup Name: 
	</TD>
	<TD ALIGN=LEFT VALIGN=TOP>
	<input type=text name=groupSet size=50 value=${result._groupSet}>
	</TD>
	<TD>
		<span class="tooltip">Monitor group name to be assigned to each set of monitors created using the above template. Default is IP address. Enter an optional text string to be appended to default name.
		</span>
	</TD>

</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Group Name:
		 </TD>

	 <TD ALIGN=LEFT VALIGN=TOP><input type=text name=group size=50 value=${result._group}>
	 </TD>

	 <TD>
		 <span class="tooltip">Enter a name for the group to be created to contain all subgroups created using the template selected above.
		</span>
	 </TD>

 </TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>SiteView Parent Group: </TD>
	<TD ALIGN=LEFT VALIGN=TOP>
		<select size=1 name=parent>
			<option value="">-- SiteView Panel -- </option>
			<option  value="__Health__">Health (__Health__) </option>
			<option  value="11">11 (11) </option>
			<option  value="11.1">11 (11.1) </option>
			<option  value="Group0.3">Group0.3 (Group0.3) </option>
			<option  value="group1">Group0.3: group1 (group1) </option>
			<option  value="pp">pp (pp) </option>
			<option  value="Group0">test (Group0) </option>
			<option  value="Group0.1">test: testsub1 (Group0.1) </option>
		</select>
	</TD>

	<TD>
		<span class="tooltip">Select an existing SiteView group to which the above container group will be added as a subgroup. Choose <tt>SiteView Panel</tt> to create a new group on the SiteView Main Panel
		</span>
	</TD>

</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Update Frequency: 
	</TD>

	<TD ALIGN=LEFT VALIGN=TOP><input type=text name=frequency size=50 value=${result._frequency}>
	</TD>

	<TD>
		<span class="tooltip">Frequency (in seconds) that SiteView will query the MIB or database for new nodes and create monitor sets for new nodes.
		</span>
	</TD>

</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Exclude IP: 
	</TD>

	<TD ALIGN=LEFT VALIGN=TOP><input type=text name=excludeIP size=50 value=${result._excludeIP}>
	</TD>

	<TD>
		<span class="tooltip">Enter IP addresses to be excluded from the Update Set, for example, the default gateway IP. To exclude multiple IP address, separate them by commas
		</span>
	</TD>

</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Title: 
	</TD>

	<TD ALIGN=LEFT VALIGN=TOP><input type=text name=name size=50 value=${result._name}>
	</TD>
	<td>
	 <span class="tooltip">
		Optional title for this Dynamic Update Set. The default title is the server address
		</span>
	</td>

</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>
	</TD>
	<TD>
		<TABLE>
			<TR>
				<TD ALIGN=LEFT VALIGN=TOP>
				<HR><CENTER><H1>SNMP MIB Search</H1></CENTER>
				</TD>
			</TR>
			<TR>
				<TD>
					<FONT SIZE=-1>
					<p><font size=-1>The Dynamic Update can walk a SNMP MIB to find new IP Addresses and automatically create monitors for new servers.</font>
					</FONT>
				</TD>
			</TR>
		</TABLE>
	</TD>
	<TD><I></I>
	</TD>
</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Server Address: 
	</TD>

	<TD ALIGN=LEFT VALIGN=TOP><input type=text name=host size=50 value=${result._host}>
	</TD>

	<TD>
	<span class="tooltip">The server or console where the SNMP MIB is found. Enter the UNC style name (For example:<tt>\servername</tt>) or the IP address.
	</span>
	</TD>

</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>SNMP Object ID: </TD>

	<TD ALIGN=LEFT VALIGN=TOP>
		<select size=1 name=oid>
			<option value=BIGIP-4.1.1PoolIncluded-(1.3.6.1.4.1.3375.1.1.8.2.1.1)>BIGIP-4.1.1PoolIncluded-(1.3.6.1.4.1.3375.1.1.8.2.1.1)</option>
			<option value=other>other</option>
		</select>
		
	 Other: <INPUT TYPE=TEXT NAME=otheroid SIZE=50 VALUE=${result._otheroid}>
	</TD>

	<TD>
		<span class="tooltip">The root OID for the object that returns the node IP addresses to be monitored
		</span>
	</TD>

</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Pool Included</TD>

	<#if result._poolIncluded=="on">
		<TD ALIGN=LEFT VALIGN=TOP><input type=checkbox name=poolIncluded checked></td>
		<#else>
		<TD ALIGN=LEFT VALIGN=TOP><input type=checkbox name=poolIncluded >
		</TD>
		</#if>
	
		<TD><span class="tooltip">Check this if the pool IP Address is included in the result of the OID walk (Note: for F5 servers).
		</span>
		</TD>

</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Community: </TD>
	<TD ALIGN=LEFT VALIGN=TOP><input type=text name=community size=50 value=${result._community}></TD>
	<TD><span class="tooltip">The community variable for the SNMP MIB. The default is <tt>public</tt></span></TD>

</TR>

<TR>
	<TD ALIGN=RIGHT VALIGN=TOP></TD>
	<TD>
		<TABLE>
			<TR>
				<TD ALIGN=LEFT VALIGN=TOP>
				<HR>
				<CENTER><H1>Database Search</H1></CENTER>
				</TD>
			</TR>
			<TR>
				<TD>
					<FONT SIZE=-1><p><font size=-1>The Dynamic Update can query a database table to find new IP Addresses and automatically create monitors for new servers.</font>
					</FONT>
				</TD>
			</TR>
		</TABLE>
	</TD>
	<TD><I></I></TD>
</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Database Connection URL: </TD>
	<TD ALIGN=LEFT VALIGN=TOP><input type=text name=dbConnectionURL size=50 value=${result._dbConnectionURL}></TD>
	<TD>
		<span class="tooltip">Enter the URL to the database connection (for example,jdbc:inetdae:myserver.mycompany.com:1433?database=master)
		</span>
	</TD>

</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Database Driver: </TD>
	<TD ALIGN=LEFT VALIGN=TOP>    <input type=text name=dbDriver size=40 value=${result._dbDriver}>  </TD>
	<TD><span class="tooltip">Driver used to connect to the database (for example, com.inet.tds.TdsDriver)</span>	</TD>
</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>SQL Query: </TD>
	<TD ALIGN=LEFT VALIGN=TOP>          <input type=text name=dbSqlQuery size=40 value=${result._dbSqlQuery}>  </TD>
	<TD><span class="tooltip">SQL query to run against a table in the database that returns the list of IP addresses to be monitored.</span>
	</TD>
</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Database Username: </TD>
	<TD ALIGN=LEFT VALIGN=TOP>  <input type=text name=dbUserName size=40 value=${result._dbUserName}>  </TD>
	<TD><span class="tooltip">Enter the username for connecting to the database.</span>	</TD>
</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Database Password: </TD>
	<TD ALIGN=LEFT VALIGN=TOP>  <input type=password name=dbPassword value=${result._dbPassword} size=40> 
	</TD>
	<TD><span class="tooltip">Enter the password used to connect to the database.</span></TD>
</TR>

<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Connection Timeout: </TD>
	<TD ALIGN=LEFT VALIGN=TOP>  <input type=text name=dbConnectTimeout size=40 value=${result._dbConnectTimeout}>  </TD>
	<TD><span class="tooltip">Connection timeout to use for the database.</span></TD>
</TR>
<TR>
	<TD ALIGN=RIGHT VALIGN=TOP>Query Timeout: </TD>
	<TD ALIGN=LEFT VALIGN=TOP>      <input type=text name=dbQueryTimeout size=40 value=${result._dbQueryTimeout}></TD> 
	<TD><span class="tooltip">Query timeout to use for the database.</span></TD>
</TR>

</TABLE>
<TABLE WIDTH=100%><TR><TD><input type=submit value="Add"> <span class="tooltip">Dynamic Update Set Definition</span>
</TD></TR></TABLE>

