package ICSharpCode.SharpZipLib.Zip.Compression;
import ICSharpCode.SharpZipLib.Zip.Compression.Streams.StreamManipulator;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:53
 */
public class InflaterHuffmanTree extends Object {

	private static InflaterHuffmanTree defDistTree;
	private static InflaterHuffmanTree defLitLenTree;
	private static Int32 MAX_BITLEN;
	private Int16 tree[];



	public void finalize() throws Throwable {
		super.finalize();
	}

	private InflaterHuffmanTree(){

	}

	/**
	 * 
	 * @param codeLengths
	 */
	public InflaterHuffmanTree(Byte[] codeLengths){

	}

	/**
	 * 
	 * @param codeLengths
	 */
	private Void BuildTree(Byte[] codeLengths){

	}

	public InflaterHuffmanTree getdefDistTree(){
		return defDistTree;
	}

	public InflaterHuffmanTree getdefLitLenTree(){
		return defLitLenTree;
	}

	/**
	 * 
	 * @param input
	 */
	public Int32 GetSymbol(StreamManipulator input){
		return 0;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefDistTree(InflaterHuffmanTree newVal){
		defDistTree = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefLitLenTree(InflaterHuffmanTree newVal){
		defLitLenTree = newVal;
	}

}