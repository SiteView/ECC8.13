package com.siteview.ecc.init;

import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

import org.ofbiz.base.util.Debug;

import com.dragonflow.Properties.ScalarProperty;
import com.siteview.ecc.service.Preference;

public class StartupServlet extends HttpServlet {
	private static final long serialVersionUID = 3966818109992769920L;
	public static final String module = StartupServlet.class.getName();
	
    public StartupServlet() {
    }

    public void destroy() {
    }

    /*
     * ofbiz 启动时自动启动的服务
     * @see javax.servlet.GenericServlet#init(javax.servlet.ServletConfig)
     */
    public void init(ServletConfig config) throws ServletException {

        // Get context
        //ServletContext context = config.getServletContext();

        // Load configuation file
        //String file = config.getInitParameter("config-file");
        //String configFilename = context.getRealPath(file);
        
        //Debug.logInfo("Config file : " + configFilename + " be loaded!", module);
        
        try {
 			Debug.logInfo("pre-Started Monitor service !", module);
            new SiteViewThread().start();

            Debug.logInfo("Successfully Started Monitor service", module);
        	
		} catch (Exception e) {
			e.printStackTrace();
		}

     }
}
