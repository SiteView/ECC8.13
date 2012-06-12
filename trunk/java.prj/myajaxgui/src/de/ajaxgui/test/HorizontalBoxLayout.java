package de.ajaxgui.test;

import de.ajaxgui.Application;

public class HorizontalBoxLayout extends Application {

	public void run() {
		this.init();
		HorizontalBoxLayoutMainForm hblmf = new HorizontalBoxLayoutMainForm();
		this.setMainForm(hblmf);
	}
}
