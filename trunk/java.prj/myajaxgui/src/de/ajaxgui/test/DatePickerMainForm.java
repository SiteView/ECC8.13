package de.ajaxgui.test;

import de.ajaxgui.DatePicker;
import de.ajaxgui.MainForm;
import de.ajaxgui.TextField;

public class DatePickerMainForm extends MainForm {

	public DatePickerMainForm() {
		TextField tf = new TextField();
		tf.setLocation(20, 20);
		tf.setWidth(80);
		this.add(tf);

		DatePicker dtp = new DatePicker(tf);
		dtp.setLocation(105, 20);
		this.add(dtp);
	}
}
