package Fusion;

import java.util.Hashtable;

import Fusion.control.ISerializable;
import Fusion.control.ReaderWriterLock;
import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;
import Fusion.control.TimeSpan;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:37
 */
public class RWHashtable extends ISerializable {

	private Hashtable m_htColl;
	private ReaderWriterLock m_RWLock;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public RWHashtable(){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public RWHashtable(SerializationInfo info, StreamingContext context){

	}

	public void AcquireReaderLock(){

	}

	/**
	 * 
	 * @param nTimeOut
	 */
	public void AcquireReaderLock(int nTimeOut){

	}

	/**
	 * 
	 * @param tsTimeOut
	 */
	public void AcquireReaderLock(TimeSpan tsTimeOut){

	}

	public void AcquireWriterLock(){

	}

	/**
	 * 
	 * @param nTimeOut
	 */
	public void AcquireWriterLock(int nTimeOut){

	}

	/**
	 * 
	 * @param tsTimeOut
	 */
	public void AcquireWriterLock(TimeSpan tsTimeOut){

	}

	public Hashtable Coll(){
		return null;
	}

	public int Count(){
		return 0;
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

	public void ReleaseReaderLock(){

	}

	public void ReleaseWriterLock(){

	}

	public ReaderWriterLock RWLock(){
		return null;
	}

	/**
	 * 
	 * @param oKey
	 * @param oValue
	 */
	public void SafeAdd(Object oKey, Object oValue){

	}

	public void SafeClear(){

	}

	/**
	 * 
	 * @param oKey
	 */
	public Boolean SafeContains(Object oKey){
		return null;
	}

	/**
	 * 
	 * @param oKey
	 */
	public void SafeRemove(Object oKey){

	}

	/**
	 * 
	 * @param oKey
	 */
	public Object getThis(Object oKey){
		return null;
	}

}