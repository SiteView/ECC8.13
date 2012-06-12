/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.ProcessUtils;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

// Referenced classes of package com.dragonflow.ProcessUtils:
// WaitForInputEvents
public class WaitForInput implements java.lang.Runnable {

    public static final int STATUS_RECEIVED = 0;

    public static final int STATUS_TIMEOUT = 1;

    public static final int STATUS_ERROR = 2;

    private java.io.InputStream in;

    java.lang.String waitString;

    java.lang.String timeoutString;

    com.dragonflow.ProcessUtils.WaitForInputEvents events;

    public WaitForInput(java.io.InputStream inputstream, java.lang.String s, java.lang.String s1, com.dragonflow.ProcessUtils.WaitForInputEvents waitforinputevents) {
        waitString = "";
        timeoutString = "";
        events = null;
        in = inputstream;
        waitString = s;
        timeoutString = s1;
        events = waitforinputevents;
    }

    public void run() {
        java.io.BufferedReader bufferedreader;
        try {
            bufferedreader = com.dragonflow.Utils.FileUtils.MakeInputReader(in);
        } catch (java.io.IOException ioexception) {
            com.dragonflow.Log.LogManager.log("Error", "WaitForInput: Failed to get the stdin, exception: " + ioexception.getMessage());
            events.onInputReceived(2);
            return;
        }
        java.lang.String s;
        do {
            try {
                s = bufferedreader.readLine();
            } catch (java.io.IOException ioexception1) {
                com.dragonflow.Log.LogManager.log("Error", "WaitForInput: Failed to read line, exception: " + ioexception1.getMessage());
                events.onInputReceived(2);
                return;
            }
            if (s == null) {
                events.onInputReceived(2);
                return;
            }
            if (s.equals(waitString)) {
                events.onInputReceived(0);
                return;
            }
        } while (!s.equals(timeoutString));
        events.onInputReceived(1);
    }
}
