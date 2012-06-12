package ICSharpCode.SharpZipLib.Tar;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:59
 */
public class TarOutputStream extends Stream {

	protected byte assemBuf[];
	protected Int32 assemLen;
	protected byte blockBuf[];
	protected TarBuffer buffer;
	protected Int32 currBytes;
	protected Int64 currSize;
	protected boolean debug;
	protected Stream outputStream;

	public TarOutputStream(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param outputStream
	 */
	public TarOutputStream(Stream outputStream){

	}

	/**
	 * 
	 * @param outputStream
	 * @param blockFactor
	 */
	public TarOutputStream(Stream outputStream, Int32 blockFactor){

	}

	public boolean CanRead(){
		return false;
	}

	public boolean CanSeek(){
		return false;
	}

	public boolean CanWrite(){
		return false;
	}

	public Void Close(){

	}

	public Void CloseEntry(){

	}

	public Void Finish(){

	}

	public Void Flush(){

	}

	public Int32 GetRecordSize(){
		return 0;
	}

	public Int64 Length(){
		return null;
	}

	public Int64 Position(){
		return null;
	}

	/**
	 * 
	 * @param entry
	 */
	public Void PutNextEntry(TarEntry entry){

	}

	/**
	 * 
	 * @param b
	 * @param off
	 * @param len
	 */
	public Int32 Read(Byte[] b, Int32 off, Int32 len){
		return 0;
	}

	public Int32 ReadByte(){
		return 0;
	}

	/**
	 * 
	 * @param offset
	 * @param origin
	 */
	public Int64 Seek(Int64 offset, SeekOrigin origin){
		return null;
	}

	/**
	 * 
	 * @param debug
	 */
	public Void SetBufferDebug(boolean debug){

	}

	/**
	 * 
	 * @param debugFlag
	 */
	public Void SetDebug(boolean debugFlag){

	}

	/**
	 * 
	 * @param val
	 */
	public Void SetLength(Int64 val){

	}

	/**
	 * 
	 * @param wBuf
	 * @param wOffset
	 * @param numToWrite
	 */
	public Void Write(Byte[] wBuf, Int32 wOffset, Int32 numToWrite){

	}

	/**
	 * 
	 * @param b
	 */
	public Void WriteByte(byte b){

	}

	private Void WriteEOFRecord(){

	}

}