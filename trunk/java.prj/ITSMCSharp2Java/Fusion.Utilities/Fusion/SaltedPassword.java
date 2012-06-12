package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:37
 */
public final class SaltedPassword {

	private int SALT_BYTELEN = 0x10;
	private int SHA1_BYTELEN = 20;

	public SaltedPassword(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param left
	 * @param right
	 */
	private static Boolean CompareByteArray(byte[] left, byte[] right){
		return null;
	}

	/**
	 * 
	 * @param cipherTextPassword
	 * @param plainTextPassword
	 */
	public static Boolean CompareSaltedPassword(String cipherTextPassword, String plainTextPassword){
		return null;
	}

	/**
	 * 
	 * @param plainTextPassword
	 * @param salt
	 */
	private static byte[] ComputeHashValue(String plainTextPassword, byte[] salt){
		return null;
	}

	/**
	 * 
	 * @param plainTextPassword
	 */
	public static String CreateSaltedPassword(String plainTextPassword){
		return "";
	}

}
