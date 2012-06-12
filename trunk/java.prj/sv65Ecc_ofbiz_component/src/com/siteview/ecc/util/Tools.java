package com.siteview.ecc.util;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.http.HttpServletResponse;

public class Tools {
	public static Boolean reflash(HttpServletResponse response)
	{
		PrintWriter pw;
		try {
			pw = response.getWriter();
		} catch (IOException e) {
			e.printStackTrace();
			return Boolean.FALSE;
		}
		sleep(1000);
		pw.write("hello!\n");
		pw.flush();
		sleep(1000);
		pw.write("hello!\n");
		pw.flush();
		sleep(1000);
		pw.write("hello!\n");
		pw.flush();
		sleep(1000);
		pw.write("hello!\n");
		pw.flush();
		sleep(1000);
		pw.write("hello!\n");
		pw.flush();
		sleep(1000);
		pw.write("hello!\n");
		pw.flush();
		sleep(1000);
		pw.write("hello!\n");
		pw.flush();
		sleep(1000);
		pw.write("hello!\n");
		pw.flush();
		return Boolean.TRUE;
		
	}
	public static void sleep(long millis)
	{
		try {
			Thread.sleep(millis);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}
