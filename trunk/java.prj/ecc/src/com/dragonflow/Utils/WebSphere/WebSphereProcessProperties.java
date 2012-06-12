/*
 * 
 * Created on 2005-3-9 18:55:36
 *
 * PDHRawCounterCache.java
 *
 * History:
 *
 */
package com.dragonflow.Utils.WebSphere;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Properties;

// Referenced classes of package com.dragonflow.Utils.WebSphere:
// ProcessWaiter, ReaderThread, WebSphereProcessLauncher

public class WebSphereProcessProperties {

    private static long siteViewToken = java.lang.System.currentTimeMillis();

    private static java.util.Properties props;

    private static java.lang.String propsFilename;

    private static boolean enableDebugPrintouts = false;

    private static long heartBeatFrequency;

    public static final int VERSION_3_5 = 0;

    public static final int VERSION_4_X = 1;

    public static final int VERSION_5_X = 2;

    public static final java.lang.String VERSION_3_5_STR = "3.5x";

    public static final java.lang.String VERSION_4_X_STR = "4.x";

    public static final java.lang.String VERSION_5_X_STR = "5.x";

    private java.lang.String hostname;

    private java.lang.String classpath;

    private java.lang.String webSphereDir;

    private java.lang.String clientProps;

    private java.lang.String jvmName;

    private java.lang.String api;

    private int hashKey;

    private boolean isWindows;

    private boolean isRunning;

    private java.lang.Process proc;

    private int version;

    private static final java.lang.String WEBSPHERE_SERVICE_CLASSNAME = "com.dragonflow.Utils.WebSphere.WebSphereServiceImpl";

    private static final java.lang.String CODEBASE;

    private static final java.lang.String HOSTNAME = "localhost";

    private static final java.lang.String FILE_SEP = java.lang.System.getProperties().getProperty("file.separator");

    private static final java.lang.String PATH_SEP = java.lang.System.getProperties().getProperty("path.separator");

    public WebSphereProcessProperties(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, boolean flag, java.lang.String s4) {
        clientProps = "sas.client.props";
        isRunning = false;
        hostname = s4.toLowerCase();
        classpath = s;
        webSphereDir = s2;
        isWindows = flag;
        setJVMName();
        setClientProps(s1, flag);
        detectVersion(s3);
        detectAPI(version);
        augmentClasspath();
        if (version == 1) {
            hashKey = (webSphereDir + classpath + version + clientProps + hostname).hashCode();
        } else {
            hashKey = (webSphereDir + classpath + version + clientProps).hashCode();
        }
    }

    private void setClientProps(java.lang.String s, boolean flag) {
        if (s == null || s.length() == 0) {
            s = clientProps;
        }
        s = s.replace('\\', '/');
        if (s.charAt(0) != '/' && s.charAt(0) != ':') {
            s = webSphereDir.replace('\\', '/') + "/properties/" + s;
        }
        if (flag) {
            s = "/" + s;
        }
        clientProps = s;
    }

    public java.lang.String getURL() {
        java.lang.StringBuffer stringbuffer = (new StringBuffer("rmi://")).append("localhost").append(":").append(com.dragonflow.Utils.WebSphere.WebSphereProcessLauncher.getRegistryPort());
        stringbuffer.append("/WebSphereService").append(hashKey);
        return stringbuffer.toString();
    }

    private void setJVMName() {
        if (isWindows) {
            jvmName = "javaw.exe";
        } else {
            jvmName = "java";
        }
    }

    private void detectAPI(int i) {
        switch (i) {
        case 1: // '\001'
            api = "PMI";
            break;

        case 2: // '\002'
            api = "JMX";
            break;
        }
    }

    private void detectVersion(java.lang.String s) {
        if (s.equals("4.x")) {
            version = 1;
        } else {
            version = 2;
        }
    }

    private void augmentClasspath() {
        java.lang.StringBuffer stringbuffer = new StringBuffer(classpath);
        if (stringbuffer.length() > 0) {
            stringbuffer.append(PATH_SEP);
        }
        stringbuffer.append(".").append(PATH_SEP).append("..").append(FILE_SEP).append("classes");
        int i = 1;
        do {
            java.lang.String s = props.getProperty("classpath" + api + i);
            if (s == null) {
                break;
            }
            stringbuffer.append(PATH_SEP + webSphereDir + FILE_SEP + "lib" + FILE_SEP + s);
            i ++;
        } while (true);
        i = 1;
        do {
            java.lang.String s1 = props.getProperty("properties" + api + i);
            if (s1 != null) {
                stringbuffer.append(PATH_SEP + webSphereDir + FILE_SEP + "properties" + FILE_SEP + s1);
                i ++;
            } else {
                classpath = stringbuffer.toString();
                return;
            }
        } while (true);
    }

    public java.lang.String getCommandLine() {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.String as[] = getCommandLineArray();
        for (int i = 0; i < as.length; i ++) {
            stringbuffer.append(as[i]).append(" ");
        }

        return stringbuffer.toString();
    }

