package ICSharpCode.SharpZipLib.Checksums;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:47
 */
public final class Crc32 extends Object implements IChecksum {

	private UInt32 crc;
	private static UInt32 CrcSeed;
	private static UInt32 CrcTable[];



	public void finalize() throws Throwable {
		super.finalize();
	}

	private Crc32(){

	}

	public Crc32(){

	}

	/**
	 * 
	 * @param oldCrc
	 * @param bval
	 */
	internal static UInt32 ComputeCrc32(UInt32 oldCrc, byte bval){
		return null;
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