package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-����-2010 14:33:23
 */
public class ExternalDbConnectionDef extends DbConnectionDef {



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ExternalDbConnectionDef(){

	}

	public static String ClassName(){
		return "";
	}

	public IDefinition Clone(){
		return null;
	}

	public ConnectionDefType ConnectionType(){
		return null;
	}

	/**
	 * 
	 * @param defConn
	 */
	public void CopyContents(ConnectionDef defConn){

	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	/**
	 * 
	 * @param serial
	 * @param defParent
	 */
	public static SerializableDef DeserializeCreate(DefSerializer serial, SerializableDef defParent){
		return null;
	}

	public String Location(){
		return "";
	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

	protected void SetConnectionPoolDefaults(){

	}

}