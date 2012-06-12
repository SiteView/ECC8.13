/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.SiteViewException;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */
import java.util.HashMap;

// Referenced classes of package com.dragonflow.SiteViewException:
// SiteViewException, SiteViewError

public class SiteViewParameterException extends com.dragonflow.SiteViewException.SiteViewException
{

    private java.util.HashMap errorParameterMap = null;
    static final boolean $assertionsDisabled; /* synthetic field */

    public SiteViewParameterException(long l)
    {
        super(l);
        errorParameterMap = new HashMap();
        siteViewError.setType(3);
    }

    public SiteViewParameterException(long l, String as[])
    {
        super(l, as);
        errorParameterMap = new HashMap();
        siteViewError.setType(3);
    }

    public SiteViewParameterException(long l, java.util.HashMap hashmap)
    {
        super(l);
        errorParameterMap = hashmap;
        siteViewError.setType(3);
    }

    public SiteViewParameterException(long l, String as[], java.util.HashMap hashmap)
    {
        super(l, as);
        errorParameterMap = hashmap;
    }

    public SiteViewParameterException(com.dragonflow.SiteViewException.SiteViewError siteviewerror)
    {
        super(siteviewerror);
        errorParameterMap = null;
        if(!$assertionsDisabled && siteviewerror.getType() != 3)
        {
            throw new AssertionError();
        } else
        {
            return;
        }
    }

    public java.util.Map getErrorParameterMap()
    {
        return errorParameterMap;
    }

    static 
    {
        $assertionsDisabled = !(com.dragonflow.SiteViewException.SiteViewParameterException.class).desiredAssertionStatus();
    }
}
