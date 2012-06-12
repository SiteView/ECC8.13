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

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.RandomAccessFile;
import java.util.Date;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import com.siteview.ecc.api.APIEntity;

import jgl.Array;
import jgl.HashMap;
import jgl.Pair;

// Referenced classes of package com.dragonflow.Utils:
// Braf, I18N, TextUtils

public class FileUtils
{

    public static final int DEFAULT_BUFFER_SIZE = 32768;
    public static final String INI_LINE_SEPARATOR = "\r\n";
    public static final int INI_LINE_SEPARATOR_LEN = "\r\n".length();
    public static final String INI_EQUAL = "=";
    public static final String INI_SECTION_PREFIX = "[";
    static jgl.HashMap fileLockMap = new HashMap();
    public static boolean singleMatchOnly = false;
    public static final int SEARCHING = 0;
    public static final int RECORDING = 1;
    public static final int DONE = 2;
    public static final int START_TAG = 0;
    public static final int END_TAG = 1;

    public FileUtils()
    {
    }

    public static java.io.PrintWriter MakeOutputWriter(java.io.OutputStream outputstream)
        throws java.io.IOException
    {
        return com.dragonflow.Utils.FileUtils.MakeOutputWriter(outputstream, com.dragonflow.Utils.I18N.nullEncoding());
    }

