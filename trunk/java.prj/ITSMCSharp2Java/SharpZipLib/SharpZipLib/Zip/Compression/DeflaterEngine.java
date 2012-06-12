package ICSharpCode.SharpZipLib.Zip.Compression;
import ICSharpCode.SharpZipLib.Checksums.Adler32;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:49
 */
public class DeflaterEngine extends DeflaterConstants {

	private Adler32 adler;
	private Int32 blockStart;
	private Int32 comprFunc;
	private Int32 goodLength;
	private Int16 head[];
	private DeflaterHuffman huffman;
	private byte inputBuf[];
	private Int32 inputEnd;
	private Int32 inputOff;
	private Int32 ins_h;
	private Int32 lookahead;
	private Int32 matchLen;
	private Int32 matchStart;
	private Int32 max_chain;
	private Int32 max_lazy;
	private Int32 niceLength;
	private DeflaterPending pending;
	private Int16 prev[];
	private boolean prevAvailable;
	private DeflateStrategy strategy;
	private Int32 strstart;
	private static Int32 TOO_FAR;
	private Int32 totalIn;
	private byte window[];



	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param pending
	 */
	public DeflaterEngine(DeflaterPending pending){

	}

	private DeflaterEngine(){

	}

	public Int32 Adler(){
		return 0;
	}

	/**
	 * 
	 * @param flush
	 * @param finish
	 */
	public boolean Deflate(boolean flush, boolean finish){
		return false;
	}

	/**
	 * 
	 * @param flush
	 * @param finish
	 */
	private boolean DeflateFast(boolean flush, boolean finish){
		return false;
	}

	/**
	 * 
	 * @param flush
	 * @param finish
	 */
	private boolean DeflateSlow(boolean flush, boolean finish){
		return false;
	}

	/**
	 * 
	 * @param flush
	 * @param finish
	 */
	private boolean DeflateStored(boolean flush, boolean finish){
		return false;
	}

	public Void FillWindow(){

	}

	/**
	 * 
	 * @param curMatch
	 */
	private boolean FindLongestMatch(Int32 curMatch){
		return false;
	}

	private Int32 InsertString(){
		return 0;
	}

	public boolean NeedsInput(){
		return false;
	}

	public Void Reset(){

	}

	public Void ResetAdler(){

	}

	/**
	 * 
	 * @param buffer
	 * @param offset
	 * @param length
	 */
	public Void SetDictionary(Byte[] buffer, Int32 offset, Int32 length){

	}

	/**
	 * 
	 * @param buf
	 * @param off
	 * @param len
	 */
	public Void SetInput(Byte[] buf, Int32 off, Int32 len){

	}

	/**
	 * 
	 * @param lvl
	 */
	public Void SetLevel(Int32 lvl){

	}

	private Void SlideWindow(){

	}

	public DeflateStrategy Strategy(){
		return null;
	}

	public Int32 TotalIn(){
		return 0;
	}

	private Void UpdateHash(){

	}

}