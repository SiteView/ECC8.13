package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:24
 */
public class IndexColumnCollection extends List implements IEnumerable {

	private ArrayList m_alColumns = new ArrayList();

	public IndexColumnCollection(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strColumnName
	 * @param bAscending
	 */
	public void AddColumn(String strColumnName, boolean bAscending){

	}

	public IndexColumnCollection Clone(){
		return null;
	}

	public String ColumnsAsString(){
		return "";
	}

	/**
	 * 
	 * @param col
	 */
	protected void CopyContents(IndexColumnCollection col){

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

	public IEnumerator GetEnumerator(){
		return null;
	}

	/**
	 * 
	 * @param col
	 */
	public void InsertColumn(IndexColumn col){

	}

	/**
	 * 
	 * @param nColumnNumber
	 * @param strColumnName
	 * @param bAscending
	 */
	public void InsertColumn(int nColumnNumber, String strColumnName, boolean bAscending){

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
	public IndexColumn this(int nColumnNumber){
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