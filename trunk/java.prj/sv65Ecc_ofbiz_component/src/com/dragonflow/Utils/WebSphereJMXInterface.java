/*
 * Created on 2005-2-9 3:06:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Utils;

import java.lang.reflect.Method;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

// Referenced classes of package com.dragonflow.Utils:
// JMXInterface
public class WebSphereJMXInterface extends com.dragonflow.Utils.JMXInterface {

    public Class AdminClientClass;

    public Class StatsClass;

    public Class PMIModuleConfigClass;

    public Class PMIDataInfoClass;

    public Class StatsImplClass;

    public Class PMIClientClass;

    public Class StatisticClass;

    public Class BoundaryStatisticImplClass;

    public Class BoundedRangeStatisticImplClass;

    public Class CountStatisticImplClass;

    public Class DoubleStatisticImplClass;

    public Class RangeStatisticImplClass;

    public Class TimeStatisticImplClass;

    public Method getStatisticNamesMethod;

    public Method getShortNameMethod;

    public Method getMBeanTypeMethod;

    public Method listAllDataMethod;

    public Method getDICategoryMethod;

    public Method getDICommentMethod;

    public Method getDIDescriptionMethod;

    public Method getDINameMethod;

    public Method setConfigMethod;

    public Method getStatisticMethod;

    public Method dataMembersMethod;

    public Method getStatisticsMethod;

    public Method getSubStatsMethod;

    public Method getStatsNameMethod;

    public Method getStatsMethod;

    public Method getStatisticNameMethod;

    public Method getLowerBoundMethod;

    public Method getUpperBoundMethod;

    public Method getCurrentMethod;

    public Method getCountMethod;

    public Method getDoubleMethod;

    public Method getRSCurrentMethod;

    public Method getTotalMethod;

    public Method getNLSValueMethod;

    public WebSphereJMXInterface(Class class1) {
        ClassLoader classloader = Thread.currentThread().getContextClassLoader();
        try {
            AdminClientClass = class1;
            queryNamesMethod = class1.getMethod("queryNames", new Class[] { ObjectNameClass, QueryExpClass });
            getAttributeMethod = class1.getMethod("getAttribute", new Class[] { ObjectNameClass, String.class });
            getMBeanInfoMethod = class1.getMethod("getMBeanInfo", new Class[] { ObjectNameClass });
            Class class2 = String.class;
            Class class3 = Object[].class;
            Class class4 = String[].class;
            invokeMethod = class1.getMethod("invoke", new Class[] { ObjectNameClass, class2, class3, class4 });
            StatsClass = classloader.loadClass("com.ibm.websphere.management.statistics.Stats");
            PMIModuleConfigClass = classloader.loadClass("com.ibm.websphere.pmi.PmiModuleConfig");
            PMIDataInfoClass = classloader.loadClass("com.ibm.websphere.pmi.PmiDataInfo");
            StatsImplClass = classloader.loadClass("com.ibm.websphere.pmi.stat.StatsImpl");
            getStatisticNamesMethod = StatsClass.getMethod("getStatisticNames", null);
            getShortNameMethod = PMIModuleConfigClass.getMethod("getShortName", null);
            getMBeanTypeMethod = PMIModuleConfigClass.getMethod("getMbeanType", null);
            listAllDataMethod = PMIModuleConfigClass.getMethod("listAllData", null);
            getDICategoryMethod = PMIDataInfoClass.getMethod("getCategory", null);
            getDICommentMethod = PMIDataInfoClass.getMethod("getComment", null);
            getDIDescriptionMethod = PMIDataInfoClass.getMethod("getDescription", null);
            getDINameMethod = PMIDataInfoClass.getMethod("getName", null);
            setConfigMethod = StatsImplClass.getMethod("setConfig", new Class[] { PMIModuleConfigClass });
            getStatisticMethod = StatsImplClass.getMethod("getStatistic", new Class[] { String.class });
            dataMembersMethod = StatsImplClass.getMethod("dataMembers", null);
            getStatisticsMethod = StatsImplClass.getMethod("getStatistics", null);
            getSubStatsMethod = StatsImplClass.getMethod("getSubStats", null);
            getStatsNameMethod = StatsImplClass.getMethod("getName", null);
            getStatsMethod = StatsImplClass.getMethod("getStats", new Class[] { String.class });
            StatisticClass = classloader.loadClass("com.ibm.websphere.management.statistics.Statistic");
            BoundaryStatisticImplClass = classloader.loadClass("com.ibm.websphere.pmi.stat.BoundaryStatisticImpl");
            BoundedRangeStatisticImplClass = classloader.loadClass("com.ibm.websphere.pmi.stat.BoundedRangeStatisticImpl");
            CountStatisticImplClass = classloader.loadClass("com.ibm.websphere.pmi.stat.CountStatisticImpl");
            DoubleStatisticImplClass = classloader.loadClass("com.ibm.websphere.pmi.stat.DoubleStatisticImpl");
            RangeStatisticImplClass = classloader.loadClass("com.ibm.websphere.pmi.stat.RangeStatisticImpl");
            TimeStatisticImplClass = classloader.loadClass("com.ibm.websphere.pmi.stat.TimeStatisticImpl");
            getStatisticNameMethod = StatisticClass.getMethod("getName", null);
            getLowerBoundMethod = BoundaryStatisticImplClass.getMethod("getLowerBound", null);
            getUpperBoundMethod = BoundaryStatisticImplClass.getMethod("getUpperBound", null);
            getCurrentMethod = BoundedRangeStatisticImplClass.getMethod("getCurrent", null);
            getCountMethod = CountStatisticImplClass.getMethod("getCount", null);
            getDoubleMethod = DoubleStatisticImplClass.getMethod("getDouble", null);
            getRSCurrentMethod = RangeStatisticImplClass.getMethod("getCurrent", null);
            getTotalMethod = TimeStatisticImplClass.getMethod("getTotal", null);
            PMIClientClass = classloader.loadClass("com.ibm.websphere.pmi.client.PmiClient");
            getNLSValueMethod = PMIClientClass.getMethod("getNLSValue", new Class[] { String.class });
        } catch (Exception exception) {
            System.err.println("Failed to load javax.management class or method: " + exception.toString());
        }
    }
}
