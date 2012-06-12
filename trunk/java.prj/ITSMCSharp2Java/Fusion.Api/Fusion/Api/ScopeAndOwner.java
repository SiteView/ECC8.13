package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:31
 */
public class ScopeAndOwner {

	private String owner;
	private Scope scope;

	public ScopeAndOwner(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param newscope
	 * @param newowner
	 */
	public ScopeAndOwner(Scope newscope, String newowner){

	}

	public String getowner(){
		return owner;
	}

	public Scope getscope(){
		return scope;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setowner(String newVal){
		owner = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setscope(Scope newVal){
		scope = newVal;
	}

}