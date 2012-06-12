package com.siteview.ecc.api;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;

import jgl.Array;
import jgl.HashMap;

import org.ofbiz.base.util.Debug;
import org.ofbiz.entity.GenericValue;

import com.dragonflow.Log.LogManager;
import com.dragonflow.Properties.FrameFile;
import com.dragonflow.Properties.HashMapOrdered;
import com.dragonflow.SiteView.DetectConfigurationChange;
import com.dragonflow.SiteView.Platform;
import com.dragonflow.SiteView.SiteViewGroup;
import com.dragonflow.Utils.FileUtils;
import com.dragonflow.Utils.TextUtils;

public class APIEntity {
	public static final String module = APIEntity.class.getName();
	
	public static Array readFromFile(String filename, boolean flag) throws Exception {
		synchronized (FileUtils.getFileLock(filename)) {
			StringBuffer stringbuffer = null;
			Array array = null;
			try {
				stringbuffer = read(filename);
			} catch (IOException e) {
				if (stringbuffer == null || stringbuffer.length() == 0) {
					if (FrameFile.readMasterConfig && filename.indexOf("master.config") >= 0) {
						LogManager.log("error", "File(" + filename + ") is missing");
					}
					File file = new File(filename);
					String s2 = file.getParent();
					File file1 = null;
					int j = 100;
					if (FrameFile.readMasterConfig) {
						SiteViewGroup siteviewgroup = SiteViewGroup
								.currentSiteView();
						j = siteviewgroup.getSettingAsLong("_backups2Keep", 1);
						String s3 = filename + ".bak" + (j <= 1 ? "" : ".1");
						file1 = new File(s3);
					} else {
						String s4 = filename + ".bak";
						file1 = new File(s4);
						if (!file1.exists()) {
							file1 = new File(s4 + ".1");
						}
					}
					try {
						if (FrameFile.popBackup(file, file1, s2, j) && FrameFile.readMasterConfig) {
							LogManager.log("error", "File(" + filename
									+ ") replacing with backup");
						} else if (FrameFile.readMasterConfig
								&& filename.indexOf("master.config") >= 0) {
							LogManager
									.log(
											"error",
											"File("
													+ filename
													+ ") CANNOT replace backup. No backup found.");
						}
					} catch (IOException e1) {
						if (FrameFile.readMasterConfig && filename.indexOf("master.config") >= 0) {
							LogManager.log("error", "File(" + filename
									+ ") Exception(" + e1.getMessage()
									+ ") replacing backup");
						}
					}
					stringbuffer = read(filename);
				}
			}
			array = FrameFile.mangleIt(filename, stringbuffer.toString(), flag);
			if (filename.indexOf("master.config") >= 0) {
				FrameFile.readMasterConfig = true;
				for (int i = 0; i < array.size(); i++) {
					String s1 = (String) array.at(i);
					if (s1.trim().startsWith("#")) {
						array.remove(i);
						i--;
					}
				}

			}

			return FrameFile.readFrames(array.elements());
		}
	}
	public static void writeToFile(String filename, Array array, String s1,
			boolean flag, boolean flag1) throws Exception {
		
/*		synchronized (FileUtils.getFileLock(filename)) {
			SiteViewGroup siteviewgroup = SiteViewGroup.currentSiteView();
			int i = siteviewgroup.getSettingAsLong("_backups2Keep", 1);
			File file = new File(filename);
			if (!file.exists() && I18N.isI18N(filename)) {
				String s2 = I18N.toDefaultEncoding(filename);
				File file1 = new File(s2);
				if (file1.exists()) {
					filename = s2;
					file = file1;
				}
			}
			String s3 = filename + ".bak" + (i <= 1 ? "" : ".1");
			boolean flag2 = siteviewgroup.getSetting("_backupDyns").length() == 0
					|| !filename.endsWith("dyn");
			File file2 = FrameFile.pushBackup(file, filename, s3, i, flag2);
			if (filename.indexOf("master.config") != -1) {
				TempFileManager.addTempByAgeFile(file, siteviewgroup
						.getSettingAsLong("_tempByAgeTTL", 168));
			}
			if (printFile(file, array, s1, flag, flag1)) {
				FrameFile.popBackup(file, file2, filename, i);
			}
		}
*/		
		printFile(new File(filename), array, s1, flag, flag1);
		DetectConfigurationChange.getInstance().resetFileTimeStamp(filename);

	}	
	public static StringBuffer read(String filename) throws Exception
	{
		//ConfigEntity.test();
		
		Array retvalues = getByFileName(filename);
		if (retvalues==null) return FileUtils.readUTF8File(filename);
		StringBuffer stringbuffer = new StringBuffer();
		
		Enumeration<?> enumeration = retvalues.elements();
		for (boolean flag2 = true; enumeration.hasMoreElements(); flag2 = false) {
			HashMap hashmap = (HashMap) enumeration.nextElement();
			if (!flag2) {
				stringbuffer.append("#" + Platform.FILE_NEWLINE);
//			} else if (TextUtils.getValue(hashmap, "_fileEncoding").length() == 0) {
	//			hashmap.put("_fileEncoding", "UTF-8");
			}
			printFrame(stringbuffer, hashmap);
		}
		return stringbuffer;
	}
	
