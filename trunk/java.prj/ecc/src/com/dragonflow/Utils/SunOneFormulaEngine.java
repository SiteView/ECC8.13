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

import java.util.HashMap;
import java.util.HashSet;
import java.util.Random;

// Referenced classes of package com.dragonflow.Utils:
// RawXmlWriter, TextUtils

public class SunOneFormulaEngine
{

    private java.util.HashMap internalDerivedCountersList;
    private java.util.HashMap internalImpliedCountersList;
    private java.lang.String externalDerivedCounterFormulas[];

    public SunOneFormulaEngine(java.lang.String as[])
    {
        internalDerivedCountersList = new HashMap();
        internalImpliedCountersList = new HashMap();
        externalDerivedCounterFormulas = null;
        externalDerivedCounterFormulas = as;
    }

    public void readFormulasFromFile(java.lang.String s)
    {
    }

    public void registerElementForDerivedCounter(java.lang.String s)
    {
        java.lang.String s1 = com.dragonflow.StandardMonitor.SunOneMonitor.extractElementFromQualifiedCounterName(s);
        java.lang.String as[] = getListOfDerivedCounterNames();
        for(int i = 0; i < as.length; i++)
        {
            int j = as[i].indexOf(s1);
            if(j < 0)
            {
                continue;
            }
            java.lang.String s2;
            if(s.indexOf('@') <= 0)
            {
                s2 = com.dragonflow.StandardMonitor.SunOneMonitor.extractAdequateCounterName(as[i], false);
            } else
            {
                s2 = s + as[i].substring(j + s1.length() + 1);
            }
            internalDerivedCountersList.put(s2, "");
        }

    }

    public void registerSelectedDerivedCounter(java.lang.String s)
    {
        java.util.Set set = getImpliedCountersForDerivedCounter(s);
        java.lang.String s1;
        for(java.util.Iterator iterator = set.iterator(); iterator.hasNext(); internalImpliedCountersList.put(s1, ""))
        {
            s1 = (java.lang.String)iterator.next();
        }

    }

    private java.lang.String qualifyCounterName(java.lang.String s, java.lang.String s1)
    {
        java.lang.String s2 = com.dragonflow.StandardMonitor.SunOneMonitor.extractQualifedElementFromQualifiedCounterName(s);
        if(s2.indexOf('@') <= 0)
        {
            return com.dragonflow.StandardMonitor.SunOneMonitor.extractAdequateCounterName(s1, false);
        } else
        {
            int i = s1.indexOf('/', 1);
            return "/" + s2 + s1.substring(i);
        }
    }

    public void setImpliedCounterValue(java.lang.String s, java.lang.String s1)
    {
        if(internalImpliedCountersList.get(s) != null)
        {
            internalImpliedCountersList.put(s, s1);
        }
    }

    public java.lang.String generateBrowseData()
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        com.dragonflow.Utils.RawXmlWriter rawxmlwriter = new RawXmlWriter(stringbuffer);
        java.util.Iterator iterator = internalDerivedCountersList.keySet().iterator();
        if(!iterator.hasNext())
        {
            return "";
        }
        java.util.Random random = new Random();
        rawxmlwriter.startElement("object name=\"Derived Counters\"");
        java.lang.String s;
        for(; iterator.hasNext(); rawxmlwriter.emptyElement("counter name=\"" + s + "\" id=\"" + random.nextInt() + "\""))
        {
            s = (java.lang.String)iterator.next();
        }

