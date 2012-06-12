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

import java.util.TreeSet;

public class TreeUtils {

    java.util.TreeSet tree;

    public TreeUtils() {
        tree = null;
        tree = new TreeSet();
    }

    public boolean add(Object obj) {
        return tree.add(obj);
    }

    public void clear() {
        tree.clear();
    }

    public Object clone() {
        return tree.clone();
    }

    public boolean contains(Object obj) {
        return tree.contains(obj);
    }

    public Object first() {
        return tree.first();
    }

    public Object last() {
        return tree.last();
    }

    public boolean isEmpty() {
        return tree.isEmpty();
    }

    public java.util.Iterator iterator() {
        return tree.iterator();
    }

    public Object[] getTreeObjectArray() {
        Object aobj[] = new Object[tree.size()];
        int i = 0;
        for (java.util.Iterator iterator1 = tree.iterator(); iterator1.hasNext();) {
            aobj[i ++] = iterator1.next();
        }

        return aobj;
    }

    public boolean remove(Object obj) {
        return tree.remove(obj);
    }

    public int size() {
        return tree.size();
    }
}
