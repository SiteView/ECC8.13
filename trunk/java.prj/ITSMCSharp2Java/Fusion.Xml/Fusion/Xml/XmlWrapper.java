package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:38:29
 */
public class XmlWrapper extends IDisposable {

	private ArrayList m_aTagStack = new ArrayList();
	private bool m_bReadMode = true;
	private int m_iTagStackPos = -1;
	private StringWriter m_writerString = null;
	private XmlTextWriter m_writerXml = null;
	private XmlDocument m_xdDocForRead = null;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public XmlWrapper(){

	}

	protected void CloseAllTags(){

	}

	private void CloseXmlTextWriter(){

	}

	private void CreateXmlTextWriter(){

	}

	public void Dispose(){

	}

	protected string GetClosingTags(){
		return "";
	}

	public string GetCurrentTag(){
		return "";
	}

	/**
	 * 
	 * @param aTagStack
	 */
	protected int GetDeepestCommonTag(ArrayList aTagStack){
		return 0;
	}

	/**
	 * 
	 * @param aTags
	 */
	protected ArrayList GetNewTagArray(Array aTags){
		return null;
	}

	protected int GetTagDepth(){
		return 0;
	}

	/**
	 * 
	 * @param strTag
	 */
	protected int GetTagDepthForTag(string strTag){
		return 0;
	}

	public string GetXml(){
		return "";
	}

	public string GetXmlSoFar(){
		return "";
	}

	public bool ReadMode(){
		return null;
	}

	public void SetReadMode(){

	}

	/**
	 * 
	 * @param aTags
	 */
	public void SetTagDepth(object[] aTags){

	}

	/**
	 * 
	 * @param strXml
	 */
	public void SetUpdateFromXml(string strXml){

	}

	public void SetWriteMode(){

	}

	public bool WriteMode(){
		return null;
	}

	public XmlDocument XmlDocForRead(){
		return null;
	}

	public XmlTextWriter XmlWriter(){
		return null;
	}

}