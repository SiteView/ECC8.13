package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:40
 */
public class QueryGroupDef extends ScopedDefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:40
	 */
	private class Tags {

		private String EditWithSearchBuilder = "EditWithSearchBuilder";
		private String Query = "Query";
		private String QueryGroup = "QueryGroup";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getEditWithSearchBuilder(){
			return EditWithSearchBuilder;
		}

		public String getQuery(){
			return Query;
		}

		public String getQueryGroup(){
			return QueryGroup;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setEditWithSearchBuilder(String newVal){
			EditWithSearchBuilder = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setQuery(String newVal){
			Query = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setQueryGroup(String newVal){
			QueryGroup = newVal;
		}

	}

	private boolean m_bEditWithSearchBuilder = false;
	private Fusion.FusionQuery m_qryFusion = null;
	private String m_strFusionQuery = "";
	private String TOKEN_VALUE = "Value=\"TOKEN\">";

	public QueryGroupDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public static String ClassName(){
		return "";
	}

	public IDefinition CloneForEdit(){
		return null;
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

	protected boolean DefinitionSupportsPerspective(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	/**
	 * 
	 * @param serial
	 * @param defParent
	 */
	public static SerializableDef DeserializeCreate(DefSerializer serial, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param strSubType
	 */
	public static IDefinition DeserializeCreateNewForEditing(String strSubType){
		return null;
	}

	public boolean EditWithSearchBuilder(){
		return null;
	}

	public Fusion.FusionQuery FusionQuery(){
		return null;
	}

	public String FusionQueryAsXml(){
		return "";
	}

	public String QueryGroupDefId(){
		return "";
	}

	protected boolean RequiresStorageTag(){
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

}