package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:28
 */
public class FrequencyRelativeIntervalValues {

	private int First = 1;
	private int Fourth = 8;
	private int Last = 0x10;
	private int Second = 2;
	private int Third = 4;
	private int UseDatabaseDefault = -1;

	public FrequencyRelativeIntervalValues(){

	}

	public void finalize() throws Throwable {

	}

	public int getFirst(){
		return First;
	}

	public int getFourth(){
		return Fourth;
	}

	public int getLast(){
		return Last;
	}

	public int getSecond(){
		return Second;
	}

	public int getThird(){
		return Third;
	}

	public int getUseDatabaseDefault(){
		return UseDatabaseDefault;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFirst(int newVal){
		First = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFourth(int newVal){
		Fourth = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLast(int newVal){
		Last = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSecond(int newVal){
		Second = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setThird(int newVal){
		Third = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUseDatabaseDefault(int newVal){
		UseDatabaseDefault = newVal;
	}

}