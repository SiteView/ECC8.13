package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:47
 */
public interface IDefinitionLibrary {

	/**
	 * 
	 * @param strType
	 * @param strXML
	 */
	public IDefinition CreateDefFromXml(String strType, String strXML);

	/**
	 * 
	 * @param req
	 */
	public List GetAllDefinitions(DefRequest req);

	/**
	 * 
	 * @param strType
	 * @param strPerspective
	 */
	public List GetAllPlaceHolders(String strType, String strPerspective);

	/**
	 * 
	 * @param req
	 */
	public IDefinition GetDefForEditing(DefRequest req);

	/**
	 * 
	 * @param req
	 */
	public IDefinition GetDefinition(DefRequest req);

	/**
	 * 
	 * @param strType
	 * @param strName
	 * @param bRetrieveBaseDef
	 * @param strPerspective
	 */
	public List GetDerivedDefsFromStore(String strType, String strName, boolean bRetrieveBaseDef, String strPerspective);

	/**
	 * 
	 * @param req
	 */
	public IDefinition GetNewDefForEditing(DefRequest req);

	/**
	 * 
	 * @param req
	 */
	public List GetPlaceHolderList(DefRequest req);

	/**
	 * 
	 * @param req
	 */
	public boolean IsDuplicateName(DefRequest req);

	/**
	 * 
	 * @param strType
	 */
	public boolean IsMdrType(String strType);

	/**
	 * 
	 * @param def
	 */
	public void MarkDefinitionForDeletion(IDefinition def);

	/**
	 * 
	 * @param req
	 */
	public void RevertDefinition(DefRequest req);

	/**
	 * 
	 * @param def
	 */
	public void RevertDefinition(IDefinition def);

	/**
	 * 
	 * @param req
	 */
	public void UndeleteDefinition(DefRequest req);

	/**
	 * 
	 * @param def
	 */
	public void UpdateDefinition(IDefinition def);

	/**
	 * 
	 * @param def
	 * @param bCreateNewOnScopeChange
	 */
	public void UpdateDefinition(IDefinition def, boolean bCreateNewOnScopeChange);

}