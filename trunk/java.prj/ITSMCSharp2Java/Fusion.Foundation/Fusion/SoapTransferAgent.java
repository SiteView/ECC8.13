package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:19
 */
public class SoapTransferAgent extends MarshalByRefObject {

	private FileInfo m_file = null;
	private byte m_nBuffer[] = null;
	private final int m_nBuffSize = 0x8000;
	private FileStream m_stream = null;
	private String m_strFileName = "";
	private String m_strRootPath = "";

	public SoapTransferAgent(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strRootPath
	 */
	public SoapTransferAgent(String strRootPath){

	}

	public void AbortFile(){

	}

	/**
	 * 
	 * @param nSize
	 * @param strChunkData
	 */
	public void AddChunk(int nSize, String strChunkData){

	}

	public int BlockSize(){
		return 0;
	}

	public void CompleteFile(){

	}

	public void DeleteFile(){

	}

	public FileInfo File(){
		return null;
	}

	/**
	 * 
	 * @param nReadLength
	 */
	public String GetChunk(int nReadLength){
		return "";
	}

	public boolean IsFileInfoValid(){
		return null;
	}

	/**
	 * 
	 * @param strFileName
	 */
	public void PrepForReceiving(String strFileName){

	}

	/**
	 * 
	 * @param strRelativePathName
	 */
	public void PrepForSending(String strRelativePathName){

	}

}