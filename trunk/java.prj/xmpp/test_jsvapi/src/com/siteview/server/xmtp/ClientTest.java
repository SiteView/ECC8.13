package com.siteview.server.xmtp;

import org.jivesoftware.smack.ConnectionConfiguration;
import org.jivesoftware.smack.PacketListener;
import org.jivesoftware.smack.XMPPConnection;
import org.jivesoftware.smack.filter.PacketFilter;
import org.jivesoftware.smack.packet.Message;
import org.jivesoftware.smack.packet.Packet;

public class ClientTest implements PacketFilter,PacketListener{

	/**
	 * @param args
	 */
	
	long old;
	public static void main(String[] args) 
	{
		new ClientTest().test();
		while(true)
		{
			System.out.print("*");
			try{Thread.sleep(1000);}catch(Exception e){}
		}
	}
	
	public void test()
	{
		  ConnectionConfiguration config = new ConnectionConfiguration("siteview-xxxjwb");
		  
	      config.setCompressionEnabled(false);
	      config.setSASLAuthenticationEnabled(true);
	      config.setDebuggerEnabled(false);
		  XMPPConnection connection = new XMPPConnection(config);
	
		
		  
		try{
			
				  connection.connect();
				  connection.login("aaa@siteview-xxxjwb", "aaa");
				  
				  for(int i=0;i<10;i++)
				  {
					  if(!connection.isConnected())
					  {
						  System.out.println("连接失败");
						  return;
					  }
					  
					  if(connection.isAuthenticated())
						  break;
					  
					  Thread.currentThread().sleep(100);
				  }
				  
				  
				  connection.addPacketListener(this,this);
				  Message msg = new Message();
				  msg.setTo("admin@siteview-xxxjwb");
				  msg.setFrom("aaa@siteview-xxxjwb");
				  msg.setBody("00000:{(id,alertlogs)(count,10000)(dowhat,QueryRecordsByCount)}");
				  
				  
				  old=System.currentTimeMillis();
				  connection.sendPacket(msg);
		}catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	@Override
	public boolean accept(Packet packet) {
			return true;
	}
	@Override
	public void processPacket(Packet packet) {
		if(packet instanceof Message)
		{	
		long ll=System.currentTimeMillis()-old;
		
		String s=((Message)packet).getBody();
		s=Util.unescapeNode(s);
		System.out.println(new Encoding().decode(s));
		System.out.println("系统查询花费时间"+ll+"ms");
		}
	}
}
