package Fusion.Api;

import javax.sql.rowset.spi.XmlReader;
import javax.sql.rowset.spi.XmlWriter;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:00
 */
public class DefinitionSet extends DefinitionLibrary {

	public DefinitionSet(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public DefinitionSet(Object fusionObject){

	}

	public DefinitionSetEventHandler Added(){
		return null;
	}

	/**
	 * 
	 * @param fApi
	 * @param defBusOb
	 * @param strDataStore
	 * @param strTable
	 * @param svcSettings
	 */
	public IDefinition BuildExternalTableBusinessObject(IFusionApi fApi, IDefinition defBusOb, String strDataStore, String strTable, ISettings svcSettings){
		return null;
	}

	/**
	 * 
	 * @param fusionApi
	 */
	public static Fusion.Api.DefinitionSet CreateInstance(IFusionApi fusionApi){
		return null;
	}

	public DefinitionSetEventHandler Deleted(){
		return null;
	}

	public DefinitionSetEventHandler Edited(){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 * @param strPerspective
	 */
	public IDefinition GetDeletedMdrDefinitionObject(String strType, String strId, String strPerspective){
		return null;
	}

	public List GetListOfModifiedDefs(){
		return null;
	}

	/**
	 * 
	 * @param strType
	 */
	public List GetListOfModifiedDefs(String strType){
		return null;
	}

	/**
	 * 
	 * @param strDefinitionType
	 * @param strId
	 * @param strPerspective
	 */
	public PlaceHolder GetPlaceHolderForDefinitionById(String strDefinitionType, String strId, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 */
	public List GetPlaceHolderListByIdAndAllPerspectives(String strType, String strId){
		return null;
	}

	public boolean HasBusinessObjectChanges(){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param strId
	 * @param strPerspective
	 */
	public boolean HasDeletedMdrDefinitionObject(String strType, String strId, String strPerspective){
		return null;
	}

	/**
	 * 
	 * @param s
	 */
	public void Load(Stream s){

	}

	/**
	 * 
	 * @param reader
	 */
	public void Load(TextReader reader){

	}

	/**
	 * 
	 * @param strFileName
	 */
	public void Load(String strFileName){

	}

	/**
	 * 
	 * @param reader
	 */
	public void Load(XmlReader reader){

	}

	/**
	 * 
	 * @param strXml
	 */
	public void LoadXml(String strXml){

	}

	/**
	 * 
	 * @param def
	 */
	public void MarkDefinitionForDeletion(IDefinition def){

	}

	/**
	 * 
	 * @param e
	 */
	protected void OnAdded(DefinitionSetEventArgs e){

	}

	/**
	 * 
	 * @param e
	 */
	protected void OnDeleted(DefinitionSetEventArgs e){

	}

	/**
	 * 
	 * @param e
	 */
	protected void OnEdited(DefinitionSetEventArgs e){

	}

	/**
	 * 
	 * @param s
	 */
	public void Save(Stream s){

	}

	/**
	 * 
	 * @param writer
	 */
	public void Save(TextWriter writer){

	}

	/**
	 * 
	 * @param strFileName
	 */
	public void Save(String strFileName){

	}

	/**
	 * 
	 * @param writer
	 */
	public void Save(XmlWriter writer){

	}

	public String SaveXml(){
		return "";
	}

	/**
	 * 
	 * @param def
	 */
	public void UpdateDefinition(IDefinition def){

	}

	/**
	 * 
	 * @param valLevel
	 */
	public MessageInfoList Validate(ValidationLevel valLevel){
		return null;
	}

	/**
	 * 
	 * @param strType
	 * @param valLevel
	 */
	public MessageInfoList Validate(String strType, ValidationLevel valLevel){
		return null;
	}

	/**
	 * 
	 * @param defObj
	 */
	public MessageInfoList ValidateDefinition(Fusion.Api.DefinitionObject defObj){
		return null;
	}

	private Fusion.DefinitionTransformation.DefinitionSet WhoAmI(){
		return null;
	}

}