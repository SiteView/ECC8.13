package com.siteview.ecc.data;

import java.io.FileOutputStream;
import java.io.FileWriter;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.ofbiz.entity.GenericDelegator;

public class MethodService {
	
	public static final String module = MethodService.class.getName();
    public static String testMethod(HttpServletRequest request, HttpServletResponse response) {
		try {
			
	        GenericDelegator delegator = (GenericDelegator) request.getAttribute("delegator");                
	        List<Map<String, String>> result = MethodDB.getAllMethod(delegator);
	        FileWriter fw = new FileWriter("monitor.txt");
	        
	        for (Map map : result){
	        	System.out.println(map);
	        	fw.write(map.toString());
	        }
	        fw.close();

			return "success";
		} catch (Exception e) {
			e.printStackTrace();
		}		
		return "error";
	}
    

}
