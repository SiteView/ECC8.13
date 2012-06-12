package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:43
 */
public class AutoConnectConfiguration {

	private boolean m_blnEnabled;
	private DefinitionCacheLevel m_cacheLevel;
	private Fusion.CompressionLevel m_compressionLevel;
	private String m_strAppServerUrl;
	private String m_strConnectionDescription;
	private String m_strConnectionId;
	private String m_strConnectionName;

	public AutoConnectConfiguration(){

	}

	public void finalize() throws Throwable {

	}

	public String AppServerUrl(){
		return "";
	}

	public DefinitionCacheLevel CacheLevel(){
		return null;
	}

	public Fusion.CompressionLevel CompressionLevel(){
		return null;
	}

	public String ConnectionDescription(){
		return "";
	}

	public String ConnectionId(){
		return "";
	}

	public String ConnectionName(){
		return "";
	}

	public boolean Enabled(){
		return null;
	}

}