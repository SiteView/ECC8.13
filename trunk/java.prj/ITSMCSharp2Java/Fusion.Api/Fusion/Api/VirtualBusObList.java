package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:46:05
 */
public class VirtualBusObList implements IVirtualList, Fusion.IVirtualList, IList, List, IEnumerable, ITypedList {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:46:05
	 */
	public protected class VirtualBusObListEnumerator extends IEnumerator {

		private int m_nCurrent = -1;
		private Fusion.Api.VirtualBusObList m_vBusObList = null;

		public VirtualBusObListEnumerator(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		/**
		 * 
		 * @param vBusObList
		 */
		public VirtualBusObListEnumerator(Fusion.Api.VirtualBusObList vBusObList){

		}

		public Object Current(){
			return null;
		}

		public boolean MoveNext(){
			return null;
		}

		public void Reset(){

		}

	}

	private FusionApi m_api;
	private Fusion.Api.BusinessObjectDef m_BusObDef;
	protected VirtualBusObListSupportedTypes m_SupportedTypes;
	private Fusion.BusinessLogic.VirtualBusObList m_vBusObList;

	public VirtualBusObList(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param api
	 * @param q
	 */
	public VirtualBusObList(IFusionApi api, FusionQuery q){

	}

	/**
	 * 
	 * @param busObList
	 * @param api
	 */
	public VirtualBusObList(Fusion.IVirtualList busObList, IFusionApi api){

	}

	/**
	 * 
	 * @param api
	 * @param q
	 * @param result
	 */
	public VirtualBusObList(IFusionApi api, FusionQuery q, IQueryResult result){

	}

	/**
	 * 
	 * @param type
	 * @param api
	 * @param q
	 */
	public VirtualBusObList(VirtualBusObListSupportedTypes type, IFusionApi api, FusionQuery q){

	}

	/**
	 * 
	 * @param type
	 * @param busObList
	 * @param api
	 */
	public VirtualBusObList(VirtualBusObListSupportedTypes type, Fusion.IVirtualList busObList, IFusionApi api){

	}

	/**
	 * 
	 * @param type
	 * @param api
	 * @param q
	 * @param result
	 */
	public VirtualBusObList(VirtualBusObListSupportedTypes type, IFusionApi api, FusionQuery q, IQueryResult result){

	}

	/**
	 * 
	 * @param value
	 */
	public int Add(Object value){
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

	private Fusion.Api.BusinessObjectDef BusObDef(){
		return null;
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
	 * @param value
	 */
	public boolean Contains(Object value){
		return null;
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

	public int DesiredPageSize(){
		return 0;
	}

	/**
	 * 
	 * @param busOb
	 */
	private Fusion.Api.BusinessObject GetAggregate(Fusion.BusinessLogic.BusinessObject busOb){
		return null;
	}

	/**
	 * 
	 * @param nIndex
	 */
	public Fusion.Api.BusinessObject GetBusObAtIndex(int nIndex){
		return null;
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
		return null;
	}

	/**
	 * 
	 * @param value
	 */
	public int IndexOf(Object value){
		return 0;
	}

	/**
	 * 
	 * @param index
	 * @param value
	 */
	public void Insert(int index, Object value){

	}

	public boolean IsFixedSize(){
		return null;
	}

	public boolean IsReadOnly(){
		return null;
	}

	public boolean IsSynchronized(){
		return null;
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
	 * @param value
	 */
	public void Remove(Object value){

	}

	/**
	 * 
	 * @param index
	 */
	public void RemoveAt(int index){

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
	 * @param nIndex
	 */
	public int ResolveToVirtualListIndex(int nIndex){
		return 0;
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
	 * @param index
	 */
	public Object this(int index){
		return null;
	}

}