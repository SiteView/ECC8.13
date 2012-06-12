package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:33
 */
public class PreLoadConfiguration {

	private boolean m_blnEnabled;
	private AssemblyEntryConfiguration m_cfgAssemblyEntries[];
	private Fusion.ProgressConfiguration m_cfgProgress;
	private String m_strAssemblySource;

	public PreLoadConfiguration(){

	}

	public void finalize() throws Throwable {

	}

	public AssemblyEntryConfiguration[] AssemblyEntries(){
		return null;
	}

	public String AssemblySource(){
		return "";
	}

	public boolean Enabled(){
		return null;
	}

	public Fusion.ProgressConfiguration ProgressConfiguration(){
		return null;
	}

}