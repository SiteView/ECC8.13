package ICSharpCode.SharpZipLib.Zip.Compression.Streams;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:55
 */
public class StreamManipulator extends Object {

	private Int32 bits_in_buffer;
	private UInt32 buffer;
	private byte window[];
	private Int32 window_end;
	private Int32 window_start;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public StreamManipulator(){

	}

	public Int32 AvailableBits(){
		return 0;
	}

	public Int32 AvailableBytes(){
		return 0;
	}

	/**
	 * 
	 * @param output
	 * @param offset
	 * @param length
	 */
	public Int32 CopyBytes(Byte[] output, Int32 offset, Int32 length){
		return 0;
	}

	/**
	 * 
	 * @param n
	 */
	public Void DropBits(Int32 n){

	}

	/**
	 * 
	 * @param n
	 */
	public Int32 GetBits(Int32 n){
		return 0;
	}

	public boolean IsNeedingInput(){
		return false;
	}

	/**
	 * 
	 * @param n
	 */
	public Int32 PeekBits(Int32 n){
		return 0;
	}

	public Void Reset(){

	}

	/**
	 * 
	 * @param buf
	 * @param off
	 * @param len
	 */
	public Void SetInput(Byte[] buf, Int32 off, Int32 len){

	}

	public Void SkipToByteBoundary(){

	}

}