package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:51
 */
public interface IModifyConstraints {

	/**
	 * 
	 * @param constraint
	 */
	public int AddConstraint(ConstraintDef constraint);

	public int ConstraintCount();

	public List Constraints();

	public void RemoveAllConstraints();

	/**
	 * 
	 * @param constraint
	 */
	public void RemoveConstraint(ConstraintDef constraint);

	/**
	 * 
	 * @param nIndex
	 */
	public void RemoveConstraintAt(int nIndex);

	/**
	 * 
	 * @param nIndex
	 */
	public ConstraintDef this(int nIndex);

}