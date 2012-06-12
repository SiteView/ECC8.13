package ICSharpCode.SharpZipLib.BZip2;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:44
 */
public final class BZip2Constants extends Object {

	private static Int32 baseBlockSize;
	private static Int32 G_SIZE;
	private static Int32 MAX_ALPHA_SIZE;
	private static Int32 MAX_CODE_LEN;
	private static Int32 MAX_SELECTORS;
	private static Int32 N_GROUPS;
	private static Int32 N_ITERS;
	private static Int32 NUM_OVERSHOOT_BYTES;
	private static Int32 rNums[];
	private static Int32 RUNA;
	private static Int32 RUNB;



	public void finalize() throws Throwable {
		super.finalize();
	}

	private BZip2Constants(){

	}

	private BZip2Constants(){

	}

	public Int32 getbaseBlockSize(){
		return baseBlockSize;
	}

	public Int32 getG_SIZE(){
		return G_SIZE;
	}

	public Int32 getMAX_ALPHA_SIZE(){
		return MAX_ALPHA_SIZE;
	}

	public Int32 getMAX_CODE_LEN(){
		return MAX_CODE_LEN;
	}

	public Int32 getMAX_SELECTORS(){
		return MAX_SELECTORS;
	}

	public Int32 getN_GROUPS(){
		return N_GROUPS;
	}

	public Int32 getN_ITERS(){
		return N_ITERS;
	}

	public Int32 getNUM_OVERSHOOT_BYTES(){
		return NUM_OVERSHOOT_BYTES;
	}

	public Int32 getrNums(){
		return rNums;
	}

	public Int32 getRUNA(){
		return RUNA;
	}

	public Int32 getRUNB(){
		return RUNB;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setbaseBlockSize(Int32 newVal){
		baseBlockSize = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setG_SIZE(Int32 newVal){
		G_SIZE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMAX_ALPHA_SIZE(Int32 newVal){
		MAX_ALPHA_SIZE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMAX_CODE_LEN(Int32 newVal){
		MAX_CODE_LEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMAX_SELECTORS(Int32 newVal){
		MAX_SELECTORS = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setN_GROUPS(Int32 newVal){
		N_GROUPS = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setN_ITERS(Int32 newVal){
		N_ITERS = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNUM_OVERSHOOT_BYTES(Int32 newVal){
		NUM_OVERSHOOT_BYTES = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setrNums(Int32 newVal){
		rNums = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRUNA(Int32 newVal){
		RUNA = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRUNB(Int32 newVal){
		RUNB = newVal;
	}

}