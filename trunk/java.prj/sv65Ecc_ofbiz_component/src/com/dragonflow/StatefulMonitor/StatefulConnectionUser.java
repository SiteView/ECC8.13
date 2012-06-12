/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.StatefulMonitor;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

// Referenced classes of package com.dragonflow.StatefulMonitor:
// StatefulConnection
public interface StatefulConnectionUser {

    public abstract Object getUniqueID();

    public abstract Object getConnID(Class class1);

    public abstract com.dragonflow.StatefulMonitor.StatefulConnection createConnection(Class class1, StringBuffer stringbuffer);
}
