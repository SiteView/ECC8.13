package Fusion;

import Fusion.control.Assembly;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:28
 */
public class LicenseUtils {

	private static final byte CONTENT_PUBLICKEYTOKEN[] = new byte[] { 20, 0x26, 0x30, (byte) 0xb3, 0x68, 0x63, 50, (byte) 0x81 };
	private static byte DEVELOPMENT_PUBLICKEYTOKEN[] = new byte[] { (byte) 0xde, (byte) 0x8e, 11, 0x37, 50, 110, (byte) 180, (byte) 0xd7 };
	private static byte FUSION_PUBLICKEYTOKEN[] = new byte[] { 0x5b, 0x72, (byte) 0xa6, 0x5e, 100, 0x57, 0x68, 0x34 };
	private static final byte ORION_PUBLICKEYTOKEN[] = new byte[] { (byte) 0x89, (byte) 0xad, (byte) 0xa6, (byte) 0xff, 0x4d, 0x1c, 0x1d, 0x18 };
	private static final byte REGULAR_PARTNER_PUBLICKEYTOKEN[] = new byte[] { 0x63, (byte) 0xac, (byte) 0xe0, (byte) 0xd8, (byte) 0x83, 50, (byte) 0xa7, 4 };
	private static final byte SUPER_PARTNER_PUBLICKEYTOKEN[] = new byte[] { 0x4b, 0x67, (byte) 0x87, 80, (byte) 0xd6, (byte) 0x9d, 0x55, 0x7f };

	public LicenseUtils(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param key
	 */
	private static String ConvertKeyToString(byte[] key){
		return "";
	}

	public byte[] getDEVELOPMENT_PUBLICKEYTOKEN(){
		return DEVELOPMENT_PUBLICKEYTOKEN;
	}

	public byte[] getFUSION_PUBLICKEYTOKEN(){
		return FUSION_PUBLICKEYTOKEN;
	}

	public static Boolean IsAssemblyValificationOff(){
		return null;
	}

	/**
	 * 
	 * @param key1
	 * @param key2
	 */
	private static Boolean IsPublicKeyTokenEqual(byte[] key1, byte[] key2){
		return null;
	}

	/**
	 * 
	 * @param assembly
	 */
	public static Boolean IsValidBrandingModule(Assembly assembly){
		return null;
	}

	/**
	 * 
	 * @param assembly
	 */
	public static Boolean IsValidExtensionModule(Assembly assembly){
		return null;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDEVELOPMENT_PUBLICKEYTOKEN(byte[] newVal){
		DEVELOPMENT_PUBLICKEYTOKEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFUSION_PUBLICKEYTOKEN(byte[] newVal){
		FUSION_PUBLICKEYTOKEN = newVal;
	}

}