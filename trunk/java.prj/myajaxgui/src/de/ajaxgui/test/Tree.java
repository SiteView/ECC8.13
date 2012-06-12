package de.ajaxgui.test;

import de.ajaxgui.Application;

public class Tree extends Application {

	public void run() {
		this.init();
		TreeMainForm tmf = new TreeMainForm();
		this.setMainForm(tmf);
	}
}
