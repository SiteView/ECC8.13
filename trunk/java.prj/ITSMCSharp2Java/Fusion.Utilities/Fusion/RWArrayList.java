package Fusion;

import java.util.ArrayList;

import Fusion.control.ReaderWriterLock;
import Fusion.control.TimeSpan;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:36
 */
public class RWArrayList {

	private ArrayList m_alColl = new ArrayList();
	private ReaderWriterLock m_RWLock = new ReaderWriterLock();

	public RWArrayList(){

	}

	public void finalize() throws Throwable {

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

	public ArrayList Coll(){
		return null;
	}

	public int Count(){
		return 0;
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
	 * @param item
	 */
	public void SafeAdd(Object item){

	}

	/**
	 * 
	 * @param item
	 */
	public Boolean SafeContains(Object item){
		return null;
	}

	/**
	 * 
	 * @param item
	 */
	public void SafeRemove(Object item){

	}

	/**
	 * 
	 * @param nIndex
	 */
	public Object getThis(int nIndex){
		return null;
	}

}
