package Fusion.Foundation.VersionDefinition;
import java.util.ArrayList;
import java.util.List;

import Fusion.DefSerializer;
import Fusion.IDefinition;
import Fusion.ScopedDefinitionObject;
import Fusion.SerializableDef;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 15:22:47
 */
public class VersionDef extends ScopedDefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 15:22:47
	 */
	private class Tags {

		private String VersionDef = "VersionDef";
		private String VersionTree = "VersionTree";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getVersionDef(){
			return VersionDef;
		}

		public String getVersionTree(){
			return VersionTree;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setVersionDef(String newVal){
			VersionDef = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setVersionTree(String newVal){
			VersionTree = newVal;
		}

	}

	private ArrayList m_aChild = new ArrayList();

	public VersionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param cnChild
	 */
	public void AddChildNode(VersionNodeDef cnChild){

	}

	public String AggregateClassName(){
		return "";
	}

	public void AssignDefaultValues(){

	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param def
	 * @param defOwner
	 */
	protected void CopyContents(SerializableDef def, SerializableDef defOwner){

	}

	public static VersionDef Create(){
		return null;
	}

	protected IDefinition CreateCloneObject(){
		return null;
	}

	protected boolean DefinitionSupportsPerspective(){
		return false;
	}

	/**
	 * 
	 * @param cnChild
	 */
	public void DeleteChildNode(VersionNodeDef cnChild){

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

	public boolean EditMode(){
		return false;
	}

	public ArrayList NodeDefs(){
		return null;
	}

	protected void PostSerialize(){

	}

	protected void RegisterNotifications(){

	}

	protected boolean RequiresNameAndId(){
		return false;
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

}