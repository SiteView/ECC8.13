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

import java.util.Vector;

// Referenced classes of package com.dragonflow.Utils:
// TextUtils

public class ThreadPool {
    public static interface ICreateThreadNotify {

        public abstract void newThreadNotification(SingleThread singlethread);

        public abstract void endThreadNotification(SingleThread singlethread);
    }

    public class SingleThread extends Thread {

        volatile Runnable m_taskToRun;

        private com.dragonflow.Utils.ThreadPool m_pool;

        private Object m_bCustomObject;

        private boolean m_bCustProp;

        private boolean m_bIsAlive;

        private int m_priority;

        private String m_name;

        public String getPoolName() {
            return m_pool.getPoolName();
        }

        public void setCustomObject(Object obj) {
            m_bCustomObject = obj;
        }

        public Object getCustomObject() {
            return m_bCustomObject;
        }

        public void setCustomProperty(boolean flag) {
            m_bCustProp = flag;
        }

        public boolean getCustomProperty() {
            return m_bCustProp;
        }

        public boolean isSingleThreadAlive() {
            if (isAlive()) {
                return m_bIsAlive;
            } else {
                com.dragonflow.Log.LogManager.log("Error", "ThreadPool: thread is not alive!");
                return false;
            }
        }

        public void stopSingleThread() {
            m_bIsAlive = false;
        }

        public void setPriorityIfNeeded(int i) {
            if (i != m_priority) {
                setPriority(i);
                m_priority = i;
            }
        }

        public void setNameIfNeeded(String s) {
            if (!s.equals(m_name)) {
                setName(s);
                m_name = s;
            }
        }

	       public void run() {
	            try {
	                if (!com.dragonflow.Utils.ThreadPool.useThreadPool && m_taskToRun != null) {
	                    m_bIsAlive = true;
	                    m_taskToRun.run();
	                    m_bIsAlive = false;
	                }
	                if (m_createThreadNotify != null) {
	                    m_createThreadNotify.newThreadNotification(this);
	                }
	                
	                if (com.dragonflow.Utils.ThreadPool.useThreadPool) {
	                    while (!SingleThread.interrupted()) {
	                        if (m_taskToRun != null) {
	                            m_bIsAlive = true;
	                            try {
	                                m_taskToRun.run();
	                            } catch (Exception exception) {
	                                com.dragonflow.Log.LogManager.log("Error", "ThreadPool: Exception while running a task in thread: " + m_taskToRun.toString() + ", Exception: " + exception.getMessage());
	                            }
	                            m_bIsAlive = false;
	                            synchronized (this) {
	                                m_pool.moveToIdle(this);
	                                m_taskToRun = null;
	                                try {
	                                    wait();
	                                } catch (InterruptedException interruptedexception) {
	                                    break;
	                                }
	                            }
	                        }
	                    }
	                }
	 
	                if (m_createThreadNotify != null) {
	                    m_createThreadNotify.endThreadNotification(this);
	                }
	            } catch (Exception exception1) {
	                com.dragonflow.Log.LogManager.log("Error", "ThreadPool: Failed to execute a thread in the thread pool, Exception: " + exception1.getMessage());
	            }
	        }
		
//        /**
//         * CAUTION: Decompiled by hand.
//         */
//        public void run() {
//            try {
//                if (!com.dragonflow.Utils.ThreadPool.useThreadPool && m_taskToRun != null) {
//                    m_bIsAlive = true;
//                    m_taskToRun.run();
//                    m_bIsAlive = false;
//                }
//                if (m_createThreadNotify != null) {
//                    m_createThreadNotify.newThreadNotification(this);
//                }
//
//                if (com.dragonflow.Utils.ThreadPool.useThreadPool) {
//                    while (!SingleThread.interrupted()) {
//                        if (m_taskToRun != null) {
//                            m_bIsAlive = true;
//                            try {
//                                m_taskToRun.run();
//                            } catch (Exception exception) {
//                                com.dragonflow.Log.LogManager.log("Error", "ThreadPool: Exception while running a task in thread: " + m_taskToRun.toString() + ", Exception: " + exception.getMessage());
//                            }
//                            m_bIsAlive = false;
//                            synchronized (this) {
//                                m_pool.moveToIdle(this);
//                                m_taskToRun = null;
//                                try {
//                                    wait();
//                                    break;
//                                } catch (InterruptedException interruptedexception) {
//                                    /* empty */
//                                }
//                            }
//
//                        }
//                    }
//                }
//
//                if (m_createThreadNotify != null) {
//                    m_createThreadNotify.endThreadNotification(this);
//                }
//            } catch (Exception exception1) {
//                com.dragonflow.Log.LogManager.log("Error", "ThreadPool: Failed to execute a thread in the thread pool, Exception: " + exception1.getMessage());
//            }
//        }

