package de.ajaxgui.test;

import de.ajaxgui.Application;

public class CheckBox extends Application {

	public void run() {
		this.init();
		CheckBoxMainForm cbmf = new CheckBoxMainForm();
		this.setMainForm(cbmf);
	}
}
