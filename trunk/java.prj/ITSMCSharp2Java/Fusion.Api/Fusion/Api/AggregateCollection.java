package Fusion.Api;

import java.awt.List;
import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:21
 */
public class AggregateCollection extends List implements IEnumerable, IEnumerator {

	private List m_collObjects = null;
	private IEnumerator m_enumObjects = null;

	public AggregateCollection(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param collObjects
	 */
	private AggregateCollection(List collObjects){

	}

	/**
	 * 
	 * @param list
	 * @param nIndex
	 */
	public void CopyTo(ArrayList list, int nIndex){

	}

	public int Count(){
		return 0;
	}

	public Object Current(){
		return null;
	}

	/**
	 * 
	 * @param fusionObj
	 */
	private Object GetAggregate(IAggregate fusionObj){
		return null;
	}

	public IEnumerator GetEnumerator(){
		return null;
	}

	public boolean IsSynchronized(){
		return false;
	}

	public boolean MoveNext(){
		return false;
	}

	public void Reset(){

	}

	public Object SyncRoot(){
		return null;
	}

}

