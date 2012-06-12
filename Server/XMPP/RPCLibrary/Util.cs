using System;
using System.Collections.Generic;
using System.Text;
using System.IO.Compression;
using System.IO;

namespace RPCLibrary
{
    public class Util
    {
        public static string Compress(string data)
        {

            MemoryStream decompressMS = new MemoryStream();
            GZipStream zip = new GZipStream(decompressMS, CompressionMode.Compress);

            byte[] buffer = System.Text.Encoding.UTF8.GetBytes(data);

            zip.Write(buffer, 0, buffer.Length);

            zip.Flush();
            zip.Close();

            byte[] temp = decompressMS.ToArray();

            string result = Convert.ToBase64String(temp);

            decompressMS.Close();

            return result;

        }

        public static string Decompress(string data)
        {
            Byte[] compressedBuffer = Convert.FromBase64String(data);

            MemoryStream compressedMS = new MemoryStream(compressedBuffer);

            GZipStream zip = new GZipStream(compressedMS, CompressionMode.Decompress, true);

            byte[] buffer = new byte[1024];
            MemoryStream decompressedMS = new MemoryStream();

            int readBytes = 0;
            while ((readBytes = zip.Read(buffer, 0, 1024)) > 0)
            {
                decompressedMS.Write(buffer, 0, readBytes);
            }

            compressedMS.Close();
            zip.Close();

            byte[] temp = decompressedMS.ToArray();
            string result = System.Text.Encoding.UTF8.GetString(temp);

            decompressedMS.Close();

            return result;
        }

        public static string EscapeNode(string node)
        {
            if (node == null)
                return null;

            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < node.Length; i++)
            {
                /*
                <space> \20
                " 	    \22
                & 	    \26
                ' 	    \27
                (       \28
                )       \29
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
                char c = node[i];
                switch (c)
                {
                    case ' ': sb.Append(@"\20"); break;
                    case '"': sb.Append(@"\22"); break;
                    case '&': sb.Append(@"\26"); break;
                    case '\'': sb.Append(@"\27"); break;
                    case '(': sb.Append(@"\28"); break;
                    case ')': sb.Append(@"\29"); break;
                    case ',': sb.Append(@"\2c"); break;
                    case '/': sb.Append(@"\2f"); break;
                    case ':': sb.Append(@"\3a"); break;
                    case '<': sb.Append(@"\3c"); break;
                    case '>': sb.Append(@"\3e"); break;
                    case '@': sb.Append(@"\40"); break;
                    case '\\': sb.Append(@"\5c"); break;
                    case '{': sb.Append(@"\7b"); break;
                    case '}': sb.Append(@"\7d"); break;
                    default: sb.Append(c); break;
                }
            }
            return sb.ToString();
        }

        public static string UnescapeNode(string node)
        {
            if (node == null)
                return null;

            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < node.Length; i++)
            {
                char c1 = node[i];
                if (c1 == '\\' && i + 2 < node.Length)
                {
                    i += 1;
                    char c2 = node[i];
                    i += 1;
                    char c3 = node[i];
                    if (c2 == '2')
                    {
                        switch (c3)
                        {
                            case '0':
                                sb.Append(' ');
                                break;
                            case '2':
                                sb.Append('"');
                                break;
                            case '6':
                                sb.Append('&');
                                break;
                            case '7':
                                sb.Append('\'');
                                break;
                            case '8':
                                sb.Append('(');
                                break;
                            case '9':
                                sb.Append(')');
                                break;
                            case 'c':
                                sb.Append(',');
                                break;
                            case 'f':
                                sb.Append('/');
                                break;
                        }
                    }
                    else if (c2 == '3')
                    {
                        switch (c3)
                        {
                            case 'a':
                                sb.Append(':');
                                break;
                            case 'c':
                                sb.Append('<');
                                break;
                            case 'e':
                                sb.Append('>');
                                break;
                        }
                    }
                    else if (c2 == '4')
                    {
                        if (c3 == '0')
                            sb.Append("@");
                    }
                    else if (c2 == '5')
                    {
                        if (c3 == 'c')
                            sb.Append("\\");
                    }
                    else if (c2 == '7')
                    {
                        switch (c3)
                        {
                            case 'b':
                                sb.Append('{');
                                break;
                            case 'd':
                                sb.Append('}');
                                break;
                        }
                    }
                }
                else
                {
                    sb.Append(c1);
                }
            }
            return sb.ToString();
        }

        public static bool IsBasicType(string type)
        {
            if (type == null || type == string.Empty)
            {
                return false;
            }

            string[] types = Enum.GetNames(typeof(BasicType));

            foreach (string item in types)
            {
                if (type == item)
                {
                    return true;
                }
            }

            return false;

        }

        public static bool IsExtensionType(string type)
        {
            if (type == null || type == string.Empty)
            {
                return false;
            }

            int index = type.IndexOf('[');

            if (index > 0)
            {
                type = type.Substring(0, index);
            }

            string[] types = Enum.GetNames(typeof(ExtensionType));

            foreach (string item in types)
            {
                if (type == item)
                {
                    return true;
                }
            }

            return false;

        }
    }
}
