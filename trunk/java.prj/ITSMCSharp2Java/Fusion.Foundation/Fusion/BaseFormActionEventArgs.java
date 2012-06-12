package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:43
 */
public abstract class BaseFormActionEventArgs extends EventArgs {

	private static CaseInsensitiveComparer comparer = new CaseInsensitiveComparer();
	private static CaseInsensitiveHashCodeProvider hashProvider = new CaseInsensitiveHashCodeProvider();
	private ArrayList m_aParameters = new ArrayList();
	private boolean m_bShiftDown = false;
	private Hashtable m_dictCargo = new Hashtable(hashProvider, comparer);
	private String m_strAction = "";

	public BaseFormActionEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public String Action(){
		return "";
	}

	public int ActionParameterCount(){
		return 0;
	}

	public List ActionParameters(){
		return null;
	}

	/**
	 * 
	 * @param o
	 */
	public void AddActionParameter(Object o){

	}

	/**
	 * 
	 * @param strName
	 * @param cargo
	 */
	public void AddCargo(String strName, Object cargo){

	}

	public void ClearActionParameters(){

	}

	/**
	 * 
	 * @param key
	 */
	public Object GetActionParameter(Object key){
		return null;
	}

	/**
	 * 
	 * @param iPos
	 */
	public Object GetActionParameterAt(int iPos){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Object GetCargo(String strName){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public boolean HasCargo(String strName){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public void RemoveCargo(String strName){

	}

	public boolean ShiftDown(){
		return null;
	}

}