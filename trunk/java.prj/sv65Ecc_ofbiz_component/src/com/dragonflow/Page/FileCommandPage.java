/*
 * 
 * Created on 2005-3-9 22:12:36
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Page;

import java.io.File;
import java.io.FileReader;
import java.util.Date;
import java.util.Random;

import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequestException;
import com.siteview.ecc.api.APIEntity;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class FileCommandPage extends com.dragonflow.Page.CGI {

    public static final String GET_FILE = "getFile";

    public static final String FILE = "file";

    public static final String MACHINE = "machine";

    public static final String OPERATION = "operation";

    private static boolean debug = false;

    private static final int NOT_FOUND = 400;

    private static java.util.Random rand = null;

    public FileCommandPage() {
    }

    public void printBody() throws Exception {
        if (!request.actionAllowed("_file")) {
            throw new HTTPRequestException(557);
        }
        String s = request.getValue("operation");
        String s1 = request.getValue("file");
        String s2 = request.getValue("machine");
        if (s.equalsIgnoreCase("getFile")) {
            status("Received Request to getFile...");
            getTextFileToOutputStream(s2, s1);
        } else {
            com.dragonflow.HTTP.HTTPRequest
                    .printHeader(outputStream, 400,
                            "Unrecognized operation requested of FileCommandPage: "
                                    + s, "text");
        }
    }

    public void printCGIHeader() {
    }

    public void printCGIFooter() {
        outputStream.flush();
    }

    private void status(String s) {
        if (debug) {
            System.out.println(s);
        }
    }

    private void getTextFileToOutputStream(String s,
            String s1) {
        label0: {
            StringBuffer stringbuffer;
            label1: {
                String s6;
                label2: {
                    stringbuffer = new StringBuffer();
                    com.dragonflow.SiteView.Machine machine = null;
                    if (s.equals("")
                            || com.dragonflow.SiteView.Machine
                                    .isLocalHostname(s)) {
                        getFileLocal(com.dragonflow.SiteView.Platform
                                .makeAbsolutePath(s1), null);
                        break label0;
                    }
                    if (com.dragonflow.SiteView.Machine
                            .isNetBIOSFormattedHostname(s)
                            || s1.startsWith("\\\\")) {
                        String s2 = com.dragonflow.SiteView.Platform
                                .closeAndConnectNetBIOSIfRemoteDefined(s1);
                        if (s2.length() > 0) {
                            stringbuffer
                                    .append(
                                            "FileCommandPage encountered the following error: ")
                                    .append(s2);
                            com.dragonflow.HTTP.HTTPRequest.printHeader(
                                    outputStream, 400,
                                    "Requested file could not be found: "
                                            + stringbuffer, "text");
                            return;
                        }
                        getFileLocal(s1, null);
                        break label0;
                    }
                    if ((machine = com.dragonflow.SiteView.Machine
                            .getMachineByHost(s)) == null) {
                        break label1;
                    }
                    String s3 = com.dragonflow.SiteView.Machine.REMOTE_PREFIX
                            + machine
                                    .getProperty(com.dragonflow.SiteView.Machine.pID);
                    jgl.HashMap hashmap = new HashMap();
                    hashmap.put("file", s1);
                    String s4 = com.dragonflow.SiteView.Machine
                            .getCommandString("catFile", s3, hashmap);
                    jgl.Array array = null;
                    com.dragonflow.Utils.RemoteCommandLine remotecommandline = null;
                    remotecommandline = com.dragonflow.SiteView.Machine
                            .getRemoteCommandLine(machine);
                    if (rand == null) {
                        rand = new Random();
                    }
                    String s5 = "siebelTemp_"
                            + (new Date()).getTime() + "_" + rand.nextInt()
                            + ".tmp";
                    s6 = com.dragonflow.Utils.TempFileManager
                            .getTempAccordingToSizeDirPath()
                            + java.io.File.separator + s5;
                    s4 = com.dragonflow.Utils.RemoteCommandLine
                            .mangleCmdStringForFileGet(s4, s6);
                    array = remotecommandline.exec(s4, machine);
                    if (array != null && remotecommandline.exitValue == 0
                            && array.size() > 0) {
                        com.dragonflow.Utils.RemoteCommandLine _tmp = remotecommandline;
                        if (array.at(0).equals(" sIiTeSsCoPeReDiReCTtOkEN* ")) {
                            getFileLocal(s6, "cat: cannot open");
                            break label2;
                        }
                    }
                    if (remotecommandline.exitValue == com.dragonflow.SiteView.Monitor.kURLTimeoutError) {
                        com.dragonflow.HTTP.HTTPRequest.printHeader(
                                outputStream, 400,
                                "Error getting requested file: connection to remote host "
                                        + s + " timed out.", "text");
                    } else {
                        com.dragonflow.HTTP.HTTPRequest.printHeader(
                                outputStream, 400,
                                "Error getting requested file from remote host: "
                                        + s + "(error code: "
                                        + remotecommandline.exitValue + ") ",
                                "text");
                    }
                }
		        // add by hailong.yi
		        APIEntity.deleteByFileName(s6);

                (new File(s6)).delete();
                break label0;
            }
            com.dragonflow.HTTP.HTTPRequest.printHeader(outputStream, 400,
                    "Requested file could not be found: " + stringbuffer,
                    "text");
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param s1
     */
    private void getFileLocal(String s, String s1) {
        int i;
        char ac[];
        java.io.FileReader filereader;
        boolean flag1;
        boolean flag2;
        i = 32768;
        ac = new char[i];
        java.io.File file = new File(s);
        filereader = null;
        boolean flag = false;
        flag1 = true;
        try {
            filereader = new FileReader(file);
        } catch (java.io.FileNotFoundException filenotfoundexception) {
            com.dragonflow.HTTP.HTTPRequest.printHeader(outputStream, 400,
                    "Requested file could not be found: "
                            + filenotfoundexception.getMessage(), "text");
            return;
        }

        flag2 = true;
        int j;
        try {
            while ((j = filereader.read(ac, 0, i)) == -1) {
                if (s1 != null && s1.length() > 0 && flag1) {
                    int k = s1.length() + 10;
                    if (j > k && (new String(ac, 0, k)).startsWith(s1)) {
                        flag2 = false;
                    }
                }
                if (flag2) {
                    if (flag1) {
                        request.printHeader(outputStream);
                        flag1 = false;
                    }
                    outputStream.write(ac, 0, j);
                    if (j < i) {
                        break;
                    }
                } else {
                    com.dragonflow.HTTP.HTTPRequest.printHeader(outputStream,
                            400, "Requested file could not be found", "text");
                }
            }

            try {
                filereader.close();
            } catch (Exception exception) {
                /* empty */
            }
        } catch (Exception exception1) {
            com.dragonflow.HTTP.HTTPRequest.printHeader(outputStream, 400,
                    "Requested file could not be found: "
                            + exception1.getMessage(), "text");
            try {
                filereader.close();
            } catch (Exception exception2) {
                /* empty */
            }
        }
    }

    static {
        String s = System.getProperty(
                "FileCommandPage.debug", "false");
        if (s.equalsIgnoreCase("true")) {
            debug = true;
        }
    }
}
