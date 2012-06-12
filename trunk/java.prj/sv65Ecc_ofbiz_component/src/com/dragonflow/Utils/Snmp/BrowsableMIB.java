/*
 * 
 * Created on 2005-3-9 18:55:36
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Utils.Snmp;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Stack;
import java.util.TreeMap;
import java.util.Vector;

import com.dragonflow.Utils.RawXmlWriter;

import com.netaphor.mibcompiler.MIBCompiler;
import com.netaphor.snmp.OID;

// Referenced classes of package com.dragonflow.Utils.Snmp:
// BrowsableMIBException, OIDComparator, SNMPSession

public class BrowsableMIB {

    public static final String ALL_MIBS = "All MIBs";

    public static final String NO_MIBS_AVAIL = "No MIBs Available";

    private static final String MIBPath;

    private static com.dragonflow.Utils.Snmp.BrowsableMIB bMIBInstance = null;

    private static Object classLockObject = new Object();

    private com.netaphor.mibcompiler.MIB mibs[];

    private java.util.TreeMap MIBNodeLookupTree;

    private com.netaphor.mibcompiler.MIBCompiler compiler;

    static final boolean $assertionsDisabled; /* synthetic field */

    private BrowsableMIB() throws java.io.IOException, com.dragonflow.Utils.Snmp.BrowsableMIBException {
        java.io.File file = new File(MIBPath);
        if (!file.exists()) {
            throw new FileNotFoundException("Could not find MIB directory: " + MIBPath);
        }
        String as[] = file.list();
        if (!$assertionsDisabled && as == null) {
            throw new AssertionError();
        }
        java.util.Vector vector = new Vector(as.length);
        for (int i = 0; i < as.length; i ++) {
            vector.add(as[i]);
        }

        compiler = new MIBCompiler();
        java.util.Vector vector1 = new Vector();
        java.util.HashMap hashmap = new HashMap();
        int j;
        do {
            if (vector.size() <= 0) {
                break;
            }
            j = vector.size();
            vector1.clear();
            for (int k = 0; k < vector.size();k++) {
                String s = file + java.io.File.separator + (String) vector.get(k);
                try {
					//s=s.replace('\\','/');
					
					compiler.compileFromFile(s);
                    vector1.add(new Integer(k));
                    continue;
                } catch (com.netaphor.mibcompiler.SyntaxError syntaxerror) {
                    int j1 = syntaxerror.getErrorCode();
                    StringBuffer stringbuffer = new StringBuffer(syntaxerror.getMessage());
                    stringbuffer.append(", at line ").append(syntaxerror.getLineNumber()).append(", while compiling ").append((String) vector.get(k));
                    switch (j1) {
                    case 3: // '\003'
                        hashmap.put(vector.get(k), stringbuffer.toString());
						
                        break;

                    case 2: // '\002'
                        vector1.add(new Integer(k));
						
                        break;

                    case 1: // '\001'
                        com.dragonflow.Log.LogManager.log("Error", stringbuffer.toString());
                        vector1.add(new Integer(k));
						
                        break;

                    default:
                        throw new BrowsableMIBException("Uknown syntax error while compiling " + s + ": " + syntaxerror.getMessage());
                    }
                   // k ++; dingbing.xu
                }
            }
			
				/*
             for (int l = vector1.size() - 1; l > 0; l --) 
			 {
				vector.remove(((Integer)vector1.get(l)).intValue());
            }*/
			

        } while (j != vector.size());
        mibs = compiler.getMIBs();
        MIBNodeLookupTree = populateLookupTree();
        for (int i1 = 0; i1 < vector.size(); i1 ++) {
            String s1 = (String) vector.get(i1);
            String s2 = (String) hashmap.get(s1);
            if (s2 != null) {
                com.dragonflow.Log.LogManager.log("Error", s2);
            } else {
                com.dragonflow.Log.LogManager.log("Error", "BrowsableMIB constructor failed to compile: " + vector.get(i1));
            }
        }

    }

    private java.util.TreeMap populateLookupTree() {
        java.util.TreeMap treemap = new TreeMap(new OIDComparator());
        for (int i = 0; i < mibs.length; i ++) {
            com.netaphor.mibcompiler.MIBNode amibnode[] = mibs[i].getNodes();
            for (int j = 0; j < amibnode.length; j ++) {
                treemap.put(amibnode[j].getOID(), amibnode[j]);
            }

        }

        return treemap;
    }

    public static com.dragonflow.Utils.Snmp.BrowsableMIB getInstance() throws java.io.IOException, com.dragonflow.Utils.Snmp.BrowsableMIBException {
        if (bMIBInstance == null) {
            synchronized (classLockObject) {
                if (bMIBInstance == null) {
                    bMIBInstance = new BrowsableMIB();
                }
            }
        }
        return bMIBInstance;
    }

    public String getMIBPath() {
        return MIBPath;
    }

    public boolean containsMIB(String s) {
        return getMIBFromMIBFileName(s) != null;
    }

    private com.netaphor.mibcompiler.MIB getMIBFromMIBFileName(String s) {
        java.io.File file = new File(s);
        String s1 = null;
        if (!file.isAbsolute()) {
            s1 = MIBPath + java.io.File.separator + s;
        } else {
            s1 = s;
        }
        for (int i = 0; i < mibs.length; i ++) {
            if (mibs[i].getSource().equals(s1)) {
                return mibs[i];
            }
        }

        return null;
    }

    public String getXML(com.dragonflow.Utils.Snmp.SNMPSession snmpsession, String s, StringBuffer stringbuffer) {
        stringbuffer.setLength(0);
        boolean flag = s.equals("All MIBs");
        StringBuffer stringbuffer1 = new StringBuffer();
        com.dragonflow.Utils.RawXmlWriter rawxmlwriter = new RawXmlWriter(stringbuffer1);
        java.util.Stack stack = new Stack();
        com.netaphor.mibcompiler.MIB mib = null;
        if (!flag) {
            mib = getMIBFromMIBFileName(s);
        }
        com.netaphor.snmp.VariableBinding avariablebinding[] = snmpsession.getColumn("1");
        rawxmlwriter.startElement("browse_data");
        String s1 = new String(stringbuffer1);
        if (avariablebinding == null || avariablebinding.length <= 0) {
            rawxmlwriter.endElement("browse_data");
            stringbuffer.append("No counters detected (no OIDs could be found on the specified server).");
            return stringbuffer1.toString();
        }
        Object obj = null;
        for (int i = 0; i < avariablebinding.length; i ++) {
            com.netaphor.snmp.OID oid = avariablebinding[i].getOid();
            com.netaphor.mibcompiler.MIBNode mibnode = (com.netaphor.mibcompiler.MIBNode) MIBNodeLookupTree.get(oid);
            if (snmpsession.formatOctetString(avariablebinding[i]).equals("NOT DISPLAYABLE")) {
                continue;
            }
            String s2;
            if (mibnode == null) {
                if ((mibnode = getClosestAncestor(oid)) == null) {
                    com.dragonflow.Log.LogManager.log("Error", "No closest ancestor could be found for OID: " + oid.toString());
                    continue;
                }
                s2 = getFullName(mibnode, oid);
            } else {
                s2 = getFullName(mibnode);
            }
            if (!flag && mibnode.getMIB() != mib) {
                continue;
            }
            if (stack.size() == 0 || !stack.peek().equals(s2)) {
                String s3 = "!";
                if (stack.size() > 0) {
                    s3 = (String) stack.peek();
                }
                for (; !s2.startsWith(s3) && stack.size() > 0; s3 = (String) stack.peek()) {
                    rawxmlwriter.endElement("object");
                    stack.pop();
                }

                String as[] = com.dragonflow.Utils.TextUtils.split(s2, ".");
                String as1[] = com.dragonflow.Utils.TextUtils.split(s3, ".");
                String s4 = "";
                for (int j = 0; j < as.length; j ++) {
                    if (j > 0) {
                        s4 = s4 + ".";
                    }
                    s4 = s4 + as[j];
                    if (j >= as1.length || !as1[j].equals(as[j])) {
                        com.netaphor.mibcompiler.MIBNode mibnode1 = getNode(as[j], oid);
                        outputObject(rawxmlwriter, mibnode1, as[j]);
                        stack.push(s4);
                    }
                }

            }
            outputCounter(rawxmlwriter, snmpsession, mibnode, avariablebinding[i]);
        }

        for (; stack.size() > 0; rawxmlwriter.endElement("object")) {
            stack.pop();
        }

        if (s1.equals(stringbuffer1.toString())) {
            stringbuffer.setLength(0);
            stringbuffer.append("No counters within the selected MIB were detected (no OIDs in MIB " + s + " could be found on the specified server).");
        }
        rawxmlwriter.endElement("browse_data");
        return stringbuffer1.toString();
    }

    private com.netaphor.mibcompiler.MIBNode getNode(String s, com.netaphor.snmp.OID oid) {
        com.netaphor.mibcompiler.MIBNode amibnode[];
        if ((amibnode = compiler.lookupAll(s)) == null) {
            return null;
        }
        for (int i = 0; i < amibnode.length; i ++) {
            com.netaphor.snmp.OID oid1 = amibnode[i].getOID();
            if (oid.startsWith(oid1)) {
                return amibnode[i];
            }
        }

        return null;
    }

    private void outputCounter(com.dragonflow.Utils.RawXmlWriter rawxmlwriter, com.dragonflow.Utils.Snmp.SNMPSession snmpsession, com.netaphor.mibcompiler.MIBNode mibnode, com.netaphor.snmp.VariableBinding variablebinding) {
        com.netaphor.snmp.OID oid = variablebinding.getOid();
        com.netaphor.snmp.Variable variable = variablebinding.getVariable();
        String s = null;
        if (variable.getSyntax() == 4) {
            s = snmpsession.formatOctetString(variablebinding);
        } else {
            s = variable.toString();
        }
        if (s.equals("NOT DISPLAYABLE")) {
            return;
        }
        String s1 = mibnode.getName();
        if (mibnode.getOID().length() < oid.length()) {
            for (int i = mibnode.getOID().length(); i < oid.length(); i ++) {
                s1 = s1 + "." + oid.getAt(i);
            }

        }
        String s2 = null;
        com.netaphor.mibcompiler.ObjectType objecttype;
        if ((objecttype = mibnode.getObjectType()) != null) {
            s2 = objecttype.getDescription();
        }
        String s3 = oid.toString();
        StringBuffer stringbuffer = new StringBuffer("counter name=\"" + rawxmlwriter.xmlEncode(s1) + "\" ");
        stringbuffer.append(" id=\"" + rawxmlwriter.xmlEncode(s3) + "\"");
        if (s2 != null) {
            stringbuffer.append(" desc=\"" + rawxmlwriter.xmlEncode(s2) + "\" ");
        }
        stringbuffer.append(" value=\"" + rawxmlwriter.xmlEncode(s) + "\" ");
        rawxmlwriter.emptyElement(stringbuffer.toString());
    }

    private void outputObject(com.dragonflow.Utils.RawXmlWriter rawxmlwriter, com.netaphor.mibcompiler.MIBNode mibnode, String s) {
        StringBuffer stringbuffer = new StringBuffer("object name=\"" + rawxmlwriter.xmlEncode(s) + "\" ");
        com.netaphor.mibcompiler.ObjectType objecttype;
        if (mibnode != null && (objecttype = mibnode.getObjectType()) != null) {
            String s1 = null;
            if ((s1 = objecttype.getDescription()) != null) {
                stringbuffer.append(" desc=\"" + rawxmlwriter.xmlEncode(s1) + "\" ");
            }
        }
        rawxmlwriter.startElement(stringbuffer.toString());
    }

    private String getFullName(com.netaphor.mibcompiler.MIBNode mibnode) {
        StringBuffer stringbuffer = new StringBuffer(mibnode.getFullName());
        int i = stringbuffer.lastIndexOf(".");
        int j = stringbuffer.length();
        if (i > 0) {
            stringbuffer.delete(i, j);
        }
        return stringbuffer.toString();
    }

    private String getFullName(com.netaphor.mibcompiler.MIBNode mibnode, com.netaphor.snmp.OID oid) {
        StringBuffer stringbuffer = new StringBuffer(mibnode.getFullName());
        com.netaphor.snmp.OID oid1 = mibnode.getOID();
        int i = oid1.length();
        int j = oid.length() - 1;
        for (int k = i; k < j; k ++) {
            stringbuffer.append("." + oid.getAt(k));
        }

        return stringbuffer.toString();
    }

    private com.netaphor.mibcompiler.MIBNode getClosestAncestor(com.netaphor.snmp.OID oid) {
        com.netaphor.mibcompiler.MIBNode mibnode = null;
        for (com.netaphor.snmp.OID oid1 = new OID(oid.toString()); mibnode == null && oid1.length() > 0; oid1.trim(1)) {
            mibnode = (com.netaphor.mibcompiler.MIBNode) MIBNodeLookupTree.get(oid1);
        }

        return mibnode;
    }

    protected com.netaphor.mibcompiler.MIBNode getLeafNode(com.netaphor.snmp.OID oid) {
        com.netaphor.mibcompiler.MIBNode mibnode = null;
        for (com.netaphor.snmp.OID oid1 = new OID(oid.toString()); mibnode == null && oid1.length() > 0; oid1.trim(1)) {
            mibnode = (com.netaphor.mibcompiler.MIBNode) MIBNodeLookupTree.get(oid1);
        }

        if (isLeafNode(mibnode)) {
            return mibnode;
        } else {
            return null;
        }
    }

    private boolean isLeafNode(com.netaphor.mibcompiler.MIBNode mibnode) {
        return mibnode != null && mibnode.getChildren().length == 0;
    }

    public String[] getCompiledMIBs() {
        int i = mibs.length + 1;
        String as[] = new String[i];
        if (mibs.length == 0) {
            as[0] = "No MIBs Available";
            return as;
        }
        as[0] = "All MIBs";
        for (int j = 1; j < i; j ++) {
            as[j] = mibs[j - 1].getSource();
        }

        return as;
    }

    static {
        $assertionsDisabled = !(com.dragonflow.Utils.Snmp.BrowsableMIB.class).desiredAssertionStatus();
        MIBPath = com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "templates.mib";
    }
}
