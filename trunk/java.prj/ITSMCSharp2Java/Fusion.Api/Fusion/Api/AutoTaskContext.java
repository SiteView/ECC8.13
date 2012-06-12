package Fusion.Api;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:28
 */
public class AutoTaskContext extends TagContext {

	private String Context = "Context";
	private ArrayList m_aDisposableObjects;
	private ArrayList m_aExposedObjects;
	private BusinessObjectCollection m_affectedBusinessObjects;
	private boolean m_bSaveAllObjects;
	private Fusion.AutoTaskDef m_defAutoTask;
	private ArrayList m_displayObjects;
	private ExecutionStage m_eStage;
	private ArrayList m_formActions;
	private AutoTaskContext m_parentContext;

	public AutoTaskContext(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionApi
	 * @param busOb
	 * @param interaction
	 */
	public AutoTaskContext(IFusionApi fusionApi, BusinessObject busOb, IUIInteraction interaction){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param collBusObs
	 * @param interaction
	 */
	public AutoTaskContext(IFusionApi fusionApi, List collBusObs, IUIInteraction interaction){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param busOb
	 * @param interaction
	 * @param cultureInfo
	 */
	public AutoTaskContext(IFusionApi fusionApi, BusinessObject busOb, IUIInteraction interaction, CultureInfo cultureInfo){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param library
	 * @param defAutoTask
	 * @param defBusOb
	 */
	public AutoTaskContext(IFusionApi fusionApi, DefinitionLibrary library, Fusion.AutoTaskDef defAutoTask, BusinessObjectDef defBusOb){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param virtualKeyList
	 * @param busOb
	 * @param interaction
	 */
	public AutoTaskContext(IFusionApi fusionApi, IVirtualKeyList virtualKeyList, BusinessObject busOb, IUIInteraction interaction){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param collBusObs
	 * @param interaction
	 * @param cultureInfo
	 */
	public AutoTaskContext(IFusionApi fusionApi, List collBusObs, IUIInteraction interaction, CultureInfo cultureInfo){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param library
	 * @param defAutoTask
	 * @param defBusOb
	 * @param cultureInfo
	 */
	public AutoTaskContext(IFusionApi fusionApi, DefinitionLibrary library, Fusion.AutoTaskDef defAutoTask, BusinessObjectDef defBusOb, CultureInfo cultureInfo){

	}

	/**
	 * 
	 * @param fusionApi
	 * @param virtualKeyList
	 * @param busOb
	 * @param interaction
	 * @param cultureInfo
	 */
	public AutoTaskContext(IFusionApi fusionApi, IVirtualKeyList virtualKeyList, BusinessObject busOb, IUIInteraction interaction, CultureInfo cultureInfo){

	}

	/**
	 * 
	 * @param busOb
	 */
	public void AddAffectedObject(BusinessObject busOb){

	}

	/**
	 * 
	 * @param busOb
	 * @param bInNewWindow
	 */
	public void AddDisplayObject(BusinessObject busOb, boolean bInNewWindow){

	}

	/**
	 * 
	 * @param type
	 * @param detail
	 * @param busObId
	 * @param busObName
	 * @param changeDisplayOption
	 */
	public void AddFormAction(String type, String detail, String busObId, String busObName, String changeDisplayOption){

	}

	/**
	 * 
	 * @param disposeOb
	 */
	public void AddRunTimeDisposableObject(IDisposable disposeOb){

	}

	/**
	 * 
	 * @param expOb
	 */
	public void AddRunTimeExposedObject(ExposedObject expOb){

	}

	public BusinessObjectCollection AffectedObjects(){
		return null;
	}

	public Fusion.AutoTaskDef AutoTaskDef(){
		return null;
	}

	public void CleanUpRunTimeDisposableObjects(){

	}

	public ArrayList DisplayObjects(){
		return null;
	}

	public ArrayList FormActions(){
		return null;
	}

	protected List GetAdditionalExposedTags(){
		return null;
	}

	public String getContext(){
		return Context;
	}

	public List GetDesignTimeActionsThatConsumeTheContextBusinessObject(){
		return null;
	}

	/**
	 * 
	 * @param expOb
	 */
	public List GetDesignTimeActionsThatConsumeTheExposedObject(ExposedObject expOb){
		return null;
	}

	public List GetDesignTimeActionsThatHaveFieldTags(){
		return null;
	}

	public List GetDesignTimeExposedObjects(){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	public List GetExposedTags(Fusion.AutoTaskDef def){
		return null;
	}

	/**
	 * 
	 * @param aExpTags
	 * @param aActionDefs
	 */
	private boolean GetExposedTags(IList aExpTags, IList aActionDefs){
		return false;
	}

	public List GetRunTimeExposedObjects(){
		return null;
	}

	private void InitializeRunTimeExposedObjects(){

	}

	public AutoTaskContext ParentContext(){
		return null;
	}

	public boolean SaveAllObjects(){
		return false;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setContext(String newVal){
		Context = newVal;
	}

	public ExecutionStage Stage(){
		return null;
	}

}