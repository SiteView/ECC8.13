package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 11:18:07
 */
public final class ByteUtils {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:07
	 */
	public class ByteAsTwoChars {

		private char m_cLowerNibble = '0';
		private char m_cUpperNibble = '0';

		public ByteAsTwoChars(){

		}

		public void finalize() throws Throwable {

		}

		public char LowerNibble(){
			return 0;
		}

		public char UpperNibble(){
			return 0;
		}

	}



	public void finalize() throws Throwable {

	}

	private ByteUtils(){

	}

	/**
	 * 
	 * @param ab
	 */
	public static String ByteArrayToString(byte[] ab){
		return "";
	}

	/**
	 * 
	 * @param b
	 */
	public static ByteAsTwoChars ByteToTwoChars(byte b){
		return null;
	}

	/**
	 * 
	 * @param c
	 */
	public static byte CharToNibble(char c){
		return 0;
	}

	/**
	 * 
	 * @param c
	 */
	private static Boolean IsHex(char c){
		return null;
	}

	/**
	 * 
	 * @param b
	 */
	public static char NibbleToChar(byte b){
		return 0;
	}

	/**
	 * 
	 * @param s
	 */
	public static byte[] StringToByteArray(String s){
		return null;
	}

	/**
	 * 
	 * @param tc
	 */
	public static byte TwoCharsToByte(ByteAsTwoChars tc){
		return 0;
	}

}