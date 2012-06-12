package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:17
 */
public class NotificationCategories {

	private String AboutToSave = "AboutToSave";
	private String AfterSave = "AfterSave";
	private String AuditingRecordsCreated = "AuditingRecordsCreated";
	private String AutoFill = "AutoFill";
	private String BackgroundChange = "BackgroundChange";
	private String BackgroundChangeFirstColor = "BackgroundChange:FirstColor";
	private String BackgroundChangeImage = "BackgroundChange:Image";
	private String BackgroundChangeSecondColor = "BackgroundChange:SecondColor";
	private String BPEventObCreated = "BPEventObjectCreated";
	private String BPEventObDeleted = "BPEventObjectDeleted";
	private String BPEventObRetrieved = "BPEventObjectRetrieved";
	private String BPEventObUpdated = "BPEventObjectUpdated";
	private String Calculate = "Calculate";
	private String ConstraintsChanged = "ConstraintsChanged";
	private String Control = "Control";
	private String ControlBackgroundChangeFirstColor = "ControlBackgroundChange:FirstColor";
	private String ControlBackgroundChangeImage = "ControlBackgroundChange:Image";
	private String ControlBackgroundChangeSecondColor = "ControlBackgroundChange:SecondColor";
	private String ControlChangeAlignment = "ControlChange:Alignment";
	private String ControlChangeAnchor = "ControlChange:Anchor";
	private String ControlChangeBorderColor = "ControlChange:BorderColor";
	private String ControlChangeBorderWeight = "ControlChange:BorderWeight";
	private String ControlChangeButtonImage = "ControlChange:ButtonImage";
	private String ControlChangeButtonText = "ControlChange:ButtonText";
	private String ControlChangeFont = "ControlChange:Font";
	private String ControlChangeForeground = "ControlChange:Foreground";
	private String ControlChangeGroupboxText = "ControlChange:GroupboxText";
	private String ControlChangeLabelText = "ControlChange:LabelText";
	private String ControlChangeLinkImage = "ControlChange:LinkImage";
	private String ControlChangeLinkText = "ControlChange:LinkText";
	private String ControlChangeNameSplitter = "ControlChange:NameSplitter";
	private String ControlChangePictureImage = "ControlChange:PictureImage";
	private String ControlChangeReadOnly = "ControlChange:ReadOnly";
	private String ControlChangeSizeOrPosition = "ControlChange:SizeOfPosition";
	private String ControlChangeSpinner = "ControlChange:Spinner";
	private String ControlChangeText = "ControlChange:Text";
	private String ControlChangeTextCombo = "ControlChange:TextCombo";
	private String ControlChangeVisible = "ControlChange:Visible";
	private String Flags = "DisplayFlags";
	private String Form = "Form";
	private String GridCellChangeBackgroundColor = "GridCellChangeBackgroundColor";
	private String GridCellChangeBorderColor = "GridCellChangeBorderColor";
	private String GridCellChangeImage = "GridCellChangeImage";
	private String GridCellChangeTextColor = "GridCellChangeTextColor";
	private String GridCurrentRowChange = "GridCurrentRowChange";
	private String GridDataSourceReloadRebind = "GridDataSourceReloadRebind";
	private String GridHeaderChanged = "GridHeaderChanged";
	private String GridRowAdd = "GridRowAdded";
	private String GridRowChange = "GridRowChanged";
	private String GridRowChangeBackgroundColor = "GridRowChangeBackgroundColor";
	private String GridRowChangeBorderColor = "GridRowChangeBorderColor";
	private String GridRowChangeImage = "GridRowChangeImage";
	private String GridRowChangeTextColor = "GridRowChangeTextColor";
	private String GridRowDataSourceRefresh = "GridRowDataSourceRefresh";
	private String GridRowRemove = "GridRowRemoved";
	private String LayoutMultiPartReloadRegions = "MultiPartRegion:ReloadRegions";
	private String LayoutPresentationChangedView = "PresentationRegion:ChangeView";
	private String LayoutPresentationChangeForm = "PresentationRegion:ChangeForm";
	private String LayoutPresentationChangeGrid = "PresentationRegion:ChangeGrid";
	private String LayoutPresentationChangeRelationship = "PresentationRegion:ChangeRelationship";
	private String LayoutPresentationChangeToolbar = "PresentationRegion:ChangeToolbar";
	private String LayoutPresentationSwapViews = "PresentationRegion:SwapViews";
	private String LayoutSplitChangeOrientation = "SplitRegion:ChangeOrientation";
	private String LayoutSplitChangeSplitBehaviour = "SplitRegion:ChangeSplitBehaviour";
	private String LayoutSplitChangeSplitColor = "SplitRegion:ChangeSplitColor";
	private String LayoutSplitChangeSplitterSize = "SplitRegion:ChangeSplitterSize";
	private String LayoutTabChangeDescription = "TabRegion:ChangeDescription";
	private String LayoutTabChangeEnabled = "TabRegion:ChangeEnabled";
	private String LayoutTabChangeImage = "TabRegion:ChangeImage";
	private String LayoutTabChangeTabPositions = "TabRegion:ChangeTabPositions";
	private String LayoutTabChangeText = "TabRegion:ChangeText";
	private String LayoutTabChangeVisible = "TabRegion:ChangeVisible";
	private String OtherColorChanged = "ControlChange:OtherColorChanged";
	private String ReadOnlyChange = "ReadOnlyChange";
	private String RelationshipAboutToChangeCurrentObject = "RelationshipAboutToChangeCurrentObject";
	private String RelationshipModifiedCurrentObject = "RelationshipModifiedCurrentObject";
	private String RelationshipSwitchHandlerChange = "RelationshipSwitchHandlerChange";
	private String RelationshipTypeChange = "RelationshipTypeChange";
	private String scrFieldPropertyReadOnly = "FieldProperty#ReadOnly:";
	private String scrFieldValidationConstraintChanged = "FieldValidation#ConstraintChanged:";
	private String srcAuditingModified = "Auditing#CModified";
	private String srcBusOb = "BusOb:";
	private String srcBusObAfterSave = "BusOb#AfterSave:";
	private String srcBusObBeforeSave = "BusOb#BeforeSave:";
	private String srcField = "Field:";
	private String srcRelationshipAdded = "Relationship#Added:";
	private String srcRelationshipChanged = "Relationship#Changed:";
	private String srcRelationshipCurrent = "Relationship#Current:";
	private String srcRelationshipCurrentAboutToChange = "Relationship#CurrentAboutToChange:";
	private String srcRelationshipCurrentModified = "Relationship#CurrentModified";
	private String srcRelationshipDataSourceRefresh = "Relationship#DataSourceRefresh:";
	private String srcRelationshipDataSourceReloadRebind = "Relationship#DataSourceReloadRebind:";
	private String srcRelationshipRemoved = "Relationship#Removed:";
	private String StateChange = "StateChange";
	private String UpdateControlDisplay = "UpdateControlDisplay";
	private String ValidationChange = "ValidationChange";

