package Fusion.Foundation;
import Fusion.PlaceHolder;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 15:22:46
 */
public class ObjectCompareInfo extends CompareInfo {

	private Fusion.PlaceHolder m_placeHolder;
	private String m_strClassName;
	private String m_strDefinitionID;
	private String m_strDefinitionName;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ObjectCompareInfo(){

	}

	/**
	 * 
	 * @param parentCompareInfo
	 * @param compCat
	 */
	public ObjectCompareInfo(CompareInfo parentCompareInfo, CompareCategory compCat){

	}

	/**
	 * 
	 * @param parentCompareInfo
	 * @param compCat
	 * @param placeHolder
	 */
	public ObjectCompareInfo(CompareInfo parentCompareInfo, CompareCategory compCat, Fusion.PlaceHolder placeHolder){

	}

	public String ClassName(){
		return "";
	}

	public String DefinitionID(){
		return "";
	}

	public String DefinitionName(){
		return "";
	}

	public String Perspective(){
		return "";
	}

	public Fusion.PlaceHolder PlaceHolder(){
		return null;
	}

	public String ToString(){
		return "";
	}

}