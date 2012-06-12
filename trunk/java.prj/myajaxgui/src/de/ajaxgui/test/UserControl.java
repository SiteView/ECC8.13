package de.ajaxgui.test;

import de.ajaxgui.Application;

public class UserControl extends Application {

	public void run() {
		this.init();
		UserControlMainForm ucmf = new UserControlMainForm();
		this.setMainForm(ucmf);
	}
}
