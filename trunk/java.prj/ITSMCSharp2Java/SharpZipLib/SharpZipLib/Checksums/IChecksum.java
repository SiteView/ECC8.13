package ICSharpCode.SharpZipLib.Checksums;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:52
 */
public interface IChecksum {

	public abstract Void Reset();

	/**
	 * 
	 * @param bval
	 */
	public abstract Void Update(Int32 bval);

	/**
	 * 
	 * @param buffer
	 */
	public abstract Void Update(Byte[] buffer);

	/**
	 * 
	 * @param buf
	 * @param off
	 * @param len
	 */
	public abstract Void Update(Byte[] buf, Int32 off, Int32 len);

	public Int64 Value();

}