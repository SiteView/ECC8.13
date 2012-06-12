package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:58
 */
public interface ISystemPrompt extends IDefinition, ISystemFunction {

	public String Caption();

	public Object DefaultValue();

	public String Message();

	public String PromptRefId();

	public String PromptRefName();

	public String PromptRefType();

}