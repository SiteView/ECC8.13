package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:58
 */
public interface ITagFormatter {

	public boolean ApplyLast();

	/**
	 * 
	 * @param val
	 * @param format
	 */
	public FusionValue Format(FusionValue val, TagFormat format);

}