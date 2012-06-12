/*
 * 
 * Created on 2005-3-7 1:20:16
 *
 * IPlanetWSMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>IPlanetWSMonitor</code>
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

public class IPlanetWSMonitor extends BrowsableSNMPBase
{

    private String IPlanetWSMIB;

    public IPlanetWSMonitor()
    {
        IPlanetWSMIB = "NO_IPLANET_WS_MIB_AVAILABLE";
    }

    public Array getConnectionProperties()
    {
        Array array = super.getConnectionProperties();
        return array;
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
                if(browsablemib.containsMIB(IPlanetWSMIB))
                {
                    vector.add(IPlanetWSMIB);
                    vector.add(IPlanetWSMIB);
                }
            }
            catch(Exception exception)
            {
                LogManager.log("Error", "IPlanet WS Monitor could not get BrowsableMIB instance: " + exception.getMessage());
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

    protected String getMonitorType()
    {
        return "IPlanet WebServer";
    }

    static 
    {
        jgl.HashMap hashmap = MasterConfig.getMasterConfig();
        StringProperty astringproperty[] = new StringProperty[0];
        addProperties("com.dragonflow.StandardMonitor.IPlanetWSMonitor", astringproperty);
        addClassElement("com.dragonflow.StandardMonitor.IPlanetWSMonitor", Rule.stringToClassifier("countersInError > 0\terror"));
        addClassElement("com.dragonflow.StandardMonitor.IPlanetWSMonitor", Rule.stringToClassifier("always\tgood"));
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetWSMonitor", "description", "Monitors IPlanet Web servers using snmp.");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetWSMonitor", "help", "IPWSMon.htm");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetWSMonitor", "title", "IPlanet Web Server");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetWSMonitor", "class", "IPlanetWSMonitor");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetWSMonitor", "target", "_server");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetWSMonitor", "topazName", "IPlanet Web Server");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetWSMonitor", "classType", "application");
        setClassProperty("com.dragonflow.StandardMonitor.IPlanetWSMonitor", "topazType", "Web Server");
        if(TextUtils.getValue(hashmap, "_allowIPlanet").length() > 0)
        {
            setClassProperty("com.dragonflow.StandardMonitor.IPlanetWSMonitor", "loadable", "true");
        } else
        {
            setClassProperty("com.dragonflow.StandardMonitor.IPlanetWSMonitor", "loadable", "false");
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
