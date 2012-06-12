package com.focus.util;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;
public class ZipUtil {
	public static String compress(String str) throws IOException {
	    if (str == null || str.length() == 0) {
	      return str;
	    }
	    ByteArrayOutputStream out = new ByteArrayOutputStream();
	    GZIPOutputStream gzip = new GZIPOutputStream(out);
	    gzip.write(str.getBytes("UTF-8"));
	    gzip.close();
	    return out.toString("UTF-8");
	  }

	  // ��ѹ��
	  public static String uncompress(String str) throws IOException {
	    if (str == null || str.length() == 0) {
	      return str;
	    }
	    ByteArrayOutputStream out = new ByteArrayOutputStream();
	    ByteArrayInputStream in = new ByteArrayInputStream(str
	        .getBytes("UTF-8"));
	    GZIPInputStream gunzip = new GZIPInputStream(in);
	    byte[] buffer = new byte[256];
	    int n;
	    while ((n = gunzip.read(buffer)) >= 0) {
	      out.write(buffer, 0, n);
	    }
	    // toString()ʹ��ƽ̨Ĭ�ϱ��룬Ҳ������ʽ��ָ����toString("GBK")
	    return out.toString();
	  }

	  // ���Է���
	  public static void main(String[] args) throws IOException {
	    System.out.println(ZipUtil.uncompress(ZipUtil.compress("�й�China")));
	  }
}
