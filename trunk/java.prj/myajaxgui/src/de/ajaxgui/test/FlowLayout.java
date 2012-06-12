package de.ajaxgui.test;

import de.ajaxgui.Application;

public class FlowLayout extends Application {

	public void run() {
		this.init();
		FlowLayoutMainForm flmf = new FlowLayoutMainForm();
		this.setMainForm(flmf);
	}
}
