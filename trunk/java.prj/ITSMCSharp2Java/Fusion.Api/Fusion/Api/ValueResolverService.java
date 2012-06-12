package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:46:02
 */
public class ValueResolverService {

	private FusionApi m_fusionApi = null;

	public ValueResolverService(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param fusionApi
	 */
	public ValueResolverService(FusionApi fusionApi){

	}

	/**
	 * 
	 * @param busOb
	 * @param defField
	 * @param valFusion
	 */
	private boolean ResolveField(BusinessObject busOb, FieldDef defField, FusionValue valFusion){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 * @param strName
	 * @param valFusion
	 */
	public boolean ResolveField(BusinessObject busOb, String strName, FusionValue valFusion){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 * @param defField
	 * @param strValue
	 */
	private boolean ResolveFieldAsString(BusinessObject busOb, FieldDef defField, String strValue){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 * @param strName
	 * @param strValue
	 */
	public boolean ResolveFieldAsString(BusinessObject busOb, String strName, String strValue){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 * @param valFusion
	 */
	public boolean ResolveIdField(BusinessObject busOb, FusionValue valFusion){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 * @param strValue
	 */
	public boolean ResolveIdFieldAsString(BusinessObject busOb, String strValue){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 * @param valFusion
	 */
	public boolean ResolveParentIdField(BusinessObject busOb, FusionValue valFusion){
		return null;
	}

	/**
	 * 
	 * @param busOb
	 * @param strValue
	 */
	public boolean ResolveParentIdFieldAsString(BusinessObject busOb, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param valFusion
	 */
	public boolean ResolveSystemFunction(String strName, FusionValue valFusion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strValue
	 */
	public boolean ResolveSystemFunctionAsString(String strName, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param valFusion
	 */
	public boolean ResolveToken(String strName, FusionValue valFusion){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param strValue
	 */
	public boolean ResolveTokenAsString(String strName, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strValueToResolve
	 * @param vs
	 * @param valFusion
	 */
	public boolean ResolveValue(String strValueToResolve, ValueSources vs, FusionValue valFusion){
		return null;
	}

	/**
	 * 
	 * @param strValueToResolve
	 * @param busOb
	 * @param vs
	 * @param valFusion
	 */
	public boolean ResolveValue(String strValueToResolve, BusinessObject busOb, ValueSources vs, FusionValue valFusion){
		return null;
	}

	/**
	 * 
	 * @param strValueToResolve
	 * @param vs
	 * @param busOb
	 * @param valFusion
	 */
	public boolean ResolveValue(String strValueToResolve, ValueSources vs, BusinessObject busOb, FusionValue valFusion){
		return null;
	}

	/**
	 * 
	 * @param strValueToResolve
	 * @param vs
	 * @param strValue
	 */
	public boolean ResolveValueAsString(String strValueToResolve, ValueSources vs, String strValue){
		return null;
	}

	/**
	 * 
	 * @param strValueToResolve
	 * @param vs
	 * @param busOb
	 * @param strValue
	 */
	public boolean ResolveValueAsString(String strValueToResolve, ValueSources vs, BusinessObject busOb, String strValue){
		return null;
	}

}