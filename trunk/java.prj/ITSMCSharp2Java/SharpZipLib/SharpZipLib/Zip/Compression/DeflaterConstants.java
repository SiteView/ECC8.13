package ICSharpCode.SharpZipLib.Zip.Compression;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:48
 */
public class DeflaterConstants extends Object {

	private static Int32 COMPR_FUNC[];
	private static boolean DEBUGGING;
	private static Int32 DEFAULT_MEM_LEVEL;
	private static Int32 DEFLATE_FAST;
	private static Int32 DEFLATE_SLOW;
	private static Int32 DEFLATE_STORED;
	private static Int32 DYN_TREES;
	private static Int32 GOOD_LENGTH[];
	private static Int32 HASH_BITS;
	private static Int32 HASH_MASK;
	private static Int32 HASH_SHIFT;
	private static Int32 HASH_SIZE;
	private static Int32 MAX_BLOCK_SIZE;
	private static Int32 MAX_CHAIN[];
	private static Int32 MAX_DIST;
	private static Int32 MAX_LAZY[];
	private static Int32 MAX_MATCH;
	private static Int32 MAX_WBITS;
	private static Int32 MIN_LOOKAHEAD;
	private static Int32 MIN_MATCH;
	private static Int32 NICE_LENGTH[];
	private static Int32 PENDING_BUF_SIZE;
	private static Int32 PRESET_DICT;
	private static Int32 STATIC_TREES;
	private static Int32 STORED_BLOCK;
	private static Int32 WMASK;
	private static Int32 WSIZE;



	public void finalize() throws Throwable {
		super.finalize();
	}

	private DeflaterConstants(){

	}

	public DeflaterConstants(){

	}

	public Int32 getCOMPR_FUNC(){
		return COMPR_FUNC;
	}

	public boolean getDEBUGGING(){
		return DEBUGGING;
	}

	public Int32 getDEFAULT_MEM_LEVEL(){
		return DEFAULT_MEM_LEVEL;
	}

	public Int32 getDEFLATE_FAST(){
		return DEFLATE_FAST;
	}

	public Int32 getDEFLATE_SLOW(){
		return DEFLATE_SLOW;
	}

	public Int32 getDEFLATE_STORED(){
		return DEFLATE_STORED;
	}

	public Int32 getDYN_TREES(){
		return DYN_TREES;
	}

	public Int32 getGOOD_LENGTH(){
		return GOOD_LENGTH;
	}

	public Int32 getHASH_BITS(){
		return HASH_BITS;
	}

	public Int32 getHASH_MASK(){
		return HASH_MASK;
	}

	public Int32 getHASH_SHIFT(){
		return HASH_SHIFT;
	}

	public Int32 getHASH_SIZE(){
		return HASH_SIZE;
	}

	public Int32 getMAX_BLOCK_SIZE(){
		return MAX_BLOCK_SIZE;
	}

	public Int32 getMAX_CHAIN(){
		return MAX_CHAIN;
	}

	public Int32 getMAX_DIST(){
		return MAX_DIST;
	}

	public Int32 getMAX_LAZY(){
		return MAX_LAZY;
	}

	public Int32 getMAX_MATCH(){
		return MAX_MATCH;
	}

	public Int32 getMAX_WBITS(){
		return MAX_WBITS;
	}

	public Int32 getMIN_LOOKAHEAD(){
		return MIN_LOOKAHEAD;
	}

	public Int32 getMIN_MATCH(){
		return MIN_MATCH;
	}

	public Int32 getNICE_LENGTH(){
		return NICE_LENGTH;
	}

	public Int32 getPENDING_BUF_SIZE(){
		return PENDING_BUF_SIZE;
	}

	public Int32 getPRESET_DICT(){
		return PRESET_DICT;
	}

	public Int32 getSTATIC_TREES(){
		return STATIC_TREES;
	}

	public Int32 getSTORED_BLOCK(){
		return STORED_BLOCK;
	}

	public Int32 getWMASK(){
		return WMASK;
	}

	public Int32 getWSIZE(){
		return WSIZE;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCOMPR_FUNC(Int32 newVal){
		COMPR_FUNC = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDEBUGGING(boolean newVal){
		DEBUGGING = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDEFAULT_MEM_LEVEL(Int32 newVal){
		DEFAULT_MEM_LEVEL = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDEFLATE_FAST(Int32 newVal){
		DEFLATE_FAST = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDEFLATE_SLOW(Int32 newVal){
		DEFLATE_SLOW = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDEFLATE_STORED(Int32 newVal){
		DEFLATE_STORED = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDYN_TREES(Int32 newVal){
		DYN_TREES = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGOOD_LENGTH(Int32 newVal){
		GOOD_LENGTH = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setHASH_BITS(Int32 newVal){
		HASH_BITS = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setHASH_MASK(Int32 newVal){
		HASH_MASK = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setHASH_SHIFT(Int32 newVal){
		HASH_SHIFT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setHASH_SIZE(Int32 newVal){
		HASH_SIZE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMAX_BLOCK_SIZE(Int32 newVal){
		MAX_BLOCK_SIZE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMAX_CHAIN(Int32 newVal){
		MAX_CHAIN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMAX_DIST(Int32 newVal){
		MAX_DIST = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMAX_LAZY(Int32 newVal){
		MAX_LAZY = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMAX_MATCH(Int32 newVal){
		MAX_MATCH = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMAX_WBITS(Int32 newVal){
		MAX_WBITS = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMIN_LOOKAHEAD(Int32 newVal){
		MIN_LOOKAHEAD = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMIN_MATCH(Int32 newVal){
		MIN_MATCH = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNICE_LENGTH(Int32 newVal){
		NICE_LENGTH = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPENDING_BUF_SIZE(Int32 newVal){
		PENDING_BUF_SIZE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPRESET_DICT(Int32 newVal){
		PRESET_DICT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSTATIC_TREES(Int32 newVal){
		STATIC_TREES = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSTORED_BLOCK(Int32 newVal){
		STORED_BLOCK = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setWMASK(Int32 newVal){
		WMASK = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setWSIZE(Int32 newVal){
		WSIZE = newVal;
	}

}