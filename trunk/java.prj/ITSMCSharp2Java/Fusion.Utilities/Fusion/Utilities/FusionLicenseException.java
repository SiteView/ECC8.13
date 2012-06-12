package Fusion.Utilities;
import Fusion.FusionException;
import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:20
 */
public class FusionLicenseException extends FusionException {

	public FusionLicenseException(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected FusionLicenseException(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 */
	public FusionLicenseException(String message, String source){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 * @param inner
	 */
	public FusionLicenseException(String message, String source, Exception inner){

	}

}