package Fusion;

import java.io.Serializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:15
 */
public class SerializableXmlDocument implements Serializable {

	private XmlDocument m_XmlDocument;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public SerializableXmlDocument(){

	}

	/**
	 * 
	 * @param doc
	 */
	public SerializableXmlDocument(XmlDocument doc){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected SerializableXmlDocument(SerializationInfo info, StreamingContext context){

	}

	public XmlDocument Document(){
		return null;
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

}