        rawxmlwriter.endElement("object");
        return stringbuffer.toString();
    }

    public java.lang.String[] getListOfDerivedCounterNames()
    {
        java.lang.String as[] = new java.lang.String[externalDerivedCounterFormulas.length];
        for(int i = 0; i < as.length; i++)
        {
            int j = externalDerivedCounterFormulas[i].indexOf('=');
            java.lang.String s = externalDerivedCounterFormulas[i].substring(0, j);
            as[i] = s.trim();
        }

        return as;
    }

    public void calculateDerivedCounterValues(java.util.HashMap hashmap, java.lang.String as[])
    {
        java.util.Iterator iterator = hashmap.keySet().iterator();
        while (iterator.hasNext()) {
            java.lang.String s = (java.lang.String)iterator.next();
            java.lang.Integer integer = (java.lang.Integer)hashmap.get(s);
            if(as[integer.intValue()] == "")
            {
                as[integer.intValue()] = calculateValueForDerivedCounter(s, internalImpliedCountersList);
            }
        } 
    }

    private java.lang.String calculateValueForDerivedCounter(java.lang.String s, java.util.HashMap hashmap)
    {
        java.lang.String s1 = null;
        java.lang.String s2 = null;
        java.lang.String s3 = getFormulaForCounter(s);
        if(s3 == null)
        {
            return "";
        }
        int i = s3.indexOf("=");
        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s3.substring(i + 1), " ");
        for(int j = 0; j < as.length; j++)
        {
            java.lang.String s4 = as[j];
            if(!isOperator(s4))
            {
                s4 = (java.lang.String)hashmap.get(qualifyCounterName(s, s4));
                if(s4 == null || s4 == "")
                {
                    return "";
                }
            }
            if(s1 == null)
            {
                s1 = s4;
                continue;
            }
            if(s2 == null)
            {
                s2 = s4;
            } else
            {
                s1 = calculate(s1, s2, s4);
                s2 = null;
            }
        }

        return s1;
    }

    private java.util.Set getImpliedCountersForDerivedCounter(java.lang.String s)
    {
        java.util.HashSet hashset = new HashSet();
        java.lang.String s1 = getFormulaForCounter(s);
        int i = s1.indexOf("=");
        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s1.substring(i + 1), " ");
        for(int j = 0; j < as.length; j++)
        {
            java.lang.String s2 = as[j].trim();
            if(!isOperator(s2))
            {
                java.lang.String s3 = qualifyCounterName(s, s2);
                hashset.add(s3);
            }
        }

        return hashset;
    }

    private boolean isOperator(java.lang.String s)
    {
        return "+/-*%".indexOf(s) >= 0;
    }

    private java.lang.String getGenericNameForCounter(java.lang.String s)
    {
        java.lang.String s1 = s;
        int i = s1.indexOf('@');
        if(i > 0)
        {
            int j = s1.lastIndexOf('/', i);
            int k = s1.indexOf("/", i);
            s1 = s1.substring(j, i) + s1.substring(k);
        } else
        {
            s1 = com.dragonflow.StandardMonitor.SunOneMonitor.extractAdequateCounterName(s1, true);
        }
        return s1;
    }

    private java.lang.String getFormulaForCounter(java.lang.String s)
    {
        java.lang.String s1 = getGenericNameForCounter(s);
        java.lang.String s2 = null;
        for(int i = 0; i < externalDerivedCounterFormulas.length; i++)
        {
            java.lang.String s3 = externalDerivedCounterFormulas[i];
            int j = s3.indexOf('=');
            if(j <= 0)
            {
                continue;
            }
            java.lang.String s4 = s3.substring(0, j - 1).trim();
            if(!smartStringIsEqual(s4, s1))
            {
                continue;
            }
            s2 = s3;
            break;
        }

        return s2;
    }

    private boolean smartStringIsEqual(java.lang.String s, java.lang.String s1)
    {
        java.lang.String s2 = s1;
        if(s.charAt(0) == '/')
        {
            if(s1.charAt(0) != '/')
            {
                s2 = "/" + s1;
            }
        } else
        if(s1.charAt(0) == '/')
        {
            s2 = s1.substring(1);
        }
        return s.equalsIgnoreCase(s2);
    }

    private java.lang.String calculate(java.lang.String s, java.lang.String s1, java.lang.String s2)
    {
        Object obj = null;
        float f = 0.0F;
        float f1 = (new Float(s)).floatValue();
        float f2 = (new Float(s2)).floatValue();
        if(s1.equals("+"))
        {
            f = f1 + f2;
        } else
        if(s1.equals("/"))
        {
            if(f2 <= 0.0F)
            {
                return "No Activity";
            }
            f = f1 / f2;
        } else
        if(s1.equals("-"))
        {
            f = f1 - f2;
        } else
        if(s1.equals("*"))
        {
            f = f1 * f2;
        } else
        if(s1.equals("%"))
        {
            if(f1 + f2 <= 0.0F)
            {
                return "No Activity";
            }
            f = f1 / (f1 + f2);
        } else
        {
            java.lang.System.out.println("Unrecognized Operator: " + s1);
        }
        f *= 100F;
        return java.lang.Float.toString(f);
    }
}
