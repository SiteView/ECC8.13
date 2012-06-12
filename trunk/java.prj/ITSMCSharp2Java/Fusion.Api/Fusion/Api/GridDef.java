package Fusion.Api;

import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:43
 */
public class GridDef extends BllDefinitionObject {

	public GridDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public GridDef(Object fusionObject){

	}

	/**
	 * 
	 * @param cdef
	 */
	public int AddColumnDef(Fusion.Api.ColumnDef cdef){
		return 0;
	}

	/**
	 * 
	 * @param cdef
	 * @param nNdx
	 */
	public int AddColumnDefAt(Fusion.Api.ColumnDef cdef, int nNdx){
		return 0;
	}

	public String AutoSizeColumnDefID(){
		return "";
	}

	public int AutoSizeColumnIndex(){
		return 0;
	}

	public String BaseObject(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public List ColumnDefs(){
		return null;
	}

	public List ColumnNames(){
		return null;
	}

	public Fusion.Api.ColumnDef CreateColumn(){
		return null;
	}

	public Fusion.Api.ColumnDef CreateColumnDef(){
		return null;
	}

	public String DefaultFontKey(){
		return "";
	}

	public FontSource DefaultFontSource(){
		return null;
	}

	public ArrayList DefaultGroupBy(){
		return null;
	}

	public ArrayList DefaultSort(){
		return null;
	}

	public boolean EditableGrid(){
		return null;
	}

	public System.Drawing.Font Font(){
		return null;
	}

	public Size FullSize(){
		return null;
	}

	/**
	 * 
	 * @param sID
	 */
	public Fusion.Api.ColumnDef GetColumnDef(String sID){
		return null;
	}

	/**
	 * 
	 * @param index
	 */
	public Fusion.Api.ColumnDef GetColumnDefAt(int index){
		return null;
	}

	/**
	 * 
	 * @param sQualifiedName
	 */
	public Fusion.Api.ColumnDef GetColumnDefByField(String sQualifiedName){
		return null;
	}

	/**
	 * 
	 * @param sName
	 */
	public Fusion.Api.ColumnDef GetColumnDefByQualifiedName(String sName){
		return null;
	}

	/**
	 * 
	 * @param busObDef
	 */
	public FieldDef GetGridRowColorFieldDef(BusinessObjectDef busObDef){
		return null;
	}

	/**
	 * 
	 * @param busObDef
	 */
	public FieldDef GetGridRowFontFieldDef(BusinessObjectDef busObDef){
		return null;
	}

	/**
	 * 
	 * @param index
	 */
	public String GetGroupByColumnName(int index){
		return "";
	}

	/**
	 * 
	 * @param iFusionApi
	 * @param strSettingId
	 */
	public List GetRequestedFields(IFusionApi iFusionApi, String strSettingId){
		return null;
	}

	/**
	 * 
	 * @param busObDef
	 * @param alFields
	 */
	private ArrayList GetRequestedFieldsFromGridDef(BusinessObjectDef busObDef, ArrayList alFields){
		return null;
	}

	/**
	 * 
	 * @param gridColumnSettings
	 * @param busObDef
	 * @param alFields
	 */
	private ArrayList GetRequestedFieldsFromSettings(List gridColumnSettings, BusinessObjectDef busObDef, ArrayList alFields){
		return null;
	}

	/**
	 * 
	 * @param index
	 */
	public String GetSortColumnName(int index){
		return "";
	}

	/**
	 * 
	 * @param index
	 */
	public boolean IsSortColumnAsc(int index){
		return null;
	}

	/**
	 * 
	 * @param strColName
	 */
	public boolean IsSortColumnAsc(String strColName){
		return null;
	}

	/**
	 * 
	 * @param cDef
	 * @param iNewPos
	 */
	public void MoveColumnDef(Fusion.Api.ColumnDef cDef, int iNewPos){

	}

	public String RelationshipName(){
		return "";
	}

	public void RemoveAllColumnDefs(){

	}

	/**
	 * 
	 * @param cdef
	 */
	public void RemoveColumnDef(Fusion.Api.ColumnDef cdef){

	}

	/**
	 * 
	 * @param nIndex
	 */
	public void RemoveColumnDefAt(int nIndex){

	}

	public String RowBackColor(){
		return "";
	}

	public Fusion.Api.RuleDef RowBackColorRule(){
		return null;
	}

	public String RowBorderColor(){
		return "";
	}

	public Fusion.Api.RuleDef RowBorderColorRule(){
		return null;
	}

	public String RowImage(){
		return "";
	}

	public Fusion.Api.RuleDef RowImageRule(){
		return null;
	}

	public String RowTextColor(){
		return "";
	}

	public Fusion.Api.RuleDef RowTextColorRule(){
		return null;
	}

	private Fusion.Presentation.GridDef WhoAmI(){
		return null;
	}

}