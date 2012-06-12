package ICSharpCode.SharpZipLib.Zip.Compression.Streams;
import ICSharpCode.SharpZipLib.Zip.Compression.Deflater;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:50
 */
public class DeflaterOutputStream extends Stream {

	protected Stream baseOutputStream;
	protected byte buf[];
	protected Deflater def;
	private UInt32 keys[];
	private String password;

	public DeflaterOutputStream(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param baseOutputStream
	 */
	public DeflaterOutputStream(Stream baseOutputStream){

	}

	/**
	 * 
	 * @param baseOutputStream
	 * @param defl
	 */
	public DeflaterOutputStream(Stream baseOutputStream, Deflater defl){

	}

	/**
	 * 
	 * @param baseOutputStream
	 * @param deflater
	 * @param bufsize
	 */
	public DeflaterOutputStream(Stream baseOutputStream, Deflater deflater, Int32 bufsize){

	}

	/**
	 * 
	 * @param buffer
	 * @param offset
	 * @param count
	 * @param callback
	 * @param state
	 */
	public IAsyncResult BeginRead(Byte[] buffer, Int32 offset, Int32 count, AsyncCallback callback, Object state){
		return null;
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

	public boolean CanPatchEntries(){
		return false;
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

	protected Void Deflate(){

	}

	/**
	 * 
	 * @param buffer
	 * @param offset
	 * @param length
	 */
	protected Void EncryptBlock(Byte[] buffer, Int32 offset, Int32 length){

	}

	protected byte EncryptByte(){
		return 0;
	}

	public Void Finish(){

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

	public String Password(){
		return "";
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
	 * @param ch
	 */
	protected Void UpdateKeys(byte ch){

	}

	/**
	 * 
	 * @param buf
	 * @param off
	 * @param len
	 */
	public Void Write(Byte[] buf, Int32 off, Int32 len){

	}

	/**
	 * 
	 * @param bval
	 */
	public Void WriteByte(byte bval){

	}

}