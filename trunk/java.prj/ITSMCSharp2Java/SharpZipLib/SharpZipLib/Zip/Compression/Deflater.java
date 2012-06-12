package ICSharpCode.SharpZipLib.Zip.Compression;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:47
 */
public class Deflater extends Object {

	private static Int32 BEST_COMPRESSION;
	private static Int32 BEST_SPEED;
	private static Int32 BUSY_STATE;
	private static Int32 CLOSED_STATE;
	private static Int32 DEFAULT_COMPRESSION;
	private static Int32 DEFLATED;
	private DeflaterEngine engine;
	private static Int32 FINISHED_STATE;
	private static Int32 FINISHING_STATE;
	private static Int32 FLUSHING_STATE;
	private static Int32 INIT_STATE;
	private static Int32 IS_FINISHING;
	private static Int32 IS_FLUSHING;
	private static Int32 IS_SETDICT;
	private Int32 level;
	private static Int32 NO_COMPRESSION;
	private boolean noHeaderOrFooter;
	private DeflaterPending pending;
	private static Int32 SETDICT_STATE;
	private Int32 state;
	private Int64 totalOut;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public Deflater(){

	}

	/**
	 * 
	 * @param lvl
	 */
	public Deflater(Int32 lvl){

	}

	/**
	 * 
	 * @param level
	 * @param noHeaderOrFooter
	 */
	public Deflater(Int32 level, boolean noHeaderOrFooter){

	}

	private Deflater(){

	}

	public Int32 Adler(){
		return 0;
	}

	/**
	 * 
	 * @param output
	 */
	public Int32 Deflate(Byte[] output){
		return 0;
	}

	/**
	 * 
	 * @param output
	 * @param offset
	 * @param length
	 */
	public Int32 Deflate(Byte[] output, Int32 offset, Int32 length){
		return 0;
	}

	public Void Finish(){

	}

	public Void Flush(){

	}

	public Int32 getBEST_COMPRESSION(){
		return BEST_COMPRESSION;
	}

	public Int32 getBEST_SPEED(){
		return BEST_SPEED;
	}

	public Int32 getDEFAULT_COMPRESSION(){
		return DEFAULT_COMPRESSION;
	}

	public Int32 getDEFLATED(){
		return DEFLATED;
	}

	public Int32 GetLevel(){
		return 0;
	}

	public Int32 getNO_COMPRESSION(){
		return NO_COMPRESSION;
	}

	public boolean IsFinished(){
		return false;
	}

	public boolean IsNeedingInput(){
		return false;
	}

	public Void Reset(){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBEST_COMPRESSION(Int32 newVal){
		BEST_COMPRESSION = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBEST_SPEED(Int32 newVal){
		BEST_SPEED = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDEFAULT_COMPRESSION(Int32 newVal){
		DEFAULT_COMPRESSION = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDEFLATED(Int32 newVal){
		DEFLATED = newVal;
	}

	/**
	 * 
	 * @param dict
	 */
	public Void SetDictionary(Byte[] dict){

	}

	/**
	 * 
	 * @param dict
	 * @param offset
	 * @param length
	 */
	public Void SetDictionary(Byte[] dict, Int32 offset, Int32 length){

	}

	/**
	 * 
	 * @param input
	 */
	public Void SetInput(Byte[] input){

	}

	/**
	 * 
	 * @param input
	 * @param off
	 * @param len
	 */
	public Void SetInput(Byte[] input, Int32 off, Int32 len){

	}

	/**
	 * 
	 * @param lvl
	 */
	public Void SetLevel(Int32 lvl){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNO_COMPRESSION(Int32 newVal){
		NO_COMPRESSION = newVal;
	}

	/**
	 * 
	 * @param strategy
	 */
	public Void SetStrategy(DeflateStrategy strategy){

	}

	public Int32 TotalIn(){
		return 0;
	}

	public Int64 TotalOut(){
		return null;
	}

}