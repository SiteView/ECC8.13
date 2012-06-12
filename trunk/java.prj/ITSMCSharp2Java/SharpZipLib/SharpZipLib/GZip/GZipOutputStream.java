package ICSharpCode.SharpZipLib.GZip;
import ICSharpCode.SharpZipLib.Checksums.Crc32;
import ICSharpCode.SharpZipLib.Zip.Compression.Streams.DeflaterOutputStream;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:51
 */
public class GZipOutputStream extends DeflaterOutputStream {

	protected Crc32 crc;

	public GZipOutputStream(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param baseOutputStream
	 */
	public GZipOutputStream(Stream baseOutputStream){

	}

	/**
	 * 
	 * @param baseOutputStream
	 * @param size
	 */
	public GZipOutputStream(Stream baseOutputStream, Int32 size){

	}

	public Void Close(){

	}

	public Void Finish(){

	}

	/**
	 * 
	 * @param buf
	 * @param off
	 * @param len
	 */
	public Void Write(Byte[] buf, Int32 off, Int32 len){

	}

	private Void WriteHeader(){

	}

}