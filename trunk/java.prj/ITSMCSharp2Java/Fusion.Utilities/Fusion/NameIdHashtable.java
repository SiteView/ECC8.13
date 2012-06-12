package Fusion;

import java.util.Hashtable;

import Fusion.control.Array;
import Fusion.control.ICollection;
import Fusion.control.IEnumerable;
import Fusion.control.IEnumerator;
import Fusion.control.inter.ICloneable;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 11:18:32
 */
public class NameIdHashtable extends ICollection implements IEnumerable, ICloneable {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:32
	 */
	public class IdAccessor {

		private NameIdHashtable m_nihtParent = null;

		public IdAccessor(){

		}

		public void finalize() throws Throwable {

		}

		/**
		 * 
		 * @param ht
		 */
		public IdAccessor(NameIdHashtable ht){

		}

		/**
		 * 
		 * @param strId
		 */
		public Boolean Contains(String strId){
			return null;
		}

		public ICollection Keys(){
			return null;
		}

		/**
		 * 
		 * @param strId
		 */
		public void Remove(String strId){

		}

		/**
		 * 
		 * @param strId
		 */
		public INameId getThis(String strId){
			return null;
		}

		public ICollection Values(){
			return null;
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:32
	 */
	public class NameAccessor {

		private NameIdHashtable m_nihtParent = null;

		public NameAccessor(){

		}

		public void finalize() throws Throwable {

		}

		/**
		 * 
		 * @param ht
		 */
		public NameAccessor(NameIdHashtable ht){

		}

		/**
		 * 
		 * @param strName
		 */
		public Boolean Contains(String strName){
			return null;
		}

		public ICollection Keys(){
			return null;
		}

		/**
		 * 
		 * @param strName
		 */
		public void Remove(String strName){

		}

		/**
		 * 
		 * @param strName
		 */
		public INameId getThis(String strName){
			return null;
		}

		public ICollection Values(){
			return null;
		}

	}

	private Hashtable m_htById = new Hashtable();
	private Hashtable m_htByName = new Hashtable();
	private IdAccessor m_IdAccessor = null;
	private NameAccessor m_NameAccessor = null;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public NameIdHashtable(){

	}

	/**
	 * 
	 * @param item
	 */
	public void Add(INameId item){

	}

	public void Clear(){

	}

	public Object Clone(){
		return null;
	}

	/**
	 * 
	 * @param item
	 */
	public Boolean Contains(INameId item){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Boolean Contains(String strName){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public Boolean ContainsId(String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Boolean ContainsName(String strName){
		return null;
	}

	/**
	 * 
	 * @param ht
	 */
	protected void CopyElements(NameIdHashtable ht){

	}

	/**
	 * 
	 * @param array
	 * @param index
	 */
	public void CopyTo(Array array, int index){

	}

	public int Count(){
		return 0;
	}

	/**
	 * 
	 * @param strName
	 */
	public INameId GetAt(String strName){
		return null;
	}

	/**
	 * 
	 * @param strId
	 */
	public INameId GetAtId(String strId){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public INameId GetAtName(String strName){
		return null;
	}

	public IEnumerator GetEnumerator(){
		return null;
	}

	public IdAccessor Id(){
		return null;
	}

	public ICollection IdKeys(){
		return null;
	}

	private void Initialize(){

	}

	public Boolean IsSynchronized(){
		return null;
	}

	public NameAccessor Name(){
		return null;
	}

	public ICollection NameKeys(){
		return null;
	}

	/**
	 * 
	 * @param item
	 */
	public void Remove(INameId item){

	}

	/**
	 * 
	 * @param strName
	 */
	public void Remove(String strName){

	}

	/**
	 * 
	 * @param strId
	 */
	public void RemoveId(String strId){

	}

	/**
	 * 
	 * @param strName
	 */
	public void RemoveName(String strName){

	}

	/**
	 * 
	 * @param item
	 */
	public void ReplaceOrAdd(INameId item){

	}

	public Object SyncRoot(){
		return null;
	}

	public ICollection Values(){
		return null;
	}

}