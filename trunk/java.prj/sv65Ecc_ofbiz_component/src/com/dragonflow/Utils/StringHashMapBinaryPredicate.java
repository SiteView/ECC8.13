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
    String _properties[];

    public StringHashMapBinaryPredicate(String as[], boolean flag)
    {
        _properties = as;
        _bCaseSensitive = flag;
    }

    public boolean execute(Object obj, Object obj1)
    {
        jgl.HashMap hashmap = (jgl.HashMap)obj;
        jgl.HashMap hashmap1 = (jgl.HashMap)obj1;
        if(hashmap == null || hashmap1 == null)
        {
            return true;
        }
        for(int i = 0; i < _properties.length; i++)
        {
            String s = _properties[i];
            if(s == null)
            {
                continue;
            }
            String s1 = (String)hashmap.get(s);
            String s2 = (String)hashmap1.get(s);
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
