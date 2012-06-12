package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:45:12
 */
public class PresentationRegionDef extends RegionDef {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:45:12
	 */
	public class ViewHolder {

		private ArrayList<String> m_colExcludedGroupMembers = null;
		private String m_strAllowedViews = "";
		private String m_strDefaultView = "";
		private String m_strFormId = "";
		private String m_strFormName = "";
		private String m_strGridId = "";
		private String m_strGridName = "";
		private String m_strModuleSnapInID = "";
		private String m_strModuleSnapInName = "";

		public ViewHolder(){

		}

		public void finalize() throws Throwable {

		}

		public String AllowedViews(){
			return "";
		}

		public String DefaultView(){
			return "";
		}

		public ArrayList<String> ExcludedGroupMembers(){
			return null;
		}

		public String FormId(){
			return "";
		}

		public String FormName(){
			return "";
		}

		public String GridId(){
			return "";
		}

		public String GridName(){
			return "";
		}

		public String ModuleSnapInId(){
			return "";
		}

		public String ModuleSnapInName(){
			return "";
		}

	}

	public PresentationRegionDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public PresentationRegionDef(Object fusionObject){

	}

	public boolean AllowAdd(){
		return false;
	}

	public boolean AllowDelete(){
		return false;
	}

	public boolean AllowEdit(){
		return false;
	}

	public boolean AllowGoto(){
		return false;
	}

	public boolean AllowLink(){
		return false;
	}

	public boolean AllowPrint(){
		return false;
	}

	public boolean AllowSearchLink(){
		return false;
	}

	public boolean AllowUnLink(){
		return false;
	}

	public static String ClassName(){
		return "";
	}

	public ConstraintDefContainer ConstraintDefs(){
		return null;
	}

	public ViewHolder CurrentViewHolder(){
		return null;
	}

	public ArrayList<String> ExludedGroupMembers(){
		return null;
	}

	public String GridId(){
		return "";
	}

	public String GridName(){
		return "";
	}

	public String GridRelationship(){
		return "";
	}

	public boolean HideToolbar(){
		return false;
	}

	public String ModuleSnapInID(){
		return "";
	}

	public String ModuleSnapInName(){
		return "";
	}

	public String PanelId(){
		return "";
	}

	public String PanelName(){
		return "";
	}

	private Fusion.Presentation.PresentationRegionDef WhoAmI(){
		return null;
	}

}