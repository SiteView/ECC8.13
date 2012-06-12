package de.ajaxgui.test;

import de.ajaxgui.Application;

public class Image extends Application {

	public void run() {
		this.init();
		ImageMainForm imf = new ImageMainForm();
		this.setMainForm(imf);
	}
}
