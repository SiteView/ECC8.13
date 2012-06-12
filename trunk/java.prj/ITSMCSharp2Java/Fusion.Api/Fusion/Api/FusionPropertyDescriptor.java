package Fusion.Api;

import java.beans.PropertyDescriptor;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:40
 */
public class FusionPropertyDescriptor extends PropertyDescriptor {

	protected FieldDef m_fieldDef;

	public FusionPropertyDescriptor(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fieldDef
	 */
	public FusionPropertyDescriptor(FieldDef fieldDef){

	}

	/**
	 * 
	 * @param component
	 */
	public boolean CanResetValue(Object component){
		return false;
	}

	public Type ComponentType(){
		return null;
	}

	/**
	 * 
	 * @param component
	 */
	public Object GetValue(Object component){
		return null;
	}

	public boolean IsReadOnly(){
		return null;
	}

	public Type PropertyType(){
		return null;
	}

	/**
	 * 
	 * @param component
	 */
	public void ResetValue(Object component){

	}

	/**
	 * 
	 * @param component
	 * @param value
	 */
	public void SetValue(Object component, Object value){

	}

	/**
	 * 
	 * @param component
	 */
	public boolean ShouldSerializeValue(Object component){
		return null;
	}

}