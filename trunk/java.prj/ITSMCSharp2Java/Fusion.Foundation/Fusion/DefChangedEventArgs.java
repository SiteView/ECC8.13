package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:05
 */
public class DefChangedEventArgs extends EventArgs {

	private DefModifiedLevel m_modificationLevel = DefModifiedLevel.NoModification;

	public DefChangedEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param level
	 */
	public DefChangedEventArgs(DefModifiedLevel level){

	}

	public DefModifiedLevel Level(){
		return null;
	}

}