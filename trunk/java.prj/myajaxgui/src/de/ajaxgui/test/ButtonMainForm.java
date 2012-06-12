package de.ajaxgui.test;

import de.ajaxgui.Button;
import de.ajaxgui.Label;
import de.ajaxgui.MainForm;

public class ButtonMainForm extends MainForm {

	private Label label = null;

	public ButtonMainForm() {
		Button btn1 = new Button("Button 1");
		btn1.setTop(48);
		btn1.setLeft(20);
		btn1.addClick(this, "btn1Clicked");
		this.add(btn1);

		Button btn2 = new Button("Button 2", "themes/icons/kids/16/apply.png");
		btn2.setTop(48);
		btn2.setLeft(80);
		btn2.addClick(this, "btn2Clicked");
		this.add(btn2);

		label = new Label("No news");
		label.setTop(80);
		label.setLeft(50);
		this.add(label);
	}

	public void btn1Clicked() {
		label.setText("Button 1 clicked");
	}

	public void btn2Clicked() {
		label.setText("Button 2 clicked");
	}
}
