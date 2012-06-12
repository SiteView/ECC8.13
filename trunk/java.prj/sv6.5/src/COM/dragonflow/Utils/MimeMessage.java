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

import java.util.StringTokenizer;

import jgl.Array;
import jgl.HashMap;

// Referenced classes of package COM.dragonflow.Utils:
// Base64Decoder

public class MimeMessage
{

    public boolean debug;
    boolean is_good;
    java.lang.String msg;
    java.lang.String Head[];
    java.lang.String Body[];
    jgl.HashMap Headers;
    jgl.Array Bodies;

    public MimeMessage(java.lang.String as[])
    {
        debug = false;
        is_good = true;
        msg = "";
        Head = null;
        Body = null;
        Headers = null;
        Bodies = null;
        jgl.Array array = splitHeaderBody(as);
        Head = (java.lang.String[])array.at(0);
        Body = (java.lang.String[])array.at(1);
        Headers = parseHeader(Head);
        parseSubject();
        java.lang.String s = (java.lang.String)Headers.get("Content-Type");
        java.lang.String s1 = "";
        boolean flag = false;
        if(s != null && s.indexOf("multipart") != -1 && s.indexOf("boundary=") != -1)
        {
            flag = true;
            s1 = s.substring(s.indexOf("boundary="));
            int i = s1.indexOf('"');
            int j = s1.lastIndexOf('"');
            s1 = s1.substring(i + 1, j - 1);
        }
        Bodies = new Array();
        if(!flag)
        {
            java.lang.String s2 = (java.lang.String)Headers.get("Content-Type");
            if(debug)
            {
                java.lang.System.out.println("MimeMessage: single body content type = " + s2);
            }
            Body = decodeBody(Body, s2);
            Bodies.add(Body);
        } else
        {
            jgl.Array array1 = splitMultiParts(Body, s1);
            for(int k = 0; k < array1.size(); k++)
            {
                java.lang.String as1[] = (java.lang.String[])array1.at(k);
                jgl.Array array2 = splitHeaderBody(as1);
                java.lang.String as2[] = (java.lang.String[])array2.at(0);
                java.lang.String as3[] = (java.lang.String[])array2.at(1);
                jgl.HashMap hashmap = parseHeader(as2);
                java.lang.String s3 = (java.lang.String)hashmap.get("Content-Type");
                if(debug)
                {
                    java.lang.System.out.println("MimeMessage: multipart content type = " + s3);
                }
                as3 = decodeBody(as3, s3);
                Bodies.add(as3);
            }

        }
        if(debug)
        {
            java.lang.System.out.println("MimeMessage, Dump: ");
            dump();
        }
    }

    public boolean isOkay()
    {
        return is_good;
    }

    public java.lang.String getStatusMsg()
    {
        return msg;
    }

    public java.lang.String getHeaderVal(java.lang.String s)
    {
        return (java.lang.String)Headers.get(s);
    }

    public int getBodyCount()
    {
        return Bodies.size();
    }

    public jgl.Array getBodies()
    {
        return Bodies;
    }

    jgl.Array splitHeaderBody(java.lang.String as[])
    {
        java.lang.String as1[] = getheader(as);
        java.lang.String as2[] = getbody(as);
        jgl.Array array = new Array();
        array.add(as1);
        array.add(as2);
        return array;
    }

    java.lang.String[] getheader(java.lang.String as[])
    {
        int i = headsize(as);
        java.lang.String as1[] = new java.lang.String[i];
        for(int j = 0; j < i; j++)
        {
            as1[j] = as[j];
        }

        return as1;
    }

    java.lang.String[] getbody(java.lang.String as[])
    {
        int i = headsize(as);
        int j = as.length - i;
        java.lang.String as1[] = new java.lang.String[j];
        int k = i;
        for(int l = 0; k < as.length; l++)
        {
            as1[l] = as[k];
            k++;
        }

        return as1;
    }

    int headsize(java.lang.String as[])
    {
        int i = 0;
        int j = 0;
        do
        {
            if(j >= as.length)
            {
                break;
            }
            i++;
            if(as[j].length() == 0 || as[j].charAt(0) == '\n')
            {
                break;
            }
            j++;
        } while(true);
        return i;
    }

    jgl.Array splitMultiParts(java.lang.String as[], java.lang.String s)
    {
        jgl.Array array = new Array();
        jgl.Array array1 = new Array();
        boolean flag = false;
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s1 = as[i];
            if(s1.indexOf(s) > -1)
            {
                flag = true;
                if(array1.size() <= 0)
                {
                    continue;
                }
                java.lang.String as2[] = new java.lang.String[array1.size()];
                for(int k = 0; k < array1.size(); k++)
                {
                    as2[k] = (java.lang.String)array1.at(k);
                }

                array.add(as2);
                array1 = new Array();
                continue;
            }
            if(flag)
            {
                array1.add(s1);
            }
        }

