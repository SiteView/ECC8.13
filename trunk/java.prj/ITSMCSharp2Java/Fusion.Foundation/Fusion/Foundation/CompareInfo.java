package Fusion.Foundation;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 15:22:44
 */
public class CompareInfo extends ILogicalThreadAffinative {

	private ArrayList m_alGroupCompareInfos;
	private ArrayList m_alPropertyCompareInfos;
	private boolean m_bDeepCompareDone;
	private CompareCategory m_Category;
	private CompareInfo m_ParentCompareInfo;
	private ArrayList<String> m_scMessages;
	private String m_strDisplayName;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public CompareInfo(){

	}

	/**
	 * 
	 * @param parentCompareInfo
	 * @param compCat
	 */
	public CompareInfo(CompareInfo parentCompareInfo, CompareCategory compCat){

	}

	/**
	 * 
	 * @param ci
	 */
	public void AddCompareInfo(CompareInfo ci){

	}

	/**
	 * 
	 * @param strMessage
	 */
	public void AddMessage(String strMessage){

	}

	/**
	 * 
	 * @param scMessages
	 */
	public void AddMessages(ArrayList<String> scMessages){

	}

	public CompareCategory Category(){
		return null;
	}

	public void ClearAll(){

	}

	public boolean DeepCompareDone(){
		return false;
	}

	public String DisplayName(){
		return "";
	}

	private String GetMessages(){
		return "";
	}

	public List GroupCompareInfos(){
		return null;
	}

	public int MessageCount(){
		return 0;
	}

	public ArrayList<String> Messages(){
		return null;
	}

	public CompareInfo ParentCompareInfo(){
		return null;
	}

	public List PropertyCompareInfos(){
		return null;
	}

	public int PropertyCount(){
		return 0;
	}

	/**
	 * 
	 * @param ci
	 */
	public void RemoveCompareInfo(CompareInfo ci){

	}

	/**
	 * 
	 * @param strMessage
	 */
	public void RemoveMessage(String strMessage){

	}

	public CompareInfo TopMostParentCompareInfo(){
		return null;
	}

	public String ToString(){
		return "";
	}

}