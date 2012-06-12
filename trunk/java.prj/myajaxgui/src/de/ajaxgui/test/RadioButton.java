package de.ajaxgui.test;

import de.ajaxgui.Application;

public class RadioButton extends Application {

	public void run() {
		this.init();
		RadioButtonMainForm rbmf = new RadioButtonMainForm();
		this.setMainForm(rbmf);
	}
}
