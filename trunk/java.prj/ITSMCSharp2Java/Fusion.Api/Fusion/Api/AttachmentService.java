package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:26
 */
public class AttachmentService {

	private IAttachmentService m_svc = null;

	public AttachmentService(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param svc
	 */
	public AttachmentService(IAttachmentService svc){

	}

	/**
	 * 
	 * @param busOb
	 * @param strAttachmentName
	 * @param strAttachmentPath
	 * @param strAttachmentId
	 */
	public boolean AttachmentExists(Fusion.Api.BusinessObject busOb, String strAttachmentName, String strAttachmentPath, String strAttachmentId){
		return false;
	}

	/**
	 * 
	 * @param strAttachmentName
	 */
	public void DeleteAttachment(String strAttachmentName){

	}

	public IFileStore FileStorage(){
		return null;
	}

	protected IAttachmentService InternalService(){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 * @param strAttachmentName
	 * @param indicator
	 */
	public Attachment LoadAttachment(Fusion.Api.BusinessObject busOb, String strAttachmentName, IProgressIndicator indicator){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 * @param file
	 * @param indicator
	 * @param strAttachmentId
	 */
	public void SaveAttachment(Fusion.Api.BusinessObject busOb, FileInfo file, IProgressIndicator indicator, String strAttachmentId){

	}

	/**
	 * 
	 * @param busOb
	 * @param file
	 * @param indicator
	 * @param createAttachmentObject
	 * @param strAttachmentId
	 */
	public void SaveAttachment(Fusion.Api.BusinessObject busOb, FileInfo file, IProgressIndicator indicator, boolean createAttachmentObject, String strAttachmentId){

	}

	/**
	 * 
	 * @param busOb
	 * @param file
	 * @param indicator
	 * @param createAttachmentObject
	 * @param fromWebClient
	 * @param strAttachmentId
	 */
	public void SaveAttachment(Fusion.Api.BusinessObject busOb, FileInfo file, IProgressIndicator indicator, boolean createAttachmentObject, boolean fromWebClient, String strAttachmentId){

	}

}