package ICSharpCode.SharpZipLib.Zip.Compression.Streams;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:54
 */
public class OutputWindow extends Object {

	private byte window[];
	private static Int32 WINDOW_MASK;
	private static Int32 WINDOW_SIZE;
	private Int32 windowEnd;
	private Int32 windowFilled;



	public void finalize() throws Throwable {
		super.finalize();
	}

	private OutputWindow(){

	}

	public OutputWindow(){

	}

	/**
	 * 
	 * @param dict
	 * @param offset
	 * @param len
	 */
	public Void CopyDict(Byte[] dict, Int32 offset, Int32 len){

	}

	/**
	 * 
	 * @param output
	 * @param offset
	 * @param len
	 */
	public Int32 CopyOutput(Byte[] output, Int32 offset, Int32 len){
		return 0;
	}

	/**
	 * 
	 * @param input
	 * @param len
	 */
	public Int32 CopyStored(StreamManipulator input, Int32 len){
		return 0;
	}

	public Int32 GetAvailable(){
		return 0;
	}

	public Int32 GetFreeSpace(){
		return 0;
	}

	/**
	 * 
	 * @param len
	 * @param dist
	 */
	public Void Repeat(Int32 len, Int32 dist){

	}

	public Void Reset(){

	}

	/**
	 * 
	 * @param repStart
	 * @param len
	 * @param dist
	 */
	private Void SlowRepeat(Int32 repStart, Int32 len, Int32 dist){

	}

	/**
	 * 
	 * @param abyte
	 */
	public Void Write(Int32 abyte){

	}

}