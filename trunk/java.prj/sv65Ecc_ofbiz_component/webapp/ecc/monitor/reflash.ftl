<script type="text/javascript" src="/svecc/yui/build/yuiloader/yuiloader-beta-min.js"></script>
<script type="text/javascript" src="/svecc/yui/build/event/event-min.js"></script>

<script type="text/javascript" src="/svecc/yui/build/dom/dom-min.js"></script>
<script type="text/javascript" src="/svecc/yui/build/logger/logger-min.js"></script>
<script type="text/javascript" src="/svecc/yui/build/json/json-debug.js"></script>
<script type="text/javascript" src="/svecc/yui/build/connection/connection-min.js"></script>
<script type="text/javascript" src="/svecc/yui/build/element/element-beta-min.js"></script>
<script type="text/javascript" src="/svecc/yui/build/button/button-min.js"></script>
<div id="reflash_msg"></div>
<script type="text/javascript">

//    YAHOO.util.Event.on(window,'load',function (e) {
    function reflash(groupId,id) {
    
    // Get the div element in which to report messages from the server
    var msg_section = YAHOO.util.Dom.get('reflash_msg');
    msg_section.innerHTML = 'Running...';

    // Define the callbacks for the asyncRequest
    var callbacks = {

        success : function (o) {
            YAHOO.log("RAW JSON DATA: " + o.responseText);

            // Process the JSON data returned from the server
            var messages = [];
            try {
                messages = YAHOO.lang.JSON.parse(o.responseText);
            }
            catch (x) {
                alert("JSON Parse failed!");
                return;
            }

            YAHOO.log("PARSED DATA: " + YAHOO.lang.dump(messages));

            // The returned data was parsed into an array of objects.
            // Add a P element for each received message
            msg_section.innerHTML = "";
            for (var i = 0, len = messages.length; i < len; ++i) {
                var m = messages[i];
                msg_section.innerHTML = m.message;
            }
        },

        failure : function (o) {
            if (!YAHOO.util.Connect.isCallInProgress(o)) {
                alert("Async call failed!");
            }
        },

        timeout : 30000
    }
    // Make the call to the server for JSON data
    YAHOO.util.Connect.asyncRequest('GET',"jsondataForMonitor?groupId=" + groupId + "&id=" + id + "", callbacks);
 };
</script>
