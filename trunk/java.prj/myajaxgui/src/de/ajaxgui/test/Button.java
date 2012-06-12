package de.ajaxgui.test;

import de.ajaxgui.Application;

public class Button extends Application {

	public void run() {
		this.init();
		ButtonMainForm bmf = new ButtonMainForm();
		this.setMainForm(bmf);
	}
}
