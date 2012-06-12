/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.HTTP;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.RandomAccessFile;
import java.util.Date;

import com.siteview.ecc.api.APIEntity;

// Referenced classes of package com.dragonflow.HTTP:
// HTTPRequestHandler, HTTPRequestException, HTTPRequest, HTTPServer,
// VirtualDirectory

public class DocumentRequestHandler extends com.dragonflow.HTTP.HTTPRequestHandler {

    com.dragonflow.HTTP.HTTPServer httpServer;

    static boolean debug = false;

    static String bannerSuffix = "banner.gif";

    static int maxAds = 10;

    public DocumentRequestHandler(com.dragonflow.HTTP.HTTPServer httpserver) {
        httpServer = httpserver;
    }

    String randomAd(com.dragonflow.HTTP.VirtualDirectory virtualdirectory, String s) {
        int i = (int) (Math.random() * (double) maxAds) + 1;
        s = s.substring(0, s.length() - bannerSuffix.length()) + "banner" + i + ".gif";
        return s;
    }

    void printReportPage(java.io.PrintWriter printwriter, String s, com.dragonflow.HTTP.HTTPRequest httprequest) throws Exception {
        int i = s.indexOf("/accounts");
        int j = s.indexOf("/htdocs");
        if (i != -1 && j != -1) {
            s = s.substring(0, i) + s.substring(j);
        }
        String s1 = com.dragonflow.Utils.FileUtils.readFile(s).toString();
        if (!httprequest.getAccount().equals("administrator") && !httprequest.getAccount().equals("user") && s.endsWith(".html")) {
            if (!httprequest.actionAllowed("_reportGenerate")) {
                int k = s1.indexOf("<FORM");
                if (k != -1) {
                    int l = s1.indexOf("<CENTER>", k);
                    if (l != -1) {
                        s1 = s1.substring(0, k) + s1.substring(l);
                    }
                }
            }
            s1 = com.dragonflow.Utils.TextUtils.replaceString(s1, "/SiteView/htdocs/Reports-", "/SiteView/accounts/" + httprequest.getAccount() + "/htdocs/Reports-");
            s1 = com.dragonflow.Utils.TextUtils.replaceString(s1, "/SiteView/accounts/administrator/htdocs", "/SiteView/accounts/" + httprequest.getAccount() + "/htdocs");
            s1 = com.dragonflow.Utils.TextUtils.replaceString(s1, "/SiteView/htdocs/SiteView.html", "/SiteView/accounts/" + httprequest.getAccount() + "/htdocs/SiteView.html");
            s1 = com.dragonflow.Utils.TextUtils.replaceString(s1, "name=account value=administrator", "name=account value=" + httprequest.getAccount());
            s1 = com.dragonflow.Utils.TextUtils.replaceString(s1, "account=administrator", "account=" + httprequest.getAccount());
        }
        printwriter.print(s1);
    }

