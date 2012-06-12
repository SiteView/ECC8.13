package ICSharpCode.SharpZipLib.GZip;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:51
 */
public class GZipConstants extends Object {

	private static Int32 FCOMMENT;
	private static Int32 FEXTRA;
	private static Int32 FHCRC;
	private static Int32 FNAME;
	private static Int32 FTEXT;
	private static Int32 GZIP_MAGIC;



	public void finalize() throws Throwable {
		super.finalize();
	}

	private GZipConstants(){

	}

	private GZipConstants(){

	}

	public Int32 getFCOMMENT(){
		return FCOMMENT;
	}

	public Int32 getFEXTRA(){
		return FEXTRA;
	}

	public Int32 getFHCRC(){
		return FHCRC;
	}

	public Int32 getFNAME(){
		return FNAME;
	}

	public Int32 getFTEXT(){
		return FTEXT;
	}

	public Int32 getGZIP_MAGIC(){
		return GZIP_MAGIC;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFCOMMENT(Int32 newVal){
		FCOMMENT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFEXTRA(Int32 newVal){
		FEXTRA = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFHCRC(Int32 newVal){
		FHCRC = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFNAME(Int32 newVal){
		FNAME = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFTEXT(Int32 newVal){
		FTEXT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGZIP_MAGIC(Int32 newVal){
		GZIP_MAGIC = newVal;
	}

}