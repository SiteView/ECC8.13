/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Chart;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */
import java.util.Hashtable;

import com.dragonflow.Chart.GD.GDImage;
import com.dragonflow.Chart.GD.GDMediumBoldFont;
import com.dragonflow.Chart.GD.GDSmallFont;
import com.dragonflow.Chart.GD.GDTinyFont;

// Referenced classes of package com.dragonflow.Chart:
// Drawer

public class DrawerGD extends com.dragonflow.Chart.Drawer {

    com.dragonflow.Chart.GD.GDImage image;

    com.dragonflow.Chart.GD.GDFont gdfont;

    int colorIndex;

    int white;

    int black;

    java.util.Hashtable colorMap;

    public static final int LEFT_JUSTIFIED = 0;

    public static final int CENTER_JUSTIFIED = 1;

    public static final int RIGHT_JUSTIFIED = 2;

    com.dragonflow.Chart.GD.GDFont tinyFont;

    com.dragonflow.Chart.GD.GDFont smallFont;

    com.dragonflow.Chart.GD.GDFont mediumFont;

    com.dragonflow.Chart.GD.GDFont largeFont;

    public DrawerGD(int i, int j) {
        super(i, j);
        image = null;
        gdfont = null;
        colorIndex = 0;
        white = 0;
        black = 1;
        colorMap = new Hashtable();
        tinyFont = null;
        smallFont = null;
        mediumFont = null;
        largeFont = null;
        image = new GDImage(i, j);
        white = image.colorAllocate(255, 255, 255);
        colorMap.put(java.awt.Color.white, new Integer(white));
        black = image.colorAllocate(0, 0, 0);
        colorMap.put(java.awt.Color.black, new Integer(black));
    }

    public void startDraw() {
        super.startDraw();
        image.drawFilledRectangle(0, 0, width, height, white);
        setFont("Helvetica", "plain", 10);
        colorIndex = black;
    }

    public void endDraw() {
        super.endDraw();
    }

    public int[] getPixels() {
        return image.getPixels();
    }

    public void setPenColor(java.awt.Color color) {
        super.setPenColor(color);
        Integer integer = (Integer) colorMap.get(color);
        if (integer == null) {
            colorIndex = image.colorAllocate(color.getRed(), color.getGreen(), color.getBlue());
            colorMap.put(color, new Integer(colorIndex));
        } else {
            colorIndex = integer.intValue();
        }
    }

    public void drawLine(int i, int j, int k, int l) {
        image.drawLine(i, j, k, l, colorIndex);
    }

    public void drawDashedLine(int i, int j, int k, int l) {
        image.drawDashedLine(i, j, k, l, colorIndex);
    }

    public void drawRectangle(int i, int j, int k, int l) {
        image.drawRectangle(i, j, i + k, j + l, colorIndex);
    }

    public void fillRectangle(int i, int j, int k, int l) {
        image.drawFilledRectangle(i, j, i + k, j + l, colorIndex);
    }

    public void drawStringJustified(int i, int j, String s, int k) {
        image.drawStringJustified(gdfont, i, j, com.dragonflow.Chart.DrawerGD.stripDoubleByte(s), black, k);
    }

    public void drawString(int i, int j, String s) {
        image.drawString(gdfont, i, j, com.dragonflow.Chart.DrawerGD.stripDoubleByte(s), colorIndex);
    }

    public void drawStringUp(int i, int j, String s) {
        image.drawStringUp(gdfont, i, j, com.dragonflow.Chart.DrawerGD.stripDoubleByte(s), colorIndex);
    }

    static boolean isDoubleByte(char c) {
        if (c >= '\201' && c <= '\237' || c >= '\340' && c <= '\357') {
            return true;
        }
        return c >= '\241' && c <= '\376';
    }

    static String stripDoubleByte(String s) {
        StringBuffer stringbuffer = new StringBuffer(s.length());
        for (int i = 0; i < s.length();) {
            char c = s.charAt(i ++);
            if (com.dragonflow.Chart.DrawerGD.isDoubleByte(c)) {
                i ++;
            } else {
                stringbuffer.append(c);
            }
        }

        return stringbuffer.toString();
    }

    public int stringWidth(String s) {
        return gdfont.getStringWidth(s);
    }

    public int stringHeight() {
        return gdfont.getHeight();
    }

    public void setFont(String s, String s1, int i) {
        if (setFontCharacteristics(s, s1, i)) {
            gdfont = null;
            try {
                switch (i) {
                case 10: // '\n'
                    if (smallFont == null) {
                        smallFont = new GDSmallFont();
                    }
                    gdfont = smallFont;
                    break;

                case 9: // '\t'
                    if (tinyFont == null) {
                        tinyFont = new GDTinyFont();
                    }
                    gdfont = tinyFont;
                    break;

                case 12: // '\f'
                    if (mediumFont == null) {
                        mediumFont = new GDMediumBoldFont();
                    }
                    gdfont = mediumFont;
                    break;
                }
            } catch (NoClassDefFoundError noclassdeffounderror) {
            }
            if (gdfont == null) {
                if (smallFont == null) {
                    smallFont = new GDSmallFont();
                }
                gdfont = smallFont;
            }
        }
    }
}