	public NotificationCategories(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strCode
	 * @param strSource
	 */
	public static String BuildSource(String strCode, String strSource){
		return "";
	}

	public String getAboutToSave(){
		return AboutToSave;
	}

	public String getAfterSave(){
		return AfterSave;
	}

	public String getAuditingRecordsCreated(){
		return AuditingRecordsCreated;
	}

	public String getAutoFill(){
		return AutoFill;
	}

	public String getBackgroundChange(){
		return BackgroundChange;
	}

	public String getBackgroundChangeFirstColor(){
		return BackgroundChangeFirstColor;
	}

	public String getBackgroundChangeImage(){
		return BackgroundChangeImage;
	}

	public String getBackgroundChangeSecondColor(){
		return BackgroundChangeSecondColor;
	}

	public String getBPEventObCreated(){
		return BPEventObCreated;
	}

	public String getBPEventObDeleted(){
		return BPEventObDeleted;
	}

	public String getBPEventObRetrieved(){
		return BPEventObRetrieved;
	}

	public String getBPEventObUpdated(){
		return BPEventObUpdated;
	}

	public String getCalculate(){
		return Calculate;
	}

	public String getConstraintsChanged(){
		return ConstraintsChanged;
	}

	public String getControl(){
		return Control;
	}

	public String getControlBackgroundChangeFirstColor(){
		return ControlBackgroundChangeFirstColor;
	}

	public String getControlBackgroundChangeImage(){
		return ControlBackgroundChangeImage;
	}

	public String getControlBackgroundChangeSecondColor(){
		return ControlBackgroundChangeSecondColor;
	}

	public String getControlChangeAlignment(){
		return ControlChangeAlignment;
	}

	public String getControlChangeAnchor(){
		return ControlChangeAnchor;
	}

	public String getControlChangeBorderColor(){
		return ControlChangeBorderColor;
	}

	public String getControlChangeBorderWeight(){
		return ControlChangeBorderWeight;
	}

	public String getControlChangeButtonImage(){
		return ControlChangeButtonImage;
	}

	public String getControlChangeButtonText(){
		return ControlChangeButtonText;
	}

	public String getControlChangeFont(){
		return ControlChangeFont;
	}

	public String getControlChangeForeground(){
		return ControlChangeForeground;
	}

	public String getControlChangeGroupboxText(){
		return ControlChangeGroupboxText;
	}

	public String getControlChangeLabelText(){
		return ControlChangeLabelText;
	}

	public String getControlChangeLinkImage(){
		return ControlChangeLinkImage;
	}

	public String getControlChangeLinkText(){
		return ControlChangeLinkText;
	}

	public String getControlChangeNameSplitter(){
		return ControlChangeNameSplitter;
	}

	public String getControlChangePictureImage(){
		return ControlChangePictureImage;
	}

	public String getControlChangeReadOnly(){
		return ControlChangeReadOnly;
	}

	public String getControlChangeSizeOrPosition(){
		return ControlChangeSizeOrPosition;
	}

	public String getControlChangeSpinner(){
		return ControlChangeSpinner;
	}

	public String getControlChangeText(){
		return ControlChangeText;
	}

	public String getControlChangeTextCombo(){
		return ControlChangeTextCombo;
	}

	public String getControlChangeVisible(){
		return ControlChangeVisible;
	}

	public String getFlags(){
		return Flags;
	}

	public String getForm(){
		return Form;
	}

	public String getGridCellChangeBackgroundColor(){
		return GridCellChangeBackgroundColor;
	}

	public String getGridCellChangeBorderColor(){
		return GridCellChangeBorderColor;
	}

	public String getGridCellChangeImage(){
		return GridCellChangeImage;
	}

	public String getGridCellChangeTextColor(){
		return GridCellChangeTextColor;
	}

	public String getGridCurrentRowChange(){
		return GridCurrentRowChange;
	}

	public String getGridDataSourceReloadRebind(){
		return GridDataSourceReloadRebind;
	}

	public String getGridHeaderChanged(){
		return GridHeaderChanged;
	}

	public String getGridRowAdd(){
		return GridRowAdd;
	}

	public String getGridRowChange(){
		return GridRowChange;
	}

	public String getGridRowChangeBackgroundColor(){
		return GridRowChangeBackgroundColor;
	}

	public String getGridRowChangeBorderColor(){
		return GridRowChangeBorderColor;
	}

	public String getGridRowChangeImage(){
		return GridRowChangeImage;
	}

	public String getGridRowChangeTextColor(){
		return GridRowChangeTextColor;
	}

	public String getGridRowDataSourceRefresh(){
		return GridRowDataSourceRefresh;
	}

	public String getGridRowRemove(){
		return GridRowRemove;
	}

	public String getLayoutMultiPartReloadRegions(){
		return LayoutMultiPartReloadRegions;
	}

	public String getLayoutPresentationChangedView(){
		return LayoutPresentationChangedView;
	}

	public String getLayoutPresentationChangeForm(){
		return LayoutPresentationChangeForm;
	}

	public String getLayoutPresentationChangeGrid(){
		return LayoutPresentationChangeGrid;
	}

	public String getLayoutPresentationChangeRelationship(){
		return LayoutPresentationChangeRelationship;
	}

	public String getLayoutPresentationChangeToolbar(){
		return LayoutPresentationChangeToolbar;
	}

	public String getLayoutPresentationSwapViews(){
		return LayoutPresentationSwapViews;
	}

	public String getLayoutSplitChangeOrientation(){
		return LayoutSplitChangeOrientation;
	}

	public String getLayoutSplitChangeSplitBehaviour(){
		return LayoutSplitChangeSplitBehaviour;
	}

	public String getLayoutSplitChangeSplitColor(){
		return LayoutSplitChangeSplitColor;
	}

	public String getLayoutSplitChangeSplitterSize(){
		return LayoutSplitChangeSplitterSize;
	}

	public String getLayoutTabChangeDescription(){
		return LayoutTabChangeDescription;
	}

	public String getLayoutTabChangeEnabled(){
		return LayoutTabChangeEnabled;
	}

	public String getLayoutTabChangeImage(){
		return LayoutTabChangeImage;
	}

	public String getLayoutTabChangeTabPositions(){
		return LayoutTabChangeTabPositions;
	}

	public String getLayoutTabChangeText(){
		return LayoutTabChangeText;
	}

	public String getLayoutTabChangeVisible(){
		return LayoutTabChangeVisible;
	}

	public String getOtherColorChanged(){
		return OtherColorChanged;
	}

	public String getReadOnlyChange(){
		return ReadOnlyChange;
	}

	public String getRelationshipAboutToChangeCurrentObject(){
		return RelationshipAboutToChangeCurrentObject;
	}

	public String getRelationshipModifiedCurrentObject(){
		return RelationshipModifiedCurrentObject;
	}

	public String getRelationshipSwitchHandlerChange(){
		return RelationshipSwitchHandlerChange;
	}

	public String getRelationshipTypeChange(){
		return RelationshipTypeChange;
	}

	public String getscrFieldPropertyReadOnly(){
		return scrFieldPropertyReadOnly;
	}

	public String getscrFieldValidationConstraintChanged(){
		return scrFieldValidationConstraintChanged;
	}

	public String getsrcAuditingModified(){
		return srcAuditingModified;
	}

	public String getsrcBusOb(){
		return srcBusOb;
	}

	public String getsrcBusObAfterSave(){
		return srcBusObAfterSave;
	}

	public String getsrcBusObBeforeSave(){
		return srcBusObBeforeSave;
	}

	public String getsrcField(){
		return srcField;
	}

	public String getsrcRelationshipAdded(){
		return srcRelationshipAdded;
	}

	public String getsrcRelationshipChanged(){
		return srcRelationshipChanged;
	}

	public String getsrcRelationshipCurrent(){
		return srcRelationshipCurrent;
	}

	public String getsrcRelationshipCurrentAboutToChange(){
		return srcRelationshipCurrentAboutToChange;
	}

	public String getsrcRelationshipCurrentModified(){
		return srcRelationshipCurrentModified;
	}

	public String getsrcRelationshipDataSourceRefresh(){
		return srcRelationshipDataSourceRefresh;
	}

	public String getsrcRelationshipDataSourceReloadRebind(){
		return srcRelationshipDataSourceReloadRebind;
	}

	public String getsrcRelationshipRemoved(){
		return srcRelationshipRemoved;
	}

	public String getStateChange(){
		return StateChange;
	}

	public String getUpdateControlDisplay(){
		return UpdateControlDisplay;
	}

	public String getValidationChange(){
		return ValidationChange;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAboutToSave(String newVal){
		AboutToSave = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAfterSave(String newVal){
		AfterSave = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAuditingRecordsCreated(String newVal){
		AuditingRecordsCreated = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAutoFill(String newVal){
		AutoFill = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBackgroundChange(String newVal){
		BackgroundChange = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBackgroundChangeFirstColor(String newVal){
		BackgroundChangeFirstColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBackgroundChangeImage(String newVal){
		BackgroundChangeImage = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBackgroundChangeSecondColor(String newVal){
		BackgroundChangeSecondColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBPEventObCreated(String newVal){
		BPEventObCreated = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBPEventObDeleted(String newVal){
		BPEventObDeleted = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBPEventObRetrieved(String newVal){
		BPEventObRetrieved = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBPEventObUpdated(String newVal){
		BPEventObUpdated = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCalculate(String newVal){
		Calculate = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setConstraintsChanged(String newVal){
		ConstraintsChanged = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControl(String newVal){
		Control = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlBackgroundChangeFirstColor(String newVal){
		ControlBackgroundChangeFirstColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlBackgroundChangeImage(String newVal){
		ControlBackgroundChangeImage = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlBackgroundChangeSecondColor(String newVal){
		ControlBackgroundChangeSecondColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeAlignment(String newVal){
		ControlChangeAlignment = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeAnchor(String newVal){
		ControlChangeAnchor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeBorderColor(String newVal){
		ControlChangeBorderColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeBorderWeight(String newVal){
		ControlChangeBorderWeight = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeButtonImage(String newVal){
		ControlChangeButtonImage = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeButtonText(String newVal){
		ControlChangeButtonText = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeFont(String newVal){
		ControlChangeFont = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeForeground(String newVal){
		ControlChangeForeground = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeGroupboxText(String newVal){
		ControlChangeGroupboxText = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeLabelText(String newVal){
		ControlChangeLabelText = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeLinkImage(String newVal){
		ControlChangeLinkImage = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeLinkText(String newVal){
		ControlChangeLinkText = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeNameSplitter(String newVal){
		ControlChangeNameSplitter = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangePictureImage(String newVal){
		ControlChangePictureImage = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeReadOnly(String newVal){
		ControlChangeReadOnly = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeSizeOrPosition(String newVal){
		ControlChangeSizeOrPosition = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeSpinner(String newVal){
		ControlChangeSpinner = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeText(String newVal){
		ControlChangeText = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeTextCombo(String newVal){
		ControlChangeTextCombo = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setControlChangeVisible(String newVal){
		ControlChangeVisible = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFlags(String newVal){
		Flags = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setForm(String newVal){
		Form = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridCellChangeBackgroundColor(String newVal){
		GridCellChangeBackgroundColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridCellChangeBorderColor(String newVal){
		GridCellChangeBorderColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridCellChangeImage(String newVal){
		GridCellChangeImage = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridCellChangeTextColor(String newVal){
		GridCellChangeTextColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridCurrentRowChange(String newVal){
		GridCurrentRowChange = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridDataSourceReloadRebind(String newVal){
		GridDataSourceReloadRebind = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridHeaderChanged(String newVal){
		GridHeaderChanged = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridRowAdd(String newVal){
		GridRowAdd = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridRowChange(String newVal){
		GridRowChange = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridRowChangeBackgroundColor(String newVal){
		GridRowChangeBackgroundColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridRowChangeBorderColor(String newVal){
		GridRowChangeBorderColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridRowChangeImage(String newVal){
		GridRowChangeImage = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridRowChangeTextColor(String newVal){
		GridRowChangeTextColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridRowDataSourceRefresh(String newVal){
		GridRowDataSourceRefresh = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGridRowRemove(String newVal){
		GridRowRemove = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutMultiPartReloadRegions(String newVal){
		LayoutMultiPartReloadRegions = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutPresentationChangedView(String newVal){
		LayoutPresentationChangedView = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutPresentationChangeForm(String newVal){
		LayoutPresentationChangeForm = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutPresentationChangeGrid(String newVal){
		LayoutPresentationChangeGrid = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutPresentationChangeRelationship(String newVal){
		LayoutPresentationChangeRelationship = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutPresentationChangeToolbar(String newVal){
		LayoutPresentationChangeToolbar = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutPresentationSwapViews(String newVal){
		LayoutPresentationSwapViews = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutSplitChangeOrientation(String newVal){
		LayoutSplitChangeOrientation = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutSplitChangeSplitBehaviour(String newVal){
		LayoutSplitChangeSplitBehaviour = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutSplitChangeSplitColor(String newVal){
		LayoutSplitChangeSplitColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutSplitChangeSplitterSize(String newVal){
		LayoutSplitChangeSplitterSize = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutTabChangeDescription(String newVal){
		LayoutTabChangeDescription = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutTabChangeEnabled(String newVal){
		LayoutTabChangeEnabled = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutTabChangeImage(String newVal){
		LayoutTabChangeImage = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutTabChangeTabPositions(String newVal){
		LayoutTabChangeTabPositions = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutTabChangeText(String newVal){
		LayoutTabChangeText = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLayoutTabChangeVisible(String newVal){
		LayoutTabChangeVisible = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOtherColorChanged(String newVal){
		OtherColorChanged = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setReadOnlyChange(String newVal){
		ReadOnlyChange = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRelationshipAboutToChangeCurrentObject(String newVal){
		RelationshipAboutToChangeCurrentObject = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRelationshipModifiedCurrentObject(String newVal){
		RelationshipModifiedCurrentObject = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRelationshipSwitchHandlerChange(String newVal){
		RelationshipSwitchHandlerChange = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRelationshipTypeChange(String newVal){
		RelationshipTypeChange = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setscrFieldPropertyReadOnly(String newVal){
		scrFieldPropertyReadOnly = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setscrFieldValidationConstraintChanged(String newVal){
		scrFieldValidationConstraintChanged = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcAuditingModified(String newVal){
		srcAuditingModified = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcBusOb(String newVal){
		srcBusOb = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcBusObAfterSave(String newVal){
		srcBusObAfterSave = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcBusObBeforeSave(String newVal){
		srcBusObBeforeSave = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcField(String newVal){
		srcField = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcRelationshipAdded(String newVal){
		srcRelationshipAdded = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcRelationshipChanged(String newVal){
		srcRelationshipChanged = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcRelationshipCurrent(String newVal){
		srcRelationshipCurrent = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcRelationshipCurrentAboutToChange(String newVal){
		srcRelationshipCurrentAboutToChange = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcRelationshipCurrentModified(String newVal){
		srcRelationshipCurrentModified = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcRelationshipDataSourceRefresh(String newVal){
		srcRelationshipDataSourceRefresh = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcRelationshipDataSourceReloadRebind(String newVal){
		srcRelationshipDataSourceReloadRebind = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsrcRelationshipRemoved(String newVal){
		srcRelationshipRemoved = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setStateChange(String newVal){
		StateChange = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUpdateControlDisplay(String newVal){
		UpdateControlDisplay = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setValidationChange(String newVal){
		ValidationChange = newVal;
	}

}