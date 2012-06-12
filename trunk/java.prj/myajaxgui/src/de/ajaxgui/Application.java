package de.ajaxgui;

import java.util.Hashtable;

import de.ajaxgui.ext.ComponentManager;
import de.ajaxgui.ext.EventManager;
import de.ajaxgui.ext.JsGenerator;
import de.ajaxgui.ext.Singleton;
import de.ajaxgui.ext.SingletonManager;
import de.ajaxgui.ext.ThreadManager;

public class Application extends Thread {

	private JsGenerator jg = null;

	private ComponentManager cm = null;

	private ThreadManager tm = null;

	private EventManager em = null;

	private Hashtable<Class, Singleton> singletonHt = null;

	public void setup(JsGenerator jg, ComponentManager cm, ThreadManager tm,
			EventManager em, Hashtable<Class, Singleton> singletonHt) {
		this.jg = jg;
		this.cm = cm;
		this.tm = tm;
		this.em = em;
		this.singletonHt = singletonHt;
	}

	public void init() {
		JsGenerator.set(jg);

		ComponentManager.set(cm);

		ThreadManager.set(tm);

		EventManager.set(em);

		SingletonManager.set(singletonHt);
	}

	public void setMainForm(MainForm mf) {
		mf.show();
	}
}
