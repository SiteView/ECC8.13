package Fusion.Api;

import java.awt.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:22
 */
public class AggregateUser {

	public AggregateUser(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param def
	 */
	protected IDefinition UnwrapAggregateIfRequired(IDefinition def){
		return null;
	}

	/**
	 * 
	 * @param collDefs
	 */
	protected List WrapAsAggregateCollectionIfRequired(List collDefs){
		return null;
	}

	/**
	 * 
	 * @param iDef
	 */
	protected IDefinition WrapAsAggregateIfRequired(IDefinition iDef){
		return null;
	}

}

