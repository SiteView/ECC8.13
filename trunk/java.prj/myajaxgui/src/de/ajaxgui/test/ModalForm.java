package de.ajaxgui.test;

import de.ajaxgui.Button;
import de.ajaxgui.Form;
import de.ajaxgui.Label;

public class ModalForm extends Form {

	private Label label = null;

	public ModalForm() {
		this.setTitle("This is a modal window");

		Button btn1 = new Button("Button 1");
		btn1.setTop(48);
		btn1.setLeft(20);
		btn1.addClick(this, "btn1Clicked");
		this.add(btn1);

		Button btn2 = new Button("Button 2");
		btn2.setTop(48);
		btn2.setLeft(80);
		btn2.addClick(this, "btn2Clicked");
		this.add(btn2);

		Button btn3 = new Button("Close window");
		btn3.setTop(190);
		btn3.setLeft(230);
		btn3.addClick(this, "btn3Clicked");
		this.add(btn3);

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

	public void btn3Clicked() {
		this.close();
	}
}
