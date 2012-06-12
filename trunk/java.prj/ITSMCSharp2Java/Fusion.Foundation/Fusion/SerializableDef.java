package Fusion;
import Fusion.Foundation.CompareInfo;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:35:15
 */
public abstract class SerializableDef extends INameId {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:35:15
	 */
	private class Tags {

		private String Def = "Def";
		private String Details = "Details";
		private String Version = "Version";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getDef(){
			return Def;
		}

		public String getDetails(){
			return Details;
		}

		public String getVersion(){
			return Version;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDef(String newVal){
			Def = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDetails(String newVal){
			Details = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setVersion(String newVal){
			Version = newVal;
		}

	}

	private boolean m_bDefDirty = false;
	private boolean m_bEditMode = false;
	private MessageInfoList m_msgHolder = null;
	private int m_nVersion = 1;
	private String m_strId = "";
	private String m_strName = "";

	public SerializableDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param bWarning
	 * @param strResourceId
	 * @param strSource
	 * @param severity
	 */
	protected ErrorInfo AddMessage(boolean bWarning, String strResourceId, String strSource, ErrorSeverity severity){
		return null;
	}

	/**
	 * 
	 * @param bWarning
	 * @param strResourceId
	 * @param strSource
	 * @param severity
	 * @param parentDef
	 */
	protected ErrorInfo AddMessage(boolean bWarning, String strResourceId, String strSource, ErrorSeverity severity, IDefinition parentDef){
		return null;
	}

	/**
	 * 
	 * @param ds
	 */
	protected void AddSerializationCargo(DefSerializer ds){

	}

	/**
	 * 
	 * @param bWarning
	 * @param strSource
	 * @param severity
	 * @param strMsg
	 */
	public ErrorInfo AddValidationMessage(boolean bWarning, String strSource, ErrorSeverity severity, String strMsg){
		return null;
	}

	/**
	 * 
	 * @param bWarning
	 * @param strSource
	 * @param severity
	 * @param strMsg
	 * @param parentDef
	 */
	public ErrorInfo AddValidationMessage(boolean bWarning, String strSource, ErrorSeverity severity, String strMsg, IDefinition parentDef){
		return null;
	}

	public String AggregateClassName(){
		return "";
	}

	/**
	 * 
	 * @param strOriginal
	 * @param strFixed
	 * @param correction
	 */
	public static boolean CheckFieldRefForNamedReferenceCorrection(String strOriginal, String strFixed, NamedReferenceCorrection correction){
		return false;
	}

	/**
	 * 
	 * @param strOriginal
	 * @param strFixed
	 * @param correction
	 * @param strBusOb
	 * @param strField
	 * @param strRelationship
	 * @param strLinkField
	 * @param strJustCorrectOldBusOb
	 * @param strJustCorrectOldField
	 */
	public static boolean CheckFieldRefForNamedReferenceCorrection(String strOriginal, String strFixed, NamedReferenceCorrection correction, String strBusOb, String strField, String strRelationship, String strLinkField, String strJustCorrectOldBusOb, String strJustCorrectOldField){
		return false;
	}

	public static String ClassName(){
		return "";
	}

	public void ClearDefDirtyFlags(){

	}

	/**
	 * 
	 * @param defToCompare
	 * @param ci
	 */
	public void CompareContents(SerializableDef defToCompare, CompareInfo ci){

	}

	/**
	 * 
	 * @param strPropertyID
	 * @param objSource
	 * @param objTarget
	 * @param parentCompareInfo
	 */
	protected void CompareValueProperties(String strPropertyID, Object objSource, Object objTarget, CompareInfo parentCompareInfo){

	}

	public void ConfirmEditMode(){

	}

	/**
	 * 
	 * @param bMarkDirty
	 */
	protected void ConfirmEditMode(boolean bMarkDirty){

	}

	/**
	 * 
	 * @param def
	 */
	protected void CopyContents(SerializableDef def){

	}

	/**
	 * 
	 * @param def
	 * @param defOwner
	 */
	protected void CopyContents(SerializableDef def, SerializableDef defOwner){

	}

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 */
	public void CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect){

	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	public boolean EditMode(){
		return false;
	}

	public boolean Encrypted(){
		return false;
	}

	/**
	 * 
	 * @param strXml
	 */
	public void FromXml(String strXml){

	}

	/**
	 * 
	 * @param xr
	 */
	public void FromXml(XmlReader xr){

	}

	public boolean HasErrors(){
		return false;
	}

	public String Id(){
		return "";
	}

	public String IdKey(){
		return "";
	}

	public String InstanceClassName(){
		return "";
	}

	public boolean IsDefDirty(){
		return false;
	}

	public String KeyName(){
		return "";
	}

	public MessageInfoList MessageList(){
		return null;
	}

	public String Name(){
		return "";
	}

	public String NameKey(){
		return "";
	}

	/**
	 * 
	 * @param def
	 */
	public boolean ReportConflicts(IDefinition def){
		return false;
	}

	/**
	 * 
	 * @param plHolder
	 */
	public boolean ReportConflicts(PlaceHolder plHolder){
		return null;
	}

	protected boolean RequiresName(){
		return null;
	}

	protected boolean RequiresNameAndId(){
		return null;
	}

	public DefSerializer Serialize(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

	public String SerializeClassName(){
		return "";
	}

	public String SerializeGeneralPropertyRoot(){
		return "";
	}

	public String SerializeSpecificPropertyRoot(){
		return "";
	}

	protected boolean SerializeVersion(){
		return null;
	}

	public void SetDefDirty(){

	}

	/**
	 * 
	 * @param bDefDirty
	 */
	public void SetDefDirty(boolean bDefDirty){

	}

	public String ToString(){
		return "";
	}

	public String ToXml(){
		return "";
	}

	/**
	 * 
	 * @param xw
	 */
	public void ToXmlWriter(XmlTextWriter xw){

	}

	/**
	 * 
	 * @param parentDef
	 */
	protected boolean Validate(IDefinition parentDef){
		return null;
	}

	public int Version(){
		return 0;
	}

}