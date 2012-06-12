package Fusion.Api;

import java.awt.Point;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:48
 */
public class ControlDef extends BllDefinitionObject {

	public ControlDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ControlDef(Object fusionObject){

	}

	public AnchorStyles Anchor(){
		return null;
	}

	public Map Annotations(){
		return null;
	}

	public void AssignDefaultValues(){

	}

	public String AssociatedFieldId(){
		return "";
	}

	public String AssociatedFieldName(){
		return "";
	}

	public String AssociatedGroupId(){
		return "";
	}

	public String AssociatedLabel(){
		return "";
	}

	public Fusion.Api.BackgroundDef BackgroundDef(){
		return null;
	}

	public String BorderColor(){
		return "";
	}

	public Fusion.Api.RuleDef BorderColorRule(){
		return null;
	}

	public System.Windows.Forms.BorderStyle BorderStyle(){
		return null;
	}

	public int BorderWeight(){
		return 0;
	}

	public Point BottomRight(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public System.Drawing.ContentAlignment ContentAlignment(){
		return null;
	}

	public ControlCategory ControlDefCategory(){
		return null;
	}

	public ControlCategory ControlHolderCategory(){
		return null;
	}

	/**
	 * 
	 * @param parent
	 * @param category
	 */
	public static Fusion.Api.ControlDef Create(Fusion.Api.PanelDef parent, ControlCategory category){
		return null;
	}

	/**
	 * 
	 * @param pdParent
	 * @param element
	 */
	public static Fusion.Api.ControlDef CreateFromXml(Fusion.Api.PanelDef pdParent, XmlElement element){
		return null;
	}

	public System.Drawing.Font Font(){
		return null;
	}

	public String FontKey(){
		return "";
	}

	public Fusion.Xml.FontSource FontSource(){
		return null;
	}

	public String Foreground(){
		return "";
	}

	public Fusion.Api.RuleDef ForegroundRule(){
		return null;
	}

	/**
	 * 
	 * @param fldDef
	 */
	public static ControlCategory GetPrimaryDefinitionType(Fusion.Api.FieldDef fldDef){
		return null;
	}

	/**
	 * 
	 * @param fldDef
	 */
	public static List GetSupportedDefinitionTypes(Fusion.Api.FieldDef fldDef){
		return null;
	}

	public Point LocationInPixels(){
		return null;
	}

	public Fusion.Api.PanelDef Parent(){
		return null;
	}

	public Size SizeInPixels(){
		return null;
	}

	public Fusion.Api.RuleDef SolidBackgroundRule(){
		return null;
	}

	public boolean SupportsTransparentBackground(){
		return null;
	}

	public int TabIndex(){
		return 0;
	}

	public boolean TabStop(){
		return null;
	}

	public Fusion.Api.RuleDef VisibleRule(){
		return null;
	}

	public boolean WebPostBack(){
		return null;
	}

	private Fusion.Presentation.ControlDef WhoAmI(){
		return null;
	}

	public int ZOrder(){
		return 0;
	}

}