package com.siteview.server.xmtp;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
/*
 * 
   {(8,{m}),}
*/
public class Map2String 
{
	
	
	public static String toString(Map map)
	{
		
		StringBuilder sb=new StringBuilder();
		Iterator iterator=map.keySet().iterator();
		sb.append("{");
		
		for(int i=0;iterator.hasNext();)
		{
			Object key=iterator.next();
			
			if(i>0)
				sb.append(",");
			
			Object value=map.get(key);
			sb.append("(").append(Util.escapeNode(key.toString())).append(",");
			
			if(value instanceof String)
				sb.append(Util.escapeNode(value.toString())).append(")");
			else if(value instanceof Map)
				sb.append(toString((Map)value)).append(")");
			else
			{
				System.out.println("error data type in map:"+value);
				return "{}";
			}
		}
		sb.append("}");
		return sb.toString();
	}
	/*     5                    20                                 
	 *                    19                          42             
	 * {(2,{(k1,v1)(k2,v2)})(1,{(key2,4444)(key1,5555)})(0,key1=2222)}
	 */
	public static HashMap<String, String> toMap(String data)
	{
		HashMap<String, String> retMap=new HashMap<String, String>();
		//切头去尾
		data=data.substring(1,data.length()-1);
		//
		int pos=0;
		while(true)
		{
		 int start=data.indexOf("(",pos);
		 if(start==-1)
			 break;
		 
		 int counter=0;
		 for(int i=start+1;i<data.length();i++)
		 {
			 if(data.charAt(i)=='(')
				 counter++;
			 else if(data.charAt(i)==')')
			 {
				 if(counter==0)
				 {
					 pos=i; //找到合法的结束表志,跳出
					 break;
				 }
				 counter--;
			 }
		 }

		 doKeyValue(retMap,data.substring(start, pos+1));
			 
		}
		return retMap;
	}
	public static void doKeyValue(Map map,String keyvalue)
	{
		int pos=keyvalue.indexOf(",");
		String key=keyvalue.substring(1,pos);
		String value=keyvalue.substring(pos+1,keyvalue.length()-1);
		if(value.startsWith("{"))
			map.put(Util.unescapeNode(key), toMap(value));
		else
			map.put(Util.unescapeNode(key), Util.unescapeNode(value));
	}

}
