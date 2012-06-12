package de.ajaxgui.test;

import de.ajaxgui.Application;

public class Singleton extends Application {

	public void run() {
		this.init();

		MySingleton ms = new MySingleton("This is a singleton!");
		MySingleton.setMySingleton(ms);

		SingletonMainForm smf = new SingletonMainForm();
		this.setMainForm(smf);
		int i = 0;
	}
}
