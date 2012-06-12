package Fusion.Api.FusionUpgrade;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:13
 */
public class ProgressEventArgs extends EventArgs {

	private int m_nCurrentValue;
	private int m_nMaxValue;
	private int m_nMinValue;
	private String m_strCurrentDefinition;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ProgressEventArgs(){

	}

	/**
	 * 
	 * @param nMinValue
	 * @param nMaxValue
	 * @param nCurrentValue
	 * @param currDef
	 */
	public ProgressEventArgs(int nMinValue, int nMaxValue, int nCurrentValue, String currDef){

	}

	public String CurrentDefinition(){
		return "";
	}

	public int CurrentValue(){
		return 0;
	}

	public int MaxValue(){
		return 0;
	}

	public int MinValue(){
		return 0;
	}

}