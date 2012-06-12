package de.ajaxgui.test;

import de.ajaxgui.CheckBox;
import de.ajaxgui.MainForm;

public class CheckBoxMainForm extends MainForm {

	private CheckBox cb1 = null;

	private CheckBox cb2 = null;

	public CheckBoxMainForm() {
		cb1 = new CheckBox("This is CheckBox 1");
		cb1.setTop(20);
		cb1.setLeft(20);
		cb1.addCheckedChanged(this, "cb1Clicked");
		this.add(cb1);

		cb2 = new CheckBox("And this is CheckBox 2, which is checked");
		cb2.setChecked(true);
		cb2.setTop(50);
		cb2.setLeft(20);
		cb2.addCheckedChanged(this, "cb2Clicked");
		this.add(cb2);
	}

	public void cb1Clicked() {
		if (cb1.isChecked())
			cb1.setText("CheckBox 1 is checked");
		else
			cb1.setText("CheckBox 1 is not checked");
	}

	public void cb2Clicked() {
		if (cb2.isChecked())
			cb2.setText("CheckBox 2 is checked");
		else
			cb2.setText("CheckBox 2 is not checked");
	}

}
