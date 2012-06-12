package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:40
 */
public final class ThreadUtils {

	private int Infinite = -1;

	public ThreadUtils(){

	}

	public void finalize() throws Throwable {

	}

	public int getInfinite(){
		return Infinite;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setInfinite(int newVal){
		Infinite = newVal;
	}

}
