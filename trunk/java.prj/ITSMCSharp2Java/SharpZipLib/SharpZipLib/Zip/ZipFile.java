package ICSharpCode.SharpZipLib.Zip;
import ICSharpCode.SharpZipLib.Zip.Compression.Streams.InflaterInputStream;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-四月-2010 17:17:02
 */
public class ZipFile extends Object implements IEnumerable {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 14-四月-2010 17:17:02
	 */
	private class ZipEntryEnumeration extends Object implements IEnumerator {

		private ZipEntry array[];
		private Int32 ptr;

		public ZipEntryEnumeration(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		/**
		 * 
		 * @param arr
		 */
		public ZipEntryEnumeration(ZipEntry[] arr){

		}

		public Object Current(){
			return null;
		}

		public boolean MoveNext(){
			return false;
		}

		public Void Reset(){

		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 14-四月-2010 17:17:02
	 */
	private class PartialInputStream extends InflaterInputStream {

		private Stream baseStream;
		private Int64 end;
		private Int64 filepos;

		public PartialInputStream(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		/**
		 * 
		 * @param baseStream
		 * @param start
		 * @param len
		 */
		public PartialInputStream(Stream baseStream, Int64 start, Int64 len){

		}

		public Int32 Available(){
			return 0;
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

		public Int32 ReadByte(){
			return 0;
		}

		/**
		 * 
		 * @param amount
		 */
		public Int64 SkipBytes(Int64 amount){
			return null;
		}

	}

	private Stream baseStream;
	private String comment;
	private ZipEntry entries[];
	private String name;

	public ZipFile(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param name
	 */
	public ZipFile(String name){

	}

	/**
	 * 
	 * @param file
	 */
	public ZipFile(FileStream file){

	}

	/**
	 * 
	 * @param baseStream
	 */
	public ZipFile(Stream baseStream){

	}

	/**
	 * 
	 * @param entry
	 */
	private Int64 CheckLocalHeader(ZipEntry entry){
		return null;
	}

	public Void Close(){

	}

	public ZipEntry EntryByIndex(){
		return null;
	}

	/**
	 * 
	 * @param name
	 * @param ignoreCase
	 */
	public Int32 FindEntry(String name, boolean ignoreCase){
		return 0;
	}

	/**
	 * 
	 * @param name
	 */
	public ZipEntry GetEntry(String name){
		return null;
	}

	public IEnumerator GetEnumerator(){
		return null;
	}

	/**
	 * 
	 * @param entry
	 */
	public Stream GetInputStream(ZipEntry entry){
		return null;
	}

	/**
	 * 
	 * @param entryIndex
	 */
	public Stream GetInputStream(Int32 entryIndex){
		return null;
	}

	public String Name(){
		return "";
	}

	private Void ReadEntries(){

	}

	private Int32 ReadLeInt(){
		return 0;
	}

	private Int32 ReadLeShort(){
		return 0;
	}

	public Int32 Size(){
		return 0;
	}

	public String ZipFileComment(){
		return "";
	}

}