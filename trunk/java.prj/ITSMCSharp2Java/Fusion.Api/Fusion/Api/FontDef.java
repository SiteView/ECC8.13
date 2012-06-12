package Fusion.Api;

import java.awt.Font;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:32
 */
public class FontDef extends FusionAggregate {

	public FontDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public FontDef(Object fusionObject){

	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param strFontKey
	 */
	public static Font FontFromKey(String strFontKey){
		return null;
	}

	/**
	 * 
	 * @param serial
	 * @param source
	 * @param strFontKey
	 */
	public static void FontInfoFromSerial(DefSerializer serial, FontSource source, String strFontKey){

	}

	/**
	 * 
	 * @param serial
	 * @param source
	 * @param strFontKey
	 */
	public static void FontInfoToSerial(DefSerializer serial, FontSource source, String strFontKey){

	}

	/**
	 * 
	 * @param font
	 */
	public static String KeyFromFont(Font font){
		return "";
	}

	private Fusion.Presentation.FontDef WhoAmI(){
		return null;
	}

}