package Fusion.Api;

import java.beans.PropertyDescriptor;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:32
 */
public final class BusinessObjectCollection extends CollectionBase implements ITypedList {

	private Fusion.Api.BusinessObjectDef m_busObDef;
	private List<String> m_collRecordIdIndex;
	private Fusion.Api.Relationship m_relationship;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public BusinessObjectCollection(){

	}

	/**
	 * 
	 * @param busObDef
	 */
	public BusinessObjectCollection(Fusion.Api.BusinessObjectDef busObDef){

	}

	/**
	 * 
	 * @param rel
	 */
	public BusinessObjectCollection(Fusion.Api.Relationship rel){

	}

	/**
	 * 
	 * @param busObDef
	 * @param collBusinessObjects
	 */
	public BusinessObjectCollection(Fusion.Api.BusinessObjectDef busObDef, List collBusinessObjects){

	}

	/**
	 * 
	 * @param value
	 */
	public int Add(Fusion.Api.BusinessObject value){
		return 0;
	}

	/**
	 * 
	 * @param c
	 */
	public void AddRange(List c){

	}

	public Fusion.Api.BusinessObjectDef BusinessObjectDefinition(){
		return null;
	}

	/**
	 * 
	 * @param value
	 */
	public boolean Contains(Fusion.Api.BusinessObject value){
		return false;
	}

	/**
	 * 
	 * @param value
	 */
	public boolean Contains(String value){
		return false;
	}

	/**
	 * 
	 * @param recId
	 */
	private Fusion.Api.BusinessObject GetBusinessObjectByRecId(String recId){
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
	 * @param value
	 */
	public int IndexOf(Fusion.Api.BusinessObject value){
		return 0;
	}

	/**
	 * 
	 * @param value
	 */
	public int IndexOf(String value){
		return 0;
	}

	/**
	 * 
	 * @param index
	 * @param value
	 */
	public void Insert(int index, Fusion.Api.BusinessObject value){

	}

	protected void OnClearComplete(){

	}

	/**
	 * 
	 * @param index
	 * @param value
	 */
	protected void OnInsertComplete(int index, Object value){

	}

	/**
	 * 
	 * @param index
	 * @param value
	 */
	protected void OnRemoveComplete(int index, Object value){

	}

	/**
	 * 
	 * @param index
	 * @param oldValue
	 * @param newValue
	 */
	protected void OnSetComplete(int index, Object oldValue, Object newValue){

	}

	/**
	 * 
	 * @param value
	 */
	protected void OnValidate(Object value){

	}

	/**
	 * 
	 * @param value
	 */
	public void Remove(Fusion.Api.BusinessObject value){

	}

	/**
	 * 
	 * @param value
	 */
	public void Remove(String value){

	}

	/**
	 * 
	 * @param recId
	 */
	public Fusion.Api.BusinessObject get(String recId){
		return null;
	}

	/**
	 * 
	 * @param index
	 */
	public Fusion.Api.BusinessObject get(int index){
		return null;
	}

}