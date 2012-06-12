package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:54
 */
public interface ISearchParameter {

	public String SearchParameterCategoryType();

	public Object SearchParameterDefaultValue();

	public String SearchParameterId();

	public String SearchParameterName();

	public String SearchParameterType();

	public String SearchParameterUIMessage();

	public Object SearchParameterValue();

	public String ToXml();

}