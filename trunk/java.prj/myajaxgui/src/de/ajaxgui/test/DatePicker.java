package de.ajaxgui.test;

import de.ajaxgui.Application;

public class DatePicker extends Application {

	public void run() {
		this.init();
		DatePickerMainForm dtpmf = new DatePickerMainForm();
		this.setMainForm(dtpmf);
	}
}
