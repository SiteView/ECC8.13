package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:45
 */
public class UpdateResult {

	private static CaseInsensitiveComparer comparer = new CaseInsensitiveComparer();
	private static final UpdateResult EmptySuccesful = new UpdateResult();
	private static CaseInsensitiveHashCodeProvider hashProvider = new CaseInsensitiveHashCodeProvider();
	private ArrayList m_aDelayedNotifications;
	private boolean m_bBusObsIgnoreNotifications = false;
	private boolean m_bDelayNotification = false;
	private boolean m_bResult = true;
	private boolean m_bRollback = false;
	private ConcurrencyViolationException m_ConcurrencyViolationException;
	private Hashtable m_dictCargo;
	private Hashtable m_dictIgnoreNotifications;
	private Exception m_ExceptionToThrow;
	private static int m_iNextTransactionID = 1;
	private int m_iTransactionDepth = 0;
	private int m_iTransactionID = -1;
	private MessageInfoList m_msgHolder;
	private Stack m_stackRollbacks;
	private UpdatePackage m_updatePackage;

	public UpdateResult(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strName
	 * @param cargo
	 */
	public void AddCargo(String strName, Object cargo){

	}

	/**
	 * 
	 * @param strSource
	 * @param strCategory
	 */
	public void AddNotificationToIgnore(String strSource, String strCategory){

	}

	public void BeginTransaction(){

	}

	public boolean BusObsIgnoreNotifications(){
		return null;
	}

	public void ClearDelayedNotifications(){

	}

	protected void ClearRollbackStack(){

	}

	public void ClearUpdates(){

	}

	public boolean DelayNotification(){
		return null;
	}

	/**
	 * 
	 * @param bResult
	 */
	public void EndTransaction(boolean bResult){

	}

	public String ErrorMessages(){
		return "";
	}

	public void FireDelayedNotifications(){

	}

	/**
	 * 
	 * @param strName
	 */
	public Object GetCargo(String strName){
		return null;
	}

	public UpdateResult getEmptySuccesful(){
		return EmptySuccesful;
	}

	/**
	 * 
	 * @param strName
	 */
	public boolean HasCargo(String strName){
		return null;
	}

	public boolean HasErrors(){
		return null;
	}

	public ConcurrencyViolationException HeldConcurrencyViolationException(){
		return null;
	}

	public boolean InTransaction(){
		return null;
	}

	/**
	 * 
	 * @param strSource
	 */
	public String LookupNotificationToIgnore(String strSource){
		return "";
	}

	public MessageInfoList MessageList(){
		return null;
	}

	/**
	 * 
	 * @param ur
	 */
	public static UpdateResult NonNull(UpdateResult ur){
		return null;
	}

	/**
	 * 
	 * @param PrimaryTarget
	 * @param notif
	 */
	public void Notify(INotifiable PrimaryTarget, Notification notif){

	}

	/**
	 * 
	 * @param rb
	 */
	public void RecordRollbackInfo(IRollback rb){

	}

	public void RemoveAllNotificationsToIgnore(){

	}

	/**
	 * 
	 * @param strName
	 */
	public void RemoveCargo(String strName){

	}

	/**
	 * 
	 * @param strSource
	 */
	public void RemoveNotificationToIgnore(String strSource){

	}

	public void Rollback(){

	}

	protected void RollbackAllChanges(){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEmptySuccesful(UpdateResult newVal){
		EmptySuccesful = newVal;
	}

	/**
	 * 
	 * @param bResult
	 */
	public void SetErrorResult(boolean bResult){

	}

	/**
	 * 
	 * @param ex
	 */
	public void SetException(Exception ex){

	}

	public boolean ShouldRollback(){
		return null;
	}

	public boolean Success(){
		return null;
	}

	protected void ThrowExceptionIfAppropriate(){

	}

	public int TransactionID(){
		return 0;
	}

	public UpdatePackage Updates(){
		return null;
	}

}