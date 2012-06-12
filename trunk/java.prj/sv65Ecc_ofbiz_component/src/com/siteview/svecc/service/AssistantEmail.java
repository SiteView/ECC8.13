package com.siteview.svecc.service;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

public class AssistantEmail {
	
	public static Map<?,?> getTimeString(String select,String startTime,String endTime,Map<?,?> context){
		String scheduleStart,scheduleEnd;
		boolean flag=false;
		Map<String,Object> retMap=new HashMap<String, Object>();
		if(((String)context.get(select)).equals("disabled")){			
			scheduleStart="";
			scheduleEnd="";
			 flag=true;
		}else{
			scheduleStart=(String)context.get(startTime);
			scheduleEnd=(String)context.get(endTime);
			 
			 if(scheduleStart!=null&&scheduleEnd!=null){
				 String timeStart0[]= scheduleStart.split(":");
				 String timeEnd0[]= scheduleEnd.split(":");
				 if(timeStart0.length==2&&timeEnd0.length==2){	
						 try{
						  int hourStart=Integer.parseInt(timeStart0[0]);
						  int minuteStart=Integer.parseInt(timeStart0[1]);
						 
						  int hourEnd=Integer.parseInt(timeEnd0[0]);
						  int minuteEnd=Integer.parseInt(timeEnd0[1]);
						  	if(hourStart<=24&&hourStart>=0&&minuteStart<=60&&minuteStart>=0&&hourEnd<=24&&hourEnd>=0&&minuteEnd<=60&&minuteEnd>=0&&hourStart<=hourEnd)
						  		flag=true;
						  	}catch(Exception e){							 
							 e.printStackTrace();
						 }
				 }
			 }
		}
		 
		retMap.put("flag", flag);
		retMap.put("scheduleStart", scheduleStart);
		retMap.put("scheduleEnd", scheduleEnd);
		return retMap;
	}
	
	public static Map<?,?> ScheduleOperate(Map<?,?> context){
		Map<String,Object> map=new HashMap<String,Object>();
		String 		time,scheduleStart0,scheduleEnd0,scheduleStart1,scheduleEnd1,scheduleStart2,
		scheduleEnd2,scheduleStart3,scheduleEnd3
		,scheduleStart4,cheduleEnd4,scheduleStart5,scheduleEnd5
		,scheduleStart6,scheduleEnd6;
		boolean flag=true;
		Map map0=getTimeString("select0","scheduleStart0","scheduleEnd0",context);
		scheduleStart0=(String) map0.get("scheduleStart");
		scheduleEnd0=(String) map0.get("scheduleEnd");
		flag=flag&&(Boolean)map0.get("flag");

		
		Map map1=getTimeString("select1","scheduleStart1","scheduleEnd1",context);
		scheduleStart1=(String) map1.get("scheduleStart");
		scheduleEnd1=(String) map1.get("scheduleEnd");
		flag=flag&&(Boolean)map1.get("flag");
		
		Map map2=getTimeString("select2","scheduleStart2","scheduleEnd2",context);
		scheduleStart2=(String) map2.get("scheduleStart");
		scheduleEnd2=(String) map2.get("scheduleEnd");
		flag=flag&&(Boolean)map2.get("flag");
		
		Map map3=getTimeString("select3","scheduleStart3","scheduleEnd3",context);
		scheduleStart3=(String) map3.get("scheduleStart");
		scheduleEnd3=(String) map3.get("scheduleEnd");
		flag=flag&&(Boolean)map3.get("flag");
		
		Map map4=getTimeString("select4","scheduleStart4","scheduleEnd4",context);
		scheduleStart4=(String) map4.get("scheduleStart");
		cheduleEnd4=(String) map4.get("scheduleEnd");
		flag=flag&&(Boolean)map4.get("flag");
		
		Map map5=getTimeString("select5","scheduleStart5","scheduleEnd5",context);
		scheduleStart5=(String) map5.get("scheduleStart");
		scheduleEnd5=(String) map5.get("scheduleEnd");
		flag=flag&&(Boolean)map5.get("flag");
		
		Map map6=getTimeString("select6","scheduleStart6","scheduleEnd6",context);
		scheduleStart6=(String) map6.get("scheduleStart");
		scheduleEnd6=(String) map6.get("scheduleEnd");
		flag=flag&&(Boolean)map6.get("flag");

	
		time=" Sunday"+scheduleStart0+"-"+scheduleEnd0+" Monday"+scheduleStart1+"-"+scheduleEnd1+
		" Tuesday"+scheduleStart2+"-"+scheduleEnd2+" Wednesday"+scheduleStart3+"-"+scheduleEnd3+
		" Thursday"+scheduleStart4+"-"+cheduleEnd4+" Friday"+scheduleStart5+"-"+scheduleEnd5+
		" Saturday"+scheduleStart6+"-"+scheduleEnd6;
		
		map.put("sodier",flag);
		map.put("timeString",time);	

		return map;
	}	
		
	public static String sendMail(String mailServer, String recipient,String subject,String content) { 
		   try {    
		      Socket s = new Socket(mailServer, 25); 
		      BufferedReader in = new BufferedReader 
		          (new InputStreamReader(s.getInputStream(), "8859_1")); 
		      BufferedWriter out = new BufferedWriter 
		          (new OutputStreamWriter(s.getOutputStream(), "8859_1")); 

		      AssistantEmail.send(in, out, "HELO theWorld"); 
		      // warning : some mail server validate the sender address 
		      //           in the MAIL FROm command, put your real address here 
		      AssistantEmail.send(in, out, "MAIL FROM: <Elvis.Presley@jailhouse.rock>"); 
		      AssistantEmail.send(in, out, "RCPT TO: " + recipient); 
		      AssistantEmail.send(in, out, "DATA"); 
		      AssistantEmail.send(out, "Subject: "+"subject"+subject); 
		      AssistantEmail.send(out, "From: deeplylovemycountry@sina.com <deeplylovemycountry@sina.com>"); 
		      AssistantEmail.send (out, "\n");       
		      // message body 
		      AssistantEmail.send(out, "This is the content!"+content); 
		      AssistantEmail.send(out, "\n.\n"); 
		      AssistantEmail.send(in, out, "QUIT"); 
		      s.close(); 
		      } 
		   catch (Exception e) { 
				return e.toString(); 
		      } 
		return "success";
		   } 	
	 
	public static void send(BufferedReader in, BufferedWriter out, String s) { 
		   try { 
		      out.write(s + "\n"); 
		      out.flush(); 
		      System.out.println(s); 
		      s = in.readLine(); 
		      System.out.println(s); 
		      } 
		   catch (Exception e) { 
		      e.printStackTrace(); 
		      } 
		   } 

	public static void send(BufferedWriter out, String s) { 
		   try { 
		      out.write(s + "\n"); 
		      out.flush(); 
		      System.out.println(s); 
		      } 
		   catch (Exception e) { 
		      e.printStackTrace(); 
		      } 
		   }
		 		 
}
