/*
 * 
 * Created on 2005-3-9 22:12:36
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Page;

class monitorSetFilter implements java.io.FilenameFilter {

    java.lang.String m_suffix;

    monitorSetFilter(java.lang.String s) {
        m_suffix = s;
    }

    public boolean accept(java.io.File file, java.lang.String s) {
        return s.endsWith(m_suffix);
    }
}
