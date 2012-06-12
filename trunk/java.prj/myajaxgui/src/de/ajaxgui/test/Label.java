package de.ajaxgui.test;

import de.ajaxgui.Application;

public class Label extends Application {

	public void run() {
		this.init();
		LabelMainForm lmf = new LabelMainForm();
		this.setMainForm(lmf);
	}
}
