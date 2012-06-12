package Fusion.Api;

import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:43:56
 */
public abstract class DefinitionObject extends FusionAggregate implements IDefinition {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:43:56
	 */
	public class CommonMessageTags {

		private String DefRights_AllowChangeDatabasePropertiesId = "DefRights.AllowChangeDatabaseProperties";
		private String DefRights_AllowChangeId = "DefRights.AllowChange";

		public CommonMessageTags(){

		}

		public void finalize() throws Throwable {

		}

		public String getDefRights_AllowChangeDatabasePropertiesId(){
			return DefRights_AllowChangeDatabasePropertiesId;
		}

		public String getDefRights_AllowChangeId(){
			return DefRights_AllowChangeId;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDefRights_AllowChangeDatabasePropertiesId(String newVal){
			DefRights_AllowChangeDatabasePropertiesId = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDefRights_AllowChangeId(String newVal){
			DefRights_AllowChangeId = newVal;
		}

	}



	public void finalize() throws Throwable {
		super.finalize();
	}

	public DefinitionObject(){

	}

	/**
	 * 
	 * @param fusionObject
	 */
	public DefinitionObject(Object fusionObject){

	}

	/**
	 * 
	 * @param strName
	 * @param strValue
	 */
	public void AddAnnotation(String strName, String strValue){

	}

	public String Alias(){
		return "";
	}

	public boolean AllowDefRemoval(){
		return false;
	}

	public Map Annotations(){
		return null;
	}

	public void ApplyEdits(){

	}

	public void AssignIdIfRequired(){

	}

	public String AssociatedImage(){
		return "";
	}

	public boolean CanEdit(){
		return false;
	}

	public String CategoryAsString(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param Name
	 */
	public void ClearCargo(String Name){

	}

	public IDefinition Clone(){
		return null;
	}

	public IDefinition CloneForCopy(){
		return null;
	}

	public IDefinition CloneForEdit(){
		return null;
	}

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 */
	public void CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect){

	}

	public String DefinitionType(){
		return "";
	}

	public Fusion.Api.DefRights DefRights(){
		return null;
	}

	public String Description(){
		return "";
	}

	public boolean EditMode(){
		return false;
	}

	public String Flags(){
		return "";
	}

	public String Folder(){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public String GetAnnotationValue(String strName){
		return "";
	}

	/**
	 * 
	 * @param strName
	 * @param defaultValue
	 */
	public int GetAnnotationValueAsInt(String strName, int defaultValue){
		return 0;
	}

	/**
	 * 
	 * @param Name
	 */
	public Object GetCargo(String Name){
		return null;
	}

	/**
	 * 
	 * @param Name
	 */
	public String GetCargoAsString(String Name){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public boolean HasAnnotation(String strName){
		return false;
	}

	public String Id(){
		return "";
	}

	public String InstanceClassName(){
		return "";
	}

	public boolean IsDefDirty(){
		return false;
	}

	/**
	 * 
	 * @param strId
	 */
	public boolean IsMatchingId(String strId){
		return false;
	}

	public String LinkedTo(){
		return "";
	}

	public String Name(){
		return "";
	}

	public String OriginalName(){
		return "";
	}

	public Fusion.Xml.Scope OriginalScope(){
		return null;
	}

	public String OriginalScopeOwner(){
		return "";
	}

	public String Perspective(){
		return "";
	}

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 */
	public void ReconcileScope(Fusion.Xml.Scope scopeType, String strScopeOwner){

	}

	/**
	 * 
	 * @param strXML
	 */
	public void RedefineFromXml(String strXML){

	}

	/**
	 * 
	 * @param strName
	 */
	public void RemoveAnnotation(String strName){

	}

	public Fusion.Xml.Scope Scope(){
		return null;
	}

	public String ScopeOwner(){
		return "";
	}

	/**
	 * 
	 * @param Name
	 * @param Cargo
	 */
	public void SetCargo(String Name, Object Cargo){

	}

	public String StorageName(){
		return "";
	}

	public String StorageSource(){
		return "";
	}

	public boolean Stored(){
		return false;
	}

	public String ToString(){
		return "";
	}

	public String ToXml(){
		return "";
	}

	public int Version(){
		return 0;
	}

	public String Visualize(){
		return "";
	}

	private Fusion.DefinitionObject WhoAmI(){
		return null;
	}

}

