/*******************************************************************************
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *******************************************************************************/
package com.siteview.ecc.service;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletContext;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.transaction.Transaction;

import org.ofbiz.base.component.ComponentConfig;
import org.ofbiz.base.util.Debug;
import org.ofbiz.base.util.UtilHttp;
import org.ofbiz.base.util.UtilMisc;
import org.ofbiz.base.util.UtilProperties;
import org.ofbiz.base.util.UtilValidate;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericEntityException;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.model.ModelEntity;
import org.ofbiz.entity.transaction.GenericTransactionException;
import org.ofbiz.entity.transaction.TransactionUtil;
import org.ofbiz.security.Security;
import org.ofbiz.service.LocalDispatcher;
import org.ofbiz.service.ModelService;
import org.ofbiz.service.ServiceUtil;
import org.ofbiz.webapp.control.RequestHandler;

import com.siteview.svecc.service.Message;

/**
 * Common Workers
 */
public class LoginWorker {
    public final static String module = LoginWorker.class.getName();
	private static final String USER_INFORMATION = "_userInformation_";
    public static final String resourceWebapp = "WebappUiLabels";
    
	public static String login(HttpServletRequest request,
			HttpServletResponse response) {
		HttpSession session = request.getSession();
		LocalDispatcher dispatcher = (LocalDispatcher) request
				.getAttribute("dispatcher");
		Map result = null;

		try {

			if(checkLogin(request, response).equals("success")){
				return "success";
			}
			String username = request.getParameter("USERNAME");
			if (username == null || username.equals(""))
				throw new Exception(Message.getMessage(3000L));
			String password = request.getParameter("PASSWORD");
			if (password == null || password.equals(""))
				throw new Exception(Message.getMessage(3001L));

			result = dispatcher.runSync("checkUser", UtilMisc.toMap("username",
					username, "password", password));
			Boolean isOk = (Boolean) result.get("result");
			if (!isOk)
				throw new Exception(Message.getMessage(3008L));
			String userid = (String) result.get("id");
			result = dispatcher.runSync("getUserById", UtilMisc.toMap("id",
					userid));

			session.setAttribute(USER_INFORMATION, result.get("result"));
			System.out.println("**************************"+result.get("result"));
			return "success";

		} catch (Exception e) {
			String message = result == null ? null : (String) result
					.get("message");
			//Map<?, ?> retmap = ServiceUtil.returnFailure(message == null ? e
			//		.getMessage() : message);

          //  Map messageMap = UtilMisc.toMap("errorMessage", (String) result.get(ModelService.ERROR_MESSAGE));
          //  String errMsg = UtilProperties.getMessage(resourceWebapp, "loginevents.following_error_occurred_during_login", messageMap, UtilHttp.getLocale(request));	
//		  String errMsg = UtilProperties.getMessage(resourceWebapp, "loginevents.unable_to_login_this_application", UtilHttp.getLocale(request));
		  request.setAttribute("_ERROR_MESSAGE_", message == null ? e
					.getMessage() : message);
		
			
			return "error";
		}
	}

	 public static String checkLogin(HttpServletRequest request, HttpServletResponse response) {

		 HttpSession session=request.getSession();
			Object userInfo = session.getAttribute(USER_INFORMATION);		 
		 			if (userInfo != null) {

		 				return "success";
		 			}
	        return "error";
	    }

	    public static String logout(HttpServletRequest request, HttpServletResponse response) {
			 HttpSession session = request.getSession();
			 session.invalidate();
			 return "success";
	        
	    }
	  
}
