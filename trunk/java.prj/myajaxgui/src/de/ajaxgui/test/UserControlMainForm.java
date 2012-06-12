package de.ajaxgui.test;

import de.ajaxgui.Button;
import de.ajaxgui.Label;
import de.ajaxgui.MainForm;

public class UserControlMainForm extends MainForm {

	private Label label = null;

	public UserControlMainForm() {
		de.ajaxgui.UserControl uc = new de.ajaxgui.UserControl();
		uc.setTop(48);
		uc.setLeft(20);
		this.add(uc);

		Button btn1 = new Button("Button 1");
		btn1.setTop(48);
		btn1.setLeft(20);
		btn1.addClick(this, "btn1Clicked");
		uc.add(btn1);

		Button btn2 = new Button("Button 2");
		btn2.setTop(48);
		btn2.setLeft(80);
		btn2.addClick(this, "btn2Clicked");
		uc.add(btn2);

		label = new Label("No news");
		label.setTop(80);
		label.setLeft(50);
		uc.add(label);
	}

	public void btn1Clicked() {
		label.setText("Button 1 clicked");
	}

	public void btn2Clicked() {
		label.setText("Button 2 clicked");
	}
}
