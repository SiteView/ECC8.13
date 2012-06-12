package Fusion;

import java.util.ArrayList;
import java.util.Hashtable;

import Fusion.control.ILogicalThreadAffinative;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:30
 */
public class MessageInfo extends ILogicalThreadAffinative {

	private String CodeSeparator = ":";
	private Hashtable m_dictParameters = new Hashtable();
	private ArrayList m_itemList = new ArrayList();
	private String m_strBusObId = "";
	private String m_strBusObName = "";
	private String m_strGrandparentId = "";
	private String m_strGrandparentName = "";
	private String m_strMessage = "";
	private String m_strParentId = "";
	private String m_strParentName = "";
	private String m_strResourceId = null;
	private String m_strSource = "";

	public MessageInfo(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strItem
	 */
	public void AddItem(String strItem){

	}

	/**
	 * 
	 * @param strName
	 * @param value
	 * @param parameterDataCategory
	 */
	public void AddMessageParameter(String strName, Object value, ParameterDataCategory parameterDataCategory){

	}

	public String BusObId(){
		return "";
	}

	public String BusObName(){
		return "";
	}

	public MessageCategory Category(){
		return null;
	}

	public void ClearItems(){

	}

	/**
	 * 
	 * @param strItem
	 */
	public void DeleteItem(String strItem){

	}

	/**
	 * 
	 * @param strName
	 */
	public void DeleteMessageParameter(String strName){

	}

	/**
	 * 
	 * @param msgService
	 * @param strName
	 * @param value
	 */
	protected String FormatParameterValue(IMessageService msgService, String strName, Object value){
		return "";
	}

	public String getCodeSeparator(){
		return CodeSeparator;
	}

	/**
	 * 
	 * @param strName
	 */
	protected Object GetMessageParameter(String strName){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	protected ParameterDataCategory GetParameterDataCategory(String strName){
		return null;
	}

	/**
	 * 
	 * @param msgService
	 * @param strName
	 */
	public String GetParameterValue(IMessageService msgService, String strName){
		return "";
	}

	public String GrandparentId(){
		return "";
	}

	public String GrandparentName(){
		return "";
	}

	public ArrayList ItemList(){
		return null;
	}

	public String Message(){
		return "";
	}

	public String ParentId(){
		return "";
	}

	public String ParentName(){
		return "";
	}

	public String ResourceId(){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCodeSeparator(String newVal){
		CodeSeparator = newVal;
	}

	public String Source(){
		return "";
	}

}