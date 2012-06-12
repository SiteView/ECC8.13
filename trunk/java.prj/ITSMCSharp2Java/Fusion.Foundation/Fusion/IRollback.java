package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:54
 */
public interface IRollback {

	public RollbackInfo GetRollbackInfo();

	/**
	 * 
	 * @param ri
	 * @param ur
	 */
	public void Rollback(RollbackInfo ri, UpdateResult ur);

}