        if(array1.size() > 0)
        {
            java.lang.String as1[] = new java.lang.String[array1.size()];
            for(int j = 0; j < array1.size(); j++)
            {
                as1[j] = (java.lang.String)array1.at(j);
            }

            array.add(as1);
        }
        return array;
    }

    jgl.HashMap parseHeader(java.lang.String as[])
    {
        java.lang.String s = null;
        jgl.HashMap hashmap = new HashMap();
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s1 = as[i];
            if(s1.length() == 0)
            {
                continue;
            }
            if((s1.charAt(0) == ' ' || s1.charAt(0) == '\t') && s != null)
            {
                java.lang.String s2 = (java.lang.String)hashmap.get(s);
                s2 = s2.concat(s1);
                hashmap.remove(s);
                hashmap.add(s, s2);
                continue;
            }
            int j = s1.indexOf(":");
            if(j > -1)
            {
                java.lang.String s3 = s1.substring(0, j);
                java.lang.String s4 = s1.substring(j + 1);
                hashmap.add(s3, s4);
                s = s3;
            }
        }

        return hashmap;
    }

    void parseSubject()
    {
        java.lang.String s = (java.lang.String)Headers.get("Subject");
        if(debug)
        {
            java.lang.System.out.println("MimeMessage: parsing Subject: " + s);
        }
        if(s != null)
        {
            s = s.trim();
            if(s.startsWith("=?") && s.endsWith("?="))
            {
                int i = s.indexOf("=?") + 2;
                int j = s.indexOf("?", i);
                java.lang.String s1 = s.substring(i, j);
                if(debug)
                {
                    java.lang.System.out.println("MimeMessage: got encoding of: " + s1);
                }
                i = j + 1;
                j = s.indexOf("?", i);
                java.lang.String s2 = s.substring(i, j);
                if(debug)
                {
                    java.lang.System.out.println("MimeMessage: got packing of: " + s2);
                }
                i = j + 1;
                j = s.indexOf("?=", i);
                java.lang.String s3 = s.substring(i, j);
                if(debug)
                {
                    java.lang.System.out.println("MimeMessage: got text of: " + s3);
                }
                if(s2.toUpperCase().compareTo("B") == 0)
                {
                    COM.dragonflow.Utils.Base64Decoder base64decoder = new Base64Decoder(s3);
                    try
                    {
                        java.lang.String s4 = base64decoder.processString();
                        if(debug)
                        {
                            java.lang.System.out.println("MimeMessage: decoding subject: " + s);
                        }
                        byte abyte0[] = s4.getBytes();
                        s4 = new String(abyte0, s1);
                        if(debug)
                        {
                            java.lang.System.out.println("MimeMessage Subject decoded to: " + s4);
                        }
                        Headers.put("Subject", s4);
                    }
                    catch(java.lang.Exception exception)
                    {
                        java.lang.System.out.println("MimeMessage Caught exception: " + exception);
                        is_good = false;
                        msg = "Exception processing encoded Subject: " + exception;
                    }
                }
            }
        }
    }

    java.lang.String[] decodeBody(java.lang.String as[], java.lang.String s)
    {
        if(s == null)
        {
            return as;
        }
        if(debug)
        {
            java.lang.System.out.println("MimeMessage.decodeBody - parsing charset from = " + s);
        }
        java.util.StringTokenizer stringtokenizer = new StringTokenizer(s, ";");
        java.lang.String s1 = null;
        do
        {
            if(!stringtokenizer.hasMoreTokens())
            {
                break;
            }
            java.lang.String s2 = stringtokenizer.nextToken();
            if(s2.indexOf("charset=") <= -1)
            {
                continue;
            }
            s1 = new String(s2);
            break;
        } while(true);
        if(s1 == null)
        {
            return as;
        }
        s1 = s1.trim();
        int i = s1.indexOf('=');
        if(i < 0)
        {
            return as;
        }
        s1 = s1.substring(i + 1);
        if(s1.startsWith("\""))
        {
            s1 = s1.substring(1);
        }
        if(s1.endsWith("\""))
        {
            s1 = s1.substring(0, s1.length() - 1);
        }
        if(debug)
        {
            java.lang.System.out.println("MimeMessage.decodeBody - contenttype charset = " + s1);
        }
        for(int j = 0; j < as.length;j++)
        {
            if(debug)
            {
                java.lang.System.out.println("MimeMessage decoding line: " + as[j]);
            }
            byte abyte0[] = as[j].getBytes();
            try
            {
                as[j] = new String(abyte0, s1);
                if(debug)
                {
                    java.lang.System.out.println("MimeMessage decoded to: " + as[j]);
                }
                continue;
            }
            catch(java.lang.Exception exception)
            {
                java.lang.System.out.println("MimeMessage Caught exception: " + exception);
                is_good = false;
                msg = "Exception processing body parts: " + exception;
                //j++;/*dingbing.xu delete j++*/
            }
        }

        return as;
    }

    public void dump()
    {
        java.lang.System.out.println("MimeMessage: debug = " + debug);
        java.lang.System.out.println("MimeMessage: is_good = " + is_good);
        java.lang.System.out.println("MimeMessage: msg = " + msg);
        for(int i = 0; i < Head.length; i++)
        {
            java.lang.System.out.println("MimeMessage: Head[" + i + "] = " + Head[i]);
        }

        for(int j = 0; j < Body.length; j++)
        {
            java.lang.System.out.println("MimeMessage: Body[" + j + "] = " + Body[j]);
        }

        java.lang.String s;
        java.lang.String s1;
        for(java.util.Enumeration enumeration = Headers.keys(); enumeration.hasMoreElements(); java.lang.System.out.println("MimeMessage: Headers " + s + " = " + s1))
        {
            s = (java.lang.String)enumeration.nextElement();
            s1 = (java.lang.String)Headers.get(s);
        }

        java.lang.System.out.println("MimeMessage: Number of Bodies = " + Bodies.size());
        for(int k = 0; k < Bodies.size(); k++)
        {
            java.lang.System.out.println("MimeMessage: Body " + k + "----------------------------");
            java.lang.String as[] = (java.lang.String[])Bodies.at(k);
            for(int l = 0; l < as.length; l++)
            {
                java.lang.System.out.println("MimeMessage: body[" + l + "] = " + as[l]);
            }

        }

    }
}
