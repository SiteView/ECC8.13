package de.ajaxgui.ext;

import java.io.Serializable;

public class Singleton implements Serializable {
	private static transient final ThreadLocal<Singleton> singletonManager = new ThreadLocal<Singleton>();

	protected static Singleton get(Class cl) {
		return SingletonManager.getSingleton(cl);
	}

	protected static void set(Singleton sm) {
		singletonManager.set(sm);
	}

	protected static void setSingleton(Class cl, Singleton sm) {
		Singleton.set(sm);
		SingletonManager.setSingleton(cl, sm);
	}
}
