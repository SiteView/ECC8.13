package Fusion.Api;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:45
 */
public class HolderUtils {



	public void finalize() throws Throwable {

	}

	private HolderUtils(){

	}

	/**
	 * 
	 * @param api
	 * @param fldValidated
	 */
	public static boolean AreStoredAndDisplayFieldsSame(IFusionApi api, Field fldValidated){
		return false;
	}

	/**
	 * 
	 * @param api
	 * @param ruleValidate
	 * @param bo
	 * @param strSortOrder
	 * @param bAscending
	 */
	public static FusionQuery BuildTableValidateQuery(IFusionApi api, RuleDef ruleValidate, BusinessObject bo, String strSortOrder, boolean bAscending){
		return null;
	}

	/**
	 * 
	 * @param api
	 * @param fldValidated
	 * @param rule
	 * @param strSortOrder
	 * @param bAscending
	 */
	private static List GetBusinessObjectList(IFusionApi api, Field fldValidated, TableValidation rule, String strSortOrder, boolean bAscending){
		return null;
	}

	/**
	 * 
	 * @param api
	 * @param fldValidated
	 */
	public static ArrayList GetFieldValueDisplayHolders(IFusionApi api, Field fldValidated){
		return null;
	}

	/**
	 * 
	 * @param api
	 */
	private static List GetHOPPlaceHolders(IFusionApi api){
		return null;
	}

	/**
	 * 
	 * @param api
	 * @param fldValidated
	 */
	public static List GetListFromFieldValidation(IFusionApi api, Field fldValidated){
		return null;
	}

	/**
	 * 
	 * @param api
	 * @param fldValidated
	 * @param strSortOrder
	 * @param bAscending
	 */
	public static List GetListFromFieldValidation(IFusionApi api, Field fldValidated, String strSortOrder, boolean bAscending){
		return null;
	}

	/**
	 * 
	 * @param api
	 * @param arrFld
	 * @param strSortOrder
	 * @param bAscending
	 */
	public static List GetListFromFieldValidation(IFusionApi api, List arrFld, String strSortOrder, boolean bAscending){
		return null;
	}

	/**
	 * 
	 * @param api
	 * @param fldValidated
	 */
	public static List GetListOfValuesFromFieldValidation(IFusionApi api, Field fldValidated){
		return null;
	}

	/**
	 * 
	 * @param api
	 * @param fldValidated
	 * @param strSortOrder
	 * @param bAscending
	 */
	public static List GetListOfValuesFromFieldValidation(IFusionApi api, Field fldValidated, String strSortOrder, boolean bAscending){
		return null;
	}

	/**
	 * 
	 * @param api
	 * @param listRule
	 * @param fldValidated
	 */
	private static List GetListRuleValues(IFusionApi api, ListRule listRule, Field fldValidated){
		return null;
	}

	/**
	 * 
	 * @param api
	 * @param relDef
	 * @param busObDefTarget
	 */
	public static List GetPurposeListFromContainsEmbeddedRelationshipDef(IFusionApi api, RelationshipDef relDef, BusinessObjectDef busObDefTarget){
		return null;
	}

	/**
	 * 
	 * @param api
	 * @param fldValidated
	 */
	public static BusinessObjectDef GetValidatingBusObDef(IFusionApi api, FieldDef fldValidated){
		return null;
	}

	/**
	 * 
	 * @param colBusObj
	 * @param strSortOrder
	 * @param bAscending
	 */
	public static List SortBusObjCollection(List colBusObj, String strSortOrder, boolean bAscending){
		return null;
	}

}