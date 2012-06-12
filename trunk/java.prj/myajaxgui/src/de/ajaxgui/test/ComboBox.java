package de.ajaxgui.test;

import de.ajaxgui.Application;

public class ComboBox extends Application {

	public void run() {
		this.init();
		ComboBoxMainForm cbmf = new ComboBoxMainForm();
		this.setMainForm(cbmf);
	}
}
