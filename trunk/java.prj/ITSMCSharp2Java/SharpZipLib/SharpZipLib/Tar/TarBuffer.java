package ICSharpCode.SharpZipLib.Tar;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:56
 */
public class TarBuffer extends Object {

	private Int32 blockFactor;
	private static Int32 BlockSize;
	private Int32 currentBlockIndex;
	private Int32 currentRecordIndex;
	private boolean debug;
	private static Int32 DefaultBlockFactor;
	private static Int32 DefaultRecordSize;
	private Stream inputStream;
	private Stream outputStream;
	private byte recordBuffer[];
	private Int32 recordSize;



	public void finalize() throws Throwable {
		super.finalize();
	}

	protected TarBuffer(){

	}

	private TarBuffer(){

	}

	public Int32 BlockFactor(){
		return 0;
	}

	public Void Close(){

	}

	/**
	 * 
	 * @param inputStream
	 */
	public static TarBuffer CreateInputTarBuffer(Stream inputStream){
		return null;
	}

	/**
	 * 
	 * @param inputStream
	 * @param blockFactor
	 */
	public static TarBuffer CreateInputTarBuffer(Stream inputStream, Int32 blockFactor){
		return null;
	}

	/**
	 * 
	 * @param outputStream
	 */
	public static TarBuffer CreateOutputTarBuffer(Stream outputStream){
		return null;
	}

	/**
	 * 
	 * @param outputStream
	 * @param blockFactor
	 */
	public static TarBuffer CreateOutputTarBuffer(Stream outputStream, Int32 blockFactor){
		return null;
	}

	private Void Flush(){

	}

	public Int32 GetBlockFactor(){
		return 0;
	}

	public Int32 getBlockSize(){
		return BlockSize;
	}

	public Int32 GetCurrentBlockNum(){
		return 0;
	}

	public Int32 GetCurrentRecordNum(){
		return 0;
	}

	public Int32 getDefaultBlockFactor(){
		return DefaultBlockFactor;
	}

	public Int32 getDefaultRecordSize(){
		return DefaultRecordSize;
	}

	public Int32 GetRecordSize(){
		return 0;
	}

	/**
	 * 
	 * @param blockFactor
	 */
	private Void Initialize(Int32 blockFactor){

	}

	/**
	 * 
	 * @param block
	 */
	public boolean IsEOFBlock(Byte[] block){
		return false;
	}

	public byte[] ReadBlock(){
		return 0;
	}

	private boolean ReadRecord(){
		return false;
	}

	public Int32 RecordSize(){
		return 0;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBlockSize(Int32 newVal){
		BlockSize = newVal;
	}

	/**
	 * 
	 * @param debug
	 */
	public Void SetDebug(boolean debug){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDefaultBlockFactor(Int32 newVal){
		DefaultBlockFactor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDefaultRecordSize(Int32 newVal){
		DefaultRecordSize = newVal;
	}

	public Void SkipBlock(){

	}

	/**
	 * 
	 * @param block
	 */
	public Void WriteBlock(Byte[] block){

	}

	/**
	 * 
	 * @param buf
	 * @param offset
	 */
	public Void WriteBlock(Byte[] buf, Int32 offset){

	}

	private Void WriteRecord(){

	}

}