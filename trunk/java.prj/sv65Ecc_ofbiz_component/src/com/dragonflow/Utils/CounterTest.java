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
// CounterLock
class CounterTest extends Thread {

    com.dragonflow.Utils.CounterLock lock;

    int delay1;

    int delay2;

    static int nameCounter = 10;

    int name;

    CounterTest(com.dragonflow.Utils.CounterLock counterlock, int i, int j) {
        lock = counterlock;
        delay1 = i;
        delay2 = j;
        name = nameCounter ++;
    }

    public void run() {
        for (int i = 1; i < 1000; i ++) {
            try {
                Thread.sleep(delay1);
                System.out.println(name + ": getting");
                int j = lock.get();
                System.out.println(name + ":  got it=" + j);
                Thread.sleep(delay2);
                j = lock.release();
                System.out.println(name + ": release=" + j);
            } catch (Exception exception) {
            }
        }

    }

}