	/*
	private static void printFrame(StringBuffer stringbuffer, HashMap hashmap
			) {
		Enumeration<?> enumeration = hashmap.keys();
		while (enumeration.hasMoreElements()) {
			Object key = enumeration.nextElement();
			Object element = hashmap.get(key);
			if (element instanceof HashMap) {
				//printFrame(stringbuffer,(HashMap) element);
			} else {
				String val = ("" + element).trim();
				if (val.length() != 0 ) {
					stringbuffer.append(key + "=" + val
							+ Platform.FILE_NEWLINE);
				}
			}
		}

		enumeration = hashmap.elements();
		while (enumeration.hasMoreElements()) {
			Object element = enumeration.nextElement();
			if (element instanceof HashMap) {
				printFrame(stringbuffer,(HashMap) element);
			}
		}
	}	
*/
	
	private static void printFrame(StringBuffer stringbuffer, HashMap hashmap) {
		Enumeration<?> enumeration = hashmap.keys();
		while (enumeration.hasMoreElements()) {
			Object key = enumeration.nextElement();
			Object element = hashmap.get(key);
			if (element instanceof HashMap) {
				printFrame(stringbuffer,(HashMap) element);
			} if (element instanceof String) {
				printFrame((String)key,stringbuffer,(String) element);
			} if (element instanceof Array) {
				printFrame((String)key,stringbuffer,(Array) element);
			}
		}
	}	
	private static void printFrame(String key,StringBuffer stringbuffer, String str) {
		stringbuffer.append(key);
		stringbuffer.append("=");
		stringbuffer.append(str);
		stringbuffer.append(Platform.FILE_NEWLINE);
	}
	private static void printFrame(String key,StringBuffer stringbuffer, Array array) {
		Enumeration<?> enumeration = array.elements();
		while (enumeration.hasMoreElements()) {
			Object element = enumeration.nextElement();
			if (element instanceof HashMap) {
				printFrame(stringbuffer,(HashMap) element);
			} if (element instanceof String) {
				printFrame((String)key,stringbuffer,(String) element);
			} if (element instanceof Array) {
				printFrame((String)key,stringbuffer,(Array) element);
			}
		}
		
	}
	public static Array toArrayWithMap(String str)
	{
		String[] strs = TextUtils.split(str,"#");
		Array retArray = new Array();
		for (String val : strs)
		{
			if ("".equals(val) || val == null) continue;
			HashMap map = toHashMap(val);
			retArray.add(map);
		}
		return retArray;
	}
	
	public static HashMap toHashMap(String str)
	{
		String[] strs = TextUtils.split(str,"\n");
		HashMapOrdered retHashMap = new HashMapOrdered(true);
		for (String val : strs)
		{
			if ("".equals(val) || val == null) continue;
			int index = val.indexOf('=');
			if (!(index>0)) continue;
			String key = val.substring(0,index);
			String value = val.substring(index + 1);
			retHashMap.add(key,value);
		}
		return retHashMap;
	}
	
