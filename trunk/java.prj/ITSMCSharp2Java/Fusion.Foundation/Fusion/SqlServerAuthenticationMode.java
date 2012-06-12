package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:20
 */
public class SqlServerAuthenticationMode {

	private int SqlServer = 0;
	private int Windows = 1;

	public SqlServerAuthenticationMode(){

	}

	public void finalize() throws Throwable {

	}

	public int getSqlServer(){
		return SqlServer;
	}

	public int getWindows(){
		return Windows;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSqlServer(int newVal){
		SqlServer = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setWindows(int newVal){
		Windows = newVal;
	}

}