/*
 * Created on 2005-2-9 3:06:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Utils;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

// Referenced classes of package COM.dragonflow.Utils:
// SMTP, TextUtils, LUtils, FileUtils
public class MailUtils {

    public MailUtils() {
    }

    public static void sendEmailWarning(java.lang.String s, java.lang.String s1) {
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
        java.lang.String s2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_autoEmail");
        if (s2.length() != 0 && s.length() > 0 && s1.length() > 0) {
            COM.dragonflow.Utils.MailUtils.mail(hashmap, s2, s, s1, "", null, false);
        }
    }

    public static java.lang.String mail(jgl.HashMap hashmap, java.lang.String s, java.lang.String s1, java.lang.String s2) {
        return COM.dragonflow.Utils.MailUtils.mail(hashmap, s, s1, s2, "");
    }

    public static java.lang.String mail(jgl.HashMap hashmap, java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3) {
        return COM.dragonflow.Utils.MailUtils.mail(hashmap, s, s1, s2, s3, null, true);
    }

    public static java.lang.String mail(jgl.HashMap hashmap, java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, jgl.Array array) {
        return COM.dragonflow.Utils.MailUtils.mail(hashmap, s, s1, s2, s3, array, true);
    }

    public static java.lang.String mail(jgl.HashMap hashmap, java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, jgl.Array array, boolean flag) {
        return COM.dragonflow.Utils.MailUtils.mail(hashmap, s, s1, s2, s3, array, flag, "");
    }

    public static java.lang.String mail(jgl.HashMap hashmap, java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, jgl.Array array, boolean flag, java.lang.String s4) {
        return COM.dragonflow.Utils.MailUtils.mail(hashmap, s, s1, s2, s3, array, flag, s4, null);
    }

    public static java.lang.String mail(jgl.HashMap hashmap, java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, jgl.Array array, boolean flag, java.lang.String s4, java.lang.String s5) {
        java.lang.String s6 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_mailServer");
        if (s6.length() == 0) {
            return "missing mail server";
        }
        java.lang.String s8 = COM.dragonflow.Utils.MailUtils.mail1(hashmap, s6, s, s1, s2, s3, array, flag, s4, s5);
        if (s8.length() != 0) {
            java.lang.String s7 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_mailServerBackup");
            if (s7.length() > 0) {
                COM.dragonflow.Log.LogManager.log("Error", "Using backup mail server (" + s8 + ") for " + s1 + " To: " + s);
                s8 = COM.dragonflow.Utils.MailUtils.mail1(hashmap, s7, s, s1, s2, s3, array, flag, s4, s5);
            }
        }
        return s8;
    }

    static java.lang.String mail1(jgl.HashMap hashmap, java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4, jgl.Array array, boolean flag, java.lang.String s5, java.lang.String s6) {
        java.lang.String s7 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_fromAddress");
        java.lang.String s8 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_smtpUser");
        java.lang.String s9 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_smtpPassword");
        s1 = COM.dragonflow.Utils.TextUtils.toEmailList(s1);
        if (s7.length() == 0) {
            java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s1, ",");
            if (as.length > 0) {
                s7 = as[0];
            }
        }
        java.lang.String s10 = COM.dragonflow.Utils.LUtils.getLicenseSummary(hashmap, true);
        if (s10.length() == 0) {
            s10 = COM.dragonflow.SiteView.Platform.productName + " from " + COM.dragonflow.SiteView.Platform.companyName;
        }
        java.lang.String s11 = "\n\n-----------------------------------------------------\n" + s10 + "\n" + "\n" + COM.dragonflow.SiteView.Platform.salesFooter + "-----------------------------------------------------\n\n";
        if (s7.indexOf("siteseer@") != -1) {
            s11 = "\n\n-----------------------------------------------------\nSiteSeer from " + COM.dragonflow.SiteView.Platform.companyName + "\n" + "\n" + COM.dragonflow.SiteView.Platform.salesFooter
                    + "-----------------------------------------------------\n\n";
            if (s5.length() > 0) {
                COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup) siteviewgroup.getElement(s5);
                if (monitorgroup != null) {
                    java.lang.String s14 = monitorgroup.getProperty("_customer");
                    if (s14.indexOf("trial") != -1) {
                        s11 = "\n\n-----------------------------------------------------\nSiteSeer from " + COM.dragonflow.SiteView.Platform.companyName + "\n" + "\n" + "$expired$\n" + "\n" + "Call " + COM.dragonflow.SiteView.Platform.salesPhone
                                + " or e-mail " + COM.dragonflow.SiteView.Platform.salesEmail + "\n" + "to subscribe to the SiteSeer service.\n" + "\n" + COM.dragonflow.SiteView.Platform.salesFooter
                                + "-----------------------------------------------------\n\n";
                    }
                    java.lang.String s16 = monitorgroup.getProperty("_partner");
                    if (s16.length() > 0) {
                        COM.dragonflow.SiteView.MonitorGroup monitorgroup1 = (COM.dragonflow.SiteView.MonitorGroup) siteviewgroup.getElement(s16);
                        if (monitorgroup1 != null) {
                            java.lang.String s18 = monitorgroup1.getProperty("_partnerMailFooter");
                            if (s14.indexOf("trial") != -1) {
                                s18 = monitorgroup1.getProperty("_partnerMailTrialFooter");
                            }
                            if (s18.length() != 0) {
                                s11 = s18.replace('^', '\n');
                            }
                            java.lang.String s20 = monitorgroup1.getProperty("_partnerFromAddress");
                            if (s20.length() != 0) {
                                s7 = s20;
                            }
                        }
                    }
                    if (s14.indexOf("trial") != -1) {
                        java.lang.String s17 = monitorgroup.getProperty("_startDate");
                        java.util.Date date = COM.dragonflow.Utils.TextUtils.stringToDate(s17);
                        java.util.Date date1 = COM.dragonflow.SiteView.Platform.makeDate();
                        long l1 = 0x15180L;
                        long l2 = (date1.getTime() - date.getTime()) / (l1 * 1000L);
                        java.lang.String s21 = "   Your SiteSeer Trial Period Has Expired.\n\n";
                        if (l2 < 10L) {
                            java.lang.String s22 = java.lang.String.valueOf(10L - l2);
                            s21 = "   Your SiteSeer Trial Period Expires In " + s22 + " Days.";
                        }
                        s11 = COM.dragonflow.Utils.TextUtils.replaceString(s11, "$expired$", s21);
                    }
                }
            }
        }
        java.lang.String s12 = "";
        if (COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_hideServerInSubject").length() == 0) {
            s12 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_webserverAddress");
            int i = s12.indexOf(":");
            if (i >= 0) {
                s12 = s12.substring(0, i);
            }
        }
        if (s12.length() != 0) {
            s2 = s2 + " (" + s12 + ")";
        }
        if (flag) {
            s3 = s3 + s11;
        }
        java.lang.String s13 = "";
        try {
            java.lang.String s15 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_mailSubjectMax");
            int j = COM.dragonflow.Utils.TextUtils.toInt(s15);
            if (j == 0) {
                j = 160;
            }
            if (s2.length() > j) {
                s2 = s2.substring(0, j) + "...";
            }
            int k = COM.dragonflow.Utils.SMTP.defaultTimeout;
            java.lang.String s19 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_mailTimeout");
            if (s19.length() > 0) {
                int l = COM.dragonflow.Utils.TextUtils.toInt(s19) * 1000;
                if (l > COM.dragonflow.Utils.SMTP.defaultTimeout) {
                    k = l;
                }
            }
            COM.dragonflow.Utils.SMTP smtp = new SMTP(s, k, array);
            if (s8.length() > 0) {
                smtp.sendSecure(s7, s1, s4, s2, s3, s6, s8, s9);
            } else {
                smtp.send(s7, s1, s4, s2, s3, s6);
            }
            smtp.close();
        } catch (java.net.UnknownHostException unknownhostexception) {
            s13 = COM.dragonflow.SiteView.Monitor.lookupStatus(COM.dragonflow.SiteView.Monitor.kURLBadHostNameError);
        } catch (java.net.SocketException socketexception) {
            if (COM.dragonflow.SiteView.Platform.noRoute(socketexception)) {
                s13 = COM.dragonflow.SiteView.Monitor.lookupStatus(COM.dragonflow.SiteView.Monitor.kURLNoRouteToHostError);
            } else {
                s13 = COM.dragonflow.SiteView.Monitor.lookupStatus(COM.dragonflow.SiteView.Monitor.kURLNoConnectionError);
            }
        } catch (java.io.InterruptedIOException interruptedioexception) {
            s13 = COM.dragonflow.SiteView.Monitor.lookupStatus(COM.dragonflow.SiteView.Monitor.kURLTimeoutError);
        } catch (java.lang.Exception exception) {
            s13 = exception.toString();
            if (s13.indexOf("NullPointerException") >= 0) {
                s13 = s13 + "\n" + COM.dragonflow.Utils.FileUtils.stackTraceText(exception);
            }
        }
        return s13;
    }
}
