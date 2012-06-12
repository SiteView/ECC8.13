package de.ajaxgui.test;

import de.ajaxgui.Application;

public class ImageStream extends Application {

	public void run() {
		this.init();
		ImageStreamMainForm ismf = new ImageStreamMainForm();
		this.setMainForm(ismf);
	}
}
