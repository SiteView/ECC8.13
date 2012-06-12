package Fusion;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:38
 */
public abstract class ActionDef extends DefinitionObject {

	private DefinitionObject m_defParent;

	public ActionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public abstract String ActionItem();

	/**
	 * 
	 * @param match
	 * @param promptDefs
	 */
	private void AddPromptDef(Match match, List promptDefs){

	}

	public boolean ConsumesContextBusinessObject(){
		return false;
	}

	/**
	 * 
	 * @param expOb
	 */
	public boolean ConsumesExposedObject(ExposedObject expOb){
		return false;
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
	 * @param strAssociatedBusOb
	 */
	public abstract boolean CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect, String strAssociatedBusOb);

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 * @param strAssociatedBusOb
	 * @param strValue
	 */
	protected static boolean CorrectNamedReferenceInTags(NamedReferenceCorrection correction, boolean bJustCollect, String strAssociatedBusOb, String strValue){
		return false;
	}

	/**
	 * 
	 * @param strCategory
	 */
	private static ActionDef CreateFromCategory(String strCategory){
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
	 * @param strCategory
	 */
	public static IDefinition DeserializeCreateNewForEditing(String strCategory){
		return null;
	}

	/**
	 * 
	 * @param list
	 */
	public void GatherPromptDefs(List list){

	}

	/**
	 * 
	 * @param strTags
	 * @param list
	 */
	protected void GatherPromptDefsFromString(String strTags, List list){

	}

	public List GetActionsThatConsumeTheContextBusinessObject(){
		return null;
	}

	/**
	 * 
	 * @param expOb
	 */
	public List GetActionsThatConsumeTheExposedObject(ExposedObject expOb){
		return null;
	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public List GetActionsThatHaveTagsContainingTagCategory(String strTagCategoryName){
		return null;
	}

	public List GetExposedObjects(){
		return null;
	}

	/**
	 * 
	 * @param strTagCategoryName
	 */
	public abstract boolean HasTagsContainingTagCategory(String strTagCategoryName);

	/**
	 * 
	 * @param strValue
	 * @param strTagCategoryName
	 */
	protected static boolean HasTagsContainingTagCategory(String strValue, String strTagCategoryName){
		return false;
	}

	/**
	 * 
	 * @param strValue
	 * @param strTagCategoryName
	 * @param strTagSubCategoryName
	 */
	protected static boolean HasTagsContainingTagCategoryAndSubCategory(String strValue, String strTagCategoryName, String strTagSubCategoryName){
		return false;
	}

	/**
	 * 
	 * @param strName
	 * @param strId
	 */
	public boolean IsActionNameUnique(String strName, String strId){
		return false;
	}

	public DefinitionObject Parent(){
		return null;
	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

}