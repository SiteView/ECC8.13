package com.siteview.server.xmtp;

import org.jivesoftware.smack.Chat;
import org.jivesoftware.smack.ConnectionConfiguration;
import org.jivesoftware.smack.XMPPConnection;
import org.jivesoftware.smack.packet.Message;

public class ServerStart  
{
  public static void main(String[] arg)
  {
	  ConnectionConfiguration config = new ConnectionConfiguration("siteview-xxxjwb");
      config.setCompressionEnabled(true);
      config.setSASLAuthenticationEnabled(true);
      config.setDebuggerEnabled(false);
	  XMPPConnection connection = new XMPPConnection(config);
	  
	  while(true)
	  {
		  try
		  {
			  connection.connect();
			  connection.login("admin", "admin123");
			  if(!connection.isConnected())
			  {
				  try{Thread.sleep(5000);}catch(Exception err){}
				  continue;
			  }
			  break;
			  
		  }catch(Exception e)
		  {
			  System.out.println("Chat server login Error:"+e.getMessage());
			  try{Thread.sleep(5000);}catch(Exception err){}
			  continue;  
		  }
	  }
		  
	 connection.addPacketListener(new SiteViewPacketListener(connection), new SiteViewPacketFilter());
	 System.out.println("Chat Server is started!!");
	 while(true)
	 {
		 System.out.print(".");
		 try{Thread.sleep(10000);}catch(Exception e){}
	 }
		  
  }
}
