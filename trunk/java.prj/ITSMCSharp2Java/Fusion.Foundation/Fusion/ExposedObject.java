package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:22
 */
public class ExposedObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:22
	 */
	public enum ObjectKinds {
		ParentBusOb,
		ChildBusOb,
		BusOb,
		LinkedBusOb
	}

	private ObjectKinds m_Kind;
	private Object m_Object;
	private String m_strExposedBy;

	public ExposedObject(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strExposedBy
	 * @param kind
	 * @param ob
	 */
	public ExposedObject(String strExposedBy, ObjectKinds kind, Object ob){

	}

	public String ExposedBy(){
		return "";
	}

	public ObjectKinds Kind(){
		return null;
	}

	public Object Object(){
		return null;
	}

}