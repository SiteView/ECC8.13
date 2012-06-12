package Fusion.Api;

import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:44
 */
public class CompareWorker {

	private ArrayList m_alCompareInfoResults = null;
	private ArrayList m_alDefsWhereCompareOccured = new ArrayList();
	private boolean m_bDeepCompare = false;
	private IDefinition m_DefsToCheck[] = null;
	private PlaceHolder m_PlaceHoldersToCheck[] = null;
	private IProgressIndicator m_ProgressIndicator = null;
	private DefinitionLibrary m_SourceDefLib = null;
	private DefinitionLibrary m_TargetDefLib = null;
	private Thread m_workerThread = null;

	public CompareWorker(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param defLibSource
	 * @param defLibTarget
	 * @param progressIndicator
	 * @param bDoDeepCompare
	 */
	public CompareWorker(DefinitionLibrary defLibSource, DefinitionLibrary defLibTarget, IProgressIndicator progressIndicator, boolean bDoDeepCompare){

	}

	private void Compare(){

	}

	/**
	 * 
	 * @param ph
	 * @param strErrorMessage
	 */
	private ObjectCompareInfo CreateErrorObjectCompareInfo(PlaceHolder ph, String strErrorMessage){
		return null;
	}

	/**
	 * 
	 * @param ph
	 */
	private ObjectCompareInfo CreateObjectCompareInfoFromPlaceHolder(PlaceHolder ph){
		return null;
	}

	public ArrayList DefListWhereCompareOccured(){
		return null;
	}

	public IDefinition[] DefsToCheck(){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	private Object GetFusionObjectToCompare(IDefinition def){
		return null;
	}

	public DefinitionLibrary HeldSourceDefinitionLibrary(){
		return null;
	}

	public DefinitionLibrary HeldTargetDefinitionLibrary(){
		return null;
	}

	public PlaceHolder[] PlaceHoldersToCheck(){
		return null;
	}

	public ArrayList ResultCompareInfos(){
		return null;
	}

	public void StartCompare(){

	}

	public Thread WorkerThread(){
		return null;
	}

}