<ul>
<li>number of groups is <B>${num_of_groups}</B> </li>
<li>number of monitor is <B>${num_of_monitor} </B> </li>
<li>&nbsp</li>
</ul>


<link rel="stylesheet" type="text/css" href="/crmimages/yui/build/fonts/fonts-min.css" />
<link rel="stylesheet" type="text/css" href="/crmimages/yui/build/datatable/assets/skins/sam/datatable.css" />
<script type="text/javascript" src="/crmimages/yui/build/yahoo-dom-event/yahoo-dom-event.js"></script>
<script type="text/javascript" src="/crmimages/yui/build/dragdrop/dragdrop-min.js"></script>
<script type="text/javascript" src="/crmimages/yui/build/element/element-beta-min.js"></script>
<script type="text/javascript" src="/crmimages/yui/build/datasource/datasource-beta-min.js"></script>
<script type="text/javascript" src="/crmimages/yui/build/datatable/datatable-beta-min.js"></script>

<div id="monitorTable" class="yui-skin-sam"></div>

<script type="text/javascript"> 
	YAHOO.Data = {
    monitors: [
       	<#list monitors as monitor>
        	{GroupID:"${monitor.GroupID}", MonitorID:"${monitor.MonitorID}", Type:"${monitor.Type}", Name:"${monitor.Name}"},
    	</#list>
    ]
}
</script>
<script type="text/javascript">
YAHOO.util.Event.addListener(window, "load", function() {
    YAHOO.example.Basic = new function() {
        var myColumnDefs = [
            {key:"GroupID", sortable:true, resizeable:true},
            {key:"MonitorID", formatter:YAHOO.widget.DataTable.formatNumber, sortable:true, resizeable:true},
            {key:"Type",  sortable:true, resizeable:true},
            {key:"Name", sortable:true, resizeable:true}
        ];

        this.myDataSource = new YAHOO.util.DataSource(YAHOO.Data.monitors);
        this.myDataSource.responseType = YAHOO.util.DataSource.TYPE_JSARRAY;
        this.myDataSource.responseSchema = {
            fields: ["GroupID","MonitorID","Type","Name"]
        };

        this.myDataTable = new YAHOO.widget.DataTable("monitorTable",
                myColumnDefs, this.myDataSource, {caption:"<h3>Monitor List using Yahoo UI JS</h3>"});
    };
});
</script>
<ul>
          <li class="h3">Simple Monitor List</li>
</ul>
 
<table class="basic-table hover-bar" cellspacing='0'>
    <tr>
        <td><B>Group ID</B></td>
        <td><B>Monitor ID</B></td>
        <td><B>Type</B></td>
        <td><B>Name</B></td>
        <td><B>&nbsp</B></td>
     </tr>   

    <#list monitors as monitor>
    <tr>
        <td>${monitor.GroupID}</td>
        <td>${monitor.MonitorID}</td>
        <td>${monitor.Type}</td>
        <td>${monitor.Name}</td>
        <td class="button-col align-float">
            <a href="<@ofbizUrl>deleteMonitor?MonitorID=${monitor.MonitorID}</@ofbizUrl>" class="smallSubmit">Remove</a>&nbsp;
         </td>
     </tr>   
    </#list>
</table>
