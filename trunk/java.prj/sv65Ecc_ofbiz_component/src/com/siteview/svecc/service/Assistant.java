package com.siteview.svecc.service;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

public class Assistant {

	public static Map<?, ?> getTimeString(String select, String startTime,
			String endTime, Map<?, ?> context) {
		String scheduleStart, scheduleEnd;
		boolean flag = false;
		Map<String, Object> retMap = new HashMap<String, Object>();
		if (((String) context.get(select)).equals("disabled")) {
			scheduleStart = "";
			scheduleEnd = "";
			flag = true;
		} else {
			scheduleStart = (String) context.get(startTime);
			scheduleEnd = (String) context.get(endTime);

			if (scheduleStart != null && scheduleEnd != null) {
				String timeStart0[] = scheduleStart.split(":");
				String timeEnd0[] = scheduleEnd.split(":");
				if (timeStart0.length == 2 && timeEnd0.length == 2) {
					try {
						int hourStart = Integer.parseInt(timeStart0[0]);
						int minuteStart = Integer.parseInt(timeStart0[1]);

						int hourEnd = Integer.parseInt(timeEnd0[0]);
						int minuteEnd = Integer.parseInt(timeEnd0[1]);
						if (hourStart <= 24 && hourStart >= 0
								&& minuteStart <= 60 && minuteStart >= 0
								&& hourEnd <= 24 && hourEnd >= 0
								&& minuteEnd <= 60 && minuteEnd >= 0
								&& hourStart <= hourEnd)
							flag = true;
					} catch (Exception e) {
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

	public static Map<?, ?> ScheduleOperate(Map<?, ?> context) {
		Map<String, Object> map = new HashMap<String, Object>();
		String time, scheduleStart0, scheduleEnd0, scheduleStart1, scheduleEnd1, scheduleStart2, scheduleEnd2, scheduleStart3, scheduleEnd3, scheduleStart4, cheduleEnd4, scheduleStart5, scheduleEnd5, scheduleStart6, scheduleEnd6;
		boolean flag = true;
		Map map0 = getTimeString("select0", "scheduleStart0", "scheduleEnd0",
				context);
		scheduleStart0 = (String) map0.get("scheduleStart");
		scheduleEnd0 = (String) map0.get("scheduleEnd");
		flag = flag && (Boolean) map0.get("flag");

		Map map1 = getTimeString("select1", "scheduleStart1", "scheduleEnd1",
				context);
		scheduleStart1 = (String) map1.get("scheduleStart");
		scheduleEnd1 = (String) map1.get("scheduleEnd");
		flag = flag && (Boolean) map1.get("flag");

		Map map2 = getTimeString("select2", "scheduleStart2", "scheduleEnd2",
				context);
		scheduleStart2 = (String) map2.get("scheduleStart");
		scheduleEnd2 = (String) map2.get("scheduleEnd");
		flag = flag && (Boolean) map2.get("flag");

		Map map3 = getTimeString("select3", "scheduleStart3", "scheduleEnd3",
				context);
		scheduleStart3 = (String) map3.get("scheduleStart");
		scheduleEnd3 = (String) map3.get("scheduleEnd");
		flag = flag && (Boolean) map3.get("flag");

		Map map4 = getTimeString("select4", "scheduleStart4", "scheduleEnd4",
				context);
		scheduleStart4 = (String) map4.get("scheduleStart");
		cheduleEnd4 = (String) map4.get("scheduleEnd");
		flag = flag && (Boolean) map4.get("flag");

		Map map5 = getTimeString("select5", "scheduleStart5", "scheduleEnd5",
				context);
		scheduleStart5 = (String) map5.get("scheduleStart");
		scheduleEnd5 = (String) map5.get("scheduleEnd");
		flag = flag && (Boolean) map5.get("flag");

		Map map6 = getTimeString("select6", "scheduleStart6", "scheduleEnd6",
				context);
		scheduleStart6 = (String) map6.get("scheduleStart");
		scheduleEnd6 = (String) map6.get("scheduleEnd");
		flag = flag && (Boolean) map6.get("flag");

		time = "Sunday" + scheduleStart0 + "-" + scheduleEnd0 + " Monday"
				+ scheduleStart1 + "-" + scheduleEnd1 + " Tuesday"
				+ scheduleStart2 + "-" + scheduleEnd2 + " Wednesday"
				+ scheduleStart3 + "-" + scheduleEnd3 + " Thursday"
				+ scheduleStart4 + "-" + cheduleEnd4 + " Friday"
				+ scheduleStart5 + "-" + scheduleEnd5 + " Saturday"
				+ scheduleStart6 + "-" + scheduleEnd6;

		map.put("sodier", flag);
		map.put("timeString", time);

		return map;
	}

	public static String sendMail(String mailServer, String recipient,
			String subject, String content) {
		try {
			Socket s = new Socket(mailServer, 25);
			BufferedReader in = new BufferedReader(new InputStreamReader(s
					.getInputStream(), "8859_1"));
			BufferedWriter out = new BufferedWriter(new OutputStreamWriter(s
					.getOutputStream(), "8859_1"));

			Assistant.send(in, out, "HELO theWorld");
			// warning : some mail server validate the sender address
			// in the MAIL FROm command, put your real address here
			Assistant
					.send(in, out, "MAIL FROM: <Elvis.Presley@jailhouse.rock>");
			Assistant.send(in, out, "RCPT TO: " + recipient);
			Assistant.send(in, out, "DATA");
			Assistant.send(out, "Subject: " + "subject" + subject);
			Assistant
					.send(out,
							"From: deeplylovemycountry@sina.com <deeplylovemycountry@sina.com>");
			Assistant.send(out, "\n");
			// message body
			Assistant.send(out, "This is the content!" + content);
			Assistant.send(out, "\n.\n");
			Assistant.send(in, out, "QUIT");
			s.close();
		} catch (Exception e) {
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
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void send(BufferedWriter out, String s) {
		try {
			out.write(s + "\n");
			out.flush();
			System.out.println(s);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static String getPagerDial(String s) {
		long tem = 1;
		try {
			StringBuffer stringbuffer = new StringBuffer();

			//此处如果没有选择发送方式，默认custom
			String s1 = (Config.getConfig("_pagerType", tem) == null) ? "custom"
					: Config.getConfig("_pagerType", tem);
			String s2 = "\"";
			if (com.dragonflow.SiteView.Platform.isUnix()) {
				s2 = "";
			}
			stringbuffer.append(s2);
			if (s1.equalsIgnoreCase("alpha")) {
				stringbuffer.append((Config.getConfig("_pagerSpeed", tem) == null) ? "custom"
						: Config.getConfig("_pagerSpeed", tem));
				stringbuffer.append((Config.getConfig("_pagerPort", tem) == null) ? "custom"
						: Config.getConfig("_pagerPort", tem));				
				stringbuffer.append("ATDT");
				stringbuffer
						.append((Config.getConfig("_pagerAlphaPhone", tem) == null) ? ""
								: Config.getConfig("_pagerAlphaPhone", tem));

			} else if (s1.equalsIgnoreCase("direct")) {
				stringbuffer.append((Config.getConfig("_pagerSpeed", tem) == null) ? "custom"
						: Config.getConfig("_pagerSpeed", tem));
				stringbuffer.append((Config.getConfig("_pagerPort", tem) == null) ? "custom"
						: Config.getConfig("_pagerPort", tem));				
				stringbuffer.append("ATDT");
				stringbuffer
						.append((Config.getConfig("_pagerDirectPhone", tem) == null) ? ""
								: Config.getConfig("_pagerDirectPhone", tem));
				stringbuffer.append(",,,");
				stringbuffer.append(s);
				stringbuffer.append('#');

			} else if (s1.equalsIgnoreCase("option")) {
				stringbuffer.append((Config.getConfig("_pagerSpeed", tem) == null) ? "custom"
						: Config.getConfig("_pagerSpeed", tem));
				stringbuffer.append((Config.getConfig("_pagerPort", tem) == null) ? "custom"
						: Config.getConfig("_pagerPort", tem));				
				stringbuffer.append("ATDT");
				stringbuffer
						.append((Config.getConfig("_pagerOptionPhone", tem) == null) ? ""
								: Config.getConfig("_pagerOptionPhone", tem));
				stringbuffer.append(",,");
				stringbuffer
						.append((Config.getConfig("_pagerOption", tem) == null) ? ""
								: Config.getConfig("_pagerOption", tem));
				stringbuffer.append(",,,");
				stringbuffer.append(s);
				stringbuffer.append('#');

			} else if (s1.equalsIgnoreCase("custom")) {
				stringbuffer.append((Config.getConfig("_pagerSpeed", tem) == null) ? "custom"
						: Config.getConfig("_pagerSpeed", tem));
				stringbuffer.append((Config.getConfig("_pagerPort", tem) == null) ? "custom"
						: Config.getConfig("_pagerPort", tem));				
				String s3 = (Config.getConfig("_pagerCustom", tem) == null) ? ""
						: Config.getConfig("_pagerCustom", tem);
				String s4 = "$message";
				int j = s3.indexOf(s4);
				if (j >= 0) {
					stringbuffer.append(s3.substring(0, j));
					stringbuffer.append(s);
					stringbuffer.append(s3.substring(j + s4.length()));
				} else {
					stringbuffer.append(s3);
				}

			}
			int i = Integer
					.parseInt((Config.getConfig("_pagerTimeout", tem) == null) ? ""
							: Config.getConfig("_pagerTimeout", tem));
			if (s1.equalsIgnoreCase("alpha")) {
				stringbuffer.append(s2 + " " + i);
				stringbuffer
						.append(" "
								+ s2
								+ ((Config.getConfig("_pagerAlphaPIN", tem) == null) ? ""
										: Config.getConfig("_pagerAlphaPIN", tem))
								+ s2);
				stringbuffer.append(" " + s2 + s + s2);
			} else {
				stringbuffer.append(";" + s2 + " " + i);
			}
			return stringbuffer.toString();

		} catch (Exception e) {
			return e.getMessage();
		}
	}
	
	public static String getPagerDial1(Map map) {	
		try {		  
		        StringBuffer stringbuffer = new StringBuffer();
		        String s1 =(String)map.get("_pagerType");  
		        String s2 = "\"";
		        if (com.dragonflow.SiteView.Platform.isUnix()) {
		            s2 = "";
		        }
		        stringbuffer.append(s2);
		        if (s1.equalsIgnoreCase("alpha")) {
		            stringbuffer.append("ATDT");
		            stringbuffer.append((String)map.get("_pagerAlphaPhone"));
		        } else if (s1.equalsIgnoreCase("direct")) {
		            stringbuffer.append("ATDT");
		            stringbuffer.append((String)map.get("_pagerDirectPhone"));
		            stringbuffer.append(",,,");
		            stringbuffer.append("message");
		            stringbuffer.append('#');
		        } else if (s1.equalsIgnoreCase("option")) {
		            stringbuffer.append("ATDT");
		            stringbuffer.append((String)map.get("_pagerOptionPhone"));
		            stringbuffer.append(",,");
		            stringbuffer.append((String)map.get("_pagerOption"));
		            stringbuffer.append(",,,");
		            stringbuffer.append("message");
		            stringbuffer.append('#');
		        } else if (s1.equalsIgnoreCase("custom")) {
		            String s3 = (String)map.get("_pagerCustom");
		            String s4 = "$message";
		            int j = s3.indexOf(s4);
		            if (j >= 0) {
		                stringbuffer.append(s3.substring(0, j));
		                stringbuffer.append("message");
		                stringbuffer.append(s3.substring(j + s4.length()));
		            } else {
		                stringbuffer.append(s3);
		            }
		        }
		        String i =((String)map.get("_pagerTimeout")==null)?"":(String)map.get("_pagerTimeout");
		        if (s1.equalsIgnoreCase("alpha")) {
		            stringbuffer.append(s2 + " " + i);
		            stringbuffer.append(" " + s2 + (String)map.get("_pagerAlphaPIN") + s2);
		            stringbuffer.append(" " + s2 + "message" + s2);
		        } else {
		            stringbuffer.append(";" + s2 + " " + i);
		        }
		        return stringbuffer.toString();		   
		
		}catch (Exception e) {
			return e.getMessage();
		}
	}

}
