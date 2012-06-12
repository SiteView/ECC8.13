package ICSharpCode.SharpZipLib.Zip;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:17:01
 */
public class ZipEntry extends Object implements ICloneable {

	private String comment;
	private UInt64 compressedSize;
	private UInt32 crc;
	private UInt32 dosTime;
	private Int32 externalFileAttributes;
	private byte extra[];
	private Int32 flags;
	private UInt16 known;
	private static Int32 KNOWN_CRC;
	private static Int32 KNOWN_CSIZE;
	private static Int32 KNOWN_EXTERN_ATTRIBUTES;
	private static Int32 KNOWN_SIZE;
	private static Int32 KNOWN_TIME;
	private CompressionMethod method;
	private String name;
	private Int32 offset;
	private UInt64 size;
	private UInt16 versionMadeBy;
	private UInt16 versionToExtract;
	private Int32 zipFileIndex;



	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param name
	 */
	public ZipEntry(String name){

	}

	/**
	 * 
	 * @param name
	 * @param versionRequiredToExtract
	 */
	internal ZipEntry(String name, Int32 versionRequiredToExtract){

	}

	/**
	 * 
	 * @param name
	 * @param versionRequiredToExtract
	 * @param madeByInfo
	 */
	internal ZipEntry(String name, Int32 versionRequiredToExtract, Int32 madeByInfo){

	}

	/**
	 * 
	 * @param e
	 */
	public ZipEntry(ZipEntry e){

	}

	private ZipEntry(){

	}

	/**
	 * 
	 * @param name
	 * @param relativePath
	 */
	public static String CleanName(String name, boolean relativePath){
		return "";
	}

	/**
	 * 
	 * @param name
	 */
	public static String CleanName(String name){
		return "";
	}

	public Object Clone(){
		return null;
	}

	public String Comment(){
		return "";
	}

	public Int64 CompressedSize(){
		return null;
	}

	public CompressionMethod CompressionMethod(){
		return null;
	}

	public Int64 Crc(){
		return null;
	}

	public DateTime DateTime(){
		return null;
	}

	public Int64 DosTime(){
		return null;
	}

	public Int32 ExternalFileAttributes(){
		return 0;
	}

	public byte[] ExtraData(){
		return 0;
	}

	public Int32 Flags(){
		return 0;
	}

	public Int32 HostSystem(){
		return 0;
	}

	public boolean IsCrypted(){
		return false;
	}

	public boolean IsDirectory(){
		return false;
	}

	public String Name(){
		return "";
	}

	public Int32 Offset(){
		return 0;
	}

	public Int64 Size(){
		return null;
	}

	public String ToString(){
		return "";
	}

	public Int32 Version(){
		return 0;
	}

	public Int32 VersionMadeBy(){
		return 0;
	}

	public Int32 ZipFileIndex(){
		return 0;
	}

}