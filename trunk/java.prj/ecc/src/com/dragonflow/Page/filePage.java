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

import com.dragonflow.HTTP.HTTPRequestException;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class filePage extends com.dragonflow.Page.CGI
{

    public static java.lang.String CRLF = "\r\n";

    public filePage()
    {
    }

    public void printBody()
        throws java.lang.Exception
    {
        if(!request.actionAllowed("_file"))
        {
            throw new HTTPRequestException(557);
        }
        java.lang.String s = request.getValue("operation");
        java.lang.String s1 = request.getValue("file");
        java.lang.String s2 = request.getValue("data");
        java.lang.String s3 = com.dragonflow.SiteView.Platform.getRoot();
        if(com.dragonflow.SiteView.Platform.isSiteSeerAccount(request.getAccount()) && (!s.equals("get") || !s1.equals("/groups/" + request.getAccount() + ".mg")) && (!s.equals("list") || !s1.equals("/groups/")))
        {
            s3 = s3 + java.io.File.separator + "accounts" + java.io.File.separator + request.getAccount();
        }
        s3 = s3 + s1;
        try
        {
            boolean flag = !s1.startsWith("/cache") && !s1.startsWith("/groups") && !s1.startsWith("/htdocs") && !s1.startsWith("/logs") && !s1.startsWith("/scripts") && !s1.startsWith("/templates");
            if(s1.startsWith("/accounts") && request.getAccount().equals("administrator"))
            {
                flag = false;
            }
            if(flag)
            {
                throw new Exception("access not allowed");
            }
            if(s1.indexOf("..") >= 0)
            {
                throw new Exception("access not allowed");
            }
            if(s1.startsWith("."))
            {
                throw new Exception("access not allowed");
            }
            if(request.isPost())
            {
                if(s.equals("delete"))
                {
                    java.io.File file = new File(s3);
                    file.delete();
                    outputStream.println("file deleted: " + s1);
                } else
                if(s.equals("put"))
                {
                    java.io.File file1 = new File(s3);
                    java.io.File file3 = new File(s3 + ".bak");
                    if(request.getValue("nobackup").length() == 0 && file1.exists())
                    {
                        com.dragonflow.Utils.FileUtils.copyFileThrow(file1, file3);
                    }
                    com.dragonflow.Utils.FileUtils.writeFile(s3, s2);
                    outputStream.println("file saved: " + s1);
                } else
                {
                    throw new Exception("unknown operation, " + s);
                }
            } else
            if(s.equals("list"))
            {
                if(com.dragonflow.SiteView.Platform.isSiteSeerAccount(request.getAccount()) && s1.equals("/groups/"))
                {
                    outputStream.println(request.getAccount() + ".mg");
                } else
                {
                    java.io.File file2 = new File(s3);
                    java.lang.String as[] = file2.list();
                    for(int i = 0; i < as.length; i++)
                    {
                        outputStream.println(as[i]);
                    }

                }
            } else
            if(s.equals("get"))
            {
                java.lang.StringBuffer stringbuffer = com.dragonflow.Utils.FileUtils.readFile(s3);
                outputStream.print(stringbuffer);
            } else
            {
                throw new Exception("unknown operation, " + s);
            }
        }
        catch(java.lang.Exception exception)
        {
            outputStream.println("error: " + exception + ", " + s1 + ", " + s3);
        }
    }

    public void printCGIHeader()
    {
        request.printHeader(outputStream);
    }

    public void printCGIFooter()
    {
        outputStream.flush();
    }

    public static void main(java.lang.String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.filePage filepage = new filePage();
        if(args.length > 0)
        {
            filepage.args = args;
        }
        filepage.handleRequest();
    }

}