    public static java.io.PrintWriter MakeOutputWriter(java.io.OutputStream outputstream, String s)
        throws java.io.IOException
    {
        if(s == null || s.length() == 0)
        {
            return new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputstream)));
        } else
        {
            return new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputstream, s)));
        }
    }

    public static java.io.BufferedReader MakeInputReader(java.io.InputStream inputstream)
        throws java.io.IOException
    {
        return new BufferedReader(new InputStreamReader(inputstream, com.dragonflow.Utils.I18N.nullEncoding()));
    }

    public static java.io.PrintWriter MakeUTF8OutputWriter(java.io.OutputStream outputstream)
        throws java.io.IOException
    {
        return new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputstream, "UTF-8")));
    }

    public static java.io.BufferedReader MakeUTF8InputReader(java.io.InputStream inputstream)
        throws java.io.IOException
    {
        return new BufferedReader(new InputStreamReader(inputstream, "UTF-8"));
    }

    public static java.io.PrintWriter MakeEncodedOutputWriter(java.io.OutputStream outputstream, String s)
        throws java.io.IOException
    {
		if(s.endsWith("firstFlash.dyn"))
			System.out.println("here");
        return new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputstream, s)));
    }

    public static java.io.BufferedReader MakeInputReader(java.io.InputStream inputstream, String s)
        throws java.io.IOException
    {
        if(s == null || s.length() <= 0)
        {
            return new BufferedReader(new InputStreamReader(inputstream));
        } else
        {
            return new BufferedReader(new InputStreamReader(inputstream, s));
        }
    }

    public static java.io.BufferedReader MakeEncodedInputReader(java.io.InputStream inputstream, String s)
        throws java.io.IOException
    {
        return com.dragonflow.Utils.FileUtils.MakeInputReader(inputstream, s);
    }

    public static String stackTraceText(Throwable throwable)
    {
        String s = "";
        try
        {
            java.io.ByteArrayOutputStream bytearrayoutputstream = new ByteArrayOutputStream();
            java.io.PrintWriter printwriter = com.dragonflow.Utils.FileUtils.MakeOutputWriter(bytearrayoutputstream);
            throwable.printStackTrace(printwriter);
            printwriter.flush();
            bytearrayoutputstream.flush();
            s = bytearrayoutputstream.toString();
            printwriter.close();
            bytearrayoutputstream.close();
        }
        catch(java.io.IOException ioexception) { }
        return s;
    }

    public static boolean copyFile(String s, String s1)
    {
        return com.dragonflow.Utils.FileUtils.copyFile(new File(s), new File(s1));
    }

    public static boolean copyFile(java.io.File file, java.io.File file1)
    {
        return com.dragonflow.Utils.FileUtils.copyFile(file, file1, (String[][])null);
    }

    public static boolean copyFile(String s, String s1, String as[][])
    {
        return com.dragonflow.Utils.FileUtils.copyFile(new File(s), new File(s1), as);
    }

    public static boolean copyFile(java.io.File file, java.io.File file1, String as[][])
    {
        return com.dragonflow.Utils.FileUtils.copyFile(file, file1, as, 0L, -1L);
    }

    public static boolean copyFile(java.io.File file, java.io.File file1, long l)
    {
        return com.dragonflow.Utils.FileUtils.copyFile(file, file1, (String[][])null, l, -1L);
    }

    public static boolean copyFile(java.io.File file, java.io.File file1, long l, long l1)
    {
        return com.dragonflow.Utils.FileUtils.copyFile(file, file1, (String[][])null, l, l1);
    }

    public static boolean copyFile(java.io.File file, java.io.File file1, String as[][], long l, long l1)
    {
        boolean flag = false;
        try
        {
            com.dragonflow.Utils.FileUtils.internalCopyFile(file, file1, as, l, l1);
            flag = true;
        }
        catch(Exception exception)
        {
            System.out.println("Error" + exception.getMessage());
            com.dragonflow.Log.LogManager.log("Error", exception.getMessage());
        }
        return flag;
    }

    public static void copyFileThrow(java.io.File file, java.io.File file1)
        throws java.io.IOException
    {
        com.dragonflow.Utils.FileUtils.internalCopyFile(file, file1, (String[][])null, 0L, -1L);
    }

    public static void internalCopyFile(java.io.File file, java.io.File file1, String as[][], long l, long l1)
        throws java.io.IOException
    {
        java.io.FileInputStream fileinputstream = null;
        java.io.FileOutputStream fileoutputstream = null;
        java.io.File file2 = file1.getParentFile();
        if(!file2.exists())
        {
            file2.mkdirs();
        }
        if(!file.exists())
        {
            throw new IOException("Could not find source file for copy: " + file.getAbsolutePath());
        }
        if(!file.canRead())
        {
            throw new IOException("Can not read source file for copy: " + file.getAbsolutePath());
        }
        if(file1.exists() && !file1.canWrite())
        {
            throw new IOException("Can not write destination file for copy: " + file1.getAbsolutePath());
        }
        if(l1 > 0x7fffffffL)
        {
            throw new IOException("MaxBytes is too large for copy: " + l1);
        }
        java.io.BufferedOutputStream bufferedoutputstream = null;
        java.io.BufferedInputStream bufferedinputstream = null;
        try
        {
            fileinputstream = new FileInputStream(file);
            bufferedinputstream = new BufferedInputStream(fileinputstream, 32768);
            if(l > 0L)
            {
                bufferedinputstream.skip(l);
            }
            fileoutputstream = new FileOutputStream(file1);
            bufferedoutputstream = new BufferedOutputStream(fileoutputstream, 32768);
            if(as == null || as.length == 0)
            {
                int i = 0;
                byte abyte0[] = new byte[32768];
                if(l1 >= 0L)
                {
                    do
                    {
                        if((i = bufferedinputstream.read(abyte0)) == -1)
                        {
                            break;
                        }
                        if(l1 < (long)i)
                        {
                            bufferedoutputstream.write(abyte0, 0, (int)l1);
                            break;
                        }
                        bufferedoutputstream.write(abyte0, 0, i);
                        l1 -= i;
                    } while(true);
                } else
                {
                    while((i = bufferedinputstream.read(abyte0)) != -1) 
                    {
                        bufferedoutputstream.write(abyte0, 0, i);
                    }
                }
            } else
            {
                java.io.BufferedReader bufferedreader = com.dragonflow.Utils.FileUtils.MakeInputReader(bufferedinputstream);
                java.io.PrintWriter printwriter = com.dragonflow.Utils.FileUtils.MakeOutputWriter(bufferedoutputstream);
                boolean flag = false;
                String s;
                for(; (s = bufferedreader.readLine()) != null; printwriter.println(s))
                {
                    if(singleMatchOnly && flag)
                    {
                        continue;
                    }
                    for(int j = 0; j < as.length; j++)
                    {
                        int k = s.indexOf(as[j][0]);
                        if(k >= 0)
                        {
                            s = s.substring(0, k) + as[j][1] + s.substring(k + as[j][0].length());
                            flag = true;
                        }
                    }

                }

                printwriter.flush();
            }
            bufferedoutputstream.flush();
        }
        catch(java.io.FileNotFoundException filenotfoundexception)
        {
            System.out.println("File not found exception in copying " + file.getName() + " to " + file1.getName());
            throw new IOException("File not found exception in copying " + file.getName() + " to " + file1.getName());
        }
        catch(java.io.IOException ioexception)
        {
            System.out.println("IO Exception copying " + file.getName() + " to " + file1.getName());
            throw new IOException("IO Exception copying " + file.getName() + " to " + file1.getName());
        }
        finally
        {
            if(bufferedoutputstream != null)
            {
                try
                {
                    bufferedoutputstream.close();
                }
                catch(java.io.IOException ioexception1)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.internalCopyFile()" + ioexception1.getMessage());
                    ioexception1.printStackTrace();
                }
            }
            if(bufferedinputstream != null)
            {
                try
                {
                    bufferedinputstream.close();
                }
                catch(java.io.IOException ioexception2)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.internalCopyFile()" + ioexception2.getMessage());
                    ioexception2.printStackTrace();
                }
            }
            if(fileinputstream != null)
            {
                try
                {
                    fileinputstream.close();
                }
                catch(java.io.IOException ioexception3)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.internalCopyFile()" + ioexception3.getMessage());
                    ioexception3.printStackTrace();
                }
            }
            if(fileoutputstream != null)
            {
                try
                {
                    fileoutputstream.close();
                }
                catch(java.io.IOException ioexception4)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.internalCopyFile()" + ioexception4.getMessage());
                    ioexception4.printStackTrace();
                }
            }
        }
    }

    public static String getTextChunk(java.io.File file, String s, String s1)
    {
        String as[][] = {
            {
                s, s1
            }
        };
        String as1[] = com.dragonflow.Utils.FileUtils.getTextChunks(file, as);
        return as1[0];
    }

    public static String[] getTextChunks(java.io.File file, String as[][])
    {
        return com.dragonflow.Utils.FileUtils.getTextChunks(file, as, -1);
    }

    public static String[] getTextChunks(java.io.File file, String as[][], int i)
    {
        java.io.FileInputStream fileinputstream = null;
        StringBuffer astringbuffer[] = new StringBuffer[as.length];
        java.io.BufferedReader bufferedreader = null;
        int ai[] = new int[as.length];
        int j = 0;
        for(int k = 0; k < astringbuffer.length; k++)
        {
            astringbuffer[k] = new StringBuffer();
            ai[k] = 0;
        }

        try
        {
            fileinputstream = new FileInputStream(file);
            bufferedreader = com.dragonflow.Utils.FileUtils.MakeInputReader(fileinputstream);
            do
            {
                String s;
                if((s = bufferedreader.readLine()) == null)
                {
                    break;
                }
                for(int l = 0; l < ai.length; l++)
                {
                    if(ai[l] == 1)
                    {
                        if(s.startsWith(as[l][1]))
                        {
                            ai[l] = 2;
                            j++;
                            if(l == i)
                            {
                                j = ai.length;
                            }
                            continue;
                        }
                        if(astringbuffer[l].length() > 0)
                        {
                            astringbuffer[l].append('\n');
                        }
                        astringbuffer[l].append(s);
                        continue;
                    }
                    if(ai[l] == 0 && s.startsWith(as[l][0]))
                    {
                        ai[l] = 1;
                    }
                }

            } while(j != ai.length);
        }
        catch(java.io.IOException ioexception) { }
        finally
        {
            if(fileinputstream != null)
            {
                try
                {
                    fileinputstream.close();
                }
                catch(java.io.IOException ioexception1)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.getTextChunks()" + ioexception1.getMessage());
                    ioexception1.printStackTrace();
                }
            }
            if(bufferedreader != null)
            {
                try
                {
                    bufferedreader.close();
                }
                catch(java.io.IOException ioexception2)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.getTextChunks()" + ioexception2.getMessage());
                    ioexception2.printStackTrace();
                }
            }
        }
        String as1[] = new String[astringbuffer.length];
        for(int i1 = 0; i1 < astringbuffer.length; i1++)
        {
            as1[i1] = astringbuffer[i1].toString();
        }

        return as1;
    }

    public static void writeFile(String filaname, String s1)
        throws java.io.IOException
    {
		if(filaname.endsWith("firstFlash.dyn"))
			System.out.println("okok!");
		
        java.io.PrintWriter printwriter = com.dragonflow.Utils.FileUtils.MakeOutputWriter(new FileOutputStream(filaname));
        printwriter.print(s1);
        printwriter.close();
    }

    public static void appendFile(String s, String s1)
        throws java.io.IOException
    {
        java.io.RandomAccessFile randomaccessfile = new RandomAccessFile(s, "rw");
        try
        {
            randomaccessfile.seek(randomaccessfile.length());
            randomaccessfile.writeBytes(s1);
        }
        finally
        {
            try
            {
                randomaccessfile.close();
            }
            catch(java.io.IOException ioexception)
            {
                com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.appendFile()" + ioexception.getMessage());
                ioexception.printStackTrace();
            }
        }
    }

    public static StringBuffer readFile(String fileName)
        throws java.io.IOException
    {
        java.io.FileInputStream fileinputstream = null;
        StringBuffer stringbuffer = new StringBuffer();
        fileinputstream = new FileInputStream(fileName);
        int i = 0;
        byte abyte0[] = new byte[32768];
        try
        {
            while((i = fileinputstream.read(abyte0)) != -1) 
            {
                stringbuffer.append(new String(abyte0, 0, 0, i));
            }
        }
        finally
        {
            try
            {
                fileinputstream.close();
            }
            catch(java.io.IOException ioexception)
            {
                com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.readFile()" + ioexception.getMessage());
                ioexception.printStackTrace();
            }
        }
        return stringbuffer;
    }

    public static StringBuffer readCharFile(String fileName)
        throws java.io.IOException
    {
        java.io.FileReader filereader = new FileReader(fileName);
        StringBuffer stringbuffer = new StringBuffer();
        char ac[] = new char[32768];
        int i = 0;
        try
        {
            while((i = filereader.read(ac, 0, 32768)) != -1) 
            {
                stringbuffer.append(ac, 0, i);
            }
        }
        finally
        {
            try
            {
                filereader.close();
            }
            catch(java.io.IOException ioexception)
            {
                com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.readCharFile()" + ioexception.getMessage());
                ioexception.printStackTrace();
            }
        }
        return stringbuffer;
    }

    public static StringBuffer readUTF8File(String filename)
        throws java.io.IOException
    {
		System.out.println("readUTF8File --->" + filename);
        return com.dragonflow.Utils.FileUtils.readEncFile(filename, "UTF-8");
    }

    public static StringBuffer readEncFile(String s, String s1)
        throws java.io.IOException
    {
		if(s.endsWith("chinese.mg"))
		{
			System.out.println(s);
		}
		java.io.FileInputStream fileinputstream = null;
		
        StringBuffer stringbuffer = new StringBuffer();
        try
        {
            fileinputstream = new FileInputStream(s);
        }
        catch(java.io.IOException ioexception)
        {
            try
            {
                int j = 0;
                do
                {
                    if(j >= s.length())
                    {
                        break;
                    }
                    if(s.charAt(j) > '\177')
                    {
                        boolean flag = com.dragonflow.Utils.I18N.testing;
                        com.dragonflow.Utils.I18N.testing = false;
                        String s2 = com.dragonflow.Utils.I18N.toDefaultEncoding(s);
                        com.dragonflow.Utils.I18N.testing = flag;
                        fileinputstream = new FileInputStream(s2);
                        break;
                    }
                    j++;
                } while(true);
                if(fileinputstream == null)
                {
                    throw ioexception;
                }
            }
            catch(java.io.IOException ioexception1)
            {
                throw ioexception1;
            }
        }
        int i = 0;
        byte abyte0[] = new byte[32768];
        boolean flag1 = true;
        boolean flag2 = false;
        try
        {
            while((i = fileinputstream.read(abyte0)) != -1) 
            {
                String s3 = new String(abyte0, 0, i,s1);
                if(flag2 || flag1 && s3.indexOf("_fileEncoding") >= 0)
                {
                    s3 = new String(abyte0, 0, i, s1);
                    flag2 = true;
                } else
                if(com.dragonflow.Utils.I18N.isI18N && com.dragonflow.Utils.I18N.isNullEncoding(s3))
                {
                    s3 = com.dragonflow.Utils.I18N.toNullEncoding(s3);
                }
				
                stringbuffer.append(s3);
                flag1 = false;
            }
        }
        finally
        {
            try
            {
                fileinputstream.close();
            }
            catch(java.io.IOException ioexception2)
            {
                com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.readEncFile()" + ioexception2.getMessage());
                ioexception2.printStackTrace();
            }
        }
        return stringbuffer;
    }

    public static long findOffsetForDate(String s, java.util.Date date)
    {
        return com.dragonflow.Utils.FileUtils.findOffsetForDate(new File(s), date);
    }

    public static long findOffsetForDate(java.io.File file, java.util.Date date)
    {
        long l = 0L;
        java.io.RandomAccessFile randomaccessfile = null;
        try
        {
            randomaccessfile = new RandomAccessFile(file, "r");
            String s = randomaccessfile.readLine();
            java.util.Date date1 = com.dragonflow.Utils.TextUtils.stringToDate(s);
            int i = 60000;
            java.util.Date date2 = new Date(date.getTime() - (long)i);
            if(date.getTime() > date1.getTime() + (long)i)
            {
                long l1 = 0L;
                long l2 = randomaccessfile.length();
                long l3 = (l1 + l2) / 2L;
                java.util.Date date3 = new Date(0L);
                Object obj = null;
                randomaccessfile.seek(l3);
                do
                {
                    String s1 = randomaccessfile.readLine();
                    long l4 = randomaccessfile.getFilePointer();
                    s1 = randomaccessfile.readLine();
                    if(s1 == null)
                    {
                        break;
                    }
                    java.util.Date date4 = date3;
                    date3 = com.dragonflow.Utils.TextUtils.stringToDate(s1);
                    if(date3 == null)
                    {
                        break;
                    }
                    if(date3.after(date2) && date3.before(date) || date3.equals(date4))
                    {
                        l = l4;
                        break;
                    }
                    if(date3.before(date))
                    {
                        l1 = l4;
                        l4 = (l4 + l2) / 2L;
                    } else
                    {
                        l2 = l4;
                        l4 = (l4 + l1) / 2L;
                    }
                    randomaccessfile.seek(l4);
                } while(true);
            }
        }
        catch(java.io.IOException ioexception) { }
        finally
        {
            if(randomaccessfile != null)
            {
                try
                {
                    randomaccessfile.close();
                }
                catch(java.io.IOException ioexception1) { }
            }
        }
        return l;
    }

    public static String getGroupNewFileName()
    {
        String s = "Group";
        String s1 = s + "0.mg";
        java.io.File file = new File(com.dragonflow.SiteView.Platform.getRoot() + "/groups/");
        if(file.exists())
        {
            String as[] = file.list();
            int i = 0;
            do
            {
                if(i >= 10000)
                {
                    break;
                }
                s1 = s + i;
                if(as[i].indexOf(s1 + ".mg") < 0)
                {
                    break;
                }
                i++;
            } while(true);
        }
        return s1;
    }

    public static boolean deleteDuplicateLines(java.io.File file, java.io.File file1)
    {
        java.io.FileInputStream fileinputstream = null;
        java.io.FileOutputStream fileoutputstream = null;
        boolean flag = false;
        if(!file.exists())
        {
            com.dragonflow.Log.LogManager.log("Error", "Could not find source file for copy: " + file.getAbsolutePath());
            return false;
        }
        if(!file.canRead())
        {
            com.dragonflow.Log.LogManager.log("Error", "Can not read source file for copy: " + file.getAbsolutePath());
            return false;
        }
        if(file1.exists() && !file1.canWrite())
        {
            com.dragonflow.Log.LogManager.log("Error", "Can not write destination file for copy: " + file1.getAbsolutePath());
            return false;
        }
        try
        {
            fileinputstream = new FileInputStream(file);
            java.io.BufferedInputStream bufferedinputstream = new BufferedInputStream(fileinputstream, 32768);
            java.io.BufferedReader bufferedreader = com.dragonflow.Utils.FileUtils.MakeInputReader(bufferedinputstream);
            fileoutputstream = new FileOutputStream(file1);
            java.io.BufferedOutputStream bufferedoutputstream = new BufferedOutputStream(fileoutputstream, 32768);
            java.io.PrintWriter printwriter = com.dragonflow.Utils.FileUtils.MakeOutputWriter(bufferedoutputstream);
            String s;
            for(String s1 = ""; (s = bufferedreader.readLine()) != null; s1 = s)
            {
                if(!s.equals(s1))
                {
                    printwriter.println(s);
                }
            }

            printwriter.flush();
            bufferedoutputstream.flush();
            flag = true;
        }
        catch(java.io.FileNotFoundException filenotfoundexception)
        {
            com.dragonflow.Log.LogManager.log("Error", "File not found exception in copying " + file.getName() + " to " + file1.getName());
        }
        catch(java.io.IOException ioexception)
        {
            com.dragonflow.Log.LogManager.log("Error", "IO Exception copying " + file.getName() + " to " + file1.getName());
        }
        finally
        {
            if(fileinputstream != null)
            {
                try
                {
                    fileinputstream.close();
                }
                catch(java.io.IOException ioexception1)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.deleteDuplicateLines()" + ioexception1.getMessage());
                    ioexception1.printStackTrace();
                }
            }
            if(fileoutputstream != null)
            {
                try
                {
                    fileoutputstream.close();
                }
                catch(java.io.IOException ioexception2)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.deleteDuplicateLines()" + ioexception2.getMessage());
                    ioexception2.printStackTrace();
                }
            }
        }
        return flag;
    }

    public static boolean delete(String filename)
    {
        return delete(new File(filename));
    }

    public static boolean delete(File file)
    {
        if(!file.exists())
        {
            return false;
        }
        if(file.isDirectory())
        {
            deleteFilesInDirectory(file);
        }
        // add by hailong.yi
        APIEntity.deleteByFileName(file);
        return file.delete();
    }

    public static int deleteFilesInDirectory(File file)
    {
        int i = 0;
        if(file.exists() && file.isDirectory())
        {
            String as[] = file.list();
            if(as != null)
            {
                for(int j = 0; j < as.length; j++)
                {
                    delete(new File(file, as[j]));
                    i++;
                }

            }
        }
        return i;
    }

    public static boolean addCheckPre(String s)
    {
        String s1 = com.dragonflow.SiteView.Platform.getRoot() + "/logs";
        java.io.FileInputStream fileinputstream = null;
        java.io.FileOutputStream fileoutputstream = null;
        boolean flag = false;
        try
        {
            java.io.File file = new File(s1 + "/" + s);
            if(file.exists())
            {
                fileinputstream = new FileInputStream(s1 + "/" + s);
                String s2 = "<pre>\n";
                byte abyte0[] = new byte[s2.length()];
                fileinputstream.read(abyte0, 0, s2.length());
                String s3 = new String(abyte0);
                if(!s3.equals(s2))
                {
                    byte abyte1[] = s2.getBytes();
                    byte abyte2[] = new byte[(int)file.length()];
                    fileinputstream.read(abyte2, 0, (int)file.length());
                    fileoutputstream = new FileOutputStream(s1 + "/" + s);
                    fileoutputstream.write(abyte1);
                    fileoutputstream.write(abyte0);
                    fileoutputstream.write(abyte2);
                }
                flag = true;
            }
        }
        catch(Exception exception) { }
        finally
        {
            if(fileoutputstream != null)
            {
                try
                {
                    fileoutputstream.close();
                }
                catch(java.io.IOException ioexception)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.addCheckPre()" + ioexception.getMessage());
                    ioexception.printStackTrace();
                }
            }
            if(fileinputstream != null)
            {
                try
                {
                    fileinputstream.close();
                }
                catch(java.io.IOException ioexception1)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.addCheckPre()" + ioexception1.getMessage());
                    ioexception1.printStackTrace();
                }
            }
        }
        return flag;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param args
     */
    public static void main(String args[])
    {
        if(args.length < 2)
        {
            System.err.println("FileUtils requires source and dest files");
            return;
        }
        if(args[0].equals("-tail"))
        {
        com.dragonflow.Utils.Braf braf;        
        try {
        long l = 2000L;
        String s = args[1];
        if(args.length > 2)
        {
            l = com.dragonflow.Utils.TextUtils.toInt(args[2]);
        }
        System.out.println("reading last " + l + " bytes from " + s);
        l = (new File(s)).length() - l;
        if(l < 0L)
        {
            l = 0L;
        }
        braf = new Braf(s, l);

    while (true) {    
    String s1;
        s1 = braf.readLine();
        if(s1 == null)
        {
            return;
        }
        System.out.println(s1);
    }
        }
        catch(Exception exception)
        {
            /* empty */
        }
        }
        else {

        String args1[][] = new String[args.length / 2 - 1][2];
        for(int i = 2; i + 1 < args.length; i += 2)
        {
            System.err.println(args[i] + " -- " + args[i + 1]);
            args1[i / 2 - 1][0] = args[i];
            args1[i / 2 - 1][1] = args[i + 1];
        }

        if(com.dragonflow.Utils.FileUtils.copyFile(args[0], args[1], args1))
        {
            System.out.println("copy succeeded");
        } else
        {
            System.out.println("copy failed");
        }
        System.exit(0);
        }
        if(com.dragonflow.Utils.FileUtils.copyFile(args[0], args[1]))
        {
            System.out.println("copy succeeded");
        } else
        {
            System.out.println("copy failed");
        }
        System.exit(0);
        com.dragonflow.Utils.FileUtils.deleteDuplicateLines(new File(args[0]), new File(args[1]));
        System.exit(0);
        long l1 = com.dragonflow.Utils.FileUtils.findOffsetForDate("..\\SiteView.log.82597", new Date(97, 7, 10));
        System.err.println("OFFSET=" + l1);
        System.exit(0);
        return;
    }

    public static void mergeIniFiles(String filanme, String s1)
        throws java.io.IOException
    {
        StringBuffer stringbuffer = com.dragonflow.Utils.FileUtils.readFile(filanme);
        String s2 = stringbuffer.toString();
        String s4 = "";
        String s5 = "";
        String s7 = "";
        java.io.BufferedReader bufferedreader = new BufferedReader(new FileReader(s1));
        try
        {
            do
            {
                String s3;
                if((s3 = bufferedreader.readLine()) == null)
                {
                    break;
                }
                if(s3.startsWith("["))
                {
                    s4 = s3.trim();
                } else
                if(s4.length() > 0)
                {
                    int i = s3.indexOf("=");
                    if(i > 0)
                    {
                        String s6 = s3.substring(0, i).trim();
                        String s8 = s3.substring(i + "=".length()).trim();
                        if(s6.length() > 0 && s8.length() > 0)
                        {
                            com.dragonflow.Utils.FileUtils.writeToIniFile(stringbuffer, s2, s4, s6, s8);
                        }
                    }
                }
            } while(true);
        }
        finally
        {
            try
            {
                bufferedreader.close();
            }
            catch(java.io.IOException ioexception)
            {
                com.dragonflow.Log.LogManager.log("Error", "Exception in FileUtils.mergeIniFiles()" + ioexception.getMessage());
                ioexception.printStackTrace();
            }
        }
        com.dragonflow.Utils.FileUtils.writeFile(filanme, stringbuffer.toString());
    }

    public static void writeToIniFile(String s, String s1, String s2, String s3)
        throws java.io.IOException
    {
		if(s.endsWith("firstFlash.dyn"))
			System.out.println("here");
        StringBuffer stringbuffer = com.dragonflow.Utils.FileUtils.readFile(s);
        String s4 = stringbuffer.toString();
        com.dragonflow.Utils.FileUtils.writeToIniFile(stringbuffer, s4, s1, s2, s3);
        com.dragonflow.Utils.FileUtils.writeFile(s, stringbuffer.toString());
    }

    private static void writeToIniFile(StringBuffer stringbuffer, String s, String s1, String s2, String s3)
    {
		if(s.endsWith("firstFlash.dyn"))
			System.out.println("here");
		
        int i = s.indexOf("\r\n" + s1);
        if(i == -1)
        {
            String s4 = "\r\n" + s1 + "\r\n" + s2 + "=" + s3 + "\r\n" + "\r\n";
            stringbuffer.append(s4);
        } else
        {
            int j = s.indexOf(s2, i + s1.length());
            int k = s.indexOf("\r\n", j);
            if(j > -1)
            {
                stringbuffer.replace(j + s2.length(), k, "=" + s3);
            } else
            {
                int l = s.indexOf("\r\n", i + INI_LINE_SEPARATOR_LEN);
                stringbuffer.insert(l + INI_LINE_SEPARATOR_LEN, s2 + "=" + s3 + "\r\n");
            }
        }
    }

    public static jgl.Array getIniSection(String s, String s1)
        throws java.io.IOException
    {
        jgl.Array array = new Array();
        String s2 = com.dragonflow.Utils.FileUtils.readFile(s).toString();
        int i = s2.indexOf("\r\n" + s1);
        int j = s2.indexOf("\r\n[", i + INI_LINE_SEPARATOR_LEN + s1.length());
        if(j == -1)
        {
            j = s2.length();
        }
        if(i > -1 && i + s1.length() + INI_LINE_SEPARATOR_LEN < j)
        {
            String s3 = s2.substring(i + INI_LINE_SEPARATOR_LEN + s1.length() + INI_LINE_SEPARATOR_LEN, j);
            int l = 0;
            boolean flag = false;
            do
            {
                if(l == s3.length())
                {
                    break;
                }
                int i1 = s3.indexOf("\r\n", l);
                String s4 = s3.substring(l, i1);
                l = i1 + INI_LINE_SEPARATOR_LEN;
                int k = s4.indexOf("=");
                if(k != -1)
                {
                    String s5 = s4.substring(0, k);
                    String s6 = s4.substring(k + "=".length());
                    array.add(new Pair(s5.trim(), s6.trim()));
                }
            } while(true);
        }
        return array;
    }

    public static Object getFileLock(String s)
    {
        s = (new File(s)).getAbsolutePath();
        Object obj = fileLockMap.get(s);
        if(obj == null)
        {
            synchronized(fileLockMap)
            {
                obj = fileLockMap.get(s);
                if(obj == null)
                {
                    obj = new Object();
                    fileLockMap.add(s, obj);
                }
            }
        }
        return obj;
    }

    public static boolean writeBytesToFile(byte abyte0[], String s)
    {
        return com.dragonflow.Utils.FileUtils.writeBytesToFile(abyte0, s, false, 0);
    }

    public static boolean writeBytesToFile(byte abyte0[], String s, boolean flag, int i)
    {
		if(s.endsWith("firstFlash.dyn"))
			System.out.println("here");
        java.io.File file = (new File(s)).getParentFile();
        if(!file.exists())
        {
            file.mkdirs();
        }
        Object obj = null;
        boolean flag1 = true;
        synchronized(com.dragonflow.Utils.FileUtils.getFileLock(s))
        {
            try
            {
                Object obj1;
                if(flag)
                {
                    obj1 = new ZipOutputStream(new FileOutputStream(s));
                    ((java.util.zip.ZipOutputStream)obj1).setLevel(i);
                    java.util.zip.ZipEntry zipentry = new ZipEntry(s);
                    ((java.util.zip.ZipOutputStream)obj1).putNextEntry(zipentry);
                } else
                {
                    obj1 = new FileOutputStream(s);
                }
                ((java.io.OutputStream) (obj1)).write(abyte0);
                ((java.io.OutputStream) (obj1)).close();
            }
            catch(java.io.IOException ioexception)
            {
                com.dragonflow.Log.LogManager.log("Error", "FileUtils: Failed to write binary file: " + s + ", exception: " + ioexception.getMessage());
                flag1 = false;
            }
        }
        return flag1;
    }

    public static void verifyFileExists(String s, boolean flag)
    {
        java.io.File file = new File(s);
        if(flag)
        {
            file.mkdirs();
        } else
        {
            java.io.File file1 = file.getParentFile();
            file1.mkdirs();
            try
            {
                file.createNewFile();
            }
            catch(java.io.IOException ioexception)
            {
                ioexception.printStackTrace();
            }
        }
    }

    public static byte[] readFileToByteArray(String s)
    {
        byte abyte0[] = new byte[32768];
        boolean flag = false;
        java.io.ByteArrayOutputStream bytearrayoutputstream = null;
        try
        {
            java.io.FileInputStream fileinputstream = new FileInputStream(s);
            bytearrayoutputstream = new ByteArrayOutputStream();
            do
            {
                int i = fileinputstream.read(abyte0);
                if(i == -1)
                {
                    break;
                }
                bytearrayoutputstream.write(abyte0, 0, i);
            } while(true);
        }
        catch(java.io.IOException ioexception)
        {
            com.dragonflow.Log.LogManager.log("Error", "FileUtils: Failed to read binary file: " + s + ", exception: " + ioexception.getMessage());
        }
        return bytearrayoutputstream.toByteArray();
    }

    public static void copyBinaryFile(String s, String s1)
        throws java.io.IOException
    {
        java.io.FileOutputStream fileoutputstream = new FileOutputStream(s1);
        com.dragonflow.Utils.FileUtils.copyBinaryFileToStream(s, fileoutputstream);
    }

    public static void copyBinaryFileToStream(String s, java.io.OutputStream outputstream)
        throws java.io.IOException
    {
        byte abyte0[] = new byte[32768];
        boolean flag = false;
        java.io.FileInputStream fileinputstream = new FileInputStream(s);
        java.io.ByteArrayOutputStream bytearrayoutputstream = new ByteArrayOutputStream();
        do
        {
            int i = fileinputstream.read(abyte0);
            if(i != -1)
            {
                bytearrayoutputstream.write(abyte0, 0, i);
            } else
            {
                bytearrayoutputstream.writeTo(outputstream);
                return;
            }
        } while(true);
    }

}
