package de.ajaxgui.test;

import de.ajaxgui.Application;

public class TabControl extends Application {

	public void run() {
		this.init();
		TabControlMainForm tcmf = new TabControlMainForm();
		this.setMainForm(tcmf);
	}
}
