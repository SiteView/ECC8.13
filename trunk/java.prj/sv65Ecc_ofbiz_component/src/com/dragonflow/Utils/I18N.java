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
    static String enc = null;

    public I18N()
    {
    }

    public static String nullEncoding()
    {
        if(!isI18N && enc == null)
        {
            enc = com.dragonflow.Utils.I18N.getDefaultEncoding();
        }
        //return isI18N ? "Cp437" : enc;  
		return "GBK";
    }

    public static String getDefaultEncoding()
    {
        //String s = "Cp1252";
		String s = "GBK";
        try
        {
            java.io.OutputStreamWriter outputstreamwriter = new OutputStreamWriter(System.out);
            s = outputstreamwriter.getEncoding();
        }
        catch(Exception exception) { }
        return s;
    }

    public static String escapeString(String s, String s1)
    {
        return com.dragonflow.Utils.TextUtils.escapeHTML(com.dragonflow.Utils.I18N.StringToUnicode(com.dragonflow.Utils.I18N.UnicodeToString(s, com.dragonflow.Utils.I18N.nullEncoding()), s1));
    }

    public static boolean test(String s, int i)
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

    public static boolean hasUnicode(String s)
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

    public static boolean isI18N(String s)
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

    public static boolean isNullEncoding(String s)
    {
        try
        {
            String s1 = com.dragonflow.Utils.I18N.nullEncoding();
            byte abyte0[] = s1 != null && s1.length() != 0 ? s.getBytes(s1) : s.getBytes();
        }
        catch(Exception exception)
        {
            return false;
        }
        return true;
    }

    public static String toNullEncoding(String s)
    {
        if(!isI18N)
        {
            return s;
        } else
        {
            com.dragonflow.Utils.I18N.test(s, 0);
            String s1 = com.dragonflow.Utils.I18N.UnicodeToString(s, "");
            return com.dragonflow.Utils.I18N.StringToUnicode(s1, com.dragonflow.Utils.I18N.nullEncoding());
        }
    }

    public static String toDefaultEncoding(String s)
    {
        if(!isI18N)
        {
            return s;
        } else
        {
            com.dragonflow.Utils.I18N.test(s, 1);
            String s1 = com.dragonflow.Utils.I18N.UnicodeToString(s, com.dragonflow.Utils.I18N.nullEncoding());
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
            String s = (String)array.at(i);
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
            String s = (String)array.at(i);
            com.dragonflow.Utils.I18N.test(s, 1);
            array1.add(com.dragonflow.Utils.I18N.toDefaultEncoding((String)array.at(i)));
        }

        return array1;
    }

    public static String UnicodeToString(String s)
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
    public static String UnicodeToString(String s,
			String s1) {
		try {
			if (s == null)
				return "";
			if (!isI18N(s))/* change by dingbing.xu from isI18N */
			{
				return s;
			}

			if (s1 == com.dragonflow.Utils.I18N.nullEncoding()) {
				com.dragonflow.Utils.I18N.test(s, 1);
			} else if (s1.length() == 0) {
				com.dragonflow.Utils.I18N.test(s, 0);
			}
			String s2;
			byte abyte0[] = s1 != null && s1.length() != 0 ? s.getBytes(s1) : s.getBytes();
			char ac[] = new char[abyte0.length];
			for (int i = 0; i < abyte0.length; i++) {
				ac[i] = (char) (abyte0[i] & 0xff);
			}

			s2 = new String(ac);
			com.dragonflow.Utils.I18N.test(s2, 2);
			return s2;
		} catch (Exception exception) {
			if (s1 != null && s1.length() > 0) {
				com.dragonflow.Log.LogManager.log("Error","I18N: Bad Encoding(" + s1 + ") "	+ exception.getMessage());
				com.dragonflow.Utils.TextUtils.debugPrint("I18N: Bad Encoding("	+ s1 + ") " + exception.getMessage());
				exception.printStackTrace();
			}
			return s;
		}
	}

    public static String StringToUnicode(String s)
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
    public static String StringToUnicode(String s, String s1)
    {
        if(s == null||s.length()==0)
        {
            return "";
        }

		if(!isI18N(s))/*change By dingbing.xu*/
        {
            return s;
        }
        String s2 = "";
        com.dragonflow.Utils.I18N.test(s, 2);
        String s3;
        
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
        catch (Exception exception) {
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
    public static String byteString(byte abyte0[])
    {
        if(!isI18N)
        {
            return new String(abyte0);
        }
        try {
        String s;
        char ac[] = new char[abyte0.length];
        for(int i = 0; i < abyte0.length; i++)
        {
            ac[i] = (char)(abyte0[i] & 0xff);
        }

        s = new String(ac);
        return s;
        }
        catch (Exception exception) {
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
    public static String getTestUnicode()
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
        catch (Exception exception) {
        return "";
        }
    }

    public static void dumpValues(String s, String as[], String s1)
    {
        String s2 = s1;
        if(s1.indexOf("#") >= 0)
        {
            s2 = s1.substring(s1.indexOf("#"));
        }
        for(int i = 0; i < as.length; i++)
        {
            String s3 = new String(s2);
            String s4 = s3;
            for(; s3.indexOf(as[i]) >= 0; s3 = s3.substring(s3.indexOf(as[i]) + as[i].length()))
            {
                String s5 = s3.substring(s3.indexOf(as[i]));
                s5 = s5.substring(0, Math.min(Math.max(s5.indexOf("\n"), 5), s5.length()));
                com.dragonflow.Utils.I18N.dmp(s + ": " + s5.substring(0, as[i].length()), s5.substring(as[i].length()));
            }

        }

    }

    public static void dmp(String s, String s1)
    {
        System.out.print(s + " '" + s1 + "'\n      ");
        for(int i = 0; i < s1.length(); i++)
        {
            System.out.print(Integer.toHexString(s1.charAt(i)) + ", ");
        }

        System.out.print("\n");
    }

	public static boolean isI18N() {
		return isI18N;
	}

}
