package ICSharpCode.SharpZipLib.Tar;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-四月-2010 17:16:58
 */
public class TarInputStream extends Stream {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 14-四月-2010 17:16:58
	 */
	public interface IEntryFactory {

		/**
		 * 
		 * @param name
		 */
		public abstract TarEntry CreateEntry(String name);

		/**
		 * 
		 * @param headerBuf
		 */
		public abstract TarEntry CreateEntry(Byte[] headerBuf);

		/**
		 * 
		 * @param fileName
		 */
		public abstract TarEntry CreateEntryFromFile(String fileName);

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 14-四月-2010 17:16:59
	 */
	public class EntryFactoryAdapter extends Object implements IEntryFactory {



		public void finalize() throws Throwable {
			super.finalize();
		}

		public EntryFactoryAdapter(){

		}

		/**
		 * 
		 * @param name
		 */
		public TarEntry CreateEntry(String name){
			return null;
		}

		/**
		 * 
		 * @param headerBuf
		 */
		public TarEntry CreateEntry(Byte[] headerBuf){
			return null;
		}

		/**
		 * 
		 * @param fileName
		 */
		public TarEntry CreateEntryFromFile(String fileName){
			return null;
		}

	}

	protected TarBuffer buffer;
	protected TarEntry currEntry;
	protected boolean debug;
	protected IEntryFactory eFactory;
	protected Int32 entryOffset;
	protected Int32 entrySize;
	protected boolean hasHitEOF;
	private Stream inputStream;
	protected byte readBuf[];

	public TarInputStream(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param inputStream
	 */
	public TarInputStream(Stream inputStream){

	}

	/**
	 * 
	 * @param inputStream
	 * @param blockFactor
	 */
	public TarInputStream(Stream inputStream, Int32 blockFactor){

	}

	public Int32 Available(){
		return 0;
	}

	public boolean CanRead(){
		return false;
	}

	public boolean CanSeek(){
		return false;
	}

	public boolean CanWrite(){
		return false;
	}

	public Void Close(){

	}

	/**
	 * 
	 * @param outputStream
	 */
	public Void CopyEntryContents(Stream outputStream){

	}

	public Void Flush(){

	}

	public TarEntry GetNextEntry(){
		return null;
	}

	public Int32 GetRecordSize(){
		return 0;
	}

	public boolean IsMarkSupported(){
		return false;
	}

	public Int64 Length(){
		return null;
	}

	/**
	 * 
	 * @param markLimit
	 */
	public Void Mark(Int32 markLimit){

	}

	public Int64 Position(){
		return null;
	}

	/**
	 * 
	 * @param outputBuffer
	 * @param offset
	 * @param numToRead
	 */
	public Int32 Read(Byte[] outputBuffer, Int32 offset, Int32 numToRead){
		return 0;
	}

	public Int32 ReadByte(){
		return 0;
	}

	public Void Reset(){

	}

	/**
	 * 
	 * @param offset
	 * @param origin
	 */
	public Int64 Seek(Int64 offset, SeekOrigin origin){
		return null;
	}

	/**
	 * 
	 * @param debug
	 */
	public Void SetBufferDebug(boolean debug){

	}

	/**
	 * 
	 * @param debugFlag
	 */
	public Void SetDebug(boolean debugFlag){

	}

	/**
	 * 
	 * @param factory
	 */
	public Void SetEntryFactory(IEntryFactory factory){

	}

	/**
	 * 
	 * @param val
	 */
	public Void SetLength(Int64 val){

	}

	/**
	 * 
	 * @param numToSkip
	 */
	public Void Skip(Int32 numToSkip){

	}

	private Void SkipToNextEntry(){

	}

	/**
	 * 
	 * @param array
	 * @param offset
	 * @param count
	 */
	public Void Write(Byte[] array, Int32 offset, Int32 count){

	}

	/**
	 * 
	 * @param val
	 */
	public Void WriteByte(byte val){

	}

}