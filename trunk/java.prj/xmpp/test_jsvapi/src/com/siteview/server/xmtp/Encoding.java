package com.siteview.server.xmtp;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

public class Encoding {
	public String encode(String str)
	{
	    if (str == null || str.length() == 0) {
		      return str;
		    }
	    
	    try{
	    	ByteArrayOutputStream out = new ByteArrayOutputStream();
		    GZIPOutputStream gzip = new GZIPOutputStream(out);
		    
		    gzip.write(str.getBytes("UTF-8"));
		    gzip.close();
		    
		    return (new sun.misc.BASE64Encoder()).encode(out.toByteArray());
		    
	    }catch(Exception e)
	    {
	    	e.printStackTrace();
	    	return null;
	    }
		    
	}
	public String decode(String str)
	{
		if (str == null || str.length() == 0) {
		      return str;
		    }
		 try{
		   byte[] b=(new sun.misc.BASE64Decoder()).decodeBuffer(str);
		
		    ByteArrayOutputStream out = new ByteArrayOutputStream();
		    ByteArrayInputStream in = new ByteArrayInputStream(b);
		    GZIPInputStream gunzip = new GZIPInputStream(in);
		    byte[] buffer = new byte[256];
		    int n;
		    while ((n = gunzip.read(buffer)) >= 0) {
		      out.write(buffer, 0, n);
		    }
		    
		    return out.toString("UTF-8");
		 }catch(Exception e)
		    {
		    	e.printStackTrace();
		    	return null;
		    }
		    
	}
}
