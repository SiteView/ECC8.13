package Fusion.Api;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:50
 */
public interface IDefinitions {

	public List BusinessObjectNames();

	/**
	 * 
	 * @param name
	 */
	public BusinessObjectDef GetBusinessObjectDef(String name);

	/**
	 * 
	 * @param id
	 */
	public BusinessObjectDef GetBusinessObjectDefById(String id);

	/**
	 * 
	 * @param StorageName
	 */
	public BusinessObjectDef GetBusinessObjectDefByStorageName(String StorageName);

	/**
	 * 
	 * @param FieldName
	 */
	public FieldDef GetBusinessObjectFieldDef(String FieldName);

	public List GetBusObPlaceHolderList();

	/**
	 * 
	 * @param groupName
	 * @param includeBase
	 */
	public List GetBusObPlaceHolderListForGroup(String groupName, boolean includeBase);

	/**
	 * 
	 * @param name
	 */
	public List GetCombinedGroupFieldDefs(String name);

	/**
	 * 
	 * @param strName
	 */
	public CounterDef GetCounterDef(String strName);

	/**
	 * 
	 * @param strId
	 */
	public CounterDef GetCounterDefById(String strId);

	public List GetCounterPlaceHolderList();

	/**
	 * 
	 * @param strName
	 */
	public FormatDef GetFormatDef(String strName);

	/**
	 * 
	 * @param strId
	 */
	public FormatDef GetFormatDefById(String strId);

	public List GetFormatPlaceHolderList();

	/**
	 * 
	 * @param strName
	 */
	public LoginProcedureDef GetLoginProcedureDef(String strName);

	/**
	 * 
	 * @param strId
	 */
	public LoginProcedureDef GetLoginProcedureDefById(String strId);

	/**
	 * 
	 * @param strName
	 */
	public PerspectiveDef GetPerspectiveDef(String strName);

	/**
	 * 
	 * @param strId
	 */
	public PerspectiveDef GetPerspectiveDefById(String strId);

	public List GetPerspectivePlaceHolderList();

	/**
	 * 
	 * @param definitionType
	 * @param name
	 */
	public PlaceHolder GetPlaceHolderForDefinition(String definitionType, String name);

	/**
	 * 
	 * @param definitionType
	 * @param id
	 */
	public PlaceHolder GetPlaceHolderForDefinitionById(String definitionType, String id);

	/**
	 * 
	 * @param RelationshipName
	 */
	public BusinessObjectDef GetRelatedBusinessObjectDef(String RelationshipName);

	/**
	 * 
	 * @param name
	 */
	public RelationshipDef GetRelationshipDef(String name);

	/**
	 * 
	 * @param id
	 */
	public RelationshipDef GetRelationshipDefById(String id);

	/**
	 * 
	 * @param strName
	 */
	public RuleDef GetRuleDef(String strName);

	/**
	 * 
	 * @param strId
	 */
	public RuleDef GetRuleDefById(String strId);

	public List GetRulePlaceHolderList();

	public List GetSupportedDefinitionTypes();

	/**
	 * 
	 * @param strName
	 */
	public TokenDef GetTokenDef(String strName);

	/**
	 * 
	 * @param strId
	 */
	public TokenDef GetTokenDefById(String strId);

	public List GetTokenPlaceHolderList();

	public void InvalidateCache();

	public List MasterObjectNames();

	public List RuleNames();

}