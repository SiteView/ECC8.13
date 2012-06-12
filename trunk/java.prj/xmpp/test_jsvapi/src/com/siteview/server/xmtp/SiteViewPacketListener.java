package com.siteview.server.xmtp;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;


import org.jivesoftware.smack.PacketListener;
import org.jivesoftware.smack.XMPPConnection;
import org.jivesoftware.smack.packet.Message;
import org.jivesoftware.smack.packet.Packet;

import com.focus.util.Base64;
import com.focus.util.ZipUtil;
import com.siteview.jsvapi.Jsvapi;

public class SiteViewPacketListener implements PacketListener {

	XMPPConnection connection;
	Jsvapi svapi = new Jsvapi();

	public SiteViewPacketListener(XMPPConnection connection) {
		this.connection = connection;
		svapi.test1();
		svapi.test2();
	}

	@Override
	public void processPacket(Packet packet) {

		System.out.print(packet.getFrom());
		// 292929:{(1,2)(2,3)}
		if (packet instanceof Message) {
			String request = ((Message) packet).getBody();
			Message msg = new Message();
			msg.setTo(packet.getFrom());
			msg.setFrom(packet.getTo());

			int pos = request.indexOf(":");
			if (pos == -1)
			{
				System.out.println("error request without id from "+packet.getFrom());
				return;
			}

			String id = request.substring(0, pos);
			String mapData = request.substring(pos + 1);

			//HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
			Vector<HashMap<String, String>> fmap = new Vector<HashMap<String, String>>();
			HashMap<String, String> ndata = null;
			
			try {
				ndata = Map2String.toMap(mapData);
			} catch (Exception e) 
			{
				System.out.println("error request from "+packet.getFrom()+":" + mapData);
				return;
			}
			
			StringBuilder estr = new StringBuilder();
			
			
			System.out.println("beign query!");
			long l0=System.currentTimeMillis();
			boolean ret = true;
			
			ret = svapi.GetForestData(fmap, ndata, estr);
			ret = GetUnivData2(fmap, ndata, estr);

			//提交的复杂一些，等上两个完了再搞
			//ret = SubmitUnivData2(fmap, ndata, estr);
			
			System.out.println("query OK!"+(System.currentTimeMillis()-l0)+"ms");
			long l1=System.currentTimeMillis();
			StringBuilder sb=new StringBuilder(id).append(":");
			for(int i=0;i<fmap.size();i++)
				sb.append("[").append(Map2String.toString(fmap.get(i))).append("]");
			
			System.out.println("my encode cost:"+(System.currentTimeMillis()-l1));
			
			
			String out=null;
			try{	
				
				/*long kk=System.currentTimeMillis();
				String s=ZipUtil.compress(id+ ":" + sb.toString());
				System.out.println("zip花费时间"+(System.currentTimeMillis()-kk));
				long mm=System.currentTimeMillis();
				out=Base64Util.getBASE64(s);
				System.out.println("Base64Util花费时间"+(System.currentTimeMillis()-mm));
				*/
				out=new Encoding().encode(sb.toString());
				
			}catch(Exception e)
			{
				e.printStackTrace();
				return;
			}
			
			System.out.println("编码时间!"+(System.currentTimeMillis()-l1)+"ms");	
			
			try{			
				//msg.setBody(id+ ":" + sb.toString());
				//System.out.println(id+ ":" + sb.toString()+"================");
				//msg.setBody(id+ ":" + sb.toString());
				//System.out.println(Base64Util.getBASE64(ZipUtil.compress(id+ ":" + sb.toString())));
				System.out.println(out); 
				msg.setBody(out);
			     
			}catch(Exception e)
			{
				e.printStackTrace();
				return;
			}
			long l=System.currentTimeMillis();
			System.out.println("beign send!");
			connection.sendPacket(msg);
			System.out.println("send OK!"+(System.currentTimeMillis()-l)+"ms");
		}
	}
	
	public boolean GetUnivData2(Vector<HashMap<String, String>> vmap,HashMap<String, String> inwhat,StringBuilder estr)
	{
		HashMap<String, HashMap<String, String>> fmap = new HashMap<String, HashMap<String, String>>();
		boolean ret = true;
		
		try
		{
			ret = svapi.GetUnivData(fmap, inwhat, estr);
			HashMap<String, String> ndata= new HashMap<String, String>();
			
			Integer index= new Integer(0);  
			for (String key : fmap.keySet())
			{
				vmap.add(fmap.get(key));
				ndata.put(index.toString(),key);
				++index;
			}
			vmap.add(0,ndata);
		} catch (Exception e)
		{
			estr.append(e + " ;  ");
			System.out.println(e);
			ret = false;
		}
		return ret;
	}
	
	public boolean SubmitUnivData2(Vector<HashMap<String, String>> invmap,HashMap<String, String> inwhat,StringBuilder estr)
	{
		boolean ret = true;
		
		try
		{
			boolean inok= false;
			HashMap<String, HashMap<String, String>> infmap = new HashMap<String, HashMap<String, String>>();
			if (invmap.size() >= 1)
			{
				HashMap<String, String> names = invmap.get(0);
				if ((names.size() + 1) == invmap.size())
				{
					inok= true;
					for (int i = 1; i < invmap.size(); ++i)
					{
						HashMap<String, String> ndata = invmap.get(i);
						Integer ikey= new Integer(i-1); 
						infmap.put(names.get(ikey.toString()).toString(), ndata);
					}
				}
			}
			
			ret = svapi.SubmitUnivData(infmap, inwhat, estr);
			HashMap<String, String> ndata= new HashMap<String, String>();
			if(!inok)
				estr=estr.append(" 要提交给服务器的数据 invmap 非法;  ");
			
			invmap.clear();
			Integer index= new Integer(0);  
			for (String key : infmap.keySet())
			{
				invmap.add(infmap.get(key));
				ndata.put(index.toString(),key);
				++index;
			}
			invmap.add(0,ndata);
		} catch (Exception e)
		{
			estr.append(e + " ;  ");
			e.printStackTrace();
			ret = false;
		}
		
		return ret;
	}

}
