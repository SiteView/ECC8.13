package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:32:59
 */
public class DataTransport extends PersistenceInfo {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:32:59
	 */
	public enum MessagePriority {
		Low,
		Normal,
		High
	}

	private static CaseInsensitiveComparer comparer = new CaseInsensitiveComparer();
	private static CaseInsensitiveHashCodeProvider hashProvider = new CaseInsensitiveHashCodeProvider();
	private boolean m_bAtLeastOneLinked = false;
	private ArrayList m_bizObjs = new ArrayList();
	private boolean m_bSaveBackToFusion = true;
	private DateTime m_dateCreated = DateTime.MinValue;
	private DateTime m_dateReceived = DateTime.MinValue;
	private DateTime m_dateSent = DateTime.MinValue;
	private Hashtable m_dictHints = new Hashtable(hashProvider, comparer);
	private EmailAddress m_fromAddr = null;
	private IBusObDisplayKey m_key = null;
	private EmailAddressGroup m_linkToAddressGroup = EmailAddressGroup.AllEmailAddresses;
	private ArrayList m_listAttachmentInfo = new ArrayList();
	private ArrayList m_listBccAddr = new ArrayList();
	private ArrayList m_listCcAddr = new ArrayList();
	private ArrayList m_listLinkedObjects = new ArrayList();
	private ArrayList m_listMessageTokens = new ArrayList();
	private ArrayList m_listSelectedBusObs = new ArrayList();
	private ArrayList m_listToAddr = new ArrayList();
	private ArrayList m_listUnlinkedAddresses = new ArrayList();
	private ArrayList m_listUnlinkedBusObs = new ArrayList();
	private MessagePriority m_msgPriority = MessagePriority.Normal;
	private String m_strEntryId = "";
	private String m_strSourceApplication = "";
	private String m_strSubject = "";
	private UpdateResult m_updResult = null;

	public DataTransport(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param addGroup
	 */
	public void AddAddressGroup(EmailAddressGroup addGroup){

	}

	/**
	 * 
	 * @param strFileName
	 */
	public void AddAttachment(String strFileName){

	}

	/**
	 * 
	 * @param strKey
	 * @param key
	 */
	public void AddHint(String strKey, IBusObDisplayKey key){

	}

	/**
	 * 
	 * @param key
	 */
	public void AddLinkKey(IBusObDisplayKey key){

	}

	/**
	 * 
	 * @param strToken
	 */
	public void AddMessageToken(String strToken){

	}

	/**
	 * 
	 * @param key
	 */
	public void AddSelectedBusOb(IBusObDisplayKey key){

	}

	/**
	 * 
	 * @param address
	 * @param collKeys
	 */
	public void AddUnlinkedAddress(EmailAddress address, List collKeys){

	}

	/**
	 * 
	 * @param results
	 * @param address
	 */
	public void AddUnlinkedAddress(LinkResults results, EmailAddress address){

	}

	/**
	 * 
	 * @param results
	 * @param key
	 */
	public void AddUnlinkedBusOb(LinkResults results, IBusObDisplayKey key){

	}

	/**
	 * 
	 * @param collAddresses
	 */
	public static String AppendAddresses(List collAddresses){
		return "";
	}

	/**
	 * 
	 * @param collAttachments
	 */
	public static String AppendAttachmentNames(List collAttachments){
		return "";
	}

	/**
	 * 
	 * @param s
	 */
	protected String AssignNotNull(String s){
		return "";
	}

	public boolean AtLeastOneLinked(){
		return null;
	}

	public List AttachmentInfo(){
		return null;
	}

	public ArrayList BCC(){
		return null;
	}

	/**
	 * 
	 * @param strFormat
	 */
	public String BuildLayout(String strFormat){
		return "";
	}

	public ArrayList CC(){
		return null;
	}

	public void ClearHints(){

	}

	public void ClearLinkKeys(){

	}

	public void ClearUnlinkedAddresses(){

	}

	public void ClearUnlinkedBusObs(){

	}

	/**
	 * 
	 * @param strKey
	 */
	public boolean ContainsHint(String strKey){
		return null;
	}

	public DateTime Created(){
		return null;
	}

	public String EntryId(){
		return "";
	}

	public EmailAddress From(){
		return null;
	}

	public ArrayList FusionBusinessObjects(){
		return null;
	}

	public Map Hints(){
		return null;
	}

	public IBusObDisplayKey Key(){
		return null;
	}

	public List LinkedBusinessObjects(){
		return null;
	}

	public EmailAddressGroup LinkToAddressGroup(){
		return null;
	}

	/**
	 * 
	 * @param strKey
	 */
	public IBusObDisplayKey LookupHint(String strKey){
		return null;
	}

	public List MessageTokens(){
		return null;
	}

	/**
	 * 
	 * @param strAddressList
	 */
	public static List ParseAddresses(String strAddressList){
		return null;
	}

	public MessagePriority Priority(){
		return null;
	}

	public DateTime Received(){
		return null;
	}

	/**
	 * 
	 * @param removeGroup
	 */
	public void RemoveAddressGroup(EmailAddressGroup removeGroup){

	}

	/**
	 * 
	 * @param strKey
	 */
	public void RemoveHint(String strKey){

	}

	public boolean SaveBackToFusion(){
		return null;
	}

	public UpdateResult SaveStatus(){
		return null;
	}

	public List SelectedBusObs(){
		return null;
	}

	public DateTime Sent(){
		return null;
	}

	/**
	 * 
	 * @param n
	 */
	public void SetPriority(int n){

	}

	public String SourceApplication(){
		return "";
	}

	public String Subject(){
		return "";
	}

	public ArrayList To(){
		return null;
	}

	public List UnlinkedAddresses(){
		return null;
	}

	public List UnlinkedBusObs(){
		return null;
	}

	/**
	 * 
	 * @param addressGroup
	 */
	public boolean UseAddressGroup(EmailAddressGroup addressGroup){
		return null;
	}

}