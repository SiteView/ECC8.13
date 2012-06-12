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


// Referenced classes of package com.dragonflow.Utils:
// Expression, BooleanLiteral, ParseException, InterpreterException,
// Literal, TextUtils

public class SimpleExpression extends com.dragonflow.Utils.Expression
{

    com.dragonflow.Utils.Expression left;
    com.dragonflow.Utils.Expression right;
    boolean notEqual;
    boolean equal;
    boolean greaterThan;
    boolean lessThan;
    boolean contains;
    boolean notContains;
    boolean multipleOf;

    public com.dragonflow.Utils.Expression getLeft()
    {
        return left;
    }

    public com.dragonflow.Utils.Expression getRight()
    {
        return right;
    }

    static com.dragonflow.Utils.Expression parse(String as[], int i, int j)
        throws com.dragonflow.Utils.ParseException
    {
        if(j - i == 2)
        {
            com.dragonflow.Utils.Expression expression = com.dragonflow.Utils.Literal.parse(as[i]);
            String s = as[i + 1];
            com.dragonflow.Utils.Expression expression1 = com.dragonflow.Utils.Literal.parse(as[i + 2]);
            return new SimpleExpression(expression, s, expression1);
        }
        if(i == j)
        {
            return new BooleanLiteral(as[i]);
        } else
        {
            throw new ParseException("Improper expression: \"" + com.dragonflow.Utils.SimpleExpression.getTokenString(as, i, j) + "\"");
        }
    }

    SimpleExpression(com.dragonflow.Utils.Expression expression, String s, com.dragonflow.Utils.Expression expression1)
    {
        notEqual = false;
        equal = false;
        greaterThan = false;
        lessThan = false;
        contains = false;
        notContains = false;
        multipleOf = false;
        left = expression;
        right = expression1;
        if(s.indexOf('>') >= 0)
        {
            greaterThan = true;
        }
        if(s.indexOf('<') >= 0)
        {
            lessThan = true;
        }
        if(s.indexOf('=') >= 0)
        {
            equal = true;
        }
        if(s.indexOf('!') >= 0)
        {
            notEqual = true;
        }
        if(s.equals("eq"))
        {
            equal = true;
        }
        if(s.equals("ne"))
        {
            notEqual = true;
        }
        if(s.equals("contains"))
        {
            contains = true;
        }
        if(s.equals("doesNotContain"))
        {
            notContains = true;
        }
        if(s.equals("multipleOf"))
        {
            multipleOf = true;
        }
        if(greaterThan && lessThan)
        {
            notEqual = true;
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     */
    Object interpret(com.dragonflow.SiteView.SiteViewObject siteviewobject, com.dragonflow.SiteView.Rule rule)
        throws com.dragonflow.Utils.InterpreterException
    {
        Object obj = left.interpret(siteviewobject, rule);
        Object obj1 = right.interpret(siteviewobject, rule);
        if((obj instanceof Number) || (obj1 instanceof Number))
        {
            Object obj2;
            if(obj instanceof String)
            {
                if(obj.equals("n/a"))
                {
                    return new Boolean(false);
                }
                try
                {
                    obj2 = Float.valueOf((String)obj);
                }
                catch(Exception exception)
                {
                    obj2 = new Float(0.0F);
                }
            } else
            {
                obj2 = (Number)obj;
            }
            Object obj3;
            if(obj1 instanceof String)
            {
                if(obj1.equals("n/a"))
                {
                    return new Boolean(false);
                }
                try
                {
                    obj3 = Float.valueOf((String)obj1);
                }
                catch(Exception exception1)
                {
                    obj3 = new Float(0.0F);
                }
            } else
            {
                obj3 = (Number)obj1;
            }
            float f = ((Number) (obj2)).floatValue();
            float f1 = ((Number) (obj3)).floatValue();
            if(notEqual)
            {
                return new Boolean(f != f1);
            }
            if(greaterThan && equal)
            {
                return new Boolean(f >= f1);
            }
            if(lessThan && equal)
            {
                return new Boolean(f <= f1);
            }
            if(greaterThan)
            {
                return new Boolean(f > f1);
            }
            if(lessThan)
            {
                return new Boolean(f < f1);
            }
            if(equal)
            {
                return new Boolean(f == f1);
            }
            if(multipleOf)
            {
                long l = (long)f;
                long l1 = (long)(f1 * 1000F + 0.1F);
                long l2 = l1 / 1000L;
                long l3 = l1 % 1000L;
                boolean flag1 = false;
                if(l2 > 0L)
                {
                    flag1 = l % l2 == l3;
                }
                return new Boolean(flag1);
            } else
            {
                return new Boolean(false);
            }
        }
        boolean flag;
        if(contains || notContains)
        {
            flag = com.dragonflow.Utils.TextUtils.match((String)obj, (String)obj1);
            if(notContains)
            {
                return new Boolean(!flag);
            }
        } else
        if(equal || notEqual)
        {
            flag = ((String)obj).equalsIgnoreCase((String)obj1);
            if(notEqual)
            {
                return new Boolean(!flag);
            }
        } else
        {
            throw new InterpreterException("Unknown string comparison: " + obj + "," + obj1);
        }
        return new Boolean(flag);
    }

    public String toString(com.dragonflow.SiteView.SiteViewObject siteviewobject)
    {
        String s = left.toString(siteviewobject);
        String s1 = right.toString(siteviewobject);
        String s2 = "";
        if(notEqual)
        {
            s2 = " != ";
        } else
        if(greaterThan && equal)
        {
            s2 = " >= ";
        } else
        if(lessThan && equal)
        {
            s2 = " <= ";
        } else
        if(greaterThan)
        {
            s2 = " > ";
        } else
        if(lessThan)
        {
            s2 = " < ";
        } else
        if(equal)
        {
            s2 = " == ";
        } else
        if(multipleOf)
        {
            s2 = " multipleOf ";
        } else
        if(contains)
        {
            s2 = " contains ";
        } else
        if(notContains)
        {
            s2 = " doesNotContain ";
        } else
        {
            s2 = " UNKNOWN_COMPARE_OPERATOR ";
        }
        return s + s2 + s1;
    }
}
