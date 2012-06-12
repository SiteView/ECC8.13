package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:57
 */
public interface ISystemFunction extends IDefinition {

	/**
	 * 
	 * @param dictParameters
	 */
	public void AddParameter(IDictionary dictParameters);

	/**
	 * 
	 * @param strName
	 * @param value
	 */
	public void AddParameter(String strName, Object value);

	public String Category();

	public SystemFunctionValueType DataType();

	/**
	 * 
	 * @param strXml
	 */
	public void FromXml(String strXml);

	public Map NamedParameters();

	/**
	 * 
	 * @param strName
	 */
	public void RemoveParameter(String strName);

	/**
	 * 
	 * @param funct
	 */
	public void Update(ISystemFunction funct);

	/**
	 * 
	 * @param strName
	 * @param value
	 */
	public void UpdateParameter(String strName, Object value);

	public Object Value();

}