        public void activate(Runnable runnable) {
            if (!com.dragonflow.Utils.ThreadPool.useThreadPool) {
                m_taskToRun = runnable;
                start();
            } else {
                synchronized (this) {
                    m_taskToRun = runnable;
                    if (!isAlive()) {
                        start();
                    }
                    notify();
                }
            }
        }

        public SingleThread(com.dragonflow.Utils.ThreadPool threadpool1) {
            super();
            m_taskToRun = null;
            m_bCustomObject = null;
            m_bCustProp = false;
            m_bIsAlive = false;
            m_priority = 0;
            m_name = "";
            m_pool = threadpool1;
        }
    }

    static boolean debug = false;

    static boolean useThreadPool = true;

    static int maxIdleThread = -1;

    private java.util.Vector m_idleThreads;

    private java.util.Vector m_busyThreads;

    private int m_maxNumberOfThreads;

    private int m_numOfActiveThreads;

    private boolean m_maxThreadLimit;

    private String m_name;

    private ICreateThreadNotify m_createThreadNotify;

    public ThreadPool(String s, ICreateThreadNotify icreatethreadnotify) {
        m_maxThreadLimit = false;
        m_createThreadNotify = null;
        m_idleThreads = new Vector(10, 10);
        m_busyThreads = new Vector(10, 10);
        m_maxThreadLimit = false;
        m_name = s;
        m_createThreadNotify = icreatethreadnotify;
    }

    public ThreadPool(String s, int i, ICreateThreadNotify icreatethreadnotify) {
        m_maxThreadLimit = false;
        m_createThreadNotify = null;
        m_idleThreads = new Vector(i);
        m_busyThreads = new Vector(i);
        m_maxNumberOfThreads = i;
        m_maxThreadLimit = true;
        m_name = s;
        m_createThreadNotify = icreatethreadnotify;
    }

    public void setPoolName(String s) {
        m_name = s;
    }

    public String getPoolName() {
        return m_name;
    }

    public synchronized SingleThread getThread() {
        SingleThread singlethread = null;
        if (!useThreadPool) {
            singlethread = new SingleThread(this);
            return singlethread;
        }
        if (m_maxThreadLimit && m_numOfActiveThreads == m_maxNumberOfThreads) {
            if (m_idleThreads.size() != 0) {
                singlethread = (SingleThread) m_idleThreads.remove(0);
                m_busyThreads.addElement(singlethread);
            }
            if (debug) {
                String s = "ThreadPool: " + m_name + " exceeded the specified max number of threads: " + m_maxNumberOfThreads + "\n";
                System.out.print(s);
            }
        } else if (m_idleThreads.size() == 0) {
            singlethread = new SingleThread(this);
            m_busyThreads.addElement(singlethread);
            m_numOfActiveThreads ++;
            if (debug) {
                String s1 = "ThreadPool: " + m_name + " created new thread - total threads running: " + m_numOfActiveThreads + "\n";
                System.out.print(s1);
            }
        } else {
            singlethread = (SingleThread) m_idleThreads.remove(0);
            m_busyThreads.addElement(singlethread);
            if (debug) {
                String s2 = "ThreadPool: " + m_name + " reused a thread - total threads running: " + m_numOfActiveThreads + "\n";
                System.out.print(s2);
            }
        }
        return singlethread;
    }

    protected synchronized void moveToIdle(SingleThread singlethread) {
        m_busyThreads.remove(singlethread);
        m_idleThreads.addElement(singlethread);
        if (debug) {
            String s = "ThreadPool: " + m_name + " move to idle - total threads running: " + m_numOfActiveThreads + " total idle threads: " + m_idleThreads.size() + "\n";
            System.out.print(s);
        }
        if (m_idleThreads.size() > 14 && m_idleThreads.size() >= m_numOfActiveThreads / 3 && m_idleThreads.size() >= maxIdleThread) {
            if (debug) {
                String s1 = "ThreadPool: " + m_name + " clean idle threads - total idle threads: " + m_idleThreads.size() + "\n";
                System.out.print(s1);
            }
            int i = m_idleThreads.size() / 2;
            for (int j = 0; j < i; j ++) {
                SingleThread singlethread1 = (SingleThread) m_idleThreads.remove(m_idleThreads.size() - 1);
                singlethread1.interrupt();
                m_numOfActiveThreads --;
            }

        }
    }

    static {
        String s = System.getProperty("ThreadPool.debug");
        if (s != null && s.length() > 0) {
            debug = true;
        }
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_useThreadPool");
        if (s1.equals("no")) {
            useThreadPool = false;
        }
        String s2 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_threadPoolMaxIdle");
        if (s2.length() > 0) {
            maxIdleThread = com.dragonflow.Utils.TextUtils.toInt(s2);
        }
    }
}
