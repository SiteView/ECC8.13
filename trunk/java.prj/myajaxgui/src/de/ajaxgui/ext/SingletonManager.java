package de.ajaxgui.ext;

import java.util.Hashtable;

public class SingletonManager {
	private static final ThreadLocal<Hashtable<Class, Singleton>> hashtableManager = new ThreadLocal<Hashtable<Class, Singleton>>();

	public static Singleton getSingleton(Class cl) {
		return hashtableManager.get().get(cl);
	}

	public static void setSingleton(Class cl, Singleton sm) {
		hashtableManager.get().put(cl, sm);
	}

	public static void set(Hashtable<Class, Singleton> ht) {
		hashtableManager.set(ht);
	}
}