	public static boolean printFile(File file, Array array, String s,
			boolean flag, boolean flag1) throws Exception {
		PrintWriter printwriter = null;
		FileOutputStream fileoutputstream = null;
		boolean flag2 = false;
		try {
			StringBuffer stringbuffer = new StringBuffer();
			FrameFile.printFrames(stringbuffer, array, s, flag, flag1);
			if (FrameFile.forceMangleOnWrite) {
				stringbuffer = FrameFile.mangle(stringbuffer);
			}

			//Array data = FrameFile.readFrames(FrameFile.mangleIt(file.getName(), stringbuffer.toString(), false).elements());
			Array data = toArrayWithMap(stringbuffer.toString());
			boolean bRet = saveByFileName(file.getName(),data,s,flag,flag1);
			
			if (bRet) return false;
			fileoutputstream = new FileOutputStream(file);
			printwriter = FileUtils.MakeUTF8OutputWriter(fileoutputstream);
			
			
			printwriter.print(stringbuffer);
			flag2 = printwriter.checkError();
		} catch (Exception e) {
			LogManager.log("Error", " Exception during write of "
					+ file.getAbsolutePath() + " " + e.getMessage());
			e.printStackTrace();
			throw e;
		} finally {
			if (printwriter != null) {
				printwriter.close();
			}
			try {
				if (fileoutputstream != null) {
					fileoutputstream.close();
				}
			} catch (IOException e) {
				LogManager.log("Error", "Exception in FrameFile.printFile()"
						+ e.getMessage());
				e.printStackTrace();
			}
		}
		return flag2;
	}	
	public static Array getByFileName(String filename)  throws Exception
	{
		if (filename == null) return null;
		try {
			Debug.log("read from = " + filename,module);
			File file = new File(filename);
			String newfilename = file.getName();
			if (newfilename.endsWith(".dyn"))
			{
				String id = newfilename.replace(".dyn", "");
				return GroupEntity.get(id,GroupEntity.FILENAME_EXT_DYN);
			} else if (newfilename.endsWith(".mg")){
				String id = newfilename.replace(".mg", "");
				return GroupEntity.get(id,GroupEntity.FILENAME_EXT_MG);
			} else if (newfilename.equals("users.config")) {
				return UserEntity.get();
			} else if (newfilename.equals("master.config")) {
				return MasterConfigEntity.get();
			} else {
				
			}
		} catch (Exception e) {
			Debug.log(e,module);
		}
		return null;
	}	
	public static boolean saveByFileName(String filename,Array data,String s,
			boolean flag, boolean flag1) throws Exception
	{
		if (filename == null) return false;
		try {
			Debug.log("write to = " + filename,module);
			File file = new File(filename);
			String newfilename = file.getName();
			if (newfilename.endsWith(".dyn"))
			{
				String id = newfilename.replace(".dyn", "");
				GroupEntity.saveDYN(id,data,s,flag,flag1);
			} else if (newfilename.endsWith(".mg")){
				String id = newfilename.replace(".mg", "");
				GroupEntity.saveMG(id,data,s,flag,flag1);
			} else if (newfilename.equals("users.config")) {
				UserEntity.put(data);
			} else if (newfilename.equals("master.config")) {
				MasterConfigEntity.put(data);
			} else {
				return false;
			}
			return true;
		} catch (Exception e) {
			Debug.log(e,module);
		}
		return false;
	}	

	public static void deleteByFileName(String filename)
	{
		deleteByFileName(new File(filename));
	}
	public static void deleteByFileName(File file)
	{
		if (file == null) return;
		try {
			Debug.log("delete from = " + file.getAbsolutePath(),module);
			String newfilename = file.getName();
			if (newfilename.endsWith(".dyn"))
			{
				String id = newfilename.replace(".dyn", "");
				GroupEntity.delete(id, GroupEntity.FILENAME_EXT_DYN);
			} else if (newfilename.endsWith(".mg")){
				String id = newfilename.replace(".mg", "");
				GroupEntity.delete(id, GroupEntity.FILENAME_EXT_MG);
			} else if (newfilename.equals("users.config")) {
				UserEntity.deleteAll();
			} else if (newfilename.equals("master.config")) {
				MasterConfigEntity.deleteAll();
			} else {
			}
		} catch (Exception e) {
			Debug.log(e,module);
		}
	}	
		
	public static boolean exist(String filename)
	{
		try {
			if (filename == null) return false;
			if (filename.indexOf("users.config")>=0) {
				return true;
			} else if (filename.indexOf("master.config")>=0) {
				return true;
			} else if (filename.endsWith(".dyn") || filename.endsWith(".mg")) {
				return getByFileName(filename)!=null;
			}
		} catch (Exception e) {
			Debug.log(e,module);
		}
		return false;
	}
	
	public static String[] getMgFileNames()
	{
		try {
			List<GenericValue> list = GroupEntity.getAllGroup();
			List<String> retlist = new ArrayList<String>();
			for (GenericValue val : list)
			{
				if (GroupEntity.FILENAME_EXT_MG.equals(val.getString("stype"))){
					retlist.add(val.getString("id") + ".mg");
				}
			}
			return retlist.toArray(new String[0]);
		} catch (Exception e) {
			Debug.log(e,module);
		}
		return new String[0];
		
	}
}
