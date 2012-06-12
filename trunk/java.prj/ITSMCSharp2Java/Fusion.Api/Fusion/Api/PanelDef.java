package Fusion.Api;

import java.awt.Font;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:09
 */
public class PanelDef extends BllDefinitionObject {

	private ArrayList m_aControlDefs;

	public PanelDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public PanelDef(Object fusionObject){

	}

	/**
	 * 
	 * @param controlDef
	 */
	public int AddControlDef(Fusion.Api.ControlDef controlDef){
		return 0;
	}

	/**
	 * 
	 * @param groupDef
	 */
	public int AddGroupDef(Fusion.Api.GroupDef groupDef){
		return 0;
	}

	public Fusion.Api.BackgroundDef BackgroundDef(){
		return null;
	}

	public String BaseObject(){
		return "";
	}

	public Size CalculateOptimiumSize(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public List ControlDefs(){
		return null;
	}

	/**
	 * 
	 * @param api
	 * @param strXml
	 */
	public static Fusion.Api.PanelDef Create(IFusionApi api, String strXml){
		return null;
	}

	/**
	 * 
	 * @param bod
	 */
	public void CreateFromBusObDef(Fusion.Api.BusinessObjectDef bod){

	}

	public Font DefaultFont(){
		return null;
	}

	public String DefaultFontKey(){
		return "";
	}

	public FontSource DefaultFontSource(){
		return null;
	}

	public int ExtendedStartPoint(){
		return 0;
	}

	public Size FullSize(){
		return null;
	}

	/**
	 * 
	 * @param strID
	 */
	public Fusion.Api.ControlDef GetControlById(String strID){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.ControlDef GetControlDefByName(String strName){
		return null;
	}

	public List GroupDefs(){
		return null;
	}

	public boolean IsBrief(){
		return false;
	}

	public boolean LoadFormInExpandedViewMode(){
		return false;
	}

	/**
	 * 
	 * @param cDef
	 * @param iNdx
	 */
	public void MoveControlDefTo(Fusion.Api.ControlDef cDef, int iNdx){

	}

	public String RelationshipName(){
		return "";
	}

	public void RemoveAllControlDefs(){

	}

	public void RemoveAllGroupDefs(){

	}

	/**
	 * 
	 * @param controlDef
	 */
	public void RemoveControlDef(Fusion.Api.ControlDef controlDef){

	}

	/**
	 * 
	 * @param nIndex
	 */
	public void RemoveControlDefAt(int nIndex){

	}

	/**
	 * 
	 * @param groupDef
	 */
	public void RemoveGroupDef(Fusion.Api.GroupDef groupDef){

	}

	/**
	 * 
	 * @param nIndex
	 */
	public void RemoveGroupDefAt(int nIndex){

	}

	/**
	 * 
	 * @param bod
	 */
	public void SimpleCreateBrief(Fusion.Api.BusinessObjectDef bod){

	}

	/**
	 * 
	 * @param bod
	 */
	public void SimpleCreateForm(Fusion.Api.BusinessObjectDef bod){

	}

	private Fusion.Presentation.PanelDef WhoAmI(){
		return null;
	}

}