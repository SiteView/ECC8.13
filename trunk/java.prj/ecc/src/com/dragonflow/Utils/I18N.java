 /*
  * Created on 2005-2-9 3:06:20
  *
  * .java
  *
  * History:
  *
  */
  package com.dragonflow.Utils;

 /**
     * Comment for <code></code>
     * 
     * @author
     * @version 0.0
     * 
     * 
     */
import java.io.OutputStreamWriter;

import jgl.Array;

// Referenced classes of package com.dragonflow.Utils:
// TextUtils

public class I18N
{

    public static boolean  isI18N= false;
    public static boolean testing = false;
    public static final int DEFAULT = 0;
    public static final int NULL = 1;
    public static final int STRING = 2;
    static java.lang.String enc = null;

    public I18N()
    {
    }

    public static java.lang.String nullEncoding()
    {
        if(!isI18N && enc == null)
        {
            enc = com.dragonflow.Utils.I18N.getDefaultEncoding();
        }
        //return isI18N ? "Cp437" : enc;  
		return "GBK";
    }

    public static java.lang.String getDefaultEncoding()
    {
        //java.lang.String s = "Cp1252";
		java.lang.String s = "GBK";
        try
        {
            java.io.OutputStreamWriter outputstreamwriter = new OutputStreamWriter(java.lang.System.out);
            s = outputstreamwriter.getEncoding();
        }
        catch(java.lang.Exception exception) { }
        return s;
    }

    public static java.lang.String escapeString(java.lang.String s, java.lang.String s1)
    {
        return com.dragonflow.Utils.TextUtils.escapeHTML(com.dragonflow.Utils.I18N.StringToUnicode(com.dragonflow.Utils.I18N.UnicodeToString(s, com.dragonflow.Utils.I18N.nullEncoding()), s1));
    }

    public static boolean test(java.lang.String s, int i)
    {
        if(!testing)
        {
            return true;
        }
        if(s.length() > 0 && s.indexOf("SAP") >= 0)
        {
            int j = s.indexOf("SAP");
            int k = s.charAt(j + 3) & 0xff;
            if(k == 37)
            {
                return true;
            }
            if(i == 0 && (k == 146 || k == 184))
            {
                return true;
            }
            if(i == 1 && k == 226)
            {
                return true;
            }
            if(i == 2 && k == 131)
            {
                return true;
            } else
            {
                com.dragonflow.Utils.I18N.dmp("!!!!!!!!!!Bad encoding: Looking for " + (i != 0 ? i != 1 ? "STRING" : "NULL" : "DEFAULT"), s);
                return false;
            }
        } else
        {
            return true;
        }
    }

    public static boolean hasUnicode(java.lang.String s)
    {
        for(int i = 0; i < s.length(); i++)
        {
            if(s.charAt(i) > '\377')
            {
                return true;
            }
        }

        return false;
    }

    public static boolean isI18N(java.lang.String s)
    {
        for(int i = 0; i < s.length(); i++)
        {
			if(Character.getNumericValue(s.charAt(i))==-1)
				return true;
			
/*			if(s.charAt(i) > '\177')
            {
                return true;
            }
 */           
        }

        return false;
    }

    public static boolean isNullEncoding(java.lang.String s)
    {
        try
        {
            java.lang.String s1 = com.dragonflow.Utils.I18N.nullEncoding();
            byte abyte0[] = s1 != null && s1.length() != 0 ? s.getBytes(s1) : s.getBytes();
        }
        catch(java.lang.Exception exception)
        {
            return false;
        }
        return true;
    }

    public static java.lang.String toNullEncoding(java.lang.String s)
    {
        if(!isI18N)
        {
            return s;
        } else
        {
            com.dragonflow.Utils.I18N.test(s, 0);
            java.lang.String s1 = com.dragonflow.Utils.I18N.UnicodeToString(s, "");
            return com.dragonflow.Utils.I18N.StringToUnicode(s1, com.dragonflow.Utils.I18N.nullEncoding());
        }
    }

    public static java.lang.String toDefaultEncoding(java.lang.String s)
    {
        if(!isI18N)
        {
            return s;
        } else
        {
            com.dragonflow.Utils.I18N.test(s, 1);
            java.lang.String s1 = com.dragonflow.Utils.I18N.UnicodeToString(s, com.dragonflow.Utils.I18N.nullEncoding());
            return com.dragonflow.Utils.I18N.StringToUnicode(s1, "");
        }
    }

    public static jgl.Array toNullArray(jgl.Array array)
    {
        if(!isI18N)
        {
            return array;
        }
        jgl.Array array1 = new Array();
        for(int i = 0; i < array.size(); i++)
        {
            java.lang.String s = (java.lang.String)array.at(i);
            com.dragonflow.Utils.I18N.test(s, 0);
            array1.add(com.dragonflow.Utils.I18N.toNullEncoding(s));
        }

        return array1;
    }

    public static jgl.Array toDefaultArray(jgl.Array array)
    {
        if(!isI18N)
        {
            return array;
        }
        jgl.Array array1 = new Array();
        for(int i = 0; i < array.size(); i++)
        {
            java.lang.String s = (java.lang.String)array.at(i);
            com.dragonflow.Utils.I18N.test(s, 1);
            array1.add(com.dragonflow.Utils.I18N.toDefaultEncoding((java.lang.String)array.at(i)));
        }

        return array1;
    }

