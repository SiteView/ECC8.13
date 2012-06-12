package Fusion.Foundation.VersionDefinition;
import java.util.ArrayList;

import Fusion.DefSerializer;
import Fusion.DefinitionObject;
import Fusion.SerializableDef;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 15:22:49
 */
public class VersionNodeDef extends DefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 15:22:49
	 */
	private class Tags {

		private String BusinessObjectName = "BusinessObjectName";
		private String RelationShipName = "RelationShipName";
		private String VersionNode = "VersionNode";
		private String VersionNodeDef = "VersionNodeDef";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getBusinessObjectName(){
			return BusinessObjectName;
		}

		public String getRelationShipName(){
			return RelationShipName;
		}

		public String getVersionNode(){
			return VersionNode;
		}

		public String getVersionNodeDef(){
			return VersionNodeDef;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBusinessObjectName(String newVal){
			BusinessObjectName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRelationShipName(String newVal){
			RelationShipName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setVersionNode(String newVal){
			VersionNode = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setVersionNodeDef(String newVal){
			VersionNodeDef = newVal;
		}

	}

	private ArrayList m_aChild;
	private String m_BusinessObjectName;
	private SerializableDef m_ParentDef;
	private String m_RelationShipName;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public VersionNodeDef(){

	}

	/**
	 * 
	 * @param parentDef
	 */
	public VersionNodeDef(SerializableDef parentDef){

	}

	/**
	 * 
	 * @param BusinessObjectName
	 * @param RelationShipName
	 * @param aChild
	 */
	public VersionNodeDef(String BusinessObjectName, String RelationShipName, ArrayList aChild){

	}

	/**
	 * 
	 * @param cnChild
	 */
	public void AddChildNode(VersionNodeDef cnChild){

	}

	public String BusinessObjectName(){
		return "";
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

	/**
	 * 
	 * @param defParent
	 */
	public static VersionNodeDef Create(SerializableDef defParent){
		return null;
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

	public boolean EditMode(){
		return false;
	}

	/**
	 * 
	 * @param businessObjectName
	 */
	public VersionNodeDef GetVersionNodeByBusinessObjectName(String businessObjectName){
		return null;
	}

	public ArrayList NodeDefs(){
		return null;
	}

	public SerializableDef ParentDef(){
		return null;
	}

	public VersionDef ParentVersionDef(){
		return null;
	}

	public String RelationShipName(){
		return "";
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