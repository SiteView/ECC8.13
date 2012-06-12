package com.siteview.server.xmtp;

public class Util {
	 public static String escapeNode(String node)
     {
         if (node == null)
             return null;

         StringBuilder sb = new StringBuilder();
         for (int i = 0; i < node.length(); i++)
         {
             /*
             <space> \20
             " 	    \22
             & 	    \26
             ' 	    \27
             ,       \2c
             / 	    \2f
             : 	    \3a
             < 	    \3c
             > 	    \3e
             @ 	    \40
             \ 	    \5c
             {       \7b
             }       \7d
             */
             char c = node.charAt(i);
             switch (c)
             {
                 /*case ' ': sb.append("\\20"); break;
                 case '"': sb.append("\\22"); break;
                 case '&': sb.append("\\26"); break;
                 case '\'': sb.append("\\27"); break;*/
                 case ',': sb.append("\\2c"); break;
                 /*case '/': sb.append("\\2f"); break;
                 case ':': sb.append("\\3a"); break;
                 case '<': sb.append("\\3c"); break;
                 case '>': sb.append("\\3e"); break;
                 case '@': sb.append("\\40"); break;*/
                 case '\\':sb.append("\\5c"); break;
                 case '(': sb.append("\\28"); break;
                 case ')': sb.append("\\29"); break;
                 case '{': sb.append("\\7b"); break;
                 case '}': sb.append("\\7d"); break;
                 default: sb.append(c); break;
             }
         }
         return sb.toString();
     }

     public static String unescapeNode(String node)
     {
         if (node == null)
             return null;

         StringBuilder sb = new StringBuilder();
         for (int i = 0; i < node.length(); i++)
         {
             char c1 = node.charAt(i);
             if (c1 == '\\' && i + 2 < node.length())
             {
                 i += 1;
                 char c2 = node.charAt(i);
                 i += 1;
                 char c3 = node.charAt(i);
                 if (c2 == '2')
                 {
                     switch (c3)
                     {
                         case '0':
                             sb.append(' ');
                             break;
                         case '2':
                             sb.append('"');
                             break;
                         case '6':
                             sb.append('&');
                             break;
                         case '7':
                             sb.append('\'');
                             break;
                         case '8':
                             sb.append('(');
                             break;
                         case '9':
                             sb.append(')');
                             break;
                         case 'c':
                             sb.append(',');
                             break;
                         case 'f':
                             sb.append('/');
                             break;
                     }
                 }
                 else if (c2 == '3')
                 {
                     switch (c3)
                     {
                         case 'a':
                             sb.append(':');
                             break;
                         case 'c':
                             sb.append('<');
                             break;
                         case 'e':
                             sb.append('>');
                             break;
                     }
                 }
                 else if (c2 == '4')
                 {
                     if (c3 == '0')
                         sb.append("@");
                 }
                 else if (c2 == '5')
                 {
                     if (c3 == 'c')
                         sb.append("\\");
                 }
                 else if (c2 == '7')
                 {
                     switch (c3)
                     {
                         case 'b':
                             sb.append('{');
                             break;
                         case 'd':
                             sb.append('}');
                             break;
                     }
                 }
             }
             else
             {
                 sb.append(c1);
             }
         }
         return sb.toString();
     }

  
}
