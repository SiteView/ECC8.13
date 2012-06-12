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

// Referenced classes of package com.dragonflow.Chart:
// AppletLineChart
public class AppletDataSet {

    int index;

    int currentDataIndex;

    boolean sampleHasValue;

    long sampleTime;

    java.lang.String sampleCategory;

    float sampleValue;

    java.lang.String sampleString;

    float scale;

    java.lang.String average;

    java.lang.String maximum;

    java.lang.String maximumTime;

    java.lang.String minimum;

    java.lang.String minimumTime;

    java.lang.String errorPercentage;

    java.lang.String errorTime;

    boolean averagedSamples;

    int bucketCount;

    long firstTime;

    long lastTime;

    java.lang.String data;

    java.lang.String name;

    java.awt.Color color;

    java.lang.StringBuffer sampleBuffer;

    AppletDataSet(java.lang.String s) {
        index = 0;
        currentDataIndex = 0;
        sampleHasValue = false;
        sampleTime = 0L;
        sampleCategory = "";
        sampleValue = 0.0F;
        sampleString = "";
        scale = 1.0F;
        average = "";
        maximum = "";
        maximumTime = "";
        minimum = "";
        minimumTime = "";
        errorPercentage = "";
        errorTime = "";
        averagedSamples = false;
        bucketCount = 0;
        firstTime = 0L;
        lastTime = 0L;
        data = "";
        name = "untitled";
        color = java.awt.Color.black;
        sampleBuffer = new StringBuffer();
        data = s;
    }

    void sampleStart() {
        currentDataIndex = 0;
    }

    boolean isErrorSample() {
        return sampleCategory.equals("e") || sampleString.equals("n/a");
    }

    boolean isErrorCategorySample() {
        return sampleCategory.equals("e");
    }

    boolean isDisabledSample() {
        return sampleCategory.equals("d");
    }

    boolean isWarningSample() {
        return sampleCategory.equals("w");
    }

    boolean isOKSample() {
        return sampleCategory.equals("g");
    }

    boolean nextSample() {
        if (currentDataIndex < data.length()) {
            long l = 0L;
            sampleCategory = "";
            sampleString = "";
            sampleValue = 0.0F;
            sampleHasValue = false;
            sampleBuffer.setLength(0);
            boolean flag = true;
            boolean flag1 = false;
            boolean flag2 = false;
            for (; currentDataIndex < data.length(); currentDataIndex ++) {
                char c = data.charAt(currentDataIndex);
                if (flag) {
                    if (sampleTime == 0L) {
                        l = com.dragonflow.Chart.AppletLineChart.stringToDate(data).getTime();
                        currentDataIndex = data.indexOf('$') + 1;
                        if (currentDataIndex < data.length()) {
                            c = data.charAt(currentDataIndex);
                        } else {
                            c = ' ';
                        }
                    }
                    if (java.lang.Character.isDigit(c)) {
                        l = l * 10L + (long) java.lang.Character.digit(c, 10);
                    } else {
                        flag = false;
                        flag1 = true;
                        if (sampleTime != 0L) {
                            sampleTime += l * 1000L;
                        } else {
                            sampleTime = l;
                        }
                    }
                }
                if (flag1) {
                    sampleCategory += c;
                    flag1 = false;
                    flag2 = true;
                    currentDataIndex ++;
                    if (currentDataIndex >= data.length()) {
                        break;
                    }
                    c = data.charAt(currentDataIndex);
                }
                if (!flag2) {
                    continue;
                }
                if (c == '|') {
                    currentDataIndex ++;
                    break;
                }
                sampleBuffer.append(c);
            }

            if (flag2) {
                sampleString = sampleBuffer.toString();
                try {
                    if (!sampleString.equals("n/a")) {
                        sampleValue = java.lang.Float.valueOf(sampleString).floatValue();
                        sampleHasValue = true;
                    }
                } catch (java.lang.NumberFormatException numberformatexception) {
                    sampleValue = 0.0F;
                }
            }
            return flag2;
        } else {
            return false;
        }
    }
}
