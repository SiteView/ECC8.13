package ICSharpCode.SharpZipLib.Zip.Compression;
import ICSharpCode.SharpZipLib.Zip.Compression.Streams.StreamManipulator;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:52
 */
private class InflaterDynHeader extends Object {

	private static Int32 BL_ORDER[];
	private byte blLens[];
	private static Int32 BLLENS;
	private Int32 blnum;
	private static Int32 BLNUM;
	private InflaterHuffmanTree blTree;
	private Int32 dnum;
	private static Int32 DNUM;
	private byte lastLen;
	private static Int32 LENS;
	private byte litdistLens[];
	private Int32 lnum;
	private static Int32 LNUM;
	private Int32 mode;
	private Int32 num;
	private Int32 ptr;
	private static Int32 repBits[];
	private static Int32 repMin[];
	private static Int32 REPS;
	private Int32 repSymbol;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public InflaterDynHeader(){

	}

	private InflaterDynHeader(){

	}

	public InflaterHuffmanTree BuildDistTree(){
		return null;
	}

	public InflaterHuffmanTree BuildLitLenTree(){
		return null;
	}

	/**
	 * 
	 * @param input
	 */
	public boolean Decode(StreamManipulator input){
		return false;
	}

}