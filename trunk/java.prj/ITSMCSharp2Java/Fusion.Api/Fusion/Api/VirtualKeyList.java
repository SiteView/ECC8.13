package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:46:07
 */
public class VirtualKeyList extends VirtualList implements IVirtualKeyList, IDisposable {

	public VirtualKeyList(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param api
	 */
	public VirtualKeyList(IFusionApi api){

	}

	/**
	 * 
	 * @param api
	 * @param q
	 */
	public VirtualKeyList(IFusionApi api, FusionQuery q){

	}

	/**
	 * 
	 * @param type
	 * @param api
	 */
	public VirtualKeyList(VirtualListSupportedTypes type, IFusionApi api){

	}

	/**
	 * 
	 * @param type
	 * @param api
	 * @param q
	 */
	public VirtualKeyList(VirtualListSupportedTypes type, IFusionApi api, FusionQuery q){

	}

	public boolean AddAboveCurrentRow(){
		return false;
	}

	/**
	 * 
	 * @param strId
	 * @param strName
	 */
	public int AddKey(String strId, String strName){
		return 0;
	}

	/**
	 * 
	 * @param qr
	 */
	protected Fusion.BusinessLogic.VirtualList CreateVirtualList(QueryResolver qr){
		return null;
	}

	/**
	 * 
	 * @param qr
	 * @param q
	 */
	protected Fusion.BusinessLogic.VirtualList CreateVirtualList(QueryResolver qr, FusionQuery q){
		return null;
	}

	/**
	 * 
	 * @param qr
	 * @param q
	 * @param result
	 */
	protected Fusion.BusinessLogic.VirtualList CreateVirtualList(QueryResolver qr, FusionQuery q, IQueryResult result){
		return null;
	}

	public IVirtualBusObKey Current(){
		return null;
	}

	public int CurrentPosition(){
		return 0;
	}

	public void Dispose(){

	}

	public void First(){

	}

	public boolean HasItems(){
		return false;
	}

	private Fusion.BusinessLogic.VirtualKeyList InternalVirtualKeyList(){
		return null;
	}

	/**
	 * 
	 * @param nPos
	 */
	public boolean Jump(int nPos){
		return false;
	}

	public void Last(){

	}

	public boolean Next(){
		return false;
	}

	public boolean Previous(){
		return false;
	}

	/**
	 * 
	 * @param strId
	 */
	public void RemoveCachedDataForRow(String strId){

	}

	public void RemoveCurrentKey(){

	}

}