    public static java.lang.String UnicodeToString(java.lang.String s)
    {
        return com.dragonflow.Utils.I18N.UnicodeToString(s, "");
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param s1
     * @return
     */
    public static java.lang.String UnicodeToString(java.lang.String s, java.lang.String s1)
    {
		if(!isI18N(s))/*change by dingbing.xu from isI18N*/
        {
            return s;
        }
       
        try {
			if(s==null)
				return "";
	
        if(s1 == com.dragonflow.Utils.I18N.nullEncoding())
        {
            com.dragonflow.Utils.I18N.test(s, 1);
        } else
        if(s1.length() == 0)
        {
            com.dragonflow.Utils.I18N.test(s, 0);
        }
        java.lang.String s2;
        byte abyte0[] = s1 != null && s1.length() != 0 ? s.getBytes(s1) : s.getBytes();
        char ac[] = new char[abyte0.length];
        for(int i = 0; i < abyte0.length; i++)
        {
            ac[i] = (char)(abyte0[i] & 0xff);
        }

        s2 = new String(ac);
        com.dragonflow.Utils.I18N.test(s2, 2);
        return s2;
        }
        catch (java.lang.Exception exception) {
        if(s1 != null && s1.length() > 0)
        {
            com.dragonflow.Log.LogManager.log("Error", "I18N: Bad Encoding(" + s1 + ") " + exception.getMessage());
            com.dragonflow.Utils.TextUtils.debugPrint("I18N: Bad Encoding(" + s1 + ") " + exception.getMessage());
            exception.printStackTrace();
        }
        return s;
        }
    }

    public static java.lang.String StringToUnicode(java.lang.String s)
    {
        if(!isI18N)
        {
            return s;
        } else
        {
            return com.dragonflow.Utils.I18N.StringToUnicode(s, "");
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param s1
     * @return
     */
    public static java.lang.String StringToUnicode(java.lang.String s, java.lang.String s1)
    {
        if(s == null||s.length()==0)
        {
            return "";
        }

		if(!isI18N(s))/*change By dingbing.xu*/
        {
            return s;
        }
        java.lang.String s2 = "";
        com.dragonflow.Utils.I18N.test(s, 2);
        java.lang.String s3;
        
        try {
        byte abyte0[] = new byte[s.length()];
        for(int i = 0; i < s.length(); i++)
        {
            abyte0[i] = (byte)(s.charAt(i) & 0xff);
        }

        s3 = s1 != null && s1.length() != 0 ? new String(abyte0, s1) : new String(abyte0);
        if(s1 == com.dragonflow.Utils.I18N.nullEncoding())
        {
            com.dragonflow.Utils.I18N.test(s3, 1);
        } else
        if(s1.length() == 0)
        {
            com.dragonflow.Utils.I18N.test(s3, 0);
        }
        return s3;
        }
        catch (java.lang.Exception exception) {
        if(s1 != null && s1.length() > 0)
        {
            com.dragonflow.Log.LogManager.log("Error", "I18N: Bad Encoding(" + s1 + ") " + exception.getMessage());
            com.dragonflow.Utils.TextUtils.debugPrint("I18N: Bad Encoding(" + s1 + ") " + exception.getMessage());
            exception.printStackTrace();
        }
        return s;
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param abyte0
     * @return
     */
    public static java.lang.String byteString(byte abyte0[])
    {
        if(!isI18N)
        {
            return new String(abyte0);
        }
        try {
        java.lang.String s;
        char ac[] = new char[abyte0.length];
        for(int i = 0; i < abyte0.length; i++)
        {
            ac[i] = (char)(abyte0[i] & 0xff);
        }

        s = new String(ac);
        return s;
        }
        catch (java.lang.Exception exception) {
        com.dragonflow.Log.LogManager.log("Error", "I18N: Cannot Encode " + exception.getMessage());
        com.dragonflow.Utils.TextUtils.debugPrint("I18N: Cannot Encode " + exception.getMessage());
        exception.printStackTrace();
        return "";
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @return
     */
    public static java.lang.String getTestUnicode()
    {
        String s = "SAP\u0192W\u0192\u0192\u0192p\u0192\u201C\u0160\u201D\u017D\256\u2030\357\u017D\320";
        String s1 = com.dragonflow.Utils.I18N.UnicodeToString(s);
        try {
        byte abyte0[];
        char ac[] = s1.toCharArray();
        abyte0 = new byte[ac.length];
        for(int i = 0; i < ac.length; i++)
        {
            abyte0[i] = (byte)(ac[i] & 0xff);
        }

        return new String(abyte0, "shift_jis");
    }
        catch (java.lang.Exception exception) {
        return "";
        }
    }

    public static void dumpValues(java.lang.String s, java.lang.String as[], java.lang.String s1)
    {
        java.lang.String s2 = s1;
        if(s1.indexOf("#") >= 0)
        {
            s2 = s1.substring(s1.indexOf("#"));
        }
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s3 = new String(s2);
            java.lang.String s4 = s3;
            for(; s3.indexOf(as[i]) >= 0; s3 = s3.substring(s3.indexOf(as[i]) + as[i].length()))
            {
                java.lang.String s5 = s3.substring(s3.indexOf(as[i]));
                s5 = s5.substring(0, java.lang.Math.min(java.lang.Math.max(s5.indexOf("\n"), 5), s5.length()));
                com.dragonflow.Utils.I18N.dmp(s + ": " + s5.substring(0, as[i].length()), s5.substring(as[i].length()));
            }

        }

    }

    public static void dmp(java.lang.String s, java.lang.String s1)
    {
        java.lang.System.out.print(s + " '" + s1 + "'\n      ");
        for(int i = 0; i < s1.length(); i++)
        {
            java.lang.System.out.print(java.lang.Integer.toHexString(s1.charAt(i)) + ", ");
        }

        java.lang.System.out.print("\n");
    }

}
