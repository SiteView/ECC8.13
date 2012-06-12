package de.ajaxgui.test;

import de.ajaxgui.Label;
import de.ajaxgui.MainForm;
import de.ajaxgui.RadioButton;
import de.ajaxgui.RadioGroup;

public class RadioButtonMainForm extends MainForm {

	private Label label = null;

	public RadioButtonMainForm() {
		RadioButton rb1 = new RadioButton("RadioButton 1");
		rb1.setTop(20);
		rb1.setLeft(20);
		rb1.addClick(this, "rb1Clicked");
		this.add(rb1);

		RadioButton rb2 = new RadioButton("RadioButton 2");
		rb2.setTop(40);
		rb2.setLeft(20);
		rb2.addClick(this, "rb2Clicked");
		this.add(rb2);

		RadioButton rb3 = new RadioButton("RadioButton 3");
		rb3.setTop(60);
		rb3.setLeft(20);
		rb3.addClick(this, "rb3Clicked");
		this.add(rb3);

		RadioGroup rg = new RadioGroup();
		rg.add(rb1);
		rg.add(rb2);
		rg.add(rb3);

		label = new Label("xxx");
		label.setTop(100);
		label.setLeft(50);
		this.add(label);
	}

	public void rb1Clicked() {
		label.setText("RadioButton 1 selected");
	}

	public void rb2Clicked() {
		label.setText("RadioButton 2 selected");
	}

	public void rb3Clicked() {
		label.setText("RadioButton 3 selected");
	}
}
