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

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.StringTokenizer;

//import com.dragonflow.infra.xdr.XDRMemInputStream;
//import com.dragonflow.infra.xdr_utils.PropertyBag;

// Referenced classes of package com.dragonflow.Utils:
// Base64Encoder, Base64Decoder

public class SerializerUtils {

    public SerializerUtils() {
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param propertybag
     * @return
     */
//    public static String encodePropBagToString(com.dragonflow.infra.xdr_utils.PropertyBag propertybag) {
//        Object obj = null;
//        String s;
//        try {
//            byte abyte0[] = propertybag.encode();
//            s = com.dragonflow.Utils.SerializerUtils.encodeByteArrayToString(abyte0);
//            return s;
//        } catch (com.dragonflow.infra.xdr.XDRException xdrexception) {
//            xdrexception.printStackTrace();
//            com.dragonflow.Log.LogManager.logException(xdrexception);
//            return null;
//        }
//    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param serializable
     * @return
     */
    public static String encodeObject(java.io.Serializable serializable) {
        if (serializable == null) {
            return "";
        }
        java.io.ByteArrayOutputStream bytearrayoutputstream;
        java.io.ObjectOutputStream objectoutputstream = null;
        bytearrayoutputstream = new ByteArrayOutputStream();
        try {
            objectoutputstream = new ObjectOutputStream(bytearrayoutputstream);
            objectoutputstream.writeObject(serializable);
            return com.dragonflow.Utils.SerializerUtils.encodeByteArrayToString(bytearrayoutputstream.toByteArray());
        } catch (java.io.IOException ioexception) {
            ioexception.printStackTrace();
            com.dragonflow.Log.LogManager.log("Error", ioexception.getMessage());
            return null;
        }
    }

    public static String encodeObjectBase64(java.io.Serializable serializable) {
        return com.dragonflow.Utils.SerializerUtils.encodeObjectBase64(serializable, true);
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param serializable
     * @param flag
     * @return
     */
    public static String encodeObjectBase64(java.io.Serializable serializable, boolean flag) {
        if (serializable == null) {
            return "";
        }
        String s;
        try {
            java.io.ByteArrayOutputStream bytearrayoutputstream = new ByteArrayOutputStream();
            java.io.ObjectOutputStream objectoutputstream = new ObjectOutputStream(bytearrayoutputstream);
            objectoutputstream.writeObject(serializable);
            java.io.ByteArrayInputStream bytearrayinputstream = new ByteArrayInputStream(bytearrayoutputstream.toByteArray());
            bytearrayoutputstream.reset();
            com.dragonflow.Utils.Base64Encoder base64encoder = new Base64Encoder(bytearrayinputstream, bytearrayoutputstream);
            base64encoder.process();
            s = bytearrayoutputstream.toString();
            if (flag) {
                return s;
            }
            return s.replaceAll("\n|\r", "");
        } catch (java.io.IOException ioexception) {
            ioexception.printStackTrace();
            com.dragonflow.Log.LogManager.log("Error", ioexception.getMessage());
            return null;
        }
    }

    public static java.io.Serializable decodeJavaObjectFromStringBase64(String s) {
        return com.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromByteArray(com.dragonflow.Utils.SerializerUtils.decodeBytesFromStringBase64(s));
    }

    public static java.io.Serializable decodeJavaObjectFromString(String s) {
        return com.dragonflow.Utils.SerializerUtils.decodeJavaObjectFromByteArray(com.dragonflow.Utils.SerializerUtils.decodeBytesFromString(s));
    }

//    public static com.dragonflow.infra.xdr_utils.PropertyBag decodePropBagFromString(String s) {
//        return com.dragonflow.Utils.SerializerUtils.decodePropBagFromByteArray(com.dragonflow.Utils.SerializerUtils.decodeBytesFromString(s));
//    }

    private static String encodeByteArrayToString(byte abyte0[]) {
        StringBuffer stringbuffer = new StringBuffer();
        for (int i = 0; i < abyte0.length; i ++) {
            stringbuffer.append(abyte0[i]);
            stringbuffer.append('.');
        }

        return stringbuffer.toString();
    }

    private static byte[] decodeBytesFromString(String s) {
        if (s == null || s.length() == 0) {
            return null;
        }
        java.util.StringTokenizer stringtokenizer = new StringTokenizer(s, ".");
        byte abyte0[] = new byte[stringtokenizer.countTokens()];
        for (int i = 0; stringtokenizer.hasMoreElements(); i ++) {
            try {
                abyte0[i] = (byte) Integer.parseInt((String) stringtokenizer.nextElement());
            } catch (NumberFormatException numberformatexception) {
                numberformatexception.printStackTrace();
            }
        }

        return abyte0;
    }

    private static byte[] decodeBytesFromStringBase64(String s) {
        if (s == null || s.length() == 0) {
            return null;
        }
        byte abyte0[] = null;
        com.dragonflow.Utils.Base64Decoder base64decoder = new Base64Decoder(s);
        try {
            abyte0 = base64decoder.processBytes();
        } catch (Exception exception) {
            exception.printStackTrace();
        }
        return abyte0;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param abyte0
     * @return
     */
    private static java.io.Serializable decodeJavaObjectFromByteArray(byte abyte0[]) {
        if (abyte0 == null || abyte0.length == 0) {
            return null;
        }
        java.io.Serializable serializable;
        try {
            java.io.ByteArrayInputStream bytearrayinputstream = new ByteArrayInputStream(abyte0);
            java.io.ObjectInputStream objectinputstream = new ObjectInputStream(bytearrayinputstream);
            serializable = (java.io.Serializable) objectinputstream.readObject();
            bytearrayinputstream = null;
            objectinputstream = null;
            return serializable;
        } catch (IOException e) {
            e.printStackTrace();
            com.dragonflow.Log.LogManager.logException(e);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            com.dragonflow.Log.LogManager.logException(e);
        }
        return null;
    }

//    private static com.dragonflow.infra.xdr_utils.PropertyBag decodePropBagFromByteArray(byte abyte0[]) {
//        if (abyte0 == null || abyte0.length == 0) {
//            return null;
//        }
//
//        try {
//            com.dragonflow.infra.xdr_utils.PropertyBag propertybag;
//            propertybag = new PropertyBag();
//            com.dragonflow.infra.xdr.XDRMemInputStream xdrmeminputstream = new XDRMemInputStream(abyte0);
//            propertybag.decode(xdrmeminputstream);
//            return propertybag;
//        } catch (com.dragonflow.infra.xdr.XDRException xdrexception) {
//            xdrexception.printStackTrace();
//            com.dragonflow.Log.LogManager.logException(xdrexception);
//            return null;
//        }
//    }
}
