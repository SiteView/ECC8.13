package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:25
 */
public class KeyColumnCollection extends List implements IEnumerable {

	private ArrayList m_alColumns = new ArrayList();

	public KeyColumnCollection(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param col
	 */
	public void AddColumn(KeyColumn col){

	}

	/**
	 * 
	 * @param strColumnName
	 * @param strForeignKeyMapToColumn
	 */
	public void AddColumn(String strColumnName, String strForeignKeyMapToColumn){

	}

	public KeyColumnCollection Clone(){
		return null;
	}

	public String ColumnsAsString(){
		return "";
	}

	/**
	 * 
	 * @param col
	 */
	protected void CopyContents(KeyColumnCollection col){

	}

	/**
	 * 
	 * @param array
	 * @param nIndex
	 */
	public void CopyTo(Array array, int nIndex){

	}

	public int Count(){
		return 0;
	}

	public String ForeignKeyMapToColumnsAsString(){
		return "";
	}

	public IEnumerator GetEnumerator(){
		return null;
	}

	/**
	 * 
	 * @param col
	 */
	public void InsertColumn(KeyColumn col){

	}

	/**
	 * 
	 * @param nColumnNumber
	 * @param strColumnName
	 * @param strForeignKeyMapToColumn
	 */
	public void InsertColumn(int nColumnNumber, String strColumnName, String strForeignKeyMapToColumn){

	}

	public boolean IsSynchronized(){
		return null;
	}

	/**
	 * 
	 * @param nColumnNumber
	 */
	public void RemoveColumn(int nColumnNumber){

	}

	/**
	 * 
	 * @param strColumnName
	 */
	public void RemoveColumn(String strColumnName){

	}

	public Object SyncRoot(){
		return null;
	}

	/**
	 * 
	 * @param nColumnNumber
	 */
	public KeyColumn this(int nColumnNumber){
		return null;
	}

	/**
	 * 
	 * @param strColumn
	 */
	public Object this(String strColumn){
		return null;
	}

}