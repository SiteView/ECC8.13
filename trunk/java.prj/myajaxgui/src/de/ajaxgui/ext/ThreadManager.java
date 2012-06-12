package de.ajaxgui.ext;

public class ThreadManager {
	private static final ThreadLocal<ThreadManager> threadManager = new ThreadLocal<ThreadManager>();

	public static ThreadManager get() {
		return threadManager.get();
	}

	public static void set(ThreadManager tm) {
		threadManager.set(tm);
	}

	private Thread applicationThread = null;

	private Thread servletThread = null;

	public Thread getApplicationThread() {
		return applicationThread;
	}

	public void setApplicationThread(Thread applicationThread) {
		this.applicationThread = applicationThread;
	}

	public Thread getServletThread() {
		return servletThread;
	}

	public void setServletThread(Thread servletThread) {
		this.servletThread = servletThread;
	}
}
