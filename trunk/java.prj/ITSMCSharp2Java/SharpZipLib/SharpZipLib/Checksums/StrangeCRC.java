package ICSharpCode.SharpZipLib.Checksums;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:55
 */
public class StrangeCRC extends Object implements IChecksum {

	private static UInt32 crc32Table[];
	private Int32 globalCrc;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public StrangeCRC(){

	}

	private StrangeCRC(){

	}

	public Void Reset(){

	}

	/**
	 * 
	 * @param inCh
	 */
	public Void Update(Int32 inCh){

	}

	/**
	 * 
	 * @param buf
	 */
	public Void Update(Byte[] buf){

	}

	/**
	 * 
	 * @param buf
	 * @param off
	 * @param len
	 */
	public Void Update(Byte[] buf, Int32 off, Int32 len){

	}

	public Int64 Value(){
		return null;
	}

}