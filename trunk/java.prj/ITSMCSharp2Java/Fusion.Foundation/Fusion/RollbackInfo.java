package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:50
 */
public class RollbackInfo {

	private boolean m_bDirty;
	private boolean m_bScuffed;
	private Object m_oValue;
	private IRollback m_RollbackTarget;



	public void finalize() throws Throwable {

	}

	public RollbackInfo(){

	}

	/**
	 * 
	 * @param target
	 * @param oValue
	 * @param bDirty
	 * @param bScuffed
	 */
	public RollbackInfo(IRollback target, Object oValue, boolean bDirty, boolean bScuffed){

	}

	public boolean Dirty(){
		return null;
	}

	public boolean Scuffed(){
		return null;
	}

	public IRollback Target(){
		return null;
	}

	public Object TargetValue(){
		return null;
	}

}