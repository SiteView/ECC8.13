package Fusion;

import java.util.Hashtable;

import Fusion.control.ILogicalThreadAffinative;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 11:18:10
 */
public class ContextAccess {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:10
	 */
	public class ContextString extends ILogicalThreadAffinative {

		private String m_str = "";

		public ContextString(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		/**
		 * 
		 * @param str
		 */
		public ContextString(String str){

		}

		public String ToString(){
			return "";
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:10
	 */
	public class HashtableHolder extends ILogicalThreadAffinative {

		private Hashtable m_ht = null;



		public void finalize() throws Throwable {
			super.finalize();
		}

		public HashtableHolder(){

		}

		public Hashtable Hashtable(){
			return null;
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:10
	 */
	public class PrincipleHolder extends ILogicalThreadAffinative {

		private FusionPrincipal m_fp = null;

		public PrincipleHolder(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		/**
		 * 
		 * @param fp
		 */
		public PrincipleHolder(FusionPrincipal fp){

		}

		public FusionPrincipal PrincipleObject(){
			return null;
		}

	}

	private static final String PrincipalSlotName = "Principal";



	public void finalize() throws Throwable {

	}

	protected ContextAccess(){

	}

	public static void GetPrincipleFromContext(){

	}

	public static void SetPrincipleToContext(){

	}

}