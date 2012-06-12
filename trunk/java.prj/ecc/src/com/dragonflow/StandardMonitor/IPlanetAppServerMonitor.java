/*
 * 
 * Created on 2005-3-7 1:20:16
 *
 * IPlanetAppServerMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>IPlanetAppServerMonitor</code>
 * 
 * @author 
 * @version 0.0
 *
 *
 */

import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Log.LogManager;
import com.dragonflow.Page.CGI;
import com.dragonflow.Properties.ScalarProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.*;
import com.dragonflow.SiteViewException.SiteViewException;
import com.dragonflow.Utils.Snmp.BrowsableMIB;
import com.dragonflow.Utils.TextUtils;

import java.util.Vector;
import jgl.Array;

public class IPlanetAppServerMonitor extends BrowsableSNMPBase
{

    private String IPlanetAppServerMIB;

    public IPlanetAppServerMonitor()
    {
        IPlanetAppServerMIB = "NO_IPLANET_APPSERVER_MIB_AVAILABLE";
    }

    public Array getConnectionProperties()
    {
        Array array = super.getConnectionProperties();
        return array;
    }

    protected String getMonitorType()
    {
        return "IPlanet Application Server";
    }

    public Vector getScalarValues(ScalarProperty scalarproperty, HTTPRequest httprequest, CGI cgi)
        throws SiteViewException
    {
        if(scalarproperty == pMIB)
        {
            Vector vector = new Vector();
            try
            {
                BrowsableMIB browsablemib = BrowsableMIB.getInstance();
                if(browsablemib.containsMIB(IPlanetAppServerMIB))
                {
                    vector.add(IPlanetAppServerMIB);
                    vector.add(IPlanetAppServerMIB);
                }
            }
            catch(Exception exception)
            {
                LogManager.log("Error", "IPlanet AppServer Monitor could not get BrowsableMIB instance: " + exception.getMessage());
            }
            if(vector.size() == 0)
            {
                vector.add("No MIBs Available");
                vector.add("No MIBs Available");
            }
            return vector;
        } else
        {
            return super.getScalarValues(scalarproperty, httprequest, cgi);
        }
    }

    static 
    {
        jgl.HashMap hashmap = MasterConfig.getMasterConfig();
        StringProperty astringproperty[] = new StringProperty[0];
        addProperties("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", astringproperty);
        addClassElement("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", Rule.stringToClassifier("countersInError > 0\terror"));
        addClassElement("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", Rule.stringToClassifier("always\tgood"));
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", "description", "Monitors IPlanet Application servers using snmp.");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", "help", "IPASMon.htm");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", "title", "IPlanet Application Server");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", "class", "IPlanetAppServerMonitor");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", "target", "_server");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", "topazName", "IPlanet Application");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", "classType", "application");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", "topazType", "Web Application Server");
        if(TextUtils.getValue(hashmap, "_allowIPlanet").length() > 0)
        {
            setClassProperty("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", "loadable", "true");
        } else
        {
            setClassProperty("com.dragonflow.StandardMonitor.IPlanetAppServerMonitor", "loadable", "false");
        }
    }

	@Override
	public boolean getSvdbRecordState(String paramName, String operate,
			String paramValue) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public String getSvdbkeyValueStr() {
		// TODO Auto-generated method stub
		return null;
	}
}
