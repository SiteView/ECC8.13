package de.ajaxgui.test;

import de.ajaxgui.Application;

public class Modal extends Application {

	public void run() {
		this.init();
		ModalMainForm mmf = new ModalMainForm();
		this.setMainForm(mmf);
	}
}
