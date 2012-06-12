package Fusion;

import Fusion.control.IIdentity;
import Fusion.control.IPrincipal;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:21
 */
public class FusionPrincipal extends IPrincipal {

	private FusionIdentity m_identity = null;

	public FusionPrincipal(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param ident
	 */
	public FusionPrincipal(FusionIdentity ident){

	}

	public IIdentity Identity(){
		return null;
	}

	/**
	 * 
	 * @param role
	 */
	public Boolean IsInRole(String role){
		return null;
	}

}