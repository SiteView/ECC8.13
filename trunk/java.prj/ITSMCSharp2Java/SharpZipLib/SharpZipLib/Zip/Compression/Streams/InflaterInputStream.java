package ICSharpCode.SharpZipLib.Zip.Compression.Streams;
import ICSharpCode.SharpZipLib.Zip.Compression.Inflater;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:53
 */
public class InflaterInputStream extends Stream {

	protected Stream baseInputStream;
	protected byte buf[];
	protected byte cryptbuffer[];
	protected Int64 csize;
	protected Inflater inf;
	private UInt32 keys[];
	protected Int32 len;
	private byte onebytebuffer[];
	private Int32 readChunkSize;

	public InflaterInputStream(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param baseInputStream
	 */
	public InflaterInputStream(Stream baseInputStream){

	}

	/**
	 * 
	 * @param baseInputStream
	 * @param inf
	 */
	public InflaterInputStream(Stream baseInputStream, Inflater inf){

	}

	/**
	 * 
	 * @param baseInputStream
	 * @param inflater
	 * @param bufferSize
	 */
	public InflaterInputStream(Stream baseInputStream, Inflater inflater, Int32 bufferSize){

	}

	public Int32 Available(){
		return 0;
	}

	/**
	 * 
	 * @param buffer
	 * @param offset
	 * @param count
	 * @param callback
	 * @param state
	 */
	public IAsyncResult BeginWrite(Byte[] buffer, Int32 offset, Int32 count, AsyncCallback callback, Object state){
		return null;
	}

	public Int32 BufferReadSize(){
		return 0;
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

	/**
	 * 
	 * @param buf
	 * @param off
	 * @param len
	 */
	protected Void DecryptBlock(Byte[] buf, Int32 off, Int32 len){

	}

	protected byte DecryptByte(){
		return 0;
	}

	protected Void Fill(){

	}

	protected Void FillInputBuffer(){

	}

	public Void Flush(){

	}

	/**
	 * 
	 * @param password
	 */
	protected Void InitializePassword(String password){

	}

	public Int64 Length(){
		return null;
	}

	public Int64 Position(){
		return null;
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
	 * @param val
	 */
	public Void SetLength(Int64 val){

	}

	/**
	 * 
	 * @param n
	 */
	public Int64 Skip(Int64 n){
		return null;
	}

	protected Void StopDecrypting(){

	}

	/**
	 * 
	 * @param ch
	 */
	protected Void UpdateKeys(byte ch){

	}

	/**
	 * 
	 * @param array
	 * @param offset
	 * @param count
	 */
	public Void Write(Byte[] array, Int32 offset, Int32 count){

	}

	/**
	 * 
	 * @param val
	 */
	public Void WriteByte(byte val){

	}

}