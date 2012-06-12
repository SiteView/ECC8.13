package ICSharpCode.SharpZipLib.Tar;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:55
 */
public class TarArchive extends Object {

	private boolean asciiTranslate;
	private boolean debug;
	private Int32 groupId;
	private String groupName;
	private boolean keepOldFiles;
	private String pathPrefix;
	private ProgressMessageHandler ProgressMessageEvent;
	private byte recordBuf[];
	private Int32 recordSize;
	private String rootPath;
	private TarInputStream tarIn;
	private TarOutputStream tarOut;
	private Int32 userId;
	private String userName;
	private boolean verbose;



	public void finalize() throws Throwable {
		super.finalize();
	}

	protected TarArchive(){

	}

	/**
	 * 
	 * @param value
	 */
	public Void add_ProgressMessageEvent(ProgressMessageHandler value){

	}

	public Void CloseArchive(){

	}

	/**
	 * 
	 * @param inputStream
	 */
	public static TarArchive CreateInputTarArchive(Stream inputStream){
		return null;
	}

	/**
	 * 
	 * @param inputStream
	 * @param blockFactor
	 */
	public static TarArchive CreateInputTarArchive(Stream inputStream, Int32 blockFactor){
		return null;
	}

	/**
	 * 
	 * @param outputStream
	 */
	public static TarArchive CreateOutputTarArchive(Stream outputStream){
		return null;
	}

	/**
	 * 
	 * @param outputStream
	 * @param blockFactor
	 */
	public static TarArchive CreateOutputTarArchive(Stream outputStream, Int32 blockFactor){
		return null;
	}

	/**
	 * 
	 * @param directoryName
	 */
	private Void EnsureDirectoryExists(String directoryName){

	}

	/**
	 * 
	 * @param destDir
	 */
	public Void ExtractContents(String destDir){

	}

	/**
	 * 
	 * @param destDir
	 * @param entry
	 */
	private Void ExtractEntry(String destDir, TarEntry entry){

	}

	public Int32 GroupId(){
		return 0;
	}

	public String GroupName(){
		return "";
	}

	/**
	 * 
	 * @param recordSize
	 */
	private Void Initialize(Int32 recordSize){

	}

	/**
	 * 
	 * @param filename
	 */
	private boolean IsBinary(String filename){
		return false;
	}

	public boolean IsVerbose(){
		return false;
	}

	public Void ListContents(){

	}

	/**
	 * 
	 * @param entry
	 * @param message
	 */
	protected Void OnProgressMessageEvent(TarEntry entry, String message){

	}

	public ProgressMessageHandler ProgressMessageEvent(){
		return null;
	}

	public Int32 RecordSize(){
		return 0;
	}

	/**
	 * 
	 * @param value
	 */
	public Void remove_ProgressMessageEvent(ProgressMessageHandler value){

	}

	/**
	 * 
	 * @param asciiTranslate
	 */
	public Void SetAsciiTranslation(boolean asciiTranslate){

	}

	/**
	 * 
	 * @param debugFlag
	 */
	public Void SetDebug(boolean debugFlag){

	}

	/**
	 * 
	 * @param keepOldFiles
	 */
	public Void SetKeepOldFiles(boolean keepOldFiles){

	}

	/**
	 * 
	 * @param userId
	 * @param userName
	 * @param groupId
	 * @param groupName
	 */
	public Void SetUserInfo(Int32 userId, String userName, Int32 groupId, String groupName){

	}

	public Int32 UserId(){
		return 0;
	}

	public String UserName(){
		return "";
	}

	/**
	 * 
	 * @param entry
	 * @param recurse
	 */
	public Void WriteEntry(TarEntry entry, boolean recurse){

	}

}