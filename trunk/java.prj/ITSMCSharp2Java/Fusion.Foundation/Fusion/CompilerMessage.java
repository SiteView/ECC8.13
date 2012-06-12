package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:52
 */
public class CompilerMessage {

	private int m_intEndColumn;
	private int m_intLine;
	private int m_intNumber;
	private int m_intSeverity;
	private int m_intStartColumn;
	private String m_strDescription;
	private String m_strLineText;
	private String m_strSeverityText;
	private String m_strSourceMoniker;
	private String MessageDisplayFormat = "{0} {1} ({2},{3}): {4}";

	public CompilerMessage(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param number
	 * @param severity
	 * @param description
	 * @param line
	 * @param startColumn
	 * @param endColumn
	 * @param sourceMoniker
	 * @param lineText
	 */
	public CompilerMessage(int number, int severity, String description, int line, int startColumn, int endColumn, String sourceMoniker, String lineText){

	}

	public String Description(){
		return "";
	}

	public int EndColumn(){
		return 0;
	}

	public int Line(){
		return 0;
	}

	public String LineText(){
		return "";
	}

	public int Number(){
		return 0;
	}

	public int Severity(){
		return 0;
	}

	public String SeverityText(){
		return "";
	}

	public String SourceMoniker(){
		return "";
	}

	public int StartColumn(){
		return 0;
	}

	public String ToString(){
		return "";
	}

}