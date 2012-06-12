package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;

public final class index_jsp extends org.apache.jasper.runtime.HttpJspBase
    implements org.apache.jasper.runtime.JspSourceDependent {

  private static final JspFactory _jspxFactory = JspFactory.getDefaultFactory();

  private static java.util.List _jspx_dependants;

  private javax.el.ExpressionFactory _el_expressionfactory;
  private org.apache.AnnotationProcessor _jsp_annotationprocessor;

  public Object getDependants() {
    return _jspx_dependants;
  }

  public void _jspInit() {
    _el_expressionfactory = _jspxFactory.getJspApplicationContext(getServletConfig().getServletContext()).getExpressionFactory();
    _jsp_annotationprocessor = (org.apache.AnnotationProcessor) getServletConfig().getServletContext().getAttribute(org.apache.AnnotationProcessor.class.getName());
  }

  public void _jspDestroy() {
  }

  public void _jspService(HttpServletRequest request, HttpServletResponse response)
        throws java.io.IOException, ServletException {

    PageContext pageContext = null;
    ServletContext application = null;
    ServletConfig config = null;
    JspWriter out = null;
    Object page = this;
    JspWriter _jspx_out = null;
    PageContext _jspx_page_context = null;


    try {
      response.setContentType("text/html");
      pageContext = _jspxFactory.getPageContext(this, request, response,
      			null, false, 8192, true);
      _jspx_page_context = pageContext;
      application = pageContext.getServletContext();
      config = pageContext.getServletConfig();
      out = pageContext.getOut();
      _jspx_out = out;

      out.write("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\r\n");
      out.write("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\r\n");
      out.write("   \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\r\n");
      out.write("\r\n");
      out.write("<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\r\n");
      out.write("    <head>\r\n");
      out.write("    <title>");
      out.print( application.getServerInfo() );
      out.write("</title>\r\n");
      out.write("    <style type=\"text/css\">\r\n");
      out.write("    /*<![CDATA[*/\r\n");
      out.write("      body {\r\n");
      out.write("          color: #000000;\r\n");
      out.write("          background-color: #FFFFFF;\r\n");
      out.write("\t  font-family: Arial, \"Times New Roman\", Times, serif;\r\n");
      out.write("          margin: 10px 0px;\r\n");
      out.write("      }\r\n");
      out.write("\r\n");
      out.write("    img {\r\n");
      out.write("       border: none;\r\n");
      out.write("    }\r\n");
      out.write("    \r\n");
      out.write("    a:link, a:visited {\r\n");
      out.write("        color: blue\r\n");
      out.write("    }\r\n");
      out.write("\r\n");
      out.write("    th {\r\n");
      out.write("        font-family: Verdana, \"Times New Roman\", Times, serif;\r\n");
      out.write("        font-size: 110%;\r\n");
      out.write("        font-weight: normal;\r\n");
      out.write("        font-style: italic;\r\n");
      out.write("        background: #D2A41C;\r\n");
      out.write("        text-align: left;\r\n");
      out.write("    }\r\n");
      out.write("\r\n");
      out.write("    td {\r\n");
      out.write("        color: #000000;\r\n");
      out.write("\tfont-family: Arial, Helvetica, sans-serif;\r\n");
      out.write("    }\r\n");
      out.write("    \r\n");
      out.write("    td.menu {\r\n");
      out.write("        background: #FFDC75;\r\n");
      out.write("    }\r\n");
      out.write("\r\n");
      out.write("    .center {\r\n");
      out.write("        text-align: center;\r\n");
      out.write("    }\r\n");
      out.write("\r\n");
      out.write("    .code {\r\n");
      out.write("        color: #000000;\r\n");
      out.write("        font-family: \"Courier New\", Courier, monospace;\r\n");
      out.write("        font-size: 110%;\r\n");
      out.write("        margin-left: 2.5em;\r\n");
      out.write("    }\r\n");
      out.write("    \r\n");
      out.write("     #banner {\r\n");
      out.write("        margin-bottom: 12px;\r\n");
      out.write("     }\r\n");
      out.write("\r\n");
      out.write("     p#congrats {\r\n");
      out.write("         margin-top: 0;\r\n");
      out.write("         font-weight: bold;\r\n");
      out.write("         text-align: center;\r\n");
      out.write("     }\r\n");
      out.write("\r\n");
      out.write("     p#footer {\r\n");
      out.write("         text-align: right;\r\n");
      out.write("         font-size: 80%;\r\n");
      out.write("     }\r\n");
      out.write("     /*]]>*/\r\n");
      out.write("   </style>\r\n");
      out.write("</head>\r\n");
      out.write("\r\n");
      out.write("<body>\r\n");
      out.write("\r\n");
      out.write("<!-- Header -->\r\n");
      out.write("<table id=\"banner\" width=\"100%\">\r\n");
      out.write("    <tr>\r\n");
      out.write("      <td align=\"left\" style=\"width:130px\">\r\n");
      out.write("        <a href=\"http://tomcat.apache.org/\">\r\n");
      out.write("\t  <img src=\"tomcat.gif\" height=\"92\" width=\"130\" alt=\"The Mighty Tomcat - MEOW!\"/>\r\n");
      out.write("\t</a>\r\n");
      out.write("      </td>\r\n");
      out.write("      <td align=\"left\" valign=\"top\"><b>");
      out.print( application.getServerInfo() );
      out.write("</b></td>\r\n");
      out.write("      <td align=\"right\">\r\n");
      out.write("        <a href=\"http://jakarta.apache.org/\">\r\n");
      out.write("\t  <img src=\"asf-logo-wide.gif\" height=\"51\" width=\"537\" alt=\"The Apache Software Foundation\"/>\r\n");
      out.write("\t</a>\r\n");
      out.write("       </td>\r\n");
      out.write("     </tr>\r\n");
      out.write("</table>\r\n");
      out.write("\r\n");
      out.write("<table>\r\n");
      out.write("    <tr>\r\n");
      out.write("\r\n");
      out.write("        <!-- Table of Contents -->\r\n");
      out.write("        <td valign=\"top\">\r\n");
      out.write("            <table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\">\r\n");
      out.write("                <tr>\r\n");
      out.write("\t\t  <th>Administration</th>\r\n");
      out.write("                </tr>\r\n");
      out.write("                <tr>\r\n");
      out.write("\t\t  <td class=\"menu\">\r\n");
      out.write("\t\t    <a href=\"manager/status\">Status</a><br/>\r\n");
      out.write("                    <!--<a href=\"admin\">Tomcat&nbsp;Administration</a><br/>-->\r\n");
      out.write("                    <a href=\"manager/html\">Tomcat&nbsp;Manager</a><br/>\r\n");
      out.write("                    &nbsp;\r\n");
      out.write("                  </td>\r\n");
      out.write("                </tr>\r\n");
      out.write("            </table>\r\n");
      out.write("\r\n");
      out.write("\t    <br />\r\n");
      out.write("            <table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\">\r\n");
      out.write("                <tr>\r\n");
      out.write("\t\t  <th>Documentation</th>\r\n");
      out.write("                </tr>\r\n");
      out.write("                <tr>\r\n");
      out.write("                  <td class=\"menu\">\r\n");
      out.write("                    <a href=\"RELEASE-NOTES.txt\">Release&nbsp;Notes</a><br/>\r\n");
      out.write("                    <a href=\"docs/changelog.html\">Change&nbsp;Log</a><br/>\r\n");
      out.write("                    <a href=\"docs\">Tomcat&nbsp;Documentation</a><br/>                        &nbsp;\r\n");
      out.write("                    &nbsp;\r\n");
      out.write("\t\t    </td>\r\n");
      out.write("                </tr>\r\n");
      out.write("            </table>\r\n");
      out.write("\t    \r\n");
      out.write("            <br/>\r\n");
      out.write("            <table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\">\r\n");
      out.write("                <tr>\r\n");
      out.write("                  <th>Tomcat Online</th>\r\n");
      out.write("                </tr>\r\n");
      out.write("                <tr>\r\n");
      out.write("                  <td class=\"menu\">\r\n");
      out.write("                    <a href=\"http://tomcat.apache.org/\">Home&nbsp;Page</a><br/>\r\n");
      out.write("\t\t    <a href=\"http://tomcat.apache.org/faq/\">FAQ</a><br/>\r\n");
      out.write("                    <a href=\"http://tomcat.apache.org/bugreport.html\">Bug&nbsp;Database</a><br/>\r\n");
      out.write("                    <a href=\"http://issues.apache.org/bugzilla/buglist.cgi?bug_status=UNCONFIRMED&amp;bug_status=NEW&amp;bug_status=ASSIGNED&amp;bug_status=REOPENED&amp;bug_status=RESOLVED&amp;resolution=LATER&amp;resolution=REMIND&amp;resolution=---&amp;bugidtype=include&amp;product=Tomcat+5&amp;cmdtype=doit&amp;order=Importance\">Open Bugs</a><br/>\r\n");
      out.write("                    <a href=\"http://mail-archives.apache.org/mod_mbox/tomcat-users/\">Users&nbsp;Mailing&nbsp;List</a><br/>\r\n");
      out.write("                    <a href=\"http://mail-archives.apache.org/mod_mbox/tomcat-dev/\">Developers&nbsp;Mailing&nbsp;List</a><br/>\r\n");
      out.write("                    <a href=\"irc://irc.freenode.net/#tomcat\">IRC</a><br/>\r\n");
      out.write("\t\t    &nbsp;\r\n");
      out.write("                  </td>\r\n");
      out.write("                </tr>\r\n");
      out.write("            </table>\r\n");
      out.write("\t    \r\n");
      out.write("            <br/>\r\n");
      out.write("            <table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\">\r\n");
      out.write("                <tr>\r\n");
      out.write("                  <th>Examples</th>\r\n");
      out.write("                </tr>\r\n");
      out.write("                <tr>\r\n");
      out.write("                  <td class=\"menu\">\r\n");
      out.write("                    <a href=\"examples/servlets/\">Servlets Examples</a><br/>\r\n");
      out.write("                    <a href=\"examples/jsp/\">JSP Examples</a><br/>\r\n");
      out.write("                    <a href=\"webdav/\">WebDAV&nbsp;capabilities</a><br/>\r\n");
      out.write("     \t\t    &nbsp;\r\n");
      out.write("                  </td>\r\n");
      out.write("                </tr>\r\n");
      out.write("            </table>\r\n");
      out.write("\t    \r\n");
      out.write("            <br/>\r\n");
      out.write("            <table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\">\r\n");
      out.write("                <tr>\r\n");
      out.write("\t\t  <th>Miscellaneous</th>\r\n");
      out.write("                </tr>\r\n");
      out.write("                <tr>\r\n");
      out.write("                  <td class=\"menu\">\r\n");
      out.write("                    <a href=\"http://java.sun.com/products/jsp\">Sun's&nbsp;Java&nbsp;Server&nbsp;Pages&nbsp;Site</a><br/>\r\n");
      out.write("                    <a href=\"http://java.sun.com/products/servlet\">Sun's&nbsp;Servlet&nbsp;Site</a><br/>\r\n");
      out.write("    \t\t    &nbsp;\r\n");
      out.write("                  </td>\r\n");
      out.write("                </tr>\r\n");
      out.write("            </table>\r\n");
      out.write("        </td>\r\n");
      out.write("\r\n");
      out.write("        <td style=\"width:20px\">&nbsp;</td>\r\n");
      out.write("\t\r\n");
      out.write("        <!-- Body -->\r\n");
      out.write("        <td align=\"left\" valign=\"top\">\r\n");
      out.write("          <p id=\"congrats\">If you're seeing this page via a web browser, it means you've setup Tomcat successfully. Congratulations!</p>\r\n");
      out.write(" \r\n");
      out.write("          <p>As you may have guessed by now, this is the default Tomcat home page. It can be found on the local filesystem at:</p>\r\n");
      out.write("          <p class=\"code\">$CATALINA_HOME/webapps/ROOT/index.jsp</p>\r\n");
      out.write("\t  \r\n");
      out.write("          <p>where \"$CATALINA_HOME\" is the root of the Tomcat installation directory. If you're seeing this page, and you don't think you should be, then either you're either a user who has arrived at new installation of Tomcat, or you're an administrator who hasn't got his/her setup quite right. Providing the latter is the case, please refer to the <a href=\"docs\">Tomcat Documentation</a> for more detailed setup and administration information than is found in the INSTALL file.</p>\r\n");
      out.write("\r\n");
      out.write("            <p><b>NOTE: For security reasons, using the administration webapp\r\n");
      out.write("            is restricted to users with role \"admin\". The manager webapp\r\n");
      out.write("            is restricted to users with role \"manager\".</b>\r\n");
      out.write("            Users are defined in <code>$CATALINA_HOME/conf/tomcat-users.xml</code>.</p>\r\n");
      out.write("\r\n");
      out.write("            <p>Included with this release are a host of sample Servlets and JSPs (with associated source code), extensive documentation, and an introductory guide to developing web applications.</p>\r\n");
      out.write("\r\n");
      out.write("            <p>Tomcat mailing lists are available at the Tomcat project web site:</p>\r\n");
      out.write("\r\n");
      out.write("           <ul>\r\n");
      out.write("               <li><b><a href=\"mailto:users@tomcat.apache.org\">users@tomcat.apache.org</a></b> for general questions related to configuring and using Tomcat</li>\r\n");
      out.write("               <li><b><a href=\"mailto:dev@tomcat.apache.org\">dev@tomcat.apache.org</a></b> for developers working on Tomcat</li>\r\n");
      out.write("           </ul>\r\n");
      out.write("\r\n");
      out.write("            <p>Thanks for using Tomcat!</p>\r\n");
      out.write("\r\n");
      out.write("            <p id=\"footer\"><img src=\"tomcat-power.gif\" width=\"77\" height=\"80\" alt=\"Powered by Tomcat\"/><br/>\r\n");
      out.write("\t    &nbsp;\r\n");
      out.write("\r\n");
      out.write("\t    Copyright &copy; 1999-2006 Apache Software Foundation<br/>\r\n");
      out.write("            All Rights Reserved\r\n");
      out.write("            </p>\r\n");
      out.write("        </td>\r\n");
      out.write("\r\n");
      out.write("    </tr>\r\n");
      out.write("</table>\r\n");
      out.write("\r\n");
      out.write("</body>\r\n");
      out.write("</html>\r\n");
    } catch (Throwable t) {
      if (!(t instanceof SkipPageException)){
        out = _jspx_out;
        if (out != null && out.getBufferSize() != 0)
          try { out.clearBuffer(); } catch (java.io.IOException e) {}
        if (_jspx_page_context != null) _jspx_page_context.handlePageException(t);
      }
    } finally {
      _jspxFactory.releasePageContext(_jspx_page_context);
    }
  }
}
