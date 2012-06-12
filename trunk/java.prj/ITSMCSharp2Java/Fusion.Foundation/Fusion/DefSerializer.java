package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:13
 */
public class DefSerializer {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:13
	 */
	private class Tags {

		private String attCategory = "Category";
		private String attId = "ID";
		private String attName = "Name";
		private String attValue = "Value";
		private String attVersion = "Version";
		private String valFalse = "FALSE";
		private String valTrue = "TRUE";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getattCategory(){
			return attCategory;
		}

		public String getattId(){
			return attId;
		}

		public String getattName(){
			return attName;
		}

		public String getattValue(){
			return attValue;
		}

		public String getattVersion(){
			return attVersion;
		}

		public String getvalFalse(){
			return valFalse;
		}

		public String getvalTrue(){
			return valTrue;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setattCategory(String newVal){
			attCategory = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setattId(String newVal){
			attId = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setattName(String newVal){
			attName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setattValue(String newVal){
			attValue = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setattVersion(String newVal){
			attVersion = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setvalFalse(String newVal){
			valFalse = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setvalTrue(String newVal){
			valTrue = newVal;
		}

	}

	private static CaseInsensitiveComparer comparer = new CaseInsensitiveComparer();
	private String EncryptedDataElementName = "EncryptedData";
	private static CaseInsensitiveHashCodeProvider hashProvider = new CaseInsensitiveHashCodeProvider();
	private static byte iv[] = new byte[] { 0x45, 15, 210, 0x93, 0x7a, 0xa9, 0x92, 0x2d, 0x95, 0x79, 0x7f, 0x27, 0x12, 0x6d, 0x37, 14 };
	private static byte key[] = new byte[] { 
	                  0x73, 0x3f, 14, 0xdb, 0xc7, 0x31, 0xee, 0x70, 0x95, 7, 0x18, 190, 0xc1, 0x93, 0x7f, 0xf4, 
	                  0x10, 1, 0x37, 0xae, 0xc6, 0x63, 0xae, 0x5b, 0x6b, 0xa1, 0xdb, 0x52, 0x39, 0xb8, 0xd9, 5
	               };
	private boolean m_bEncrypted = false;
	private boolean m_bListSubSerializer = false;
	private boolean m_bReadPrimaryInfo = false;
	private boolean m_bSerializer = false;
	private Hashtable m_htCargo = null;
	private int m_iVersion = 0;
	private XmlElement m_ListElement = null;
	private MethodInfo m_miLastUsed = null;
	private IEnumerator m_NodeListEnumerator = null;
	private String m_strCategory = "";
	private String m_strGeneralPropertyRoot = "";
	private String m_strId = "";
	private String m_strName = "";
	private String m_strSpecificPropertyRoot = "";
	private Type m_typeLastUsed = null;
	private XmlElement m_xeGeneralPropertyRoot = null;
	private XmlElement m_xeRoot = null;
	private XmlElement m_xeSpecificPropertyRoot = null;
	private XmlDocument m_XmlDocument = null;
	private XmlNodeList m_xnlSubList = null;

	public DefSerializer(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param bEncrypted
	 */
	public DefSerializer(boolean bEncrypted){

	}

	/**
	 * 
	 * @param strName
	 * @param oCargo
	 */
	public void AddCargo(String strName, Object oCargo){

	}

	/**
	 * 
	 * @param alItems
	 * @param htItems
	 * @param bByName
	 * @param bUpperCase
	 */
	protected void ArrayToHashtable(ArrayList alItems, Hashtable htItems, boolean bByName, boolean bUpperCase){

	}

	protected Hashtable Cargo(){
		return null;
	}

	public String Category(){
		return "";
	}

	public void Clear(){

	}

	public void ClearCargo(){

	}

	protected void ConfirmDeserializer(){

	}

	protected void ConfirmSerializer(){

	}

	private SymmetricAlgorithm CreateAlgorithm(){
		return null;
	}

	/**
	 * 
	 * @param typeChild
	 * @param parentSerializer
	 */
	protected static DefSerializer CreateChildSerializer(Type typeChild, DefSerializer parentSerializer){
		return null;
	}

	/**
	 * 
	 * @param element
	 * @param defType
	 * @param bllOrch
	 */
	public static SerializableDef CreateFromXml(XmlElement element, Type defType, IBllOrchestrator bllOrch){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 */
	public void CreateNewChild(String strProperty){

	}

	/**
	 * 
	 * @param def
	 */
	public static DefSerializer CreateSerializer(SerializableDef def){
		return null;
	}

	/**
	 * 
	 * @param defType
	 */
	public static DefSerializer CreateSerializer(Type defType){
		return null;
	}

	/**
	 * 
	 * @param xmlElement
	 */
	private void Decrypt(XmlElement xmlElement){

	}

	/**
	 * 
	 * @param doc
	 * @param xeChild
	 * @param typeListItems
	 * @param defParent
	 */
	protected SerializableDef DeserializeChild(XmlDocument doc, XmlElement xeChild, Type typeListItems, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param doc
	 * @param xeChild
	 * @param typeListItems
	 * @param defParent
	 */
	protected String DeserializeIdFromChild(XmlDocument doc, XmlElement xeChild, Type typeListItems, SerializableDef defParent){
		return "";
	}

	protected void DetermineBaseInfo(){

	}

	/**
	 * 
	 * @param xmlDoc
	 */
	private void Encrypt(XmlDocument xmlDoc){

	}

	public String GeneralComment(){
		return "";
	}

	public String GeneralPropertyRoot(){
		return "";
	}

	/**
	 * 
	 * @param htItems
	 * @param typeListItems
	 * @param bUpperCase
	 * @param defParent
	 */
	public boolean GetCoreDictionaryProperty(Hashtable htItems, Type typeListItems, boolean bUpperCase, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param htItems
	 * @param typeListItems
	 * @param bUpperCase
	 * @param defParent
	 */
	public boolean GetCoreDictionaryPropertyById(Hashtable htItems, Type typeListItems, boolean bUpperCase, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strValue
	 */
	public boolean GetCoreInnerXml(String strValue){
		return null;
	}

	/**
	 * 
	 * @param alItems
	 * @param typeListItems
	 * @param defParent
	 */
	public boolean GetCoreListProperty(ArrayList alItems, Type typeListItems, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public boolean GetCoreListSubSerializer(DefSerializer serial){
		return null;
	}

	/**
	 * 
	 * @param bValue
	 */
	public boolean GetCoreProperty(boolean bValue){
		return null;
	}

	/**
	 * 
	 * @param dValue
	 */
	public boolean GetCoreProperty(double dValue){
		return null;
	}

	/**
	 * 
	 * @param nValue
	 */
	public boolean GetCoreProperty(int nValue){
		return null;
	}

	/**
	 * 
	 * @param strValue
	 */
	public boolean GetCoreProperty(String strValue){
		return null;
	}

	/**
	 * 
	 * @param bDefaultValue
	 * @param bValue
	 */
	public void GetCoreProperty(boolean bDefaultValue, boolean bValue){

	}

	/**
	 * 
	 * @param dDefaultValue
	 * @param dValue
	 */
	public void GetCoreProperty(double dDefaultValue, double dValue){

	}

	/**
	 * 
	 * @param nDefaultValue
	 * @param nValue
	 */
	public void GetCoreProperty(int nDefaultValue, int nValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param bValue
	 */
	public boolean GetCoreProperty(String strProperty, boolean bValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param dValue
	 */
	public boolean GetCoreProperty(String strProperty, double dValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param nValue
	 */
	public boolean GetCoreProperty(String strProperty, int nValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public boolean GetCoreProperty(String strProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param bDefaultValue
	 * @param bValue
	 */
	public void GetCoreProperty(String strProperty, boolean bDefaultValue, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param dDefaultValue
	 * @param dValue
	 */
	public void GetCoreProperty(String strProperty, double dDefaultValue, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param nDefaultValue
	 * @param nValue
	 */
	public void GetCoreProperty(String strProperty, int nDefaultValue, int nValue){

	}

	/**
	 * 
	 * @param typeClass
	 */
	protected MethodInfo GetCreateMethodInfo(Type typeClass){
		return null;
	}

	/**
	 * 
	 * @param xeParent
	 * @param strElement
	 * @param bCreateIfNeeded
	 */
	protected XmlElement GetElement(XmlElement xeParent, String strElement, boolean bCreateIfNeeded){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param typeItem
	 * @param defParent
	 */
	public SerializableDef GetGeneralChildProperty(String strProperty, Type typeItem, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param bCreateIfNeeded
	 */
	protected XmlComment GetGeneralCommentElement(boolean bCreateIfNeeded){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param htItems
	 * @param typeListItems
	 * @param bUpperCase
	 * @param defParent
	 */
	public boolean GetGeneralDictionaryProperty(String strListProperty, Hashtable htItems, Type typeListItems, boolean bUpperCase, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param htItems
	 * @param typeListItems
	 * @param bUpperCase
	 * @param defParent
	 */
	public boolean GetGeneralDictionaryPropertyById(String strListProperty, Hashtable htItems, Type typeListItems, boolean bUpperCase, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strElement
	 * @param bCreateIfNeeded
	 */
	protected XmlElement GetGeneralElement(String strElement, boolean bCreateIfNeeded){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public boolean GetGeneralInnerXml(String strProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param alItems
	 * @param typeListItems
	 * @param defParent
	 */
	public boolean GetGeneralListProperty(String strListProperty, ArrayList alItems, Type typeListItems, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param serial
	 */
	public boolean GetGeneralListSubSerializer(String strListProperty, DefSerializer serial){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param bValue
	 */
	public boolean GetGeneralProperty(String strProperty, boolean bValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param dValue
	 */
	public boolean GetGeneralProperty(String strProperty, double dValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param nValue
	 */
	public boolean GetGeneralProperty(String strProperty, int nValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public boolean GetGeneralProperty(String strProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param bDefaultValue
	 * @param bValue
	 */
	public void GetGeneralProperty(String strProperty, boolean bDefaultValue, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param dDefaultValue
	 * @param dValue
	 */
	public void GetGeneralProperty(String strProperty, double dDefaultValue, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param nDefaultValue
	 * @param nValue
	 */
	public void GetGeneralProperty(String strProperty, int nDefaultValue, int nValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param bValue
	 */
	public boolean GetGeneralProperty(String strProperty, String strSubProperty, boolean bValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param dValue
	 */
	public boolean GetGeneralProperty(String strProperty, String strSubProperty, double dValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param nValue
	 */
	public boolean GetGeneralProperty(String strProperty, String strSubProperty, int nValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param strValue
	 */
	public boolean GetGeneralProperty(String strProperty, String strSubProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param bDefaultValue
	 * @param bValue
	 */
	public void GetGeneralProperty(String strProperty, String strSubProperty, boolean bDefaultValue, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param dDefaultValue
	 * @param dValue
	 */
	public void GetGeneralProperty(String strProperty, String strSubProperty, double dDefaultValue, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param nDefaultValue
	 * @param nValue
	 */
	public void GetGeneralProperty(String strProperty, String strSubProperty, int nDefaultValue, int nValue){

	}

	/**
	 * 
	 * @param bCreateIfNeeded
	 */
	protected XmlElement GetGeneralPropertyRootNode(boolean bCreateIfNeeded){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public boolean GetGeneralRawProperty(String strProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param alItems
	 */
	public boolean GetGeneralStringList(String strListProperty, String strListItemProperty, ArrayList alItems){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strProperty
	 * @param alItems
	 */
	public boolean GetGeneralStringList(String strListProperty, String strListItemProperty, String strProperty, ArrayList alItems){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param htItems
	 * @param bUpperCase
	 */
	public boolean GetGeneralStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, Hashtable htItems, boolean bUpperCase){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param strValueProperty
	 * @param htItems
	 * @param bUpperCase
	 */
	public boolean GetGeneralStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, String strValueProperty, Hashtable htItems, boolean bUpperCase){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param strValueProperty
	 * @param htItems
	 * @param bUpperCase
	 */
	public boolean GetGeneralStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, String strValueProperty, SortedList htItems, boolean bUpperCase){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param strValueProperty
	 * @param ldListDictionary
	 * @param bUpperCase
	 */
	public boolean GetGeneralStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, String strValueProperty, ListDictionary ldListDictionary, boolean bUpperCase){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param serial
	 */
	public boolean GetGeneralSubSerializer(String strProperty, DefSerializer serial){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public boolean GetGeneralValueProperty(String strProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeList
	 * @param alItems
	 * @param typeListItems
	 * @param defParent
	 */
	protected boolean GetListProperty(XmlElement xeList, ArrayList alItems, Type typeListItems, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param xeProperty
	 * @param serial
	 */
	protected boolean GetListSubSerializer(XmlElement xeProperty, DefSerializer serial){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param typeItem
	 * @param defParent
	 */
	public SerializableDef GetSpecificChildProperty(String strProperty, Type typeItem, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param bValue
	 */
	public boolean GetSpecificCoreProperty(String strProperty, boolean bValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param dValue
	 */
	public boolean GetSpecificCoreProperty(String strProperty, double dValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param nValue
	 */
	public boolean GetSpecificCoreProperty(String strProperty, int nValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public boolean GetSpecificCoreProperty(String strProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param bDefaultValue
	 * @param bValue
	 */
	public void GetSpecificCoreProperty(String strProperty, boolean bDefaultValue, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param dDefaultValue
	 * @param dValue
	 */
	public void GetSpecificCoreProperty(String strProperty, double dDefaultValue, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param nDefaultValue
	 * @param nValue
	 */
	public void GetSpecificCoreProperty(String strProperty, int nDefaultValue, int nValue){

	}

	/**
	 * 
	 * @param strListProperty
	 * @param htItems
	 * @param typeListItems
	 * @param bUpperCase
	 * @param defParent
	 */
	public boolean GetSpecificDictionaryProperty(String strListProperty, Hashtable htItems, Type typeListItems, boolean bUpperCase, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param htItems
	 * @param typeListItems
	 * @param bUpperCase
	 * @param defParent
	 */
	public boolean GetSpecificDictionaryPropertyById(String strListProperty, Hashtable htItems, Type typeListItems, boolean bUpperCase, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strElement
	 * @param bCreateIfNeeded
	 */
	protected XmlElement GetSpecificElement(String strElement, boolean bCreateIfNeeded){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public boolean GetSpecificInnerXml(String strProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param alItems
	 * @param typeListItems
	 * @param defParent
	 */
	public boolean GetSpecificListProperty(ArrayList alItems, Type typeListItems, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param alItems
	 * @param typeListItems
	 * @param defParent
	 */
	public boolean GetSpecificListProperty(String strListProperty, ArrayList alItems, Type typeListItems, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param serial
	 */
	public boolean GetSpecificListSubSerializer(String strListProperty, DefSerializer serial){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param bValue
	 */
	public boolean GetSpecificProperty(String strProperty, boolean bValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param dValue
	 */
	public boolean GetSpecificProperty(String strProperty, double dValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param nValue
	 */
	public boolean GetSpecificProperty(String strProperty, int nValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public boolean GetSpecificProperty(String strProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param bDefaultValue
	 * @param bValue
	 */
	public void GetSpecificProperty(String strProperty, boolean bDefaultValue, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param dDefaultValue
	 * @param dValue
	 */
	public void GetSpecificProperty(String strProperty, double dDefaultValue, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param nDefaultValue
	 * @param nValue
	 */
	public void GetSpecificProperty(String strProperty, int nDefaultValue, int nValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param bValue
	 */
	public boolean GetSpecificProperty(String strProperty, String strSubProperty, boolean bValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param dValue
	 */
	public boolean GetSpecificProperty(String strProperty, String strSubProperty, double dValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param nValue
	 */
	public boolean GetSpecificProperty(String strProperty, String strSubProperty, int nValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param strValue
	 */
	public boolean GetSpecificProperty(String strProperty, String strSubProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param bDefaultValue
	 * @param bValue
	 */
	public void GetSpecificProperty(String strProperty, String strSubProperty, boolean bDefaultValue, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param dDefaultValue
	 * @param dValue
	 */
	public void GetSpecificProperty(String strProperty, String strSubProperty, double dDefaultValue, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param nDefaultValue
	 * @param nValue
	 */
	public void GetSpecificProperty(String strProperty, String strSubProperty, int nDefaultValue, int nValue){

	}

	/**
	 * 
	 * @param bCreateIfNeeded
	 */
	protected XmlElement GetSpecificPropertyRootNode(boolean bCreateIfNeeded){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public boolean GetSpecificRawProperty(String strProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param alItems
	 */
	public boolean GetSpecificStringList(String strListProperty, String strListItemProperty, ArrayList alItems){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strProperty
	 * @param alItems
	 */
	public boolean GetSpecificStringList(String strListProperty, String strListItemProperty, String strProperty, ArrayList alItems){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param htItems
	 * @param bUpperCase
	 */
	public boolean GetSpecificStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, Hashtable htItems, boolean bUpperCase){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param strValueProperty
	 * @param htItems
	 * @param bUpperCase
	 */
	public boolean GetSpecificStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, String strValueProperty, Hashtable htItems, boolean bUpperCase){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param strValueProperty
	 * @param htItems
	 * @param bUpperCase
	 */
	public boolean GetSpecificStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, String strValueProperty, SortedList htItems, boolean bUpperCase){
		return null;
	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param strValueProperty
	 * @param ldListDictionary
	 * @param bUpperCase
	 */
	public boolean GetSpecificStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, String strValueProperty, ListDictionary ldListDictionary, boolean bUpperCase){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param serial
	 */
	public boolean GetSpecificSubSerializer(String strProperty, DefSerializer serial){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public boolean GetSpecificValueProperty(String strProperty, String strValue){
		return null;
	}

	/**
	 * 
	 * @param xeList
	 * @param strListItemProperty
	 * @param strProperty
	 * @param alItems
	 */
	protected boolean GetStringListFromAttribute(XmlElement xeList, String strListItemProperty, String strProperty, ArrayList alItems){
		return null;
	}

	/**
	 * 
	 * @param xeList
	 * @param strListItemProperty
	 * @param alItems
	 */
	protected boolean GetStringListFromInnerText(XmlElement xeList, String strListItemProperty, ArrayList alItems){
		return null;
	}

	/**
	 * 
	 * @param xeList
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param strValueProperty
	 * @param iDictionary
	 * @param bUpperCase
	 */
	protected Map GetStringPairListFromAttribute(XmlElement xeList, String strListItemProperty, String strKeyProperty, String strValueProperty, Map iDictionary, boolean bUpperCase){
		return null;
	}

	/**
	 * 
	 * @param xeList
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param htItems
	 * @param bUpperCase
	 */
	protected boolean GetStringPairListFromAttributeAndInnerText(XmlElement xeList, String strListItemProperty, String strKeyProperty, Hashtable htItems, boolean bUpperCase){
		return null;
	}

	/**
	 * 
	 * @param xeProperty
	 * @param serial
	 */
	protected boolean GetSubSerializer(XmlElement xeProperty, DefSerializer serial){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 */
	public boolean HasGeneralProperty(String strProperty){
		return null;
	}

	/**
	 * 
	 * @param strProperty
	 */
	public boolean HasSpecificProperty(String strProperty){
		return null;
	}

	public String Id(){
		return "";
	}

	/**
	 * 
	 * @param element
	 * @param defType
	 */
	public static String IdFromXml(XmlElement element, Type defType){
		return "";
	}

	public boolean IsDeserializer(){
		return null;
	}

	public boolean IsSerializer(){
		return null;
	}

	public String Name(){
		return "";
	}

	public boolean NextChild(){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public void RemoveFromCargo(String strName){

	}

	/**
	 * 
	 * @param strName
	 */
	public Object RetrieveCargo(String strName){
		return null;
	}

	protected String RetrieveGeneralComment(){
		return "";
	}

	/**
	 * 
	 * @param doc
	 * @param xeParent
	 * @param def
	 */
	protected void SerializeChild(XmlDocument doc, XmlElement xeParent, SerializableDef def){

	}

	/**
	 * 
	 * @param strXml
	 */
	public void SetAsDeserializer(String strXml){

	}

	/**
	 * 
	 * @param xr
	 */
	public void SetAsDeserializer(XmlReader xr){

	}

	/**
	 * 
	 * @param doc
	 * @param xeRoot
	 */
	public void SetAsDeserializer(XmlDocument doc, XmlElement xeRoot){

	}

	public void SetAsSerializer(){

	}

	/**
	 * 
	 * @param strValue
	 */
	public void SetCoreInnerXml(String strValue){

	}

	/**
	 * 
	 * @param collItems
	 * @param typeListItems
	 */
	public void SetCoreListProperty(List collItems, Type typeListItems){

	}

	/**
	 * 
	 * @param bValue
	 */
	public void SetCoreProperty(boolean bValue){

	}

	/**
	 * 
	 * @param dValue
	 */
	public void SetCoreProperty(double dValue){

	}

	/**
	 * 
	 * @param nValue
	 */
	public void SetCoreProperty(int nValue){

	}

	/**
	 * 
	 * @param strValue
	 */
	public void SetCoreProperty(String strValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param bValue
	 */
	public void SetCoreProperty(String strProperty, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param dValue
	 */
	public void SetCoreProperty(String strProperty, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param nValue
	 */
	public void SetCoreProperty(String strProperty, int nValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public void SetCoreProperty(String strProperty, String strValue){

	}

	/**
	 * 
	 * @param defChild
	 * @param typeItem
	 */
	public void SetGeneralChildProperty(SerializableDef defChild, Type typeItem){

	}

	/**
	 * 
	 * @param strValue
	 */
	protected void SetGeneralComment(String strValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public void SetGeneralInnerXml(String strProperty, String strValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param collItems
	 * @param typeListItems
	 */
	public void SetGeneralListProperty(String strProperty, List collItems, Type typeListItems){

	}

	/**
	 * 
	 * @param strProperty
	 * @param bValue
	 */
	public void SetGeneralProperty(String strProperty, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param dValue
	 */
	public void SetGeneralProperty(String strProperty, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param nValue
	 */
	public void SetGeneralProperty(String strProperty, int nValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public void SetGeneralProperty(String strProperty, String strValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param bValue
	 */
	public void SetGeneralProperty(String strProperty, String strSubProperty, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param dValue
	 */
	public void SetGeneralProperty(String strProperty, String strSubProperty, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param nValue
	 */
	public void SetGeneralProperty(String strProperty, String strSubProperty, int nValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param strValue
	 */
	public void SetGeneralProperty(String strProperty, String strSubProperty, String strValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public void SetGeneralRawProperty(String strProperty, String strValue){

	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param alItems
	 */
	public void SetGeneralStringList(String strListProperty, String strListItemProperty, List alItems){

	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strProperty
	 * @param alItems
	 */
	public void SetGeneralStringList(String strListProperty, String strListItemProperty, String strProperty, List alItems){

	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param htItems
	 */
	public void SetGeneralStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, Hashtable htItems){

	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param strValueProperty
	 * @param iDictionary
	 */
	public void SetGeneralStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, String strValueProperty, Map iDictionary){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public void SetGeneralValueProperty(String strProperty, String strValue){

	}

	/**
	 * 
	 * @param xeList
	 * @param collItems
	 * @param typeListItems
	 */
	protected void SetListProperty(XmlElement xeList, List collItems, Type typeListItems){

	}

	/**
	 * 
	 * @param defChild
	 * @param typeItem
	 */
	public void SetSpecificChildProperty(SerializableDef defChild, Type typeItem){

	}

	/**
	 * 
	 * @param strProperty
	 * @param bValue
	 */
	public void SetSpecificCoreProperty(String strProperty, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param dValue
	 */
	public void SetSpecificCoreProperty(String strProperty, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param nValue
	 */
	public void SetSpecificCoreProperty(String strProperty, int nValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public void SetSpecificCoreProperty(String strProperty, String strValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public void SetSpecificInnerXml(String strProperty, String strValue){

	}

	/**
	 * 
	 * @param collItems
	 * @param typeListItems
	 */
	public void SetSpecificListProperty(List collItems, Type typeListItems){

	}

	/**
	 * 
	 * @param strProperty
	 * @param collItems
	 * @param typeListItems
	 */
	public void SetSpecificListProperty(String strProperty, List collItems, Type typeListItems){

	}

	/**
	 * 
	 * @param strProperty
	 * @param bValue
	 */
	public void SetSpecificProperty(String strProperty, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param dValue
	 */
	public void SetSpecificProperty(String strProperty, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param nValue
	 */
	public void SetSpecificProperty(String strProperty, int nValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public void SetSpecificProperty(String strProperty, String strValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param bValue
	 */
	public void SetSpecificProperty(String strProperty, String strSubProperty, boolean bValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param dValue
	 */
	public void SetSpecificProperty(String strProperty, String strSubProperty, double dValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param nValue
	 */
	public void SetSpecificProperty(String strProperty, String strSubProperty, int nValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strSubProperty
	 * @param strValue
	 */
	public void SetSpecificProperty(String strProperty, String strSubProperty, String strValue){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public void SetSpecificRawProperty(String strProperty, String strValue){

	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param alItems
	 */
	public void SetSpecificStringList(String strListProperty, String strListItemProperty, ArrayList alItems){

	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strProperty
	 * @param alItems
	 */
	public void SetSpecificStringList(String strListProperty, String strListItemProperty, String strProperty, ArrayList alItems){

	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param htItems
	 */
	public void SetSpecificStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, Hashtable htItems){

	}

	/**
	 * 
	 * @param strListProperty
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param strValueProperty
	 * @param iDictionary
	 */
	public void SetSpecificStringPairList(String strListProperty, String strListItemProperty, String strKeyProperty, String strValueProperty, Map iDictionary){

	}

	/**
	 * 
	 * @param strProperty
	 * @param strValue
	 */
	public void SetSpecificValueProperty(String strProperty, String strValue){

	}

	/**
	 * 
	 * @param xeList
	 * @param strListItemProperty
	 * @param strProperty
	 * @param alItems
	 */
	protected void SetStringListForAttribute(XmlElement xeList, String strListItemProperty, String strProperty, List alItems){

	}

	/**
	 * 
	 * @param xeList
	 * @param strListItemProperty
	 * @param collItems
	 */
	protected void SetStringListForInnerText(XmlElement xeList, String strListItemProperty, List collItems){

	}

	/**
	 * 
	 * @param xeList
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param strValueProperty
	 * @param iDictionary
	 */
	protected void SetStringPairListForAttribute(XmlElement xeList, String strListItemProperty, String strKeyProperty, String strValueProperty, Map iDictionary){

	}

	/**
	 * 
	 * @param xeList
	 * @param strListItemProperty
	 * @param strKeyProperty
	 * @param collItems
	 */
	protected void SetStringPairListForAttributeAndInnerText(XmlElement xeList, String strListItemProperty, String strKeyProperty, List collItems){

	}

	public String SpecificPropertyRoot(){
		return "";
	}

	public int SubSerializerChildCount(){
		return 0;
	}

	public String ToXml(){
		return "";
	}

	/**
	 * 
	 * @param xw
	 */
	public void ToXmlWriter(XmlWriter xw){

	}

	public int Version(){
		return 0;
	}

}