    public void handleRequest(com.dragonflow.HTTP.HTTPRequest httprequest) throws Exception {
        String s = httprequest.getURL();
        if (s.endsWith("/")) {
            s = s + "index.html";
        }
        VirtualDirectory virtualdirectory = httpServer.getVirtualDirectory(s);
        String filename = null;
        if (virtualdirectory != null) {
            filename = virtualdirectory.getFullDocumentPath(s);
        }
        if (filename == null) {
            throw new HTTPRequestException(404, s);
        }
        if (debug) {
            System.out.println("DOCUHANDLER - got docpath = " + filename);
        }
        if (filename.indexOf("..") != -1 && com.dragonflow.SiteView.Platform.getRoot().indexOf("..") == -1) {
            throw new HTTPRequestException(403, s);
        }
        boolean flag = false;
        filename = com.dragonflow.Utils.I18N.StringToUnicode(com.dragonflow.HTTP.HTTPRequest.decodeString(filename));
        if (filename.indexOf("/logs/") != -1) {
            if (debug) {
                System.out.println("DOCUHANDLER - docpath is a log = " + filename);
            }
            com.dragonflow.HTTP.HTTPRequest _tmp = httprequest;
            com.dragonflow.HTTP.HTTPRequest.noCache = true;
            if (httprequest.isStandardAccount()) {
                if (!httprequest.actionAllowed("_logs")) {
                    throw new HTTPRequestException(557);
                }
                if (!httprequest.getAccount().equals("administrator")) {
                    int i = filename.indexOf("/accounts");
                    int j = filename.indexOf("/logs");
                    if (i != -1 && j != -1) {
                        filename = filename.substring(0, i) + filename.substring(j);
                    }
                }
            }
            if (httprequest.getValue("xml").length() > 0) {
                flag = true;
            }
        }
        java.io.File file = null;
        java.util.Date date = new Date();
        boolean flag1 = httprequest.isStandardAccount() && filename.indexOf("/htdocs/Reports-") != -1;
        int k = filename.lastIndexOf('.');
        String s2 = "text/plain";
        if (k >= 0) {
            s2 = httpServer.getType(filename.substring(k));
        }
        if (flag1 && s2.startsWith("image")) {
            if (debug) {
                System.out.println("DOCUHANDLER - docpath is an image = " + filename);
            }
            flag1 = false;
        }
        if (!flag && !flag1 && filename.indexOf("/SiteView.html") == -1 && filename.indexOf("/Progress.html") == -1 && filename.indexOf("/Reports.html") == -1 && filename.indexOf("/Detail") == -1) {
            boolean flag2 = false;
            if (filename.indexOf(bannerSuffix) != -1) {
                filename = randomAd(virtualdirectory, filename);
                flag2 = true;
            }
            if (!com.dragonflow.SiteView.Platform.isSiteSeerServer()) {
                int l = filename.indexOf("/accounts");
                int i1 = filename.indexOf("/htdocs");
                if (l != -1 && i1 != -1) {
                    filename = filename.substring(0, l) + filename.substring(i1);
                }
            }
            if (debug) {
                System.out.println("DOCUHANDLER - making file from = " + filename);
            }
            file = new File(filename);
            if (!file.exists() ) {
                throw new HTTPRequestException(404, s);
            }
            if (!file.canRead() ) {
                throw new HTTPRequestException(403, s);
            }
            if (!file.isFile() ) {
                throw new HTTPRequestException(404, s);
            }
            if (!flag2) {
                date = new Date(file.lastModified());
            }
        }
        httprequest.setLastModified(date);
        if (!httprequest.hasBeenModified(date)) {
            httprequest.setStatus(304);
            httprequest.printHeader(outputStream);
            return;
        }
        try {
            String s3 = new String("<pre>\n");
            httprequest.setContentType(s2);
            if (file == null) {
                if (debug) {
                    System.out.println("DOCUHANDLER - file is null - calling printSpecial");
                }
                com.dragonflow.HTTP.HTTPRequest _tmp1 = httprequest;
                com.dragonflow.HTTP.HTTPRequest.noCache = true;

				httprequest.printHeader(outputStream);
                com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.cCurrentSiteView;
                if (siteviewgroup != null) {
                    siteviewgroup.printSpecial(filename, outputStream, httprequest);
                }
            } else if (filename.indexOf("SiteView/docs/") != -1 && !s2.startsWith("image")) {
                if (debug) {
                    System.out.println("DOCUHANDLER - document type " + s2 + " for " + filename);
                    System.out.println("DOCUHANDLER - file in docs - handling help file " + filename);
                }
                long l1 = file.length();
                httprequest.setContentLength(-1L);
                httprequest.printHeader(outputStream);
                boolean flag3 = false;
                outputStream.flush();
                java.io.FileInputStream fileinputstream = new FileInputStream(file);
                java.io.BufferedReader bufferedreader = com.dragonflow.Utils.FileUtils.MakeEncodedInputReader(fileinputstream, "");
                Object obj = null;
                if (s2.equals("application/pdf")) {
                    byte abyte0[] = new byte[20480];
                    for (int j2 = -1; (j2 = fileinputstream.read(abyte0, 0, abyte0.length)) != -1;) {
                        rawOutput.write(abyte0, 0, j2);
                    }

                } else {
                    do {
                        String s7 = bufferedreader.readLine();
                        if (s7 == null) {
                            break;
                        }
                        outputStream.println(s7);
                    } while (true);
                }
                fileinputstream.close();
                outputStream.flush();
                httprequest.setBytesTransferred((int) l1);
            } else {
                if (debug) {
                    System.out.println("DOCUHANDLER - file is not null - handle file");
                }
                long l2 = file.length();
                httprequest.entityLength = l2;
                if (httprequest.getValue("addPre").length() > 0) {
                    l2 += s3.length();
                }
                String s4 = httprequest.byteRange;
                String s6 = "bytes=";
                if (s4.length() > 0 && s4.startsWith(s6) && s4.indexOf("-") != -1) {
                    s4 = s4.substring(s6.length());
                    int j1 = s4.indexOf("-");
                    s4 = s4.substring(0, j1);
                    long l3 = com.dragonflow.Utils.TextUtils.toInt(s4);
                    if (l3 >= 0L) {
                        httprequest.rangeStart = l3;
                        httprequest.setStatus(206);
                        l2 -= l3;
                        if (l2 < 0L) {
                            l2 = 0L;
                        } else {
                            String s5 = httprequest.byteRange;
                            int k1 = s5.indexOf("-");
                            s5 = s5.substring(k1 + 1);
                            long l4 = com.dragonflow.Utils.TextUtils.toInt(s5);
                            if (s5.length() > 0 && l4 >= l3) {
                                l2 = (l4 - l3) + 1L;
                                if (l2 + l3 > file.length()) {
                                    l2 = file.length() - l3;
                                }
                            } else {
                                com.dragonflow.SiteView.SiteViewGroup siteviewgroup1 = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                                int j3 = com.dragonflow.Utils.TextUtils.toInt(siteviewgroup1.getSetting("_maxFileTransferSize"));
                                if (j3 < 30000) {
                                    j3 = 0x7a120;
                                }
                                if (l2 > (long) j3) {
                                    l2 = j3;
                                }
                            }
                        }
                    }
                }
                httprequest.setContentLength(l2);
                httprequest.printHeader(outputStream);
                int i2 = 0;
                outputStream.flush();
                if (!httprequest.isHEADRequest()) {
                    if (debug) {
                        System.out.println("DOCUHANDLER - not HEAD request sending file down rawOutput");
                    }
                    char c = '\u7800';
                    byte abyte1[] = new byte[c];
                    if (httprequest.rangeStart >= 0L) {
                        if (debug) {
                            System.out.println("DOCUHANDLER - not HEAD request sending down rawOutput by a range " + file);
                        }
                        java.io.RandomAccessFile randomaccessfile = new RandomAccessFile(file, "r");
                        randomaccessfile.seek(httprequest.rangeStart);
                        do {
                            int k2 = randomaccessfile.read(abyte1);
                            if (k2 == -1) {
                                break;
                            }
                            if ((long) k2 > l2 - (long) i2) {
                                k2 = (int) (l2 - (long) i2);
                            }
                            rawOutput.write(abyte1, 0, k2);
                            i2 += k2;
                        } while ((long) i2 < l2);
                        randomaccessfile.close();
                    } else {
                        if (debug) {
                            System.out.println("DOCUHANDLER - not HEAD request sending entire file " + file);
                        }
                        java.io.FileInputStream fileinputstream1 = new FileInputStream(file);
                        boolean flag4 = true;
                        do {
                            int i3 = fileinputstream1.read(abyte1);
                            if (i3 == -1) {
                                break;
                            }
                            if (flag4 && httprequest.getValue("addPre").length() > 0) {
                                byte abyte2[] = s3.getBytes();
                                rawOutput.write(abyte2, 0, abyte2.length);
                                i2 += abyte2.length;
                                flag4 = false;
                            }
                            rawOutput.write(abyte1, 0, i3);
                            i2 += i3;
                        } while (true);
                        fileinputstream1.close();
                    }
                }
                httprequest.setBytesTransferred(i2);
            }
        } catch (java.io.FileNotFoundException filenotfoundexception) {
            throw new HTTPRequestException(404, s);
        } catch (java.io.IOException ioexception) {
            throw new HTTPRequestException(501, s);
        }
    }

    static {
        String s = System.getProperty("DocumentRequestHandler.debug");
        if (s != null && s.length() > 0) {
            debug = true;
        }
    }
}