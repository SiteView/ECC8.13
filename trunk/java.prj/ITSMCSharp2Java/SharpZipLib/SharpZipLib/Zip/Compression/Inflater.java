package ICSharpCode.SharpZipLib.Zip.Compression;
import ICSharpCode.SharpZipLib.Checksums.Adler32;
import ICSharpCode.SharpZipLib.Zip.Compression.Streams.StreamManipulator;
import ICSharpCode.SharpZipLib.Zip.Compression.Streams.OutputWindow;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:52
 */
public class Inflater extends Object {

	private Adler32 adler;
	private static Int32 CPDEXT[];
	private static Int32 CPDIST[];
	private static Int32 CPLENS[];
	private static Int32 CPLEXT[];
	private static Int32 DECODE_BLOCKS;
	private static Int32 DECODE_CHKSUM;
	private static Int32 DECODE_DICT;
	private static Int32 DECODE_DYN_HEADER;
	private static Int32 DECODE_HEADER;
	private static Int32 DECODE_HUFFMAN;
	private static Int32 DECODE_HUFFMAN_DIST;
	private static Int32 DECODE_HUFFMAN_DISTBITS;
	private static Int32 DECODE_HUFFMAN_LENBITS;
	private static Int32 DECODE_STORED;
	private static Int32 DECODE_STORED_LEN1;
	private static Int32 DECODE_STORED_LEN2;
	private InflaterHuffmanTree distTree;
	private InflaterDynHeader dynHeader;
	private static Int32 FINISHED;
	private StreamManipulator input;
	private boolean isLastBlock;
	private InflaterHuffmanTree litlenTree;
	private Int32 mode;
	private Int32 neededBits;
	private boolean noHeader;
	private OutputWindow outputWindow;
	private Int32 readAdler;
	private Int32 repDist;
	private Int32 repLength;
	private Int32 totalIn;
	private Int32 totalOut;
	private Int32 uncomprLen;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public Inflater(){

	}

	/**
	 * 
	 * @param noHeader
	 */
	public Inflater(boolean noHeader){

	}

	private Inflater(){

	}

	public Int32 Adler(){
		return 0;
	}

	private boolean Decode(){
		return false;
	}

	private boolean DecodeChksum(){
		return false;
	}

	private boolean DecodeDict(){
		return false;
	}

	private boolean DecodeHeader(){
		return false;
	}

	private boolean DecodeHuffman(){
		return false;
	}

	/**
	 * 
	 * @param buf
	 */
	public Int32 Inflate(Byte[] buf){
		return 0;
	}

	/**
	 * 
	 * @param buf
	 * @param offset
	 * @param len
	 */
	public Int32 Inflate(Byte[] buf, Int32 offset, Int32 len){
		return 0;
	}

	public boolean IsFinished(){
		return false;
	}

	public boolean IsNeedingDictionary(){
		return false;
	}

	public boolean IsNeedingInput(){
		return false;
	}

	public Int32 RemainingInput(){
		return 0;
	}

	public Void Reset(){

	}

	/**
	 * 
	 * @param buffer
	 */
	public Void SetDictionary(Byte[] buffer){

	}

	/**
	 * 
	 * @param buffer
	 * @param offset
	 * @param len
	 */
	public Void SetDictionary(Byte[] buffer, Int32 offset, Int32 len){

	}

	/**
	 * 
	 * @param buf
	 */
	public Void SetInput(Byte[] buf){

	}

	/**
	 * 
	 * @param buffer
	 * @param offset
	 * @param length
	 */
	public Void SetInput(Byte[] buffer, Int32 offset, Int32 length){

	}

	public Int32 TotalIn(){
		return 0;
	}

	public Int32 TotalOut(){
		return 0;
	}

}