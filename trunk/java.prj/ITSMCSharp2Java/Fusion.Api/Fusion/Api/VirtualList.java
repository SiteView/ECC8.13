package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:46:07
 */
public class VirtualList implements IVirtualList, Fusion.IVirtualList, IList, List, IEnumerable, ITypedList {

	protected Fusion.BusinessLogic.VirtualList m_vList;

	public VirtualList(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param api
	 */
	public VirtualList(IFusionApi api){

	}

	/**
	 * 
	 * @param api
	 * @param q
	 */
	public VirtualList(IFusionApi api, FusionQuery q){

	}

	/**
	 * 
	 * @param type
	 * @param api
	 */
	public VirtualList(VirtualListSupportedTypes type, IFusionApi api){

	}

	/**
	 * 
	 * @param api
	 * @param q
	 * @param result
	 */
	public VirtualList(IFusionApi api, FusionQuery q, IQueryResult result){

	}

	/**
	 * 
	 * @param type
	 * @param api
	 * @param q
	 */
	public VirtualList(VirtualListSupportedTypes type, IFusionApi api, FusionQuery q){

	}

	/**
	 * 
	 * @param type
	 * @param api
	 * @param q
	 * @param result
	 */
	public VirtualList(VirtualListSupportedTypes type, IFusionApi api, FusionQuery q, IQueryResult result){

	}

	/**
	 * 
	 * @param o
	 */
	public int Add(Object o){
		return 0;
	}

	/**
	 * 
	 * @param aFields
	 */
	public void AddGroupBy(String[] aFields){

	}

	/**
	 * 
	 * @param bAscending
	 * @param aFields
	 */
	public void AddOrderBy(boolean bAscending, String[] aFields){

	}

	public CellDataRequestedHandler CellDataRequested(){
		return null;
	}

	public void Clear(){

	}

	public void ClearFilter(){

	}

	/**
	 * 
	 * @param o
	 */
	public boolean Contains(Object o){
		return false;
	}

	/**
	 * 
	 * @param a
	 * @param ind
	 */
	public void CopyTo(Array a, int ind){

	}

	public int Count(){
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
	 * @param type
	 * @param qr
	 */
	protected Fusion.BusinessLogic.VirtualList CreateVirtualList(VirtualListSupportedTypes type, QueryResolver qr){
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

	/**
	 * 
	 * @param type
	 * @param qr
	 * @param q
	 */
	protected Fusion.BusinessLogic.VirtualList CreateVirtualList(VirtualListSupportedTypes type, QueryResolver qr, FusionQuery q){
		return null;
	}

	/**
	 * 
	 * @param type
	 * @param qr
	 * @param q
	 * @param result
	 */
	protected Fusion.BusinessLogic.VirtualList CreateVirtualList(VirtualListSupportedTypes type, QueryResolver qr, FusionQuery q, IQueryResult result){
		return null;
	}

	public int DesiredPageSize(){
		return 0;
	}

	/**
	 * 
	 * @param iRow
	 * @param sColumn
	 */
	public Object GetCellData(int iRow, String sColumn){
		return null;
	}

	public IEnumerator GetEnumerator(){
		return null;
	}

	/**
	 * 
	 * @param iFunction
	 * @param iStart
	 */
	public Object GetFunction(int iFunction, int iStart){
		return null;
	}

	/**
	 * 
	 * @param listAccessors
	 */
	public PropertyDescriptorCollection GetItemProperties(PropertyDescriptor[] listAccessors){
		return null;
	}

	/**
	 * 
	 * @param listAccessors
	 */
	public String GetListName(PropertyDescriptor[] listAccessors){
		return "";
	}

	/**
	 * 
	 * @param iRow
	 */
	public DataRow GetRowData(int iRow){
		return null;
	}

	/**
	 * 
	 * @param sField
	 */
	public int HasGroupBy(String sField){
		return 0;
	}

	public boolean IgnoreRequest(){
		return false;
	}

	/**
	 * 
	 * @param o
	 */
	public int IndexOf(Object o){
		return 0;
	}

	/**
	 * 
	 * @param ind
	 * @param o
	 */
	public void Insert(int ind, Object o){

	}

	public boolean IsFixedSize(){
		return false;
	}

	public boolean IsReadOnly(){
		return false;
	}

	public boolean IsSynchronized(){
		return false;
	}

	public IQueryResult MoveToFirstPage(){
		return null;
	}

	public IQueryResult MoveToNextPage(){
		return null;
	}

	/**
	 * 
	 * @param iPage
	 */
	public IQueryResult MoveToPage(int iPage){
		return null;
	}

	public IQueryResult MoveToPrevPage(){
		return null;
	}

	/**
	 * 
	 * @param sender
	 * @param iRowIndex
	 * @param sColumn
	 */
	public void OnCellDataRequested(Object sender, int iRowIndex, String sColumn){

	}

	public int PagesCount(){
		return 0;
	}

	public int PageSize(){
		return 0;
	}

	public FusionQuery Query(){
		return null;
	}

	/**
	 * 
	 * @param ind
	 */
	public int RecordPage(int ind){
		return 0;
	}

	/**
	 * 
	 * @param o
	 */
	public void Remove(Object o){

	}

	/**
	 * 
	 * @param ind
	 */
	public void RemoveAt(int ind){

	}

	/**
	 * 
	 * @param aFields
	 */
	public void RemoveGroupBy(String[] aFields){

	}

	/**
	 * 
	 * @param aFields
	 */
	public void RemoveOrderBy(String[] aFields){

	}

	public void Reset(){

	}

	/**
	 * 
	 * @param el
	 */
	public DataTable ResolveFunctions(XmlElement[] el){
		return null;
	}

	/**
	 * 
	 * @param el
	 */
	public void SetFilter(XmlElement el){

	}

	public void SoftReset(){

	}

	public Object SyncRoot(){
		return null;
	}

	/**
	 * 
	 * @param ind
	 */
	public Object this(int ind){
		return null;
	}

}