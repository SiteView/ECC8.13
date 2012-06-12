/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.StandardPreference;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import com.dragonflow.Properties.BooleanProperty;
import com.dragonflow.Properties.NumericProperty;
import com.dragonflow.Properties.StringProperty;
import com.siteview.ecc.util.PreferencesIniValueReader;

public class DDCDefaultPreferences extends com.dragonflow.SiteView.Preferences {

    public static com.dragonflow.Properties.StringProperty pConfigJdbcURL;

    public static com.dragonflow.Properties.StringProperty pConfigJdbcDriver;

    public static com.dragonflow.Properties.StringProperty pConfigJdbcUser;

    public static com.dragonflow.Properties.StringProperty pConfigJdbcPassword;

    public static com.dragonflow.Properties.StringProperty pInitializeDatabaseFromFiles;

    public static com.dragonflow.Properties.StringProperty pFileCheckFrequency;

    public DDCDefaultPreferences() {
    }

    public String verify(com.dragonflow.Properties.StringProperty stringproperty, String s, com.dragonflow.HTTP.HTTPRequest httprequest, java.util.HashMap hashmap, java.util.HashMap hashmap1) {
        if (stringproperty == pFileCheckFrequency) {
            try {
                new Integer(s);
            } catch (NumberFormatException numberformatexception) {
                hashmap1.put(stringproperty, "The entry is not a valid number.");
            }
        }
        return s;
    }

    static {
        pConfigJdbcURL = new StringProperty("_configJdbcURL");
        //pConfigJdbcURL.setDisplayText("Database Connection URL", "Enter the URL to the database connection (for example, if the ODBC connection is called, the URL would be jdbc:odbc:).");
        pConfigJdbcURL.setDisplayText(
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_configJdbcURL",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_configJdbcURL",PreferencesIniValueReader.DESCRIPTION));
        pConfigJdbcURL.setParameterOptions(true, 1, false);
        pConfigJdbcDriver = new StringProperty("_configJdbcDriver");
        //pConfigJdbcDriver.setDisplayText("Database Driver", "Enter the driver used to connect to the database.");
        pConfigJdbcDriver.setDisplayText(
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_configJdbcDriver",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_configJdbcDriver",PreferencesIniValueReader.DESCRIPTION));
        pConfigJdbcDriver.setParameterOptions(true, 2, false);
        pConfigJdbcUser = new StringProperty("_configJdbcUser");
        //pConfigJdbcUser.setDisplayText("Database Username", "Enter the username used to connect to the database.");
        pConfigJdbcUser.setDisplayText(
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_configJdbcUser",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_configJdbcUser",PreferencesIniValueReader.DESCRIPTION));
        pConfigJdbcUser.setParameterOptions(true, 3, false);
        pConfigJdbcPassword = new StringProperty("_configJdbcPassword");
        //pConfigJdbcPassword.setDisplayText("Database Password", "Enter the password used to connect to the database.");
        pConfigJdbcPassword.setDisplayText(
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_configJdbcPassword",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_configJdbcPassword",PreferencesIniValueReader.DESCRIPTION));
        pConfigJdbcPassword.setParameterOptions(true, 4, false);
        pConfigJdbcPassword.isPassword = true;
        pInitializeDatabaseFromFiles = new BooleanProperty("_initializeDatabaseFromFiles", "");
        //pInitializeDatabaseFromFiles
        //        .setDisplayText(
        //                "Initialize database from current configuration files",
        //                "If you would like the database initialized with the current contents of the configuration files, check this box. Warning: checking this box will delete the current configurations stored in the database for this server - we advise using this feature only when initially setting up database configuration.");
        pInitializeDatabaseFromFiles.setDisplayText(
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_initializeDatabaseFromFiles",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_initializeDatabaseFromFiles",PreferencesIniValueReader.DESCRIPTION));
        pInitializeDatabaseFromFiles.setParameterOptions(true, 5, true);
        //pFileCheckFrequency = new NumericProperty("_fileCheckFrequency", "120", "seconds");
        pFileCheckFrequency = new NumericProperty("_fileCheckFrequency", "120", PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_fileCheckFrequency",PreferencesIniValueReader.UNIT));
        //pFileCheckFrequency.setDisplayText("Configuration Update Frequency", "Enter the configuration update frequency in seconds.");
        pFileCheckFrequency.setDisplayText(
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_fileCheckFrequency",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(DDCDefaultPreferences.class.getName(), "_fileCheckFrequency",PreferencesIniValueReader.DESCRIPTION));
        pFileCheckFrequency.setParameterOptions(true, 6, true);
        com.dragonflow.Properties.StringProperty astringproperty[] = { pConfigJdbcURL, pConfigJdbcDriver, pConfigJdbcUser, pConfigJdbcPassword, pInitializeDatabaseFromFiles, pFileCheckFrequency };
        com.dragonflow.StandardPreference.DDCDefaultPreferences.addProperties("com.dragonflow.StandardPreference.DDCDefaultPreferences", astringproperty);
    }
}
