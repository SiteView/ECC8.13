package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:18
 */
public class ExportImportTableEventArgs extends FusionAggregate {

	public ExportImportTableEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ExportImportTableEventArgs(Object fusionObject){

	}

	public String TableName(){
		return "";
	}

	public int TableNumber(){
		return 0;
	}

	public int TotalNumberOfTables(){
		return 0;
	}

	private Fusion.BusinessLogic.ExportImportTableEventArgs WhoAmI(){
		return null;
	}

}