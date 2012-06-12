package de.ajaxgui.test;

import de.ajaxgui.ext.Singleton;

public class MySingleton extends Singleton {

	public static MySingleton getMySingleton() {
		return (MySingleton) MySingleton.get(MySingleton.class);
	}

	public static void setMySingleton(MySingleton ms) {
		MySingleton.setSingleton(MySingleton.class, ms);
	}

	private String text = "";

	public MySingleton(String text) {
		this.text = text;
	}

	public String getText() {
		return text;
	}
}
