package Fusion.Api.FusionUpgrade;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:57
 */
public class ThreadFinishArgs extends EventArgs {

	private ProgressStatus m_ProgressStatus;
	private String m_strError;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ThreadFinishArgs(){

	}

	/**
	 * 
	 * @param strError
	 * @param status
	 */
	public ThreadFinishArgs(String strError, ProgressStatus status){

	}

	public String ErrorMessage(){
		return "";
	}

	public ProgressStatus Status(){
		return null;
	}

}