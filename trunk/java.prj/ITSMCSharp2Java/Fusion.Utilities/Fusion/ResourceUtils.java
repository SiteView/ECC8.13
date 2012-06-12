package Fusion;

import java.awt.Image;
import java.util.Hashtable;

import javax.swing.Icon;

import Fusion.control.Assembly;
import Fusion.control.Bitmap;
import Fusion.control.CultureInfo;
import Fusion.control.ImageList;
import Fusion.control.ResourceManager;
import Fusion.control.Size;
import Fusion.control.Stream;
import Fusion.control.Version;


/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:35
 */
public class ResourceUtils {

	private static Hashtable m_htAssemblyNameToResMgr = new Hashtable();

	public ResourceUtils(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param al
	 * @param strBitmapResourceName
	 * @param bLocalize
	 */
	public static Bitmap GetBitmap(Assembly al, String strBitmapResourceName, Boolean bLocalize){
		return null;
	}

	/**
	 * 
	 * @param al
	 * @param strIconResourceName
	 * @param bLocalize
	 */
	public static Icon GetIcon(Assembly al, String strIconResourceName, Boolean bLocalize){
		return null;
	}

	/**
	 * 
	 * @param al
	 * @param strIconResourceName
	 * @param nSize
	 * @param bLocalize
	 */
	public static Icon GetIcon(Assembly al, String strIconResourceName, int nSize, Boolean bLocalize){
		return null;
	}

	/**
	 * 
	 * @param al
	 * @param strImageResourceName
	 * @param bLocalize
	 */
	public static Image GetImage(Assembly al, String strImageResourceName, Boolean bLocalize){
		return null;
	}

	/**
	 * 
	 * @param al
	 * @param size
	 * @param astrIconResourceNames
	 */
	public static ImageList GetImageList(Assembly al, Size size, String[] astrIconResourceNames){
		return null;
	}

	/**
	 * 
	 * @param al
	 * @param strManifestResourceName
	 */
	private static Stream GetLocalizedResourceStream(Assembly al, String strManifestResourceName){
		return null;
	}

	/**
	 * 
	 * @param al
	 * @param aSizes
	 * @param astrIconResourceNames
	 * @param aImgLists
	 */
	public static void GetMultipleImageLists(Assembly al, Size[] aSizes, String[] astrIconResourceNames, ImageList[] aImgLists){

	}

	/**
	 * 
	 * @param strResourceName
	 * @param callingAssembly
	 */
	public static ResourceManager GetNamedResourceManager(String strResourceName, Assembly callingAssembly){
		return null;
	}

	/**
	 * 
	 * @param al
	 */
	private static CultureInfo GetNeutralResourcesLanguage(Assembly al){
		return null;
	}

	/**
	 * 
	 * @param al
	 * @param version
	 */
	private static Assembly GetParentSatelliteAssembly(Assembly al, Version version){
		return null;
	}

	/**
	 * 
	 * @param al
	 * @param strManifestResourceName
	 */
	public static Stream GetResourceFile(Assembly al, String strManifestResourceName){
		return null;
	}

	/**
	 * 
	 * @param al
	 * @param strManifestResourceName
	 */
	public static String GetResourceFileData(Assembly al, String strManifestResourceName){
		return "";
	}

	/**
	 * 
	 * @param strAssemblyName
	 * @param strManifestResourceName
	 */
	public static String GetResourceFileData(String strAssemblyName, String strManifestResourceName){
		return "";
	}

	/**
	 * 
	 * @param al
	 * @param strManifestResourceName
	 * @param bLocalize
	 */
	public static String GetResourceFileData(Assembly al, String strManifestResourceName, Boolean bLocalize){
		return "";
	}

	/**
	 * 
	 * @param strAssemblyName
	 * @param strManifestResourceName
	 * @param bLocalize
	 */
	public static String GetResourceFileData(String strAssemblyName, String strManifestResourceName, Boolean bLocalize){
		return "";
	}

	/**
	 * 
	 * @param al
	 * @param strManifestResourceName
	 */
	public static Stream GetResourceStream(Assembly al, String strManifestResourceName){
		return null;
	}

	/**
	 * 
	 * @param al
	 * @param strManifestResourceName
	 * @param bLocalize
	 */
	public static Stream GetResourceStream(Assembly al, String strManifestResourceName, Boolean bLocalize){
		return null;
	}

	/**
	 * 
	 * @param al
	 * @param version
	 */
	private static Assembly GetSatelliteAssembly(Assembly al, Version version){
		return null;
	}

	/**
	 * 
	 * @param al
	 */
	private static Version GetSatelliteContractVersion(Assembly al){
		return null;
	}

	/**
	 * 
	 * @param asm
	 * @param strResourceName
	 */
	public static String GetString(Assembly asm, String strResourceName){
		return "";
	}

	/**
	 * 
	 * @param al
	 * @param strManifestResourceName
	 */
	private static String GetValidFileName(Assembly al, String strManifestResourceName){
		return "";
	}

	/**
	 * 
	 * @param strAssemblyName
	 */
	public static Assembly LoadAssembly(String strAssemblyName){
		return null;
	}

}