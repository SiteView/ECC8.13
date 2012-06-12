/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Api;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.io.File;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Vector;

import jgl.Array;
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Resource.SiteViewErrorCodes;
import com.dragonflow.SiteView.DetectConfigurationChange;
import com.dragonflow.SiteView.Preferences;
import com.dragonflow.SiteViewException.SiteViewException;
import com.dragonflow.SiteViewException.SiteViewOperationalException;
import com.dragonflow.SiteViewException.SiteViewParameterException;
import com.dragonflow.StandardPreference.RemoteNTInstancePreferences;
import com.dragonflow.StandardPreference.RemoteUnixInstancePreferences;

// Referenced classes of package com.dragonflow.Api:
// APISiteView, SSInstanceProperty, SSPropertyDetails, SSPreferenceInstance,
// SSStringReturnValue

public class APIPreference extends APISiteView {

	public APIPreference() {
	}

	public SSInstanceProperty create(String s,SSInstanceProperty assinstanceproperty[])
			throws com.dragonflow.SiteViewException.SiteViewException {
		SSInstanceProperty ssinstanceproperty = null;
		try {
			String s1 = "com.dragonflow.StandardPreference." + s;
			java.util.HashMap hashmap = new HashMap();
			for (int i = 0; i < assinstanceproperty.length; i++) {
				hashmap.put(assinstanceproperty[i].getName(),assinstanceproperty[i].getValue());
			}

			Class class1 = Class.forName(s1);
			com.dragonflow.SiteView.Preferences preferences = (com.dragonflow.SiteView.Preferences) class1.newInstance();
			jgl.Array array = getPropertiesForClass(preferences, s1,"Preferences",APISiteView.FILTER_CONFIGURATION_ADD_ALL);
			hashmap = preferences.validateProperties(hashmap, array,new HashMap());
			String as[] = preferences.addPreferences(hashmap);
			ssinstanceproperty = new SSInstanceProperty(as[0], as[1]);
			DetectConfigurationChange detectconfigurationchange = DetectConfigurationChange.getInstance();
			detectconfigurationchange.setConfigChangeFlag();
		} catch (SiteViewException siteviewexception) {
			siteviewexception.fillInStackTrace();
			throw siteviewexception;
		} catch (Exception exception) {
			throw new SiteViewOperationalException(
					com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_EXCEPTION,
					new String[] { "APIPreference", "create" }, 0L, exception
							.getMessage());
		}
		return ssinstanceproperty;
	}