    public java.lang.String[] getCommandLineArray() {
        int i = webSphereDir.length();
        if (i > 0 && webSphereDir.charAt(i - 1) == '\\') {
            webSphereDir = webSphereDir.substring(0, i - 1);
        }
        java.lang.String s = webSphereDir + FILE_SEP + "java" + FILE_SEP + "jre" + FILE_SEP + "bin" + FILE_SEP + jvmName;
        java.lang.String s1 = getClass().getPackage().getName();
        java.util.ArrayList arraylist = new ArrayList();
        arraylist.add(s);
        arraylist.add("-classpath");
        arraylist.add(classpath);
        arraylist.add("-Djava.rmi.server.codebase=" + CODEBASE);
        arraylist.add("-Djava.rmi.server.hostname=localhost");
        arraylist.add("-D" + s1 + "." + "registryURL" + "=" + getURL());
        arraylist.add("-D" + s1 + "." + "heartBeatFrequency" + "=" + heartBeatFrequency);
        arraylist.add("-D" + s1 + "." + "token" + "=" + siteViewToken);
        arraylist.add("-Dcom.ibm.CORBA.ConfigURL=file:" + clientProps);
        arraylist.add("-Dcom.ibm.SOAP.ConfigURL=file:" + clientProps);
        java.lang.String s2 = java.lang.System.getProperty("com.dragonflow.Utils.WebSphere.remoteDebugger");
        if (s2 != null && s2.equalsIgnoreCase("true")) {
            arraylist.add("-Xdebug");
            arraylist.add("-Xnoagent");
            arraylist.add("-Djava.compiler=NONE");
            arraylist.add("-Xrunjdwp:transport=dt_socket,server=y,suspend=n,address=5005");
        }
        if (enableDebugPrintouts) {
            arraylist.add("-D" + s1 + "." + "debug" + "=true");
        }
        arraylist.add("com.dragonflow.Utils.WebSphere.WebSphereServiceImpl");
        java.lang.String as[] = new java.lang.String[arraylist.size()];
        as = (java.lang.String[]) arraylist.toArray(as);
        return as;
    }

    public java.lang.String getClasspath() {
        return classpath;
    }

    public java.lang.String getWebSphereDir() {
        return webSphereDir;
    }

    public int getVersion() {
        return version;
    }

    public boolean isWindows() {
        return isWindows;
    }

    public java.lang.String getJvmName() {
        return jvmName;
    }

    public java.lang.String getApi() {
        return api;
    }

    public java.lang.Process getProcess() {
        return proc;
    }

    public void registerNewProcess(java.lang.Process process) {
        isRunning = true;
        proc = process;
        com.dragonflow.Utils.WebSphere.ProcessWaiter processwaiter = new ProcessWaiter(this);
        processwaiter.start();
        java.lang.String s = "WebSphereService[" + hashKey + "]: ";
        java.io.BufferedReader bufferedreader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        com.dragonflow.Utils.WebSphere.ReaderThread readerthread = new ReaderThread(bufferedreader, "RunMonitor", s);
        readerthread.start();
        java.io.BufferedReader bufferedreader1 = new BufferedReader(new InputStreamReader(process.getErrorStream()));
        com.dragonflow.Utils.WebSphere.ReaderThread readerthread1 = new ReaderThread(bufferedreader1, "Error", s);
        readerthread1.start();
    }

    public int getHashKey() {
        return hashKey;
    }

    public java.lang.Integer getHashKeyAsInteger() {
        return new Integer(hashKey);
    }

    public boolean isRunning() {
        return isRunning;
    }

    protected void setRunning(boolean flag) {
        isRunning = flag;
    }

    static {
        props = new Properties();
        propsFilename = com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "templates.applications" + java.io.File.separator + "websphere.props";
        heartBeatFrequency = 3000L;
        try {
            props.load(new FileInputStream(propsFilename));
        } catch (java.lang.Exception exception) {
            com.dragonflow.Log.LogManager.log("Error", "Cannot open Websphere properties file: " + propsFilename);
        }
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        if (com.dragonflow.Utils.TextUtils.getValue(hashmap, "_webSphereDebug").length() > 0) {
            enableDebugPrintouts = true;
        }
        java.lang.String s = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_webSphereServiceHeartBeatFrequency");
        if (s.length() > 0) {
            try {
                heartBeatFrequency = java.lang.Long.parseLong(s);
            } catch (java.lang.NumberFormatException numberformatexception) {
                heartBeatFrequency = 3000L;
                com.dragonflow.Log.LogManager.log("Error", "Could not parse a number from _webSphereServiceHeartBeatFrequency=" + s + ".  Using the default of " + heartBeatFrequency);
            }
        }
        CODEBASE = "file:/" + com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "classes" + java.io.File.separator;
    }
}
