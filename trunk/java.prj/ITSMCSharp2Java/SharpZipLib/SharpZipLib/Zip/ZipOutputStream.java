package ICSharpCode.SharpZipLib.Zip;
import ICSharpCode.SharpZipLib.Checksums.Crc32;
import ICSharpCode.SharpZipLib.Zip.Compression.Streams.DeflaterOutputStream;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:17:03
 */
public class ZipOutputStream extends DeflaterOutputStream {

	private Crc32 crc;
	private ZipEntry curEntry;
	private CompressionMethod curMethod;
	private Int32 defaultCompressionLevel;
	private ArrayList entries;
	private Int64 headerPatchPos;
	private Int64 offset;
	private boolean patchEntryHeader;
	private Int64 size;
	private byte zipComment[];

	public ZipOutputStream(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param baseOutputStream
	 */
	public ZipOutputStream(Stream baseOutputStream){

	}

	public Void CloseEntry(){

	}

	public Void Finish(){

	}

	public Int32 GetLevel(){
		return 0;
	}

	public boolean IsFinished(){
		return false;
	}

	/**
	 * 
	 * @param entry
	 */
	public Void PutNextEntry(ZipEntry entry){

	}

	/**
	 * 
	 * @param comment
	 */
	public Void SetComment(String comment){

	}

	/**
	 * 
	 * @param level
	 */
	public Void SetLevel(Int32 level){

	}

	/**
	 * 
	 * @param b
	 * @param off
	 * @param len
	 */
	public Void Write(Byte[] b, Int32 off, Int32 len){

	}

	/**
	 * 
	 * @param crcValue
	 */
	private Void WriteEncryptionHeader(Int64 crcValue){

	}

	/**
	 * 
	 * @param value
	 */
	private Void WriteLeInt(Int32 value){

	}

	/**
	 * 
	 * @param value
	 */
	private Void WriteLeLong(Int64 value){

	}

	/**
	 * 
	 * @param value
	 */
	private Void WriteLeShort(Int32 value){

	}

}