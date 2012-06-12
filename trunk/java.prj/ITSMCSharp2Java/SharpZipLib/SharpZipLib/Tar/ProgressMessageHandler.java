package ICSharpCode.SharpZipLib.Tar;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:54
 */
public final class ProgressMessageHandler extends MulticastDelegate {

	public ProgressMessageHandler(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param object
	 * @param method
	 */
	public ProgressMessageHandler(Object object, IntPtr method){

	}

	/**
	 * 
	 * @param archive
	 * @param entry
	 * @param message
	 * @param callback
	 * @param object
	 */
	public IAsyncResult BeginInvoke(TarArchive archive, TarEntry entry, String message, AsyncCallback callback, Object object){
		return null;
	}

	/**
	 * 
	 * @param result
	 */
	public Void EndInvoke(IAsyncResult result){

	}

	/**
	 * 
	 * @param archive
	 * @param entry
	 * @param message
	 */
	public Void Invoke(TarArchive archive, TarEntry entry, String message){

	}

}