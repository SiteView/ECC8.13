package Fusion;

import Fusion.control.XmlCDataSection;
import Fusion.control.XmlElement;
import Fusion.control.XmlNode;
import Fusion.control.XmlNodeList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:44
 */
public class XmlUtils {

	private String False = "false";
	private String True = "true";
	private String Value = "Value";



	public void finalize() throws Throwable {

	}

	protected XmlUtils(){

	}

	/**
	 * 
	 * @param xn
	 * @param strXmlElement
	 */
	public static Boolean ElementExists(XmlNode xn, String strXmlElement){
		return null;
	}

	/**
	 * 
	 * @param xn
	 * @param strXmlElement
	 * @param strAttribute
	 * @param strValue
	 */
	public static Boolean ElementWithAttributeExists(XmlNode xn, String strXmlElement, String strAttribute, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strUnencoded
	 */
	private static String EncodeForXPath(String strUnencoded){
		return "";
	}

	/**
	 * 
	 * @param element
	 * @param strTag
	 */
	public static Boolean GetAttributeAsFlag(XmlElement element, String strTag){
		return null;
	}

	/**
	 * 
	 * @param element
	 * @param strTag
	 * @param bDefault
	 */
	public static Boolean GetAttributeAsFlag(XmlElement element, String strTag, Boolean bDefault){
		return null;
	}

	/**
	 * 
	 * @param element
	 * @param strTag
	 */
	public static int GetAttributeAsInt32(XmlElement element, String strTag){
		return 0;
	}

	/**
	 * 
	 * @param element
	 * @param strTag
	 * @param iDefault
	 */
	public static int GetAttributeAsInt32(XmlElement element, String strTag, int iDefault){
		return 0;
	}

	/**
	 * 
	 * @param xn
	 * @param strChildElement
	 * @param strAttribute
	 */
	public static String GetAttributeOfChildElement(XmlNode xn, String strChildElement, String strAttribute){
		return "";
	}

	/**
	 * 
	 * @param bAttVal
	 * @param xn
	 * @param strChildElement
	 * @param strAttribute
	 */
	public static void GetAttributeOfChildElement(Boolean bAttVal, XmlNode xn, String strChildElement, String strAttribute){

	}

	/**
	 * 
	 * @param nAttVal
	 * @param xn
	 * @param strChildElement
	 * @param strAttribute
	 */
	public static void GetAttributeOfChildElement(int nAttVal, XmlNode xn, String strChildElement, String strAttribute){

	}

	/**
	 * 
	 * @param fAttVal
	 * @param xn
	 * @param strChildElement
	 * @param strAttribute
	 */
	public static void GetAttributeOfChildElement(float fAttVal, XmlNode xn, String strChildElement, String strAttribute){

	}

	/**
	 * 
	 * @param strAttVal
	 * @param xn
	 * @param strChildElement
	 * @param strAttribute
	 */
	public static void GetAttributeOfChildElement(String strAttVal, XmlNode xn, String strChildElement, String strAttribute){

	}

	/**
	 * 
	 * @param xn
	 * @param strAttribute
	 */
	public static String GetAttributeOfElement(XmlNode xn, String strAttribute){
		return "";
	}

	/**
	 * 
	 * @param bAttVal
	 * @param xn
	 * @param strAttribute
	 */
	public static void GetAttributeOfElement(Boolean bAttVal, XmlNode xn, String strAttribute){

	}

	/**
	 * 
	 * @param nAttVal
	 * @param xn
	 * @param strAttribute
	 */
	public static void GetAttributeOfElement(int nAttVal, XmlNode xn, String strAttribute){

	}

	/**
	 * 
	 * @param fAttVal
	 * @param xn
	 * @param strAttribute
	 */
	public static void GetAttributeOfElement(float fAttVal, XmlNode xn, String strAttribute){

	}

	/**
	 * 
	 * @param strAttVal
	 * @param xn
	 * @param strAttribute
	 */
	public static void GetAttributeOfElement(String strAttVal, XmlNode xn, String strAttribute){

	}

	/**
	 * 
	 * @param xn
	 * @param strXmlElement
	 * @param strXmlAttribute
	 */
	public static Boolean GetAttributeOfElementAsFlag(XmlNode xn, String strXmlElement, String strXmlAttribute){
		return null;
	}

	/**
	 * 
	 * @param bValue
	 */
	public static String GetBooleaneanString(Boolean bValue){
		return "";
	}

	/**
	 * 
	 * @param element
	 */
	public static XmlCDataSection GetCDataSectionNode(XmlElement element){
		return null;
	}

	/**
	 * 
	 * @param xn
	 * @param strTag
	 */
	public static XmlNodeList GetChildElementsByTagName(XmlNode xn, String strTag){
		return null;
	}

	/**
	 * 
	 * @param node
	 * @param strChildTagName
	 * @param strAttributeName
	 * @param strAttributeValue
	 */
	public static XmlElement GetChildWithSpecifiedAttribute(XmlElement node, String strChildTagName, String strAttributeName, String strAttributeValue){
		return null;
	}

	/**
	 * 
	 * @param node
	 */
	public static Boolean GetCurrentElementAsFlag(XmlElement node){
		return null;
	}

	/**
	 * 
	 * @param node
	 * @param bDefault
	 */
	public static Boolean GetCurrentElementAsFlag(XmlElement node, Boolean bDefault){
		return null;
	}

	/**
	 * 
	 * @param node
	 * @param strElement
	 */
	public static XmlElement GetDescendantElementAsElement(XmlNode node, String strElement){
		return null;
	}

	/**
	 * 
	 * @param node
	 * @param strElement
	 */
	public static XmlElement GetElementAsElement(XmlNode node, String strElement){
		return null;
	}

	/**
	 * 
	 * @param xn
	 * @param strElement
	 * @param strAttributeName
	 * @param strAttributeValue
	 */
	public static XmlElement GetElementAsElementByAttributeValue(XmlNode xn, String strElement, String strAttributeName, String strAttributeValue){
		return null;
	}

	/**
	 * 
	 * @param node
	 * @param strElement
	 */
	public static Boolean GetElementAsFlag(XmlElement node, String strElement){
		return null;
	}

	/**
	 * 
	 * @param node
	 * @param strElement
	 * @param bDefault
	 */
	public static Boolean GetElementAsFlag(XmlElement node, String strElement, Boolean bDefault){
		return null;
	}

	/**
	 * 
	 * @param node
	 * @param strElement
	 */
	public static String GetElementAsString(XmlElement node, String strElement){
		return "";
	}

	/**
	 * 
	 * @param node
	 * @param strElement
	 * @param strDefault
	 */
	public static String GetElementAsString(XmlElement node, String strElement, String strDefault){
		return "";
	}

	/**
	 * 
	 * @param node
	 * @param strElement
	 * @param strAttribute
	 */
	public static String GetElementAttributeString(XmlElement node, String strElement, String strAttribute){
		return "";
	}

	/**
	 * 
	 * @param node
	 * @param strElement
	 * @param strAttribute
	 * @param strDefault
	 */
	public static String GetElementAttributeString(XmlElement node, String strElement, String strAttribute, String strDefault){
		return "";
	}

	/**
	 * 
	 * @param strTag
	 */
	public static String GetEndTag(String strTag){
		return "";
	}

	public String getFalse(){
		return False;
	}

	/**
	 * 
	 * @param element
	 * @param strChildElement
	 */
	public static String GetOnlyChildElementInnerText(XmlElement element, String strChildElement){
		return "";
	}

	/**
	 * 
	 * @param element
	 */
	public static String GetOnlyElementInnerText(XmlElement element){
		return "";
	}

	/**
	 * 
	 * @param node
	 * @param strElement
	 * @param bResult
	 */
	public static Boolean GetRequiredElementAsFlag(XmlElement node, String strElement, Boolean bResult){
		return null;
	}

	/**
	 * 
	 * @param strTag
	 */
	public static String GetStartTag(String strTag){
		return "";
	}

	public String getTrue(){
		return True;
	}

	public String getValue(){
		return Value;
	}

	/**
	 * 
	 * @param strXml
	 * @param strElementToGet
	 */
	public static XmlElement LoadDocAndGetElement(String strXml, String strElementToGet){
		return null;
	}

	/**
	 * 
	 * @param strXml
	 * @param strElementToGet
	 */
	public static String LoadDocAndGetElementAsXml(String strXml, String strElementToGet){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFalse(String newVal){
		False = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTrue(String newVal){
		True = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setValue(String newVal){
		Value = newVal;
	}

	/**
	 * 
	 * @param bValue
	 */
	public static String ToXmlString(Boolean bValue){
		return "";
	}

}
