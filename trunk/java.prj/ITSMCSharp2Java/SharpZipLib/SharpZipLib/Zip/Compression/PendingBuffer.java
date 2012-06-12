package ICSharpCode.SharpZipLib.Zip.Compression;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:54
 */
public class PendingBuffer extends Object {

	private Int32 bitCount;
	private UInt32 bits;
	protected byte buf[];
	private Int32 end;
	private Int32 start;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public PendingBuffer(){

	}

	/**
	 * 
	 * @param bufsize
	 */
	public PendingBuffer(Int32 bufsize){

	}

	public Void AlignToByte(){

	}

	public Int32 BitCount(){
		return 0;
	}

	/**
	 * 
	 * @param output
	 * @param offset
	 * @param length
	 */
	public Int32 Flush(Byte[] output, Int32 offset, Int32 length){
		return 0;
	}

	public boolean IsFlushed(){
		return false;
	}

	public Void Reset(){

	}

	public byte[] ToByteArray(){
		return 0;
	}

	/**
	 * 
	 * @param b
	 * @param count
	 */
	public Void WriteBits(Int32 b, Int32 count){

	}

	/**
	 * 
	 * @param block
	 * @param offset
	 * @param len
	 */
	public Void WriteBlock(Byte[] block, Int32 offset, Int32 len){

	}

	/**
	 * 
	 * @param b
	 */
	public Void WriteByte(Int32 b){

	}

	/**
	 * 
	 * @param s
	 */
	public Void WriteInt(Int32 s){

	}

	/**
	 * 
	 * @param s
	 */
	public Void WriteShort(Int32 s){

	}

	/**
	 * 
	 * @param s
	 */
	public Void WriteShortMSB(Int32 s){

	}

}