package ICSharpCode.SharpZipLib.GZip;
import ICSharpCode.SharpZipLib.Checksums.Crc32;
import ICSharpCode.SharpZipLib.Zip.Compression.Streams.InflaterInputStream;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:51
 */
public class GZipInputStream extends InflaterInputStream {

	protected Crc32 crc;
	protected boolean eos;
	private boolean readGZIPHeader;

	public GZipInputStream(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param baseInputStream
	 */
	public GZipInputStream(Stream baseInputStream){

	}

	/**
	 * 
	 * @param baseInputStream
	 * @param size
	 */
	public GZipInputStream(Stream baseInputStream, Int32 size){

	}

	/**
	 * 
	 * @param buf
	 * @param offset
	 * @param len
	 */
	public Int32 Read(Byte[] buf, Int32 offset, Int32 len){
		return 0;
	}

	private Void ReadFooter(){

	}

	private Void ReadHeader(){

	}

}