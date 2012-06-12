package de.ajaxgui.test;

import de.ajaxgui.Application;

public class GridLayout extends Application {

	public void run() {
		this.init();
		GridLayoutMainForm glmf = new GridLayoutMainForm();
		this.setMainForm(glmf);
	}
}
