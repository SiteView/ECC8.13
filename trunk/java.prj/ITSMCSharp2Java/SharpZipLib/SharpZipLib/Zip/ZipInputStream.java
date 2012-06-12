package ICSharpCode.SharpZipLib.Zip;
import ICSharpCode.SharpZipLib.Checksums.Crc32;
import ICSharpCode.SharpZipLib.Zip.Compression.Streams.InflaterInputStream;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:17:03
 */
public class ZipInputStream extends InflaterInputStream {

	private Int64 avail;
	private Crc32 crc;
	private ZipEntry entry;
	private Int32 flags;
	private Int32 method;
	private String password;
	private Int64 size;

	public ZipInputStream(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param baseInputStream
	 */
	public ZipInputStream(Stream baseInputStream){

	}

	public Int32 Available(){
		return 0;
	}

	public boolean CanDecompressEntry(){
		return false;
	}

	public Void Close(){

	}

	public Void CloseEntry(){

	}

	/**
	 * 
	 * @param size
	 */
	private Void FillBuf(Int32 size){

	}

	public ZipEntry GetNextEntry(){
		return null;
	}

	public String Password(){
		return "";
	}

	/**
	 * 
	 * @param b
	 * @param off
	 * @param len
	 */
	public Int32 Read(Byte[] b, Int32 off, Int32 len){
		return 0;
	}

	/**
	 * 
	 * @param outBuf
	 * @param offset
	 * @param length
	 */
	private Int32 ReadBuf(Byte[] outBuf, Int32 offset, Int32 length){
		return 0;
	}

	public Int32 ReadByte(){
		return 0;
	}

	private Void ReadDataDescriptor(){

	}

	/**
	 * 
	 * @param outBuf
	 */
	private Void ReadFully(Byte[] outBuf){

	}

	private Int32 ReadLeByte(){
		return 0;
	}

	private Int32 ReadLeInt(){
		return 0;
	}

	private Int64 ReadLeLong(){
		return null;
	}

	private Int32 ReadLeShort(){
		return 0;
	}

}