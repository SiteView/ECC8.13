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

class StringBinaryPredicate implements jgl.BinaryPredicate {

    boolean _bCaseSensitive;

    public StringBinaryPredicate(boolean flag) {
        _bCaseSensitive = flag;
    }

    public boolean execute(java.lang.Object obj, java.lang.Object obj1) {
        java.lang.String s = (java.lang.String) obj;
        java.lang.String s1 = (java.lang.String) obj1;
        if (s == null || s1 == null) {
            return false;
        }
        if (!_bCaseSensitive) {
            s = s.toLowerCase();
            s1 = s1.toLowerCase();
        }
        return s.compareTo(s1) <= 0;
    }
}
