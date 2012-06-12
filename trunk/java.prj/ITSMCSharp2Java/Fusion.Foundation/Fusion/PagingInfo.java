package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:29
 */
public class PagingInfo extends ICloneable {

	private String m_aPagePosCache[] = null;
	private int m_iCount = -1;
	private int m_iCurrentPage = -1;
	private int m_iPageSize = 100;
	private int m_iRequestedPage = -1;

	public PagingInfo(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public Object Clone(){
		return null;
	}

	public int Count(){
		return 0;
	}

	public int CurrentPage(){
		return 0;
	}

	/**
	 * 
	 * @param iFromTop
	 * @param iFromBottom
	 */
	public int FindClosestEnd(int iFromTop, int iFromBottom){
		return 0;
	}

	public int FindClosestPageWithIndex(){
		return 0;
	}

	public String GetClosestPageIndex(){
		return "";
	}

	public string[] GetPosCache(){
		return "";
	}

	/**
	 * 
	 * @param ind
	 */
	public String GetPosCacheValue(int ind){
		return "";
	}

	public int PagesCount(){
		return 0;
	}

	public int PageSize(){
		return 0;
	}

	protected string[] PosCache(){
		return "";
	}

	public int RecordsOnLastPage(){
		return 0;
	}

	public int RequestedPage(){
		return 0;
	}

	/**
	 * 
	 * @param a
	 */
	public void SetPosCache(string[] a){

	}

	/**
	 * 
	 * @param ind
	 * @param sVal
	 */
	public void SetPosCacheValue(int ind, String sVal){

	}

}