/*
 * 
 * Created on 2005-2-16 15:14:00
 *
 * NonDeferringClassLoader.java
 *
 * History:
 *
 */
package COM.dragonflow.SiteView;

/**
 * Comment for <code>NonDeferringClassLoader</code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */
import java.net.URL;
import java.net.URLClassLoader;
import java.net.URLStreamHandlerFactory;

public class NonDeferringClassLoader extends URLClassLoader {

    public NonDeferringClassLoader(URL aurl[]) {
        super(aurl);
    }

    public NonDeferringClassLoader(URL aurl[], ClassLoader classloader) {
        super(aurl, classloader);
    }

    public NonDeferringClassLoader(URL aurl[], ClassLoader classloader,
            URLStreamHandlerFactory urlstreamhandlerfactory) {
        super(aurl, classloader, urlstreamhandlerfactory);
    }

    public Class loadClass(String s, boolean flag)
            throws ClassNotFoundException {
        Class class1 = findLoadedClass(s);
        if (class1 == null) {
            try {
                class1 = findClass(s);
            } catch (ClassNotFoundException classnotfoundexception) {
            }
        }
        if (class1 != null && flag) {
            resolveClass(class1);
        }
        if (class1 == null) {
            class1 = super.loadClass(s, flag);
        }
        return class1;
    }
}
