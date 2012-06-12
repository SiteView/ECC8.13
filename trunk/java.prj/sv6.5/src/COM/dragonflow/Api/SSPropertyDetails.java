/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Api;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */


// Referenced classes of package COM.dragonflow.Api:
// SSBaseReturnValues

public class SSPropertyDetails extends COM.dragonflow.Api.SSBaseReturnValues
{

    private java.lang.String name;
    private java.lang.String value;
    private java.lang.String propertyType;
    private java.lang.String description;
    private java.lang.String label;
    private boolean editable;
    private boolean multiValued;
    private java.lang.String defaultValue;
    private java.lang.String selectionDisplayNames[];
    private java.lang.String selectionIDs[];
    private java.lang.String selectionChoiceType;
    private boolean required;
    private boolean prerequisite;
    private int order;
    private java.lang.String displayUnits;
    private boolean advanced;
    private boolean password;
    public static final java.lang.String BOOLEAN = "BOOLEAN";
    public static final java.lang.String BROWSABLE = "BROWSABLE";
    public static final java.lang.String FILE = "FILE";
    public static final java.lang.String FREQUENCY = "FREQUENCY";
    public static final java.lang.String NUMERIC = "NUMERIC";
    public static final java.lang.String PERCENT = "PERCENT";
    public static final java.lang.String RATE = "RATE";
    public static final java.lang.String SCALAR = "SCALAR";
    public static final java.lang.String SCHEDULE = "SCHEDULE";
    public static final java.lang.String SERVER = "SERVER";
    public static final java.lang.String TEXT = "TEXT";
    public static final java.lang.String PASSWORD = "PASSWORD";
    public static final java.lang.String SELECTION_CHOICE_XML = "XML";
    public static final java.lang.String SELECTION_CHOICE_LIST = "LIST";
    public static final java.lang.String SELECTION_CHOICE_THRESHOLD = "THRESHOLD";

    public SSPropertyDetails(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, boolean flag, boolean flag1, java.lang.String s4, 
            java.lang.String as[], java.lang.String as1[], java.lang.String s5, boolean flag2, boolean flag3, int i, java.lang.String s6, 
            boolean flag4, boolean flag5, java.lang.String s7)
    {
        name = s;
        propertyType = s1;
        description = s2;
        label = s3;
        editable = flag;
        multiValued = flag1;
        defaultValue = s4;
        selectionDisplayNames = as;
        selectionIDs = as1;
        selectionChoiceType = s5;
        required = flag2;
        prerequisite = flag3;
        order = i;
        value = s7;
        if(s1.equals("NUMERIC") || s1.equals("FREQUENCY") || s1.equals("PERCENT"))
        {
            displayUnits = s6;
        } else
        {
            displayUnits = "";
        }
        advanced = flag4;
        password = flag5;
    }

    public java.lang.Object getReturnValueType()
    {
        java.lang.Class class1 = getClass();
        return class1.getName();
    }

    public java.lang.String getName()
    {
        return name;
    }

    public java.lang.String getValue()
    {
        return value;
    }

    public java.lang.String getPropertyType()
    {
        return propertyType;
    }

    public java.lang.String getDescription()
    {
        return description;
    }

    public java.lang.String getLabel()
    {
        return label;
    }

    public boolean isEditable()
    {
        return editable;
    }

    public boolean isMultiValued()
    {
        return multiValued;
    }

    public java.lang.String getDefaultValue()
    {
        return defaultValue;
    }

    public java.lang.String[] getSelectionDisplayNames()
    {
        return selectionDisplayNames;
    }

    public java.lang.String[] getSelectionIDs()
    {
        return selectionIDs;
    }

    public java.lang.String getSelectionChoiceType()
    {
        return selectionChoiceType;
    }

    public boolean isRequired()
    {
        return required;
    }

    public boolean isPrerequisite()
    {
        return prerequisite;
    }

    public int getOrder()
    {
        return order;
    }

    public java.lang.String getDisplayUnits()
    {
        return displayUnits;
    }

    public boolean isAdvanced()
    {
        return advanced;
    }

    public boolean isPassword()
    {
        return password;
    }

    public static void extractDetailsIntoHashMap(COM.dragonflow.Api.SSPropertyDetails sspropertydetails, jgl.HashMap hashmap)
    {
        if(sspropertydetails.getClass() != null)
        {
            hashmap.put("class", sspropertydetails.getClass());
        } else
        {
            hashmap.put("class", "");
        }
        if(sspropertydetails.getDefaultValue() != null)
        {
            hashmap.put("defaultValue", sspropertydetails.getDefaultValue());
        } else
        {
            hashmap.put("defaultValue", "");
        }
        if(sspropertydetails.getDescription() != null)
        {
            hashmap.put("description", sspropertydetails.getDescription());
        } else
        {
            hashmap.put("description", "");
        }
        if(sspropertydetails.getDisplayUnits() != null)
        {
            hashmap.put("displayUnits", sspropertydetails.getDisplayUnits());
        } else
        {
            hashmap.put("displayUnits", "");
        }
        if(sspropertydetails.getLabel() != null)
        {
            hashmap.put("label", sspropertydetails.getLabel());
        } else
        {
            hashmap.put("label", "");
        }
        if(sspropertydetails.getName() != null)
        {
            hashmap.put("name", sspropertydetails.getName());
        } else
        {
            hashmap.put("name", "");
        }
        if(sspropertydetails.getValue() != null)
        {
            hashmap.put("value", sspropertydetails.getValue());
        } else
        {
            hashmap.put("value", "");
        }
        hashmap.put("order", (new Integer(sspropertydetails.getOrder())).toString());
        if(sspropertydetails.getPropertyType() != null)
        {
            hashmap.put("propertyType", sspropertydetails.getPropertyType());
        } else
        {
            hashmap.put("propertyType", "");
        }
        if(sspropertydetails.getSelectionChoiceType() != null)
        {
            hashmap.put("selectionChoiceType", sspropertydetails.getSelectionChoiceType());
        } else
        {
            hashmap.put("selectionChoiceType", "");
        }
        if(sspropertydetails.getSelectionDisplayNames() != null)
        {
            hashmap.put(sspropertydetails.getName() + "DisplayNames", sspropertydetails.getSelectionDisplayNames());
        } else
        {
            hashmap.put(sspropertydetails.getName() + "DisplayNames", "");
        }
        if(sspropertydetails.getSelectionIDs() != null)
        {
            hashmap.put(sspropertydetails.getName() + "SelectionIDs", sspropertydetails.getSelectionIDs());
        } else
        {
            hashmap.put(sspropertydetails.getName() + "SelectionIDs", "");
        }
        hashmap.put("isAdvanced", (new Boolean(sspropertydetails.isAdvanced())).toString());
        hashmap.put("isEditable", (new Boolean(sspropertydetails.isEditable())).toString());
        hashmap.put("isMultivalued", (new Boolean(sspropertydetails.isMultiValued())).toString());
        hashmap.put("isPassword", (new Boolean(sspropertydetails.isPassword())).toString());
        hashmap.put("isPrerequisite", (new Boolean(sspropertydetails.isPrerequisite())).toString());
        hashmap.put("isRequired", (new Boolean(sspropertydetails.isRequired())).toString());
    }
}