	public SSInstanceProperty update(String className, String s1, String s2,
			SSInstanceProperty assinstanceproperty[])
			throws com.dragonflow.SiteViewException.SiteViewException {
		SSInstanceProperty ssinstanceproperty = null;
		try {
			String absClassName = "com.dragonflow.StandardPreference."
					+ className;
			HashMap hashmap = new HashMap();
			for (int i = 0; i < assinstanceproperty.length; i++) {
				hashmap.put(assinstanceproperty[i].getName(),
						assinstanceproperty[i].getValue());
			}

			Class class1 = Class.forName(absClassName);
			Preferences preferences = (Preferences) class1.newInstance();
			jgl.Array array = getPropertiesForClass(preferences, absClassName,
					"Preferences", APISiteView.FILTER_CONFIGURATION_EDIT_ALL);
			hashmap = preferences.validateProperties(hashmap, array,
					new HashMap());
			String as[] = preferences.updatePreferences(hashmap, s1, s2);
			ssinstanceproperty = new SSInstanceProperty(as[0], as[1]);
			com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange
					.getInstance();
			detectconfigurationchange.setConfigChangeFlag();
		} catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
			siteviewexception.fillInStackTrace();
			throw siteviewexception;
		} catch (Exception exception) {
			throw new SiteViewOperationalException(
					com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_EXCEPTION,
					new String[] { "APIPreference", "update" }, 0L, exception
							.getMessage());
		}
		return ssinstanceproperty;
	}

	public void delete(String s, String s1, String s2)
			throws com.dragonflow.SiteViewException.SiteViewException {
		try {
			String s3 = "com.dragonflow.StandardPreference." + s;
			Class class1 = Class.forName(s3);
			Preferences preferences = (Preferences) class1.newInstance();
			preferences.deletePreferences(s1, s2);
			DetectConfigurationChange detectconfigurationchange = DetectConfigurationChange
					.getInstance();
			detectconfigurationchange.setConfigChangeFlag();
		} catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
			siteviewexception.fillInStackTrace();
			throw siteviewexception;
		} catch (Exception exception) {
			throw new SiteViewOperationalException(
					SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_EXCEPTION,
					new String[] { "APIPreference", "delete" }, 0L, exception
							.getMessage());
		}
	}

	public java.util.Vector test(String s, String s1, String s2, String s3,
			boolean flag)
			throws com.dragonflow.SiteViewException.SiteViewException {
		java.util.Vector vector = new Vector();
		try {
			String s4 = "com.dragonflow.StandardPreference." + s;
			Class class1 = Class.forName(s4);
			com.dragonflow.SiteView.Preferences preferences = (com.dragonflow.SiteView.Preferences) class1
					.newInstance();
			SSInstanceProperty assinstanceproperty[] = getInstanceProperties(s,
					preferences.getSettingName(), s1, s2,
					APISiteView.FILTER_RUNTIME_ALL);
			if (assinstanceproperty != null && assinstanceproperty.length > 0) {
				for (int i = 0; i < assinstanceproperty.length; i++) {
					String s5 = assinstanceproperty[i].getName();
					String s6 = (String) assinstanceproperty[i].getValue();
					if (s5 != null && s6 != null) {
						preferences.setProperty(s5, s6);
					}
				}

				vector = preferences.test(s3);
				assinstanceproperty = getInstanceProperties(s, preferences
						.getSettingName(), s1, s2,
						APISiteView.FILTER_RUNTIME_ALL);
				if (assinstanceproperty != null
						&& assinstanceproperty.length > 0) {
					if (flag) {
						vector = new Vector();
					}
					for (int j = 0; j < assinstanceproperty.length; j++) {
						if (flag) {
							if (assinstanceproperty[j].getName().equals(
									"_status")) {
								vector.addElement(assinstanceproperty[j]
										.getValue());
							}
						} else {
							vector
									.addElement(assinstanceproperty[j]
											.getValue());
						}
					}

				}
			} else {
				vector
						.addElement("attribute " + s1 + " = " + s2
								+ " not found");
			}
		} catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
			siteviewexception.fillInStackTrace();
			throw siteviewexception;
		} catch (Exception exception) {
			throw new SiteViewOperationalException(
					com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_EXCEPTION,
					new String[] { "APIPreference", "test" }, 0L, exception
							.getMessage());
		}
		return vector;
	}

	public SSPropertyDetails[] getClassPropertiesDetails(String className, int i)
			throws com.dragonflow.SiteViewException.SiteViewException {
		Object obj = null;
		SSPropertyDetails asspropertydetails[] = null;
		try {
			String s1 = "com.dragonflow.StandardPreference." + className;
			Class class1 = Class.forName(s1);
			com.dragonflow.SiteView.SiteViewObject siteviewobject = (com.dragonflow.SiteView.SiteViewObject) class1
					.newInstance();
			jgl.Array array = getPropertiesForClass(siteviewobject, s1,
					"Preferences", i);
			java.util.Vector vector = new Vector();
			if (i == APISiteView.FILTER_CONFIGURATION_ADD_ALL
					|| i == APISiteView.FILTER_CONFIGURATION_ADD_BASIC
					|| i == APISiteView.FILTER_CONFIGURATION_ADD_ADVANCED
					|| i == APISiteView.FILTER_CONFIGURATION_EDIT_ALL
					|| i == APISiteView.FILTER_CONFIGURATION_EDIT_BASIC
					|| i == APISiteView.FILTER_CONFIGURATION_EDIT_ADVANCED) {
				java.util.Enumeration enumeration = array.elements();
				jgl.Array array1 = new Array();
				while (enumeration.hasMoreElements()) {
					com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty) enumeration
							.nextElement();
					if (stringproperty.isThreshold()) {
						array1.add(stringproperty);
					}
				}
				for (int k = 0; k < array1.size(); k++) {
					array.remove(array1.at(k));
				}

			}
			asspropertydetails = new SSPropertyDetails[array.size()
					+ vector.size()];
			for (int j = 0; j < array.size(); j++) {
				asspropertydetails[j] = getClassProperty(
						(com.dragonflow.Properties.StringProperty) array.at(j),
						(com.dragonflow.SiteView.Preferences) siteviewobject);
			}

		} catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
			siteviewexception.fillInStackTrace();
			throw siteviewexception;
		} catch (Exception exception) {
			throw new SiteViewOperationalException(
					com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_EXCEPTION,
					new String[] { "APIPreference", "getClassPropertiesDetails" },
					0L, exception.getMessage());
		}
		return asspropertydetails;
	}

	public SSPropertyDetails getClassPropertyDetails(String s, String s1, int i)
			throws com.dragonflow.SiteViewException.SiteViewException {
		SSPropertyDetails sspropertydetails = null;
		try {
			String s2 = "com.dragonflow.StandardPreference." + s1;
			Class class1 = Class.forName(s2);
			com.dragonflow.SiteView.SiteViewObject siteviewobject = (com.dragonflow.SiteView.SiteViewObject) class1
					.newInstance();
			com.dragonflow.Properties.StringProperty stringproperty = siteviewobject
					.getPropertyObject(s);
			sspropertydetails = getClassProperty(stringproperty,
					(com.dragonflow.SiteView.Preferences) siteviewobject);
		} catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
			siteviewexception.fillInStackTrace();
			throw siteviewexception;
		} catch (Exception exception) {
			throw new SiteViewOperationalException(
					com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_EXCEPTION,
					new String[] { "APIPreference", "getClassPropertyDetails" },
					0L, exception.getMessage());
		}
		return sspropertydetails;
	}

	/**
	 * CAUTION: Decompiled by hand.
	 * 
	 * @param s
	 * @param s1
	 * @param s2
	 * @param s3
	 * @param i
	 * @return
	 * @throws com.dragonflow.SiteViewException.SiteViewException
	 */
	public SSPreferenceInstance[] getInstances(String className, String s1,
			String s2, String s3, int i)
			throws com.dragonflow.SiteViewException.SiteViewException {
		try {
			java.util.Vector vector = new Vector();
			SSPreferenceInstance asspreferenceinstance[];
			String s4 = "com.dragonflow.StandardPreference." + className;
			Class class1 = Class.forName(s4);
			com.dragonflow.SiteView.Preferences preferences = (com.dragonflow.SiteView.Preferences) class1
					.newInstance();
			s1 = preferences.getSettingName();
			java.util.Vector vector1 = preferences.getPreferenceProperties(
					className, s1, "", "", i);
			java.util.HashSet hashset = new HashSet();
			for (int j = 0; j < vector1.size(); j++) {
				java.util.HashMap hashmap = (java.util.HashMap) vector1
						.elementAt(j);
				String s5 = (String) hashmap
						.get(com.dragonflow.SiteView.Preferences.pID.getName());
				if (hashset.contains(s5)) {
					com.dragonflow.Log.LogManager.log("error",
							"Duplicate preference ID for " + className + ": "
									+ s5);
					continue;
				}
				hashset.add(s5);
				SSInstanceProperty assinstanceproperty[] = new SSInstanceProperty[hashmap
						.size()];
				java.util.Set set = hashmap.keySet();
				java.util.Iterator iterator = set.iterator();
				for (int l = 0; iterator.hasNext(); l++) {
					String s6 = (String) iterator.next();
					assinstanceproperty[l] = new SSInstanceProperty(s6, hashmap
							.get(s6));
				}

				vector.add(new SSPreferenceInstance(s1, assinstanceproperty));
			}

			asspreferenceinstance = new SSPreferenceInstance[vector.size()];
			for (int k = 0; k < vector.size(); k++) {
				asspreferenceinstance[k] = (SSPreferenceInstance) vector
						.elementAt(k);
			}

			return asspreferenceinstance;
		} catch (SiteViewException e) {
			e.fillInStackTrace();
			throw e;
		} catch (Exception e) {
			throw new SiteViewOperationalException(
					com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_EXCEPTION,
					new String[] { "APIPreference", "getInstances" }, 0L, e
							.getMessage());
		}
	}

	public SSInstanceProperty[] getInstanceProperties(String className, String s1,
			String s2, String s3, int i)
			throws com.dragonflow.SiteViewException.SiteViewException {
		SSInstanceProperty assinstanceproperty[] = null;
		try {
			String s4 = "com.dragonflow.StandardPreference." + className;
			Object obj = null;
			Class class1 = Class.forName(s4);
			com.dragonflow.SiteView.Preferences preferences = (com.dragonflow.SiteView.Preferences) class1
					.newInstance();
			if (s1 != null && s1.length() == 0) {
				s1 = preferences.getSettingName();
			}
			java.util.Vector vector = preferences.getPreferenceProperties(className,
					s1, s2, s3, i);
			if (vector.size() > 0) {
				java.util.HashMap hashmap = (java.util.HashMap) vector
						.elementAt(0);
				assinstanceproperty = new SSInstanceProperty[hashmap.size()];
				java.util.Set set = hashmap.keySet();
				java.util.Iterator iterator = set.iterator();
				for (int j = 0; iterator.hasNext(); j++) {
					String s5 = (String) iterator.next();
					assinstanceproperty[j] = new SSInstanceProperty(s5, hashmap
							.get(s5));
				}

			} else {
				throw new SiteViewParameterException(
						com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_PREFERENCE_INSTANCE_NOTFOUND,
						new String[] { s2, s3 });
			}
		} catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
			siteviewexception.fillInStackTrace();
			throw siteviewexception;
		} catch (Exception exception) {
			throw new SiteViewOperationalException(
					com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_EXCEPTION,
					new String[] { "APIPreference", "getInstanceProperties" },
					0L, exception.getMessage());
		}
		return assinstanceproperty;
	}

	public SSStringReturnValue[] getPreferenceTypes()
			throws com.dragonflow.SiteViewException.SiteViewException {
		SSStringReturnValue assstringreturnvalue[] = null;
		try {
			java.util.Vector vector = new Vector();
			java.io.File file = new File(com.dragonflow.SiteView.Platform
					.getRoot()
					+ "/classes/com/dragonflow/StandardPreference");
			String as[] = file.list();
			for (int i = 0; i < as.length; i++) {
				int k = as[i].lastIndexOf(".class");
				if (k != -1) {
					vector.addElement(as[i].substring(0, k));
				}
			}

			assstringreturnvalue = new SSStringReturnValue[vector.size()];
			for (int j = 0; j < vector.size(); j++) {
				assstringreturnvalue[j] = new SSStringReturnValue(
						(String) vector.elementAt(j));
			}

		} catch (Exception exception) {
			throw new SiteViewOperationalException(
					com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_EXCEPTION,
					new String[] { "APIPreference", "getPreferenceTypes" }, 0L,
					exception.getMessage());
		}
		return assstringreturnvalue;
	}

	private SSPropertyDetails getClassProperty(
			com.dragonflow.Properties.StringProperty stringproperty,
			com.dragonflow.SiteView.Preferences preferences)
			throws com.dragonflow.SiteViewException.SiteViewException {
		String as[] = null;
		String as1[] = null;
		String s = "";
		String s1 = "TEXT";
		String s2 = "";
		boolean flag = false;
		try {
			com.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
			httprequest.setUser(account);
			if (stringproperty.isPassword) {
				s1 = "PASSWORD";
			} else if (stringproperty instanceof com.dragonflow.Properties.ServerProperty) {
				s1 = "SERVER";
				java.util.Vector<String> vector = null;
				if (httprequest.getValue("noNTRemote").length() == 0) {
					vector = getLocalServers();
					vector = addServers(vector, new RemoteNTInstancePreferences().getSettingName(), true);
				} else {
					vector = new Vector<String>();
					vector.addElement("this server");
					vector.addElement("this server");
				}
				if (httprequest.getValue("noremote").length() == 0) {
					vector = addServers(vector, new RemoteUnixInstancePreferences().getSettingName(), false);
				}
				String s3 = httprequest.getValue("server");
				if (s3.length() == 0) {
					s3 = "this server";
				} else {
					s3 = com.dragonflow.SiteView.Machine.getFullMachineID(s3,
							httprequest);
				}
				as = new String[vector.size() / 2];
				as1 = new String[vector.size() / 2];
				int i = 0;
				for (int j = 0; i < vector.size(); j++) {
					String s4 = (String) vector.elementAt(i);
					as[j + 1] = s4;
					as1[j] = s4;
					i += 2;
				}

				s = "LIST";
			} else if (stringproperty instanceof com.dragonflow.Properties.ScheduleProperty) {
				s1 = "SCHEDULE";
			} else if (stringproperty instanceof com.dragonflow.Properties.ScalarProperty) {
				s1 = "SCALAR";
				com.dragonflow.Properties.ScalarProperty scalarproperty = (com.dragonflow.Properties.ScalarProperty) stringproperty;
				Class<?> class1 = Class
						.forName("com.dragonflow.Page.monitorPage");
				com.dragonflow.Page.CGI cgi = (com.dragonflow.Page.CGI) class1
						.newInstance();
				cgi.initialize(httprequest, null);
				Vector<?> vector1 = preferences.getScalarValues(scalarproperty,
						httprequest, cgi);
				as = new String[vector1.size() / 2];
				as1 = new String[vector1.size() / 2];
				int k = 0;
				for (int l = 0; k < vector1.size() / 2; l += 2) {
					as1[k] = (String) vector1.elementAt(l);
					as[k] = (String) vector1.elementAt(l + 1);
					k++;
				}

				s = "LIST";
			} else if (stringproperty instanceof com.dragonflow.Properties.RateProperty) {
				s1 = "RATE";
			} else if (stringproperty instanceof com.dragonflow.Properties.PercentProperty) {
				s1 = "PERCENT";
				s2 = ((com.dragonflow.Properties.PercentProperty) stringproperty)
						.getUnits();
			} else if (stringproperty instanceof com.dragonflow.Properties.FrequencyProperty) {
				s1 = "FREQUENCY";
				s2 = "seconds";
			} else if (stringproperty instanceof com.dragonflow.Properties.FileProperty) {
				s1 = "FILE";
			} else if (stringproperty instanceof com.dragonflow.Properties.BrowsableProperty) {
				s1 = "BROWSABLE";
			} else if (stringproperty instanceof com.dragonflow.Properties.BooleanProperty) {
				s1 = "BOOLEAN";
			} else if (stringproperty instanceof com.dragonflow.Properties.NumericProperty) {
				s1 = "NUMERIC";
				s2 = ((com.dragonflow.Properties.NumericProperty) stringproperty)
						.getUnits();
			}
		} catch (com.dragonflow.SiteViewException.SiteViewException siteviewexception) {
			siteviewexception.fillInStackTrace();
			throw siteviewexception;
		} catch (Exception exception) {
			throw new SiteViewOperationalException(
					com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_EXCEPTION,
					new String[] { "APIPreference", "getClassProperty" }, 0L,
					exception.getMessage());
		}
		return new SSPropertyDetails(stringproperty.getName(), s1,
				stringproperty.getDescription(), stringproperty.getLabel(),
				stringproperty.isEditable, stringproperty.isMultivalued,
				stringproperty.getDefault(), as, as1, s,
				!stringproperty.isAdvanced, flag, stringproperty.getOrder(),
				s2, stringproperty.isAdvanced, stringproperty.isPassword,
				preferences.getProperty(stringproperty.getName()));
	}

	public Preferences getPreferencesById(String id, String className)
			throws Exception {
		String absClassName = "com.dragonflow.StandardPreference." + className;
		Class<?> class1 = Class.forName(absClassName);
		Preferences preferences = (Preferences) class1.newInstance();
		SSInstanceProperty assinstanceproperty[] = getInstanceProperties(
				className, preferences.getSettingName(), "_id", id,
				APISiteView.FILTER_ALL);
		if (assinstanceproperty != null) {
			for (SSInstanceProperty val : assinstanceproperty) {
				String name = val.getName();
				if (name == null)
					continue;
				String value = (String) val.getValue();
				if (value == null)
					continue;
				preferences.setProperty(name, value);
			}
		}
		return preferences;

	}

	public static void main(String args[]) {
		try {
			APIPreference apipreference = new APIPreference();
			apipreference.delete("RemoteNTPreferences", "_id", "10");
		} catch (Exception exception) {
		}
	}
}
