 /*
  * Created on 2005-2-9 3:06:20
  *
  * .java
  *
  * History:
  *
  */
  package com.dragonflow.Utils;

 /**
     * Comment for <code></code>
     * 
     * @author
     * @version 0.0
     * 
     * 
     */

class StringHashMapBinaryPredicate
    implements jgl.BinaryPredicate
{

    boolean _bCaseSensitive;
    java.lang.String _properties[];

    public StringHashMapBinaryPredicate(java.lang.String as[], boolean flag)
    {
        _properties = as;
        _bCaseSensitive = flag;
    }

    public boolean execute(java.lang.Object obj, java.lang.Object obj1)
    {
        jgl.HashMap hashmap = (jgl.HashMap)obj;
        jgl.HashMap hashmap1 = (jgl.HashMap)obj1;
        if(hashmap == null || hashmap1 == null)
        {
            return true;
        }
        for(int i = 0; i < _properties.length; i++)
        {
            java.lang.String s = _properties[i];
            if(s == null)
            {
                continue;
            }
            java.lang.String s1 = (java.lang.String)hashmap.get(s);
            java.lang.String s2 = (java.lang.String)hashmap1.get(s);
            if(s1 == null || s2 == null)
            {
                continue;
            }
            if(!_bCaseSensitive)
            {
                s1 = s1.toLowerCase();
                s2 = s2.toLowerCase();
            }
            int j = s1.compareTo(s2);
            if(j != 0)
            {
                return j < 0;
            }
        }

        return true;
    }
}
