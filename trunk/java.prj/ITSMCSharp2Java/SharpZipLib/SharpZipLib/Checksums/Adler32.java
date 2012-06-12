package ICSharpCode.SharpZipLib.Checksums;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:44
 */
public final class Adler32 extends Object implements IChecksum {

	private static UInt32 BASE;
	private UInt32 checksum;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public Adler32(){

	}

	private Adler32(){

	}

	public Void Reset(){

	}

	/**
	 * 
	 * @param bval
	 */
	public Void Update(Int32 bval){

	}

	/**
	 * 
	 * @param buffer
	 */
	public Void Update(Byte[] buffer){

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