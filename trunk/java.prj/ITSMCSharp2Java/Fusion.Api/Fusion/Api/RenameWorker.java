package Fusion.Api;

import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:22
 */
public class RenameWorker {

	private ArrayList m_alDefsWhereRenameOccured;
	private NamedReferenceCorrection m_arNamedReferenceCorrection[];
	private boolean m_bJustCollect;
	private IDefinition m_Def;
	private DefinitionLibrary m_DefLib;
	private PlaceHolder m_PlaceHoldersToCheck[];
	private IProgressIndicator m_ProgressIndicator;
	private Thread m_workerThread;

	public RenameWorker(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param defLib
	 * @param nrcAr
	 * @param def
	 * @param progressIndicator
	 */
	public RenameWorker(DefinitionLibrary defLib, NamedReferenceCorrection[] nrcAr, IDefinition def, IProgressIndicator progressIndicator){

	}

	/**
	 * 
	 * @param defLib
	 * @param nrcAr
	 * @param def
	 * @param progressIndicator
	 * @param bJustCollect
	 */
	public RenameWorker(DefinitionLibrary defLib, NamedReferenceCorrection[] nrcAr, IDefinition def, IProgressIndicator progressIndicator, boolean bJustCollect){

	}

	public ArrayList DefListWhereRenameOccured(){
		return null;
	}

	private ArrayList GetPlaceHolderForRename(){
		return null;
	}

	private ArrayList GetPlaceHoldersForNameChange(){
		return null;
	}

	private ArrayList GetPlaceHoldersForStorageNameChange(){
		return null;
	}

	public DefinitionLibrary HeldDefinitionLibrary(){
		return null;
	}

	public NamedReferenceCorrection[] HeldNamedReferenceCorrectionArray(){
		return null;
	}

	public boolean JustCollect(){
		return null;
	}

	public PlaceHolder[] PlaceHoldersToCheck(){
		return null;
	}

	private void Rename(){

	}

	public void StartRename(){

	}

	public Thread WorkerThread(){
		return null;
	}

}