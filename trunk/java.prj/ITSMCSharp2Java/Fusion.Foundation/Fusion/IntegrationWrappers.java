package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:51
 */
public class IntegrationWrappers {

	private String ExcelTypeName = "ExcelWrapper";
	private String IntegrationAssemblyName = "Fusion.OfficeIntegration";
	private static Assembly m_assembly;
	private static ConstructorInfo m_constructor;
	private static Type m_type;

	public IntegrationWrappers(){

	}

	public void finalize() throws Throwable {

	}

	public static IExcelWrapper GetExcelWrapper(){
		return null;
	}

	private static ConstructorInfo GetWrapperConstructorInfo(){
		return null;
	}

}