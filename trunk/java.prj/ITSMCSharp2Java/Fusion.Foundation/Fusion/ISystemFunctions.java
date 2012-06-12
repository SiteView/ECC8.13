package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:58
 */
public interface ISystemFunctions {

	public DateTime CurrentDate();

	public DateTime CurrentDateTime();

	public String CurrentLoginId();

	public String CurrentSecurityGroup();

	public String CurrentSecurityGroupId();

	public String CurrentUserBusinessUnit();

	public String CurrentUserEmailAddress();

	public String CurrentUserName();

	public String CurrentUserRecId();

	public String CurrentUserTeam();

	public String CurrentUserType();

	public String DefaultUserName();

	public String DefaultUserRecId();

	public String DefaultUserTeam();

	public String DefaultUserType();

	public DateTime EndOfLastMonth();

	public DateTime EndOfLastQuarter();

	public DateTime EndOfLastWeek();

	public DateTime EndOfLastYear();

	public DateTime EndOfNextMonth();

	public DateTime EndOfNextQuarter();

	public DateTime EndOfNextWeek();

	public DateTime EndOfNextYear();

	public DateTime EndOfThisMonth();

	public DateTime EndOfThisQuarter();

	public DateTime EndOfThisWeek();

	public DateTime EndOfThisYear();

	/**
	 * 
	 * @param strFunction
	 */
	public ISystemFunction GetSystemFunction(String strFunction);

	/**
	 * 
	 * @param strFunction
	 * @param scope
	 */
	public ISystemFunction GetSystemFunction(String strFunction, Scope scope);

	/**
	 * 
	 * @param strFunction
	 */
	public SystemFunctionValueType GetSystemFunctionDataType(String strFunction);

	/**
	 * 
	 * @param strFunction
	 * @param scope
	 */
	public SystemFunctionValueType GetSystemFunctionDataType(String strFunction, Scope scope);

	/**
	 * 
	 * @param strFunction
	 */
	public FusionValue GetSystemValue(String strFunction);

	public List ListOfSystemFunctionExtensions();

	public List ListOfSystemFunctions();

	public List ListOfSystemPromptTypes();

	public DateTime StartOfLastMonth();

	public DateTime StartOfLastQuarter();

	public DateTime StartOfLastWeek();

	public DateTime StartOfLastYear();

	public DateTime StartOfNextMonth();

	public DateTime StartOfNextQuarter();

	public DateTime StartOfNextWeek();

	public DateTime StartOfNextYear();

	public DateTime StartOfThisMonth();

	public DateTime StartOfThisQuarter();

	public DateTime StartOfThisWeek();

	public DateTime StartOfThisYear();

	public DateTime Tomorrow();

	public DateTime Yesterday();

}