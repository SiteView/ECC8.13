package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:35
 */
public abstract class FusionAggregate extends AggregateBase {

	private Object m_fusionObject;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public FusionAggregate(){

	}

	/**
	 * 
	 * @param fusionObject
	 */
	public FusionAggregate(Object fusionObject){

	}

	public static String ClassName(){
		return "";
	}

	public Object FusionObject(){
		return null;
	}

	/**
	 * 
	 * @param binaryFieldDefRights
	 */
	protected Fusion.Api.BinaryFieldDefRights GetAggregate(Fusion.BusinessLogic.BinaryFieldDefRights binaryFieldDefRights){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 */
	public static Fusion.Api.BusinessObject GetAggregate(Fusion.BusinessLogic.BusinessObject busOb){
		return null;
	}

	/**
	 * 
	 * @param busObDef
	 */
	protected Fusion.Api.BusinessObjectDef GetAggregate(Fusion.BusinessLogic.BusinessObjectDef busObDef){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.BusinessProcessDef GetAggregate(Fusion.BusinessLogic.BusinessProcessDef def){
		return null;
	}

	/**
	 * 
	 * @param busObDefRights
	 */
	protected Fusion.Api.BusObDefRights GetAggregate(Fusion.BusinessLogic.BusObDefRights busObDefRights){
		return null;
	}

	/**
	 * 
	 * @param constraint
	 */
	protected Fusion.Api.ConstraintDef GetAggregate(Fusion.BusinessLogic.ConstraintDef constraint){
		return null;
	}

	/**
	 * 
	 * @param cdef
	 */
	protected Fusion.Api.ConstraintDefContainer GetAggregate(Fusion.BusinessLogic.ConstraintDefContainer cdef){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.CounterDef GetAggregate(Fusion.BusinessLogic.CounterDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.CriteriaDef GetAggregate(Fusion.BusinessLogic.CriteriaDef def){
		return null;
	}

	/**
	 * 
	 * @param defMgr
	 */
	protected static Fusion.Api.DefLibraryConnectionDefMgr GetAggregate(Fusion.BusinessLogic.DefLibraryConnectionDefMgr defMgr){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.ElementDef GetAggregate(Fusion.BusinessLogic.ElementDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.EventDef GetAggregate(Fusion.BusinessLogic.EventDef def){
		return null;
	}

	/**
	 * 
	 * @param field
	 */
	protected Fusion.Api.Field GetAggregate(Fusion.BusinessLogic.Field field){
		return null;
	}

	/**
	 * 
	 * @param fieldDef
	 */
	protected Fusion.Api.FieldDef GetAggregate(Fusion.BusinessLogic.FieldDef fieldDef){
		return null;
	}

	/**
	 * 
	 * @param fldContainer
	 */
	protected Fusion.Api.DefinitionObject GetAggregate(FieldDefContainer fldContainer){
		return null;
	}

	/**
	 * 
	 * @param fieldDefRights
	 */
	protected Fusion.Api.FieldDefRights GetAggregate(Fusion.BusinessLogic.FieldDefRights fieldDefRights){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.FieldEventDef GetAggregate(Fusion.BusinessLogic.FieldEventDef def){
		return null;
	}

	/**
	 * 
	 * @param formatDef
	 */
	protected Fusion.Api.FormatDef GetAggregate(Fusion.BusinessLogic.FormatDef formatDef){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.HoursOfOperationDef GetAggregate(Fusion.BusinessLogic.HoursOfOperationDef def){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.HoursOfOperationExemptionDef GetAggregate(Fusion.BusinessLogic.HoursOfOperationExemptionDef def){
		return null;
	}

	/**
	 * 
	 * @param defPerspective
	 */
	protected Fusion.Api.PerspectiveDef GetAggregate(Fusion.BusinessLogic.PerspectiveDef defPerspective){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.ReferenceDef GetAggregate(Fusion.BusinessLogic.ReferenceDef def){
		return null;
	}

	/**
	 * 
	 * @param rel
	 */
	protected Fusion.Api.Relationship GetAggregate(Fusion.BusinessLogic.Relationship rel){
		return null;
	}

	/**
	 * 
	 * @param relDef
	 */
	protected Fusion.Api.RelationshipDef GetAggregate(Fusion.BusinessLogic.RelationshipDef relDef){
		return null;
	}

	/**
	 * 
	 * @param relationshipDefRights
	 */
	protected Fusion.Api.RelationshipDefRights GetAggregate(Fusion.BusinessLogic.RelationshipDefRights relationshipDefRights){
		return null;
	}

	/**
	 * 
	 * @param role
	 */
	public static Fusion.Api.RoleDef GetAggregate(Fusion.BusinessLogic.RoleDef role){
		return null;
	}

	/**
	 * 
	 * @param rollUp
	 */
	protected Fusion.Api.RollUpDef GetAggregate(Fusion.BusinessLogic.RollUpDef rollUp){
		return null;
	}

	/**
	 * 
	 * @param rollUpLevel
	 */
	protected Fusion.Api.RollUpLevel GetAggregate(Fusion.BusinessLogic.RollUpLevel rollUpLevel){
		return null;
	}

	/**
	 * 
	 * @param val
	 */
	protected Fusion.Api.EvaluationBundle GetAggregate(Fusion.BusinessLogic.Rules.EvaluationBundle val){
		return null;
	}

	/**
	 * 
	 * @param val
	 */
	protected ValueSource GetAggregate(LiteralValue val){
		return null;
	}

	/**
	 * 
	 * @param rule
	 */
	public static Fusion.Api.RuleDef GetAggregate(Fusion.BusinessLogic.Rules.RuleDef rule){
		return null;
	}

	/**
	 * 
	 * @param textFieldDefRights
	 */
	protected Fusion.Api.TextFieldDefRights GetAggregate(Fusion.BusinessLogic.TextFieldDefRights textFieldDefRights){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected static Fusion.Api.TokenDef GetAggregate(Fusion.BusinessLogic.TokenDef def){
		return null;
	}

	/**
	 * 
	 * @param hints
	 */
	protected Fusion.Api.DbEngineHints GetAggregate(Fusion.DbEngineHints hints){
		return null;
	}

	/**
	 * 
	 * @param hint
	 */
	protected Fusion.Api.DbHint GetAggregate(Fusion.DbHint hint){
		return null;
	}

	/**
	 * 
	 * @param mgrDbHints
	 */
	protected Fusion.Api.DbHintManager GetAggregate(Fusion.DbHintManager mgrDbHints){
		return null;
	}

	/**
	 * 
	 * @param def
	 */
	protected Fusion.Api.DefinitionObject GetAggregate(Fusion.DefinitionObject def){
		return null;
	}

	/**
	 * 
	 * @param defRights
	 */
	protected Fusion.Api.DefRights GetAggregate(Fusion.DefRights defRights){
		return null;
	}

	/**
	 * 
	 * @param backgroundDef
	 */
	protected Fusion.Api.BackgroundDef GetAggregate(Fusion.Presentation.BackgroundDef backgroundDef){
		return null;
	}

	/**
	 * 
	 * @param buttonControlDef
	 */
	protected static Fusion.Api.ButtonControlDef GetAggregate(Fusion.Presentation.ButtonControlDef buttonControlDef){
		return null;
	}

	/**
	 * 
	 * @param columnDef
	 */
	protected Fusion.Api.ColumnDef GetAggregate(Fusion.Presentation.ColumnDef columnDef){
		return null;
	}

	/**
	 * 
	 * @param controldef
	 */
	protected static Fusion.Api.ControlDef GetAggregate(Fusion.Presentation.ControlDef controldef){
		return null;
	}

	/**
	 * 
	 * @param dateControlDef
	 */
	protected static Fusion.Api.DateControlDef GetAggregate(Fusion.Presentation.DateControlDef dateControlDef){
		return null;
	}

	/**
	 * 
	 * @param dateTimeControlDef
	 */
	protected static Fusion.Api.DateTimeControlDef GetAggregate(Fusion.Presentation.DateTimeControlDef dateTimeControlDef){
		return null;
	}

	/**
	 * 
	 * @param edgeBannerControlDef
	 */
	protected static Fusion.Api.EdgeBannerControlDef GetAggregate(Fusion.Presentation.EdgeBannerControlDef edgeBannerControlDef){
		return null;
	}

	/**
	 * 
	 * @param gridDef
	 */
	protected Fusion.Api.GridDef GetAggregate(Fusion.Presentation.GridDef gridDef){
		return null;
	}

	/**
	 * 
	 * @param groupboxControlDef
	 */
	protected static Fusion.Api.GroupboxControlDef GetAggregate(Fusion.Presentation.GroupboxControlDef groupboxControlDef){
		return null;
	}

	/**
	 * 
	 * @param groupDef
	 */
	protected Fusion.Api.GroupDef GetAggregate(Fusion.Presentation.GroupDef groupDef){
		return null;
	}

	/**
	 * 
	 * @param imageDef
	 */
	protected Fusion.Api.ImageDef GetAggregate(Fusion.Presentation.ImageDef imageDef){
		return null;
	}

	/**
	 * 
	 * @param labelControlDef
	 */
	protected static Fusion.Api.LabelControlDef GetAggregate(Fusion.Presentation.LabelControlDef labelControlDef){
		return null;
	}

	/**
	 * 
	 * @param labelMenuControlDef
	 */
	protected static Fusion.Api.LabelMenuControlDef GetAggregate(Fusion.Presentation.LabelMenuControlDef labelMenuControlDef){
		return null;
	}

	/**
	 * 
	 * @param layoutDef
	 */
	protected Fusion.Api.LayoutDef GetAggregate(Fusion.Presentation.LayoutDef layoutDef){
		return null;
	}

	/**
	 * 
	 * @param linkLabelControlDef
	 */
	protected static Fusion.Api.LinkLabelControlDef GetAggregate(Fusion.Presentation.LinkLabelControlDef linkLabelControlDef){
		return null;
	}

	/**
	 * 
	 * @param logicalControlDef
	 */
	protected static Fusion.Api.LogicalControlDef GetAggregate(Fusion.Presentation.LogicalControlDef logicalControlDef){
		return null;
	}

	/**
	 * 
	 * @param nsControlDef
	 */
	protected static Fusion.Api.NameSplitterControlDef GetAggregate(Fusion.Presentation.NameSplitterControlDef nsControlDef){
		return null;
	}

	/**
	 * 
	 * @param numberControlDef
	 */
	protected static Fusion.Api.NumberControlDef GetAggregate(Fusion.Presentation.NumberControlDef numberControlDef){
		return null;
	}

	/**
	 * 
	 * @param objectRegionDef
	 */
	protected Fusion.Api.ObjectRegionDef GetAggregate(Fusion.Presentation.ObjectRegionDef objectRegionDef){
		return null;
	}

	/**
	 * 
	 * @param panelDef
	 */
	protected static Fusion.Api.PanelDef GetAggregate(Fusion.Presentation.PanelDef panelDef){
		return null;
	}

	/**
	 * 
	 * @param pictureControlDef
	 */
	protected static Fusion.Api.PictureControlDef GetAggregate(Fusion.Presentation.PictureControlDef pictureControlDef){
		return null;
	}

	/**
	 * 
	 * @param presentationRegionDef
	 */
	protected Fusion.Api.PresentationRegionDef GetAggregate(Fusion.Presentation.PresentationRegionDef presentationRegionDef){
		return null;
	}

	/**
	 * 
	 * @param radioButtonControlDef
	 */
	protected static Fusion.Api.RadioButtonControlDef GetAggregate(Fusion.Presentation.RadioButtonControlDef radioButtonControlDef){
		return null;
	}

	/**
	 * 
	 * @param regionDef
	 */
	protected Fusion.Api.RegionDef GetAggregate(Fusion.Presentation.RegionDef regionDef){
		return null;
	}

	/**
	 * 
	 * @param scopedItemSelectorDef
	 */
	protected static Fusion.Api.ScopedItemSelectorDef GetAggregate(Fusion.Presentation.ScopedItemSelectorDef scopedItemSelectorDef){
		return null;
	}

	/**
	 * 
	 * @param shapeControlDef
	 */
	protected static Fusion.Api.ShapeControlDef GetAggregate(Fusion.Presentation.ShapeControlDef shapeControlDef){
		return null;
	}

	/**
	 * 
	 * @param splitterRegionDef
	 */
	protected Fusion.Api.SplitterRegionDef GetAggregate(Fusion.Presentation.SplitterRegionDef splitterRegionDef){
		return null;
	}

	/**
	 * 
	 * @param tabbedRegionDef
	 */
	protected Fusion.Api.TabbedRegionDef GetAggregate(Fusion.Presentation.TabbedRegionDef tabbedRegionDef){
		return null;
	}

	/**
	 * 
	 * @param tabDef
	 */
	protected Fusion.Api.TabDef GetAggregate(Fusion.Presentation.TabDef tabDef){
		return null;
	}

	/**
	 * 
	 * @param textControlDef
	 */
	protected static Fusion.Api.TextControlDef GetAggregate(Fusion.Presentation.TextControlDef textControlDef){
		return null;
	}

	/**
	 * 
	 * @param timeControlDef
	 */
	protected static Fusion.Api.TimeControlDef GetAggregate(Fusion.Presentation.TimeControlDef timeControlDef){
		return null;
	}

	/**
	 * 
	 * @param obj
	 */
	private Object GetAggregate(Object obj){
		return null;
	}

	public Object UnprotectedFusionObject(){
		return null;
	}

	private Object WhoAmI(){
		return null;
	}

}