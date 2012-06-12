package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:47
 */
public interface IDefinition {

	public String Alias();

	public Map Annotations();

	public void ApplyEdits();

	public void AssignIdIfRequired();

	public String AssociatedImage();

	public boolean CanEdit();

	public String CategoryAsString();

	/**
	 * 
	 * @param Name
	 */
	public void ClearCargo(String Name);

	public IDefinition Clone();

	public IDefinition CloneForCopy();

	public IDefinition CloneForEdit();

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 */
	public void CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect);

	public String DefinitionType();

	public String Description();

	public String Flags();

	public String Folder();

	/**
	 * 
	 * @param Name
	 */
	public Object GetCargo(String Name);

	public String Id();

	public String InstanceClassName();

	public boolean IsDefDirty();

	public String LinkedTo();

	public String Name();

	public String OriginalName();

	public Fusion.Xml.Scope OriginalScope();

	public String OriginalScopeOwner();

	public String Perspective();

	/**
	 * 
	 * @param scopeType
	 * @param strScopeOwner
	 */
	public void ReconcileScope(Fusion.Xml.Scope scopeType, String strScopeOwner);

	public Fusion.Xml.Scope Scope();

	public String ScopeOwner();

	/**
	 * 
	 * @param Name
	 * @param Cargo
	 */
	public void SetCargo(String Name, Object Cargo);

	public String StorageName();

	public String StorageSource();

	public boolean Stored();

	public String ToXml();

	public int Version();

}