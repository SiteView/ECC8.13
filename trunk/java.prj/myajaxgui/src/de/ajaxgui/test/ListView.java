package de.ajaxgui.test;

import de.ajaxgui.Application;

public class ListView extends Application {

	public void run() {
		this.init();
		ListViewMainForm lvmf = new ListViewMainForm();
		this.setMainForm(lvmf);
	}
}
