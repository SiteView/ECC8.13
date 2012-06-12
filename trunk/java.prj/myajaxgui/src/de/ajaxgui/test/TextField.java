package de.ajaxgui.test;

import de.ajaxgui.Application;

public class TextField extends Application {

	public void run() {
		this.init();
		TextFieldMainForm tfmf = new TextFieldMainForm();
		this.setMainForm(tfmf);
	}
}
