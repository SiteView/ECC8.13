package ICSharpCode.SharpZipLib.Tar;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:56
 */
public class TarEntry extends Object {

	private String file;
	private TarHeader header;



	public void finalize() throws Throwable {
		super.finalize();
	}

	private TarEntry(){

	}

	/**
	 * 
	 * @param headerBuf
	 */
	public TarEntry(Byte[] headerBuf){

	}

	/**
	 * 
	 * @param header
	 */
	public TarEntry(TarHeader header){

	}

	/**
	 * 
	 * @param outbuf
	 * @param newName
	 */
	public Void AdjustEntryName(Byte[] outbuf, String newName){

	}

	/**
	 * 
	 * @param fileName
	 */
	public static TarEntry CreateEntryFromFile(String fileName){
		return null;
	}

	/**
	 * 
	 * @param name
	 */
	public static TarEntry CreateTarEntry(String name){
		return null;
	}

	/**
	 * 
	 * @param it
	 */
	public boolean Equals(Object it){
		return false;
	}

	public String File(){
		return "";
	}

	public TarEntry[] GetDirectoryEntries(){
		return null;
	}

	/**
	 * 
	 * @param hdr
	 * @param file
	 */
	public Void GetFileTarHeader(TarHeader hdr, String file){

	}

	public Int32 GetHashCode(){
		return 0;
	}

	public Int32 GroupId(){
		return 0;
	}

	public String GroupName(){
		return "";
	}

	private Void Initialize(){

	}

	/**
	 * 
	 * @param desc
	 */
	public boolean IsDescendent(TarEntry desc){
		return false;
	}

	public boolean IsDirectory(){
		return false;
	}

	public DateTime ModTime(){
		return null;
	}

	public String Name(){
		return "";
	}

	/**
	 * 
	 * @param hdr
	 * @param name
	 */
	public Void NameTarHeader(TarHeader hdr, String name){

	}

	/**
	 * 
	 * @param userId
	 * @param groupId
	 */
	public Void SetIds(Int32 userId, Int32 groupId){

	}

	/**
	 * 
	 * @param userName
	 * @param groupName
	 */
	public Void SetNames(String userName, String groupName){

	}

	public Int64 Size(){
		return null;
	}

	public TarHeader TarHeader(){
		return null;
	}

	public Int32 UserId(){
		return 0;
	}

	public String UserName(){
		return "";
	}

	/**
	 * 
	 * @param outbuf
	 */
	public Void WriteEntryHeader(Byte[] outbuf){

	}

}