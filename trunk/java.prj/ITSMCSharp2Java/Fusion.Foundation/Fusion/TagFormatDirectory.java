package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:34
 */
public class TagFormatDirectory {

	private static TagFormatDirectory m_Dir;
	private SortedList m_htTagFormatItemToDirectoryEntry = new SortedList();



	public void finalize() throws Throwable {

	}

	private TagFormatDirectory(){

	}

	private void AddCoreEntries(){

	}

	public static TagFormatDirectory Directory(){
		return null;
	}

	/**
	 * 
	 * @param strTagFormatItem
	 * @param strFormatterType
	 * @param strEditorType
	 */
	private void RegisterFactory(String strTagFormatItem, String strFormatterType, String strEditorType){

	}

	public Map TagFormatItemToDirectoryEntry(){
		return null;
	}

	/**
	 * 
	 * @param strTagFormatItem
	 */
	public TagFormatDirectoryEntry this(String strTagFormatItem){
		return null;
	}

}