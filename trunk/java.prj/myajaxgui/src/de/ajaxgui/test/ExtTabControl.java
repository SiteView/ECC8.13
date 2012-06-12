package de.ajaxgui.test;

import de.ajaxgui.Application;

public class ExtTabControl extends Application {

	public void run() {
		this.init();
		ExtTabControlMainControl etcmf = new ExtTabControlMainControl();
		this.setMainForm(etcmf);
	}
}
